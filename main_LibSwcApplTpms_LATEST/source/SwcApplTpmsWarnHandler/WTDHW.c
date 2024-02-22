

#include "global.h"
#include "uswarn.h"
#include "WnTypePar.h"
#include "uswarn_Ifx.h"

#define P_GRAD ((uint8) 8)
 #define cFPLStarTimeInSec ((uint8) 120)

static uint8 ui8GradSurpassed(uint8 ui8Ix, uint8 ui8P);
static void RewindFPLTimer(uint8 ui8Ix);
static uint8 ui8FPLTime(uint8 ui8Ix);

static uint8 aucLastPressureM1DHW[ucSumWEc];
static uint8 aui8DpEvCt[ucSumWEc ];
static uint8 ui8FPLTimer[ucSumWEc] = {(uint8) 0,(uint8) 0,(uint8) 0,(uint8) 0};

void ResetM1Pressure(uint8 i)
{
  if (i < ucSumWEc)
  {
    aucLastPressureM1DHW[i] = 0;
  }
  else
  {
    for ( i = 0; i < ucSumWEc; i++ )
    {
      aucLastPressureM1DHW[i] = 0;
    }
  }
}

uint8 * pui8GetLastM1Pressure(void)
{
  return (aucLastPressureM1DHW);
}

uint8 bDHW( struct LocalWarnDat *ptLWD, uint8 ucWarnCfg)
{
  uint8 ui8CompRes,ui8Ret;
  uint16 ushHelp;
  ushHelp = (uint16) ptLWD->tHFD.tHF.scTWE + ush273Kelvinc;
  ui8CompRes = ucPfT((uint16) (ptLWD->tSD.ushMSoll - ushMIso(ucDP_TOLERANCEc, ptLWD->tSD.scTSoll )), ushHelp) ;
  ptLWD->ucCurWarnLevel = aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId];

  if (ucGetWarnBitWN (ptLWD->tHFD.tHF.ucId, ucDHWIxc) == 1)
   {
    if ( ptLWD ->tHFD .tHF .ucP  <= ui8CompRes )
    {
      return ((uint8) 1);
    }
  }

  ui8Ret = (uint8) 0;
  if ((uint8) 0 < aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId])
  {
    if ( ptLWD->tHFD .tHF.ucP < aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId] )
     {
      if (ui8GradSurpassed(ptLWD->tHFD.tHF.ucId, ptLWD->tHFD .tHF.ucP) > (uint8) 0)
       {
        aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId] = ptLWD->tHFD .tHF.ucP;
        RewindFPLTimer (ptLWD->tHFD.tHF.ucId);
        if (aui8DpEvCt [ptLWD->tHFD.tHF.ucId] > (uint8) 0 )
        {
          if (0 == ucGetWarnBitWN (ptLWD->tHFD.tHF.ucId,ucSFactorIxc))
             return ((uint8) 0);
          if (ptLWD->tHFD .tHF.ushVehicleSpeed > 0)
             return (ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc));
          else
            if ( ptLWD->tHFD.tHF.ucP <= ((ptLWD ->PRefMin > ucDP_TOLERANCEc) ? (ptLWD ->PRefMin - ucDP_TOLERANCEc):ucDP_TOLERANCEc) )
               return (ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc));
            else
              return ((uint8) 0);
        }
        else
        {
          aui8DpEvCt [ptLWD->tHFD.tHF.ucId]++;
          return ((uint8) 0);
        }
      }
    }
  }

   aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId] = ptLWD->tHFD.tHF.ucP;
  aui8DpEvCt [ptLWD->tHFD.tHF.ucId] = 0;
  RewindFPLTimer (ptLWD->tHFD.tHF.ucId);
  ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucDHWIxc);
  ptLWD->ucCurWarnLevel = aucLastPressureM1DHW[ptLWD->tHFD.tHF.ucId];
  return((uint8) 0);
}

void CtFPLTimer(void)
{
  uint8 i;

  for (i = ((uint8) 0); i < ucSumWEc; i++  )
  {
    if (ui8FPLTimer[i] > ((uint8) 0))
    {
      ui8FPLTimer[i]--;
    }
  }
}

static void RewindFPLTimer(uint8 ui8Ix)
{
  if ( ui8Ix < ucSumWEc )
  {
    ui8FPLTimer[ui8Ix] = cFPLStarTimeInSec;
  }
}

static uint8 ui8GradSurpassed(uint8 ui8Ix, uint8 ui8P)
{
  uint16 ui16Grad;
  uint8 ui8Ret = ((uint8) 0);

  if (ui8Ix < ucSumWEc )
  {
    if (ui8FPLTime(ui8Ix) > ((uint8) 0))
    {
      if (ui8P < aucLastPressureM1DHW [ui8Ix])
      {
        ui16Grad = (uint16) (aucLastPressureM1DHW [ui8Ix] - ui8P);
        ui16Grad <<= 6;
        ui16Grad /= ui8FPLTime(ui8Ix);
        if (8 < ui16Grad)
        {
          ui8Ret = (uint8) 0xFF;
        }
      }
    }
  }

  return ui8Ret;
}

static uint8 ui8FPLTime(uint8 ui8Ix)
{
  uint8 ui8TDif = (uint8) 0;

  if (ucSumWEc > ui8Ix)
  {
    ui8TDif = cFPLStarTimeInSec - ui8FPLTimer[ui8Ix];
  }

  return((cFPLStarTimeInSec == ui8TDif) ? (uint8) 0:ui8TDif);
}
