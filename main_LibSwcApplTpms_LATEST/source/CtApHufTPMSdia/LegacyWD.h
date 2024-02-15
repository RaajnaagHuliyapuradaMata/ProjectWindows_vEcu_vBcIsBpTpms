/*
(c)  Electronics GmbH     BEE1     08/2016
================================================================================================

file name:     SensorLoBat.c

file status:   fine

------------------------------------------------------------------------------------------------

author:        Peter Brand                 Electronics GmbH

intials:       pb

Purpose:
sensor low battery diagnostice logic  according to TPMS Logic  PAL2 V1.5 implementation's interface 


*/
#include "Platform_Types.h"

#ifndef LegacyWD_H
#define LegacyWD_H


/*******************************************************************************
Macros
*/
//#define TestPin4WD
#define WDTime4sec  // !!! must be active 4 delivery !!!
/*******************************************************************************
Data
*/

/*******************************************************************************
private functions
*/

/*******************************************************************************
public functions
*/

extern void TriggerLegacyWD1(void);
extern void InitLegacyWD1(void);

extern void TriggerLegacyWD0(void);
extern void InitLegacyWD0(void);

extern void ShowWDTrigger(void);
#endif
/******************************************************************************/
