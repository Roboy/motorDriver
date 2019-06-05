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

EEPROM_DATA eePromData;
int oldNodeID;

/*!brief returns the old Node ID
 *
 */
int getOldNodeID()
{
	return oldNodeID;
}

/*!brief returns the number of configuration messages required
 *
 */
unsigned getNumberOfRequiredCanMessage()
{
	//each config message contains 3 16-bit words

	int messageCount=((sizeof(eePromData)>>1)+(3-1))/3;
	return messageCount;
}

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

unsigned short serializeData(unsigned dataIndex)
{
	int dataSize,i;
/*	void *dataPacket;
	dataSize=sizeof(eePromData);

	dataPacket=& (eePromData.ControlMode);
	cout<<"firstAddress:" <<dataPacket<<endl;

	cout<<"EEPROM data size: "<<dataSize<<" bytes. \n Data: \n"<<endl;
	for (i=0; i<(dataSize>>1);i++)
	{
		printf("0x%04x  \n",eePromData.dataStream[i]);
	}
*/
	return eePromData.dataStream[dataIndex];
}

int loadConfigDataFromFile()
{
	int configDataIndex=0;
	 QDir configDirectory("configFiles");
	 QString configPath = configDirectory.absolutePath();

     QStringList filters;
     filters << "*.txt";
     configDirectory.setNameFilters(filters);

     QStringList allFiles=configDirectory.entryList(filters);



	 cout<<"Config files are read from:"<<configPath.toStdString()<<endl;
	 cout<<"Directory contains "<<allFiles.size()<<" file(s)"<<endl;
	 for (int i=0;i<allFiles.size();i++)
	 {
		 cout<<i<<":  "<<allFiles.at(i).toStdString()<<endl;
	 }

	 int configIndex;
	 cout<<endl<<"Select Configuration file index an press return"<<endl;
	 cin>>configIndex;

	 if ((configIndex>=0)&&(configIndex<allFiles.size()))
	 {
		 configPath.append("/");
		 configPath.append(allFiles.at(configIndex));
		 cout<<"Reading configuration files:"<<configPath.toStdString()<<endl;
		 cout<<"Here is the EEPROM configuration that will be loaded:"<<endl;
	 }
	 else
	 {
		 cout<<"INVALID SELECTION, try again!"<<endl<<endl;
		 return -1;
	 }

    QFile inputFile(configPath);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while ( !in.atEnd() )
       {
          QString line = in.readLine();
          line.remove(" "); //get rid of the empty space

          if ((line.startsWith("#"))|| (line.isEmpty()))
          {
        	  //all lines like this are comments and are not read
        	 // cout<<"comment: ";
          }
          else
          {
        	  unsigned dummy;
        	  float floatDummy;
        	  bool ok;
        	  line.remove("x");line.remove("X"); //get rid of the x in 0x expressions
        	  //we should have line with a relevant value;
        	  //now we add the values in order to the internal storage structure.
        	  switch (configDataIndex)
        	  {
        	  case 0:
        		  //cout<<"line with control mode:"<<line.toStdString()<<" ";
        		  eePromData.ControlMode=line.toInt(); cout<<"eePromData.ControlMode: 0x"<<hex<<eePromData.ControlMode<<endl;//"  index:"<<configDataIndex;
        		  break;
        	  case 1:
        		  eePromData.cycleTimeIn100usIncrements=line.toUInt(); cout<<"eePromData.cycleTimeIn100usIncrements: "<<eePromData.cycleTimeIn100usIncrements<<endl;//<<"  index:"<<configDataIndex;
        		  break;
        	  case 2:
        		  eePromData.PGain=line.toFloat(); cout<<"eePromData.PGain: "<<eePromData.PGain<<endl;//<<"  index:"<<configDataIndex;
        		  break;
        	  case 3:
        		  eePromData.IGain=line.toFloat(); cout<<"eePromData.IGain: "<<eePromData.IGain<<endl;//<<"  index:"<<configDataIndex;
        		  break;
        	  case 4:
        		  eePromData.DGain=line.toFloat(); cout<<"eePromData.DGain: "<<eePromData.DGain<<endl;//<<"  index:"<<configDataIndex;
        		  break;


        	  case 5:
        	         		  eePromData.positiveSaturation=line.toFloat(); cout<<"eePromData.positiveSaturation: "<<eePromData.positiveSaturation<<endl;//<<"  index:"<<configDataIndex;
        	         		  break;

        	  case 6:
        	         		  eePromData.negativeSaturation=line.toFloat(); cout<<"eePromData.negativeSaturation: "<<eePromData.negativeSaturation<<endl;//<<"  index:"<<configDataIndex;
        	         		  break;


        	  case 7:
        	         		  eePromData.integratorSaturation=line.toFloat(); cout<<"eePromData.integratorSaturation: "<<eePromData.integratorSaturation<<endl;//<<"  index:"<<configDataIndex;
        	         		  break;

        	  case 8:
        	         		  eePromData.currentConversionFactor=line.toFloat(); cout<<"eePromData.currentConversionFactor: "<<eePromData.currentConversionFactor<<endl;//<<"  index:"<<configDataIndex;
        	         		  break;


        	  case 9:
        	        eePromData.EncoderCountsPerRevolution=line.toInt(); cout<<"eePromData.EncoderCountsPerRevolution: "<<eePromData.EncoderCountsPerRevolution<<endl;//<<"  index:"<<configDataIndex;
        	        		  break;

        	  case 10:
        		  eePromData.referenceValueMessageId=line.toUInt(&ok,16); cout<<"eePromData.referenceValueMessageId: 0x"<<hex<<eePromData.referenceValueMessageId<<endl;//<<"  index:"<<configDataIndex;
        		  break;
        	  case 11:
        		  eePromData.actualValueMessageId =line.toUInt(&ok,16); cout<<"eePromData.actualValueMessageId:  0x"<<hex<< eePromData.actualValueMessageId<<endl;//<<"  index:"<<configDataIndex;
        		  break;
        	  case 12:
        		  eePromData.pidGainsMessageId  =line.toUInt(&ok,16); cout<<"eePromData.pidGainsMessageId: 0x"<<hex<<eePromData.pidGainsMessageId<<endl;//<<"  index:"<<configDataIndex;
        		  break;
        	  case 13:
        		  eePromData.nodeID  =line.toUInt(); cout<<"eePromData.nodeID:"<<dec<<eePromData.nodeID<<endl;//<<"  index:"<<configDataIndex;
        		  break;

        	  }

        	  cout<<dec; //switch back to decimal display after hex display
        	  configDataIndex++;
        	  //cout<<line.toStdString() <<endl;
          }

       }
    }

    inputFile.close();
    cout<<endl<<endl;
    char yesNo;
    cout<<"Config data ok? (press y/n and return):" <<endl;
    cin>>yesNo;
    if ((yesNo=='y') or (yesNo=='Y'))
    {
    		cout<<endl<<"Is old node ID also :"<<eePromData.nodeID<<" ?  (press y/n and return):"<<endl;
    		cin>>yesNo;
    		if ((yesNo=='y') or (yesNo=='Y'))
    		{
    			oldNodeID=eePromData.nodeID;
    			return 1;
    		}
    		else
    		{
    			cout<<"Enter old node ID (enter number between -1 and 64 and return)"<<endl;
    			cin>>oldNodeID;

    			cout<<endl<<endl<<"Old node id is"<<oldNodeID<<" !"<<endl;
    			return 1;
    		}


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


