

#include "global.h"
#include "USWarnX.h"
#include "DAG_TVWarn.h"
#include "WallocX.h"
#include "WnTypePar.h"

#define HtWrnWhite (uint8) 0
#define HtWrnYellow (uint8) 1
#define HtWrnRed (uint8) 2

#define TimeDel4RedSpeedInSec 120

static sint8 i8CurT[ucSumWEc ] = {-127,-127,-127,-127};
static uint16 ui16HeatCt = 0;
#ifdef SPEED_FILTER_IN_FLOAT
static float32 f32FilterSpeed = 0;
#else
static uint16 ui16FilterSpeed = 0;
#endif
static uint8 ui8RedSpeedActive = 0;
static uint8 ui8OHWActive = 0;
static uint16 ui16RedSpeedCt = 0;

static sint8 i8GetMaxT(void);
static void IncHCt(uint8 ui8Inc);
static void DecHCt(uint8 ui8Dec);
static uint16 ui16CombinedVehicleSpeed(const uint16 ui16SpeedInKmh);
static uint8 ui8RedSpeed(uint16 ui16FilteredSpeed, sint8 i8Temp );
 static uint8 ui8GetWrnClr(sint8 i8Temp);

static sint8 i8GetMaxT(void)
{
    uint8 i;
    sint8 i8Max = -127;

    for (i = 0; i < ucSumWEc ; i++)
    {
        if (i8CurT[i] > i8Max)
        {
            i8Max = i8CurT[i];
        }
    }

    return (i8Max);
}

static void IncHCt(uint8 ui8Inc)
{
  ui16HeatCt = (ui16HeatCt + ui8Inc > tDAG_TemPara .ui16_HC_MAX) ? tDAG_TemPara .ui16_HC_MAX:(ui16HeatCt + ui8Inc);
 }

static void DecHCt(uint8 ui8Dec)
{
  ui16HeatCt = (ui16HeatCt > (uint16) ui8Dec) ? (ui16HeatCt - (uint16) ui8Dec):0;
}

    #ifdef SPEED_FILTER_IN_FLOAT
static uint16 ui16CombinedVehicleSpeed(const uint16 ui16CurSpeed)
{
    float32 f32CurSpeed = (float32) ui16CurSpeed;

    f32FilterSpeed = ((149*f32FilterSpeed + f32CurSpeed) / 150);

    if (f32CurSpeed < f32FilterSpeed)
    {
        return (ui16CurSpeed);
    }
    else
    {
        return ((uint16) f32FilterSpeed);
    }
}
#else
static uint16 ui16CombinedVehicleSpeed(uint16 ui16CurSpeedInKmh)
{
    uint16 ui16ShiftSpeed;

    if ( ui16CurSpeedInKmh > 511)
        ui16CurSpeedInKmh = 511;

    ui16ShiftSpeed = ui16CurSpeedInKmh<<7;

    ui16FilterSpeed = ui16FilterSpeed + (uint16) ((ui16ShiftSpeed - ui16FilterSpeed)/150);

    ui16ShiftSpeed = ui16FilterSpeed>>7;

    if (ui16CurSpeedInKmh < ui16ShiftSpeed)
    {
        return (ui16CurSpeedInKmh);
    }
    else
    {
        return (ui16ShiftSpeed);
    }
}
#endif
static uint8 ui8GetWrnClr(sint8 i8Temp)
{
    if (tDAG_TemPara .i8_T1 <= i8Temp )
    {
        return HtWrnRed;
    }
    else if ( tDAG_TemPara .i8_T0 > i8Temp)
    {
        return HtWrnWhite ;
    }
    else
    {
        return HtWrnYellow ;
    }
}

static uint8 ui8RedSpeed(uint16 ui16FilteredSpeed, sint8 i8Temp )
 {
    uint8 ui8Ret = (uint8) 0;

    if (tDAG_TemPara .ui16_HC_MAX == ui16HeatCt )
    {
        if (ui16RedSpeedCt < TimeDel4RedSpeedInSec )
            ui16RedSpeedCt++;
        else if ((tDAG_TemPara .ui16_V3 < ui16FilteredSpeed) && (tDAG_TemPara .i8_T2 <= i8Temp))
             ui8Ret = (uint8) 1;
        else if ((ui8RedSpeedActive > 0) && (tDAG_TemPara .ui16_V1 < ui16FilteredSpeed ))
             ui8Ret = (uint8) 1;
    }
    else
        ui16RedSpeedCt = 0;

    return (ui8Ret);
}

void IniTVWarn(void)
{
    ui16HeatCt = 0;
    i8CurT[0] = -127;
    i8CurT[1] = -127;
    i8CurT[2] = -127;
    i8CurT[3] = -127;

#ifdef SPEED_FILTER_IN_FLOAT
    f32FilterSpeed = 0;
#else
    ui16FilterSpeed = 0;
#endif

    ui8OHWActive = 0;
    ui8RedSpeedActive = 0;
    ui16RedSpeedCt = 0;
}

void IniTVWarnAtKL15Off(void)
{
    ui16HeatCt = 0;

#ifdef SPEED_FILTER_IN_FLOAT
    f32FilterSpeed = 0;
#else
    ui16FilterSpeed = 0;
#endif

    ui8OHWActive = 0;
    ui8RedSpeedActive = 0;
    ui16RedSpeedCt = 0;
}

void CheckTVWarnAllSec(uint16 ui16SpeedInKmh)
 {
  sint8 i8MaxTemp = i8GetMaxT();
  uint16 ui16FilteredSpeed = ui16CombinedVehicleSpeed(ui16SpeedInKmh);

  if (tDAG_TemPara .ui16_V1 >= ui16FilteredSpeed)
    if (tDAG_TemPara .i8_T2 < i8MaxTemp)
      DecHCt (1);
    else
      ui16HeatCt = 0;
  else if (tDAG_TemPara .ui16_V2 >= ui16FilteredSpeed)
  {
    if (tDAG_TemPara .i8_T1 > i8MaxTemp )
      ui16HeatCt = 0;
    else if (tDAG_TemPara .i8_T2 < i8MaxTemp)
      IncHCt (1);
  }
  else if (tDAG_TemPara .ui16_V3 >= ui16FilteredSpeed )
  {
    if ( tDAG_TemPara .i8_T1 > i8MaxTemp )
      DecHCt (1);
    else if ( tDAG_TemPara .i8_T2 < i8MaxTemp )
      IncHCt (3);
    else
      IncHCt (1);
   }
  else
   {
    if (tDAG_TemPara .i8_T1 > i8MaxTemp )
      DecHCt (1);
    else if (tDAG_TemPara .i8_T2 < i8MaxTemp)
      ui16HeatCt = tDAG_TemPara .ui16_HC_MAX ;
    else
       IncHCt (3);
  }

  if (tDAG_TemPara.i8_T0 > i8MaxTemp )
    ui8OHWActive = (uint8) 0;
   else if (tDAG_TemPara .ui16_HC_MAX <= ui16HeatCt)
    ui8OHWActive = (uint8) 1;

  ui8RedSpeedActive = ui8RedSpeed(ui16FilteredSpeed, i8MaxTemp );
}

void PuT(uint8 ui8Ix, sint8 i8T)
{
 if ( ui8Ix  < ucSumWEc)
     i8CurT[ui8Ix ] = i8T;

}

uint8 ui8OvrHeatWrnIsActive(void)
 {
    if (tDAG_TemPara .ui8_TempWarnEnable > (uint8) 0)
        if (ui8RedSpeedActive > (uint8) 0)
            return ((uint8) 2);
        else
            return ((ui8OHWActive > (uint8) 0 ) ? (uint8) 1: (uint8) 0);
    else
        return ((uint8) 0);
 }

uint8 ui8GetOvrHeatId(uint8 * pui8ZPos)
 {
    uint8 i,j = (uint8) 0;
    sint8 i8Max = i8GetMaxT();

    if (tDAG_TemPara .ui8_TempWarnEnable > (uint8) 0)
    {
        if (ui8OHWActive > (uint8) 0  )
        {
            for (i = 0; i < ucSumWEc ; i++)
            {
                if (i8Max == i8CurT [i])
                {
                    pui8ZPos [j++] = i | ((uint8) (ui8GetWrnClr(i8Max)<<4));
                }
            }
        }
    }

    return (j);
}

  uint8 ui8GetTempColeurWP(const uint8 ui8WP)
{
    uint8 i;
    sint8 i8Max = i8GetMaxT();

    if (ui8WP > ucWPRRc )
     {
        return (ui8GetWrnClr(i8Max));
    }
    else
     {
        for (i = 0; i < ucSumWEc ;i++)
        {
            if (ui8WP == ucGetWPOfCol(i))
                break;
        }

        if ( ucSumWEc == i)
        {
            return ((uint8) 0xFF);
         }
        else
        {
            return (ui8GetWrnClr(i8CurT [i]));
        }
    }
}
uint8 ui8GetTempColeurWP_FL(void)
{
    return(ui8GetTempColeurWP(ucWPFLc));
}
uint8 ui8GetTempColeurWP_FR(void)
{
    return(ui8GetTempColeurWP(ucWPFRc));
}
uint8 ui8GetTempColeurWP_RL(void)
{
    return(ui8GetTempColeurWP(ucWPRLc));
}
uint8 ui8GetTempColeurWP_RR(void)
{
    return(ui8GetTempColeurWP(ucWPRRc));
}
uint8 ui8GetTempColeurWP_UK(void)
{
    return(ui8GetTempColeurWP(4));
}

uint16 ui16GetFilterSpeedInKmh(void)
{
  return ((uint16) (ui16FilterSpeed>>7));
}
uint16 ui16GetOvrHeatCt(void)
{
  return ( ui16HeatCt );
}
uint16 ui16GetCombVSpeed(uint16 ui16CurVehSpeed)
{
  if (ui16CurVehSpeed <  (ui16FilterSpeed>>7))
    return (ui16CurVehSpeed);
  else
   return (ui16FilterSpeed>>7);
}
uint16 ui16GetSpeedCtInSec(void)
{
  return ui16RedSpeedCt;
}

