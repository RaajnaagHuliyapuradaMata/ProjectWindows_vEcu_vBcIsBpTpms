/*
 *(c) Huf Electronics GmbH     BEE1     08/2012
 *================================================================================================
 *
 *$Archive: /LIB/WAF/work/FPA.h $
 *
 *file status:   under construction
 *
 *------------------------------------------------------------------------------------------------
 *
 *author:        Peter Brand                Huf Electronics GmbH
 *
 *intials:       pb
 *
 *
 *
 *Modul Description
 *
 *
 *Global description: 
 *Purpose: 
 *
 *
 *
 *Modul Modification
 *
 *
 *
 * $Log: /LIB/WAF/work/FPA.h $
 * 
 * 4     7.09.12 17:48 Peter
 * pb_ModulTest_050104
 * 
 * 3     7.09.12 16:54 Peter
 * adaption to sensor revision 15 6 2 
 * works with 2 delay correction tabs and different speed ranges (lo/hi)
 * on correction tab 4 2nd frames of the multiburst
 * 
 * 2     21.08.12 17:52 Peter
 * new module structure (FPA and AEC, CA seperated)
 * 
 * 1     17.08.12 17:27 Peter
 * 
 * 1     10.08.12 10:09 Peter
 * 
*/
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


extern unsigned char ucAdjABSIface(unsigned char ucID, tRFTelType * ptInputWA); // returns > 0 if ABS iface could be adjusted - means further FPA allocate actions possible
extern unsigned char ucFPDecPossible(unsigned short * p2ushSlots,unsigned char ucCtLimit); // returns nr of zom slots ready to decide
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
#endif //pb_ModulTest_050104
#endif