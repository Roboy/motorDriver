/*
 * canConfigLoader.c
 *
 *  Created on: 24 Oct 2012
 *      Author: alex
 */


#include "canConfigLoader.h"
#include <QMutex>
#include <QMutex>
 #include <QThread>
#include <stdio.h>
#include <iostream>
#include "KvaserCanInterface.h"
#include "configDataHandling.h"
using namespace std;
//#include "moc_CanConfigLoader.h"

CONFIG_STATE canConfigState;

canConfigLoader::canConfigLoader()
{
	canConfigState=WAIT_FOR_WAKEUP;

}


 void canConfigLoader::run()
 {

	 cout << "CAN Configuration Loader for the MyoMotorDriver " <<endl;// thread()->currentThreadId();
	 KvaserCanInterface myCan;
	 CHANNEL_HANDLE busHandle0;
	 busHandle0=myCan.openCanChannel(0);
	 string myString;
	 CAN_MESSAGE myCanMessage, canSentMessage;
	 STATUS_CODE myCanStatus;

	while (loadConfigDataFromFile()<0); // only return once a valid configuration has been read  ///
	  //serializeData(0);
	  //int canMessageRequired=getNumberOfRequiredCanMessage();
	  //cout<<"There are " << canMessageRequired <<" configuration messages required!"<<end
	 int numberOfRequiredCANMessages=getNumberOfRequiredCanMessage();
	 cout<<"There are "<<numberOfRequiredCANMessages<<" CAN messages necessary to transmit configuration!"<<endl;
	 int CANMessageCount=0;
	 if (busHandle0>-1)
	 {
		 cout<<"CAN bus available:"<<endl;

		 //configure bus
		  myCanStatus=myCan.configureCanChannel(busHandle0,CAN_BAUDRATE__1M,0); //1Mbit/s not silent
		  myCan.getErrorText(myCanStatus,myString);
		  myCan.connectCanChannel(busHandle0);
		  cout<<"CAN configured, 1Mbit/s: status is "<<myString<<endl;
		  cout<<"Reading CAN, waiting for START_MESSAGE:"<<endl;
		 //
		 int configurationComplete=0;
		 while (configurationComplete!=1)
		 {
			  myCanStatus=myCan.readCanMessage(busHandle0, myCanMessage);
			  if (myCanStatus>-1)
			  {
				 // myCan.printCanMessage(myCanMessage); //print message


			  }
			  else if (canERR_NOMSG)
			  {
				  //there was no message but also no error, so we just continue
			  }
			  else
			  {
				  cout<<"Error Reading From CAN bus, termination of configuration"<<endl;
				  configurationComplete=1;
			  }


			  switch (canConfigState)
			  {
			  	  case WAIT_FOR_WAKEUP:
			  	  {
					  if (myCanMessage.messageID ==  WAKE_UP_MSG_BASE_ID+getOldNodeID())
						  {
						  myCan.printCanMessage(myCanMessage); //print message
						  canConfigState=START_CONFIG;
						  cout<<"STARTING CONFIGURATION:"<<endl;

						  }
			  	  }
			  	  break;
			  	  case START_CONFIG:
			  	  {
			  		//assembel CAN message
			  		canSentMessage.dlc=8;
			  		canSentMessage.messageID=CONFIGURATION_MSG_BASE_ID + getOldNodeID();
			  		canSentMessage.extended=0;
			  		provideConfigMessageData( (short unsigned *)(canSentMessage.data16),CANMessageCount);
			  		myCan.printCanMessage(canSentMessage);
			  		myCan.sendCanMessage(busHandle0,canSentMessage);
			  		canConfigState=CONFIG_MESSAGE_SENT;

			  	  }
			  	  break;


			  	  case CONFIG_MESSAGE_SENT:
			  	  {
			  		if (myCanMessage.messageID ==  CONFIGURATION_REPLY_ID)
			  		{
			  			if ( (myCanMessage.data16[0]==canSentMessage.data16[0])&&
			  					(myCanMessage.data16[1]==canSentMessage.data16[1])&&
			  					(myCanMessage.data16[2]==canSentMessage.data16[2])&&
			  					(myCanMessage.data16[3]==canSentMessage.data16[3]))
			  			{
			  				//we had a correct reply
			  				 CANMessageCount++;

			  				 if (CANMessageCount < numberOfRequiredCANMessages)
			  				 {
			  					 canConfigState=CONFIG_REPLY_RECEIVED;
			  				 }
			  				 else
			  				 {
			  					 canConfigState=END_CONFIG;
			  				 }
			  			}
			  		}

			  	  }
			  	  break;


			  	  case CONFIG_REPLY_RECEIVED:
			  	  {
			  		canConfigState=START_CONFIG;
			  	  }
			  	  break;

			  	  case END_CONFIG:
			  	  {

			  		  cout<<"CONFIGURATION COMPLETE!"<<endl;
			  		  configurationComplete=1;
			  	  }
			  	  break;

			  }


		 }


	     myCan.closeCanChannel(busHandle0);
	 }
	 else
	 {
		 cout<<"ERROR opening CAN interface, bus handle is: "<< busHandle0<<endl;

	 }



 }


//QMutex canDataMutex;

//canDataMutex.lock();
//canDataMutex.unlock();

