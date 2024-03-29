/*
 * muscleDriverCANInterface.cpp
 *
 *  Created on: 18 Dec 2013
 *      Author: alex
 */

#include "FlexRayUSBInterface.h"
#include <stdio.h>
#include <iostream>
#include <ios>
#include <iomanip>

#include <QSettings>
#include <QDir>
#include <QTextStream>
#include "ftd2xx.h"
#include "WinTypes.h"
#include  "../../../myode/src/eu.myode.Myorobot/robot/CommunicationData.h"
/*
 *
 */

/*
 * */



void FlexRayUSBInterface::initSafeCommandFrame()
{
	comsCommandFrame InitCommandFrame1[GANGLIONS_PER_CONTROL_FRAME];
	comsCommandFrame InitCommandFrame2[GANGLIONS_PER_CONTROL_FRAME];
	control_Parameters_t InitControlParams;

	// Command all motors connected to all Ganglions into disabled mode, also set to raw mode with 0% pwm activation

	cout<<endl<<endl<<endl<<"CREATING SAFE COMMAND FRAME!"<<endl;
	for(int j=0;j<3;j++)
	{
			for(int i=0;i<4;i++)
			{
				InitCommandFrame1[j].ControlMode[i]   = Raw;
				InitCommandFrame1[j].OperationMode[i] = Disable; //Initialise; //Run
				InitCommandFrame1[j].sp[i] 		  = 0;

				InitCommandFrame2[j].ControlMode[i]   = Raw;
				InitCommandFrame2[j].OperationMode[i] = Disable; //Initialise //Run;
				InitCommandFrame2[j].sp[i] 		  = 0;
			}
	}

	//set the dynamic config parameters to 0
	InitControlParams.tag = 0;			// sint32
	InitControlParams.outputPosMax = 0;	// sint32			// set arbitary max position
	InitControlParams.outputNegMax = 0;		// sint32
	InitControlParams.spPosMax = 0;		// float32
	InitControlParams.spNegMax = 0;		// float32
	InitControlParams.timePeriod = 10000;		// float32		//in us	// set time period to avoid error case
	InitControlParams.radPerEncoderCount = 0;	// float32
	InitControlParams.polyPar[0] = 0;		// float32
	InitControlParams.polyPar[1] = 0;
	InitControlParams.polyPar[2] = 0;
	InitControlParams.polyPar[3] = 0;
	InitControlParams.torqueConstant = 0;	// float32

	InitControlParams.params.pidParameters.integral = 0;	// float32
	InitControlParams.params.pidParameters.pgain = 0;		// float32
	InitControlParams.params.pidParameters.igain = 0;		// float32
	InitControlParams.params.pidParameters.dgain = 0;		// float32
	InitControlParams.params.pidParameters.forwardGain = 0;	// float32
	InitControlParams.params.pidParameters.deadBand = 0;	// float32
	InitControlParams.params.pidParameters.lastError = 0;	// float32
	InitControlParams.params.pidParameters.IntegralPosMax = 0;	// float32
	InitControlParams.params.pidParameters.IntegralNegMax = 0;	// float32
	cout<<"Init Data Set."<<endl;

	cout<<"Updating Command Frame"<<endl;
	sendCommandFrame(InitCommandFrame1, InitCommandFrame2, &InitControlParams);

}



/* ! \brief slot calls data exchange method.
 *
 *	comsCommandFrame CommandFrame1[6]; //for ganglion 1,2,3,4,5,6
 *	control_Parameters_t ControlParams; //motor control parameters
 */

void FlexRayUSBInterface::sendAllCommandFrames( comsCommandFrame * completeCommandFrames, control_Parameters_t * ControlParams)
{
	comsCommandFrame allCommandFrames[NUMBER_OF_GANGLIONS];
	control_Parameters_t oneSetOfControlParameters;


	//memcpy((void *)&dataset[0], CommandFrame1, sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME );
	memcpy((void *)&allCommandFrames[0] , completeCommandFrames,sizeof(allCommandFrames) );
	memcpy (& oneSetOfControlParameters,ControlParams ,sizeof(oneSetOfControlParameters));

//	cout<<"Command Frame Size: "<<sizeof(allCommandFrames)<<endl;
//	cout<<"Parameter Frame Size: "<<sizeof(oneSetOfControlParameters)<<endl;

	int a=6;

	/*
	cout<<"printing several parameters:"<<dec<< a<< endl;
			for (int j=0;j<NUMBER_OF_GANGLIONS;j++)
			{
				for (int k=0;k<4; k++)
				{

					cout<< "allCommandFrames["<<j<<"].OperationMode["<<k<<"]: "<<(int) allCommandFrames[j].OperationMode[k]<<endl;
					cout<<" allCommandFrames["<<j<<"].ControlMode["<<k<<"]: "<<(int) allCommandFrames[j].ControlMode[k]<<endl;
					cout<<" allCommandFrames["<<j<<"].sp["<<k<<"]: "<<allCommandFrames[j].sp[k]<<endl;
				}
			}

			cout<<" oneSetOfControlParameters.timePeriod= "<<oneSetOfControlParameters.timePeriod<<endl;

	*/

	this->sendCommandFrame( &allCommandFrames[0],  &allCommandFrames[3], &oneSetOfControlParameters );

}

/* ! \brief slot calls data exchange method.
 *
 *	comsCommandFrame CommandFrame1[3]; //for ganglion 1,2 and 3
 *	comsCommandFrame CommandFrame2[3]; //for ganglion 4,5 and 6
 *	control_Parameters_t ControlParams; //motor control parameters
 */
 void FlexRayUSBInterface::sendCommandFrame( comsCommandFrame  * CommandFrame1, comsCommandFrame  * CommandFrame2,   control_Parameters_t * ControlParams)
 {
	 dataExchangeMutex.lock();

	 //cout<<"command Frame Updated!"<<endl;

	 //copy data into local USB send stream, exchange happens during
	 //here we need to be careful CommandFramd1 is a pointer, so the size of the pointer is only 4
	 //we need to get the size of the full array though
	 memcpy((void *)&dataset[0], CommandFrame1, sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME );
	 memcpy((void *)&dataset[sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME / 2], CommandFrame2, sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME );
	 memcpy((void *)&dataset[72], ControlParams, sizeof(control_Parameters_t));

	 //sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME  //index for control parameter copcy


	 mNewSendDataReady=1;
	 dataExchangeMutex.unlock();

	 /*
	 //cout<<"New FlexRay Command Frame Sent"<<endl;
	// cout<<"Data to be send, set point: "<<CommandFrame1[2].sp[0] <<endl;

	   // cout<<endl<<"copied data size: "<<dec<< sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME/2 <<"  "<< sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME/2<<"  " << sizeof(control_Parameters_t)<<endl;
	 	//cout<<"Printing data in dataset[] array"<<endl;

	 	//cout<<"Index for control parameter start: "<<sizeof(comsCommandFrame)*GANGLIONS_PER_CONTROL_FRAME<<endl;

	 	int k=0;
	 	cout<<endl;
	 	for (int j=0;j<DATASETSIZE;j++)
		{
			if ((j%12)==0)
			{
				cout<<endl<<"offset: "<<dec<<(k++)*12<<" :";
			}
			//		cout<<dec<<cout<<"offset: "<<k++<<" : "<<endl;;
			cout<<hex<<"0x"<<dataset[j]<<" ";


		}
*/
	 //	cout<<endl<<"Sending Config Parameters, ControlParams->timePeriod: "<< ControlParams->timePeriod<<endl;
	 //	cout<<dec<<&ControlParams->tag<<endl;/*!<Tag to indicate data type when passing the union*/
	 //	cout<<&ControlParams->outputPosMax<<endl; /*!< maximum control output in the positive direction in counts, max 4000*/
	 //	cout<<&ControlParams->outputNegMax<<endl; /*!< maximum control output in the negative direction in counts, max -4000*/
	 //	cout<<&ControlParams->spPosMax<<endl;/*<!Positive limit for the set point.*/
	 //	cout<<&ControlParams->spNegMax<<endl;/*<!Negative limit for the set point.*/
	 //	cout<<&ControlParams->timePeriod<<endl;/*!<Time period of each control iteration in microseconds.*/
	 //	cout<<&ControlParams->radPerEncoderCount<<endl; /*!output shaft rotation (in rad) per encoder count */
	 //	cout<<&ControlParams->polyPar[0]<<endl; /*! polynomial fit from displacement (d)  to tendon force (f) f=polyPar[0]+polyPar[1]*d +polyPar[2]*d^2+ +polyPar[3]*d^3+ +polyPar[4]*d^4 */ //mjp-3rd order?
	 //	cout<<&ControlParams->torqueConstant<<endl;


	//	cout<<dec<<endl<<"--data set in send array"<<endl;



 }
/* ! \brief sends and receive FlexRay bus data.
 *
 */
int FlexRayUSBInterface::exchangeData()
{
	DWORD dwNumInputBuffer=0;
	DWORD dwNumBytesRead;

	/*
	for (int j=0;j<DATASETSIZE;j++)
	{
		cout<<hex<<dataset[j]<< " ";
	}
	*/

	//cout<<dec<<" data"<<endl;
	if (mFTDIReady)
	{
		//ready to send
		//cout<<"Sending command frames."<<endl;
		// SEND DATA
				ftStatus = SPI_WriteBuffer(ftHandle, &dataset[0], DATASETSIZE);		// send data
				if (ftStatus != FT_OK)
				{
						printf("Failed to Send a byte through SPI...\n");
						printf("Error Code: %d \n", ftStatus);
						//FT_SetBitMode(ftHandle, 0x0, 0x00); 			// Reset the port to disable MPSSE
						//FT_Close(ftHandle);					// Close the USB port


				}
				else
				{
					//cout<<"Data successfully sent via USB!"<<endl;
					// WAIT FOR DATA TO ARRIVE
					while(dwNumInputBuffer!=DATASETSIZE*2)
					{
							ftStatus = FT_GetQueueStatus(ftHandle, &dwNumInputBuffer); // get the number of bytes in the device receive buffer
									//cout << t << ": " << dwNumInputBuffer << endl;
					}

					// RECEIVE DATA
					if(dwNumInputBuffer > DATASETSIZE*2)					// to prevent segfaults
						dwNumInputBuffer = DATASETSIZE*2;
					FT_Read(ftHandle, &InputBuffer[0], dwNumInputBuffer, &dwNumBytesRead); 	// read bytes into word locations
					dwNumInputBuffer = 0;							// reset the byte counter
				//	cout<<"Data read!"<<endl;

					//now make a copy of relevant signal and emit signal with data

					memcpy( GanglionData, InputBuffer, sizeof(GanglionData));
					//cout<<"Data arrived, copied "<<sizeof(GanglionData)/2<<" words." <<endl;
				//	cout<<"Feedback from Ganglion board 2:"<<endl;
				//	cout<<"Set Point: "<<dec<<GanglionData[2].muscleState[3].jointPos<<endl; //"  bytes transferred: "<<dwNumBytesRead<<" "<<endl;
				//	cout<<"Timer Data:   "<<dec<<GanglionData[2].muscleState[1].jointPos<<endl;
					//cout<<":  "<<hex<<GanglionData[2].extSensor[0]   <<endl;

					emit newGanglionDataReady(GanglionData);


				}




		return 1;
	}
	else
	{
		cout<<"FTDI USB interface not ready."<<endl;
		return -1;
	}
}

void FlexRayUSBInterface::stop()
{
	cout<<"closing FTDI USB to FlexRay Interface"<<endl;
	close();

}

void FlexRayUSBInterface::testConnection(comsCommandFrame * CommandFrame1)
{
	cout<<"TESTING CONNECTION!"<<endl;
}

void FlexRayUSBInterface::close()
{

	cout<<"Closing FTDI connection."<<endl;
	FT_SetBitMode(ftHandle, 0x0, 0x00); 				// Reset MPSSE
	cout<<"Close returns: "<< FT_Close(ftHandle)<<" ."<<endl;						// Close the port
	mFTDIReady=0;
	timerThread->quit();
}

void   FlexRayUSBInterface::cyclicProcessor()
{
	dataExchangeMutex.lock();
	exchangeData(); //send data via USB
	dataExchangeMutex.unlock();

	//emit signal with new data;

	//cout<<"Cyclic Processor:"<<endl;

	return;
}

FlexRayUSBInterface::FlexRayUSBInterface(int cycleTimeInMilliSeconds)
{


	DWORD dwNumDevs; 				// The number of devices
	DWORD dwNumBytesRead = 0;		// Count of actual bytes read - used with FT_Read
	DWORD dwClockDivisor = 2;	    	// Value of clock divisor, SCL Frequency = 60/((1+value)*2) = MHz i.e., value of 2 = 10MHz, or 29 = 1Mhz


	DWORD dwNumInputBuffer;

	mCycleTime=cycleTimeInMilliSeconds;
	mFTDIReady=0;

	/* todo:
	 * possibly initialise
	 *
     * //communication data for USB SPI FLEXRAY stream
     * WORD dataset[DATASETSIZE];
     * WORD InputBuffer[DATASETSIZE];
	 */

	initSafeCommandFrame(); //initialise data to be send to motors before proper data is set by application
	cout<<"Creating FlexRay USB interface with "<<cycleTimeInMilliSeconds<<"ms data update rate "<<endl;

	if(CheckDeviceConnected(&dwNumDevs)==true)
	{


		if(GetDeviceInfo(&dwNumDevs)==true)
		{

			if(OpenPortAndConfigureMPSSE(&ftHandle,USBINSIZE,USBOUTSIZE)==true)
			{


				if(TestMPSSE(&ftHandle)==true)
				{


					if(ConfigureSPI(&ftHandle, dwClockDivisor)==true)
					{
						cout<<"Configuration OK"<<endl;
						mFTDIReady=1;
					}


				}//TestMPSSE
				else
				{
					cout<<"device test failed"<<endl;
				}
			}//OpenPortAndConfigureMPSSE
			else
			{
				cout<<"open port failed"<<endl;
				cout<<" Perhaps the kernel automatically loaded another driver for the   FTDI USB device, from command line try: "<<endl<<"sudo rmmod ftdi_sio"<<endl<<"sudo rmmod usbserial"<<endl;
			}
		}//GetDeviceInfo
		else
		{
			cout<<"device info failed"<<endl;
		}
	} //CheckDeviceConnected
	else
	{
		cout<<"device not connected"<<endl;
	}



	if (mFTDIReady==1)
	{
		//successfully connected start timer to exchange data cyclically
		timerThread =new QThread(this); //create timer thread

		//create timer with current cyclic time
		QTimer* timer = new QTimer(0);
		cout<<"Setting communication timer to "<<mCycleTime<<" ms."<<endl;
		timer->setInterval(mCycleTime);


		std::cout<<"Timers Created"<<endl;

		//let timer run in its own thread this thread
		timer->moveToThread(timerThread);
		//connect time so the cyclic processor runs
		connect(timer, SIGNAL(timeout()), this, SLOT(cyclicProcessor()));
	    connect(timerThread, SIGNAL(started()), timer, SLOT(start()));

	    //start the timer
	    timerThread->start();

	}

}













////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write a number of words to the SPI bus
//////////////////////////////////////////////////////////
FT_STATUS FlexRayUSBInterface::SPI_WriteBuffer(FT_HANDLE ftHandle, WORD* buffer, DWORD numwords)
	{
		DWORD dwNumBytesSent=0;
		DWORD dwNumBytesToSend=0;
		BYTE OutputBuffer[USBOUTSIZE];
		FT_STATUS ftStatus; 			// Result of each D2XX call
		WORD bdata;

// Bytes actually sent = data words*2 + 3 Commands*data words + 3 CSenable*data words + 6 CSdisable*data words => 14* Data words

		for(unsigned int i=0;i<numwords;i++)
			{
				bdata = buffer[i];
				dwNumBytesToSend = SPI_CSEnable(&OutputBuffer[0], &dwNumBytesToSend);
				OutputBuffer[dwNumBytesToSend++] = MSB_FALLING_EDGE_OUT_RISING_EDGE_IN_BYTE;//MSB_RISING_EDGE_OUT_FALLING_EDGE_IN_BYTE;//
				OutputBuffer[dwNumBytesToSend++] = 1;				// data length in bytes (low byte)  } +1!!
				OutputBuffer[dwNumBytesToSend++] = 0;				// data length in bytes (high byte) }
				OutputBuffer[dwNumBytesToSend++] = (BYTE)(bdata >> 8);		// output high byte
				OutputBuffer[dwNumBytesToSend++] = (BYTE)(bdata & 0xff);	// output low byte
				dwNumBytesToSend = SPI_CSDisable(&OutputBuffer[0], &dwNumBytesToSend, true);
			}
		//dwNumBytesToSend = SPI_CSDisable(&OutputBuffer[0], &dwNumBytesToSend, true);
		//printf("%i NumBytesToSend", sizeof(OutputBuffer));
		do
			{
				ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);	//send out MPSSE command to MPSSE engine
				if(ftStatus != FT_OK)
					printf("something wrong with FT_Write call!! \n");
				//else
				//	cout << dwNumBytesSent <<" bytes sent through SPI" << endl;
			}while(ftStatus!=FT_OK);

		dwNumBytesToSend = 0;								//Clear output buffer
		return ftStatus;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this routine is used to enable slave
//////////////////////////////////////////////////////////
DWORD FlexRayUSBInterface::SPI_CSEnable(BYTE* OutputBuffer, DWORD* NumBytesToSend)
	{
		DWORD dwNumBytesToSend;
		dwNumBytesToSend = *NumBytesToSend;

		for(int loop=0;loop<2;loop++) //one 0x80 command can keep 0.2us, do 5 times to stay in this situation for 1us
			{
				OutputBuffer[dwNumBytesToSend++] = '\x80';	// GPIO command for ADBUS
				OutputBuffer[dwNumBytesToSend++] = '\x00';	// set CS, MOSI and SCL low
				OutputBuffer[dwNumBytesToSend++] = '\x0b';	// bit3:CS, bit2:MISO, bit1:MOSI, bit0:SCK
			}
		return dwNumBytesToSend;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this routine is used to disable slave
//////////////////////////////////////////////////////////
DWORD FlexRayUSBInterface::SPI_CSDisable(BYTE* OutputBuffer, DWORD* NumBytesToSend, bool end)
	{
		DWORD dwNumBytesToSend;
		dwNumBytesToSend = *NumBytesToSend;

		// one 0x80 command can keep 0.2us, do 5 times to stay in this situation for 1us (leave CS low)
		//for(int loop=0;loop<2;loop++)
			{
				OutputBuffer[dwNumBytesToSend++] = '\x80';	// GPIO command for ADBUS
				OutputBuffer[dwNumBytesToSend++] = '\x00';	// set CS, MOSI and SCL low
				OutputBuffer[dwNumBytesToSend++] = '\x0b';	// bit3:CS, bit2:MISO, bit1:MOSI, bit0:SCK
			}

		if(end==true)
			{
				// finally pull CS high
				OutputBuffer[dwNumBytesToSend++] = '\x80';	// GPIO command for ADBUS
				OutputBuffer[dwNumBytesToSend++] = '\x08';	// set CS high, MOSI and SCL low
				OutputBuffer[dwNumBytesToSend++] = '\x0b';	// bit3:CS, bit2:MISO, bit1:MOSI, bit0:SCK
			}

		return dwNumBytesToSend;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// find connected devices
//////////////////////////////////////////////////////////
bool FlexRayUSBInterface::CheckDeviceConnected(DWORD* NumDevs)
{
	FT_STATUS ftStatus;

	// -----------------------------------------------------------
	// Does an FTDI device exist?
	// -----------------------------------------------------------
	cout << "Checking for FTDI devices..." << endl;

	ftStatus = FT_CreateDeviceInfoList(NumDevs);				// Get the number of FTDI devices
	if (ftStatus != FT_OK)							// Did the command execute OK?
		{
			cout << "Error in getting the number of devices" << endl;
			return false;								// Exit with error
		}
	if (*NumDevs < 1)								// Exit if we don't see any
		{
			cout << "There are no FTDI devices installed" << endl;
			return false;								// Exit with error
		}
	cout << *NumDevs << " FTDI devices found-the count includes individual ports on a single chip" << endl;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Get device info
//////////////////////////////////////////////////////////
bool FlexRayUSBInterface::GetDeviceInfo(DWORD* NumDevs)
{
	FT_STATUS ftStatus;
	FT_DEVICE_LIST_INFO_NODE *devInfo;

	// ------------------------------------------------------------
	// If yes then print details of devices
	// ------------------------------------------------------------
	devInfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*(*NumDevs));
	ftStatus = FT_GetDeviceInfoList(devInfo,NumDevs);
	if (ftStatus == FT_OK)
		{
			for (unsigned int i = 0; i < *NumDevs; i++)
				{
					cout << " Dev: " << i << endl;
					cout << " Flags=0x" << devInfo[i].Flags << endl;
					cout << " Type=0x" << devInfo[i].Type << endl;
					cout << " ID=0x" << devInfo[i].ID << endl;
					cout << " LocId=0x" << devInfo[i].LocId << endl;
					cout << " SerialNumber=" << devInfo[i].SerialNumber << endl;
					cout << " Description=" << devInfo[i].Description << endl;
					cout << " ftHandle=0x" << devInfo[i].ftHandle << endl;
				}
			return true;
		}
	else
		{
			printf("Could not find info for devices\n");
			return false;								// return with error
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Open device and configure the MPSSE controller
//////////////////////////////////////////////////////////
bool FlexRayUSBInterface::OpenPortAndConfigureMPSSE(FT_HANDLE* ftHandle, DWORD InTransferSize, DWORD OutTransferSize)
{
	FT_STATUS ftStatus;
	DWORD dwNumBytesToRead, dwNumBytesRead;
	BYTE byInputBuffer[DATASETSIZE*2]; 			// Local buffer to hold data read from the FT2232H

	// -----------------------------------------------------------
	// Open the port on first device located
	// -----------------------------------------------------------
	ftStatus = FT_Open(0, ftHandle);
	if (ftStatus != FT_OK)
		{
			printf("Open Failed with error %d\n", ftStatus);
			return false;								// Exit with error
		}
	else
		printf("Port opened....\n");

	// ------------------------------------------------------------
	// Configure MPSSE and test for synchronisation
	// ------------------------------------------------------------

	// Configure port parameters
	printf("\nConfiguring port for MPSSE use...\n");
	ftStatus |= FT_ResetDevice(*ftHandle);				//Reset USB device
	ftStatus |= FT_GetQueueStatus(*ftHandle, &dwNumBytesToRead); 	// Purge USB receive buffer first by reading out all old data from FT2232H receive buffer
									// Get the number of bytes in the FT2232H receive buffer
	if ((ftStatus == FT_OK) && (dwNumBytesToRead > 0))		//Read out the data from FT2232H receive buffer if not empty
		FT_Read(*ftHandle, &byInputBuffer, dwNumBytesToRead, &dwNumBytesRead);
	else
		printf("Buffer empty.\n");

	//ftStatus |= FT_SetUSBParameters(ftHandle, 65536, 65535); 	// Set USB request transfer sizes to 64K
	ftStatus |= FT_SetUSBParameters(*ftHandle, InTransferSize, OutTransferSize); 	// Set USB request transfer sizes...page 73 d2XX programmer guide (only dwInTransferSize has been implemented)
	/*	FT_STATUS FT_SetUSBParameters(FT_HANDLE ftHandle, DWORD dwInTransferSize, DWORD dwOutTransferSize)
		(only dwInTransferSize currently supported..test this...see d2XX programmers guide p 73)
	*/
	ftStatus |= FT_SetChars(*ftHandle, false, 0, false, 0);		// Disable event and error characters
	/*	FT_STATUS FT_SetChars (FT_HANDLE ftHandle, UCHAR uEventCh, UCHAR uEventChEn,UCHAR uErrorCh, UCHAR uErrorChEn)
		(uEventCh = event character, uEventChEn = enable event character insertion, uErrorCh = error character, ...)
	*/
	//ftStatus |= FT_SetTimeouts(ftHandle, 3000, 3000);			// Sets the read and write timeouts in milliseconds
	ftStatus |= FT_SetTimeouts(*ftHandle, 300, 300);			// Sets the read and write timeouts in milliseconds
	/*	FT_STATUS FT_SetTimeouts (FT_HANDLE ftHandle, DWORD dwReadTimeout, DWORD dwWriteTimeout)
		(dwReadTimeout, dwWriteTimeout in ms)
	*/
	ftStatus |= FT_SetLatencyTimer(*ftHandle, 1);				// Set the latency timer to 1mS (default is 16mS)
	/*	FT_STATUS FT_SetLatencyTimer (FT_HANDLE ftHandle, UCHAR ucTimer)
		(ucTimer = require latency value in milliseconds [range of 2-255 page 68 of d2XX programmers guide?])
	*/
	//ftStatus |= FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0x00, 0x00);
																//Turn on flow control to synchronize IN requests
	/*	FT_STATUS FT_SetFlowControl (FT_HANDLE ftHandle, USHORT usFlowControl, UCHAR uXon, UCHAR uXoff)
		(usFlowControl must be either FT_FLOW_NONE, FT_FLOW_RTS_CTS, FT_FLOW_DTR_DSR or FT_FLOW_XON_XOFF)
		(uXon = character to signal Xon [Only used is set to FT_FLOW_XON_XOFF])
		(uXoff = character to signal Xoff [Only used is set to FT_FLOW_XON_XOFF])
	*/
	ftStatus |= FT_SetBitMode(*ftHandle, 0x0, 0x00);				//Reset controller
	/*	FT_STATUS FT_SetBitmode (FT_HANDLE ftHandle, UCHAR ucMask, UCHAR ucMode)
		(ucMask sets which bits are inputs [=0] or outputs [=1])
		(ucMode can one of the following:
			0x0 = Reset
			0x1 = Asynchronous Bit Bang
			0x2 = MPSSE (FT2232, FT2232H, FT4232H and FT232H devices only)
			0x4 = Synchronous Bit Bang (FT232R, FT245R, FT2232, FT2232H, FT4232H and FT232H devices only)
			0x8 = MCU Host Bus Emulation Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
			0x10 = Fast Opto-Isolated Serial Mode (FT2232, FT2232H, FT4232H and FT232H devices only)
			0x20 = CBUS Bit Bang Mode (FT232R and FT232H devices only)
			0x40 = Single Channel Synchronous 245 FIFO Mode (FT2232H and FT232H devices only)
		)

	*/
	ftStatus |= FT_SetBitMode(*ftHandle, 0x0, 0x02);				//Enable MPSSE mode
	if (ftStatus != FT_OK)
		{
			printf("Error in initializing the MPSSE on device. Error: %d\n", ftStatus);
			FT_Close(ftHandle);
			return false;											// Exit with error
		}
	sleep(1); 													// Wait for all the USB stuff to complete and work

	printf("MPSSE ready for commands.\n");
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// test the MPSSE controller
//////////////////////////////////////////////////////////
bool FlexRayUSBInterface::TestMPSSE(FT_HANDLE* ftHandle)
{
	FT_STATUS ftStatus;
	BYTE byOutputBuffer[DATASETSIZE*2];
	BYTE byInputBuffer[DATASETSIZE*2];
	DWORD dwNumBytesToSend = 0;
	DWORD dwNumBytesSent, dwNumBytesRead, dwNumBytesToRead;

	/*
	*	Now the MPSSE is ready for commands, each command consists of an op-code followed by any necessary parameters or
	*	data. Each op-code is sent using FT_Write call
	*/

	/* Synchronisation and Bad communication detection */
	// Enable internal loop-back
	byOutputBuffer[dwNumBytesToSend++] = 0x84;						// Enable loopback
	ftStatus = FT_Write(*ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent); 	// Send off the loopback command
	dwNumBytesToSend = 0; 									// Reset output buffer pointer

	// Check the receive buffer - it should be empty
	ftStatus = FT_GetQueueStatus(*ftHandle, &dwNumBytesToRead); 				// Get the number of bytes in the FT2232H receive buffer
	if (dwNumBytesToRead != 0)
		{
			cout << "Error - MPSSE receive buffer should be empty, Error Code: " << ftStatus << endl;
			FT_SetBitMode(*ftHandle, 0x0, 0x00); 					// Reset the port to disable MPSSE
			FT_Close(*ftHandle);							// Close the USB port
			return false;								// Exit with error
		}
	else
		cout << "Internal loop-back configured and receive buffer is empty" << endl;

	// send bad op-code to check every thing is working correctly
	byOutputBuffer[dwNumBytesToSend++] = 0xAB;						//Add bogus command ‘0xAB’ to the queue
	ftStatus = FT_Write(*ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent); 	// Send off the BAD command
	dwNumBytesToSend = 0;									// Reset output buffer pointer

	do
		{
			ftStatus = FT_GetQueueStatus(*ftHandle, &dwNumBytesToRead);		// Get the number of bytes in the device input buffer
		} while ((dwNumBytesToRead == 0) && (ftStatus == FT_OK));			// wait for bytes to return, an error or Timeout
	bool bCommandEchod = false;
	ftStatus = FT_Read(*ftHandle, &byInputBuffer, dwNumBytesToRead, &dwNumBytesRead); 	// Read the data from input buffer
	for (DWORD dwCount = 0; dwCount < dwNumBytesRead - 1; dwCount++)			//Check if Bad command and echo command are received
		{
			if ((byInputBuffer[dwCount] == 0xFA) && (byInputBuffer[dwCount+1] == 0xAB))
				{
					bCommandEchod = true;
					break;
				}
		}

	if (bCommandEchod == false)
		{
			cout << "Error in synchronizing the MPSSE" << endl;
			FT_SetBitMode(*ftHandle, 0x0, 0x00); 					// Reset the port to disable MPSSE
			FT_Close(*ftHandle);							// Close the USB port
			return false;								// Exit with error
		}
	else
		{
			cout << "MPSSE synchronised." << endl;
			byOutputBuffer[dwNumBytesToSend++] = '\x85';  						// Command to turn off loop back of TDI/TDO connection
			ftStatus = FT_Write(*ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent); 	// Send off the loopback command
			dwNumBytesToSend = 0; 									// Reset output buffer pointer
			return true;
		}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Configure the MPSSE controller into an SPI module
//////////////////////////////////////////////////////////
bool FlexRayUSBInterface::ConfigureSPI(FT_HANDLE* ftHandle, DWORD dwClockDivisor)
{
	FT_STATUS ftStatus;
	BYTE byOutputBuffer[DATASETSIZE*2];
	DWORD dwNumBytesToSend = 0;
	DWORD dwNumBytesSent;

	// ------------------------------------------------------------
	// Configure MPSSE for SPI communications
	// ------------------------------------------------------------
	// The SK clock frequency can be worked out as follows with divide by 5 set as off:: SK frequency = 60MHz /((1 + [(1 + (0xValueH*256) OR 0xValueL])*2)

	byOutputBuffer[dwNumBytesToSend++] = '\x8A'; 						// Ensure disable clock divide by 5 for 60Mhz master clock
	byOutputBuffer[dwNumBytesToSend++] = '\x97';						// Ensure turn off adaptive clocking
	byOutputBuffer[dwNumBytesToSend++] = '\x8D'; 						// disable 3 phase data clock
	ftStatus = FT_Write(*ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent); 	// Send out the commands
	if(ftStatus!=FT_OK)
		{
			cout << "Error configuring SPI" << endl;
			FT_SetBitMode(*ftHandle, 0x0, 0x00); 						// Reset the port to disable MPSSE
			FT_Close(*ftHandle);										// Close the USB port
			return false;
		}

	dwNumBytesToSend = 0;												// Clear output buffer
	byOutputBuffer[dwNumBytesToSend++] = '\x80'; 						// Set directions of lower 8 pins, set value on bits set as output
	byOutputBuffer[dwNumBytesToSend++] = '\x08'; 						// Set SCK, DO, DI low and CS high
	byOutputBuffer[dwNumBytesToSend++] = '\x0b'; 						// Set SK,DO,GPIOL0 pins as output =1, other pins as input=0
	byOutputBuffer[dwNumBytesToSend++] = '\x86'; 						// Command to set clock divisor
	byOutputBuffer[dwNumBytesToSend++] = (BYTE)(dwClockDivisor & '\xFF'); 			// Set 0xValueL of clock divisor
	byOutputBuffer[dwNumBytesToSend++] = (BYTE)(dwClockDivisor >> 8); 			// Set 0xValueH of clock divisor
	byOutputBuffer[dwNumBytesToSend++] = '\x85';  						// Command to turn off loop back of TDI/TDO connection
	ftStatus = FT_Write(*ftHandle, byOutputBuffer, dwNumBytesToSend, &dwNumBytesSent);	// Send out the commands
	if(ftStatus!=FT_OK)
		{
			cout << "Error configuring SPI" << endl;
			FT_SetBitMode(*ftHandle, 0x0, 0x00); 					// Reset the port to disable MPSSE
			FT_Close(*ftHandle);							// Close the USB port
			return false;
		}
	dwNumBytesToSend = 0;									// Clear output buffer
	usleep(100);										// Delay for 100us
	cout << "SPI initialisation successful" << endl;
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Send a single byte through the SPI bus
//////////////////////////////////////////////////////////
BOOL FlexRayUSBInterface::SPI_WriteByte(FT_HANDLE ftHandle, WORD bdata)
	{
		DWORD dwNumBytesSent;
		DWORD dwNumBytesToSend=0;
		BYTE OutputBuffer[512];
		FT_STATUS ftStatus; 			// Result of each D2XX call

		dwNumBytesToSend = SPI_CSEnable(&OutputBuffer[0], &dwNumBytesToSend);
		OutputBuffer[dwNumBytesToSend++] = MSB_FALLING_EDGE_CLOCK_BYTE_OUT;	// Byte out falling edge msb first
		OutputBuffer[dwNumBytesToSend++] = 1;					// data length in bytes (low byte)  } +1!!
		OutputBuffer[dwNumBytesToSend++] = 0;					// data length in bytes (high byte) }
		OutputBuffer[dwNumBytesToSend++] = bdata >> 8;		//output high byte
		OutputBuffer[dwNumBytesToSend++] = bdata & 0xff;	//output low byte
		dwNumBytesToSend = SPI_CSDisable(&OutputBuffer[0], &dwNumBytesToSend, true);
		ftStatus = FT_Write(ftHandle, OutputBuffer, dwNumBytesToSend, &dwNumBytesSent);
															//send out MPSSE command to MPSSE engine
		printf("%i bytes sent through SPI\n", dwNumBytesSent);
		dwNumBytesToSend = 0;								//Clear output buffer
		return ftStatus;
	}















