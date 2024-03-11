

#ifndef _eecate_ifX_H
#define _eecate_ifX_H

#include "tss_stdx.h"

typedef struct typedef_struct_tCalDataPair
{
  uint8 ucPressure;
  sint8 scTemperature;
} tCalDataPair;

typedef struct typedef_struct_tMirroredRamCatEDecl
{
  tCalDataPair tFillValueCAL[5];
  tCalDataPair tRatedValueCAL[2][5];

  uint8 ucForgottenReset;

  uint8 ucWAHistIDSet[cMaxLR * sizeof(uint32)];
  uint8 ucWAHistWPSet[cMaxLR];

  uint8  ucCalRequestCAL;
  uint8  ucCalNotAckCAL;
  uint8  ucFolgeAusfallCnt[5];

  uint8  ucResettingTpms;

#if(BERU_BAUREIHE_BMW_PL4_ENABLE == ON)
  uint8 ucReserved[10];

#endif

#if(BERU_BAUREIHE_BMW_PL6_ENABLE == ON)
  uint8 ucPresUnit;
  uint8 ucTempUnit;

#endif

  uint8 ucHistWarningStateBAK;
} tMirroredRamCatEDecl;

extern void InitEECATE( void );

extern uint8 GETucFillValuePressureEE( uint8 );
extern void PUTucFillValuePressureEE( uint8 , uint8 );

extern sint8 GETscFillValueTemperatureEE( uint8 );
extern void PUTscFillValueTemperatureEE( sint8 , uint8 );

extern uint8 GETucRatedValuePressureEE( uint8 , uint8 );
extern void PUTucRatedValuePressureEE( uint8 , uint8 , uint8 );

extern sint8 GETscRatedValueTemperatureEE( uint8 , uint8 );
extern void PUTscRatedValueTemperatureEE( sint8 , uint8 , uint8 );

extern void INCushResetCntEE( void );

extern uint8 GETucForgottenResetEE( void );
extern void PUTucForgottenResetEE( uint8 );

#if(BERU_BAUREIHE_BMW_PL6_ENABLE == ON)
extern uint8 GETucPresUnitEE( void );
extern void PUTucPresUnitEE( uint8 );

extern uint8 GETucTempUnitEE( void );
extern void PUTucTempUnitEE( uint8 );
#endif

extern uint8 GETucFillValuePressureCALe(uint8 );
extern sint8 GETscFillValueTemperatureCALe(uint8 );
extern uint8 GETucRatedValuePressureCALe(uint8,uint8);
extern sint8 GETscRatedValueTemperatureCALe(uint8,uint8);

extern uint8 GETucResettingTpmsEE( void );
extern void PUTucResettingTpmsEE( uint8 );

extern uint8 GETucWAHistID(uint8);
extern void PUTucWAHistID(uint8, uint8);
extern uint8 GETucWAHistWP(uint8);
extern void PUTucWAHistWP(uint8, uint8);

extern uint8 GETucHistWarningStateBAKe( void );
extern void PUTucHistWarningStateBAKe( uint8 );
#endif
