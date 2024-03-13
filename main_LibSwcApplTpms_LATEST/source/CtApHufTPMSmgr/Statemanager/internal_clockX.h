

#ifndef _INTERNAL_CLOCK_X_H
#define _INTERNAL_CLOCK_X_H

#include "Platform_Types.h"
#include "Compiler_Cfg.h"

#define cT_STANBY               (uint16) 1140

#define cT_STANBY4AFD           (uint16) 60
#define c_100km                 (uint32) 100
#define c_50km                  (uint32) 50
#define c_0km                        (uint32) 0
#define c_FFFFkm                (uint32) 0xFFFFFFFF
#define c_FF9Bkm                (uint32) 0xFFFFFF9B

#define OP_TIME_METHOD_OHDS 0x01U
#define OP_TIME_METHOD_CSTDELAY 0x00U

#define PAL_TEL_CST_DELAY_TIME 0x05U

void InternTimersInit(void);

void IncrInternMsTimer(void);

void GetInternMSTime(uint32* ulInternalTime);

void UpdateStanbyTimer(boolean bIgnState, uint16 ushVSpeed, uint8 ucVmin);

void ResetStanbyTimer(void);

boolean bStanbyTimerElapsed(void);

void SkipStanbyTimer(void);

uint8 ucGetCurrentECUParkingState(void);

uint16 ushGetCurrentECUStanbyTime(void);

void UpdateParkingTimer(uint16 ushVSpeed);

uint16 ushGetCurrentECUParkingTime(void);

uint16 ushGetCurrentECUKl15OffParkingTime(void);

uint8 ucGetCurrentECUAfdStartState(void);

void GetSystemOperatingTime(uint32* ulOpTime);
uint8 GetOpTimeMehodTarget(void);
uint8 GetPalAbsConstantDelay(void);
uint8  GetOpTimeMethodCurrent(void);
void SetOpTimeMethodTarget(uint8 ucTimeMethod, uint8 ucCstDelay);
void SetPalAbsTimeInfoSNA(void);

#endif
