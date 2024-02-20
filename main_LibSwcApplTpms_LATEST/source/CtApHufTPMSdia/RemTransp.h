
#include "Platform_Types.h"

#ifndef RemTransp_H
#define RemTransp_H

#pragma pack(1)
typedef struct
{
  uint32 ui32ID;
  uint8 ui8P;
  uint8 ui8Temp;
  uint8 ui8Method;
 } RemTranspResulType;
#pragma pack()

extern void StartRoutine302(uint8 ui8Meffed);
extern void StopRoutine302(void);
extern void Check4RemOrTrig(uint32 ui32ID, uint8 ui8P, uint8 ui8T, uint8 ui8TxTrig, uint8 ui8Mode);
extern RemTranspResulType GETtRemTranspResult(void);
extern uint8 GETui8RemTranspActive(void);

#endif

