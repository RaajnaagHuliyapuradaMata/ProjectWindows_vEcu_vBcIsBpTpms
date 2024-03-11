

#include "Walloc_IF.h"
#include "WAllocX.h"
#include "abs_linX.h"
#include "cd_decoder_x.h"
#include "watcfX.h"
#include "tel_statisticX.h"

#include "Rte_CtApHufTPMSwpa.h"
extern uint8 GETucLqiOfRam(void);

void GetWADataEE(unsigned char ucId, unsigned char *pRamAdr, unsigned char ucLen){
unsigned char i;

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

void PutWADataEE(unsigned char ucId, unsigned char *pRamAdr, unsigned char ucLen){
  unsigned char i;
  unsigned char ucChange = (unsigned char) 0;

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

#ifndef WAModulTest
  if(ucChange > ((unsigned char) 0)){
    SetWaData2NvmFlag();
  }
#endif
}

unsigned char ucGetABSTick(unsigned short * p2aushABS){

  uint8  ucRet;

  ucRet = GetLinABS( p2aushABS );

  if( ucRet == cABS_OK ){
    ucRet = (unsigned char) 1;
  }
  else
  {
    ucRet = (unsigned char) 0;
  }

  return ucRet;
}

unsigned short ushGetABSingleTick(unsigned char ucIx){

  unsigned char  ucRet;
  unsigned short ushCnt[4];
  unsigned short ushCurrentAbsTick;
  ucRet = GetLinABS( ushCnt );

  if(ucRet == cABS_OK){

    ushCurrentAbsTick = ushCnt[ucIx];
  }
  else
  {
    ushCurrentAbsTick = cABSStickError;
  }

  return ( ushCurrentAbsTick );

}

unsigned char ucGetSpeed(void){

    extern unsigned short ushV;

   if(ushV > 255)
      return ((unsigned char) 255);
   else
      return ((unsigned char) ushV);

}

unsigned char ucNoWheelSensorMounted(void){
#ifdef WAModulTest
  return 0;
#else
  return ((FAILURE_MODE_noWE == ucGetFailureState()) ? (unsigned char) 1:(unsigned char) 0);
#endif
}
void WAStatusChangedEvent(unsigned short ushWAState){
#ifndef WAModulTest
  Rte_Write_PP_WAState_DE_ushWAState(ushWAState);
#endif
}

unsigned char ucDAG_LQIParameter(void){
#ifdef WAModulTest
  return 0;
#else
  return GETucLqiOfRam();
#endif
}
