#pragma once

#define v1_inkmh 100
#define v2_inkmh 150
#define v3_inkmh 180
#define T0_inCG (sint8) 70
#define T1_inCG (sint8) 75
#define T2_inCG (sint8) 80
#define HeatCtMax 600

extern void PuT(uint8 ui8Ix, sint8 i8T);
extern void IniTVWarn(void);
extern void IniTVWarnAtKL15Off(void);
extern void CheckTVWarnAllSec(uint16 ui16SpeedInKmh) ;
