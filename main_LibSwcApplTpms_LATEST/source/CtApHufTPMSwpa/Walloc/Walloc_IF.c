/**************************************************************************************************
 *(c) Beru Electronics GmbH     BEE1     01/2004
 *================================================================================================
 *
 *$Archive: /LIB/WAF/work/Walloc_IF.c $
 *
 *file name:     WAeeiface.c
 *
 *file status:   under construction
 *
 *------------------------------------------------------------------------------------------------
 *
 *author:        Peter Brand                Beru Electronics GmbH
 *
 *intials:       pb
 *
 *Modul Description
 *
 *Global description:
 *Purpose:
 *interface module for tss basic component
 *
 *Modul Modification
 *changes in 2004
 *
 *$Log: /LIB/WAF/work/Walloc_IF.c $
 * 
 * 41    21.08.12 17:52 Peter
 * new module structure (FPA and AEC, CA seperated)
 * 
 * 40    10.08.12 10:10 Peter
 * new test module structure
 * 
 * 39    9.08.12 15:37 Peter
 * forgotten comment marks
 * 
 * 38    9.08.12 15:26 Peter
 * bugfix recalculate RefPoint at ABS overflow with 65536 (not 65535 !!)
 * TDL tab for 1sensor version 15 4 2
 * 
 * 37    27.07.12 11:48 Peter
 * new table for IAT and new sensor SW XXX???
 * 
 * 36    29.06.12 15:00 Peter
 * new ABS-counters-access function for 180° delayed FixPoint Huf
 * telegrams 
 * minimum waystretch set to 500m (again)
 * 
 * 35    24.05.12 16:52 Peter
 * IAT
 * walloc prepared 4 Conti tels
 * 
 * 34    21.05.12 9:28 Peter
 * new parameter value 4 way stretch
 * 
 * 33    7.02.12 15:08 Peter
 * ABS signal overflow protection not coupled to RF tel reception 
 * must now be detected actively at ABS signal reception (CAN cylce)
 * 
 * 32    27.01.12 15:58 Rapp
 * Ausputzen ...
 *
 * 31    23.01.12 18:29 Peter
 *
 * 30    23.01.12 18:17 Rapp
 * Datentyp der ABS-Zählvariablen von 8- auf 16-Bit geändert (Problem
 * HW-Reset !!!)
 *
 * 29    19.01.12 18:55 Rapp
 * ABS-Linearisierung
 *
 * 28    17.01.12 13:55 Peter
 * 1st runable common Peak and FixPos allocation
 *
 * 27    11.01.12 19:07 Peter
 * backup only
 *
 * 26    5.01.11 10:12 Peter
 * amount of ZOM variables reduced 4 target version
 *
 * 25    6.12.10 10:19 Peter
 * FW access fix
 *
 * 24    1.12.10 11:35 Peter
 * support FW
 *
 * 23    18.11.10 17:29 Peter
 * voerhand corrected edge count delta information to WA algo
 *
 * 22    17.11.10 15:55 Peter
 * replace waystretch by ABStick
 *
 * 21    17.11.10 12:00 Peter
 * simulation and TSS basic structure repaired
 *
 * 20    12.10.10 16:33 Schoenbeck
 * erste Version mit Abrolllängenkriterium
 * Achtung histmem wurde wegen RAM-Knappheit deaktiviert!
 *
 * 19    16.09.10 17:53 Peter
 * refactored
 * optimized active sync of edge count sum
 * optimzed delta generation
 *
 * 18    27.08.10 16:57 Peter
 * Concept III/1 implemented
 *
 * 17    29.07.10 15:02 Peter
 * version with 1st concept (dT)
 *
 * 16    27.07.10 10:47 Peter
 * 1te Version lauffähig
 *
 * 15    21.07.10 18:09 Peter
 * tel TO implemented
 *
 * 14    21.07.10 17:55 Peter
 * implement the waystretch call
 *
 * 13    21.07.10 16:17 Peter
 * 1st WAF implementation with no WAF core
 *
 */

/**************************************************************************************************
 *Include
 */

#include "Walloc_IF.h"
#include "WAllocX.h"
#include "abs_linX.h"
#include "cd_decoder_x.h"
#include "watcfX.h"
#include "tel_statisticX.h"

#include "Rte_CtApHufTPMSwpa.h"
//#include "Appl_TPMS_DCM.h" declaration causes compiler error-> use bad pseudo declaration:
extern uint8 GETucLqiOfRam(void);



/**************************************************************************************************
 *public functions
 */
/**************************************************************************************************
 *Function GetDataEE()
 *
 *Description
 *
 *Purpose:                       returns content of eeprom
 *-----------------------------------------------------------------------------------------------
 *Input:           ucId : specific id for specific eeprom content
 *							   pAdr	: ram address to save data of ee
 *							   ucLen: length in bytes to read from ee to ram
 *
 *Output:
 *------------------------------------------------------------------------------------------------
 */
void GetWADataEE(unsigned char ucId, unsigned char *pRamAdr, unsigned char ucLen)
{
unsigned char i;

switch(ucId)
  {
  case cWAParameter:
    {
      for (i=0;i < ucLen;i++)
      {
        *pRamAdr = GETtWAparam(i);
        pRamAdr++;
      }
    }
    break;
  case cHistorySet1:
    {
      for (i=0;i < ucLen;i++)
      {
        *pRamAdr = GETucWAHistID(i);
        pRamAdr++;
      }
    }
    break;
  case cHistoryWPSet1:
    {
      for (i=0;i < ucLen;i++)
      {
        *pRamAdr = GETucWAHistWP(i);
        pRamAdr++;
      }
    }
    break;

  default:
    break;
  }
}
/**************************************************************************************************
 *Function PutDataEE()
 *
 *Description
 *
 *Purpose:         writes data from ram to eeprom
 *-----------------------------------------------------------------------------------------------
 *Input:           ucId : specific id for specific eeprom content
 *							   pAdr	: ram address to save data of ee
 *							   ucLen: length in bytes to read from ee to ram
 *
 *Output:
 *------------------------------------------------------------------------------------------------
 */
void PutWADataEE(unsigned char ucId, unsigned char *pRamAdr, unsigned char ucLen)
{
  unsigned char i;
  unsigned char ucChange = (unsigned char) 0;

  switch(ucId)
  {
  case cWAParameter:
    {
      for (i=0;i < ucLen;i++)
      {
        if (GETtWAparam(i) != *pRamAdr)
        {
          PUTtWAparam( *pRamAdr,i );
          ucChange++;
        }
        pRamAdr++;
      }
    }
    break;
  case cHistorySet1:
    {
      for (i=0;i < ucLen;i++)
      {
        if (GETucWAHistID (i) != *pRamAdr)
        {
          PUTucWAHistID( *pRamAdr,i );
          ucChange ++;
        }
        pRamAdr++;
      }
    }
    break;
  case cHistoryWPSet1:
    {
      for (i=0;i < ucLen;i++)
      {
        if (GETucWAHistWP (i) != *pRamAdr )
        {
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
  if (ucChange > ((unsigned char) 0))
  {
    SetWaData2NvmFlag();
  }
#endif
}


/*!**********************************************************************************************************
 *\Function           static void GetABSTick( void )
 *
 *\Typ                publique
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Purpose            put current way stretch information (wheel pos FR..RR [0..3]) from CAN to the ush array
 *                     with time stamp ([4])
 *
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\SW_Requirements    none
 *
 * ----------------------------------------------------------------------------------------------------------
 *
 *\Parameter          pointer 2 ush array
 *
 *
 *\Output             array
 *
 *
 ************************************************************************************************************/

unsigned char ucGetABSTick(unsigned short * p2aushABS)
{
   //  ACHTUNG: receive GetWayStrectch gibt 0 zurück wenn Ergbenis OK, andernfalls 0 !!!
   // TBD GLo: Function not used, to be removed??

  uint8  ucRet;

  ucRet = GetLinABS( p2aushABS );

  if( ucRet == cABS_OK )
  {
    ucRet = (unsigned char) 1;
  }
  else
  {
    ucRet = (unsigned char) 0;
  }

  return ucRet;
}


unsigned short ushGetABSingleTick(unsigned char ucIx)
{

  unsigned char  ucRet;
  unsigned short ushCnt[4];
  unsigned short ushCurrentAbsTick;
  ucRet = GetLinABS( ushCnt );

  if (ucRet == cABS_OK)
  {

    ushCurrentAbsTick = ushCnt[ucIx];
  }
  else
  {
    ushCurrentAbsTick = cABSStickError;
  }

  return ( ushCurrentAbsTick );

}


unsigned char ucGetSpeed(void)
{

    extern unsigned short ushV;

	if (ushV > 255)
		return ((unsigned char) 255);
	else
		return ((unsigned char) ushV);

}

unsigned char ucNoWheelSensorMounted(void)
{
#ifdef WAModulTest
  return 0;
#else
  return ((FAILURE_MODE_noWE == ucGetFailureState()) ? (unsigned char) 1:(unsigned char) 0); 
#endif
}
void WAStatusChangedEvent(unsigned short ushWAState)
{
#ifndef WAModulTest		  
  Rte_Write_PP_WAState_DE_ushWAState(ushWAState);
#endif
}

unsigned char ucDAG_LQIParameter(void)
{
#ifdef WAModulTest
  return 0;
#else
  return GETucLqiOfRam();
#endif
}
