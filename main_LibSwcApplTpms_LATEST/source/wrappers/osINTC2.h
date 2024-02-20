

#ifndef _OSINTC_H
#define _OSINTC_H

#if defined __cplusplus
extern "C"
{
#endif

#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 1

#if defined USE_QUOTE_INCLUDES
 #include "vrm.h"
#else
 #include <vrm.h>
#endif

#define osdICR0MIN   (osdICRBASE0 + 0x0000UL)
#define osdICR0MAX8  (osdICRBASE0 + 0x0040UL)
#define osdICR0MAX16 (osdICRBASE0 + 0x003FUL)

#define osdICRxMIN   (osdICRBASE1 + 0x0040UL)
#define osdICRxMAX8  (osdICRBASE1 + (osdNumberOfInterrupts*2) - 1)
#define osdICRxMAX16 (osdICRBASE1 + (osdNumberOfInterrupts*2) - 2)

#define osdIMR0MIN   (osdICRBASE0 + 0x00F0UL)
#define osdIMR0MAX8  (osdICRBASE0 + 0x00F4UL)
#define osdIMR0MAX16 (osdICRBASE0 + 0x00F3UL)

#define osdIMRxMIN   (osdICRBASE1 + 0x0404UL)
#define osdIMRxMAX8  (osdICRBASE1 + 0x0400UL + ((osdNumberOfInterrupts+7)>>3) - 1)
#define osdIMRxMAX16 (osdICRBASE1 + 0x0400UL + ((osdNumberOfInterrupts+7)>>3) - 2)
#define osdIMRxMAX32 (osdICRBASE1 + 0x0400UL + ((osdNumberOfInterrupts+7)>>3) - 4)

typedef union
{
   osuint16 UINT16;
   osuint8  UINT8[2];

   struct
   {
      osuint8  level:4;
      osuint8  :2;
      osuint8  TBxxx:1;
      osuint8  MKxxx:1;
      osuint8  :4;
      osuint8  RFxxx:1;
      osuint8  :2;
      osuint8  CTxxx:1;
   } SEMANTIC;
} osICxxx_type;

typedef osICxxx_type osINTC1_ICxxx_type[32];
typedef osICxxx_type osINTC2_ICxxx_type[osdNumberOfInterrupts-32];

#define osINTC1_ICxxx (*(volatile osINTC1_ICxxx_type *)osdICRBASE0)
#define osINTC2_ICxxx (*(volatile osINTC2_ICxxx_type *)osdICRBASE1)

#if defined __cplusplus
}
#endif

#endif

