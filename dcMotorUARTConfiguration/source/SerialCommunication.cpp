/*
 * SerialCommunication.cpp
 *
 *  Created on: 14 Aug 2014
 *      Author: alex
 */

#include "SerialCommunication.h"
#include <iostream>
#include <string>
 #include <QCoreApplication>
#include <QTime>
using namespace std ;

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}


SerialCommunication::SerialCommunication(std::string const& uartName)
{


		CommsReady=0;
	    serial_port.Open( uartName.c_str() ) ;
	    if ( ! serial_port.good() )
	    {
	        cout<<"error uart name,  "<< uartName<< " cannot be accessed!"<<endl;
	        return ;
	    }
	    //
	    // Set the baud rate of the serial port.
	    //
	    serial_port.SetBaudRate( LibSerial::SerialStreamBuf::BAUD_57600 ) ;
	    if ( ! serial_port.good() )
	    {
	        std::cout<<"error, baud rate"<<endl;
	        return ;
	    }
	    //
	    // Set the number of data bits.
	    //
	    serial_port.SetCharSize( LibSerial::SerialStreamBuf::CHAR_SIZE_8 ) ;
	    if ( ! serial_port.good() )
	    {
	    	std::cout<<"error, data bits"<<endl;
	        return ;
	    }
	    //
	    // Disable parity.
	    //
	    serial_port.SetParity( LibSerial::SerialStreamBuf::PARITY_NONE ) ;
	    if ( ! serial_port.good() )
	    {
	    	std::cout<<"error, parity"<<endl;
	        return ;
	    }
	    //
	    // Set the number of stop bits.
	    //
	    serial_port.SetNumOfStopBits( 1 ) ;
	    if ( ! serial_port.good() )
	    {
	    	std::cout<<"error, stop bits"<<endl;
	        return;
	    }
	    //
	    // Turn on hardware flow control.
	    //
	    serial_port.SetFlowControl( LibSerial::SerialStreamBuf::FLOW_CONTROL_NONE ) ;
	    if ( ! serial_port.good() )
	    {
	    	std::cout<<"error, flow control"<<endl;
	        return ;
	    }
	    CommsReady=1;
	    cout<<"SERIAL PORT READY FOR COMMUNCIATION"<<endl;

}

	 bool SerialCommunication::ready()
	 {
	 if (CommsReady==1)
		 return true;
	 else
			return false;
	 }

	 int SerialCommunication::PrintCurrentConfiguration()
	 {
		 //
				 	 cout<<endl<<"Waiting for motor start-up message."<<endl<<"press reset!"<<endl<<endl;
				 	while( serial_port.rdbuf()->in_avail() < 1 );
				 	//wait a bit to receive full string

				 	delay(200);
				 	int firstTime=1;
				    while( serial_port.rdbuf()->in_avail() > 0  )
				    {
				    	if (firstTime==1)
				    	{
				    		firstTime=0;
				    		cout<<"Printing motor driver start-up string:"<<endl<<endl;
				    	}
				        char next_byte;
				        serial_port.get(next_byte);

				        if ((next_byte=='\n')||(next_byte=='\r'))
				        		cout<<endl;
				        else

				        cout << next_byte;
				    }
	 }

	 int SerialCommunication::ConfigureDriverBoard(unsigned short * configurationData, int dataLength)
	 {
		 int i=0;
		 string motorConfigString;
		 int driverBoardDetected=0;

		 cout<<"Config Data Stream ready to flash onto driver board\n "<<endl;
		// for (i=0;i < dataLength; i++)
		 {
			 //cout<< *configurationData<<endl;
		//	 configurationData++;
		 }

		 // Keep reading data from serial port and print it to the screen.
		    //
		 	 cout<<endl<<"Waiting for motor start-up message."<<endl<<"press reset!"<<endl<<endl;
		 	while( serial_port.rdbuf()->in_avail() < 1 );
		 	//wait a bit to receive full string

		 	delay(200);
		 	int firstTime=1;
		    while( serial_port.rdbuf()->in_avail() > 0  )
		    {
		    	if (firstTime==1)
		    	{
		    		firstTime=0;
		    		cout<<"Printing motor driver start-up string:"<<endl<<endl;
		    	}
		        char next_byte;
		        serial_port.get(next_byte);

		        if ((next_byte=='\n')||(next_byte=='\r'))
		        		cout<<endl;
		        else

		        cout << next_byte;
		        motorConfigString.insert( motorConfigString.end(),1, next_byte);

		        if (motorConfigString.find(CONFIG_START_STRING)!= string::npos)
		        {
		        	driverBoardDetected=1;
		        	cout<<endl<<"Board detected, starting Configuration."<<endl;
		        }

		    }
		 	 //cout<<"Start-up received."<<endl;

		 	 //cout<<motorConfigString;

		    if (driverBoardDetected==1)
		    {
		    	// go through all config words
		    	int transmissionError=0;
		    	unsigned short configWord;
		    	char configBytes[2];
				for (i=0;i < dataLength; i++)
				 {


					 configBytes[0]=((*configurationData) & 0x00FF);
					 configBytes[1]=((*configurationData)>>8) & 0x00FF;
					// printf("  byte[0]: 0x%x, byte[1]: 0x%x \n", (unsigned) configBytes[0],(unsigned) configBytes[1]);
					// cout<<",  byte[0]: "<<hex<<*configBytes<< " byte[1]: "<<hex<<*configBytes<<endl;

					 //send them byte after byte
					 for (int k=0;k<2;k++)
					 {
						 serial_port.write ( &configBytes[k],1);
						// printf("  byte[%d]: 0x%x \n",k,configBytes[k]);
						 //cout<<endl<<"sent character, reply?"<<endl;
						 //wait for reply
						 while( serial_port.rdbuf()->in_avail() < 1 );
						// cout<<"reply received"<<endl;
					     char next_byte;
					     serial_port.get(next_byte);
					     if (next_byte==configBytes[k])
					     {
					    //	cout<<endl<<", transmission ok, byte "<<k<<", word "<<dec<<i+1<<endl;
					    	printf("\n word: %d , byte %d , sent 0x%x , reply 0x%x,",i+1, k, (unsigned char) configBytes[k], (unsigned char)next_byte);
					     }
					     else
					     {
					    	 cout<<"TRANSMISSION ERROR";
					    	 printf("\n byte %d, word %d: Compare: 0x%x : 0x%x \n",k,i+1, next_byte,configBytes[k]);
					    	 transmissionError++;
					     }


					 }

					 configurationData++;
				 }

				cout<<endl<<"Transmission errors: "<<transmissionError<<"."<<endl;
				if (transmissionError==0)
				{
					cout<<"CONFIGURATION OK! Waiting for EEPROM FLASH OK Message from motor driver: "<<endl;
					delay(200);

				    while( serial_port.rdbuf()->in_avail() > 0  )
				    {
				    	if (firstTime==1)
				    	{
				    		firstTime=0;
				    		cout<<"Printing motor driver start-up string:"<<endl<<endl;
				    	}
				        char next_byte;
				        serial_port.get(next_byte);

				        if ((next_byte=='\n')||(next_byte=='\r'))
				        		cout<<endl;
				        else

				        cout << next_byte;
				    }



				}


		    		//send them byte after byte

		    		//wait for acknowledge after each byte

		    }
		    else
		    {
		    	cout<<"no board detected";
		    }

	 }
