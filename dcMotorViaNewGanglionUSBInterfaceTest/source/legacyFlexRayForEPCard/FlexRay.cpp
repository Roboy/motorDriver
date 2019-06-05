/*
 *  Copyright (c) 2012, MYOROBOTICS consortium
 *  Author: Konstantinos Dalamagkidis, Steffen Wittmeier
 *  All rights reserved
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification is governed by the MYOROBOTICS Non-Commercial Software
 *  License Agreement. See LICENSE file distributed with this work for
 *  additional information.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under this license is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either expressed or
 *  implied. See the License for the specific language governing permissions
 *  and limitations under the License.
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include "FlexRay.h"
#include "Util.h"

namespace eu
{
namespace myode
{
namespace myorobot
{
FlexRay::FlexRay() :
		flexCardId(0),
		ccFlexRay(0),
		pInfo(0),
		e(0),
		pTemp(0),
		UserId(0),
		gDevId(fcNoDevice),
		hFlexCard(0),
		slotPayload(44),
		controllerDynamicFrames(1),
		errorMessagePayload(20),
		updateParams(false),
		paramsLoaded(false),
		monitoring(false),
		gangDataIn(),
		gangCommands(),
		refValues(),
		commandMessageMutex(),
		motorDataMutex(),
		paramUpdateMutex(),
		doubleTrans(0)
{
}

FlexRay::~FlexRay()
{
}

void FlexRay::init()
{
	e = fcbGetEnumFlexCardsV3(&pInfo, false); // get only available FlexCards

	if (0 != e)
	{
		printError("fcbGetEnumFlexCardsV3", e);

		deinit();
	}
	else
	{
		flexCardId = pInfo->FlexCardId;

		gDevId = pInfo->InfoHardware.DeviceId;

		ccFlexRay = pInfo->InfoHardware.UseableCCs.FlexRay;

		printf("\n----- Eberspaecher Electronics - fcDemoLinux -----\n\n");

		printFlexCards();

		//std::cout << "pInfo=" << pInfo << std::endl;

		e = fcFreeMemory(fcMemoryTypeInfoHwSw, pInfo);
		if (0 != e)
		{
			printError("[fcFreeMemory]", e);
			deinit();
		}

		if (0 == flexCardId)
		{
			printf("No FlexCard available.\n");
			deinit();
		}

		std::string chiContent;
		std::ifstream file1(
				"/home/p2-bremner/MYODEWorkspace/MYODE/src/eu.myode.Myorobot/robot/TEST.chi");

		//printf("testing!!$%%%");
		// Read the CHI-Files
		if (!file1.is_open())
		{
			printf("Could not open chi-file1:\n");
			deinit();
		}
		else
		{
			char ch;
			while (file1.get(ch))
				chiContent += ch;
			file1.close();
		}

		//std::cout << chiContent;

		e = fcbOpen(&hFlexCard, flexCardId);
		if (0 != e)
		{
			printError("[fcbOpen]", e);
			deinit();
		}

		e = fcbFRSetCcConfigurationChi(hFlexCard, (fcCC) fcCC1,
				chiContent.c_str());
		if (0 != e)
		{
			printError("[fcbFRSetCcConfigurationChi]", fcCC1);

			deinit();
		}

		fcFRCcConfig frCcConfigGet;

		e = fcbFRGetCcConfiguration(hFlexCard, fcCC1, &frCcConfigGet);

		if (0 != e)
			printf("fcbFRGetCcConfiguration error");

		printf("Baudrate = %d\n", frCcConfigGet.BaudRate);

		fcMsgBufCfg cfg;
		unsigned int bufferId;
		memset(&cfg, 0, sizeof(fcMsgBufCfg));

		//configure the transmit buffers

		//first the static buffers

		cfg.Type = fcMsgBufTx;
		cfg.ChannelFilter = fcChannelA;
		cfg.CycleCounterFilter = 0x0; //no cycle filtering ,i.e., transmit every cycle
		cfg.Tx.FrameId = 1;
		cfg.Tx.PayloadLength = slotPayload;
		cfg.Tx.PayloadLengthMax = 127;
		cfg.Tx.PayloadPreambleIndicator = 0;
		cfg.Tx.SyncFrameIndicator = 1;
		cfg.Tx.StartupFrameIndicator = 1;
		cfg.Tx.TxAcknowledgeEnable = 0;
		cfg.Tx.TransmissionMode = fcMsgBufTxContinous;
		fcCC eCC = fcCC1;

		e = fcbFRConfigureMessageBuffer(hFlexCard, eCC, &bufferId, cfg);
		tx_frame[0].BufferIdx = bufferId;
		tx_frame[0].FrameId = cfg.Tx.FrameId;
		tx_frame[0].PayloadLength = slotPayload;

		cfg.Tx.FrameId = 2;
		cfg.Tx.SyncFrameIndicator = 0;
		cfg.Tx.StartupFrameIndicator = 0;
		e = fcbFRConfigureMessageBuffer(hFlexCard, eCC, &bufferId, cfg);
		tx_frame[1].BufferIdx = bufferId;
		tx_frame[1].FrameId = cfg.Tx.FrameId;
		tx_frame[1].PayloadLength = slotPayload;

		//then the dynamic ones
		cfg.Tx.TransmissionMode = fcMsgBufTxSingleShot; //dynamic messages are singleshot mode
		cfg.Tx.PayloadLength = 42;

		for (int i = 0; i < controllerDynamicFrames; i++)
		{
			cfg.Tx.FrameId = 9 + i; //there are 8 static frames, then the pc min-frames (ganglion mini-frames are after those)
			e = fcbFRConfigureMessageBuffer(hFlexCard, eCC, &bufferId, cfg);
			tx_frame[2 + i].BufferIdx = bufferId;
			tx_frame[2 + i].FrameId = cfg.Tx.FrameId;
			tx_frame[2 + i].PayloadLength = cfg.Tx.PayloadLength;
		}

		//configure the receive buffers
		memset(&cfg, 0, sizeof(fcMsgBufCfg));
		fcDword pData[6];
		int pDataIndex = 0;
		cfg.Type = fcMsgBufRx;
		cfg.ChannelFilter = fcChannelA;
		cfg.CycleCounterFilter = 0x0; //no cycle filtering ,i.e., transmit every cycle

		//static buffers
		cfg.Rx.PayloadLengthConfigured = slotPayload;
		cfg.Rx.PayloadLengthMax = 127;
		cfg.Rx.RxAcknowledgeEnable = 1; //not sure if I need this

		for (int frame = 3; frame <= 8; frame++)
		{
			cfg.Rx.FrameId = frame;
			e = fcbFRConfigureMessageBuffer(hFlexCard, eCC, &bufferId, cfg);
			pData[pDataIndex] = frame;
			pDataIndex++;
		}

		//dynamic buffers
		cfg.Rx.PayloadLengthConfigured = errorMessagePayload;
		for (int frame = 8 + controllerDynamicFrames+1;
				frame <= 8 + controllerDynamicFrames + 6; frame++)
		{
			cfg.Rx.FrameId = frame;
			e = fcbFRConfigureMessageBuffer(hFlexCard, eCC, &bufferId, cfg);
		}
		/*
		 //only accept static frames
		 e = fcbFRSetSoftwareAcceptanceFilter(hFlexCard, eCC, fcChannelA, pData, 6);
		 if(e)
		 printError("[fcbFRSetSoftwareAcceptanceFilter]", e, fcCC1);

		 e = fcbFRSetHardwareAcceptanceFilter(hFlexCard, eCC, fcChannelA, pData, 6, true);
		 if(e)
		 printError("[fcbFRSetHardwareAcceptanceFilter]", e, fcCC1);
		 */
		// set FlexRay bus termination
		fcbSetBusTermination(hFlexCard, fcBusChannel1, fcBusTypeFlexRay, true);

		// set event handle and start monitoring CC1
		e = fcbSetEventHandleSemaphore(hFlexCard, fcCC1, (void *) eventCC1,
				fcNotificationTypeFRCycleStarted);
		if (0 != e)
		{
			printError("[fcbSetEventHandleSemaphore]", fcCC1);
			deinit();
		}

		startMonitoring();
	}
}

void FlexRay::deinit()
{
	monitoring = false;

	//munlockall();
}

void FlexRay::printFlexCards()
{
	fcInfoHwSw* pInfo = this->pInfo;

	while (pInfo != NULL)
	{
		// if FlexCard Id is equal to zero we got NO FlexCard in the system
		bool bFlexCardAvailable = (0 != pInfo->FlexCardId);

		printf("FlexCard Id:  ");
		if (bFlexCardAvailable)
			printf("%u\n", pInfo->FlexCardId);
		else
			printf("Not available\n");

		printf("UserCard Id:  ");
		if (bFlexCardAvailable)
			printf("%u\n", pInfo->UserDefinedCardId);
		else
			printf("Not available\n");

		printf("Dev Busy:     ");
		if (bFlexCardAvailable)
			printf("%d\n", pInfo->Busy);
		else
			printf("Not available\n");

		if (bFlexCardAvailable)
		{
			printInfoHw();
			printInfoSw();
		}
		else
		{
			printf("Software Information:\n");

			printf("\tDLL:      ");
			printVersion(pInfo->InfoSoftware.VersionBaseDll);

			printf("\tDriver:   ");
			printVersion(pInfo->InfoSoftware.VersionDeviceDriver);
		}

		printf("\n");

		pInfo = pInfo->pNext; // get the next FlexCard
	}

}

void FlexRay::printInfoHw()
{
	fcInfoHw* pInfoHw = &pInfo->InfoHardware;

	if (NULL == pInfoHw)
		return;
	printf("Hardware Information:\n");

	printf("\tSerial:   %llu\n", pInfoHw->Serial);

	printf("\tDevId:    ");
	switch (pInfoHw->DeviceId)
	{
	case fcFlexCardCycloneII:
		printf("Cyclone II\n");
		break;
	case fcFlexCardCycloneIISE:
		printf("Cyclone II SE\n");
		break;
	case fcFlexCardPMC:
		printf("PMC\n");
		break;
	case fcFlexCardPMCII:
		printf("PMCII\n");
		break;
	default:
		printf("not available\n");
		break;
	};

	printf("\tFirmware: ");
	printVersion(pInfoHw->VersionFirmware);

	printf("\tHardware: ");
	printVersion(pInfoHw->VersionHardware);

	printf("\t-BusType- Sup Lic Use\n");
	printf("\t FlexRay   %1d   %1d   %1d\n", pInfoHw->SupportedCCs.FlexRay,
			pInfoHw->LicensedCCs.FlexRay, pInfoHw->UseableCCs.FlexRay);
	printf("\t CAN       %1d   %1d   %1d\n", pInfoHw->SupportedCCs.CAN,
			pInfoHw->LicensedCCs.CAN, pInfoHw->UseableCCs.CAN);

}

void FlexRay::printInfoSw()
{
	fcInfoSw* pInfoSw = &pInfo->InfoSoftware;

	if (NULL == pInfoSw)
		return;
	printf("Software Information:\n");

	printf("\tDLL:      ");
	printVersion(pInfoSw->VersionBaseDll);

	printf("\tDriver:   ");
	printVersion(pInfoSw->VersionDeviceDriver);

	printf("\tLicense:  Windows %d Linux %d Xenomai %d\n",
			pInfoSw->LicensedForWindowsDriver, pInfoSw->LicensedForLinuxDriver,
			pInfoSw->LicensedForXenomaiDriver);
}

void FlexRay::printVersion(const fcVersionNumber& v)
{
	printf("%d.%d.%d.%d\n", v.Major, v.Minor, v.Update, v.Release);
}

void FlexRay::printError(const char* szFunction, int CcIndex)
{
	char* szError = NULL;

	fcError error = fcGetErrorText(e, &szError);

	if (0 != error)
	{
		printf("printError: Function fcGetErrorText returned with error 0x%X\n",
				e);
	}
	else
	{
		if (0 >= CcIndex)
			printf(
					"Error: Function %s (CC%01d) returned with error 0x%X (%s)\n",
					szFunction, CcIndex + 1, e, szError);
		else
			printf("Error: Function %s returned with error 0x%X (%s)\n",
					szFunction, e, szError);
	}

	if (NULL != szError)
	{
		error = fcFreeMemory(fcMemoryTypeString, szError);
		if (0 != error)
			printf(
					"printError: Function fcFreeMemory returned with error 0x%X\n",
					e);
	}
}

void FlexRay::run()
{
	e = fcbFRMonitoringStart(hFlexCard, fcCC1, fcMonitoringNormal, true, true, true, true);
	printf("monitoring\n");
	unsigned int i = 0, fail = 0;

	while (monitoring)
	{
		// Wait for NewCycle on CC1
		fcDword nTimeoutInMilliSeconds = 10000;
		bool bRet = eventCC1.WaitForEvent(nTimeoutInMilliSeconds);
		if (!bRet)
		{
			printError("[WaitForEvent]", 0);
			deinit();
		}


		// Receive all frames
		pPackets = NULL;
		e = fcbReceive(hFlexCard, &pPackets);
		if (0 != e)
		{
			printError("[fcbReceive]", e);
			deinit();
		}
		else
		{
			if (NULL != pPackets)
			{
				//printf("Packets Received\n");
				processPackets(); //will need to edit process packets to do stuff with the received data and pipe it to MYODE
				e = fcFreeMemory(fcMemoryTypePacket, pPackets);
				if (0 != e)
				{
					printError("[fcFreeMemory]", e);
					deinit();
				}
			}
			else
			{
				//printf("No Packets Received\n");
				//after 10 times of getting no packets give up,
				//comment this out to see the sent messages as it causes CleanUp to be called
				fail++;
				//if (fail > 10)
				//	deinit();
			}
		}

		//Update data
		commandMessageMutex.lock();


		if(updateParams)
		{
			printf("mode %d\n", gangCommands[1].OperationMode[1]);
			memcpy(tx_frame[2].Payload, &controlParameters, sizeof(controlParameters));

			paramsLoaded = true;
			updateParams = false;
			paramUpdateMutex.lock();
		}

		memcpy(tx_frame[0].Payload, gangCommands, sizeof(gangCommands));
		memcpy(tx_frame[1].Payload, refValues, sizeof(refValues));


		commandMessageMutex.unlock();

		// Transmit frames
		for (int txframe = 0; txframe < 2; txframe++)
		{
			e = fcbFRTransmit(hFlexCard, (fcCC) fcCC1,
			tx_frame[txframe].BufferIdx, tx_frame[txframe].Payload,
			tx_frame[txframe].PayloadLength);
			if (0 != e)
			{
				printError("[fcbFRTransmit]", txframe);
				printf("Error: Frame %d\n", tx_frame[txframe].FrameId);
			}
		}

		if(paramsLoaded)
		{
			e = fcbFRTransmit(hFlexCard, (fcCC) fcCC1,
			tx_frame[2].BufferIdx, tx_frame[2].Payload,
			tx_frame[2].PayloadLength);
			if (0 != e)
			{
				printError("[fcbFRTransmit]", 2);
				printf("Error: Frame %d\n", tx_frame[2].FrameId);
			}

			/* Receiving data, and loading the new data into the message buffers takes longer than the time between frame start
			 * and transmission of data in static slot 1, but happens before the dynamic slot so the dynamic data is effectively
			 * transmitted one cycle before the corresponding command message in the static slot. To counteract this the dynamic
			 * data is transmitted in two consecutive cycles without changing the command frame word. A better fix going forward
			 * is to add an address and control_mode field to the dynamic data and use its arrival to trigger a parameter update,
			 * rather than a message in the command frame.
			 */
			if(doubleTrans==0)
				doubleTrans++;
			else
			{
				paramsLoaded = false;
				doubleTrans = 0;
				paramUpdateMutex.unlock();
			}
		}

		/*
		if(i==100)
		{
		std::system ( "clear" );
		int gangs=3;
		int motors=2;
		for(int gang=0; gang<gangs; gang++)
		{
			for(int motor=0; motor<motors; motor++)
				std::cout<< gangDataIn[gang].muscleState[motor].actuatorCurrent << "\t";
			std::cout<<std::endl;
			for(int motor=0; motor<motors; motor++)
				std::cout<< gangDataIn[gang].muscleState[motor].actuatorPos<< "\t";
			std::cout<<std::endl;
			for(int motor=0; motor<motors; motor++)
				std::cout<< gangDataIn[gang].muscleState[motor].actuatorVel<< "\t";
			std::cout<<std::endl;
			for(int motor=0; motor<motors; motor++)
				std::cout<< gangDataIn[gang].muscleState[motor].jointPos<< "\t";
			std::cout<<std::endl;
			for(int motor=0; motor<motors; motor++)
				std::cout<< gangDataIn[gang].muscleState[motor].tendonDisplacement << "\t";
			std::cout<<std::endl;
			std::cout<<std::endl;
		}

		i=0;
		}
		else
			i++;
		*/


	}

	e = fcbFRMonitoringStop(hFlexCard, (fcCC) fcCC1);
	if (0 != e)
		printError("[fcbFRMonitoringStop]", fcCC1);

	if (NULL != hFlexCard)
	{
		fcError e = 0;

		// Stop monitoring CC1 and CC2
		//for (int CcIndex = fcCC1; CcIndex < MAXCCCOUNT; CcIndex++)
		//{
		// reset FlexRay bus termination
		fcbSetBusTermination(hFlexCard, fcBusChannel1, fcBusTypeFlexRay, false);
		//fcbSetBusTermination(hFlexCard, fcBusChannel2, fcBusTypeFlexRay, false);

		// Close FlexCard
		e = fcbClose(hFlexCard);
		if (0 != e)
			printError("[fcbClose]", e);

		hFlexCard = NULL;
	}

	// flush any pending printf's
	fflush(stdout);
}



void FlexRay::startMonitoring()
{
	monitoring = true;

	start();
}

void FlexRay::stopMonitoring()
{
	monitoring = false;

	if (isRunning())
	{
		if (!wait(1000))
		{
			terminate();
		}
	}

	deinit();
}

ganglionData_t FlexRay::getGanglionData(int gangID)
{
	QMutexLocker locker(&motorDataMutex);//lock the motorDataMutex
	return gangDataIn[gangID];
}

void FlexRay::setRefValue(int gangID, int muscleID, float ref, comsControllerMode controlMode)
{
	QMutexLocker locker(&commandMessageMutex);
	gangCommands[gangID].ControlMode[muscleID] = controlMode;
	gangCommands[gangID].OperationMode[muscleID] = Run;
	refValues[4*gangID+muscleID] = ref;
}

void FlexRay::setControllerParams(int gangID, int muscleID, comsControllerMode controlMode, control_Parameters_t& cp)
{
	QMutexLocker locker(&paramUpdateMutex);//mutex to signal the data has been sent
	QMutexLocker locker2(&commandMessageMutex);//mutex to protect loading buffers
	controlParameters = cp;
	gangCommands[gangID].ControlMode[muscleID] = controlMode;
	gangCommands[gangID].OperationMode[muscleID] = Initialise;
	updateParams = true;

}

void FlexRay::disableController(int gangID, int muscleID)
{
	QMutexLocker locker(&commandMessageMutex);
	gangCommands[gangID].OperationMode[muscleID] = Disable;

}

void FlexRay::processPackets()
{
	fcPacket* p = pPackets;
	fcFlexRayFrame* fcFrame;
	QMutexLocker locker(&motorDataMutex);//lock the motorDataMutex for the duration of process packets

	while (NULL != p)
	{
		switch (p->Type)
		{
		case fcPacketTypeInfo:
		case fcPacketTypeError:
		case fcPacketTypeStatus:
		case fcPacketTypeTrigger:
		case fcPacketTypeTxAcknowledge:
		case fcPacketTypeNMVector:
		case fcPacketTypeNotification:
		case fcPacketTypeTriggerEx:
		case fcPacketTypeCAN:
		case fcPacketTypeCANError:
			//Util::print(p, gDevId);
			break;
		case fcPacketTypeFlexRayFrame:
			//Util::print(p, gDevId);
			fcFrame = p->FlexRayFrame;
			memcpy(gangDataIn+(fcFrame->ID-3), fcFrame->pData, sizeof(ganglionData_t));//destination address is incremented using message ID, but Ganglion IDs are 3-8.
			break;
		default:
			break;
		};

		// get the next packet
		p = p->pNextPacket;
	}
}
}
}
}
