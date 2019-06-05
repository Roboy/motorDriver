/*
 * configDataHandling.cpp
 *
 *  Created on: 15 Nov 2012
 *      Author: alex
 */
#include "configDataHandling.h"
#include <stdio.h>
#include <iostream>
#include <QFile>
#include <QDir>
#include<QTextStream>

using namespace std;



/*!brief returns the number of configuration messages required
 *
 *//*

unsigned getNumberOfRequiredCanMessage()
{
	//each config message contains 3 16-bit words

	int messageCount=((sizeof(eePromData)>>1)+(3-1))/3;
	return messageCount;
}

/*
unsigned provideConfigMessageData( short unsigned  *canData, unsigned int messageIndex)
{
	int currentIndex=messageIndex*3; //because we have three words in a CAN message
	if (currentIndex<(sizeof(eePromData)>>1))
	{
				*canData=currentIndex;
				canData++;
				for (int i=0;i<3;i++)
				{
					*canData=eePromData.dataStream[currentIndex+i];
					 canData++;
				}
				return 1;
	}
	else
	{
		cout<<"ERROR IN CAN CONFIG MESSAGE"<<endl;
		return -1;
	}

}
*/

/*
 *

unsigned short serializeData(unsigned dataIndex)
{
	int dataSize,i;
	void *dataPacket;
	dataSize=sizeof(eePromData);

	dataPacket=& (eePromData.ControlMode);
	cout<<"firstAddress:" <<dataPacket<<endl;

	cout<<"EEPROM data size: "<<dataSize<<" bytes. \n Data: \n"<<endl;
	for (i=0; i<(dataSize>>1);i++)
	{
		printf("0x%04x  \n",eePromData.dataStream[i]);
	}

	return eePromData.dataStream[dataIndex];
}
*/
void configLoader::printCurrentConfiguration()
{
	cout<<"eePromData.s.ControlMode=  " <<eePromData.s.ControlMode<<endl;
	cout<< "cycleTimeIn100usIncrements= "<< eePromData.s.cycleTimeIn100usIncrements<<endl;
	cout<<"eePromData.PGain= " <<eePromData.s.PGain<<endl;
	cout<<"eePromData.IGain= " <<eePromData.s.IGain<<endl;
	cout<<"eePromData.DGain= " <<eePromData.s.DGain<<endl;
	cout<<"eePromData.positiveSaturation= " <<eePromData.s.positiveSaturation<<endl;
	cout<<"eePromData.negativeSaturation= " <<eePromData.s.negativeSaturation<<endl;
	cout<<"eePromData.integratorSaturation= " <<eePromData.s.integratorSaturation<<endl;
	cout<<"eePromData.currentConversionFactor= " <<eePromData.s.currentConversionFactor<<endl;
	cout<<"eePromData.EncoderCountsPerRevolution= " <<eePromData.s.EncoderCountsPerRevolution<<endl;
	cout.setf(ios::hex, ios::basefield);
	cout<<"eePromData.referenceValueMessageId= 0x" <<eePromData.s.referenceValueMessageId<<endl;
	cout<<"eePromData.actualValueMessageId= 0x " <<eePromData.s.actualValueMessageId<<endl;
	cout<<"eePromData.pidGainsMessageId= 0x" <<eePromData.s.pidGainsMessageId<<endl<<endl;

    cout.unsetf(ios::hex);
	cout<<"eePromData.nodeID= " <<eePromData.s.nodeID<<endl<<endl<<endl;
}
int configLoader::loadConfigDataFromFile()
{
	 int configDataIndex=0;
	 QDir configDirectory("configFiles");
	 QString configPath = configDirectory.absolutePath();

     QStringList filters;
     filters << "*.ini";
     configDirectory.setNameFilters(filters);

     QStringList allFiles=configDirectory.entryList(filters);



	 cout<<"Configuration files are read from:"<<configPath.toStdString()<<endl;
	 cout<<"Directory contains "<<allFiles.size()<<" file(s)"<<endl;
	 for (int i=0;i<allFiles.size();i++)
	 {
		 cout<<i<<":  "<<allFiles.at(i).toStdString()<<endl;
	 }

	 int configIndex;
	 cout<<endl<<"Select Configuration file index an press return, enter -1 if no selection but reading of configuration  desired."<<endl;
	 cin>>configIndex;

	 if ((configIndex>=0)&&(configIndex<allFiles.size()))
	 {
		 configPath.append("/");
		 configPath.append(allFiles.at(configIndex));
		 cout<<"Reading configuration files:"<<configPath.toStdString()<<endl;
		 cout<<"Here is the EEPROM configuration that will be loaded:"<<endl;

		 //clear eeprom data first

		 for (int k=0;k<sizeof(eePromData.dataStream)/2;k++) //divide by 2 because dataStream is short array
		 {
			 eePromData.dataStream[k]=0;
			 //cout<<"deleting EEPROM word: "<<k<<endl;
		 }
	 }
	 else if (configIndex==-1)
	 {
		 cout<<"Configuration Reading selected."<<endl<<endl;
		 return configIndex;
	 }
	 else
	 {
		 cout<<"INVALID SELECTION, try again!"<<endl<<endl;
		 return -2;
	 }

    QFile inputFile(configPath);

    //realistically, we only drive 2 motors and 1 joint in a 1ms loop on CAN
   	  //so, we only implement those now

   	 QSettings settings( configPath, QSettings::IniFormat );

   	eePromData.s.ControlMode=settings.value("node/ControlMode",  7 ).toInt();
    eePromData.s.cycleTimeIn100usIncrements=settings.value("node/cycleTimeIn100usIncrements",  -99 ).toUInt();


    eePromData.s.PGain=settings.value("node/PGain",-88).toDouble();
    eePromData.s.IGain=settings.value("node/IGain",-88).toDouble();
    eePromData.s.DGain=settings.value("node/DGain",-88).toDouble();
    eePromData.s.positiveSaturation=settings.value("node/positiveSaturation",-88).toDouble();
    eePromData.s.negativeSaturation=settings.value("node/negativeSaturation",-88).toDouble();
    eePromData.s.integratorSaturation=settings.value("node/integratorSaturation",-88).toDouble();
    eePromData.s.currentConversionFactor=settings.value("node/currentConversionFactor",-88).toDouble();
    eePromData.s.EncoderCountsPerRevolution=settings.value("node/EncoderCountsPerRevolution",  -99 ).toUInt();

    bool ok;
    QString CanAddressString;


    CanAddressString=settings.value("node/referenceValueMessageId",  -99 ).toString();
   // cout<<CanAddressString.toStdString()<<endl;
  	eePromData.s.referenceValueMessageId=CanAddressString.toInt(&ok,16);

  	CanAddressString=settings.value("node/actualValueMessageId",  -99 ).toString();
    //cout<<CanAddressString.toStdString()<<endl;
    eePromData.s.actualValueMessageId=CanAddressString.toInt(&ok,16);

  	CanAddressString=settings.value("node/pidGainsMessageId",  -99 ).toString();
    //cout<<CanAddressString.toStdString()<<endl;
    eePromData.s.pidGainsMessageId =CanAddressString.toInt(&ok,16);


    eePromData.s.nodeID=settings.value("node/nodeID",  -99 ).toUInt();


   	printCurrentConfiguration();

    cout<<endl<<endl;
    int oldNodeID;
    char yesNo;
    cout<<"Config data ok? (press y/n and return):" <<endl;
    cin>>yesNo;
    if ((yesNo=='y') or (yesNo=='Y'))
    {

    	return 1;


    }
    else
    {
    	cout<<endl<<"Configuration rejected, try again!"<<endl;
       	return -1;
    }

    /*
	eePromData.ControlMode=1;
	eePromData.PGain=1.127;
	eePromData.IGain=2.2;
	eePromData.DGain=-3.3;
	eePromData.cycleTimeIn100usIncrements=1000;
	eePromData.EncoderCountsPerRevolution=2222;
	eePromData.referenceValueMessageId=0x120;
	eePromData.actualValueMessageId=0x121;
	eePromData.pidGainsMessageId=0x122;
	*/

}

int configLoader::getStreamLengthIn16bitSize()
{
	return sizeof(eePromData.dataStream)/2;
}

unsigned short *configLoader::getDataStreamPointer()
{
	return &eePromData.dataStream[0];
}


