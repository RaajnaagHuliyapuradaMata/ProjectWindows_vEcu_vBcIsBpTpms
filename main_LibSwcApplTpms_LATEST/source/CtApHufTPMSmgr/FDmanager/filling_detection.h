

#ifndef _FILLING_DETECTION_H
#define _FILLING_DETECTION_H

#include "Platform_Types.h"

extern void PUTushFDtimeout(uint16);
extern uint16 GETushFDtimeout(void);
extern void DECushFDtimeout(void);

extern void PUTucFDtimerStop(uint8);
extern uint16 GETucFDtimerStop(void);

extern uint8 GETucMinWarnThresholdOfRam(void);

extern sint8 KweightCalculation(sint8, sint8);

extern void ClearAllReCnt4FD(void);
extern uint8 GetOneReCnt4FD(void);

void PUTucTimer4MsgDispRq(uint8 x);
uint8 GETucTimer4MsgDispRq(void);

extern void PUTushSupervisoryTimerFD(uint16);
extern uint16 GETushSupervisoryTimerFD(void);

extern void PUTucOnceCheckMissingRE4FD(uint8);
extern uint8 GETucOnceCheckMissingRE4FD(void);

extern uint8 ucCheckCurrentPminWarn(void);
extern void PUTucNoCheckPmin4StopFD(uint8);
extern uint8 GETucNoCheckPmin4StopFD(void);
extern void ClearKplNoCheckPmin4StopFD(void);

extern uint16 GETushFDtimeout(void);
extern uint8 GETucRErecCounter4FDVL(void);
extern uint8 GETucRErecCounter4FDVR(void);
extern uint8 GETucRErecCounter4FDHL(void);
extern uint8 GETucRErecCounter4FDHR(void);

extern void ReplayLastREvalue2Walgo(void);

extern void PUTulLastCalMileage(uint32 x);
extern uint32 GETulLastCalMileage(void);
extern uint8 GETucPcalMinVaRelativCodOfRam(void);
extern uint8 GETucPcalMinHaRelativCodOfRam(void);

extern void PUTucPosComparePressure(uint8 , uint8);
extern uint8 GETucPosComparePressure(uint8 );

extern uint8 GETucAutoFillDetectionOnOffOfRam(void);
extern uint32 GETulKmStand4AutoCAL(void);
extern uint8 ucCheckLOW_PRESS_ReState(void);

extern uint8 ucCheckAllRePcalMinDPmanualMFD(void);

extern uint8 ChkNewIdColX4FD( void );

extern void PUTucRErecCounter4FDVL( uint8 );
extern void PUTucRErecCounter4FDVR( uint8 );
extern void PUTucRErecCounter4FDHL( uint8 );
extern void PUTucRErecCounter4FDHR( uint8 );

extern void INCucRErecCounter4FDVL( void );
extern void INCucRErecCounter4FDVR( void );
extern void INCucRErecCounter4FDHL( void );
extern void INCucRErecCounter4FDHR( void );

#endif
