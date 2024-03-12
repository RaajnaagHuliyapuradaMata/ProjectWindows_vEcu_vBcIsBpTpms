
#include "Platform_Types.h"

#ifndef SensorLoBat_H
#define SensorLoBat_H

#define cMAXWU4BATINFO (uint8) 4
 #pragma pack(1)
typedef struct {
  uint32 ui32ID;
  uint8  ui8Status;
   uint8  ui8LifeInPercent;
   uint16 ui16Odometer;
   uint8  ui8AmbienTemp;
   uint8  ui8SensorTemp;
   uint8  ui8Count;
 } BaType;
#pragma pack()

extern void InitSensorLoBat(void);
extern void CheckSensorLoBat(uint8 idx, uint8 ui8BatteryStatus, boolean bForceInit);
extern BaType GETtSensorBatInfOfRam(uint8 idx);

extern void ClearAllBatStatCounts(void);

extern void PrepareLoBat4Obsolescence(uint8* p2dat);
extern void ClearAllParaApartId(void);

#endif

