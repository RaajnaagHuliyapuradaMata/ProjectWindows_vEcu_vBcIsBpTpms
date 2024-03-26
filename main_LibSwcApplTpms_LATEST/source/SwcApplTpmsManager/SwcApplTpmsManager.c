/******************************************************************************/
/* File              : SwcApplTpmsManager.c                                   */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/*#includeS                                                                  */
/******************************************************************************/
#include "Std_Types.hpp"

#include "Rte_CtApHufTPMSmgr.h"

#include "HMI_handlerX.h"
#include "abs_linX.h"
#include "wallocX.h"
#include "USWarnX.h"
#include "cd_decoder_x.h"
#include "state_fdX.h"
#include "state_bzX.h"
#include "state_zkX.h"
#include "tss_stdX.h"
#include "Trace.h"
#include "internal_clockX.h"
#include "state_fZZX.h"
#include "HMI_handlerX.h"
#include "tel_time_filterX.h"
#include "tel_statisticX.h"
#include "filling_detectionX.h"
#include "Dem_IntEvtId.h"
#include "ComStack_Types.h"
#include "CanSM_Cfg.h"
#include "SensorLoBat.h"
#include "Appl_Dcm.h"
#include "SensorMeasError.h"
#include "EcuM_Generated_Types.h"

#if E2E_ENABLE
#include "HufE2EWrapper.h"
#endif

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define Off                 (0U)
#define On                  (1U)
#define cV_MIN_PAL          ((uint8) 20)
#define ucWPFLc             ((uint8) 0) //TBD:
#define ucWPFRc             ((uint8) 1) //TBD:
#define ucWPRLc             ((uint8) 2) //TBD:
#define ucWPRRc             ((uint8) 3) //TBD:
#define ucWPUNc             ((uint8) 8)
#define ucWPSTc             ((uint8) 4)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#define GETbWrnPMin_FL()        ((aucWheelPosWarn[ucWPFLc] & ((uint8) (1<<ucPMinIxc))) == ((uint8) (1<<ucPMinIxc)))
#define GETbWrnPMin_FR()        ((aucWheelPosWarn[ucWPFRc] & ((uint8) (1<<ucPMinIxc))) == ((uint8) (1<<ucPMinIxc)))
#define GETbWrnPMin_RL()        ((aucWheelPosWarn[ucWPRLc] & ((uint8) (1<<ucPMinIxc))) == ((uint8) (1<<ucPMinIxc)))
#define GETbWrnPMin_RR()        ((aucWheelPosWarn[ucWPRRc] & ((uint8) (1<<ucPMinIxc))) == ((uint8) (1<<ucPMinIxc)))
#define GETbWrnPMin_UK()        ((aucWheelPosWarn[4]       & ((uint8) (1<<ucPMinIxc))) == ((uint8) (1<<ucPMinIxc)))
#define GETbWrnPMin_WP(Pos)     ((aucWheelPosWarn[Pos]     & ((uint8) (1<<ucPMinIxc))) == ((uint8) (1<<ucPMinIxc)))

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
extern debugTelStruct    tDebugTelStruct;
extern debugTelStructPos tdebugTelStructPosFL;
extern debugTelStructPos tdebugTelStructPosFR;
extern debugTelStructPos tdebugTelStructPosRL;
extern debugTelStructPos tdebugTelStructPosRR;

uint8         ucLedState1    = 0;
uint8         ucRecEvent     = 0;
uint8         ucReCnt4Test   = 0;
uint8         ucEspDelayTime = 0;
boolean       bOnce          = FALSE;

DT_tEnvData   tEnvDataToSend;
DT_auRfStruct tReTelData;
uint32        ulKmStand4AutoCal;
uint32        ulTelID, ulTelTimeStamp;
uint16        ushFDtimeout;
uint16        ushSupervisoryTimerFD;
uint8         bRvsGearUsed, ucRvsGearCnt;
uint8         ucReCnt4Cal;
uint8         ucRErecCounter4FDVL;
uint8         ucRErecCounter4FDVR;
uint8         ucRErecCounter4FDHL;
uint8         ucRErecCounter4FDHR;
uint8         ucTmpPiso4Cal;
uint8         ucFillingDetectedState;
uint8         ucTelType;
uint8         ucTelPal;
uint8         ucTelP;
uint8         ucTelT;
uint8         ucTelAvgRSSI;
uint8         ucNoiseLevel;
uint8         ucTimer4MsgDispRq;
uint8         ucOnceCheckMissingRE4FD;
uint8         ucLTSmode;
uint8         ucFDtimerStop;

static boolean bWrCodNVMBlock = FALSE;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
extern FUNC(Std_ReturnType,      DCM_CODE) Dcm_GetSesCtrlType   (P2VAR(Dcm_SesCtrlType, AUTOMATIC,  DCM_APPL_DATA) SessionCtrlType);
extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState        (P2VAR(EcuM_StateType,  AUTOMATIC, ECUM_APPL_DATA) state);
extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_ReleasePOST_RUN (EcuM_UserType User_t);
extern uint16  GETucFDtimerStop               (void);
extern uint16  GETushFDtimeout                (void);
extern uint16  GETushSupervisoryTimerFD       (void);
extern uint32  GETulKmStand4AutoCAL           (void);
extern uint32  GETulLastCalMileage            (void);
extern uint8   bGETucCalRequestState          (uint8 ucBitMask);
extern uint8   GETucCalRequestStateOfRam      (void);
extern uint8   GETucCoastModeContCountOfRam   (void);
extern uint8   GETucMeasurementStateOfRam     (void);
extern uint8   GETucOnceCheckMissingRE4FD     (void);
extern uint8   GETucPosComparePressure        (uint8 i);
extern uint8   GETucPrefFront                 (void);
extern uint8   GETucPrefRear                  (void);
extern uint8   GETucRErecCounter4FDHL         (void);
extern uint8   GETucRErecCounter4FDHR         (void);
extern uint8   GETucRErecCounter4FDVL         (void);
extern uint8   GETucRErecCounter4FDVR         (void);
extern uint8   GETucTimer4MsgDispRq           (void);
extern uint8   ucCheckAllRePcalMinDPmanualMFD (void);
extern uint8   ucCheckLOW_PRESS_ReState       (void);
extern uint8   ui8GetComptoirRepare           (void);
extern sint8   GETscIdCalTemperatur           (uint8 i);
extern boolean GETbCalNotAck4PlausiCheckMFA   (void);
extern boolean GETbCalPminInvalidCAL          (void);
extern boolean GETbCalReqCAL                  (void);
extern boolean LearningWheelPosActiveSM       (void);
extern void    Appl_CanSM_BusOffEnd           (NetworkHandleType CanSm_NetworkHandle);
extern void    CheckDTCInactiveERR            (void);
extern void    ClearAllReCnt4FD               (void);
extern void    ClearBitCalRequestState        (uint8 ucBitMask);
extern void    CountCoastModeClampCycle       (void);
extern void    DECucTimer4MsgDispRq           (void);
extern void    DECushFDtimeout                (void);
extern void    DECushSupervisoryTimerFD       (void);
extern void    INCucRErecCounter4FDHL         (void);
extern void    INCucRErecCounter4FDHR         (void);
extern void    INCucRErecCounter4FDVL         (void);
extern void    INCucRErecCounter4FDVR         (void);
extern void    InitIDOM                       (void);
extern void    Nm_DisableCommunication        (uint8);
extern void    Nm_EnableCommunication         (uint8);
extern void    PUTscIdCalTemperatur           (sint8 x, uint8 i);
extern void    PUTucCalRequestState2Ram       (uint8 x);
extern void    PUTucCoastModeContCount2Nvm    (void);
extern void    PUTucCoastModeContCount2Ram    (uint8);
extern void    PUTucFDtimerStop               (uint8);
extern void    PUTucOnceCheckMissingRE4FD     (uint8);
extern void    PUTucPosComparePressure        (uint8 x, uint8 i);
extern void    PUTucPrefFront                 (uint8 x);
extern void    PUTucPrefRear                  (uint8 x);
extern void    PUTucRErecCounter4FDHL         (uint8);
extern void    PUTucRErecCounter4FDHR         (uint8);
extern void    PUTucRErecCounter4FDVL         (uint8);
extern void    PUTucRErecCounter4FDVR         (uint8);
extern void    PUTucTimer4MsgDispRq           (uint8 x);
extern void    PUTulKmStand4AutoCAL           (uint32 i);
extern void    PUTulLastCalMileage            (uint32 x);
extern void    PUTushFDtimeout                (uint16);
extern void    PUTushSupervisoryTimerFD       (uint16);
extern void    ReplayLastREvalue2Walgo        (void);
extern void    SetBitCalNotAckState2Ram       (uint8 ucBitMask);
extern void    SetBitCalRequestState2Ram      (uint8 ucBitMask);
extern void    SetClamp15State                (uint8);
extern void    SetCodNvMBlockNewDataFlag      (boolean);
extern void    TP0                            (uint8 ucSet);
extern void    TPMS_NVM_ActivateWriteAll      (void);
static void    UpdateCanMState                (void);
static void    GetZOMInfos2BeLogged           (void);
static void    AlignCodBlockRaM2NvM           (void);

typedef     uint16                            Dem_EventIdType;      //TBD:
typedef     uint8                             Dem_EventStatusType;  //TBD:
typedef VAR(uint8,          CANSM_VAR_NOINIT) CanSM_BorCounterType; //TBD:
extern FUNC(Std_ReturnType, DEM_CODE        ) Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType   EventStatus);
extern void Appl_CanSM_BusOffBegin(NetworkHandleType CanSm_NetworkHandle, CanSM_BorCounterType CanSM_BufOffNotificationCounter);

#define RTE_START_SEC_CTAPHUFTPMSMGR_APPL_CODE
#include "MemMap.h"
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ControlEcuStandbyTimer(void){
   UpdateStanbyTimer(tEnvDataToSend.ucKlState, tEnvDataToSend.ushVehSpeed, cV_MIN);
   UpdateParkingTimer(tEnvDataToSend.ushVehSpeed);
   UpdateTelStatInfo(tEnvDataToSend.ushVehSpeed, cV_MIN);
   UpdateFzzCurrentLearnMode();
   UpdateFzzDTcEnableCond();
   FillingDetectionAFDII();
   AlignCodBlockRaM2NvM();
   GetDebugVar2beLogged();
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_GenInternalClock(void){
   IncrInternMsTimer();
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_Init(void){
   InitBZ();
   InitZK();
   InitABS();
   InitTelStatInfo();
   InitTxBusMsg();
   InitFilterTime();
   bRvsGearUsed = 0;
   ucRvsGearCnt=0;
   ucRecEvent=0;

#ifdef TestLOGINPUTDATAENABLE
   testLogInputDataInit();
#endif

   tracerInit();
   InternTimersInit();

#if E2E_ENABLE
   HufE2EWrapperInit();
#endif

   ucTelType      = 0;
   ulTelTimeStamp = 0;
   ulTelID        = 0;
   ucTelPal       = 0;
   ucTelP         = 0;
   ucTelT         = 0;
   ucTelAvgRSSI   = 0;
   ucNoiseLevel   = 0;

   PUTucTimer4MsgDispRq(0);
   PUTushFDtimeout(0);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdDateTm(void){
  ClearFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEngCtrl(void){
   REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy data;
   Rte_Read_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2(&data);
   if( //TBD: Optimize with switch case
         (I_C03_ENGRUN_STAT_STOP == data.EngRun_Stat)
      || (I_C03_ENGRUN_STAT_SNA  == data.EngRun_Stat)
   ){
      tEnvDataToSend.ucEngStat = cEngStat_STOPPED;
   }
   else if(
         (I_C03_ENGRUN_STAT_START       == data.EngRun_Stat)
      || (I_C03_ENGRUN_STAT_IDLE_UNSTBL == data.EngRun_Stat)
   ){
      tEnvDataToSend.ucEngStat = cEngStat_STARTING;
   }
   else if(
         (I_C03_ENGRUN_STAT_IDLE_STBL == data.EngRun_Stat)
      || (I_C03_ENGRUN_STAT_UNLIMITED == data.EngRun_Stat)
      || (I_C03_ENGRUN_STAT_LIMITED   == data.EngRun_Stat)
   ){
      tEnvDataToSend.ucEngStat = cEngStat_RUNNING;
   }
   SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
   ClearFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEnvPressure(void){
   c08_hPa_0_1980_7k8 ucPressOut;
   Rte_Read_R_AirPress_Outsd_AirPress_Outsd(&ucPressOut);
   tEnvDataToSend.ucPressOut = ucPressOut;
   ClearFzzSignalTimeOutState(cFZZ_PRESS_OUT_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEnvTemperature(void){
   c08_degC_m40_85_0k5 tmpAussenTemp;
   Rte_Read_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp(&tmpAussenTemp);
   ClearFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT);
   if(tmpAussenTemp < I_C08_DEGC_M40_85_0K5_SNA){
      tEnvDataToSend.ucTempOut = (uint8)((tmpAussenTemp>>1) - 40);
      Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
      SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
      ClearFzzSignalUnplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU);
   }
   else{
      SetFzzSignalImplauState(cFZZ_AIRTEMP_OUT_IMPLAU);
   }
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdGrBac(void){
   c02_Disengg_Engg data;
   Rte_Read_R_RevGr_Engg_RevGr_Engg(&data);
   if(I_C02_DISENGG_ENGG_ENGG == data){
      if(
            (0 == bRvsGearUsed)
         && (ucRvsGearCnt < 0xFF)
      ){
         ucRvsGearCnt++;
      }
      bRvsGearUsed = 1;
   }
   else{
      bRvsGearUsed = 0;
   }
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdIgnStat(void){
   REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno tmpKLstate;
   Rte_Read_R_Ign_Stat_Pr2_Ign_Stat_Pr2(&tmpKLstate);
   if(
         (I_C03_ISW_STAT_IGN_ON    == tmpKLstate.ISw_Stat)
      || (I_C03_ISW_STAT_IGN_START == tmpKLstate.ISw_Stat)
   ){
      tEnvDataToSend.ucKlState = On;
   }
   else{
      if(tEnvDataToSend.ucKlState != Off){
         CountCoastModeClampCycle();
      }
      tEnvDataToSend.ucKlState = Off;
   }
   tEnvDataToSend.ucIgnOnStartProc = tmpKLstate.Ign_On_StartProc_Inact;
   Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
   SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
   ClearFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdOdo(void){
   c24_km_0_999999k9_0k1 temp;
   Rte_Read_CtApHufTPMSmgr_R_Odo_Odo(&temp);
   PUTulKmStand4AutoCAL(temp);
   ClearFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdPN14EOLDispRq(void){
   c03_EOL_Disp_Rq value;
   if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT ) == FALSE ){
      Rte_Read_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq(&value);
      if(
            (value == I_C03_EOL_DISP_RQ_IOD_MEAS)
         || (value == I_C03_EOL_DISP_RQ_IOD_ERR)
      ){
         SkipStanbyTimer();
      }
   }
   bOnce = FALSE;
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdSupPN14BatStat(void){
   ClearFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdTpmActvRq(void){
   c02_TPM_Actv_Rq_V2 temp;

   Rte_Read_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2(&temp);
   ClearFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT);
   if(temp < I_C02_TPM_ACTV_RQ_V2_SNA){
      if(temp == I_C02_TPM_ACTV_RQ_V2_ACTIVATE){
#ifndef FD_CONTROLS_FALLBACK
         if(
            !(
                  GETbWrnPMin_FL()
               || GETbWrnPMin_FR()
               || GETbWrnPMin_RL()
               || GETbWrnPMin_RR()
            )
         ){
            ClearPWP();
            Check4PWP();
         }
#endif
         FillingDetectionMFD(TRUE);
      }
      ClearFzzSignalUnplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU);
   }
   else{
      SetFzzSignalImplauState(cFZZ_IC_A3_TPM_ACTV_IMPLAU);
   }
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdVehSpeed(void){
   c12_km_p_h_0_409k4_0k1 data;
   Rte_Read_R_VehSpd_Disp_VehSpd_Disp(&data);
   ClearFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT);
   if(data < c12_km_p_h_0_409k4_0k1_UpperLimit){
      ClearFzzSignalUnplausibleState(cFZZ_VEH_SPEED_IMPLAU);
      tEnvDataToSend.ushVehSpeed = (uint16)(data/10);
      Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
      SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
   }
   else{
      SetFzzSignalImplauState(cFZZ_VEH_SPEED_IMPLAU);
      tEnvDataToSend.ushVehSpeed = 0;
      Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
      SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
   }
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdWhlPlsCnt(void){
   uint32 refTime;
   uint8 ucAbsTime;
   REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx tWheelPlsMsg;
   uint16 ushTESTABStick[4];

   Rte_Read_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2(&tWheelPlsMsg);

#if ABS_SIG_SIZE_ONEBYTE
   ushTESTABStick[0] = (uint8)tWheelPlsMsg.WhlPlsCnt_FL;
   ushTESTABStick[1] = (uint8)tWheelPlsMsg.WhlPlsCnt_FR;
   ushTESTABStick[2] = (uint8)tWheelPlsMsg.WhlPlsCnt_RL;
   ushTESTABStick[3] = (uint8)tWheelPlsMsg.WhlPlsCnt_RR;
#else
   ushTESTABStick[0] = tWheelPlsMsg.WhlPlsCnt_FL;
   ushTESTABStick[1] = tWheelPlsMsg.WhlPlsCnt_FR;
   ushTESTABStick[2] = tWheelPlsMsg.WhlPlsCnt_RL;
   ushTESTABStick[3] = tWheelPlsMsg.WhlPlsCnt_RR;
#endif

   ucAbsTime = (uint8)tWheelPlsMsg.WhlPlsCnt_TmStmp;

   GetSystemOperatingTime(&refTime);
   if(GetOpTimeMethodCurrent()==OP_TIME_METHOD_OHDS){
      if(((uint8)(refTime & 0x0000007F)) > ucAbsTime){ucEspDelayTime =  ((uint8)(refTime & 0x0000007F)) - ucAbsTime;}
      else                                           {ucEspDelayTime =  ((uint8)(refTime & 0x0000007F)) - ucAbsTime + 0x80;}
   }
   else                                              {ucEspDelayTime = GetPalAbsConstantDelay();}

   if(refTime < ucEspDelayTime){refTime += -ucEspDelayTime + 0xFFFFFFFF + 1;}
   else                        {refTime -=  ucEspDelayTime;}

   if((uint8)tWheelPlsMsg.WhlPlsCnt_FL != I_C08_IMPULSES_0_254_1_SNA){ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_FL_IMPLAU);} else{SetFzzSignalImplauState(cFZZ_WHLPLS_FL_IMPLAU); ReNewABSRef();}
   if((uint8)tWheelPlsMsg.WhlPlsCnt_FR != I_C08_IMPULSES_0_254_1_SNA){ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_FR_IMPLAU);} else{SetFzzSignalImplauState(cFZZ_WHLPLS_FR_IMPLAU); ReNewABSRef();}
   if((uint8)tWheelPlsMsg.WhlPlsCnt_RL != I_C08_IMPULSES_0_254_1_SNA){ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_RL_IMPLAU);} else{SetFzzSignalImplauState(cFZZ_WHLPLS_RL_IMPLAU); ReNewABSRef();}
   if((uint8)tWheelPlsMsg.WhlPlsCnt_RR != I_C08_IMPULSES_0_254_1_SNA){ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_RR_IMPLAU);} else{SetFzzSignalImplauState(cFZZ_WHLPLS_RR_IMPLAU); ReNewABSRef();}

   if((uint8)tWheelPlsMsg.WhlPlsCnt_TmStmp != I_C08_MS_0_254_1_SNA){ClearFzzSignalUnplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU);}
   else                                                            {SetFzzSignalImplauState       (cFZZ_TRACTION_SYSTEM_IMPLAU);}

   PutABS((uint16)refTime, ushTESTABStick);
   ClearFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT);

#if !(USE_VEH_DIR_INFO)
   if(bCarAbsStickStandstill()){
      if(bGetBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE)){
         ClearBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE);
      }
   }
   else{
      if(bRvsGearUsed == 0){
         ClearBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);
         if(!bGetBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE)){
            if(bResetAbsRefPoint())
               ReNewABSRef();
            SetBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE);
         }
      }
      else{
         if(!bGetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT)){
            if(bResetAbsRefPoint())
               ReNewABSRef();
            SetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);
         }
      }
   }
#endif
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveTelData(void){
   uint16 ushLinABStick[4];
   uint16 ushTimeStamp;
   DT_tData2Alloc tReData4Alloc;
   DT_tData2Warn tData2Warn;
   uint8 ucZomPos, ucTxTrigger,ucLTS;
   sint8 scTireTemp;
   uint8 ucLastTirePressure, ucStatusField0, ucStatusField1;
   uint16 ushlookBackTime;
   uint8 ucReTel4FD=TRUE;
   Rte_Read_PP_RfStructIn_DE_auRfStruct(&tReTelData);
   ucRecEvent++;
   ucTelType = tReTelData[5];
   ulTelTimeStamp = ((tReTelData[0]<<0) + (tReTelData[1]<<8) + (tReTelData[2]<<16) + (tReTelData[3]<<24));

   if(PAL_TEL_CST_DELAY_TIME < ulTelTimeStamp){ulTelTimeStamp -=              PAL_TEL_CST_DELAY_TIME;}
   else                                       {ulTelTimeStamp += 0xFFFFFFFF - PAL_TEL_CST_DELAY_TIME + 1;}

   ushTimeStamp = (uint16) ulTelTimeStamp;
   ulTelID =  ((tReTelData[6]<<24) + (tReTelData[7]<<16) + (tReTelData[8]<<8) + (tReTelData[9]<<0));
   ucTelAvgRSSI = tReTelData[30];
   ucNoiseLevel = tReTelData[4];

   if((ucTelType == cTelTypeSELPAL) || (ucTelType == cTelTypeSELPAL1)){
      ucTelPal = tReTelData[12];
      ucTelP = tReTelData[10];
      ucTelT = tReTelData[11];
      ucStatusField0 = tReTelData[13];
      ucStatusField1 = tReTelData[14];
      ucLTS = (ucStatusField1&0x03);
      ucTxTrigger = (ucStatusField1&0xC0)>>6;
   }
   else if((ucTelType == cTelTypeAK35def) || (ucTelType == cTelTypeAK35defLMA) || (ucTelType == cTelTypeAK35defLF)){
      ucTelPal = 0;
      ucTelP = tReTelData[10];
      ucTelT = tReTelData[11];
      ucStatusField0 = 0;
      ucStatusField1 = 0;
      ucLTS = 0;
      ucTxTrigger = 0;
   }
   else{
      ucTelPal = 0;
      ucTelP = 0x00;
      ucTelT = 0x00;
      ucStatusField0 = 0;
      ucStatusField1 = 0;
      ucLTS = 0;
      ucTxTrigger = 0;
   }

   if(ucPassTimeFilter(ulTelID, ucTelType, ulTelTimeStamp)){
      Rte_Write_PP_RfStructOut_DE_auRfStruct((const DT_auRfStruct*) &tReTelData);
      if(
            (ucTelType == 0x00)
         || (ucTelType == 0x01)
         || (ucTelType == 0x03)
         || (ucTelType == 0x20)
         || (ucTelType == 0x23)
         || (ucTelType == 0xC3)
         || (ucTelType == 0xC1)
         || (ucTelType == 0xCA)
      ){
         BuildTelStatistics(ulTelID, ucTelP, ucTelT, ulTelTimeStamp, bSensorDefect (ulTelID,ucTelType,ucTelP,ucTelT));
      }
      if(!bSensorDefect (ulTelID,ucTelType,ucTelP,ucTelT)){
         if(
               (ucTelType == cTelTypeSELPAL)
            || (ucTelType == cTelTypeSELPAL1)
            || (ucTelType == cTelTypeAK35def)
            || (ucTelType == cTelTypeAK35defLMA)
         ){
            if(LearningWheelPosActiveSM() == TRUE){
               ushlookBackTime = (ucTelPal>2) ? (ucTelPal-2)*5 :  10;

               if(ushTimeStamp < ushlookBackTime) {LinABS(ushTimeStamp - ushlookBackTime + 0xFFFF);}
               else                               {LinABS(ushTimeStamp - ushlookBackTime);}

               GetLinABS(ushLinABStick);
               tReData4Alloc.ulID =  ulTelID;
               tReData4Alloc.ucPalData = ucTelPal;
               tReData4Alloc.ushTimeStamp = (uint16)ushTimeStamp;
               tReData4Alloc.ucTelType = ucTelType;
               tReData4Alloc.ucFrameCounter = ucStatusField0;
               tReData4Alloc.ushAbsStickFL = ushLinABStick[0];
               tReData4Alloc.ushAbsStickFR = ushLinABStick[1];
               tReData4Alloc.ushAbsStickRL = ushLinABStick[2];
               tReData4Alloc.ushAbsStickRR = ushLinABStick[3];
               Rte_Call_PP_Data2Walloc_OP_SendData2Walloc(&tReData4Alloc);
            }
         }

         if(
               (ucGetColOfID(&ulTelID)<cMaxLR)
            && (
                     (ucTelType == cTelTypeSELPAL)
                  || (ucTelType == cTelTypeSELPAL1)
                  || (ucTelType == cTelTypeAK35def)
                  || (ucTelType == cTelTypeAK35defLMA)
               )
            && (bGetSensorStateMissing(ucGetColOfID(&ulTelID)) != TRUE)
         ){
            tData2Warn.ucP = ucGetLastReceivedPress(ulTelID);
            tData2Warn.ucT = ucGetLastReceivedTemp(ulTelID);
            tData2Warn.ulID = ulTelID;
            tData2Warn.ucTxTrigger = ucTxTrigger;
            tData2Warn.ucZomPos = ucGetColOfID(&ulTelID);
            Rte_Call_PP_Data2Warn_OP_SendTelData2WarnHdlr(&tData2Warn);
            ucReTel4FD = TRUE;
         }
         else{
            ucReTel4FD = FALSE;
         }

         if(
               (ucGetColOfID(&ulTelID) < cAnzRad)
            && (tEnvDataToSend.ucKlState == TRUE)
            && (ucTxTrigger == 3)
         ){
            ResetStanbyTimer();
         }

         if(
               (ucTelType == cTelTypeSELPAL)
            || (ucTelType == cTelTypeSELPAL1)
            || (ucTelType == cTelTypeAK35def)
            || (ucTelType == cTelTypeAK35defLMA)
         ){
            Rte_Call_PP_GetWANonVolatileData_OP_GetHistWPOfID(ulTelID, &ucZomPos);
            if(ucGetColOfID(&ulTelID)<cMaxLR){
#ifndef FD_CONTROLS_FALLBACK
               Check4PWP ();
#endif
               if(cRadPosHR < ucZomPos){
                  ucZomPos = USEui8PWPofHistCol(ucGetColOfID(&ulTelID));
               }
            }
            if((cRadPosHR >= ucZomPos) && (ucReTel4FD == TRUE)){
               FillingDetectionAFDIII(ucTxTrigger);
               if(ucZomPos == cRadPosVL){
                  scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
                  ClearBitInNoCheckPmin4StopFD(cFD_Pmin_FL);
                  if(
                        (
                              (bGETucCalRequestState(cCAL_MANUAL_ACTIV))
                           && (bGetBitFahrzeugzustandFZZ(cKFZFAEHRT_20KMH ) == TRUE )
                        )
                     || (
                              (bGETucCalRequestState(cCAL_AUTO_ACTIV))
                           && (GETushFDtimeout() > 0)
                        )
                  ){
                     ucLastTirePressure = ucGetAvgPress4FD(ulTelID);
                     if(
                           (ucLastTirePressure != 0xFF)
                        && (ucLastTirePressure != 0x00)
                     ){
                        if(GETucRErecCounter4FDVL() < ucGetAvgCntr4FD(ulTelID)){
                           PUTucRErecCounter4FDVL(ucGetAvgCntr4FD(ulTelID));
                        }
                        PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID));
                        PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID));
                        PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID));
                     }
                     if((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0)){
                        ucLastTirePressure = ucGetLastReceivedPress(ulTelID);
                        FD_HandleReceivedReRadPosVL4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS);
                     }
                  }
               }
               else if(ucZomPos == cRadPosVR){
                  scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
                  ClearBitInNoCheckPmin4StopFD(cFD_Pmin_FR);
                  if(
                        (
                              (bGETucCalRequestState(cCAL_MANUAL_ACTIV))
                           && (bGetBitFahrzeugzustandFZZ(cKFZFAEHRT_20KMH) == TRUE)
                        )
                     || (
                              (bGETucCalRequestState(cCAL_AUTO_ACTIV))
                           && (GETushFDtimeout() > 0)
                        )
                  ){
                     ucLastTirePressure = ucGetAvgPress4FD(ulTelID);
                     if(
                           (ucLastTirePressure != 0xFF)
                        && (ucLastTirePressure != 0x00)
                     ){
                        if(GETucRErecCounter4FDVR() < ucGetAvgCntr4FD(ulTelID)){
                           PUTucRErecCounter4FDVR(ucGetAvgCntr4FD(ulTelID));
                        }
                        PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID));
                        PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID));
                        PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID));
                     }
                     if((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0)){
                        ucLastTirePressure = ucGetLastReceivedPress(ulTelID);
                        FD_HandleReceivedReRadPosVR4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS);
                     }
                  }
               }
               else if(ucZomPos == cRadPosHL){
                  scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
                  ClearBitInNoCheckPmin4StopFD(cFD_Pmin_RL);
                  if(
                        (
                              (bGETucCalRequestState(cCAL_MANUAL_ACTIV))
                           && (bGetBitFahrzeugzustandFZZ(cKFZFAEHRT_20KMH ) == TRUE)
                        )
                     || (
                              (bGETucCalRequestState(cCAL_AUTO_ACTIV))
                           && (GETushFDtimeout() > 0)
                        )
                  ){
                     ucLastTirePressure = ucGetAvgPress4FD(ulTelID);
                     if(
                           (ucLastTirePressure != 0xFF)
                        && (ucLastTirePressure != 0x00)
                     ){
                        if(GETucRErecCounter4FDHL() < ucGetAvgCntr4FD(ulTelID)){
                           PUTucRErecCounter4FDHL(ucGetAvgCntr4FD(ulTelID));
                        }
                        PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID));
                        PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID));
                        PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID));
                     }
                     if(
                           (bGETucCalRequestState(cCAL_AUTO_ACTIV))
                        && (GETushFDtimeout() > 0)
                     ){
                        ucLastTirePressure = ucGetLastReceivedPress(ulTelID);
                        FD_HandleReceivedReRadPosHL4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS);
                     }
                  }
               }
               else if(ucZomPos == cRadPosHR){
                  scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc);
                  ClearBitInNoCheckPmin4StopFD(cFD_Pmin_RR);
                  if(
                        (
                              (bGETucCalRequestState(cCAL_MANUAL_ACTIV))
                           && (bGetBitFahrzeugzustandFZZ(cKFZFAEHRT_20KMH) == TRUE)
                        )
                     || (
                              (bGETucCalRequestState(cCAL_AUTO_ACTIV))
                           && (GETushFDtimeout() > 0)
                        )
                  ){
                     ucLastTirePressure = ucGetAvgPress4FD(ulTelID);
                     if(
                           (ucLastTirePressure != 0xFF)
                        && (ucLastTirePressure != 0x00)
                     ){
                        if(GETucRErecCounter4FDHR() < ucGetAvgCntr4FD(ulTelID)){
                           PUTucRErecCounter4FDHR(ucGetAvgCntr4FD(ulTelID));
                        }
                        PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID));
                        PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID));
                        PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID));
                     }
                     if(
                           (bGETucCalRequestState(cCAL_AUTO_ACTIV))
                        && (GETushFDtimeout() > 0)
                     ){
                        ucLastTirePressure = ucGetLastReceivedPress(ulTelID);
                        FD_HandleReceivedReRadPosHR4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS);
                     }
                  }
               }
            }
         }
      }
   }
   GetZOMInfos2BeLogged();
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveWAState(void){
   DT_ushWAState ushWaState;
   Rte_Read_PP_WAState_DE_ushWAState(&ushWaState);
   if((ushWaState & cWAChange) > 0){
      ClearBitBetriebszustandBZ(cEIGENRAD | cZUGEORDNET);
      ClearTelStatisticsStruct((ushWaState & cWAChange)>>4);
   }

   if(((ushWaState>>8) & cTO) == cTO){  SetBitBetriebszustandBZ(cZO_TIMEOUT);}
   else                              {ClearBitBetriebszustandBZ(cZO_TIMEOUT);}

   if(((ushWaState>>8) & cErrorActive) == cErrorActive){
      ClearBitBetriebszustandBZ(cZO_ERROR | cAL_RUNNING);
      SetBitBetriebszustandBZ(cZO_ERROR);
      if((ushWaState      & cWAStateER) == cWAStateER){SetBitBetriebszustandBZ(cER_FINISH);}
      if(((ushWaState>>8) & cTZG)       == cTZG      ){SetBitBetriebszustandBZ(cTEILZUGEORDNET);}
   }
   else{
      ClearBitBetriebszustandBZ(cZO_ERROR | cTEILZUGEORDNET);
           if((ushWaState & cWAStateZO) == cWAStateZO){SetBitBetriebszustandBZ(cER_FINISH | cZO_FINISH); ClearBitBetriebszustandBZ(cAL_RUNNING);}
      else if((ushWaState & cWAStateER) == cWAStateER){SetBitBetriebszustandBZ(cER_FINISH);              ClearBitBetriebszustandBZ(cZO_FINISH);}
      else{
         ClearBitBetriebszustandBZ(cER_FINISH | cZO_FINISH);
         if((ushWaState & cWAStateActive) == cWAStateActive){  SetBitBetriebszustandBZ(cAL_RUNNING);}
         else                                               {ClearBitBetriebszustandBZ(cAL_RUNNING);}
      }
   }
   if((ushWaState & (cWAIDChanged | cWAWPChanged )) > 0){
      ReplayLastREvalue2Walgo();
      if((ushWaState & (cWAIDChanged)) > 0){
         if(
               ((bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE))
            || ((bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE) && (bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE))
         ){
            PUTushFDtimeout(0);
            PUTucFDtimerStop(TRUE);
            SetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD);
         }
         SetBitCalRequestState2Ram(cCAL_AUTO_NEW_ID);
         ClearBitCalRequestState(cCAL_AUTO_ACTIV);
      }
      ZomChangedWuInfoDcm(ushWaState);

#ifndef FD_CONTROLS_FALLBACK
      ClearPWP();
      if((ushWaState & cWAStateER) == cWAStateER)
         Check4PWP();
#endif
   }
   else if(cAL_Error == ui8GetALState()){
      ReplayLastREvalue2Walgo ();
   }
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveWarnOut(void){
   uint8 ucCol;
   ucCol = ucGetColOfID(&ulTelID);
   if((ucCol < cMaxLR) && (ui8GetWarntypeOfHistCol(cDAG_PMin_WN,ucCol) == 0xFF)){SetPminDetected(TRUE);}
   else                                                                         {SetPminDetected(FALSE);}
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_SI_GetInternalClock(P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) ulInternalCLock){GetInternMSTime(ulInternalCLock);}
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutEngCtrl(void){SetFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT);}
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutEnvPressure(void){SetFzzSignalTimeOutState(cFZZ_PRESS_OUT_TIMEOUT);}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcBasicInfo(void){
   tEnvDataToSend.ushVehSpeed = 0;
   Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
   SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
   SetFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcDateTime(void){SetFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT);}
FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcSettings(void){SetFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT);}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIgnStat(void){
   tEnvDataToSend.ucKlState = Off;
   Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
   SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
   SetFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutPN14EOLDispRq(void){
   c03_EOL_Disp_Rq value;
   Rte_Read_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq(&value);
   if(
            (bOnce == FALSE)
         && (
                  (value == I_C03_EOL_DISP_RQ_IOD_MEAS)
               || (value == I_C03_EOL_DISP_RQ_IOD_ERR)
            )
   ){
      ResetStanbyTimer();
      bOnce = TRUE;
   }
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutSupPN14BatStat(void){SetFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT);}

#define Com_PduGrp_TxMess_TPM_HMI            (Com_PduGroupIdType) 0 //TBD:
typedef uint8 Com_PduGroupIdType; //TBD:
extern FUNC(void, COM_CODE) Com_IpduGroupStart(Com_PduGroupIdType IpduGroupId, boolean Initialize); //TBD:

extern FUNC(void, COM_CODE) Com_IpduGroupStop(Com_PduGroupIdType IpduGroupId); //TBD:

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutWhlPlsCnt(void){
   uint32 refTime;
   uint16 ushTESTABStick[5];
#if ABS_SIG_SIZE_ONEBYTE
   ushTESTABStick[0] = (uint8)0xFF;
   ushTESTABStick[1] = (uint8)0xFF;
   ushTESTABStick[2] = (uint8)0xFF;
   ushTESTABStick[3] = (uint8)0xFF;
#else
   ushTESTABStick[0] = (uint16)0xFFFF;
   ushTESTABStick[1] = (uint16)0xFFFF;
   ushTESTABStick[2] = (uint16)0xFFFF;
   ushTESTABStick[3] = (uint16)0xFFFF;
#endif

   GetSystemOperatingTime(&refTime);
   PutABS((uint16)refTime, ushTESTABStick);
   SetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT);
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrBusMsg(void){
   if((bGETucCalRequestState(cCAL_MSG2DISP) == TRUE) && (GETucTimer4MsgDispRq() != 0 )){
      setTireStatMsgDispRestart();
   }
   else{
      clearTireStatMsgDispRestart();
      ClearBitCalRequestState(cCAL_MSG2DISP);
   }
   if(bGetBitBetriebszustandBZ(cZO_ERROR | cZO_TIMEOUT)){
      NewPositionsUSWIF((uint8*)GETpucStartAdrWPorPWP());
   }
   else if(bGetBitBetriebszustandBZ(cZO_FINISH)){
      NewPositionsUSWIF((uint8*)GETpucStartAdrWPorPWP());
   }
   if(GETucMeasurementStateOfRam() == TRUE){
      Com_IpduGroupStart(Com_PduGrp_TxMess_TPM_HMI, TRUE);
   }
   else{
      Com_IpduGroupStop(Com_PduGrp_TxMess_TPM_HMI);
   }
   UpdateTxBusMsg();
   UpdateCanMState();
   Rte_Write_P_RefPress_RefPress(pGetHmiRefPress());
#if E2E_ENABLE
   ucHufE2EWrapperProtectTireState2((uint8*) pGetTpmLmpOnRq());
#endif
   Rte_Write_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2(pGetTpmLmpOnRq());
   Rte_Write_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old(pGetTpmLmpOnRqOld());
   Rte_Write_P_Tire_Stat_V2_Tire_Stat_V2(pGetTireStat());
   Rte_Write_P_Tire_Temp_V2_Tire_Temp_V2(pGetTireTemp());
   Rte_Write_P_WakeupRsn_TPM_WakeupRsn_TPM(ucGetHMIWakeUpRsn());
   Rte_Write_P_Awake_Diag_Actv_Awake_Diag_Actv(bGetHMIAwakeDiagActv());
   Rte_Write_P_Awake_Ignition_On_Awake_Ignition_On(bGetHMIAwakeIgnitionOn());
   Rte_Write_P_Awake_NwSt_Awake_NwSt(bGetHMIAwakeNwSt());
   Rte_Write_P_Awake_Warn_Actv_Awake_Warn_Actv(bGetHMIAwakeWarnActv());
}

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrDisplayMsg(void){
   ARR_08_UInt_noSNA_8 tHufDevMsg;
   DT_HufDisplay temp;
   if(GETucMeasurementStateOfRam() == TRUE){
      if(ucTraceGetDataFromQueue(&temp )){
         tHufDevMsg[0] = temp.Byte0;
         tHufDevMsg[1] = temp.Byte1;
         tHufDevMsg[2] = temp.Byte2;
         tHufDevMsg[3] = temp.Byte3;
         tHufDevMsg[4] = temp.Byte4;
         tHufDevMsg[5] = temp.Byte5;
         tHufDevMsg[6] = temp.Byte6;
         tHufDevMsg[7] = temp.Byte7;
         Rte_Write_P_Meas_TPM_1_Meas_XX((const ARR_08_UInt_noSNA_8*) &tHufDevMsg);
      }
   }
}

extern uint8 GetucTPM_WarnDisp_Rq(void); //TBD:

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrTpmMsgDispRq(void){
uint8 ucRtn=FALSE;
      FD_UpdateComparePressureAtWarning(GetucTPM_WarnDisp_Rq());
  if(GETucTimer4MsgDispRq()  > 0){
      DECucTimer4MsgDispRq();
      if(GETucTimer4MsgDispRq() == FALSE){
       ReplayLastREvalue2Walgo();
       }
   }
   if(GETushFDtimeout()  > 0){
      if(bGetBitFahrzeugzustandFZZ(cKFZFAEHRT_20KMH ) == TRUE){
         DECushFDtimeout();
         DECushSupervisoryTimerFD();
      }
      if(
            (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE)
         && (GETucTimer4MsgDispRq() == FALSE)
      ){
         if(FD_FlowChartFct1CheckPmin() == TRUE){
            if(FD_FlowChartFct1CheckMissingRE() == TRUE){
               if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE){
                  FD_Check3RePlausiSetMilage4FinishedMFD();
               }
               else{
                  FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD();
               }
            }
         }
      }
   }
  else{
      ucRtn=FALSE;
      if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE){
         if(GETucFDtimerStop() == FALSE){
            if(GETushSupervisoryTimerFD() == GETushFDtimeout()){
               PUTushSupervisoryTimerFD(6);
               ucRtn=TRUE;
            }
            else{
               if(   GETushSupervisoryTimerFD() > 1 ){
                  DECushSupervisoryTimerFD();
                  ucRtn=TRUE;
               }
               else{
                  ucRtn=FALSE;
               }
            }
            if(
                  (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE )
               && (
                        (ui8GetALState()      == cAL_Stored)
                     || (ui8GetALState()      == cAL_OK)
                     || (Getui8ColPWPActive() != FALSE)
                  )
            ){
               if(ucRtn == TRUE){
                  if(FD_UpdateIDvalue4MFD() == TRUE){
                     if(FD_FlowChartFct1() == TRUE){
                        FD_Check3RePlausiSetMilage4FinishedMFD();
                     }
                     else{
                        ucRtn=FALSE;
                     }
                  }
               }
            }
            else{
            }
         }
      }
      if(FALSE == ucRtn){
         if(
               (bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE)
            && (GETucTimer4MsgDispRq() == FALSE)
         ){
            if(
                  (ushGetCurrentECUParkingTime() >= cT_STANBY )
               && (bGetBitFahrzeugzustandFZZ(cKL_15_EIN )   == TRUE)
               && (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)
               && (bGETucCalRequestState(cCAL_AUTO_FIRST)   == TRUE)
            ){
               ClearBitBetriebszustandBZ(cCAL_REQUEST);
               FillingDetectionMFD(FALSE);
            }
            else{
               if(
                     (GETucFDtimerStop() == FALSE)
                  && (bGETucCalRequestState(cCAL_AUTO_NEW_ID) == FALSE)
               ){
                  if(
                        (bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)
                     || (bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)
                  ){
                     if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE){
                        if(GETushSupervisoryTimerFD() == GETushFDtimeout()){
                           PUTushSupervisoryTimerFD(6);
                        }
                        else{
                           if(GETushSupervisoryTimerFD() > 1){
                              DECushSupervisoryTimerFD();
                              if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE){
                                 PUTucFDtimerStop(TRUE);
                              }
                           }
                           else{
                              PUTucFDtimerStop(TRUE);
                           }
                        }
                     }
                     else{
                        PUTucFDtimerStop(TRUE);
                     }
                  }
               }
               else{
                  if(FD_FlowChartFct1() == TRUE){
                     if(bGETucCalRequestState(cCAL_AUTO_NEW_ID) == TRUE){
                        FD_AbortFillingDetection(cCAL_AUTO_NEW_ID);
                     }
                     else{
                        FD_AbortFillingDetection(cCAL_ABORT_REASON_2_3);
                     }
                  }
               }
            }
         }
         else{
            if(bGETucCalRequestState(cCAL_AUTO_NEW_ID) == TRUE){
               ucRtn=FD_LoadIdValues4UpdateCompareValue();
               if(ucRtn == TRUE){
                  ClearBitCalRequestState(cCAL_AUTO_NEW_ID);
               }
               else{
                  if(
                        (bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE )
                     || (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE)
                  ){
                     ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2);
                     if(ucRtn == FALSE){
                        SetBitFillingDetectionStateFD(cFILLING_NOT_DETECTED);
                     }
                     else{
                        SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);
                        SetState2AbortReasonFD(cFD_FBM_ACTIV);
                        SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK);
                     }
                  }
               }
            }
         }
      }
   }
}
#define RTE_STOP_SEC_CTAPHUFTPMSMGR_APPL_CODE
#include "MemMap.h"

void Appl_CanSM_BusOffBegin(NetworkHandleType CanSm_NetworkHandle, CanSM_BorCounterType CanSM_BufOffNotificationCounter){
   UNUSED(CanSm_NetworkHandle);
   UNUSED(CanSM_BufOffNotificationCounter);
   SetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network);
}

void Appl_CanSM_BusOffEnd(NetworkHandleType CanSm_NetworkHandle){
   UNUSED(CanSm_NetworkHandle);
   ClearFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network);
}

boolean LearningWheelPosActiveSM(void){
   boolean bLearnActive = FALSE;

   if(bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT)){
      if(bGetBitBetriebszustandBZ(cZO_FINISH) == FALSE ){
         if(bGetBitBetriebszustandBZ(cZO_TIMEOUT ) == FALSE ){bLearnActive = TRUE;}
         else                                                {bLearnActive = FALSE;}
      }
      else{
         bLearnActive = FALSE;
      }
   }
   else{
      bLearnActive = FALSE;
   }
   return bLearnActive;
}

static void GetZOMInfos2BeLogged(void){
   uint8 ucIDPosInZom;
   uint16 i;
   uint8 ucTemp1, ucTemp2;
   debugTelStructPos *tdebugTelStructPos;
   debutTelWallocStruct tDebutTelWallocStruct;
   Rte_Call_PP_GetZomData_OP_GetZomPosOfID(ulTelID, &ucIDPosInZom);
   tDebugTelStruct.ulID = ulTelID;
   tDebugTelStruct.ucIDPosInZom = ucIDPosInZom;
   tDebugTelStruct.ulTimeStamp = ulTelTimeStamp;
   tDebugTelStruct.ucPAL = ucTelPal;
   tDebugTelStruct.ucP = ucGetLastReceivedPress(ulTelID);
   tDebugTelStruct.ucT = ucGetLastReceivedTemp(ulTelID);
   tDebugTelStruct.ucAvgRssi = ucTelAvgRSSI;
   tDebugTelStruct.ucTelType = ucTelType;
   tDebugTelStruct.ucTelByte00 = tReTelData[ 5];
   tDebugTelStruct.ucTelByte01 = tReTelData[ 6];
   tDebugTelStruct.ucTelByte02 = tReTelData[ 7];
   tDebugTelStruct.ucTelByte03 = tReTelData[ 8];
   tDebugTelStruct.ucTelByte04 = tReTelData[ 9];
   tDebugTelStruct.ucTelByte05 = tReTelData[10];
   tDebugTelStruct.ucTelByte06 = tReTelData[11];
   tDebugTelStruct.ucTelByte07 = tReTelData[12];
   tDebugTelStruct.ucTelByte08 = tReTelData[13];
   tDebugTelStruct.ucTelByte09 = tReTelData[14];
   GETDAGWrnLvlOfIdCol(ucGetColOfID(&tDebugTelStruct.ulID), (uint8*)&tDebugTelStruct.ushPref_WTPmin);
   tDebugTelStruct.ushTref_WTHW = 0xFF;
   tDebugTelStruct.ushTref_WTWW = 0xFF;
   tDebugTelStruct.ECU_C_RecBlocks = ui8GetComptoirRepare();

   if(ucGetColOfID(&ulTelID)<4){
      tDebugTelStruct.ucPcompCurrID = ui8GetPRelComp2Tref((sint8)(tDebugTelStruct.ucT-ucPalTempNormFACTORc), ucGetColOfID(&ulTelID));
      tDebugTelStruct.ucPrefCurrID = ui8GetPRefRel(ucGetColOfID(&ulTelID));
      tDebugTelStruct.ucTrefCurrID = i8GetTref(ucGetColOfID(&ulTelID));
   }
   else{
      tDebugTelStruct.ucPcompCurrID = 0xFF;
      tDebugTelStruct.ucPrefCurrID = 0xFF;
      tDebugTelStruct.ucTrefCurrID = 0xFF;
   }
   if(GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) < cAnzRad){
           if(GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) == cRadPosVL){tdebugTelStructPos = &tdebugTelStructPosFL;}
      else if(GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) == cRadPosVR){tdebugTelStructPos = &tdebugTelStructPosFR;}
      else if(GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) == cRadPosHL){tdebugTelStructPos = &tdebugTelStructPosRL;}
      else                                                           {tdebugTelStructPos = &tdebugTelStructPosRR;}
      tdebugTelStructPos->ucEcuRFRSSI = ucTelAvgRSSI;
   }
   tDebugTelStruct.ucRecEvent = ucRecEvent;
   Rte_Call_PP_GetZomData_OP_GetZomPosOfID(ulTelID, &ucIDPosInZom);
   Rte_Call_PP_GetZomData_OP_GetZomStatisticTelCounter(ucIDPosInZom, &tDebutTelWallocStruct.ucZomStatTelCounter);
   tDebutTelWallocStruct.ucZomToothTelCtLearnBit = ucGetZomTelCtLearnBit(ucIDPosInZom);
   Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrLearnBit(ucIDPosInZom, &ucTemp1);
   Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrNoLearnBit(ucIDPosInZom, &ucTemp2);
   tDebutTelWallocStruct.ucZomToothTelCtCorr = ((ucTemp1 + ucTemp2) < 0xFF) ? (ucTemp1 + ucTemp2) : 0xFF;
   Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoCorr(ucIDPosInZom, &tDebutTelWallocStruct.ucZomToothTelCtrNoCorr);
   ucTemp1 = tDebutTelWallocStruct.ucZomToothTelCtCorr;
   ucTemp2 = tDebutTelWallocStruct.ucZomToothTelCtrNoCorr;
   tDebutTelWallocStruct.ucZomToothTelCtNoLearnMode = (ucTelStatGetLastRxBlocs(ulTelID) > (ucTemp1 + ucTemp2)) ? (ucTelStatGetLastRxBlocs(ulTelID) - ucTemp1 - ucTemp2) : 0;
   Rte_Call_PP_GetZomData_OP_GetZomStatus(ucIDPosInZom, &tDebutTelWallocStruct.ucZomStatus);
   Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFL(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumFL);
   Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFR(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumFR);
   Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRL(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumRL);
   Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRR(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumRR);
   Rte_Call_PP_GetZomData_OP_GetZomAbsLinFL(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsLinFL);
   Rte_Call_PP_GetZomData_OP_GetZomAbsLinFR(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsLinFR);
   Rte_Call_PP_GetZomData_OP_GetZomAbsLinRL(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsLinRL);
   Rte_Call_PP_GetZomData_OP_GetZomAbsLinRR(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsLinRR);
   Rte_Call_PP_GetZomData_OP_GetZomAbsCompFL(ucIDPosInZom, &tDebutTelWallocStruct.ucZomAbsCompFL);
   Rte_Call_PP_GetZomData_OP_GetZomAbsCompFR(ucIDPosInZom, &tDebutTelWallocStruct.ucZomAbsCompFR);
   Rte_Call_PP_GetZomData_OP_GetZomAbsCompRL(ucIDPosInZom, &tDebutTelWallocStruct.ucZomAbsCompRL);
   Rte_Call_PP_GetZomData_OP_GetZomAbsCompRR(ucIDPosInZom, &tDebutTelWallocStruct.ucZomAbsCompRR);
   TracePutTelWallocData2Queue(&tDebutTelWallocStruct);
   TracePutTelStr2Queue(&tDebugTelStruct);
   for (i=0;i<sizeof(tDebugTelStruct);i++){
      *((uint8*)&tDebugTelStruct + i) = 0;
   }
}

boolean GETbCalPminInvalidCAL(void){
   return FALSE;
}

boolean GETbCalReqCAL(void){
  if(0 != (Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState & cCAL_MANUAL_ACTIV)){return TRUE;}
   else                                                                       {return FALSE;}
}

boolean GETbCalNotAck4PlausiCheckMFA(void){
   if(cCAL_VALID == (Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState & 0x0F)){return FALSE;}
   else                                                                   {return TRUE;}
}

void CheckDTCInactiveERR(void){}
void InitIDOM(void){}

void PUTucPcalMinVaRelativCod2Ram(uint8 x){
  Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinVaRelativCod = (x);
}

uint8 GETucPcalMinVaRelativCodOfRam(void){
  return Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinVaRelativCod;
}

void PUTucPcalMinVaRelativCod2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTucPcalMinHaRelativCod2Ram(uint8 x){
  Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinHaRelativCod = (x);
}

uint8 GETucPcalMinHaRelativCodOfRam(void){
  return Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinHaRelativCod;
}

void PUTucPcalMinHaRelativCod2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

uint8 GETucPosComparePressure(uint8 i){
  uint8 ui8ret = 0;
  if(i < cAnzRad ){
    ui8ret = (*((uint8*)&Rte_Pim_Pim_tCalNvMBlock()->aucPosComparePressure + i));
  }
  else{
    ui8ret = 0x00;
  }
   return ui8ret;
}

void PUTucPosComparePressure(uint8 x, uint8 i){
  NvM_RequestResultType ErrorStatus;

  if(i < cAnzRad){
    *((uint8*)&Rte_Pim_Pim_tCalNvMBlock()->aucPosComparePressure + i) = x;
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
    if(ErrorStatus  != NVM_REQ_PENDING){
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
    }
  }
}

void PUTulKmStand4AutoCAL(uint32 ulKmStand){
   ulKmStand4AutoCal= ulKmStand/10;
}

uint32 GETulKmStand4AutoCAL(void){
   return ulKmStand4AutoCal;
}

void PUTulLastCalMileage(uint32 x){
  NvM_RequestResultType ErrorStatus;
  Rte_Pim_Pim_tCalNvMBlock()->ulLastCalMileage = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus);
  if(ErrorStatus  != NVM_REQ_PENDING){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);
  }
}

uint32 GETulLastCalMileage(void){
   return Rte_Pim_Pim_tCalNvMBlock()->ulLastCalMileage;
}

#ifdef FDasNewNVMdata
void PUTscAverageFillTemperatur(sint8 x){
   *(sint8*)Rte_Pim_Pim_AverageFillTemperatur() = (x);
}

void PUTscAverageFillTemperaturNVM(sint8 x){}
sint8 GETscAverageFillTemperatur(void){}
void PUTucPfillFront(uint8 ucP){}
void PUTucPfillFront2NVM(void){}

uint8 GETucPfillFront(void){
  return *(uint8*)Rte_Pim_Pim_PfillFront();
}

void PUTucTfillFront(sint8 scT){}
void PUTucTfillFront2NVM(void){}
sint8 GETucTfillFront(void){}
void PUTucPfillRear(uint8 ucP){}
void PUTucPfillRear2NVM(void){}

uint8 GETucPfillRear(void){
  return *(uint8*)Rte_Pim_Pim_PfillRear();
}

void PUTucTfillRear(sint8 scT){}
void PUTucTfillRear2NVM(void){}

sint8 GETucTfillRear(void){
  return *(sint8*)Rte_Pim_Pim_TfillHA();
}
#endif

uint8 ucCheckLOW_PRESS_ReState(void){
   uint8 ucRtn = FALSE;
      if(GETbWrnPMin_FL()){
         ucRtn+=cFD_Pmin_FL;
      }
    if(GETbWrnPMin_FR()){
         ucRtn+=cFD_Pmin_FR;
      }
      if(GETbWrnPMin_RL()){
         ucRtn+=cFD_Pmin_RL;
      }
       if(GETbWrnPMin_RR()){
         ucRtn+=cFD_Pmin_RR;
      }
      if(GETbWrnPMin_UK()){
         ucRtn+=cFD_Pmin_UK;
      }
   return ucRtn;
}

extern uint8 GETucWPorPWPofHistCol(uint8 ucCol); //TBD:
uint8 ucCheckAllRePcalMinDPmanualMFD(void){
  uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;
   uint8 i;
   uint8 ucRtn=FALSE;
   for(i = 0; i < cAnzRad; i++ ){
      switch (GETucWPorPWPofHistCol(i)){
         case cRadPosVL: ucColOfIdVL = i; break;
         case cRadPosVR: ucColOfIdVR = i; break;
         case cRadPosHL: ucColOfIdHL = i; break;
         case cRadPosHR: ucColOfIdHR = i; break;
         default:
            ucRtn = TRUE;
      }
   }
   if(ucRtn == FALSE){
      if(GETucStoragePaverege4CompareValue(ucColOfIdVL) < (GETucPcalMinVaRelativCodOfRam() - cDP_MANUAL)){ucRtn = TRUE;}
      if(GETucStoragePaverege4CompareValue(ucColOfIdVR) < (GETucPcalMinVaRelativCodOfRam() - cDP_MANUAL)){ucRtn = TRUE;}
      if(GETucStoragePaverege4CompareValue(ucColOfIdHL) < (GETucPcalMinHaRelativCodOfRam() - cDP_MANUAL)){ucRtn = TRUE;}
      if(GETucStoragePaverege4CompareValue(ucColOfIdHR) < (GETucPcalMinHaRelativCodOfRam() - cDP_MANUAL)){ucRtn = TRUE;}
   }
   else                                                                                                  {ucRtn = FALSE;}
   return ucRtn;
}

void ClearAllReCnt4FD(void){
   ucRErecCounter4FDVL = FALSE;
   ucRErecCounter4FDVR = FALSE;
   ucRErecCounter4FDHL = FALSE;
   ucRErecCounter4FDHR = FALSE;
}

uint8 GetOneReCnt4FD(void){
   uint8 ucRtn = FALSE;
   if(ucRErecCounter4FDVL != 0){ucRtn = TRUE;}
   if(ucRErecCounter4FDVR != 0){ucRtn = TRUE;}
   if(ucRErecCounter4FDHL != 0){ucRtn = TRUE;}
   if(ucRErecCounter4FDHR != 0){ucRtn = TRUE;}
  return ucRtn;
}

uint8 GETucRErecCounter4FDVL(void){return ucRErecCounter4FDVL;}
uint8 GETucRErecCounter4FDVR(void){return ucRErecCounter4FDVR;}
uint8 GETucRErecCounter4FDHL(void){return ucRErecCounter4FDHL;}
uint8 GETucRErecCounter4FDHR(void){return ucRErecCounter4FDHR;}
void PUTucRErecCounter4FDVL(uint8 x){ucRErecCounter4FDVL = x;}
void PUTucRErecCounter4FDVR(uint8 x){ucRErecCounter4FDVR = x;}
void PUTucRErecCounter4FDHL(uint8 x){ucRErecCounter4FDHL = x;}
void PUTucRErecCounter4FDHR(uint8 x){ucRErecCounter4FDHR = x;}
void INCucRErecCounter4FDVL(void){ucRErecCounter4FDVL++;}
void INCucRErecCounter4FDVR(void){ucRErecCounter4FDVR++;}
void INCucRErecCounter4FDHL(void){ucRErecCounter4FDHL++;}
void INCucRErecCounter4FDHR(void){ucRErecCounter4FDHR++;}
void PUTucTimer4MsgDispRq(uint8 x){ucTimer4MsgDispRq = x;}
uint8 GETucTimer4MsgDispRq(void){return ucTimer4MsgDispRq;}

void DECucTimer4MsgDispRq(void){
   if(ucTimer4MsgDispRq != 0){
      ucTimer4MsgDispRq--;
   }
}

void PUTushFDtimeout(uint16 x){ushFDtimeout = x;}
uint16 GETushFDtimeout(void){return ushFDtimeout;}

void DECushFDtimeout(void){
   if(ushFDtimeout != 0){
      ushFDtimeout--;
   }
}

void PUTushSupervisoryTimerFD(uint16 x){ushSupervisoryTimerFD = x;}
uint16 GETushSupervisoryTimerFD(void){return ushSupervisoryTimerFD;}

void DECushSupervisoryTimerFD(void){
   if(ushSupervisoryTimerFD != 0){
      ushSupervisoryTimerFD--;
   }
}

void PUTucOnceCheckMissingRE4FD(uint8 x){ucOnceCheckMissingRE4FD = x;}
uint8 GETucOnceCheckMissingRE4FD(void){return ucOnceCheckMissingRE4FD;}
void PUTucFDtimerStop(uint8 x){ucFDtimerStop = x;}
uint16 GETucFDtimerStop(void){return ucFDtimerStop;}
void PUTucMeasurementState2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->ucMeasurementOnOffCod = (x);}
uint8 GETucMeasurementStateOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->ucMeasurementOnOffCod;}

void PUTucMeasurementState2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTucMeasurementStateNvm2Ram(void){}

void PUTucCoastModeContCount2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->ucCoastModeCtrlCount = x;}
uint8 GETucCoastModeContCountOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->ucCoastModeCtrlCount;}

void PUTucCoastModeContCount2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTucMinWarnThreshold2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucMinWarnThreshold = x;}
uint8 GETucMinWarnThresholdOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucMinWarnThreshold;}
void PUTucAutoFillDetectionOnOff2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucAutoFillDetectionOnOff = x;}
uint8 GETucAutoFillDetectionOnOffOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucAutoFillDetectionOnOff;}
void PUTucT_Soft2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Soft = x;}
uint8 GETucT_SoftOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Soft;}
void PUTucPercent_Soft2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Soft = x;}
uint8 GETucPercent_SoftOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Soft;}
void PUTucT_Hard2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Hard = x;}
uint8 GETucT_HardOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Hard;}
void PUTucPercent_Hard2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Hard = x;}
uint8 GETucPercent_HardOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Hard;}
void PUTucTempWarnOnOff2Ram(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucTempWarnOnOff = x;}
uint8 GETucTempWarnOnOffOfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucTempWarnOnOff;}

void PUTLogicalDataPalCod2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTLogicalDataPalCodNvm2Ram(void){}

void PUTucV1ToRam(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV1 = x;}
uint8 GETucV1OfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV1;}
uint16 GETushV1(void){return (uint16) Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV1;}
void PUTucV2ToRam(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV2 = x;}
uint8 GETucV2OfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV2;}
uint16 GETushV2(void){return (uint16) Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV2;}
void PUTucV3ToRam(uint8 x){Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV3 = x;}
uint8 GETucV3OfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV3;}
uint16 GETushV3(void){return (uint16)Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV3;}
void PUTscT0ToRam(sint8 x){Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT0 = x;}
sint8 GETscT0OfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT0;}
void PUTscT1ToRam(sint8 x){Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT1 = x;}
sint8 GETscT1OfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT1;}
void PUTscT2ToRam(sint8 x){Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT2 = x;}
sint8 GETscT2OfRam(void){return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT2;}
void PUTushHCmaxToRam(uint8 x , uint8 y){Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX = (uint16)(x<<8) + (uint16)y;}
uint16 GETushHCmax(void){return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX;}
uint8 GETucHCmaxOfRamHbyte(void){return (uint8)(Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX>>8);}
uint8 GETucHCmaxOfRamLbyte(void){return (uint8)(Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX);}

void PUTTempWarnCod2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTTempWarnCodNvm2Ram(void){}

void PUTucKweight2Ram(uint8 x){
  Rte_Pim_Pim_tCodNvMBlock()->ucKweight = x;
}

void PUTucKweight2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

uint8 GETucKweightOfRam(void){
  uint8 Ret;
  Ret = Rte_Pim_Pim_tCodNvMBlock()->ucKweight;
  if(Ret > 100){
    Ret = 100;
  }
  return Ret;
}

void PUTucKweightNvm2Ram(void){}

void SetCodNvMBlockNewDataFlag(boolean bNewDataFlag){bWrCodNVMBlock = (boolean) bNewDataFlag;}
boolean bGetCodNvMBlockNewDataFlag(void){return (boolean)bWrCodNVMBlock;}

void AlignCodBlockRaM2NvM(void){
  NvM_RequestResultType ErrorStatus;
  if(bGetCodNvMBlockNewDataFlag() == TRUE){
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_GetErrorStatus(&ErrorStatus);
    if(ErrorStatus  != NVM_REQ_PENDING){
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_tCodNvMBlock());
      SetCodNvMBlockNewDataFlag(FALSE);
    }
  }
}

void PUTucLqi2Ram(uint8 x){*((uint8*)&Rte_Pim_Pim_tCodNvMBlock()->tCodReserved + 0) = x;}

void PUTucLqi2Nvm(void){
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

uint8 GETucLqiOfRam(void){
  uint8 ui8Ret = 0;
  ui8Ret = *((uint8*)&Rte_Pim_Pim_tCodNvMBlock()->tCodReserved + 0);
  return ui8Ret;
}

static void UpdateCanMState(void){
  ComM_ModeType ComMode;
  Dcm_SesCtrlType CurSession;
  EcuM_StateType  EcuM_State;
  Dcm_GetSesCtrlType(&CurSession);
  if((tEnvDataToSend.ucKlState==FALSE) && (CurSession==DCM_DEFAULT_SESSION)){
#if(ECU_SHUTDOWN_ENABLE)
    Rte_Call_UR_ComMUser_HMI_GetCurrentComMode(&ComMode);
    if(ComMode != COMM_NO_COMMUNICATION ){
      Rte_Call_UR_ComMUser_HMI_RequestComMode(COMM_NO_COMMUNICATION);
    }
#endif
  }
  if(bStanbyTimerElapsed()){
    (void)EcuM_GetState(&EcuM_State);
    if(EcuM_State == ECUM_STATE_APP_POST_RUN ){
      EcuM_ReleasePOST_RUN(EcuM_EcuMUserConfig_FirstUser);
    }
  }
}

void DcmFillingDetectionMFD(void){FillingDetectionMFD(TRUE);}

void ReplayLastREvalue2Walgo(void){
  DT_tData2Warn tData2Warn;
  uint8 i;
  for (i = 0; i < cMaxLR; i++){
    if(ucGetLastReceivedPress(ulGetID(i)) != 0xFF){
      tData2Warn.ucP = ucGetLastReceivedPress(ulGetID(i));
      tData2Warn.ucT = ucGetLastReceivedTemp(ulGetID(i));
      tData2Warn.ucTxTrigger = 0x01;
      tData2Warn.ulID = ulGetID(i);
      tData2Warn.ucZomPos = i;
      Rte_Call_PP_Data2Warn_OP_SendTelData2WarnHdlr(&tData2Warn);
    }
  }
}

void CountCoastModeClampCycle(void){
  uint8 uctempClampCnt;
    uctempClampCnt = GETucCoastModeContCountOfRam();
    if(uctempClampCnt>0){
      SkipStanbyTimer();
      uctempClampCnt--;
      PUTucCoastModeContCount2Ram(uctempClampCnt);
      PUTucCoastModeContCount2Nvm();
    }
    else{
      TPMS_NVM_ActivateWriteAll();
    }
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

