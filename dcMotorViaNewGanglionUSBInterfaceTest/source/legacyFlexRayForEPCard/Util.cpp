#include "Util.h"
#include <stdarg.h>
#include <stdio.h>

using namespace std;

typedef struct s_item
{
	int FlagId;
	string FlagText;
} t_item, *p_item;

static t_item g_State[] =
{
	{fcStateUnknown, "UNKNOWN"},
	{fcStateConfig, "CONFIG"},
	{fcStateNormalActive, "NORMAL_ACTIVE"},
	{fcStateNormalPassive, "NORMAL_PASSIVE"},
	{fcStateHalt, "HALT"},
	{fcStateReady, "READY"},
	{fcStateStartup, "STARTUP"},
	{fcStateWakeup, "WAKEUP"},
	{fcStateMonitorMode, "MONITOR_MODE"},
};
static unsigned int g_sizeState = sizeof(g_State) / sizeof(g_State[0]);

static t_item g_WakeupStatus[] =
{
	{fcWakeupStatusUndefined, "UNDEFINED"},
	{fcWakeupStatusReceiveHeader, "RECEIVE_HEADER"},
	{fcWakeupStatusReceiveWUP, "RECEIVE_WUP"},
	{fcWakeupStatusCollisionHeader, "COLLISION_HEADER"},
	{fcWakeupStatusCollisionWUP, "COLLISION_WUP"},
	{fcWakeupStatusCollisionUnknown, "COLLISION_UNKNOWN"},
	{fcWakeupStatusTransmitted, "TRANSMITTED"},
};
static unsigned int g_sizeWakeupStatus = sizeof(g_WakeupStatus) / sizeof(g_WakeupStatus[0]);

static t_item g_Error[] =
{
	{fcErrNone, "None"},
	{fcErrFlexcardOverflow, "FlexcardOverflow"},
	{fcErrPOCErrorModeChanged, "POCErrorModeChanged"},
	{fcErrSyncFramesBelowMinimum, "SyncFramesBelowMinimum"},
	{fcErrSyncFrameOverflow, "SyncFrameOverflow"},
	{fcErrClockCorrectionFailure, "ClockCorrectionFailure"},
	{fcErrParityError, "ParityError"},
	{fcErrReceiveFIFOOverrun, "ReceiveFIFOOverrun"},
	{fcErrEmptyFIFOAccess, "EmptyFIFOAccess"},
	{fcErrIllegalInputBufferAccess, "IllegalInputBufferAccess"},
	{fcErrIllegalOutputbufferAccess, "IllegalOutputbufferAccess"},
	{fcErrSyntax, "SyntaxError"},
	{fcErrContent, "ContentError"},
	{fcErrSlotBoundaryViolation, "SlotBoundaryViolationError"},
	{fcErrTransmissionAcrossBoundary, "TransmissionAcrossBoundaryError"},
	{fcErrLatestTransmitViolation, "LatestTransmitViolationError"},
	{fcErrSyntaxSW, "SyntaxErrorSymbolWindow"},
	{fcErrSlotBoundaryViolationSW, "SlotBoundaryViolationErrorSymbolWindow"},
	{fcErrTransmissionConflictSW, "TransmissionConflictErrorSymbolWindow"},
	{fcErrSyntaxNIT, "SyntaxErrorNetworkIdleTime"},
	{fcErrSlotBoundaryViolationNIT, "SlotBoundaryViolationErrorNetworkIdleTime"},
};
static unsigned int g_sizeError = sizeof(g_Error) / sizeof(g_Error[0]);

static t_item g_Status[] =
{
	{fcStatusNone, "None"},
	{fcStatusWakeupStatus, "WakeupStatus"},
	{fcStatusCollisionAvoidanceSymbol, "CollisionAvoidanceSymbol"},
	{fcStatusStartupCompletedSuccessfully, "StartupCompletedSuccessfully"},
	{fcStatusWakeupPatternChannelA, "WakeupPatternA"},
	{fcStatusWakeupPatternChannelB, "WakeupPatternB"},
	{fcStatusMTSReceivedonChannelA, "MTSReceivedonChannelA"},
	{fcStatusMTSReceivedonChannelB, "MTSReceivedonChannelB"},
};
static unsigned int g_sizeStatus = sizeof(g_Status) / sizeof(g_Status[0]);

static t_item g_TriggerCondition[] =
{
	{0, "TriggerConditionUnknown"},
	{fcTriggerConditionFallingEdge, "TriggerConditionFallingEdge"},
	{fcTriggerConditionRisingEdge, "TriggerConditionRisingEdge"},
	{fcTriggerConditionCycleStart, "TriggerConditionCycleStart"},
	{fcTriggerConditionUser, "TriggerConditionUser"},
	{fcTriggerConditionErrorDetected, "TriggerConditionErrorDetected"},
	{fcTriggerConditionStartupCompleted, "TriggerConditionStartupCompleted"},
	{fcTriggerConditionTimer, "TriggerConditionTimer"},
};
static unsigned int g_sizeTriggerCondition = sizeof(g_TriggerCondition) / sizeof(g_TriggerCondition[0]);

static t_item g_CANState[] =
{
	{fcCANCcStateUnknown, "UNKNOWN"},
	{fcCANCcStateConfig, "CONFIG"},
	{fcCANCcStateNormalActive, "NORMAL_ACTIVE"},
	{fcCANCcStateWarning, "WARNING"},
	{fcCANCcStateErrorPassive, "ERROR_PASSIVE"},
	{fcCANCcStateBusOff, "BUS_OFF"},
};
static unsigned int g_sizeCANState = sizeof(g_CANState) / sizeof(g_CANState[0]);

static t_item g_CANError[] =
{
	{fcCANErrorNone, "None"},
	{fcCANErrorStuff, "Stuff"},
	{fcCANErrorForm, "Form"},
	{fcCANErrorAcknowledge, "Acknowledge"},
	{fcCANErrorBit1, "Bit1"},
	{fcCANErrorBit0, "Bit0"},
	{fcCANErrorCRC, "CRC"},
	{fcCANErrorParity, "Parity"},
};
static unsigned int g_sizeCANError = sizeof(g_CANError) / sizeof(g_CANError[0]);

std::string GetChannelAsString(fcChannel ch)
{
	if (fcChannelA == ch)
		return ("A");
	else if (fcChannelB == ch)
		return ("B");
	else if (fcChannelBoth == ch)
		return ("A+B");

	return ("None");
}

std::string Format(const char* szFormat, ...)
{
	const int MAX = 512;
	char szBuffer[MAX];

	va_list ptr;
	va_start(ptr, szFormat);

	int nTotalLen = vsnprintf(szBuffer, MAX, szFormat, ptr);
	if (0 > nTotalLen || MAX == nTotalLen)
	{
		nTotalLen = MAX;
		szBuffer[nTotalLen-1] = 0;
	}

	return std::string(szBuffer);
}

void Util::print(fcPacket* p, fcFlexCardDeviceId Id)
{
	std::string sz;

	switch (p->Type)
	{
		case fcPacketTypeInfo:
			sz = ToString(p->InfoPacket, Id);
			break;
		case fcPacketTypeFlexRayFrame:
			sz = ToString(p->FlexRayFrame, Id);
			break;
		case fcPacketTypeError:
			sz = ToString(p->ErrorPacket, Id);
			break;
		case fcPacketTypeStatus:
			sz = ToString(p->StatusPacket, Id);
			break;
		case fcPacketTypeTrigger:
			sz = ToString(p->TriggerPacket, Id);
			break;
		case fcPacketTypeTxAcknowledge:
			sz = ToString(p->TxAcknowledgePacket, Id);
			break;
		case fcPacketTypeNMVector:
			sz = ToString(p->NMVectorPacket, Id);
			break;
		case fcPacketTypeNotification:
			sz = ToString(p->NotificationPacket, Id);
			break;
		case fcPacketTypeTriggerEx:
			sz = ToString(p->TriggerExPacket, Id);
			break;
		case fcPacketTypeCAN:
			sz = ToString(p->CANPacket, Id);
			break;
		case fcPacketTypeCANError:
			sz = ToString(p->CANErrorPacket, Id);
			break;
		default:
			sz = "Unknown packet identifier";
			break;
	}

	printf("%s\n", sz.c_str());
}

string Util::ToString(fcInfoPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szCC = Format("CC%01d", pFrame->CC+1);

	string szType("InfoPacket");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szCycle = Format("%03d", pFrame->CurrentCycle);

	string szRateCorrection = Format("Rate Correction: %d", pFrame->RateCorrection);
	string szOffsetCorrection = Format("Offset Correction: %d", pFrame->OffsetCorrection);
	string szClockCorrectionFailedCounter = Format("Clock Correction Failed Counter: %d", pFrame->ClockCorrectionFailedCounter);
	string szPassiveToActiveCount = Format("Passive To Active Count: %d", pFrame->PassiveToActiveCount);

	return szCC + "\t" + szType + "\t" + szTimestamp + "\t" + szCycle + "\t" + szRateCorrection + ", " + szOffsetCorrection + ", " + szClockCorrectionFailedCounter + ", " + szPassiveToActiveCount;
}

string Util::ToString(fcFlexRayFrame* pFrame, fcFlexCardDeviceId Id)
{
	if (pFrame == NULL)
		return "";

	string szCC = Format("CC%01d", pFrame->CC+1);

	string szType("FlexRayFrame");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szCycle = Format("%03d", pFrame->CycleCount);

	string szChannel(GetChannelAsString(pFrame->Channel));

	string szId = Format("%d", pFrame->ID);

	string szData = Format("Len: %04d -", pFrame->PayloadLength);

	int len = pFrame->PayloadLength;
	for (int i = 0; i < len; i++)
	{
		szData += Format(" %04X", pFrame->pData[i]);
	}

	if (pFrame->PP)
		szData.append(" PP");
	if (pFrame->NF)
		szData.append(" NF");
	if (pFrame->SYNC)
		szData.append(" SYNC");
	if (pFrame->STARTUP)
		szData.append(" STARTUP");
	if (pFrame->SyntaxError)
		szData.append(" SyntaxError");
	if (pFrame->ContentError)
		szData.append(" ContentError");
	if (pFrame->ValidFrame)
		szData.append(" ValidFrame");
	if (pFrame->SlotBoundaryViolation)
		szData.append(" SlotBoundaryViolation");
	if (pFrame->AsyncMode)
	{
		szData.append(" AsyncMode");
		szData +=  Format(" FrameCRC: %06X", pFrame->FrameCRC);
	}

	string szHeaderCRC = Format("HeaderCRC: %03X", pFrame->HeaderCRC);

	return szCC + "\t" + szType + "\t" + szTimestamp + "\t" + szCycle + "\t" + szChannel + "\t" + szId + "\t" + szData + "\t" + szHeaderCRC;
}

string Util::ToString(fcErrorPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szCC = Format("CC%01d", pFrame->CC+1);

	string szType("ErrorPacket");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szCycle = Format("%03d", pFrame->CycleCount);

	string szData;

	for (unsigned int i = 0; i < g_sizeError; i++)
	{
		if (g_Error[i].FlagId == pFrame->Flag)
		{
			szData.append(Format("%s", g_Error[i].FlagText.c_str()));
			break;
		}
	}

	switch (pFrame->Flag)
	{
		case fcErrClockCorrectionFailure:
		{
			fcErrClockCorrectionFailureInfo* CCFailureInfo = &pFrame->AdditionalInfo.ErrClockCorrectionFailureInfo;
			
			if (CCFailureInfo->MissingOffsetCorrection)
				szData.append(" MissingOffsetCorrection ");
			if (CCFailureInfo->MissingRateCorrection)
				szData.append(" MissingRateCorrection ");
			if (CCFailureInfo->OffsetCorrectionLimitReached)
				szData.append(" OffsetCorrectionLimitReached ");

			szData.append(Format(" SyncFramesEvenA: %d ", CCFailureInfo->SyncFramesEvenA));
			szData.append(Format(" SyncFramesEvenB: %d ", CCFailureInfo->SyncFramesEvenB));
			szData.append(Format(" SyncFramesOddA: %d ", CCFailureInfo->SyncFramesOddA));
			szData.append(Format(" SyncFramesOddB: %d ", CCFailureInfo->SyncFramesOddB));
			break;
		}

		case fcErrSyncFramesBelowMinimum:
		case fcErrSyncFrameOverflow:
		{
			fcErrSyncFramesInfo* SyncFramesInfo = &pFrame->AdditionalInfo.ErrSyncFramesInfo;

			szData.append(Format(" SyncFramesEvenA: %d", SyncFramesInfo->SyncFramesEvenA));
			szData.append(Format(" SyncFramesEvenB: %d", SyncFramesInfo->SyncFramesEvenB));
			szData.append(Format(" SyncFramesOddA: %d", SyncFramesInfo->SyncFramesOddA));
			szData.append(Format(" SyncFramesOddB: %d", SyncFramesInfo->SyncFramesOddB));
			break;
		}

		case fcErrParityError:
		{
			szData.append(" Internal E-Ray Error");
			break;
		}

		case fcErrReceiveFIFOOverrun:
		case fcErrEmptyFIFOAccess:
		case fcErrIllegalInputBufferAccess:
		case fcErrIllegalOutputbufferAccess:
			break;

		case fcErrSyntaxSW:
		case fcErrSyntaxNIT:
		case fcErrSyntax:
		case fcErrContent:
		case fcErrSlotBoundaryViolation:
		case fcErrSlotBoundaryViolationSW:
		case fcErrSlotBoundaryViolationNIT:
		case fcErrTransmissionAcrossBoundary:
		case fcErrTransmissionConflictSW:
		case fcErrLatestTransmitViolation:
		{
			fcErrSlotInfo* SlotInfo = &pFrame->AdditionalInfo.ErrSlotInfo;
			
			szData.append(Format(" SlotCount: %d", SlotInfo->SlotCount));
			break;
		}

		default:
			break;
	}

	return szCC + "\t" + szType + "\t" + szTimestamp + "\t" + szCycle + "\t" + szData;
}

string Util::ToString(fcStatusPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szCC = Format("CC%01d", pFrame->CC+1);

	string szType("StatusPacket");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szCycle = Format("%03d", pFrame->CycleCount);
	string szData;

	for (unsigned int i = 0; i < g_sizeStatus; i++)
	{
		if (g_Status[i].FlagId == pFrame->Flag)
		{
			szData.append(Format("%s ", g_Status[i].FlagText.c_str()));
			break;
		}
	}

	switch (pFrame->Flag)
	{
		case fcStatusWakeupStatus:
		{
			fcStatusWakeupInfo* WakeupInfo = &pFrame->AdditionalInfo.StatusWakeupInfo;
			
			for (unsigned int i = 0; i < g_sizeWakeupStatus; i++)
			{
				if (g_WakeupStatus[i].FlagId == WakeupInfo->WakeupStatus)
					szData.append(Format(" %s ", g_WakeupStatus[i].FlagText.c_str()));
			}
			break;
		}

		default:
			break;
	}
	
	return szCC + "\t" + szType + "\t" + szTimestamp + "\t" + szCycle + "\t" + szData;
}

string Util::ToString(fcTriggerInfoPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szType("TriggerInfo");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szData;

	if (pFrame->Type == fcTriggerTypeHardware)
		szData.append("Hardware");
	else if (pFrame->Type == fcTriggerTypeSoftware)
		szData.append("Software");
	else
		szData.append("Unknown");

	szData.append(Format(" %s", g_TriggerCondition[pFrame->Condition].FlagText.c_str()));

	szData.append(Format(" SequenceCount: %d", pFrame->SequenceCount));

	// The PerformanceCounter is only available for FlexCard Windows driver.
	if (pFrame->Type == fcTriggerTypeSoftware)
	{
#ifdef WIN32
		szData.append(Format(" PerformanceCounter: %I64d", pFrame->PerformanceCounter));
#else
		szData.append(Format(" PerformanceCounter: NOT IMPLEMENTED"));
#endif
	}

	return szType + "\t" + szTimestamp + "\t" + szData;
}

string Util::ToString(fcTxAcknowledgePacket* pFrame, fcFlexCardDeviceId Id)
{
	string szCC = Format("CC%01d", pFrame->CC+1);

	string szType("TxAcknowledge");

	string szIdx = Format("BufferId: %04d", pFrame->BufferId);

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szCycle = Format("%03d", pFrame->CycleCount);

	string szChannel(GetChannelAsString(pFrame->Channel));

	string szId = Format("Id: %04d",pFrame->ID);

	string szData = Format("Len: %04d -", pFrame->PayloadLength);

	int len = pFrame->PayloadLength;
	for (int i = 0; i < len; i++)
	{
		szData += Format(" %04X", pFrame->pData[i]);
	}

	if (pFrame->PP)
		szData.append(" PP");
	if (pFrame->NF)
		szData.append(" NF");
	if (pFrame->SYNC)
		szData.append(" SYNC");
	if (pFrame->STARTUP)
		szData.append(" STARTUP");
	if (pFrame->SyntaxError)
		szData.append(" SyntaxError");
	if (pFrame->ContentError)
		szData.append(" ContentError");
	if (pFrame->ValidFrame)
		szData.append(" ValidFrame");

	string szHeaderCRC = Format("HeaderCRC: %03X", pFrame->HeaderCRC);

	return szCC + "\t" + szType + "\t" + szIdx + "\t" + szTimestamp + "\t" + szCycle + "\t" + szChannel + "\t" + szId + "\t" + szData + "\t" + szHeaderCRC;
}

string Util::ToString(fcNMVectorPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szCC = Format("CC%01d", pFrame->CC + 1);

	string szType("NMVector");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szCycle = Format("%03d", pFrame->CycleCount);

	string szData = Format("Len: %04d -",pFrame->NMVectorLength);

	int len = pFrame->NMVectorLength;
	for (int i = 0; i < len; i++)
	{
		szData.append(Format(" %02X", pFrame->NMVector[i]));
	}

	return szCC + "\t" + szType + "\t" + szTimestamp + "\t" + szCycle + "\t" + szData;
}

string Util::ToString(fcNotificationPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szType("Notification");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szData = Format("SequenceCounter: %d", pFrame->SequenceCounter);

	return szType + "\t" + szTimestamp + "\t" + szData;
}

string Util::ToString(fcTriggerExInfoPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szType("TriggerExInfo");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szData;

	szData.append(Format(" SequenceCount: %d", pFrame->SequenceCount));

	if (fcFlexCardPMC == Id || fcFlexCardPMCII == Id)
	{
		if (pFrame->Condition & fcTriggerPMCIn)
		{
			szData.append(Format(" Edge: %d", pFrame->Edge));
			szData.append(Format(" TriggerLine: %d", pFrame->TriggerLine));
		}
	}
	else if (fcFlexCardCycloneII == Id || fcFlexCardCycloneIISE == Id)
	{
		if (pFrame->Condition & fcTriggerIn)
			szData.append(Format(" Edge: %d", pFrame->Edge));

		// The PerformanceCounter is only available for FlexCard Windows driver.
		if ((pFrame->Condition & fcTriggerInOnSWPulse) || (pFrame->Condition & fcTriggerInOnSWTimer))
#ifdef WIN32
			szData.append(Format(" PerformanceCounter: %I64d", pFrame->PerformanceCounter));
#else
			szData.append(" PerformanceCounter: ERROR");
#endif
	}
	else
	{
		return "unknown FlexCard device Id";
	}

	return szType + "\t" + szTimestamp + "\t" + szData;
}

string Util::ToString(fcCANPacket* pFrame, fcFlexCardDeviceId Id)
{
	if (pFrame == NULL)
		return "";

	string szCC = Format("CC%01d", pFrame->CC+1);

	string szType("CANFrame");

	szType.append(Format("%s%s", (1 == pFrame->RemoteFrame) ? " Remote" : " ", (1 == pFrame->Direction) ? "Tx" : "Rx"));

	string szIdx = Format("Buf-Nr: %d", pFrame->BufferNumber);

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szId = Format("%d %s", pFrame->ID, (1 == pFrame->ExtendedId) ? "Ext" : "Std");

	string szData = Format("Len: %04d - ", pFrame->DLC);

	int len = pFrame->DLC;
	for (int i = 0; i < len; i++)
	{
		szData += Format(" %02X", pFrame->Data[i]);
	}

	if (pFrame->MessageLost)
		szData.append(" MessageLost");

	return szCC + "\t" + szType + "\t" + szIdx + "\t" + szTimestamp + "\t" + szId + "\t" + szData;
}

string Util::ToString(fcCANErrorPacket* pFrame, fcFlexCardDeviceId Id)
{
	string szCC = Format("CC%01d", pFrame->CC + 1);

	string szType("CANErrorPacket");

	string szTimestamp = Format("%f", (float) pFrame->TimeStamp * 0.000001);

	string szData;
	for (unsigned int i = 0; i < g_sizeCANError; i++)
	{
		if (g_CANError[i].FlagId == pFrame->Type)
		{
			szData.append(Format("%s", g_CANError[i].FlagText.c_str()));
			break;
		}
	}

	string szCounters = Format("RxErrCounter: %d TxErrCounter: %s", pFrame->ReceiveErrorCounter, pFrame->TransmitErrorCounter);

	string szState;
	for (unsigned int i = 0; i < g_sizeCANState; i++)
	{
		if (g_CANState[i].FlagId == pFrame->State)
		{
			szState.append(Format("CANCcState: %s", g_CANState[i].FlagText.c_str()));
			break;
		}
	}

	return szCC + "\t" + szType + "\t" + szTimestamp + "\t" + szData + "\t" + szCounters + "\t" + szState;
}
