/*
 * configDataHandling.h
 *
 *  Created on: 15 Nov 2012
 *      Author: alex
 */

#ifndef CONFIGDATAHANDLING_H_
#define CONFIGDATAHANDLING_H_
#include <QSettings>
class configLoader
{


public:
	int loadConfigDataFromFile();
	void printCurrentConfiguration();
	int getStreamLengthIn16bitSize();
	unsigned short * getDataStreamPointer();
private:

	 struct EEPROMDATA_struct {

		union {

			struct {
				short ControlMode; //input 0xFFFF: extern (SPI driven),default
                                  //       1: local position
                                  //       2: local velocity
                                  //       3: local current
				unsigned short cycleTimeIn100usIncrements; //only valid when local control
                                                 // has been selected
				float PGain;
				float IGain;
				float DGain;
				float positiveSaturation;
            	float negativeSaturation;
            	float integratorSaturation;
            	float currentConversionFactor;
            	short EncoderCountsPerRevolution;
            	unsigned short referenceValueMessageId;
                    //message Format: 4byte position, 2byte velocity, 2byte current
            	unsigned short actualValueMessageId;
                    //message Format: 4byte int position, 2byte int velocity, 2byte int current
            	unsigned short pidGainsMessageId;
                    //message Format: 2byte index:   0=no gain config
                    //                               1=Kp
                    //                               2=kd
                    //                               3=ki

                    //                4byte float Kd,Kd or Ki, depending on index (or don't care)
                    //                2byte output on (0) or off (1)
            	unsigned short nodeID;
			}s;


        unsigned short dataStream[21];



		}; //end union

	 };
	 EEPROMDATA_struct eePromData;
};//class


unsigned short serializeData(unsigned dataIndex);
unsigned getNumberOfRequiredCanMessage();
unsigned provideConfigMessageData(short unsigned  *canData, unsigned int messageIndex);
int getOldNodeID();



#endif /* CONFIGDATAHANDLING_H_ */
