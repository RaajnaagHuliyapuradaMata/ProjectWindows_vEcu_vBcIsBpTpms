
#include "Platform_Types.h"

#ifndef SensorMeasError_H
#define SensorMeasError_H

#ifdef SensorMeasError_C

void SetMeasError(uint8 ui8HistCol);
#else

extern void ClrMeasError(uint8 ui8HistCol, uint8 ui8ReasonOnly);
extern void CheckSensorPnT(uint8 ui8HistCol, uint8 ui8AKRawPressure, uint8 ui8AKRawTemp, boolean ui8AddCondition, uint8 ui8TT);
extern uint8 GetMeasErrorPCt(uint8 ui8HistCol);
extern uint8 GetMeasErrorTCt(uint8 ui8HistCol);
extern boolean bSensorDefect(uint32 ui32ID, uint8 ui8TT, uint8 ui8P, uint8 ui8T);
#endif

#endif

