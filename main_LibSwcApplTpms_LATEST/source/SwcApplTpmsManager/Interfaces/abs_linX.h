

#ifndef _abs_lin_X_H
#define _abs_lin_X_H

#include "tss_stdx.h"
#define cABS_OK              ((uint8) 0x00)
#define cABS_ERROR           ((uint8) 0x01)

#if ABS_SIG_SIZE_ONEBYTE
#define cAbsOverflowValue (uint16)0xFFU
#else
#define cAbsOverflowValue (uint16)0xFFFFU
#endif

extern void InitABS(void);
extern uint8 LinABS( uint16 ushRfTimeStamp);
extern void  PutABS( uint16 ushTime, const uint16 ushCnt[] );
extern uint8 GetLinABS( uint16 ushCnt[] );
extern uint8 bCarAbsStickStandstill(void);
extern uint8  bResetAbsRefPoint(void);
uint8 ucGetAbsOverflowCtrFL(void);
uint8 ucGetAbsOverflowCtrFR(void);
uint8 ucGetAbsOverflowCtrRL(void);
uint8 ucGetAbsOverflowCtrRR(void);
#endif
