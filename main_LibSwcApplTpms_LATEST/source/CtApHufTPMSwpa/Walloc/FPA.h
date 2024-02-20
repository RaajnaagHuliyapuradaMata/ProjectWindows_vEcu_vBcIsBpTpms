
#include "Compiler_Cfg.h"

#define cMinCt4Dec (unsigned char) 14

#ifdef FPA_INT

void TESTPrintFPAZOMSlot(unsigned char ucSlot);
unsigned char ucGetCorER(unsigned short * p2Slots );
unsigned char ucCorLine(unsigned char  p2Line[], const unsigned char ucMaxDev);
unsigned char ucGenDMnD2(unsigned char ucDifDblWPinPC, unsigned char ucDifWPinPc, unsigned short ushSlotFilter);
unsigned char GETuCorWPofSlot(unsigned char ucSlot, unsigned char * pucWP, unsigned char * pucPcVal);

#else
extern  unsigned char ucConceptFixPos0(unsigned char ucID, tRFTelType * ptInputWA);
extern unsigned char ucFPActive(void);
extern void Very1stABSTickIinit(void);

extern unsigned char ucAdjABSIface(unsigned char ucID, tRFTelType * ptInputWA);
 extern unsigned char ucFPDecPossible(unsigned short * p2ushSlots,unsigned char ucCtLimit);
 extern void BuildCmpVal(unsigned char ucID);
extern unsigned char ucGetCorER(unsigned short * p2Slots );
extern unsigned char ucCorLine(unsigned char  p2Line[], const unsigned char ucMaxDev);
extern unsigned char ucGenDMnD2(unsigned char ucDifDblWPinPC, unsigned char ucDifWPinPc, unsigned short ushSlotFilter);
extern void ProvideFPAlgo2MT_DAG(void);
extern unsigned short ushReduceCorel24(unsigned short ushCandidate);
extern unsigned char GETuCorWPofSlot(unsigned char ucSlot, unsigned char * pucWP, unsigned char * pucPcVal);

#ifdef pb_ModulTest_050104
extern void TESTPrintToothZOM_HL(void);
extern void TESTPrintToothZOMAsLine(void);
extern void TESTPrinToothZOMSummary(unsigned char i);
extern void TESTPrintFPAZOMSlot(unsigned char ucSlot);
#endif
 #endif
