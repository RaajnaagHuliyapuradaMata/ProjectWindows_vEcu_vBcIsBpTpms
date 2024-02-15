/************************************************************************************************************
 * (c) HuF Electronics GmbH      Abteilung ENTS4     2015
 ************************************************************************************************************/

/*********************************************************************************************************//**
 * \file palLocate_statistic.c
 * \brief prepare pal locate statistic data
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


/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "palLocate_statistic.h"
#include "WallocX.h"
#include "state_bzX.h"
#include "Rte_CtApHufTPMSdia.h"
#include "tel_statisticX.h"
/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/

#define FAILURE_REASONS_NUMB 10U

typedef struct
{
  uint8 ucPrevPalResult;
  uint8 ucFullLocStatus;
  uint8 ucFullLocFailureCnt;
  uint8 ucFullLocFailureCntMax;
  uint8 ucFullLocPassCnt;
  uint8 ucPalFailureReasonsArray[FAILURE_REASONS_NUMB];
}palLocateStats; // Pal locate statistics

typedef struct
{
  uint8 ulRvsID[4]; ////reversed byte order of ID
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

typedef struct
{
  uint8 ulRvsID[4]; //reversed byte order of ID
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
/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/


/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/
void InitPalLocateStatistics(void);
/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/

/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/


/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/


/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/

 
/************************************************************************************************//**
 * \brief init PAL statistic module
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void InitPalLocateStatistics(void)
{
  // byte 0 , previous PAL result
  //*((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_0) = *((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_1);
}

/************************************************************************************************//**
 * \brief Get PAL locate statistics 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_aucPalLocateStatistics()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
uint8 * GetPalLocateStatistics(void)
{
  return (uint8*)&Rte_Pim_Pim_tDiagNvMBlock0()->aucPalLocateStatistics;
}

/************************************************************************************************//**
 * \brief Get PAL location failed counter 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_aucPalLocateStatistics()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
uint8 GetucFullLocFailureCnt(void)
{
  return (ptr2PalLocateStats->ucFullLocFailureCnt);
}

/************************************************************************************************//**
 * \brief Put PAL locate statistics to RAM 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_aucPalLocateStatistics()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void PutPalLocateStatistics2Ram(void)
{
  static boolean bPALCompleted = FALSE;
  uint8 i, ucFailureReason;
  NvM_RequestResultType ErrorStatus;

  ucFailureReason = 0; //init

  // byte 1, Full Locate Status
  if(ui8GetALState() == cAL_OK)
  {
    //*((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_1) = 0x02;
    ptr2PalLocateStats->ucFullLocStatus =  0x02;
  }
  else if (ui8GetALState() == cAL_Stored)
  {
    //*((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_1) = 0x03;
    ptr2PalLocateStats->ucFullLocStatus =  0x03;
  }
  else if (ui8GetALState() == cAL_Unknown)
  {
    //*((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_1) = 0x00;
    ptr2PalLocateStats->ucFullLocStatus =  0x00;
  }
  else if(ui8GetALState() == cAL_Error)
  {
    //*((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_1) = 0x01;
    ptr2PalLocateStats->ucFullLocStatus =  0x01;
  }
  else
  {
    // do nothing
  }

  // only do this once per learn cycle
  if( (bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT) )    && (!bPALCompleted)  &&  (ucGetLearnMode()==cCompleteLearn) ) //learn mode from walloc module)
  {
    bPALCompleted = TRUE;
    //byte 2, full locate fail count
    if( (ui8GetALState() == cAL_Error) || (ui8GetALState() == cAL_Stored))
    {
      //*((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_0) =0x01; // previous PAL result
      ptr2PalLocateStats->ucPrevPalResult = 0x01;

      //if(*((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_2) < 0xFF)
      //  *((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_2) = *((uint8*)RtePim_Pim_aucPalLocateStatistics() + PAL_LOCATE_STAT_2) + 1; // avoid overflow
      if(ptr2PalLocateStats->ucFullLocFailureCnt < 0xFF)
        ptr2PalLocateStats->ucFullLocFailureCnt ++;
      ptr2PalLocateStats->ucFullLocPassCnt = 0;  // full locate pass count

      if(ptr2PalLocateStats->ucFullLocFailureCnt > ptr2PalLocateStats->ucFullLocFailureCntMax )
      {
        ptr2PalLocateStats->ucFullLocFailureCntMax   = ptr2PalLocateStats->ucFullLocFailureCnt; // full locate fail count max
      }
    }
    else if( ui8GetALState() == cAL_OK)
    {
      ptr2PalLocateStats->ucPrevPalResult = 0x00; // previous PAL result

      if(ptr2PalLocateStats->ucFullLocPassCnt < 0xFF) // full locate pass count
        ptr2PalLocateStats->ucFullLocPassCnt++; // avoid overflow

      ptr2PalLocateStats->ucFullLocFailureCnt = 0;  // full locate fail count
      //palLocateArray[PAL_LOCATE_STAT_2] = 0;  // full locate fail count
    }
    else
    {
        // do nothing
    }


    // byte 5, PAL failure reason
    for (i=0; i<cMaxLR; i++)
    {
      if( (pucGetLocatError()[i]) != NoError)
      {
          ucFailureReason |= (0x01<<i);
      }
    }

    if( (ucFailureReason > 0) && (ucFailureReason != 0x01) && (ucFailureReason != 0x02) && (ucFailureReason != 0x04) && (ucFailureReason != 0x08)) // only do this when at least 2 sensors were not localised
    {
      // implement fifo
      for(i=FAILURE_REASONS_NUMB-1; i>0; i--)
      {
        ptr2PalLocateStats->ucPalFailureReasonsArray[i] =  ptr2PalLocateStats->ucPalFailureReasonsArray[i-1];
      }
      ptr2PalLocateStats->ucPalFailureReasonsArray[0] = ucFailureReason;
    }
    
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
    if (ErrorStatus  != NVM_REQ_PENDING)
    {
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
    }
  }
}

/************************************************************************************************//**
 * \brief Put wheel unit statistics from last driving cycle to RAM. 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_aucPalLocateStatistics()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void PutPalStatsLastCycleWU2Ram(void)
{
  uint8 ucColPos, ucZomPos, ucTemp1, ucTemp2;
  uint16 ushTemp1;
  uint32 ulTempID; //ulTempRvsID;
  static boolean bPALCompleted = FALSE;
  NvM_RequestResultType ErrorStatus;


  /*always use current stored IDs */
  
  //--------------fill ID---------------------------------------------
  for (ucColPos=0; ucColPos< cMaxLR; ucColPos++)
  {
    ulTempID = ulGetID(ucColPos);

    // fill last cycle statistic
    ptr2palStatsLastCycleWU[ucColPos].ulRvsID[0] = (uint8)(ulTempID>>24);
    ptr2palStatsLastCycleWU[ucColPos].ulRvsID[1] = (uint8)(ulTempID>>16);
    ptr2palStatsLastCycleWU[ucColPos].ulRvsID[2] = (uint8)(ulTempID>>8);
    ptr2palStatsLastCycleWU[ucColPos].ulRvsID[3] = (uint8)(ulTempID>>0);

    // fill long term statistic
    ptr2PalStatsLongTermWU[ucColPos].ulRvsID[0] = (uint8)(ulTempID>>24);
    ptr2PalStatsLongTermWU[ucColPos].ulRvsID[1] = (uint8)(ulTempID>>16);
    ptr2PalStatsLongTermWU[ucColPos].ulRvsID[2] = (uint8)(ulTempID>>8);
    ptr2PalStatsLongTermWU[ucColPos].ulRvsID[3] = (uint8)(ulTempID>>0);
  }


  if( (bGetBitBetriebszustandBZ(cZO_FINISH) || bGetBitBetriebszustandBZ(cZO_TIMEOUT) )    && (!bPALCompleted)  &&  (ucGetLearnMode()==cCompleteLearn) ) //learn mode from walloc module)
  {
    bPALCompleted = TRUE;

    // only do it once after complete learn has completed
    for (ucColPos=0; ucColPos< cMaxLR; ucColPos++)
    {
      ulTempID = ulGetID(ucColPos);
      //ulTempRvsID = (((uint8)(ulTempID>>0))<<24) + (((uint8)(ulTempID>>8))<<16) +  (((uint8)(ulTempID>>16))<<8) + (((uint8)(ulTempID>>24))<<0);
      ucZomPos = ucGetZOMPosOfID(&ulTempID);


      if (ucZomPos < cSumWE) // ID has been received at least once
      {
        // fill telegramm counter of last cycle
        Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrLearnBit(ucZomPos, &ucTemp1);
        Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrNoLearnBit(ucZomPos, &ucTemp2);
        ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks = ucTemp1 + ucTemp2; // correlated blocks
        Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoCorr(ucZomPos, &ucTemp1); // no correlation
        ptr2palStatsLastCycleWU[ucColPos].ucNoCorrBlocks = ucTemp1;
        ptr2palStatsLastCycleWU[ucColPos].ucLearnBlocks = ucGetZomTelCtLearnBit(ucZomPos);
        ptr2palStatsLastCycleWU[ucColPos].ucOtherBlocks = ucTelStatGetLastRxBlocs(ulTempID) - (ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks + ptr2palStatsLastCycleWU[ucColPos].ucNoCorrBlocks); // others
                
        if((pucGetLocatError()[ucColPos]) != SensorMissin) // sensor not missing?
        {
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFL(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL = (uint8)ushTemp1;
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFR(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR = (uint8)ushTemp1;
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRL(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL = (uint8)ushTemp1;
          Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRR(ucZomPos, &ushTemp1);
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR = (uint8)ushTemp1;
        }
        else // if sensor is detected as missing default values have to be used
        {
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL = 0;
          ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR = 0;
        }

        //----increment localization counter----------------------
        if((pucGetLocatError()[ucColPos]) == NoError) // loc passed?
        {
          ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt++;
          if(ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt == 0xFF)
          {
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
          }
          ptr2PalStatsLongTermWU[ucColPos].ucLocFailureInARowCnt = 0; // re init 
        }
        else
        {
          ptr2PalStatsLongTermWU[ucColPos].ucLocFailureCnt++;
          if(ptr2PalStatsLongTermWU[ucColPos].ucLocFailureCnt == 0xFF)
          {
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
            ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt >>= 1;
          }
          if(ptr2PalStatsLongTermWU[ucColPos].ucLocFailureInARowCnt < 0xFF)
          {
            ptr2PalStatsLongTermWU[ucColPos].ucLocFailureInARowCnt++; //n the case the maximum value of  Fail Locate Fail Count is reached, the increment should be stopped.
          }
        }
        ptr2PalStatsLongTermWU[ucColPos].ucLocPassRatio = 100*(ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt)/(ptr2PalStatsLongTermWU[ucColPos].ucLocFailureCnt + ptr2PalStatsLongTermWU[ucColPos].ucLocPassCnt);
        
        ushTemp1 = ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks + ptr2palStatsLastCycleWU[ucColPos].ucNoCorrBlocks + ptr2palStatsLastCycleWU[ucColPos].ucOtherBlocks;// sum all received blocs during last cycle 

        if(ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL == 0) // first time?
        {
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFR = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRL = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRR = ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR;
          ptr2PalStatsLongTermWU[ucColPos].ucCorrBlocksRatio =  100*ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks/ushTemp1;
        }
        else
        {
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFL + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFL)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFR = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevFR + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevFR)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRL = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRL + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRL)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRR = (ptr2palStatsLastCycleWU[ucColPos].ucAvgStdDevRR + ptr2PalStatsLongTermWU[ucColPos].ucAvgStdDevRR)>>1;
          ptr2PalStatsLongTermWU[ucColPos].ucCorrBlocksRatio =  (ptr2PalStatsLongTermWU[ucColPos].ucCorrBlocksRatio + (100*ptr2palStatsLastCycleWU[ucColPos].ucCorrBlocks/ushTemp1))>>1;
        }

      }
      else
      {
          // sensor were not received, default values are used
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
    
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
    if (ErrorStatus  != NVM_REQ_PENDING)
    {
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
    }
  }
}

/************************************************************************************************//**
 * \brief Get wheel unit statistics from last cycle
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_PalStatsLastCycleWU()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
uint8* GetPalStatsLastCycleWU(uint8 ucColPos)
{
  if (ucColPos<cMaxLR)
  {
    return (uint8*)(ptr2palStatsLastCycleWU + ucColPos);
  }
  else
  {
    return (uint8*)NULL_PTR;
  }
}

/************************************************************************************************//**
 * \brief Get wheel unit statistics longterm
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] xxx
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
uint8* GetPalStatsLongTermWU(uint8 ucColPos)
{
  if (ucColPos<cMaxLR)
  {
    return (uint8*)(ptr2PalStatsLongTermWU + ucColPos);
  }
  else
  {
    return (uint8*)NULL_PTR;
  }
}

/************************************************************************************************//**
 * \brief clear wheel unit statistics from last cycle
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_PalStatsLastCycleWU()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearStatsLastCycleWU(void)
{
  uint8 i, j;
  NvM_RequestResultType ErrorStatus;
  
  for(j=0; j<cMaxLR; j++)
  {
    for (i=0; i<sizeof(palStatsLastCycleWU); i++)
    {
      ((uint8*)(ptr2palStatsLastCycleWU + j))[i] = 0;
    }
  }
  
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}

/************************************************************************************************//**
 * \brief clear specific wheel unit statistics from last cycle 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_PalStatsLastCycleWU()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearStatsLastCycleWUx(uint8 j)
{
  uint8 i;
  NvM_RequestResultType ErrorStatus;
  
  if (j < cMaxLR) // limitation
  {
    for (i=0; i<sizeof(palStatsLastCycleWU); i++)
    {
      ((uint8*)(ptr2palStatsLastCycleWU + j))[i] = 0;
    }

    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
    if (ErrorStatus  != NVM_REQ_PENDING)
    {
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
    }
  }
}

/************************************************************************************************//**
 * \brief clear Pal locate statistics to default values
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] RtePim_Pim_aucPalLocateStatistics()
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearPalLocateStatistics(void)
{
  uint8 i;
  NvM_RequestResultType ErrorStatus;

  for (i=0; i<sizeof(DT_aucPalLocateStatistics); i++)
  {
    //*((uint8*)RtePim_Pim_aucPalLocateStatistics() +  i) = 0;
    ((uint8*)ptr2PalLocateStats)[i] =  0;
  }
  // set write pointer start adress
  //*((uint8*)RtePim_Pim_aucPalLocateStatistics() +  i-(uint8)1) = 0x05; // pointer start
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}

/************************************************************************************************//**
 * \brief clear wheel unit statistics long term
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] xxx
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearStatsLongTermWU(void)
{
  uint8 i, j;
  NvM_RequestResultType ErrorStatus;

  for(j=0; j<cMaxLR; j++)
  {
    for (i=0; i< sizeof(palStatsLongTermWU); i++)
    {
      ((uint8*)(ptr2PalStatsLongTermWU + j))[i] = 0;
    }
  }
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}

/************************************************************************************************//**
 * \brief clear specific wheel unit statistics long term
 *
 *-----------------------------------------------------------------------------------------------
 * \param [out] xxx
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearStatsLongTermWUx(uint8 j)
{
  uint8 i;
  NvM_RequestResultType ErrorStatus;

  for (i=0; i< sizeof(palStatsLongTermWU); i++)
  {
    ((uint8*)(ptr2PalStatsLongTermWU + j))[i] = 0;
  }
    
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSdia_Pim_tDiagNvMBlock0_SetRamBlockStatus(TRUE);
  }
}