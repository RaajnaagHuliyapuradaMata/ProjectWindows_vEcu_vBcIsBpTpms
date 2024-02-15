/************************************************************************************************************
 * (c) HuF Electronics GmbH      Abteilung ENTS4     2015
 ************************************************************************************************************/

/*********************************************************************************************************//**
 * \file Trace.h
 * \brief Management CAN-messages used for debugging purpuse
 *
 *------------------------------------------------------------------------------------------------------------
 * Global Description
 * 
 *
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 * Modul Description
 * 
 *
 * Purpose:
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 */

#ifndef _trace_H /* [0] */
#define _trace_H

/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "Platform_Types.h"
#include "Compiler_Cfg.h"

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
#define MAX_SIZE_DISP_BUF 500U
#define MAX_MSG_SIZE 8U

typedef uint8 DT_HufDisplayByte;

typedef struct
{
  DT_HufDisplayByte Byte0;
  DT_HufDisplayByte Byte1;
  DT_HufDisplayByte Byte2;
  DT_HufDisplayByte Byte3;
  DT_HufDisplayByte Byte4;
  DT_HufDisplayByte Byte5;
  DT_HufDisplayByte Byte6;
  DT_HufDisplayByte Byte7;
} DT_HufDisplay;




typedef struct   /* Debug parameterset*/
{
  uint16 ushBtrZustand;
  uint16 ushFZZustand;
  uint8 ucVspeed;
  uint8 ucRevGrCnt;
  uint8 ucAirTemp;
  uint8 ucPAmbient;
  uint16 ushEcuTimeStanby;
  uint16 ushEcuMissedBlocksCntID0;
  uint16 ushEcuMissedBlocksCntID1;
  uint16 ushEcuMissedBlocksCntID2;
  uint16 ushEcuMissedBlocksCntID3;
  uint16 ushEcuRxBlocksCntID0;
  uint16 ushEcuRxBlocksCntID1;
  uint16 ushEcuRxBlocksCntID2;
  uint16 ushEcuRxBlocksCntID3;
  uint8 ucEcuStopCnt;
  uint16 ushEcuOdometer;
	uint8 ucAntenaOffset;
	uint8 ucBaseNoiseLevel;
	uint8 ucStoerPegel;
	uint8 ucStoerSender; 
	uint8 ucFolgeausfallCtr0;
	uint8 ucFolgeausfallCtr1;
	uint8 ucFolgeausfallCtr2;
	uint8 ucFolgeausfallCtr3;
	uint16 ushZOTimeoutCtr;
	uint16 ushAbsResetFlag;
	uint8 ucAbsOverflowCntFL;
	uint8 ucAbsOverflowCntFR;
	uint8 ucAbsOverflowCntRL;
	uint8 ucAbsOverflowCntRR;
	uint32 aulHistoryID0;
	uint32 aulHistoryID1;
	uint32 aulHistoryID2;
	uint32 aulHistoryID3;
	uint8 aucHistoryWP0;
	uint8 aucHistoryWP1;
	uint8 aucHistoryWP2;
	uint8 aucHistoryWP3;
  uint16 ushUsedHistoryWP;
	uint8 ucWarnVector0;
	uint8 ucWarnVector1;
	uint8 ucWarnVector2;
	uint8 ucWarnVector3;
	uint16 ushWarnState;
  uint32 ulZomID0;
	uint32 ulZomID1;
	uint32 ulZomID2;
	uint32 ulZomID3;
	uint32 ulZomID4;
	uint32 ulZomID5;
	uint32 ulZomID6;
	uint32 ulZomID7;
	uint32 ulZomID8;
	uint32 ulZomID9;
	uint32 ulZomID10;
	uint32 ulZomID11;
	uint32 ulZomID12;
	uint32 ulZomID13;
	uint32 ulZomID14;
	uint32 ulZomID15;
  uint8 ucEcuEspDelay;
  uint8 ucEcuALMethod;
  /*
	uint8 ucZomStatus0;
	uint8 ucZomStatus1;
	uint8 ucZomStatus2;
	uint8 ucZomStatus3;
	uint8 ucZomStatus4;
	uint8 ucZomStatus5;
	uint8 ucZomStatus6;
	uint8 ucZomStatus7;
	uint8 ucZomStatus8;
	uint8 ucZomStatus9;
	uint8 ucZomStatus10;
	uint8 ucZomStatus11;
	uint8 ucZomStatus12;
	uint8 ucZomStatus13;
	uint8 ucZomStatus14;
	uint8 ucZomStatus15;*/
  uint8 aucZomStatus[16];
  /*
	uint8 ucZomProbeCnt0;
	uint8 ucZomProbeCnt1;
	uint8 ucZomProbeCnt2;
	uint8 ucZomProbeCnt3;
	uint8 ucZomProbeCnt4;
	uint8 ucZomProbeCnt5;
	uint8 ucZomProbeCnt6;
	uint8 ucZomProbeCnt7;
	uint8 ucZomProbeCnt8;
	uint8 ucZomProbeCnt9;
	uint8 ucZomProbeCnt10;
	uint8 ucZomProbeCnt11;
	uint8 ucZomProbeCnt12;
	uint8 ucZomProbeCnt13;
	uint8 ucZomProbeCnt14;
	uint8 ucZomProbeCnt15;
  */
  uint8 aucZomToothTelCtLearnBit[16];
	uint8 aucZomToothTelCtCorr[16];
	uint8 aucZomToothTelCtrNoCorr[16];
  uint8 aucZomStatTelCounter[16]; //
  uint8 aucZomToothTelCtNoLearnMode[16];
  uint16 aushZomAbsSumFL[16];
	uint16 aushZomAbsSumFR[16];
	uint16 aushZomAbsSumRL[16];
	uint16 aushZomAbsSumRR[16];
  uint8 ucEcuSensorFailureState;
  uint8 ucEcuFdPfillFront; // P fill front used for filling detection
  uint8 ucEcuFdPfillRear; // P fill rear used for filling detection
  uint8 ucEcuFdTfill; // Tfill used for filling detection
  uint8 ucEcuWaPminF; //lowest possible value for reference pressure p_ref_front
  uint8 ucEcuWaPminR; //lowest possible value for reference pressure p_ref_rear
  uint8 ucEcuWaHoldOff;
  uint8 ucEcuFdStatus;
  uint8 ucEcuFdAbortReason;
  uint8 ucEcuFdCalRequest;
  uint8 ucEcuFdCalNotAckState;
  uint8 ucEcuFdPlausibilityFailure; 
  uint16 ushEcuTWLevel1Time; //Display Time of first warning level
  uint8 ucEcuTWOverheatWarning; //Status of overheat warning
  uint16 ushEcuTWOverheatCount; //Counter for overheat warning
  uint8 ucEcuTWCombinedSpeed; //Combined vehicle speed for temperature warning
  uint8 ucEcuTWFilteredSpeed; //Filtered vehicle speed for temperature warning
  uint32 ulEcuFdLastCalMileage;
  uint16 ushEcuTimeSoft;
  uint16 ushEcuTimeHard;
  uint16 ushECUTimeParking;
  uint8 ucEcuAutoLocateStatus;
  uint8 ucEcuAutoLocateMode;
  uint8 ucEcuAutoLearnStatus;
}debugEnvDataStruct;



typedef struct /* parameterset of walloc */
{
	uint32 ulTimeStamp;
	uint8 ucRecEvent;
	uint8 ucTelType;
	uint8 ucIDTelCnt;
	uint32 ulID;
	uint8 ucIDPosInZom;
	uint8 ucPAL;
	uint8 ucP;
	uint8 ucT;
  uint8 ucPcompCurrID;
  uint8 ucTrefCurrID;
  uint8 ucPrefCurrID;
	uint8 ucAvgRssi;
  uint8 ECU_C_RecBlocks; //recovered blocks
	uint8 ucTelByte00;
	uint8 ucTelByte01;
	uint8 ucTelByte02;
	uint8 ucTelByte03;
	uint8 ucTelByte04;
	uint8 ucTelByte05;
	uint8 ucTelByte06;
	uint8 ucTelByte07;
	uint8 ucTelByte08;
	uint8 ucTelByte09;
	uint8 ucTelByte10;
	uint8 ucTelByte11;
	uint8 ucTelByte12;
	uint8 ucTelByte13;
	uint8 ucTelByte14;
	uint8 ucTelByte15;
  uint8 ucPref; // Calibrated pressure
	uint8 ucTref; // Calibrated temperature
  uint16 ushPref_WTPmin; // pmin
	uint16 ushPref_WTDHW; // fast  warning
	uint16 ushPref_WTHW; // hard warning
	uint16 ushPref_WTWW; // soft warning
	uint16 ushTref_WTHW;  // hard warning, ECE??
	uint16 ushTref_WTWW; // soft warning
}debugTelStruct;

typedef struct /* parameterset from walloc */
{
  //uint32 ulID;
  uint8 ucZomToothTelCtLearnBit;
	uint8 ucZomToothTelCtCorr;
	uint8 ucZomToothTelCtrNoCorr;
  uint8 ucZomStatTelCounter; //
  uint8 ucZomToothTelCtNoLearnMode;
  uint8 ucZomStatus; 
	uint16 ushZomAbsSumFL;
	uint16 ushZomAbsSumFR;
	uint16 ushZomAbsSumRL;
	uint16 ushZomAbsSumRR;
	uint16 ushZomAbsLinFL;
	uint16 ushZomAbsLinFR;
	uint16 ushZomAbsLinRL;
	uint16 ushZomAbsLinRR;
	uint8 ucZomAbsCompFL;
	uint8 ucZomAbsCompFR;
	uint8 ucZomAbsCompRL;
	uint8 ucZomAbsCompRR; 
}debutTelWallocStruct;

typedef struct /* parameterset at specific wheel position */
{
  uint32 ulID;
  uint8 ucP;
  uint8 ucT;
  uint8 ucPref;
  uint8 ucTref;
  uint8 ucWT_Pmin;
  uint8 ucWT_DHW;
  uint8 ucWT_HW;
  uint8 ucWT_WW;
  uint8 ucWT_Clear;
  uint8 ucWheelStat;
  uint16 ushTimeMute;
  uint8 ucSensorState;
  uint8 ucEcuFdNumBlocks;
  uint8 ucEcuFdPCompare;
  uint8 ucEcuRFRSSI;
  uint8 ucEcuLoBatCnt;
}debugTelStructPos;


static uint16   ushReadCounter=0; // position of the read vector
static uint16   ushWriteCounter=0; // position of the write vector
static DT_HufDisplay tHufDisplayMsgBuf[MAX_SIZE_DISP_BUF]; // Queue containing debug messages to be sent


/***********************************************************************************************************
 *                                 prototype (local fun0ctions - public)
 ***********************************************************************************************************/
void tracerInit(void);
void GetDebugVar2beLogged(void);
void TracePutEnvDataStr2Queue(debugEnvDataStruct* tDebugEnvDataStruct);
void TracePutTelStr2Queue(debugTelStruct* tDebugTelStruct);
void TracePutTelWallocData2Queue(debutTelWallocStruct* tDebutTelWallocStruct);
void TracePutTelStrPosFL2Queue(debugTelStructPos* tDebugTelStruct);
void TracePutTelStrPosFR2Queue(debugTelStructPos* tDebugTelStruct);
void TracePutTelStrPosRL2Queue(debugTelStructPos* tDebugTelStruct);
void TracePutTelStrPosRR2Queue(debugTelStructPos* tDebugTelStruct);
void static putData2Queue(DT_HufDisplay tHufDisplay);
uint8 ucTraceGetDataFromQueue(DT_HufDisplay* tHufDisplay);


#endif /* _trace_H */