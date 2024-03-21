

#include "palLocate_statistic.h"
#include "WallocX.h"
#include "state_bzX.h"
#include "Rte_CtApHufTPMSdia.h"
#include "tel_statisticX.h"

#define FAILURE_REASONS_NUMB 10U

typedef struct{
  uint8 ucPrevPalResult;
  uint8 ucFullLocStatus;
  uint8 ucFullLocFailureCnt;
  uint8 ucFullLocFailureCntMax;
  uint8 ucFullLocPassCnt;
  uint8 ucPalFailureReasonsArray[FAILURE_REASONS_NUMB];
}palLocateStats;

typedef struct{
  uint8 ulRvsID[4];
    uint8 ucLocPassCnt;
  uint8 ucLocFailureCnt;
  uint8 ucLocPassRatio;
  uint8 ucLocFailureInARowCnt;
  uint8 ucAvgStdDevFL;
  uint8 ucAvgStdDevFR;
  uint8 ucAvgStdDevRL;
  uint8 ucAvgStdDevRR;
  uint8 ucCorrBlocksRatio;
}palStatsLongTermWU;

typedef struct{
  uint8 ulRvsID[4];
   uint8 ucAvgStdDevFL;
  uint8 ucAvgStdDevFR;
  uint8 ucAvgStdDevRL;
  uint8 ucAvgStdDevRR;
  uint8 ucCorrBlocks;
  uint8 ucNoCorrBlocks;
  uint8 ucLearnBlocks;
  uint8 ucOtherBlocks;
}palStatsLastCycleWU;

static palStatsLastCycleWU* ptr2palStatsLastCycleWU = (palStatsLastCycleWU*)&Rte_Pim_Pim_tDiagNvMBlock0()->aucPalStatsLastCycleWU;
static palStatsLongTermWU* ptr2PalStatsLongTermWU = (palStatsLongTermWU*)&Rte_Pim_Pim_tDiagNvMBlock0()->aucPalStatsLongTermWU;
static palLocateStats* ptr2PalLocateStats = (palLocateStats*)&Rte_Pim_Pim_tDiagNvMBlock0()->aucPalLocateStatistics;

void InitPalLocateStatistics(void);

void InitPalLocateStatistics(void){
}

uint8* GetPalLocateStatistics(void){
  return (uint8*)&Rte_Pim_Pim_tDiagNvMBlock0()->aucPalLocateStatistics;
}

uint8 GetucFullLocFailureCnt(void){
  return (ptr2PalLocateStats->ucFullLocFailureCnt);
}

void PutPalLocateStatistics2Ram(void){
  static boolean bPALCompleted = FALSE;
  uint8 i, ucFailureReason;
  NvM_RequestResultType ErrorStatus;

  ucFailureReason = 0;
    if(ui8GetALState() == cAL_OK){
    ptr2PalLocateStats->ucFullLocStatus =  0x02;
  }
  else if(ui8GetALState() == cAL_Stored){
    ptr2PalLocateStats->ucFullLocStatus =  0x03;
  }
  else if(ui8GetALState() == cAL_Unknown){
    ptr2PalLocateStats->ucFullLocStatus =  0x00;
  }
  else if(ui8GetALState() == cAL_Error){
    ptr2PalLocateStats->ucFullLocStatus =  0x01;
  }
  else{
  }
  if( (bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT) )    && (!bPALCompleted)  &&  (ucGetLearnMode()==cCompleteLearn) ){
    bPALCompleted = TRUE;
    if( (ui8GetALState() == cAL_Error) || (ui8GetALState() == cAL_Stored)){
      ptr2PalLocateStats->ucPrevPalResult = 0x01;
      if(ptr2PalLocateStats->ucFullLocFailureCnt < 0xFF)
        ptr2PalLocateStats->ucFullLocFailureCnt ++;
      ptr2PalLocateStats->ucFullLocPassCnt = 0;

      if(ptr2PalLocateStats->ucFullLocFailureCnt > ptr2PalLocateStats->ucFullLocFailureCntMax ){
        ptr2PalLocateStats->ucFullLocFailureCntMax   = ptr2PalLocateStats->ucFullLocFailureCnt;
      }
    }
    else if( ui8GetALState() == cAL_OK){
      ptr2PalLocateStats->ucPrevPalResult = 0x00;
      if(ptr2PalLocateStats->ucFullLocPassCnt < 0xFF)
        ptr2PalLocateStats->ucFullLocPassCnt++;

      ptr2PalLocateStats->ucFullLocFailureCnt = 0;
    }
    else{
    }
    for(i=0; i<cMaxLR; i++){
      if( (pucGetLocatError()[i]) != NoError){
          ucFailureReason |= (0x01<<i);
      }
    }

    if( (ucFailureReason > 0) && (ucFailureReason != 0x01) && (ucFailureReason != 0x02) && (ucFailureReason != 0x04) && (ucFailureReason != 0x08)){
      for(i=FAILURE_REASONS_NUMB-1; i>0; i--){
        ptr2PalLocateStats->ucPalFailureReasonsArray[i] =  ptr2PalLocateStats->ucPalFailureReasonsArray[i-1];
      }
      ptr2PalLocateStats->ucPalFailureReasonsArray[0] = ucFailureReason;
    }

    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus);
    if(ErrorStatus  != NVM_REQ_PENDING){
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
    }
  }
}

void PutPalStatsLastCycleWU2Ram(void){
  uint8 ucColPos, ucZomPos, ucTemp1, ucTemp2;
  uint16 ushTemp1;
  uint32 ulTempID;
   static boolean bPALCompleted = FALSE;
  NvM_RequestResultType ErrorStatus;
   for(ucColPos=0; ucColPos< cMaxLR; ucColPos++){
    ulTempID = ulGetID(ucColPos);
     ptr2palStatsLastCycleWU[ucColPos].ulRvsID[0] = (uint8)(ulTempID>>24);
    ptr2palStatsLastCycleWU[ucColPos].ulRvsID[1] = (uint8)(ulTempID>>16);
    ptr2palStatsLastCycleWU[ucColPos].ulRvsID[2] = (uint8)(ulTempID>>8);
    ptr2palStatsLastCycleWU[ucColPos].ulRvsID[3] = (uint8)(ulTempID>>0);
     ptr2PalStatsLongTermWU[ucColPos].ulRvsID[0] = (uint8)(ulTempID>>24);
    ptr2PalStatsLongTermWU[ucColPos].ulRvsID[1] = (uint8)(ulTempID>>16);
    ptr2PalStatsLongTermWU[ucColPos].ulRvsID[2] = (uint8)(ulTempID>>8);
    ptr2PalStatsLongTermWU[ucColPos].ulRvsID[3] = (uint8)(ulTempID>>0);
  }

  if( (bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT) )    && (!bPALCompleted)  &&  (ucGetLearnMode()==cCompleteLearn) ){
    bPALCompleted = TRUE;
     for(ucColPos=0; ucColPos< cMaxLR; ucColPos++){
      ulTempID = ulGetID(ucColPos);
      ucZomPos = ucGetZOMPosOfID(&ulTempID);

      if(ucZomPos < cSumWE){
        Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrLearnBit(ucZomPos, &ucTemp1);
        Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrNoLearnBit(ucZomPos, &ucTemp2);
        ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks = ucTemp1 + ucTemp2;
         Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoCorr(ucZomPos, &ucTemp1);
         ptr2palStatsLastCycleWU[ucColPos].ucNoCorrBlocks = ucTemp1;
        ptr2palStatsLastCycleWU[ucColPos].ucLearnBlocks = ucGetZomTelCtLearnBit(ucZomPos);
        ptr2palStatsLastCycleWU[ucColPos].ucOtherBlocks = ucTelStatGetLastRxBlocs(ulTempID) - (ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks + ptr2palStatsLastCycleWU[ucColPos].ucNoCorrBlocks);

        if((pucGetLocatError()[ucColPos]) != SensorMissin){
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFL(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL = (uint8)ushTemp1;
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFR(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR = (uint8)ushTemp1;
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRL(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL = (uint8)ushTemp1;
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRR(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR = (uint8)ushTemp1;
        }
        else{
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR = 0;
        }
         if((pucGetLocatError()[ucColPos]) == NoError){
          ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt++;
          if(ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt == 0xFF){
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
          }
          ptr2PalStatsLongTermWU[ucColPos].ucLocFailureInARowCnt = 0;
         }
        else{
          ptr2PalStatsLongTermWU[ucColPos].ucLocFailureCnt++;
          if(ptr2PalStatsLongTermWU[ucColPos].ucLocFailureCnt == 0xFF){
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
          }
          if(ptr2PalStatsLongTermWU[ucColPos].ucLocFailureInARowCnt < 0xFF){
            ptr2PalStatsLongTermWU[ucColPos].ucLocFailureInARowCnt++;
           }
        }
        ptr2PalStatsLongTermWU[ucColPos].ucLocPassRatio = 100*(ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt)/(ptr2PalStatsLongTermWU[ucColPos].ucLocFailureCnt + ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt);

        ushTemp1 = ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks + ptr2palStatsLastCycleWU[ucColPos].ucNoCorrBlocks + ptr2palStatsLastCycleWU[ucColPos].ucOtherBlocks;

        if(ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL == 0){
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFR = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRL = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRR = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR;
          ptr2PalStatsLongTermWU[ucColPos].ucCorrBlocksRatio =  100*ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks/ushTemp1;
        }
        else{
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFR = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFR)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRL = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRL)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRR = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRR)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucCorrBlocksRatio =  (ptr2PalStatsLongTermWU[ucColPos].ucCorrBlocksRatio + (100*ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks/ushTemp1))>>1;
        }

      }
      else{
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR = 0;

          ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucNoCorrBlocks = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucLearnBlocks = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucOtherBlocks = 0;
      }
    }

    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus);
    if(ErrorStatus  != NVM_REQ_PENDING){
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
    }
  }
}

uint8* GetPalStatsLastCycleWU(uint8 ucColPos){
  if(ucColPos<cMaxLR){
    return (uint8*)(ptr2palStatsLastCycleWU + ucColPos);
  }
  else{
    return (uint8*)NULL_PTR;
  }
}

uint8* GetPalStatsLongTermWU(uint8 ucColPos){
  if(ucColPos<cMaxLR){
    return (uint8*)(ptr2PalStatsLongTermWU + ucColPos);
  }
  else{
    return (uint8*)NULL_PTR;
  }
}

void ClearStatsLastCycleWU(void){
  uint8 i, j;
  NvM_RequestResultType ErrorStatus;

  for(j=0; j<cMaxLR; j++){
    for(i=0; i<sizeof(palStatsLastCycleWU); i++){
      ((uint8*)(ptr2palStatsLastCycleWU + j))[i] = 0;
    }
  }

  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}

void ClearStatsLastCycleWUx(uint8 j){
  uint8 i;
  NvM_RequestResultType ErrorStatus;

  if(j < cMaxLR){
    for(i=0; i<sizeof(palStatsLastCycleWU); i++){
      ((uint8*)(ptr2palStatsLastCycleWU + j))[i] = 0;
    }

    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus);
    if(ErrorStatus  != NVM_REQ_PENDING){
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
    }
  }
}

void ClearPalLocateStatistics(void){
  uint8 i;
  NvM_RequestResultType ErrorStatus;

  for(i=0; i<sizeof(DT_aucPalLocateStatistics); i++){
    ((uint8*)ptr2PalLocateStats)[i] =  0;
  }
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}

void ClearStatsLongTermWU(void){
  uint8 i, j;
  NvM_RequestResultType ErrorStatus;

  for(j=0; j<cMaxLR; j++){
    for(i=0; i< sizeof(palStatsLongTermWU); i++){
      ((uint8*)(ptr2PalStatsLongTermWU + j))[i] = 0;
    }
  }
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}

void ClearStatsLongTermWUx(uint8 j){
  uint8 i;
  NvM_RequestResultType ErrorStatus;

  for(i=0; i< sizeof(palStatsLongTermWU); i++){
    ((uint8*)(ptr2PalStatsLongTermWU + j))[i] = 0;
  }

  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}
