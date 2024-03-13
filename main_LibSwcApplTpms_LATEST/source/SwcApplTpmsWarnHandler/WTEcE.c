/******************************************************************************/
/* File              : WTEcE.c                                                */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "infRteSwcApplTpmsWarnHandler.hpp"
#include "infCtrl.hpp"
#include "infTssMsg.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

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
uint8 bEcE(struct LocalWarnDat* ptLWD, uint8 ucWarnCfg){
   uint16 ushHelp    = (uint16) ptLWD->tHFD.tHF.scTWE + ush273Kelvinc;
   uint8  ucPCompare = ucPfT((ptLWD->tSD.ushMSoll), ushHelp);
   uint8  ucRet;

   ucPCompare -= (uint8) (((uint16) (tDAG_PPara.ui8_PERCENT_HARD) * ucPCompare) / 100);

   if(ucPCompare > (ptLWD->tSD.ucPSoll - cDP_COMP_LIMIT))
      ucPCompare = (ptLWD->tSD.ucPSoll - cDP_COMP_LIMIT);

   ptLWD->ucCurWarnLevel = ucPCompare;

   if(1 == ucGetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc)){
      if((ui8SWTimerExpired() > 0) || (cNORMAL != ushWarnOutTM)){
         ucPCompare += ucHWResetHyst;
      }
      if((ptLWD->tHFD.tHF.ucP > ucPCompare) || (ptLWD->tHFD.tHF.ucP  > (ptLWD->tSD.ucPSoll - (cDP_COMP_LIMIT - ucHWResetHyst)))){
         ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);
         ucRet = 0;
      }
      else
         ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);;
   }
   else{
      if(ptLWD->tHFD.tHF.ucP < ucPCompare){
         ucRet = ucSetWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);
      }
      else{
         ucRet = 0;
         ClearWarnBitWN(ptLWD->tHFD.tHF.ucId, ucEcEIxc);
      }
   }
   UNUSED(ucWarnCfg);
   return ucRet;
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

