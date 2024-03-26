#include "Std_Types.hpp"

#include "Trace.h"
#include "HMI_handlerX.h"
#include "state_bzX.h"
#include "state_fZZX.h"
#include "abs_linX.h"
#include "wallocX.h"
#include "USWarnX.h"
#include "SensorLoBat.h"
#include "tel_statisticX.h"
#include "filling_detectionX.h"
#include "filling_detection.h"
#include "state_fdX.h"
#include "internal_clockX.h"
#include "Rte_CtApHufTPMSmgr.h"

extern VAR(uint32, OHDS_VAR_NOINIT) OHDSCanSlave_OperatingHours_Low_t2s;
extern VAR(uint32, OHDS_VAR_NOINIT) OHDSCanSlave_OperatingHours_t2s_us;
extern VAR(uint8,  OHDS_VAR_NOINIT) OHDSCanSlave_StatusByte_t2s;
extern VAR(uint8,  OHDS_VAR_NOINIT) OHDSCanSlave_OperatingHours_High_t2s;

extern DT_tEnvData tEnvDataToSend;
extern uint8       ucEspDelayTime;
extern uint8       ucRvsGearCnt;
extern uint8       ucNoiseLevel;

debugTelStruct     tDebugTelStruct;
debugEnvDataStruct tDebugEnvDataStruct;
debugTelStructPos  tdebugTelStructPosFL;
debugTelStructPos  tdebugTelStructPosFR;
debugTelStructPos  tdebugTelStructPosRL;
debugTelStructPos  tdebugTelStructPosRR;

static DT_HufDisplay tHufDisplayMsgBuf[MAX_SIZE_DISP_BUF];
static uint16        ushReadCounter  = 0;
static uint16        ushWriteCounter = 0;

extern uint8 ui8GetAtaErrRecNVM (void);
extern uint8 ui8GetErrorCnt     (void);
static void  putData2Queue      (DT_HufDisplay tHufDisplay);

void tracerInit(void){
   uint16 i;
   ushReadCounter = 0;
   ushWriteCounter = 0;

   for(i=0;i<sizeof(debugEnvDataStruct);i++){
      *((uint8*)&tDebugEnvDataStruct + i) = 0;
   }

   for(i=0;i<sizeof(tDebugTelStruct);i++){
      *((uint8*)&tDebugTelStruct + i) = 0;
   }

  for(i=0;i<sizeof(tdebugTelStructPosFL);i++){
      *((uint8*)&tdebugTelStructPosFL + i) = 0;
    *((uint8*)&tdebugTelStructPosFR + i) = 0;
    *((uint8*)&tdebugTelStructPosRL + i) = 0;
    *((uint8*)&tdebugTelStructPosRR + i) = 0;
   }

}

void TracePutTelWallocData2Queue(debutTelWallocStruct* tDebugStruct){
   DT_HufDisplay tHufDisplay;

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 20;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucZomAbsCompFL;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugStruct->ucZomToothTelCtLearnBit);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugStruct->ucZomStatTelCounter);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsSumFL>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ushZomAbsSumFL;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsSumFR>>8);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ushZomAbsSumFR;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 21;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucZomAbsCompFR;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugStruct->ucZomToothTelCtCorr);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugStruct->ucZomToothTelCtrNoCorr);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsSumRL>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsSumRL);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsSumRR>>8);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ushZomAbsSumRR;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 22;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucZomAbsCompRL;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugStruct->ucZomToothTelCtNoLearnMode);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucZomStatus;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsLinFL>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ushZomAbsLinFL;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsLinFR>>8);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ushZomAbsLinFR;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 23;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucZomAbsCompRR;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsLinRL>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ushZomAbsLinRL;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugStruct->ushZomAbsLinRR>>8);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ushZomAbsLinRR;
   putData2Queue(tHufDisplay);

   }

void TracePutTelStr2Queue(debugTelStruct* tDebugStruct){

   DT_HufDisplay tHufDisplay;

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 11;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ECU_C_RecBlocks;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucPAL;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugStruct->ulID>>24);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugStruct->ulID>>16);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugStruct->ulID>>8);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) (tDebugStruct->ulID>>0);
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 13;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucPcompCurrID;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucTelType;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucTelByte08;
    tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTelByte09;
    tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucAvgRssi;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucP;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucT;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 14;
  tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucTrefCurrID;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucTelByte00;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucTelByte01;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTelByte02;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucTelByte03;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucTelByte04;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucTelByte05;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 15;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucPrefCurrID;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucTelByte06;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucTelByte07;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTelByte08;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucTelByte09;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucTelByte10;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucTelByte11;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 16;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) ( (tDebugStruct->ucTelByte09 & 0x3C)>>2);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucTelByte12;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucTelByte13;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTelByte14;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucTelByte15;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) 0xFF;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 10;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucIDPosInZom;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugStruct->ulTimeStamp>>24);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugStruct->ulTimeStamp>>16);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugStruct->ulTimeStamp>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugStruct->ulTimeStamp>>0);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) (tDebugStruct->ucRecEvent);
   putData2Queue(tHufDisplay);

}

void TracePutEnvDataStr2Queue(debugEnvDataStruct* tDebugEnvDataStruct){

   DT_HufDisplay tHufDisplay;

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 17;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushECUTimeParking>>8);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushECUTimeParking;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucAntenaOffset;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) ui8GetAtaErrRecNVM();
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucStoerPegel;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) ui8GetErrorCnt();
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuALMethod;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 18;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuTimeStanby>>8);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuTimeStanby;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuSensorFailureState;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushFZZustand>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushFZZustand;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushZOTimeoutCtr>>8);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushZOTimeoutCtr;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 19;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuStopCnt;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucRevGrCnt;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushBtrZustand>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushBtrZustand;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucPAmbient;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucVspeed;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucAirTemp;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 25;
  tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuAutoLocateStatus;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushAbsResetFlag>>8);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushAbsResetFlag;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucAbsOverflowCntFL;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucAbsOverflowCntFR;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucAbsOverflowCntRL;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucAbsOverflowCntRR;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 29;
  tHufDisplay.Byte1 = (DT_HufDisplayByte) OHDSCanSlave_OperatingHours_High_t2s;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (OHDSCanSlave_OperatingHours_Low_t2s>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (OHDSCanSlave_OperatingHours_Low_t2s>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (OHDSCanSlave_OperatingHours_Low_t2s>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (OHDSCanSlave_OperatingHours_Low_t2s>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) OHDSCanSlave_StatusByte_t2s;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) ((OHDSCanSlave_OperatingHours_t2s_us & 0x03FC)>>2);
    putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 30;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[0];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID0>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID0>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID0>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID0>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[0];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[0];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 31;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[1];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID1>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID1>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID1>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID1>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[1];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[1];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 32;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[2];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID2>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID2>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID2>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID2>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[2];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[2];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 33;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[3];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID3>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID3>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID3>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID3>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[3];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[3];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 34;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[4];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID4>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID4>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID4>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID4>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[4];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[4];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 35;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[5];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID5>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID5>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID5>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID5>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[5];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[5];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 36;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[6];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID6>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID6>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID6>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID6>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[6];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[6];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 37;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[7];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID7>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID7>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID7>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID7>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[7];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[7];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 38;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[8];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID8>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID8>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID8>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID8>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[8];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[8];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 39;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[9];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID9>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID9>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID9>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID9>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[9];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[9];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 40;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[10];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID10>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID10>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID10>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID10>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[10];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[10];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 41;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[11];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID11>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID11>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID11>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID11>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[11];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[11];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 42;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[12];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID12>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID12>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID12>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID12>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[12];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[12];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 43;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[13];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID13>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID13>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID13>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID13>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[13];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[13];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 44;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[14];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID14>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID14>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID14>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID14>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[14];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[14];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 45;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtLearnBit[15];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID15>>24);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID15>>16);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID15>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulZomID15>>0);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtCorr[15];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatus[15];
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 50;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuMissedBlocksCntID0>>8);
  tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuMissedBlocksCntID0;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID0>>24);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID0>>16);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID0>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID0>>0);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucHistoryWP0;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 51;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuMissedBlocksCntID1>>8);
  tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuMissedBlocksCntID1;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID1>>24);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID1>>16);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID1>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID1>>0);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucHistoryWP1;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 52;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuMissedBlocksCntID2>>8);
  tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuMissedBlocksCntID2;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID2>>24);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID2>>16);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID2>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID2>>0);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucHistoryWP2;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 53;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuMissedBlocksCntID3>>8);
  tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuMissedBlocksCntID3;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID3>>24);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID3>>16);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID3>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugEnvDataStruct->aulHistoryID3>>0);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucHistoryWP3;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 54;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuRxBlocksCntID0>>8);
  tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuRxBlocksCntID0;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuRxBlocksCntID1>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuRxBlocksCntID1;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuRxBlocksCntID2>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuRxBlocksCntID2;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuAutoLearnStatus;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 55;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuRxBlocksCntID3>>8);
  tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuRxBlocksCntID3;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuAutoLocateMode;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulEcuFdLastCalMileage>>24);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulEcuFdLastCalMileage>>16);
  tHufDisplay.Byte6 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulEcuFdLastCalMileage>>8);
  tHufDisplay.Byte7 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ulEcuFdLastCalMileage>>0);
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 56;
  tHufDisplay.Byte1 = (DT_HufDisplayByte) (ucGetZomLqi(0));
  tHufDisplay.Byte2 = (DT_HufDisplayByte) (ucGetZomLqi(1));
  tHufDisplay.Byte3 = (DT_HufDisplayByte) (ucGetZomLqi(2));
  tHufDisplay.Byte4 = (DT_HufDisplayByte) (ucGetZomLqi(3));
  tHufDisplay.Byte5 = (DT_HufDisplayByte) (ucGetZomLqi(4));
  tHufDisplay.Byte6 = (DT_HufDisplayByte) (ucGetZomLqi(5));
  tHufDisplay.Byte7 = (DT_HufDisplayByte) (ucGetZomLqi(6));
  putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 57;
  tHufDisplay.Byte1 = (DT_HufDisplayByte) (ucGetZomLqi(7));
  tHufDisplay.Byte2 = (DT_HufDisplayByte) (ucGetZomLqi(8));
  tHufDisplay.Byte3 = (DT_HufDisplayByte) (ucGetZomLqi(9));
  tHufDisplay.Byte4 = (DT_HufDisplayByte) (ucGetZomLqi(10));
  tHufDisplay.Byte5 = (DT_HufDisplayByte) (ucGetZomLqi(11));
  tHufDisplay.Byte6 = (DT_HufDisplayByte) (ucGetZomLqi(12));
  tHufDisplay.Byte7 = (DT_HufDisplayByte) (ucGetZomLqi(13));
  putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 58;
  tHufDisplay.Byte1 = (DT_HufDisplayByte) (ucGetZomLqi(14));
  tHufDisplay.Byte2 = (DT_HufDisplayByte) (ucGetZomLqi(15));
  tHufDisplay.Byte3 = (DT_HufDisplayByte) (GETucCnt4DP_FILL_DFL());
  tHufDisplay.Byte4 = (DT_HufDisplayByte) (GETucCnt4DP_FILL_IFL());
  tHufDisplay.Byte5 = (DT_HufDisplayByte) 0xFF;
  tHufDisplay.Byte6 = (DT_HufDisplayByte) 0xFF;
  tHufDisplay.Byte7 = (DT_HufDisplayByte) 0xFF;
  putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 60;
  tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushWarnState;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (GETushFDtimeout()>>8);
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (GETushFDtimeout()>>0);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushUsedHistoryWP;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushUsedHistoryWP>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuFdCalRequest;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuFdCalNotAckState;
   putData2Queue(tHufDisplay);

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 61;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuWaPminF;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuWaPminR;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuTimeSoft>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuTimeSoft;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuTimeHard>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuTimeHard;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuWaHoldOff;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 65;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ucEcuFdStatus);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ucEcuFdAbortReason);
  tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ucEcuFdPlausibilityFailure);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuEspDelay;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuFdPfillFront;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuFdPfillRear;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuFdTfill;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 66;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuTWLevel1Time>>8);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuTWLevel1Time);
  tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ucEcuTWOverheatWarning) > 0 ? 1 : 0;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (tDebugEnvDataStruct->ushEcuTWOverheatCount>>8);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->ushEcuTWOverheatCount;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuTWCombinedSpeed;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->ucEcuTWFilteredSpeed;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 67;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (ushGetTelMuteTime(0)>>8);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (ushGetTelMuteTime(0));
  tHufDisplay.Byte3 = (DT_HufDisplayByte) (ushGetTelMuteTime(1)>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) (ushGetTelMuteTime(1));
   tHufDisplay.Byte5 = (DT_HufDisplayByte) (ushGetTelMuteTime(2)>>8);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) (ushGetTelMuteTime(2));
   tHufDisplay.Byte7 = (DT_HufDisplayByte) (GETtSensorBatInfOfRam(0).ui8Count);
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 68;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (ushGetTelMuteTime(3)>>8);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (ushGetTelMuteTime(3));
  tHufDisplay.Byte3 = (DT_HufDisplayByte) ucGetSensorState(0);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) ucGetSensorState(1);
   tHufDisplay.Byte5 = (DT_HufDisplayByte) ucGetSensorState(2);
   tHufDisplay.Byte6 = (DT_HufDisplayByte) ucGetSensorState(3);
   tHufDisplay.Byte7 = (DT_HufDisplayByte) (GETtSensorBatInfOfRam(1).ui8Count);
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 69;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) (GETtSensorBatInfOfRam(2).ui8Count);
   tHufDisplay.Byte2 = (DT_HufDisplayByte) (GETtSensorBatInfOfRam(3).ui8Count);
  tHufDisplay.Byte3 = (DT_HufDisplayByte) ucGetAvgCntr4FD(ulGetID(0));
   tHufDisplay.Byte4 = (DT_HufDisplayByte) ucGetAvgCntr4FD(ulGetID(1));
   tHufDisplay.Byte5 = (DT_HufDisplayByte) ucGetAvgCntr4FD(ulGetID(2));
   tHufDisplay.Byte6 = (DT_HufDisplayByte) ucGetAvgCntr4FD(ulGetID(3));
   tHufDisplay.Byte7 = (DT_HufDisplayByte) 0xFF;
   putData2Queue(tHufDisplay);

      tHufDisplay.Byte0 = (DT_HufDisplayByte) 110;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[0];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[0];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[0];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[0];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[0];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[0];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[0];
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 111;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[1];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[1];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[1];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[1];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[1];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[1];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[1];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 112;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[2];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[2];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[2];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[2];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[2];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[2];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[2];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 113;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[3];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[3];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[3];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[3];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[3];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[3];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[3];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 114;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[4];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[4];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[4];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[4];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[4];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[4];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[4];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 115;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[5];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[5];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[5];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[5];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[5];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[5];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[5];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 116;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[6];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[6];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[6];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[6];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[6];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[6];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[6];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 117;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[7];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[7];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[7];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[7];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[7];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[7];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[7];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 118;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[8];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[8];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[8];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[8];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[8];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[8];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[8];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 119;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[9];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[9];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[9];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[9];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[9];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[9];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[9];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 120;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[10];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[10];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[10];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[10];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[10];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[10];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[10];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 121;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[11];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[11];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[11];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[11];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[11];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[11];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[11];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 122;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[12];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[12];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[12];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[12];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[12];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[12];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[12];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 123;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[13];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[13];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[13];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[13];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[13];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[13];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[13];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 124;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[14];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[14];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[14];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[14];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[14];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[14];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[14];
   putData2Queue(tHufDisplay);

    tHufDisplay.Byte0 = (DT_HufDisplayByte) 125;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtrNoCorr[15];
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomToothTelCtNoLearnMode[15];
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugEnvDataStruct->aucZomStatTelCounter[15];
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFL[15];
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumFR[15];
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRL[15];
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugEnvDataStruct->aushZomAbsSumRR[15];
   putData2Queue(tHufDisplay);

}

void TracePutTelStrPosFL2Queue(debugTelStructPos* tDebugStruct){
  DT_HufDisplay tHufDisplay;

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 70;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucP;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucT;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucPref;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTref;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucWT_Pmin;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucWT_DHW;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucWT_HW;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 71;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucWT_WW;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucWheelStat;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugStruct->ushTimeMute>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ushTimeMute;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdNumBlocks;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdPCompare;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucSensorState;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 72;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucEcuRFRSSI;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucEcuLoBatCnt;
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucWT_Clear;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) 0xFF;
   putData2Queue(tHufDisplay);

}

void TracePutTelStrPosFR2Queue(debugTelStructPos* tDebugStruct){
  DT_HufDisplay tHufDisplay;

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 80;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucP;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucT;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucPref;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTref;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucWT_Pmin;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucWT_DHW;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucWT_HW;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 81;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucWT_WW;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucWheelStat;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugStruct->ushTimeMute>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ushTimeMute;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdNumBlocks;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdPCompare;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucSensorState;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 82;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucEcuRFRSSI;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucEcuLoBatCnt;
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucWT_Clear;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) 0xFF;
   putData2Queue(tHufDisplay);

}

void TracePutTelStrPosRL2Queue(debugTelStructPos* tDebugStruct){
  DT_HufDisplay tHufDisplay;

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 90;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucP;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucT;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucPref;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTref;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucWT_Pmin;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucWT_DHW;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucWT_HW;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 91;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucWT_WW;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucWheelStat;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugStruct->ushTimeMute>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ushTimeMute;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdNumBlocks;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdPCompare;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucSensorState;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 92;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucEcuRFRSSI;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucEcuLoBatCnt;
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucWT_Clear;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) 0xFF;
   putData2Queue(tHufDisplay);

}

void TracePutTelStrPosRR2Queue(debugTelStructPos* tDebugStruct){
  DT_HufDisplay tHufDisplay;

   tHufDisplay.Byte0 = (DT_HufDisplayByte) 100;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucP;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucT;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucPref;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ucTref;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucWT_Pmin;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucWT_DHW;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucWT_HW;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 101;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucWT_WW;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucWheelStat;
   tHufDisplay.Byte3 = (DT_HufDisplayByte) (tDebugStruct->ushTimeMute>>8);
   tHufDisplay.Byte4 = (DT_HufDisplayByte) tDebugStruct->ushTimeMute;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdNumBlocks;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) tDebugStruct->ucEcuFdPCompare;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) tDebugStruct->ucSensorState;
   putData2Queue(tHufDisplay);

  tHufDisplay.Byte0 = (DT_HufDisplayByte) 102;
   tHufDisplay.Byte1 = (DT_HufDisplayByte) tDebugStruct->ucEcuRFRSSI;
   tHufDisplay.Byte2 = (DT_HufDisplayByte) tDebugStruct->ucEcuLoBatCnt;
  tHufDisplay.Byte3 = (DT_HufDisplayByte) tDebugStruct->ucWT_Clear;
   tHufDisplay.Byte4 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte5 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte6 = (DT_HufDisplayByte) 0xFF;
   tHufDisplay.Byte7 = (DT_HufDisplayByte) 0xFF;
   putData2Queue(tHufDisplay);
}

void static putData2Queue(DT_HufDisplay tHufDisplay){

   tHufDisplayMsgBuf[ushWriteCounter] = tHufDisplay;
   ushWriteCounter++;
    if(ushWriteCounter == MAX_SIZE_DISP_BUF)
      ushWriteCounter = 0;
}

uint8 ucTraceGetDataFromQueue(DT_HufDisplay* tHufDisplay){
   uint8 ucRet;
    ucRet = 0;

   if(ushWriteCounter != ushReadCounter){
      *tHufDisplay = tHufDisplayMsgBuf[ushReadCounter];
      ushReadCounter++;
    if(ushReadCounter == MAX_SIZE_DISP_BUF)
      ushReadCounter = 0;

   ucRet=1;
   }

   return ucRet;
}

void GetDebugVar2beLogged(){
      uint8 i;
    uint8 ucTemp1, ucTemp2;

      tDebugEnvDataStruct.ushBtrZustand = ushGetBetriebszustandBZ(0xFFFF);
      tDebugEnvDataStruct.ushFZZustand = ushGetFahrzeugzustandFZZ(cFZZ_ALLE_BITS);
     if(tEnvDataToSend.ushVehSpeed<0xFF){
      tDebugEnvDataStruct.ucVspeed = tEnvDataToSend.ushVehSpeed;
    }
    else{
      tDebugEnvDataStruct.ucVspeed = 0xFF;
    }

      tDebugEnvDataStruct.ucStoerPegel = ucNoiseLevel;
    tDebugEnvDataStruct.ucAntenaOffset = 0;
       tDebugEnvDataStruct.ucAirTemp = tEnvDataToSend.ucTempOut;
      tDebugEnvDataStruct.ucAbsOverflowCntFL = ucGetAbsOverflowCtrFL();
      tDebugEnvDataStruct.ucAbsOverflowCntFR = ucGetAbsOverflowCtrFR();
      tDebugEnvDataStruct.ucAbsOverflowCntRL = ucGetAbsOverflowCtrRL();
      tDebugEnvDataStruct.ucAbsOverflowCntRR = ucGetAbsOverflowCtrRR();

      Rte_Call_PP_GetWarningVectors_OP_GETushWarnstatus1WN(&tDebugEnvDataStruct.ushWarnState);
    Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)ucGetWPOfCol(0), &tDebugEnvDataStruct.ucWarnVector0);
      Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)ucGetWPOfCol(1), &tDebugEnvDataStruct.ucWarnVector1);
      Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)ucGetWPOfCol(2), &tDebugEnvDataStruct.ucWarnVector2);
      Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)ucGetWPOfCol(3), &tDebugEnvDataStruct.ucWarnVector3);
      tDebugEnvDataStruct.ushEcuTimeHard = ui16GetHarTimerInSec();
     tDebugEnvDataStruct.ushEcuTimeSoft = ui16GetSofTimerInSec();
      tDebugEnvDataStruct.ucEcuFdPfillFront = GETucPfillFront();
    tDebugEnvDataStruct.ucEcuFdPfillRear = GETucPfillRear();
      tDebugEnvDataStruct.ucEcuFdTfill = (uint8) GETscTfill();

      tDebugEnvDataStruct.ushEcuTimeStanby = ushGetCurrentECUStanbyTime();
    tDebugEnvDataStruct.ushECUTimeParking = ushGetCurrentECUParkingTime();
      tDebugEnvDataStruct.ucRevGrCnt = ucRvsGearCnt;
    tDebugEnvDataStruct.ushZOTimeoutCtr = ushGetDriveTimeInSec();
    tDebugEnvDataStruct.ucPAmbient = tEnvDataToSend.ucPressOut;
    tDebugEnvDataStruct.ucEcuStopCnt = ucGetEcuStopCntr();
    tDebugEnvDataStruct.ushEcuOdometer = 0;
     tDebugEnvDataStruct.ulEcuFdLastCalMileage = GETulLastCalMileage();
    tDebugEnvDataStruct.ucEcuAutoLocateStatus = ui8GetALState();

    tDebugEnvDataStruct.ushEcuMissedBlocksCntID0 =  ushGetMissedBlocksSum(0);
    tDebugEnvDataStruct.ushEcuMissedBlocksCntID1 =  ushGetMissedBlocksSum(1);
    tDebugEnvDataStruct.ushEcuMissedBlocksCntID2 =  ushGetMissedBlocksSum(2);
    tDebugEnvDataStruct.ushEcuMissedBlocksCntID3 =  ushGetMissedBlocksSum(3);

    tDebugEnvDataStruct.ushEcuRxBlocksCntID0 = ushGetRxBlocksSum(0);
    tDebugEnvDataStruct.ushEcuRxBlocksCntID1 = ushGetRxBlocksSum(1);
    tDebugEnvDataStruct.ushEcuRxBlocksCntID2 = ushGetRxBlocksSum(2);
    tDebugEnvDataStruct.ushEcuRxBlocksCntID3 = ushGetRxBlocksSum(3);

    tDebugEnvDataStruct.ucEcuFdStatus = Get_FD_STATUS();
    tDebugEnvDataStruct.ucEcuFdAbortReason =  Get_FD_ABORT_REASON();
    tDebugEnvDataStruct.ucEcuFdPlausibilityFailure = Get_FD_PLAUSIBILITY_FAILURE();
    tDebugEnvDataStruct.ucEcuFdCalRequest = GETucCalRequestStateOfRam();
    tDebugEnvDataStruct.ucEcuFdCalNotAckState = GETucCalNotAckStateOfRam();
    tDebugEnvDataStruct.ucEcuWaPminF = GETucPcalMinVaRelativCodOfRam();
     tDebugEnvDataStruct.ucEcuWaPminR = GETucPcalMinHaRelativCodOfRam();
     tDebugEnvDataStruct.ucEcuWaHoldOff = bHoldOffWarningEnabled();

    tDebugEnvDataStruct.ushEcuTWLevel1Time = ui16GetSpeedCtInSec();
     tDebugEnvDataStruct.ucEcuTWOverheatWarning = ui8OvrHeatWrnIsActive();
     tDebugEnvDataStruct.ushEcuTWOverheatCount = ui16GetOvrHeatCt();
     tDebugEnvDataStruct.ucEcuTWCombinedSpeed = ((ui16GetCombVSpeed(tEnvDataToSend.ushVehSpeed)<0xFF)?ui16GetCombVSpeed(tEnvDataToSend.ushVehSpeed):0xFF);
     tDebugEnvDataStruct.ucEcuTWFilteredSpeed = ((ui16GetFilterSpeedInKmh()<0xFF)?ui16GetFilterSpeedInKmh():0xFF);

    tDebugEnvDataStruct.ucEcuSensorFailureState = ucGetFailureState();
    tDebugEnvDataStruct.ucEcuAutoLocateMode = ucGetFzzCurrentLearnMode();
    tDebugEnvDataStruct.ucEcuAutoLearnStatus = ui8GetDAGAutoLearnState();

       Rte_Call_PP_GetWANonVolatileData_OP_GetHistID(0, &tDebugEnvDataStruct.aulHistoryID0);
       Rte_Call_PP_GetWANonVolatileData_OP_GetHistID(1, &tDebugEnvDataStruct.aulHistoryID1);
       Rte_Call_PP_GetWANonVolatileData_OP_GetHistID(2, &tDebugEnvDataStruct.aulHistoryID2);
       Rte_Call_PP_GetWANonVolatileData_OP_GetHistID(3, &tDebugEnvDataStruct.aulHistoryID3);
       Rte_Call_PP_GetWANonVolatileData_OP_GetWPOfCol(0, &tDebugEnvDataStruct.aucHistoryWP0);
       Rte_Call_PP_GetWANonVolatileData_OP_GetWPOfCol(1, &tDebugEnvDataStruct.aucHistoryWP1);
       Rte_Call_PP_GetWANonVolatileData_OP_GetWPOfCol(2, &tDebugEnvDataStruct.aucHistoryWP2);
       Rte_Call_PP_GetWANonVolatileData_OP_GetWPOfCol(3, &tDebugEnvDataStruct.aucHistoryWP3);

      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)0,  &tDebugEnvDataStruct.ulZomID0);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)1,  &tDebugEnvDataStruct.ulZomID1);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)2,  &tDebugEnvDataStruct.ulZomID2);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)3,  &tDebugEnvDataStruct.ulZomID3);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)4,  &tDebugEnvDataStruct.ulZomID4);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)5,  &tDebugEnvDataStruct.ulZomID5);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)6,  &tDebugEnvDataStruct.ulZomID6);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)7,  &tDebugEnvDataStruct.ulZomID7);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)8,  &tDebugEnvDataStruct.ulZomID8);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)9,  &tDebugEnvDataStruct.ulZomID9);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)10, &tDebugEnvDataStruct.ulZomID10);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)11, &tDebugEnvDataStruct.ulZomID11);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)12, &tDebugEnvDataStruct.ulZomID12);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)13, &tDebugEnvDataStruct.ulZomID13);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)14, &tDebugEnvDataStruct.ulZomID14);
      Rte_Call_PP_GetZomData_OP_GetZomID((uint8)15, &tDebugEnvDataStruct.ulZomID15);

    for(i=0; i< cSumWE; i++){
      Rte_Call_PP_GetZomData_OP_GetZomStatus((uint8)i, &tDebugEnvDataStruct.aucZomStatus[i]);
      Rte_Call_PP_GetZomData_OP_GetZomStatisticTelCounter(i, &tDebugEnvDataStruct.aucZomStatTelCounter[i]);
      tDebugEnvDataStruct.aucZomToothTelCtLearnBit[i] = ucGetZomTelCtLearnBit(i);
      Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrLearnBit(i, &ucTemp1);
      Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrNoLearnBit(i, &ucTemp2);
      tDebugEnvDataStruct.aucZomToothTelCtCorr[i] = (ucTemp1 + ucTemp2)<0xFF?(ucTemp1+ucTemp2):0xFF;
      Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoCorr(i, &tDebugEnvDataStruct.aucZomToothTelCtrNoCorr[i]);
      RCtApHufTPMSwpa_GetZomToothTelCtCorrNoLearnMode_Opetation(i,  &tDebugEnvDataStruct.aucZomToothTelCtNoLearnMode[i]);
       Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFL(i, &tDebugEnvDataStruct.aushZomAbsSumFL[i]);
       Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFR(i, &tDebugEnvDataStruct.aushZomAbsSumFR[i]);
       Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRL(i, &tDebugEnvDataStruct.aushZomAbsSumRL[i]);
       Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRR(i, &tDebugEnvDataStruct.aushZomAbsSumRR[i]);
    }
     tDebugEnvDataStruct.ucEcuEspDelay = ucEspDelayTime;
    tDebugEnvDataStruct.ucEcuALMethod = GetOpTimeMethodCurrent();

      tDebugEnvDataStruct.ushAbsResetFlag=0;
      for(i=0; i< cSumWE; i++){
         tDebugEnvDataStruct.ushAbsResetFlag |= (((uint16)ucGetZomResetAbsRefFlag(i))<<i);

         if(tDebugEnvDataStruct.ushAbsResetFlag!=0)
            tDebugEnvDataStruct.ushAbsResetFlag = tDebugEnvDataStruct.ushAbsResetFlag;
      }

    Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)cRadPosVL, &tdebugTelStructPosFL.ucWheelStat);
    Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)cRadPosVR, &tdebugTelStructPosFR.ucWheelStat);
    Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)cRadPosHL, &tdebugTelStructPosRL.ucWheelStat);
    Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn((uint8)cRadPosHR, &tdebugTelStructPosRR.ucWheelStat);
    tDebugEnvDataStruct.ushUsedHistoryWP = 0;
    for(i=0;i<cMaxLR;i++){
      tDebugEnvDataStruct.ushUsedHistoryWP = tDebugEnvDataStruct.ushUsedHistoryWP | ((GetCurUsedWPOfCol(i)&0x07) << (i*4));

      if(GetCurUsedWPOfCol(i)== cRadPosVL){
        tdebugTelStructPosFL.ulID = ulGetID(i);
      }
      else if(GetCurUsedWPOfCol(i)== cRadPosVR){
        tdebugTelStructPosFR.ulID = ulGetID(i);
      }
      else if(GetCurUsedWPOfCol(i)== cRadPosHL){
        tdebugTelStructPosRL.ulID = ulGetID(i);
      }
      else if(GetCurUsedWPOfCol(i)== cRadPosHR){
        tdebugTelStructPosRR.ulID = ulGetID(i);
      }
    }

    tdebugTelStructPosFL.ushTimeMute = ushGetTelMuteTime(ucGetColOfID(&(tdebugTelStructPosFL.ulID)));
    tdebugTelStructPosFR.ushTimeMute = ushGetTelMuteTime(ucGetColOfID(&(tdebugTelStructPosFR.ulID)));
    tdebugTelStructPosRL.ushTimeMute = ushGetTelMuteTime(ucGetColOfID(&(tdebugTelStructPosRL.ulID)));
    tdebugTelStructPosRR.ushTimeMute = ushGetTelMuteTime(ucGetColOfID(&(tdebugTelStructPosRR.ulID)));

    tdebugTelStructPosFL.ucSensorState = ucGetSensorState(ucGetColOfID(&(tdebugTelStructPosFL.ulID)));
    tdebugTelStructPosFR.ucSensorState = ucGetSensorState(ucGetColOfID(&(tdebugTelStructPosFR.ulID)));
    tdebugTelStructPosRL.ucSensorState = ucGetSensorState(ucGetColOfID(&(tdebugTelStructPosRL.ulID)));
    tdebugTelStructPosRR.ucSensorState = ucGetSensorState(ucGetColOfID(&(tdebugTelStructPosRR.ulID)));

    tdebugTelStructPosFL.ucEcuFdPCompare = GETucPosComparePressure(cRadPosVL);
    tdebugTelStructPosFR.ucEcuFdPCompare = GETucPosComparePressure(cRadPosVR);
    tdebugTelStructPosRL.ucEcuFdPCompare = GETucPosComparePressure(cRadPosHL);
    tdebugTelStructPosRR.ucEcuFdPCompare = GETucPosComparePressure(cRadPosHR);

    tdebugTelStructPosFL.ucEcuFdNumBlocks = GETucRErecCounter4FDVL();
    tdebugTelStructPosFR.ucEcuFdNumBlocks = GETucRErecCounter4FDVR();
    tdebugTelStructPosRL.ucEcuFdNumBlocks = GETucRErecCounter4FDHL();
    tdebugTelStructPosRR.ucEcuFdNumBlocks = GETucRErecCounter4FDHR();

    tdebugTelStructPosFL.ucP = ucGetLastReceivedPress(tdebugTelStructPosFL.ulID);
    tdebugTelStructPosFR.ucP = ucGetLastReceivedPress(tdebugTelStructPosFR.ulID);
    tdebugTelStructPosRL.ucP = ucGetLastReceivedPress(tdebugTelStructPosRL.ulID);
    tdebugTelStructPosRR.ucP = ucGetLastReceivedPress(tdebugTelStructPosRR.ulID);

    tdebugTelStructPosFL.ucT = ucGetLastReceivedTemp(tdebugTelStructPosFL.ulID);
    tdebugTelStructPosFR.ucT = ucGetLastReceivedTemp(tdebugTelStructPosFR.ulID);
    tdebugTelStructPosRL.ucT = ucGetLastReceivedTemp(tdebugTelStructPosRL.ulID);
    tdebugTelStructPosRR.ucT = ucGetLastReceivedTemp(tdebugTelStructPosRR.ulID);

    tdebugTelStructPosFL.ucPref = ui8GetPRefRel(ucGetColOfID(&(tdebugTelStructPosFL.ulID)));
    tdebugTelStructPosFR.ucPref = ui8GetPRefRel(ucGetColOfID(&(tdebugTelStructPosFR.ulID)));
    tdebugTelStructPosRL.ucPref = ui8GetPRefRel(ucGetColOfID(&(tdebugTelStructPosRL.ulID)));
    tdebugTelStructPosRR.ucPref = ui8GetPRefRel(ucGetColOfID(&(tdebugTelStructPosRR.ulID)));

    tdebugTelStructPosFL.ucTref = i8GetTref(ucGetColOfID(&(tdebugTelStructPosFL.ulID)));
    tdebugTelStructPosFR.ucTref = i8GetTref(ucGetColOfID(&(tdebugTelStructPosFR.ulID)));
    tdebugTelStructPosRL.ucTref = i8GetTref(ucGetColOfID(&(tdebugTelStructPosRL.ulID)));
    tdebugTelStructPosRR.ucTref = i8GetTref(ucGetColOfID(&(tdebugTelStructPosRR.ulID)));

    tdebugTelStructPosFL.ucEcuLoBatCnt = (GETtSensorBatInfOfRam(ucGetColOfID(&(tdebugTelStructPosFL.ulID)))).ui8Count;
    tdebugTelStructPosFR.ucEcuLoBatCnt = (GETtSensorBatInfOfRam(ucGetColOfID(&(tdebugTelStructPosFR.ulID)))).ui8Count;
    tdebugTelStructPosRL.ucEcuLoBatCnt = (GETtSensorBatInfOfRam(ucGetColOfID(&(tdebugTelStructPosRL.ulID)))).ui8Count;
    tdebugTelStructPosRR.ucEcuLoBatCnt = (GETtSensorBatInfOfRam(ucGetColOfID(&(tdebugTelStructPosRR.ulID)))).ui8Count;

    GETDAGWrnLvlOfIdCol(ucGetColOfID(&tdebugTelStructPosFL.ulID), (uint8*)&tdebugTelStructPosFL.ucWT_Pmin);
     GETDAGWrnLvlOfIdCol(ucGetColOfID(&tdebugTelStructPosFR.ulID), (uint8*)&tdebugTelStructPosFR.ucWT_Pmin);
     GETDAGWrnLvlOfIdCol(ucGetColOfID(&tdebugTelStructPosRL.ulID), (uint8*)&tdebugTelStructPosRL.ucWT_Pmin);
     GETDAGWrnLvlOfIdCol(ucGetColOfID(&tdebugTelStructPosRR.ulID), (uint8*)&tdebugTelStructPosRR.ucWT_Pmin);

    tdebugTelStructPosFL.ucWT_Clear = ui8GETDAGClrWrnThresOfIdCol(ucGetColOfID(&(tdebugTelStructPosFL.ulID)));
    tdebugTelStructPosFR.ucWT_Clear = ui8GETDAGClrWrnThresOfIdCol(ucGetColOfID(&(tdebugTelStructPosFR.ulID)));
    tdebugTelStructPosRL.ucWT_Clear = ui8GETDAGClrWrnThresOfIdCol(ucGetColOfID(&(tdebugTelStructPosRL.ulID)));
    tdebugTelStructPosRR.ucWT_Clear = ui8GETDAGClrWrnThresOfIdCol(ucGetColOfID(&(tdebugTelStructPosRR.ulID)));

      TracePutEnvDataStr2Queue(&tDebugEnvDataStruct);
    TracePutTelStrPosFL2Queue(&tdebugTelStructPosFL);
    TracePutTelStrPosFR2Queue(&tdebugTelStructPosFR);
    TracePutTelStrPosRL2Queue(&tdebugTelStructPosRL);
    TracePutTelStrPosRR2Queue(&tdebugTelStructPosRR);
}

