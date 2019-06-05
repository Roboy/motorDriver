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

#ifndef _EU_MYODE_MYOROBOT_ROBOT_TRANSMITFRAME_H_
#define _EU_MYODE_MYOROBOT_ROBOT_TRANSMITFRAME_H_

#include <fcBase/fcBaseTypes.h>

namespace eu
{
namespace myode
{
namespace myorobot
{
class TransmitFrame
{
public:
	fcDword FrameId;
	fcDword BufferIdx;
	fcWord Payload[fcPayloadMaximum];
	fcByte PayloadLength;
};
}
}
}
#endif
