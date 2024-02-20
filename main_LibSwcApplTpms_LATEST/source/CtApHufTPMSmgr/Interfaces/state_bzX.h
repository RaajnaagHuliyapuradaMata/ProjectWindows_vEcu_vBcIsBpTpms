

#ifndef _state_bz_X_H
#define _state_bz_X_H

#include "tss_stdx.h"
  #define cER_FINISH            ((uint16) 0x0001)
 #define cBZ_Frei0             ((uint16) 0x0002)
 #define cAL_RUNNING           ((uint16) 0x0004)
 #define cEIGENRAD             ((uint16) 0x0008)
 #define cZUGEORDNET           ((uint16) 0x0010)
 #define cZO_Fallback2Hist     ((uint16) 0x0020)
 #define cHIST_PRELOAD         ((uint16) 0x0040)
 #define cZO_FINISH            ((uint16) 0x0080)
 #define cCAL_REQUEST          ((uint16) 0x0100)
 #define cCAL_MFD_PLAUSI_ERROR ((uint16) 0x0200)
 #define cCAL_AFD_PLAUSI_ERROR ((uint16) 0x0400)
 #define cDTC_INACTIVE         ((uint16) 0x0800)
 #define cZO_TIMEOUT           ((uint16) 0x1000)
 #define cZO_ERROR             ((uint16) 0x2000)
 #define cTEILZUGEORDNET       ((uint16) 0x4000)
 #define cCAL_FINISH           ((uint16) 0x8000)
 #define cBZ_ALLE_BITS         ((uint16) 0xffff)

#define cCAL_VALID                              ((uint8) 0x00)
 #define cCAL_DP_LR_FA_NAK                     ((uint8) 0x01)
 #define cCAL_DP_LR_RA_NAK                     ((uint8) 0x02)
 #define cCAL_DP_ABS_NAK                        ((uint8) 0x04)
 #define cCAL_P_MIN_X_MINUS_DP_MANUAL   ((uint8) 0x08)
 #define cCAL_RE30K2AMBIENT                  ((uint8) 0x10)
 #define cCAL_DP_STABI_NAK                     ((uint8) 0x20)
 #define cCAL_FBM_ACTIV_NAK                  ((uint8) 0x40)
 #define cCAL_P_MIN_TIRE_NAK                  ((uint8) 0x80)

#define cCAL_ABORT_REASON_2_3 ((uint8) 0x00)
 #define cCAL_RE_MISSING_NAK   ((uint8) 0x40)

#define cCAL_AUTO_ACTIV                   ((uint8) 0x01)
 #define cCAL_AUTO_ENABLE2                  ((uint8) 0x02)
 #define cCAL_AUTO_ENABLE3                  ((uint8) 0x04)
 #define cCAL_AUTO_NEW_ID                  ((uint8) 0x08)
 #define cCAL_AUTO_FIRST                     ((uint8) 0x10)
 #define cCAL_MANUAL_ACTIV                  ((uint8) 0x20)
 #define cCAL_MSG2DISP                        ((uint8) 0x40)
 #define cCAL_MANUAL_FINISH               ((uint8) 0x80)

extern void InitBZ( void );

extern void SetBitBetriebszustandBZ( uint16 );
extern void ClearBitBetriebszustandBZ( uint16 );
extern boolean bGetBitBetriebszustandBZ( uint16 );
extern uint16 ushGetBetriebszustandBZ( uint16 );
extern uint8 ucGetBetriebszustandLByte( void );
extern uint8 ucGetBetriebszustandHByte( void );

#endif
