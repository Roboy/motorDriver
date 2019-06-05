#include "motorControl.h"
#include "pwm.h"
#include "initIO.h"
#include "spiFunctions.h"
#include "can.h"
#include "DEEEmulation.h"
#include "timers.h"
#include "qei.h"
#include "adc.h"
#include "dma.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define MOTOR_TEST_RAMP_ON 0
#define TEST_CONFIG_DATA 0
#define MAX_PWM_DRIVE_VALUE 4000

char welcomeString[]="Welcome to the MyoMotorDriver!";
char dataString[2024];
//define the number of control cycles that can pass without communcation from the MyoGanglion
int startUpTimer; //counts the time after reset
int watchDogCounter;

int canWatchDogCounter;
int maxCanWatchDogTimeCounter;

float error, error_1,error_int; //local PID parameters
float Kp, Kd, Ki;

int actualMotorCurrent;

float referenceValue;
float actualValue;

float deltaTime;
float oneOverDeltaTime;

int positiveSaturationOfPWMOutput;
int negativeSaturationOfPWMOutput;

int rawIphaseAcurrent;
int rawIphaseBcurrent;

unsigned int canDummyData[4];
MOTOR_CONTROL_STATE motorControlState;
EEPROM_DATA eePromData;
unsigned eePromWriteRequired; //will be set if config message arrives
unsigned configLoadRequested;
unsigned configLoadComplete;
unsigned int canSendData[4]; //an array to fill for sending CAN information
unsigned int startUpMessageSent=0;


/*
 * returns the filted motorCurent
 * TODO: convert to appropriate units
 */
int getFilteredMotorCurrent(void)
{
    return (int) actualMotorCurrent * eePromData.currentConversionFactor; //co
}

float getDeltaTime()
{
    return deltaTime;
}

float getOneOverDeltaTime()
{
    return oneOverDeltaTime;
}

void setDeltaTimes()
{
    deltaTime=eePromData.cycleTimeIn100usIncrements * 0.1008 * 0.001; //delta time in seconds

    //calculate CAN_WATCHDOG_TIME LIMIT for a 300ms time out

    maxCanWatchDogTimeCounter=CAN_WATCHDOG_TIME_IN_SECONDS/deltaTime;


    oneOverDeltaTime=1/deltaTime;
}

void setPWMSaturation()
{
    if ((eePromData.positiveSaturation>=0.0)&&(eePromData.positiveSaturation<=100.0)&&
       (eePromData.negativeSaturation>=0.0)&&(eePromData.negativeSaturation<=100.0))
    {

        //adjust saturation values
        positiveSaturationOfPWMOutput=(int) MAX_PWM_DRIVE_VALUE*eePromData.positiveSaturation/100;
        negativeSaturationOfPWMOutput=(int) - MAX_PWM_DRIVE_VALUE*eePromData.negativeSaturation/100;
    }
    else //just leave the saturation values at 100%
    {
        positiveSaturationOfPWMOutput=(int) MAX_PWM_DRIVE_VALUE;
        negativeSaturationOfPWMOutput=(int) - MAX_PWM_DRIVE_VALUE;
    }



}
void resetMotorController()
{
    startUpTimer=0;
    startUpMessageSent=0;
    eePromWriteRequired=0; //0 after reset, will be set if config message arrives
    configLoadRequested=0; //will be set when first configuration CAN messge arrives
    configLoadComplete=0; //will be set when all configuration bits have been transmitted and stored
    motorControlState=MOTOR_RESET;
    RESET_WATCHDOG;
    brakeMotor();
    SPI1Setup();
    resetSPI();
}

void setConfigDataInEEProm()
{
    int i;
    //LED1=0; //switch off LED1
    if (eePromWriteRequired==1)//variable set by configuration CAN message
    {
        //LED1=1; //switch on to indicate that EEPROM write was performed
        _NSTDIS=1; //disable all interrupts during write
        for(i=0;i<(sizeof(EEPROM_DATA)>>1);i++)
        {
               DataEEWrite(eePromData.dataStream[i],i);
        }
        _NSTDIS=0; //enable interrupts again
    }
}


void getConfigDataFromEEProm()
{
    int i;
    int eePromSize;
    //read out the eeprom
    eePromSize=(sizeof(EEPROM_DATA)>>1);
    for(i=0;i<eePromSize;i++)
    {
        eePromData.dataStream[i]=DataEERead(i);
    }

    //for test purposes we can manually set EEPROM parameters
    if (TEST_CONFIG_DATA==1)
    {
        eePromData.ControlMode=0xFFFF;
        eePromData.cycleTimeIn100usIncrements=100;
        eePromData.DGain=0.05;
        eePromData.IGain=0.07;
        eePromData.PGain=1.0;
        eePromData.EncoderCountsPerRevolution=2000;
    }

}

/*
 *  unsigned ControlMode; //input 0xFFFF: extern (SPI driven),default
 *                                //       0: open loop mode
                                  //       1: local position
                                  //       2: local velocity
                                  //       3: local current
            unsigned cycleTimeIn100usIncrements; //only valid when local control
                                                 // has been selected
            float PGain;
 *          float IGain;
            float DGain;
 *          float positiveSaturation;
 *          float negativeSaturation;

            unsigned EncoderCountsPerRevolution;
            unsigned referenceValueMessageId;
                    //message Format: 4byte float, position, velocity or current
            unsigned actualValueMessageId;
                    //message Format: 4byte float int position, velocity or current
            unsigned pidGainsMessageId;
                    //message Format: 2byte index:   0=no gain config
                    //                               1=Kp
                    //                               2=kd
                    //                               3=ki

                    //                4byte float Kd,Kd or Ki, depending on index (or don't care)
                    //                2byte output on (0) or off (1)
 */

void printConfigData()
{
    int i;
    int dataConfigured=0;
    int dataCounter=0;
    //go through all data in eeprom and check if motor driver has been configured

    for (i=0;i<(sizeof(EEPROM_DATA)>>1);i++)
    {
        if (eePromData.dataStream[i]!=0xffff) //all eeProm bytes are 0xff after reprogramming
        {
            dataConfigured=1;
            dataCounter++;
        }

    }

    if (dataConfigured==1)
    {
        snprintf(dataString,sizeof(dataString), ""
        "Motor Configuration:\n"
        "                    DataLength: %d \n"
        "                    ControlMode: %d\n"
        "                    CycleTimeIn100usIncrements: %d \n"
        "                    PGain: %12.4f  \n"
        "                    IGain: %12.4f  \n"
        "                    DGain: %12.4f  \n"
        "                    positiveSaturation: %12.4f \n"
        "                    negativeSaturation: %12.4f \n"
        "                    integratorSaturation: %12.4f \n"
         "                   currentConversionFactor: %12.4f \n"
        "                    encoderCountsPerRevolution: %d \n"
        "                    referenceValueMessageId:  0x%x\n"
        "                    actualValueMessageId: 0x%x\n"
        "                    pidGainsMessageId: 0x%x\n"
        "                    nodeID: %d",sizeof(EEPROM_DATA),
                eePromData.ControlMode,eePromData.cycleTimeIn100usIncrements ,eePromData.PGain,
                eePromData.IGain, eePromData.DGain, eePromData.positiveSaturation, eePromData.negativeSaturation, eePromData.integratorSaturation,eePromData.currentConversionFactor , eePromData.EncoderCountsPerRevolution,
                eePromData.referenceValueMessageId, eePromData.actualValueMessageId, eePromData.pidGainsMessageId,
                eePromData.nodeID);

    }
    else
    {

        sprintf(dataString,"Device not configured for CAN, data checked: %d",dataCounter);
    }
    CANTransmitString(STRING_MESSAGE+eePromData.nodeID, dataString);

}

void setConfigurationData(unsigned * canData,unsigned dataLength)
{

    int i;
    int eePromIndex;
    unsigned int configDataLength;
    configDataLength = (sizeof(EEPROM_DATA)>>1);
    configLoadRequested=1;

    for (i=0;i<3;i++) //with each config message we write 3 config words
    {
        eePromIndex=canData[0]+i;
        if (eePromIndex<configDataLength)//we measure bytes not words
        {
            eePromWriteRequired=1;
            eePromData.dataStream[eePromIndex]=canData[i+1];
            if (eePromIndex==configDataLength-1)
            {
                //the last config bit has been written
                configLoadComplete=1;
                //canData[0]=eePromIndex;
                //canData[1]=0xAAAA;
                //CANTransmit(TEST_MESSAGE_01, canData, 4);
            }
        }
    }
    CANTransmit(CONFIGURATION_REPLY_ID, canData, 4);
}


void setMotorDriveDcAndDirection(unsigned int dutyCycle, int direction)
{

    MOTOR_BRAKE = OPEN;
    setPWMDutyCycle(dutyCycle);
    MOTOR_DIRECTION = direction;

}

void setMotorDrive(int driveValue) {
    if (driveValue < 0)
    {
        driveValue = -driveValue;
        setMotorDriveDcAndDirection(driveValue, ANTICLOCKWISE);
    }
    else
    {
        setMotorDriveDcAndDirection(driveValue, CLOCKWISE);
    }
}

/**!brief interfaces to PWM generator, making sure the float parameter does not exceed the PWM int range
 *
 * @param driveValue is the control output to supply the PWM generator
 */

void driveMotor(float driveValue)
{
    int driveSignal;


    //restrict to EEPROM configurable saturation

                //canData[0]=driveValue;
                //canData[1]=positiveSaturationOfPWMOutput;
                //canData[2]=negativeSaturationOfPWMOutput;
                //canData[3]=0;
                //CANTransmit(TEST_MESSAGE_01, canData, 4);


    if (driveValue > positiveSaturationOfPWMOutput)
    {
        driveValue=positiveSaturationOfPWMOutput;
    }
    else if(driveValue<negativeSaturationOfPWMOutput)
    {
        driveValue=negativeSaturationOfPWMOutput;
    }



    //restrict to stay within the logical limits, function of the PWM module
    if (driveValue>MAX_PWM_DRIVE_VALUE)
    {
        driveSignal=MAX_PWM_DRIVE_VALUE;
    }
    else if (driveValue<-MAX_PWM_DRIVE_VALUE)
    {
        driveSignal=-MAX_PWM_DRIVE_VALUE;
    }
    else
    {
        driveSignal=(int)driveValue;
    }
    setMotorDrive(driveSignal);
}

void clearPIDHistory(void)
{
    error_int=0.0;
    error_1=0.0;


}

void setReferenceData(unsigned * canData,unsigned dataLength)
{
    _NSTDIS=1; //disable all interrupts during write
    memcpy(&referenceValue,canData,4); //copy data
    _NSTDIS=0; //enable again
}

void setPidGains(unsigned * canData,unsigned dataLength)
{
    float tempGainValue;

                    //message Format: 2byte index:   0=no gain config
                    //                               1=Kp
                    //                               2=kd
                    //                               3=ki

                    //                4byte float Kd,Kd or Ki, depending on index (or don't care)
                    //                2byte output on (0) or off (1)
    _NSTDIS=1; //disable all interrupts during write
    memcpy(&tempGainValue,(canData+1),4); //copy data into temp float variable


    //copy data to correct location depending on which index has been set
    if (canData[0]==1)
    {
        eePromData.PGain=tempGainValue;
    }
    else if (canData[0]==2)
    {
        eePromData.IGain=tempGainValue;

    }
    else if (canData[0]==3)
    {
        eePromData.DGain=tempGainValue;
    }

    else //for any other INDEX just print the PID gains and complete configuration
    {
             printConfigData();
    }
    _NSTDIS=0; //disable all interrupts during write
}


void filterDCCurrentMeasurements()
{
    int IphaseA, IphaseB, motorCurrent, Vsupply, SensorFieldStrength;
    static unsigned int counter=0;
    static int current[16];
    static unsigned currentAverage=0;
    int index;


        LED1=1 ;//
   //process data
    //data should be in the following order5


    //signal    index
    //================
    //Vsupply                       : 0
    //Displacement Field Strength   : 1

    //IphaseA                       : 4
    //IPhaseB                       : 5

    //get currents and subtract nominal offset
    //Vsupply, SensorFieldStrength;
    IphaseA= adcData[2]- ADCZEROOFFSET;// was 4, now 2 with simsam from S/H 2
    IphaseB= adcData[3]- ADCZEROOFFSET; //  was 5, now 3 with simsam from S/H 3


    //make currents available for zero-Offset calculation
    rawIphaseAcurrent=IphaseA;
    rawIphaseBcurrent=IphaseB;


    //correct current offsets

    IphaseA=IphaseA- IphaseAOffset;
    IphaseB=IphaseB- IphaseBOffset;

    //rectify currents

    if (IphaseA<0)
       IphaseA=-IphaseA;

    if (IphaseB<0)
        IphaseB=-IphaseB;


    //set currents below the noise level to 0

    /*
    if (IphaseB<NOISE_FLOOR)
        IphaseB=0;
    if (IphaseA<NOISE_FLOOR)
        IphaseA=0;

     */
    // decide which current is 0 and then transmit the other one

    if (IphaseA>IphaseB)
    {
        motorCurrent=IphaseA;
    }
    else
    {
        motorCurrent=IphaseB;
    }




    //debugging the offset values for different channels

    //motorCurrent=IphaseB;

    //now we run the motor current through a moving average filter



    index=counter%16; //gets an array index between 0 and 15
    currentAverage=currentAverage-current[index]; //subtract oldest value from current sum

    current[index]= motorCurrent; //update current in array

    currentAverage=currentAverage+current[index]; //update the average

    actualMotorCurrent=(currentAverage+8)>>4; //divide by 16, take care of rounding,  and supply to the rest of the system
    counter++; //increment
        //LED1=0;


        //test a2d
        //motorCurrent=adcData[2];

        LED1=0;

}


int getAnalogCurrentData()
{


  //  int IphaseA, IphaseB, motorCurrent;
   //we start the the auto-sampling

      //we make the old adc data unvalid
    //LED1=1;
   // invalidateADCData();
    AD1CON1bits.ASAM		= 1;//start the ADC converter


    //return actualMotorCurrent; //global variable that is filled by filter in DMA ISR
    return 1;
}


void localPIDController(void)
{

    float deltaError;
    float outPut;
    float sinusoidalTestOutput;
    float actualVelocity;
    static float controlTime=0;
    float motorCurrentMeasurement;

    int encoder2Value;

    long currentEncoderPosition;


    // defined globallyfloat error, error_1,error_in

   // LED1=1;
    //disable interrupts to make sure we have consistent data
    _NSTDIS=1;
    GET_ENCODER (currentEncoderPosition); //to be transmitted on CAN bus
    //disable interrupts to make sure we have consistent data
    _NSTDIS=0;
    motorCurrentMeasurement=(float) actualMotorCurrent * 805.664E-3;

    actualVelocity=getVelocityInRadPerSecond();
    actualValue=getPositionInRad();
    if ((eePromData.ControlMode==2)||(eePromData.ControlMode==0)) //for velocity or open loop mode we differntiate
    {
        actualValue=actualVelocity;
        //actualValue=motorCurrentMeasurement;
    }


    error=referenceValue-actualValue;   //control errro
    error_int=error_int+error*getDeltaTime();  //simple integration


    //limit the integration error

    if (error_int>eePromData.integratorSaturation)
    {
        error_int=eePromData.integratorSaturation;
    }

    if (error_int<-eePromData.integratorSaturation)
    {
        error_int=-eePromData.integratorSaturation;
    }

    deltaError=(error-error_1)*getOneOverDeltaTime(); //error differntiation
    error_1=error;



    //pid controller
    outPut=eePromData.PGain*error+eePromData.DGain*deltaError+eePromData.IGain*error_int;

    INCREMENT_CAN_WATCHDOG;

    if (canWatchDogCounter>=maxCanWatchDogTimeCounter)
    {
        if ((eePromData.ControlMode==2)||(eePromData.ControlMode==3)||(eePromData.ControlMode==0)) //velocity or current control
        {
            outPut=0; //do not drive if CAN connection is lost
            canDummyData[0]=0xAAAA; canDummyData[1]=0xBBBB; canDummyData[2]=0xCCCC; canDummyData[3]=C1RXOVF1;
            CANTransmit(TEST_MESSAGE_01+eePromData.nodeID, canDummyData, 4);
               while (C1TR01CONbits.TXREQ1); //wait until message is out
        }
    }


    if (eePromData.ControlMode==0)  //this is open loop control
    {
        outPut=referenceValue;
    }


    //generate a test output signal
    //controlTime=controlTime+0.0001008*eePromData.cycleTimeIn100usIncrements;
    //sinusoidalTestOutput=sin(2*3.14*1*controlTime);
    //sinusoidalTestOutput=sinusoidalTestOutput*eePromData.PGain*eePromData.IGain*eePromData.DGain;

    //drive the motor
    driveMotor(outPut);
    //transmit actual value on the bus

    //get encoder input two and transmit this
    //TODO: This is  a hack for testing the Myorobotics toolkit!!!
    GET_SPRING(encoder2Value);
    CANTransmitActualControlValue( actualValue ,currentEncoderPosition /*sinusoidalTestOutput+actualValue*/);
    //wait until transmission complete
    while (C1TR01CONbits.TXREQ1);
    CANTransmitAdditionalInternalStates(actualMotorCurrent,encoder2Value,0,0 );

   //LED1=0;

}
void brakeMotor()
{
    setPWMDutyCycle(0);
    MOTOR_BRAKE = LOCKED;
}


//called cyclicly in timer interrupt (
void motorControlLoop() {
    int dutyCycle;
#if (MOTOR_TEST_RAMP_ON==1)

    static unsigned int dc = 0;
    static int increment = 1;
    static int dir = -1;
    setMotorDrive(dc, dir);
    if (dc == 6000) {
        increment = -1;
    } else if (dc == 0) {
        increment = 1;
        if (dir == 1)//toogle motor turning direction
        {
            dir = -1;
        } else {
            dir = +1;
        }
    }
    dc = dc + increment;

#else

    /*
     * motor control loop
     *
     *

     */

     //the watchdog is incremented here and is reset
     //when a complete SPI data package has arrived
    INCREMENT_WATCHDOG;



    switch (motorControlState)

    {

        case MOTOR_RESET:
              //LED1=~LED1; //toggle LED1
              brakeMotor();
              getAnalogCurrentData();
            if (startUpMessageSent==0)//only send once
            {
                CANTransmitString(STRING_MESSAGE+eePromData.nodeID, welcomeString);

                CANTransmit(WAKE_UP_MSG_BASE_ID+eePromData.nodeID, canSendData, 0);
                startUpMessageSent=1;
            }


            //  LED1=~LED1;
              calculateOffset(rawIphaseAcurrent,rawIphaseBcurrent);
            startUpTimer++;
            RESET_WATCHDOG;
            if (configLoadRequested==1)
            {
                motorControlState=CONFIG_LOADING;
            }
            if (startUpTimer>=START_UP_TIME)
            {
                LED1=0;
                motorControlState=MOTOR_RUNNING;
                //before we go to the motor running state we set the time to the appropriate value
                initTimer1(63*eePromData.cycleTimeIn100usIncrements);
                setDeltaTimes();
                setPWMSaturation();
                startTimer1();


            }
        break;

        case CONFIG_LOADING:
                // configLoadRequested=0; //will be set when first configuration CAN messge arrives
                //configLoadComplete=0;
            if (configLoadComplete==1)
            {


                //store current config data
                setConfigDataInEEProm();
                motorControlState=CONFIG_STORED;

                //send CAN messages with current config data
                //CANTransmit(eePromData.CanID, &(eePromData.dataStream[1]), 4);
                canDummyData[0]=0xAAAA; canDummyData[1]=0xBBBB; canDummyData[2]=0xCCCC; canDummyData[3]=0xDDDD;
             //   CANTransmit(TEST_MESSAGE_01+eePromData.nodeID, canDummyData, 4);

            }

        break;

        case CONFIG_STORED:
            motorControlState=MOTOR_RUNNING;
           // canDummyData[0]=0x1111; canDummyData[1]=0x1111; canDummyData[2]=0x1111; canDummyData[3]=0x1111;
            //CANTransmit(TEST_MESSAGE_01, canDummyData, 4);
           printConfigData();
            RESET_WATCHDOG;//we reset the watchdog
            //before we go to the motor running state we set the time to the appropriate value
            initTimer1(63*eePromData.cycleTimeIn100usIncrements);
            setPWMSaturation();
            setDeltaTimes();
            startTimer1();

        break;
        case MOTOR_WATCHDOG_EVENT:
             motorControlState=MOTOR_STOP;
              canDummyData[0]=0xFFFF; canDummyData[1]=0xFFFF; canDummyData[2]=0xFFFF; canDummyData[3]=0xFFFF;
              CANTransmit(TEST_MESSAGE_01+eePromData.nodeID, canDummyData, 4);
             //resetMotorController(); //resets SPI and motor control parameters

            brakeMotor();
            SPI1Setup();
            resetSPI();

        break;

        case MOTOR_STOP:
            //here we wait until SPI communication restarts
            if (watchDogCounter<CONTROL_WATCHDOG_MAX)
            {
                //we are communicating again
                motorControlState=MOTOR_RUNNING;
            }

        break;

        case MOTOR_RUNNING:
            //normal control operation
            //lets get the reference from SPI
           // CANTransmit(TEST_MESSAGE_01+eePromData.nodeID , canDummyData, 0);
            //LED1=~LED1;

            if (watchDogCounter>=CONTROL_WATCHDOG_MAX)
            {
                //we have a watchdog event and should go into error mode
                motorControlState=MOTOR_WATCHDOG_EVENT;

            }

            //now we distinguish between SPI driven control or local control

            if (eePromData.ControlMode==0xFFFF) //spi control
            {
                if (getSPIReference(&dutyCycle) == 1)
                {
                    //valid data received
                    //setMotorDrive(dutyCycle);
                }
            }
            else //local control
            {
                RESET_WATCHDOG;//we reset the watchdog
                //
                getAnalogCurrentData();
                localPIDController();
            }


        break;


    }
#endif


}
