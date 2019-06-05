/*
 * SerialCommunication.h
 *
 *  Created on: 14 Aug 2014
 *      Author: alex
 */

#ifndef SERIALCOMMUNICATION_H_
#define SERIALCOMMUNICATION_H_
#include <fstream>
#include <SerialStream.h>
#include <string>

#define CONFIG_START_STRING "readyForConfiguration.\n"
class SerialCommunication
{

public:
	 SerialCommunication(std::string const& uartName);
	 bool ready();
	 int PrintCurrentConfiguration();
	 int ConfigureDriverBoard(unsigned short * configurationData, int dataLength);
private:
	 int CommsReady;
	 LibSerial::SerialStream serial_port;
};

#endif /* SERIALCOMMUNICATION_H_ */
