/******************************************************************************/
/* File              : Walloc_IF.c                                            */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/*#includeS                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "Walloc_IF.h"
#include "WAllocX.h"
#include "abs_linX.h"
#include "cd_decoder_x.h"
#include "watcfX.h"
#include "tel_statisticX.h"
//#include "Rte_CtApHufTPMSwpa.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern uint8 GETucLqiOfRam(void);

void GetWADataEE(uint8 ucId, uint8* pRamAdr, uint8 ucLen){
   uint8 i;
   switch(ucId){
  case cWAParameter:
    {
      for(i=0;i < ucLen;i++){
        *pRamAdr = GETtWAparam(i);
        pRamAdr++;
      }
    }
    break;
  case cHistorySet1:
    {
      for(i=0;i < ucLen;i++){
        *pRamAdr = GETucWAHistID(i);
        pRamAdr++;
      }
    }
    break;
  case cHistoryWPSet1:
    {
      for(i=0;i < ucLen;i++){
        *pRamAdr = GETucWAHistWP(i);
        pRamAdr++;
      }
    }
    break;

  default:
    break;
  }
}

void PutWADataEE(uint8 ucId, uint8 *pRamAdr, uint8 ucLen){
  uint8 i;
  uint8 ucChange = (uint8) 0;
  switch(ucId){
  case cWAParameter:
    {
      for(i=0;i < ucLen;i++){
        if(GETtWAparam(i) != *pRamAdr){
          PUTtWAparam( *pRamAdr,i );
          ucChange++;
        }
        pRamAdr++;
      }
    }
    break;
  case cHistorySet1:
    {
      for(i=0;i < ucLen;i++){
        if(GETucWAHistID (i) != *pRamAdr){
          PUTucWAHistID( *pRamAdr,i );
          ucChange ++;
        }
        pRamAdr++;
      }
    }
    break;
  case cHistoryWPSet1:
    {
      for(i=0;i < ucLen;i++){
        if(GETucWAHistWP (i) != *pRamAdr ){
          PUTucWAHistWP( *pRamAdr,i );
          ucChange ++;
        }
        pRamAdr++;
      }
    }
    break;
  default:
    break;
  }
  if(ucChange > ((uint8) 0)){
    SetWaData2NvmFlag();
  }
}

uint8 ucGetABSTick(uint16* p2aushABS){
  uint8  ucRet;
  ucRet = GetLinABS( p2aushABS );
  if( ucRet == cABS_OK ){
    ucRet = (uint8) 1;
  }
  else{
    ucRet = (uint8) 0;
  }
  return ucRet;
}

uint16 ushGetABSingleTick(uint8 ucIx){
  uint8  ucRet;
  uint16 ushCnt[4];
  uint16 ushCurrentAbsTick;
  ucRet = GetLinABS( ushCnt );
  if(ucRet == cABS_OK){
    ushCurrentAbsTick = ushCnt[ucIx];
  }
  else{
    ushCurrentAbsTick = cABSStickError;
  }
  return(ushCurrentAbsTick);
}

uint8 ucGetSpeed(void){
   extern uint16 ushV;
   if(ushV > 255)return((uint8) 255);
   else          return((uint8) ushV);
}

uint8 ucNoWheelSensorMounted(void){
  return((FAILURE_MODE_noWE == ucGetFailureState()) ? (uint8) 1:(uint8) 0);
}

typedef uint16 DT_ushWAState;
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_CtApHufTPMSwpa_PP_WAState_DE_ushWAState(DT_ushWAState data);
void WAStatusChangedEvent(uint16 ushWAState){
   Rte_Write_CtApHufTPMSwpa_PP_WAState_DE_ushWAState(ushWAState);
}

uint8 ucDAG_LQIParameter(void){
  return GETucLqiOfRam();
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

