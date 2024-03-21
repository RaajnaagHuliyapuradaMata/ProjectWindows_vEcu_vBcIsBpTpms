/******************************************************************************/
/* File              : uswarn_If.c                                            */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/*#includeS                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "infRteSwcApplTpmsWarnHandler.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define cWheelPos_FL  0x00
#define cWheelPos_FR  0x01
#define cWheelPos_RL  0x02
#define cWheelPos_RR  0x03
#define uc1Barc       ((uint8) 40)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern void   updateHoldOff4Pmin            (void);
extern void   updateHoldOffWarning          (void);
extern uint8  GETucWPorPWPofHistCol         (uint8 ucCol);
extern uint8  GETucPrefFront                (void);
extern uint8  GETucPrefRear                 (void);
extern sint8  GETscTref                     (void);
extern uint16 ui16MIsoRel                   (uint8 ucPrel, sint8 scT);
extern uint8  GETucPcalMinVaRelativCodOfRam (void);
extern uint8  GETucPcalMinHaRelativCodOfRam (void);

void UpdateDAGsOldOff(void){
   updateHoldOff4Pmin();
   updateHoldOffWarning();
}

void GetRatValOfId(uint8 uiHistCol, struct SollDat* p2RatVal){
   uint8 ui8WP  = GETucWPorPWPofHistCol(uiHistCol);
   uint8 ui8PFA = GETucPrefFront();
   uint8 ui8PRA = GETucPrefRear();
   sint8 i8TFA  = GETscTref();
   sint8 i8TRA  = GETscTref();

   switch(ui8WP){
      case cWheelPos_FL:
      case cWheelPos_FR:
         p2RatVal->ucPSoll = ui8PFA;
         p2RatVal->scTSoll = i8TFA;
         break;

      case cWheelPos_RL:
      case cWheelPos_RR:
         p2RatVal->ucPSoll = ui8PRA;
         p2RatVal->scTSoll = i8TRA;
         break;

      default:
         p2RatVal->ucPSoll = (ui8PRA > ui8PFA) ? ui8PFA:ui8PRA;
         p2RatVal->scTSoll = (ui8PRA > ui8PFA) ? i8TFA:i8TRA;
         break;
   }
   p2RatVal->ushMSoll = ui16MIsoRel(p2RatVal->ucPSoll,p2RatVal->scTSoll);
}

const uint8* GETpui82SysWP(void){return((const uint8*) GETpucStartAdrWPorPWP());}

uint8 Getui8PrefMinOfId(uint8 histCol){
   uint8 wp           = GETucWPorPWPofHistCol(histCol);
   uint8 pRefMinRelFA = GETucPcalMinVaRelativCodOfRam();
   uint8 pRefMinRelRA = GETucPcalMinHaRelativCodOfRam();
   uint8 pRefMinRel   = 0;

   switch(wp){
      case cWheelPos_FL:
      case cWheelPos_FR:
         pRefMinRel = pRefMinRelFA;
         break;

      case cWheelPos_RL:
      case cWheelPos_RR:
         pRefMinRel = pRefMinRelRA;
         break;

      default:
         pRefMinRel = (pRefMinRelFA < pRefMinRelRA) ? pRefMinRelFA:pRefMinRelRA;
         break;
   }
   return pRefMinRel;
}

uint8 Getui8AtmosphericP(void){return uc1Barc;}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/


