/*! \file main.c
*
* DEPENDECIES: Kvaser CAN library: lcanlib lpthread
* 
*
* CMAKE: change to build folder and run the following CMAKE command to build a Eclipse project
*       ~\$ cd /build  
*       ~\$ cmake -G"Eclipse CDT4 - Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../source 
*
*            Import the created project file into Eclipse
*
*            Import project using Menu File->Import
*            Select General->Existing projects into workspace:
*            Browse where your build tree is and select the root build tree directory. Keep "Copy projects into workspace" unchecked.
*            You get a fully functional eclipse project
*
*/

#include <canlib.h>
#include <stdio.h>
#include <iostream>
#include <signal.h>

#include "KvaserCanInterface.h"
#include "configDataHandling.h"
#include "canConfigLoader.h"
 #include <QCoreApplication>
using namespace std;

KvaserCanInterface myCan;

int main (int argc, char *argv[])

{
  CAN_MESSAGE myCanMessage;
  STATUS_CODE myCanStatus;
  canHandle handle;
  canStatus status;
  int ret = -1;
  long id;
  unsigned char msg[8];
  unsigned int dlc;
  unsigned int flag;
  unsigned long time;
  int channelCount;
  int channel = 0;
  int bitrate = BAUD_1M;
  int j;

  unsigned int canData[4];
  QCoreApplication app();
  canConfigLoader myoMotorConfigLoader;
  ///loadConfigDataFromFile();
  //serializeData(0);
  //int canMessageRequired=getNumberOfRequiredCanMessage();
  //cout<<"There are " << canMessageRequired <<" configuration messages required!"<<endl;

  myCanMessage.messageID=0x09;
  myCanMessage.dlc=8;


 // for (int k=0;k<canMessageRequired;k++)
 // {
//	  provideConfigMessageData( (short unsigned *)(myCanMessage.data16),k);
//	  myCan.printCanMessage(myCanMessage);
	 // cout<<"CAN config data:"<< canData[0]<<"  "<< canData[1]<<"  "<< canData[2]<<"  "<< canData[3]<<"  "<<endl;
  //}


  myoMotorConfigLoader.start();
  myoMotorConfigLoader.wait();

//  myCanMessage.messageID=0x110;
 // myCanMessage.data16[0]=0x8899;
  //myCanMessage.data16[1]=0xAABB;
  //myCanMessage.data16[2]=0xCCDD;
  //myCanMessage.data16[3]=0XEEFF;
  //myCanMessage.extended=0;
  //myCanMessage.dlc=8;

  ///myCan.printCanMessage(myCanMessage);

  //myCan.getAvailableCanChannels(channelCount);
  //cout<<"class: channel count: "<<channelCount <<endl;

  string myString;
 // myCan.getErrorText(-2,myString);
  //cout<<"erro text:    "<<myString<<"  END OF ERROR TEXT"<<endl<<endl;



  //CHANNEL_HANDLE busHandle0;
  //busHandle0=myCan.openCanChannel(0);

  //cout<<"Channle handle is:" <<busHandle0<<endl;
/*
  if (busHandle0 > -1)
  {
	  cout<<"configure can"<<endl;
	  myCanStatus=myCan.configureCanChannel(busHandle0,CAN_BAUDRATE__1M,0); //1Mbit/s not silent
	  myCan.getErrorText(myCanStatus,myString);
	  cout<<"Status is "<<myString<<endl;

	  myCan.connectCanChannel(busHandle0);

	  cout<<"send message"<<endl;
	  myCanStatus=myCan.sendCanMessage(busHandle0,myCanMessage);
	  myCan.getErrorText(myCanStatus,myString);
	  cout<<"Status is "<<myString<<endl;

	  cout<<"reading"<<endl;
	  int stopReading=0;


	  myCan.setUprxCallback(busHandle0);


	  do
	  {
		  myCanStatus=myCan.readCanMessage(busHandle0, myCanMessage);
		  if (myCanStatus>-1)
		  {
			  myCan.printCanMessage(myCanMessage); //print message
		  }
		  else if (canERR_NOMSG)
		  {
			  //there was no message but also no error, so we just continue
		  }
		  else
		  {
			  stopReading=1;
		  }
	  }
		  while(stopReading==0);

  }
  else
  {
	  cout<<"failed to open channel, handle is: "<<busHandle0<<endl;
  }

  */
  int dummy;
  cout<<" write 0 and press return to end application!"<<endl;
  cin>>dummy;
  /*
  //find out how many can channels are available
  status= canGetNumberOfChannels(&channelCount);

  cout<<endl<<endl<<"Number of available CAN channels:  "<< channelCount<< endl;

  if (channelCount>0)
  {
	  cout<<"Opening channel 0"<<endl;

	  handle =  canOpenChannel(0 , canWANT_EXCLUSIVE);
	  if (handle>-1)
	  {
		  	cout<<"Opening channel 0 returns handle: "<< handle<< endl;

		  //set up bus parameters

		  	char textBuffer[100];
		    long freq= BAUD_1M;
		    canStatus can0Status;
		    //values below from Kvaser example
		    unsigned int tseg1=4;
		    unsigned int tseg2=3;
		    unsigned int sjw=1;
		    unsigned int noSamp=1;
		    unsigned int syncmod=0;
		    can0Status = canSetBusParams(handle, freq, tseg1,tseg2, sjw, noSamp,  syncmod);
		    canGetErrorText(can0Status,textBuffer,100);
		    cout<<endl<<"opened channel 0, status is: "<<textBuffer<<endl;
		    //we are ready to send and receive
		    if (can0Status>-1)
		    {

		    }


		  //close channel
		  cout<<"Closing channel 0!"<<endl;
		  canClose(handle);

	  }
	  else
	  {
		  cout<<"Opening channel 0 returns error code: "<< handle<< endl;
	  }


  }
  else
  {
	  cout<<endl<<"NO CAN HARDWARE FOUND, CLOSING!"<<endl<<endl;
  }
  */


 // cin>>dummy;

  cout<<endl<<"Quitting"<<endl;
}
