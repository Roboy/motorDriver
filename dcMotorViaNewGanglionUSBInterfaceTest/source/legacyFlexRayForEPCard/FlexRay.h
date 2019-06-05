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

#ifndef _EU_MYODE_MYOROBOT_ROBOT_FLEXRAY_H_
#define _EU_MYODE_MYOROBOT_ROBOT_FLEXRAY_H_

#include <QThread>
#include <qmutex.h>

#include <stdio.h>
#include <fcBase/fcBaseTypes.h>
#include <fcBase/fcBaseTypesFlexRay.h>
#include <fcBase/fcBaseTypesPMC.h>
#include <fcBase/fcBaseTypesCAN.h>
#include <fcBase/fcBase.h>
#include <fcBase/fcBaseFlexRay.h>
#include <fcBase/fcBaseCAN.h>
#include <fcBase/fcBasePMC.h>
#include <fcBase/fcBaseLinux.h>
#include "Event.h"
#include "TransmitFrame.h"
#include "CommunicationData.h"

namespace eu
{
namespace myode
{
namespace myorobot
{
class FlexRay: public QThread
{
public:
	FlexRay();

	virtual ~FlexRay();

	void init();

	void deinit();

	void printFlexCards();

	void printInfoHw();

	void printInfoSw();

	void printVersion(const fcVersionNumber& v);

	void printError(const char* szFunction, int CcIndex = -1);

	void run();

	void startMonitoring();

	void stopMonitoring();

	ganglionData_t getGanglionData(int gangID);

	void setRefValue(int gangID, int muscleID, float ref, comsControllerMode controlMode);

	void setControllerParams(int gangID, int muscleID, comsControllerMode controlMode, control_Parameters_t& cp);

	void disableController(int gangID, int muscleID);


	//void setRefValues()

protected:
	void processPackets();

	unsigned int flexCardId, ccFlexRay;

	fcInfoHwSw* pInfo;

	fcError e;

	char *pTemp, *UserId;

	EventSem eventCC1;

	fcFlexCardDeviceId gDevId;

	fcHandle hFlexCard;

	unsigned int slotPayload;

	unsigned int controllerDynamicFrames;

	unsigned int errorMessagePayload;

	TransmitFrame tx_frame[4];

	bool monitoring;

	fcPacket* pPackets;

	ganglionData_t gangDataIn[6];//ganglion data received

	comsCommandFrame gangCommands[6];//ganglion command data to be sent

	float refValues[24];//array of the ref values for all possible connected motors

	control_Parameters_t controlParameters;//control parameters to be sent out in dynamic frame

	bool updateParams;//flag to indicate if the current data in controlParameters should be copied to the dynamic frame buffer

	bool paramsLoaded;//flag to indicate if the dynamic buffer contains new data

	QMutex motorDataMutex, commandMessageMutex, paramUpdateMutex;

	int doubleTrans;
};
}
}
}
#endif
