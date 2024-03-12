

#ifndef _tss_stdX_H
#define _tss_stdX_H

#include "Std_Types.h"

#define cAnzAnt       ( (uint8)  1 )
#define cAnzRad       ( (uint8)  4 )
#define cAnzAchse     ( (uint8)  2 )

#define cRadPosVL     ( (uint8) 0 )
#define cRadPosVR     ( (uint8) 1 )
#define cRadPosHL     ( (uint8) 2 )
#define cRadPosHR     ( (uint8) 3 )
#define cRadPosUkw      ( (uint8) 4 )
#define cRadPosFR     ( (uint8) 5 )
#define cRadPosUndef  ( (uint8) 8 )

#define ctFillFront   ( (uint8) 0 )
#define ctFillRear    ( (uint8) 1 )
#define ctRefFront    ( (uint8) 2 )
#define ctRefRear     ( (uint8) 3 )

#define cLTS30Days     ( (uint8) 3 )

#define cZOMPos0      ( (uint8) 0 )
#define cZOMPos1      ( (uint8) 1 )
#define cZOMPos2      ( (uint8) 2 )
#define cZOMPos3      ( (uint8) 3 )

#define ucPalTempNormFACTORc (uint8) 50
#define ucPalTempNormFACTOR4Calc (uint8) 50
#define ucPalTempNormLIMITCalc (uint8) 125
#define ucPalTempNorm4AM (uint8) 85
 #define ucPalTempNormOFFSETc (uint8) 2
#define cDP_STABI            ( (uint8) 4 )
#define cDP_MANUAL         ( (uint8) 8 )
#define cDP_AUTO            ( (uint8) 4 )
#define cDP_LR               ( (uint8) 83)
#define cDP_Abs               ( (uint8) 60 )
#define cDP_FILL            ( (uint8) 8 )
#define cP_GRAD               ( (uint8) 8 )
#define cM_MAX               ( (uint16) 540 )
#define cV_MAX_PAL         ( (uint8) 150 )
#define cV_MIN               ( (uint8) 20 )

#define cDP_FILL_FL         ( (uint8) 0x10 )
#define cDP_FILL_FR         ( (uint8) 0x20 )
#define cDP_FILL_RL         ( (uint8) 0x40 )
#define cDP_FILL_RR         ( (uint8) 0x80 )

#define cFD_Pmin_FL         ( (uint8) 0x01 )
#define cFD_Pmin_FR         ( (uint8) 0x02 )
#define cFD_Pmin_RL         ( (uint8) 0x04 )
#define cFD_Pmin_RR         ( (uint8) 0x08 )
#define cFD_Pmin_UK         ( (uint8) 0xF0 )

#define cTfillLimitH      ( (uint8) 60 )

#define FREQUENCY_433MHZ  ( (uint8) 0x00 )
#define FREQUENCY_868MHZ  ( (uint8) 0x01 )
#define FREQUENCY_315MHZ  ( (uint8) 0x02 )

#define cInvalidREpressure     ( (uint8) 0xff )
#define cInvalidREtemperature  ( (sint8) 0x7f )
#define cInvalidRElifeTime     ( (uint8) 0x00 )
#define cInvalidREstate        ( (uint8) 0x00 )
#define cInvalidRSSIsum        ( (uint8) 0x00 )
#define cInvalidSpinDir        ( (uint8) 0xFF )

#define cRetError    ( (uint8) 0x00 )
#define cRetOk       ( (uint8) 0x01 )

#define cNewIdInHistoryColumn0 ( (uint16) 0x0010)
#define cNewIdInHistoryColumn1 ( (uint16) 0x0020)
#define cNewIdInHistoryColumn2 ( (uint16) 0x0040)
#define cNewIdInHistoryColumn3 ( (uint16) 0x0080)

typedef struct
{
  uint8 hi;
  uint8 lo;
} tWord;

typedef union
{
  uint32 ulLongAccess;
  uint16 ushWordAccess[2];
  uint8  ucByteAccess[4];
} tLong;

#endif

