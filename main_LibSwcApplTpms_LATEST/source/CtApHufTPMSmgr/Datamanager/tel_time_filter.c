

#include "tel_time_filter.h"
#include "tel_time_filterX.h"
#include "tel_StatisticX.h"
#include "WallocX.h"

#define cTimeOverFlow (uint32) 0xFFFFFFFF
#define cTimeFilterLength (uint16) 900

static uint16 ushTimeFilterInMilliSec = cTimeFilterLength;

uint8 ucPassTimeFilter(uint32 ulID, uint8 ucTelType, uint32 ulSysTime)
{

  uint8 ucIx,ucRet = 0;
   uint32 ulCurTimeDif = 0;

  if ( (ucTelType == cTelTypeSELPAL) ||  (ucTelType == cTelTypeSELPAL1) || (ucTelType == 0x00) || (ucTelType == 0x20) || (ucTelType == 0x01) || (ucTelType == 0xC3) || (ucTelType == 0xC1) || (ucTelType == 0xCA))
  {
    ucIx = ucTelStatGetIDPosInTable( (uint32)ulID );

    if (ucIx < cTableSize)
    {
       ulCurTimeDif = ulSysTime >= ulTelStatGetLastRxTime((uint32)ulID ) ? ulSysTime - ulTelStatGetLastRxTime((uint32)ulID ) :  cTimeOverFlow +  ulSysTime - ulTelStatGetLastRxTime((uint32)ulID );
       if ((ulTelStatGetLastRxTime((uint32)ulID ) == 0) || (ulCurTimeDif > ((uint32) ushTimeFilterInMilliSec)))
      {
        ucRet = 1;
       }
    }
    else
    {
      ucRet = 1;
     }
  }
  else
  {
      ucRet = 0;
   }

  return (ucRet);
}

void SetTimeFilter(uint16 ushFilterTime)
{
  ushTimeFilterInMilliSec = ushFilterTime;
}

uint16 ushGetFilterTimeInSec(void)
{
  return (ushTimeFilterInMilliSec);
}
void InitFilterTime(void)
{
  SetTimeFilter(cTimeFilterLength);
}
