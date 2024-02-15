/*
(c)  Electronics GmbH     BEE1     08/2016
================================================================================================

file name:     RemTransp.c

file status:   fine

------------------------------------------------------------------------------------------------

author:        Peter Brand                 Electronics GmbH

intials:       pb

Purpose:
asynchron diagnostic routine $0302 to check reception of any triggered sensor  according to TPMS Logic  PAL2 V1.5 implementation's interface 


*/
#include "Platform_Types.h"

#ifndef RemTransp_H
#define RemTransp_H


/*******************************************************************************
Macros
*/

/*******************************************************************************
Data
*/
#pragma pack(1)
typedef struct
{
  uint32 ui32ID;
  uint8 ui8P;
  uint8 ui8Temp;
  uint8 ui8Method;  // 0 = remeasure, 1 = transpondere
} RemTranspResulType;
#pragma pack()
/*******************************************************************************
private functions
*/

/*******************************************************************************
public functions
*/
extern void StartRoutine302(uint8 ui8Meffed);
extern void StopRoutine302(void);
extern void Check4RemOrTrig(uint32 ui32ID, uint8 ui8P, uint8 ui8T, uint8 ui8TxTrig, uint8 ui8Mode);
extern RemTranspResulType GETtRemTranspResult(void);
extern uint8 GETui8RemTranspActive(void);


#endif
/******************************************************************************/
