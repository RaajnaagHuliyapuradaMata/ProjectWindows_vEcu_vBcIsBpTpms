/************************************************************************************************************
 * (c) HuF Electronics GmbH      Abteilung ENTS4     2015
 ************************************************************************************************************/
/*********************************************************************************************************//**
 * \file tel_time_filter.c
 * \brief Manage telegramm time frame filters
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


/*
Include
*/
#include "tel_time_filter.h"
#include "tel_time_filterX.h"
#include "tel_StatisticX.h"
#include "WallocX.h"
/*
Prototypes and Macros
*/



/*
Prototypes
*/

/*
_______________________________________________________Macros
*/
#define cTimeOverFlow (uint32) 0xFFFFFFFF
#define cTimeFilterLength (uint16) 900 // 900 ms
/*
_________________________________________________________Data
*/
static uint16 ushTimeFilterInMilliSec = cTimeFilterLength; // time filter off per default

/*____________________________________________definitions___________________________________________________*/
uint8 ucPassTimeFilter(uint32 ulID, uint8 ucTelType, uint32 ulSysTime)
{
  
  uint8 ucIx,ucRet = 0;  // filter closed by default
  uint32 ulCurTimeDif = 0;


  if ( (ucTelType == cTelTypeSELPAL) ||  (ucTelType == cTelTypeSELPAL1) || (ucTelType == 0x00) || (ucTelType == 0x20) || (ucTelType == 0x01) || (ucTelType == 0xC3) || (ucTelType == 0xC1) || (ucTelType == 0xCA))
  {
    ucIx = ucTelStatGetIDPosInTable( (uint32)ulID );

    if (ucIx < cTableSize)
    {
	    ulCurTimeDif = ulSysTime >= ulTelStatGetLastRxTime((uint32)ulID ) ? ulSysTime - ulTelStatGetLastRxTime((uint32)ulID ) :  cTimeOverFlow +  ulSysTime - ulTelStatGetLastRxTime((uint32)ulID ); // time diff assuming max time value can't excedd 0xFF
      if ((ulTelStatGetLastRxTime((uint32)ulID ) == 0) || (ulCurTimeDif > ((uint32) ushTimeFilterInMilliSec)))
      {
        ucRet = 1; // pass       
      }
    }
    else
    {
      ucRet = 1; // first received telegram of this ID
    }
  }
  else
  {
      ucRet = 0;  // all other telegrams are blocked since not supported in the project
  }

  return (ucRet);
}


/*____________________________________provided interface_________________________________________________*/
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
