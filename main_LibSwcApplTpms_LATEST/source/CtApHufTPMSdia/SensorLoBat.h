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

#ifndef SensorLoBat_H
#define SensorLoBat_H


/*******************************************************************************
Macros
*/

#define cMAXWU4BATINFO (uint8) 4
////////////////////////////////////////////////////////////////////////////////
// tipicos
#pragma pack(1)
typedef struct {
  uint32 ui32ID;
  uint8  ui8Status;     // 1 = NOK, 0 = OK
  uint8  ui8LifeInPercent;  // only lower 4 bit used (1 = 10%)
  uint16 ui16Odometer;  // hi - lo (moto) byte order = 0...0xFFFE = 16 x km, 0xFFFF = n.a.
  uint8  ui8AmbienTemp; // 0xFF = n.a., 1..FE = x - 50°C , 0 = 999°C
  uint8  ui8SensorTemp; // 0xFF = n.a., 1..FE = x - 50°C , 0 = 999°C
  uint8  ui8Count;      // 0..15 (events of received low battery telegrams of this sensor)
} BaType;
#pragma pack()

/*******************************************************************************

Data
*/

/*******************************************************************************
private functions
*/

/*******************************************************************************
public functions
*/

extern void InitSensorLoBat(void);
extern void CheckSensorLoBat(uint8 idx, uint8 ui8BatteryStatus, boolean bForceInit);
extern BaType GETtSensorBatInfOfRam(uint8 idx);

extern void ClearAllBatStatCounts(void);

extern void PrepareLoBat4Obsolescence(uint8 * p2dat);
extern void ClearAllParaApartId(void);

#endif
/******************************************************************************/
