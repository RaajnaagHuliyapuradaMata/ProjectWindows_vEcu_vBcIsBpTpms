/*
(c)  Electronics GmbH     BEE1     11/2015
================================================================================================

file name:     DAG_TVWarn.c

file status:   fine

------------------------------------------------------------------------------------------------

author:        Peter Brand                 Electronics GmbH

intials:       pb

Purpose:
temperature speed warning implementation according to TPMS Logic  PAL2 V1.2


*/
/*******************************************************************************
Declaration
*/

/*******************************************************************************
Include
*/
#include "global.h"
#include "USWarnX.h"
#include "DAG_TVWarn.h"
#include "WallocX.h"
#include "WnTypePar.h"



/*******************************************************************************
Macros
*/

#define HtWrnWhite (uint8) 0
#define HtWrnYellow (uint8) 1
#define HtWrnRed (uint8) 2

#define TimeDel4RedSpeedInSec 120   // for more than 2 minutes

/*******************************************************************************
Data
*/
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

/*******************************************************************************
prototipicos locale
*/
static sint8 i8GetMaxT(void);
static void IncHCt(uint8 ui8Inc);
static void DecHCt(uint8 ui8Dec);
static uint16 ui16CombinedVehicleSpeed(const uint16 ui16SpeedInKmh);
static uint8 ui8RedSpeed(uint16 ui16FilteredSpeed, sint8 i8Temp ); // call cycle must be 1sec
static uint8 ui8GetWrnClr(sint8 i8Temp);
/*******************************************************************************
Implementation
*/
/*******************************************************************************
private functions
*/
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
  ui16HeatCt = (ui16HeatCt + ui8Inc > tDAG_TemPara .ui16_HC_MAX) ? tDAG_TemPara .ui16_HC_MAX:(ui16HeatCt + ui8Inc); //see TPMS Logic  PAL2 V1.3 chap 2.4 HC_MAX MAXIMUM VALUE for Heat Counter
}

static void DecHCt(uint8 ui8Dec)
{
  ui16HeatCt = (ui16HeatCt > (uint16) ui8Dec) ? (ui16HeatCt - (uint16) ui8Dec):0;
}

// ui16CombinedVehicleSpeed
// purpose:
// 7.1.2 Combined vehicle speed
//  combined vehicle speed: v = MIN (v_unfiltered, v_filtered)
//  v_filtered shall be created using a PT1-filter with time constant of 150 seconds:
//  v_filtered = (v_unfiltered + 149 * v_filtered) / 150
//  At increasing speed the combined speed signal follows slowly. When the current speed is lower than the filtered speed, the combined
//  signal follows immediately.
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

static uint8 ui8RedSpeed(uint16 ui16FilteredSpeed, sint8 i8Temp ) // call cycle must be 1sec
{
    uint8 ui8Ret = (uint8) 0;

    if (tDAG_TemPara .ui16_HC_MAX == ui16HeatCt )
    {
        if (ui16RedSpeedCt < TimeDel4RedSpeedInSec )
            ui16RedSpeedCt++;
        else if ((tDAG_TemPara .ui16_V3 < ui16FilteredSpeed) && (tDAG_TemPara .i8_T2 <= i8Temp)) // set condition
            ui8Ret = (uint8) 1;
        else if ((ui8RedSpeedActive > 0) && (tDAG_TemPara .ui16_V1 < ui16FilteredSpeed ))    // hysteresis
            ui8Ret = (uint8) 1;
    }
    else
        ui16RedSpeedCt = 0;

    return (ui8Ret);
}
/*******************************************************************************
public functions
*/
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


void CheckTVWarnAllSec(uint16 ui16SpeedInKmh)   // treat heat counter following the rules of DAG's 7.1.1 Rules for incrementing and decrementing the counter
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
      IncHCt (1); // new in TPMS Logic PAL2 V1.4.docx
  }
  else // v > V3
  {
    if (tDAG_TemPara .i8_T1 > i8MaxTemp )
      DecHCt (1);
    else if (tDAG_TemPara .i8_T2 < i8MaxTemp)
      ui16HeatCt = tDAG_TemPara .ui16_HC_MAX ;
    else  // T1 <= t_max <= T2
      IncHCt (3);
  }

  if (tDAG_TemPara.i8_T0 > i8MaxTemp )
    ui8OHWActive = (uint8) 0;                       // see TPMS Logic  PAL2 V1.3 chap. 7.1.4 Temperature Warning Condition
  else if (tDAG_TemPara .ui16_HC_MAX <= ui16HeatCt) 
    ui8OHWActive = (uint8) 1;                       // see TPMS Logic  PAL2 V1.3 chap. 7.1.4 Temperature Warning Condition

  ui8RedSpeedActive = ui8RedSpeed(ui16FilteredSpeed, i8MaxTemp );
}

void PuT(uint8 ui8Ix, sint8 i8T)
{
 if ( ui8Ix  < ucSumWEc)
     i8CurT[ui8Ix ] = i8T;
  
}

uint8 ui8OvrHeatWrnIsActive(void)     //0= no méssage, 1 = over eat , 2 = reduce speed
{
    if (tDAG_TemPara .ui8_TempWarnEnable > (uint8) 0)
        if (ui8RedSpeedActive > (uint8) 0)
            return ((uint8) 2);
        else
            return ((ui8OHWActive > (uint8) 0 ) ? (uint8) 1: (uint8) 0);
    else
        return ((uint8) 0); // disabled
}

uint8 ui8GetOvrHeatId(uint8 * pui8ZPos) // returns amount of OverHeatWarning affected zom IDs [0..4], writes affected IDs to pui8ZPos [0..3] low nibble and warn colour to high nibble
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

// uint8 ui8GetTempColeurWP(const uint8 ui8WP) and uint8 ui8GetTempColeurWP_xx(void)
// purpose: returns: last received sensor's temperature color according to 7.2 CAN-Signals for Temperature Warning
//                   0xFF if wheel position is not available
//          [parameter: ui8WP = 0,1..3 = FL,FR..RR, 4 unspecific wheel position returns max temperature's colour ]
uint8 ui8GetTempColeurWP(const uint8 ui8WP)
{
    uint8 i;
    sint8 i8Max = i8GetMaxT();
    
    if (ui8WP > ucWPRRc )   // wheel position undefined ?
    {
        return (ui8GetWrnClr(i8Max));
    }
    else  // wheel position specific
    {
        for (i = 0; i < ucSumWEc ;i++)
        {
            if (ui8WP == ucGetWPOfCol(i))
                break;
        }
        
        if ( ucSumWEc == i)
        {
            return ((uint8) 0xFF);  // wheel position not available
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

/******************************************************************************/