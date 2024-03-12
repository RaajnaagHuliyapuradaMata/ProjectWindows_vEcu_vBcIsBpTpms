
#include "Compiler_Cfg.h"

#define cMinCt4Dec (uint8) 14

#ifdef FPA_INT

void TESTPrintFPAZOMSlot(uint8 ucSlot);
uint8 ucGetCorER(uint16 * p2Slots );
uint8 ucCorLine(uint8  p2Line[], const uint8 ucMaxDev);
uint8 ucGenDMnD2(uint8 ucDifDblWPinPC, uint8 ucDifWPinPc, uint16 ushSlotFilter);
uint8 GETuCorWPofSlot(uint8 ucSlot, uint8* pucWP, uint8* pucPcVal);

#else
extern  uint8 ucConceptFixPos0(uint8 ucID, tRFTelType * ptInputWA);
extern uint8 ucFPActive(void);
extern void Very1stABSTickIinit(void);

extern uint8 ucAdjABSIface(uint8 ucID, tRFTelType * ptInputWA);
 extern uint8 ucFPDecPossible(uint16 * p2ushSlots,uint8 ucCtLimit);
 extern void BuildCmpVal(uint8 ucID);
extern uint8 ucGetCorER(uint16 * p2Slots );
extern uint8 ucCorLine(uint8  p2Line[], const uint8 ucMaxDev);
extern uint8 ucGenDMnD2(uint8 ucDifDblWPinPC, uint8 ucDifWPinPc, uint16 ushSlotFilter);
extern void ProvideFPAlgo2MT_DAG(void);
extern uint16 ushReduceCorel24(uint16 ushCandidate);
extern uint8 GETuCorWPofSlot(uint8 ucSlot, uint8* pucWP, uint8* pucPcVal);

#ifdef pb_ModulTest_050104
extern void TESTPrintToothZOM_HL(void);
extern void TESTPrintToothZOMAsLine(void);
extern void TESTPrinToothZOMSummary(uint8 i);
extern void TESTPrintFPAZOMSlot(uint8 ucSlot);
#endif
 #endif
