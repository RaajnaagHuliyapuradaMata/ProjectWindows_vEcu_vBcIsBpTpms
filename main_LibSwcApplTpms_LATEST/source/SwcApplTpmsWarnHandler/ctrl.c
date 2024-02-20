

#include "USWarnX.h"
#include "global.h"
#include "DAG_TVWarn.h"
#include "WnTypePar.h"
#include "Appl_TPMS_Dcm.h"
#include "wallocX.h"

TempWarnParaType tDAG_TemPara;
PWarnParaType tDAG_PPara;

static void RdDAGPara(void);
static void InitDefValPPara(void);
static void InitDefValTemPara(void);

static uint8 ui8GetDAGTempWarnPara(TempWarnParaType * ptTemPara);
 static uint8 ui8GetDAGPWarnPara(PWarnParaType * ptPPara);

void InitUSWAlgo(const unsigned char *ptWPos)
{
    unsigned char aucDgServ[6]={0};

    aucDgServ[0] = 0x00;
    aucDgServ[0] = ucWarnManagerWN(ucPorInitc, aucDgServ);
    aucDgServ[0] = 0x00;
    aucDgServ[1] = 0x00;
    aucDgServ[2] = 0x00;
    aucDgServ[0] = ucTSSMsgManagerTM(ucPorInitc,aucDgServ);
    TimerWTinit();

    UpdateWarnOut (ptWPos);

    RdDAGPara();

    IniTVWarn ();
}

static void RdDAGPara (void)
 {
    if ( ui8GetDAGPWarnPara (&tDAG_PPara) == (uint8) 0)
        InitDefValPPara();
    if (ui8GetDAGTempWarnPara (&tDAG_TemPara ) == (uint8) 0)
        InitDefValTemPara ();
}

static void InitDefValPPara(void)
{
    tDAG_PPara.ui16_CONSTANT_DELAY = 0;
    tDAG_PPara .ui16_T_HARD = 60 * GETucT_HardOfRam();
    tDAG_PPara .ui16_T_SOFT = 60 * GETucT_SoftOfRam();
    tDAG_PPara .ui8_PERCENT_HARD = GETucPercent_HardOfRam();
    tDAG_PPara .ui8_PERCENT_SOFT = GETucPercent_SoftOfRam();
    tDAG_PPara .ui8_P_MIN_F = GETucPcalMinVaRelativCodOfRam();
    tDAG_PPara .ui8_P_MIN_R = GETucPcalMinHaRelativCodOfRam();
    tDAG_PPara .ui8_P_MIN_TIRE = GETucMinWarnThresholdOfRam();
}
static void InitDefValTemPara(void)
{
    tDAG_TemPara .i8_T0 = GETscT0OfRam();
    tDAG_TemPara .i8_T1 = GETscT1OfRam();
    tDAG_TemPara .i8_T2 = GETscT2OfRam();
    tDAG_TemPara .ui16_V1 = GETushV1();
    tDAG_TemPara .ui16_V2 = GETushV2();
    tDAG_TemPara .ui16_V3 = GETushV3();
    tDAG_TemPara .ui16_HC_MAX = GETushHCmax();
    tDAG_TemPara.ui8_TempWarnEnable = GETucTempWarnOnOffOfRam();
}
 static uint8 ui8GetDAGTempWarnPara(TempWarnParaType * ptTemPara)
{
    return 0;
}
static uint8 ui8GetDAGPWarnPara(PWarnParaType * ptPPara)
{
    return 0;
}

void KL15OffWarnInit(const unsigned char *ptWPos)
{
  USWPostInit();

  UpdateWarnOut (ptWPos );

  IniTVWarnAtKL15Off();

  UpdateGlobWrnLvlNWarnDisp();
}

uint8 ui8GetPMIN_F(void)
{
  return (tDAG_PPara .ui8_P_MIN_F );
}

uint8 ui8GetPMIN_R(void)
{
  return (tDAG_PPara .ui8_P_MIN_R );
}

 void UpdateWarnOut(const unsigned char * p2WPs)
{
  unsigned char aucDgServ[6]={0};
  unsigned char i;

  aucDgServ[1] = ucGetWarnVectorsc;
  aucDgServ[0] = (unsigned char) ucWarnManagerWN(ucDiagServicec, &aucDgServ[1]);

  aucDgServ[0] = ucPutWarnVectorSetc;
  aucDgServ[0] = ucTSSMsgManagerTM(ucDiagServicec,aucDgServ);

  aucDgServ[0] = ucNewPositionsc;
  aucDgServ[1] = *p2WPs;
  for (i = 0; i < (ucSumWEc-1); i++)
  {
    aucDgServ[2+i] = p2WPs[1+i];
  }
  aucDgServ[0] = ucTSSMsgManagerTM(ucDiagServicec,aucDgServ);
}

