#ifndef _TEL_STATISTIC_X_H
#define _TEL_STATISTIC_X_H

#define FAILURE_MODE_ok 0U
#define FAILURE_MODE_soWE 1U
#define FAILURE_MODE_noWE 2U
#define FAILURE_MODE_RfInterference 3U
#define SENSOR_STATE_UNKNOWN 0u
#define SENSOR_STATE_OK 1U
#define SENSOR_STATE_SUSPICIOUS 2U
#define SENSOR_STATE_DISTURBED 3U
#define SENSOR_STATE_MISSING 4U
#define SENSOR_POS_0 0U
#define SENSOR_POS_1 1U
#define SENSOR_POS_2 2U
#define SENSOR_POS_3 3U
#define cTableSize 16
#define AVG_PRESS_ENABLED

void BuildTelStatistics(uint32 ulTelID, uint8 ucTelP, uint8 ucTelT, uint32 ulTime, boolean bSensorDefect);
void InitTelStatInfo(void);
void UpdateTelStatInfo(uint16 ushCurrentVehSpeed, uint8 ucMinPalSpeed);
uint8 ucGetFailureState(void);
void ClearTelRxStatistics(void);
void ClearTelStatisticsStruct(uint8 ucPosMask);
void ZomChangedWuInfoDcm(uint16 ushWaState);
uint16 ushGetTelMuteTime(uint8 ucPos);
uint8 ucGetSensorState(uint8 ucPos);
uint8 ucGetLastReceivedPress(uint32 ulTelID);
uint8 ucGetLastReceivedTemp(uint32 ulTelID);
uint8 ucTelStatGetIDPosInTable(uint32 ulTelID);
void UpdateSensorStateAtClamp15Off(void);
uint32 ulTelStatGetLastRxTime(uint32 ulTelID);
uint8 ucTelStatGetLastRxBlocs(uint32 ulTelID);
void ResetFailureState(void);
void InitTelStatInfoAtModeChange(void);
boolean bGetSensorStateMissing(uint8 ucColOfID);
void ResetFailureStateSensorMissing(uint8 ucPos);
void ResetFailureStateSensorDisturbed(void);
boolean bCheckHistIDReception1(void);

#ifdef AVG_PRESS_ENABLED
void  ClearAvgPress4FD(void);
uint8 ucGetAvgCntr4FD(uint32 ulTelID);
uint8 ucGetAvgPress4FD(uint32 ulTelID);
#endif

extern uint16 ushGetRxBlocksSum(uint8 ucPos);
extern void PutRxBlocksSum(uint16 x, uint8 idx);
extern uint16 ushGetMissedBlocksSum(uint8 ucPos);
extern void PutMissedBlocksSum(uint16 x, uint8 idx);

#endif
