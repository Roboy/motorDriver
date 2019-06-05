/*! \file main.c
*
* DEPENDECIES: 
*   UART config loader, drivers of VCP part of linux kernel in 12.04 LTS and above
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
*
*			Serial Port Access requires LibSerial library.
*			Currently version 0.5.2 does not compile on Linux 12.04 LTS unless
*
*			the following changes are made to the source files indicated below.
*
*
*			 src/PosixSignalDispatcher.cpp
*            #include <string.h>
*
*            src/SerialPort.cpp
*            #include <string.h>
*            #include <stdlib.h>

*            src/SerialStreamBuf.cc
*            #include <string.h>

*            examples/read_port.cpp
*            #include <stdlib.h>

*            examples/write_port.cpp
*            include <stdlib.h>
*
*
*
*			Also make sure to add /usr/local/lib/ to your library path since libserial is
*			installed there: e.g. ~$ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
*/

#include <stdio.h>
#include <iostream>
#include <signal.h>

//#include "KvaserCanInterface.h"
#include "configDataHandling.h"
//#include "canConfigLoader.h"
 #include <QCoreApplication>
#include <iostream>
//#include <fstream>
//#include <SerialStream.h>
#include "SerialCommunication.h"

using namespace std;



int main (int argc, char *argv[])

{
  
  QCoreApplication app();
  configLoader motorConfigLoader;

  QSettings settings( "settings.ini", QSettings::IniFormat );
  QString uartName = settings.value("interface/UART", -1).toString();
  cout<<"USING UART as specified in settings.ini: "<<uartName.toStdString()<<endl;


  SerialCommunication serialPort(uartName.toStdString());
  int selection;
  while ((selection=motorConfigLoader.loadConfigDataFromFile())==-2);

  if (selection==-1)
  {
	  cout<<endl<<"Would you like to read current configuration? (y/n)"<<endl;
	  char readConfig;
	  cin>>readConfig;

	  if ((readConfig=='y')||(readConfig=='Y'))
	  {
		  //read config only
		  if (serialPort.ready())
		  {
				  serialPort.PrintCurrentConfiguration();
		  }
		  else
		  {
			  cout<<endl<<"SERIAL PORT NOT READY!"<<endl;
		  }
	  }
	  else
	  {
		  //
	  }
  }




  if (selection>-1)
  {
	  if (serialPort.ready())
	  {
		  cout<<"Configuration Loaded and UART ready, press 1 and return to start configuration"<<endl<<endl;

		  cout<<"Data Stream word length: "<<motorConfigLoader.getStreamLengthIn16bitSize()<<endl;

		  serialPort.ConfigureDriverBoard( motorConfigLoader.getDataStreamPointer(), motorConfigLoader.getStreamLengthIn16bitSize());
	  }
	  else
	  {
		  cout<<"UART PORT NOT ACCESSIBLE, restart!"<<endl;
	  }
  }





  int dummy;
  cout<<" write 0 and press return to end application!"<<endl;
  cin>>dummy;
 

 // cin>>dummy;

  cout<<endl<<"Quitting"<<endl;
}
