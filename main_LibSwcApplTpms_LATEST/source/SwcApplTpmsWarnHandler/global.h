#pragma once

#define ucWarnTypeArrayIdWNc (uint16) 6
#define ucIxWnCfgc 1
#define ucIxGlobWrnLvl 0

extern uint8 bGETucCalRequestState( uint8 ucBitMask );
extern void ClearBitCalRequestState( uint8 ucBitMask );
extern void ClearCalRequestStateAtMFDfinish(void);
extern uint8 GETucPrefFront(void);
extern uint8 GETucPrefRear(void);
extern void PUTucPrefFront(uint8 x);
extern void PUTucPrefRear(uint8 x);
extern sint8 GETscTref(void);
extern void PUTucIdCalPressure(uint8 x, uint8 i);
extern void PUTscIdCalTemperatur(sint8 x, uint8 i);
extern void PUTscTref(sint8 x);
