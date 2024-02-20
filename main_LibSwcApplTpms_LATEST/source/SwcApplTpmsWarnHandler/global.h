
#ifndef GLOBAL_H

#define GLOBAL_H

#include "Std_Types.h"

#if defined(pb_ModulTest_02062003) || defined(TestUSCSc) || defined(pb_TestCtrl_110203) || defined (pb_TestEeIface_200103)
#define pb_EeIfaceOnPc_200103
#endif

#define ucMaxPosc 4
#define ucSumWEc  (unsigned char) 4

#define ucCbIdTMc (unsigned short) 5
#define ucWarnTypeArrayIdWNc (unsigned short) 6

#define ucIxWnCfgc 1
#define ucIxGlobWrnLvl 0

extern const unsigned char ucBitNoc[ucSumWEc];

extern uint8 bGETucCalRequestState( uint8 ucBitMask );
extern void ClearBitCalRequestState( uint8 ucBitMask );
extern void ClearCalRequestStateAtMFDfinish( void );

extern uint8 GETucPrefFront(void);
extern uint8 GETucPrefRear(void);
extern void PUTucPrefFront(uint8 x);
extern void PUTucPrefRear(uint8 x);

extern sint8 GETscTref(void);
extern void PUTucIdCalPressure(uint8 x, uint8 i);
extern void PUTscIdCalTemperatur(sint8 x, uint8 i);
extern void PUTscTref(sint8 x);

extern uint8 * pui8GetLastM1Pressure(void);
extern uint8 ui8GetPMIN_F(void);
extern uint8 ui8GetPMIN_R(void);

extern void UpdateWarnOut(const uint8 * p2WPs);
#endif

