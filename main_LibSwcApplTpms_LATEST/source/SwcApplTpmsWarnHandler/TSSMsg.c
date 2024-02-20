

#include "USWarnX.h"
#include "global.h"
#include "tssmsg.h"
#include "eeiface.h"
#include "WnTypePar.h"
#include "USWTime.h"
#include "uswarn_Ifx.h"

#ifndef pb_TestTssMsg_300103

#else
#include <stdio.h>
#endif

static void TSSMsgOut(const unsigned char *ptData);
static unsigned char ucTSSMsgService(unsigned char * pucData);
static void TSSMsgInit(void);
static void GenTPM_WarnDisp_Rq(void);
static void GenDAGlobalWarningLevel(void);
static void IdWarn2WP(const uint8 * p2WP);

static unsigned char ucGlobalWarnStatus;

unsigned short ushWarnOutTM;

unsigned char aucWheelPosWarn[ucMaxPosc + 1];

static unsigned char aucWarnAtPosTM[ucMaxPosc + 1];

static unsigned char ucTPM_WarnDisp_Rq = cNORMAL;

static unsigned char ucAnyHWActive(void)
{
  if (((aucWarnAtPosTM[ucSumWEc] & (1<<ucPMinIxc)) > 0) || (((aucWarnAtPosTM[ucSumWEc] & (1<<ucEcEIxc)) > 0) && (ui8HWTimerExpired() > (uint8) 0)) )
    return ((unsigned char) 1);
  else
    return ((unsigned char) 0);
}

static unsigned char ucAnySWActive(void)
{
  if (((aucWarnAtPosTM[ucSumWEc] & (1<<ucSFactorIxc)) > 0) && (ui8SWTimerExpired () > (uint8) 0))
    return ((unsigned char) 1);
  else
    return ((unsigned char) 0);
}

static void TSSMsgOut(const unsigned char *ptData)
{
  union TssMsgAccess
  {
    struct TssMsg tTssMsg;
    unsigned char ucByte[sizeof(struct TssMsg)];
  }tTMD;
   unsigned char i;

   for (i=0; i < (unsigned char) sizeof(struct TssMsg) ;i++)
   {
      tTMD.ucByte[i] = ptData[i];
   }
   if (tTMD.tTssMsg.ucId < ucSumWEc)
   {
      aucWarnAtPosTM[tTMD.tTssMsg.ucId] = tTMD.tTssMsg.ucWarning;
      IdWarn2WP (GETpui82SysWP());
    }
}
static unsigned char ucTSSMsgService(unsigned char * pucData)
{
   unsigned char i, ucRet = 0;

   switch (*pucData)
   {
   case (unsigned short) ucNewPositionsc:
      {
            IdWarn2WP (GETpui82SysWP());
             ucRet = 0;
    }
      break;

   case (unsigned short) ucPutWarnVectorSetc:
      {
         pucData++;
         for (i=0;i<ucSumWEc;i++)
         {
            aucWarnAtPosTM[i] = pucData[i];
         }
      }
      break;
   default:
      ucRet = 0xff;
      break;
   }
   return ( ucRet );
}

static void TSSMsgInit(void)
{
  unsigned char i;

  GetDataEE(ucCbIdTMc,&ucGlobalWarnStatus , 1);
  for ( i = 0; i < (ucSumWEc + 1);i++)
  {
    aucWarnAtPosTM[i] = 0;
    aucWheelPosWarn[i] = 0;
  }

  if (cFAST_DEFLATION == ucGlobalWarnStatus)
  {
    ucGlobalWarnStatus = cHARD_WARNING;
    PutDataEE(ucCbIdTMc, &ucGlobalWarnStatus , 1);
  }
  ushWarnOutTM = ucGlobalWarnStatus;

  ucTPM_WarnDisp_Rq = cNORMAL;
}

unsigned char ucTSSMsgManagerTM(unsigned char ucAction, unsigned char *ptData)
{
   unsigned char ucRet = 0;

  switch( ucAction )
  {
      case (unsigned short) ucPorInitc:
      {
        TSSMsgInit();
      }
      break;
    case (unsigned short) ucTssMsgOutc :

      TSSMsgOut(ptData);
      break;
    case (unsigned short) ucDiagServicec:

      ucRet = ucTSSMsgService(ptData);
         break;
    default:
      ucRet = 0xff;
      break;
  }
  return(ucRet);
}

static void GenTPM_WarnDisp_Rq(void)
{
  if (ui8KL15OFFnXsec() > 0)
  {
    ucTPM_WarnDisp_Rq = cNORMAL;
  }

  switch (ucTPM_WarnDisp_Rq)
  {
  case cNORMAL:
    if (cFAST_DEFLATION == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
    else if ((cHARD_WARNING == ushWarnOutTM) && (ui8NoHoldOff () > (uint8) 0) )
      ucTPM_WarnDisp_Rq = cHARD_WARNING;
    else if ((cSOFT_WARNING == ushWarnOutTM) && (ui8NoHoldOff () > (uint8) 0) )
      ucTPM_WarnDisp_Rq = cSOFT_WARNING;
    break;

  case cSOFT_WARNING:
    if (cFAST_DEFLATION == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
    else if (cHARD_WARNING == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cHARD_WARNING;
    else if (cNORMAL == ushWarnOutTM )
      ucTPM_WarnDisp_Rq = cNORMAL;
    break;

  case cHARD_WARNING:
    if (cFAST_DEFLATION == ushWarnOutTM)
      ucTPM_WarnDisp_Rq = cFAST_DEFLATION;
    else if (cNORMAL == ushWarnOutTM )
      ucTPM_WarnDisp_Rq = cNORMAL;
    break;

  case cFAST_DEFLATION :
    if (cNORMAL == ushWarnOutTM )
      ucTPM_WarnDisp_Rq = cNORMAL;

    break;

  default:
    ucTPM_WarnDisp_Rq = cNORMAL;
    break;
  }
}

static void GenDAGlobalWarningLevel(void)
{
  ushWarnOutTM = (unsigned short) ucGlobalWarnStatus;
  switch (ucGlobalWarnStatus)
  {
  case cNORMAL:
    if ((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0)
      ucGlobalWarnStatus = cFAST_DEFLATION;
    else if ((ucAnyHWActive () > 0) && (ui8CalActive () == 0))
      ucGlobalWarnStatus = cHARD_WARNING;
    else if ((ucAnySWActive () > 0) && (ui8CalActive () == 0))
      ucGlobalWarnStatus = cSOFT_WARNING;
    break;

  case cSOFT_WARNING:
    if ((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0)
      ucGlobalWarnStatus = cFAST_DEFLATION;
    else if ((ucAnyHWActive () > 0) )
       ucGlobalWarnStatus = cHARD_WARNING;
    else if (((aucWarnAtPosTM[ucSumWEc] & ucAllDAGWarningBits) == (unsigned char) 0) || ((ui8MfdCalActive () == 1)))
      ucGlobalWarnStatus = cNORMAL;
    break;

  case cHARD_WARNING:
    if (((aucWarnAtPosTM[ucSumWEc] & (1<<ucDHWIxc)) > 0) && (ui8KL15OFF () == 0))
      ucGlobalWarnStatus = cFAST_DEFLATION;
   else if (ui8MfdCalActive () == 1)
         ucGlobalWarnStatus = cNORMAL;
    else if ((aucWarnAtPosTM[ucSumWEc] & ((1<<ucPMinIxc)|(1<<ucEcEIxc))) == ((unsigned char) 0))
      ucGlobalWarnStatus = cSOFT_WARNING;
    break;

  case cFAST_DEFLATION :
    if (ui8KL15OFF () > 0)
      ucGlobalWarnStatus = cHARD_WARNING;
    else if (((aucWarnAtPosTM[ucSumWEc] & ucAllDAGWarningBits) == (unsigned char) 0) || ((ui8MfdCalActive () == 1)))
      ucGlobalWarnStatus = cNORMAL;
    break;
  
  default:
    ucGlobalWarnStatus = cNORMAL;
    break;
    }
  if (((unsigned char) ushWarnOutTM) !=  ucGlobalWarnStatus)
  {
    PutDataEE(ucCbIdTMc, &ucGlobalWarnStatus , 1);
    ushWarnOutTM = (unsigned short) ucGlobalWarnStatus;
  }
}

unsigned char GetucTPM_WarnDisp_Rq(void)
{
  return (ucTPM_WarnDisp_Rq);
}

void UpdateGlobWrnLvlNWarnDisp(void)
{
  GenDAGlobalWarningLevel ();
  UpdateDAGsOldOff();
  GenTPM_WarnDisp_Rq ();
}

uint8 ui8GetHardWrnOfWP(uint8 ui8WP)
 {
  if (sizeof(aucWheelPosWarn) > ui8WP)
    return( (( (aucWheelPosWarn[ui8WP] & ((unsigned char) (1<<ucEcEIxc)) ) == ((unsigned char) (1<<ucEcEIxc))  ) && (ui8HWTimerExpired() > (uint8) 0)) ? (uint8)1:(uint8)0);

  return ( (uint8) 0);
}

uint8 ui8GetSoftWrnOfWP(uint8 ui8WP)
 {
  if (sizeof(aucWheelPosWarn) > ui8WP)
    return( ( (aucWheelPosWarn[ui8WP] & ((unsigned char) (1<<ucSFactorIxc)) ) == ((unsigned char) (1<<ucSFactorIxc)) && (ui8SWTimerExpired() > (uint8) 0)) ? (uint8)1:(uint8)0);

  return ( (uint8) 0);
}

 uint8 ui8GetWarntypeOfHistCol(uint8 ui8WnType, uint8 ui8HistCol)
{
  if (((uint8) 4) > ui8HistCol )
  {
    ui8WnType &= ucAllDAGWarningBits;
    if (ui8WnType == (aucWarnAtPosTM[ui8HistCol ] & ui8WnType ))
    {
      return ((uint8) 0xFF);
    }
    else
    {
      return ((uint8) 0);
    }
  }
  else
  {
    return ((uint8) 0);
  }
}

static void IdWarn2WP(const uint8 * p2WP)
{
  uint8 i, ui8UnusedWP;

  ui8UnusedWP = (uint8) 0x0F;
   aucWheelPosWarn[ucSumWEc] = (uint8) 0;
  aucWarnAtPosTM[ucSumWEc] = (uint8) 0;

  for (i=0;i<ucSumWEc;i++)
   {
    switch(p2WP[i])
    {
    case (unsigned short) ucWPFLc:
      aucWheelPosWarn[ucWPFLc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~1);
       break;
    case (unsigned short) ucWPFRc:
      aucWheelPosWarn[ucWPFRc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~2);
       break;
    case (unsigned short) ucWPRLc:
      aucWheelPosWarn[ucWPRLc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~4);
       break;
    case (unsigned short) ucWPRRc:
      aucWheelPosWarn[ucWPRRc] = aucWarnAtPosTM[i];
      ui8UnusedWP &= ((uint8) ~8);
       break;
    default:
      aucWheelPosWarn[ucSumWEc] |= aucWarnAtPosTM[i];
      break;
    }
    aucWarnAtPosTM[ucSumWEc] |= aucWarnAtPosTM[i];
  }

  for (i=0;i<ucSumWEc;i++)
   {
    if ((uint8) 0 < (ui8UnusedWP & ((uint8) (1<<i))))
    {
      aucWheelPosWarn[i] = (uint8) 0;
    }
  }

  UpdateGlobWrnLvlNWarnDisp();
}

uint8 NewPositionsUSWIF( const uint8 *pucRadPos )
 {
  uint8 i, ucResult, aucDiagService[5];

  aucDiagService[0] = ucNewPositionsc;

  for( i = 0; i < ucSumWEc; i++ )
  {
    aucDiagService[i + 1] = pucRadPos[i];
  }

  if ( ucTSSMsgManagerTM( ucDiagServicec, aucDiagService ) == 0x00 )
  {
    ucResult = 0;
  }else{
    ucResult = 0xff;
  }

  return( ucResult );
}
