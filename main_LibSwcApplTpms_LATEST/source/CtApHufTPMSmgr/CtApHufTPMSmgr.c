/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  CtApHufTPMSmgr.c
 *     Workspace:  C:/_TSS/DAG/MFA2/Target/Config/Developer/HufTPMS_G6_F1L.dev
 *     SW-C Type:  CtApHufTPMSmgr
 *  Generated at:  Fri Dec 15 13:11:54 2017
 *
 *     Generator:  MICROSAR RTE Generator Version 2.27.0
 *                 RTE Core Version 1.6.0
 *       License:  License CBD1500122 valid for Huf Electronics Bretten GmbH Package: MSR Daimler SLP10 Micro: R7F7010133AFP Compiler: Green Hills 6.1.4
 *
 *   Description:  C-Code implementation template for SW-C <CtApHufTPMSmgr>
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* PRQA S 0777, 0779 EOF */ /* MD_Rte_0777, MD_Rte_0779 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *
 * AUTOSAR Modelling Object Descriptions
 *
 **********************************************************************************************************************

 Data Types:
 ===========
  DT_auRfStruct
    4  Byte timestamp
     24 Byte data
     6  Byte RSSI value

  NvM_DestPtr
    DataPtr Type to be used by WriteBlock, ReadBlock and RestoreBlockDefaults operations. 	This type is used for all NVRAM blocks

  REC_DateTm_AR2_f0ifkphxunpp94u3ro8qn5tdm
     (degraded)

  REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy
     (degraded)

  REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno
     (degraded)

  REC_PN14_SupBat_Stat_2is6fi0meeac78nkn35zc5ui3
     (degraded)

  REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt
     (degraded)

  REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx
     (degraded)


 Port Prototypes:
 ================
  P_Awake_Diag_Actv
    Wachhalten fuer Diagnose aktiv

  P_Awake_Ignition_On
    Wachhalten fuer Zuendung eingeschaltet

  P_Awake_NwSt
    Wachhalten fuer Netzwerkstartphase

  P_Awake_Warn_Actv
    Wachhalten wegen Warnung aktiv

  P_Meas_TPM_1
    Messdaten

  P_RefPress
    Referenzdruck

  P_TPM_Lmp_On_Rq_Pr2
    Anforderung Reifendruckkontrolle Lampe einschalten (degraded)

  P_TPM_Lmp_On_Rq_old
    Anforderung Reifendruckkontrolle Lampen einschalten

  P_Tire_Stat_V2
    Reifenstatus

  P_Tire_Temp_V2
    Reifentemperatur

  P_WakeupRsn_TPM
    Weckgrund

  R_AirPress_Outsd
    Aussenluftdruck

  R_AirTemp_Outsd_Disp
    Angezeigte Aussenlufttemperatur

  R_DateTm_AR2
    Datum und Uhrzeit (degraded)

  R_Eng_Rs_EngCtrl_Pr2
    Motoransprechverhalten Engine Control (degraded)

  R_Ign_Stat_Pr2
    Zuendungsstatus (degraded)

  R_OHDS_GetOperatingHours
    OHDS_GetOperatingHours

  R_Odo
    Kilometerstand (fuer alle, FFFFFEh: Signal ungueltig)

  R_PN14_EOL_Disp_Rq
    Ruhestrommessung per CAN Signal

  R_PN14_SupBat_Stat
    Bordnetz 14V Status Verbraucherbatterie (degraded)

  R_RevGr_Engg
    Rueckwaertsgang eingelegt

  R_TPM_Actv_Rq_V2
    Anforderung Reifendruckkontrolle aktivieren

  R_VehSpd_Disp
    Angezeigte Geschwindigkeit (ohne Zeigerdaempfung)

  R_WhlPlsCnt_TPM_Pr2
    Radimpuls-Ringzaehler fuer TPM (degraded)


 Data Element Prototypes:
 ========================
  Awake_Diag_Actv of Port Interface IF_Awake_Diag_Actv
    Wachhalten fuer Diagnose aktiv

  Awake_Ignition_On of Port Interface IF_Awake_Ignition_On
    Wachhalten fuer Zuendung eingeschaltet

  Awake_NwSt of Port Interface IF_Awake_NwSt
    Wachhalten fuer Netzwerkstartphase

  Awake_Warn_Actv of Port Interface IF_Awake_Warn_Actv
    Wachhalten wegen Warnung aktiv

  Meas_XX of Port Interface IG_Meas_XX
    Messdaten

  RefPress of Port Interface IG_RefPress
    Referenzdruck

  TPM_Lmp_On_Rq_Pr2 of Port Interface IG_TPM_Lmp_On_Rq_Pr2_2rnjlwsei0w52qmw3bw9laydt
    Anforderung Reifendruckkontrolle Lampe einschalten (degraded)

  TPM_Lmp_On_Rq_old of Port Interface IG_TPM_Lmp_On_Rq_old
    Anforderung Reifendruckkontrolle Lampen einschalten

  Tire_Stat_V2 of Port Interface IG_Tire_Stat_V2
    Reifenstatus

  Tire_Temp_V2 of Port Interface IG_Tire_Temp_V2
    Reifentemperatur

  WakeupRsn_TPM of Port Interface IF_WakeupRsn_TPM
    Weckgrund

  AirPress_Outsd of Port Interface IF_AirPress_Outsd
    Aussenluftdruck

  AirTemp_Outsd_Disp of Port Interface IF_AirTemp_Outsd_Disp
    Angezeigte Aussenlufttemperatur

  DateTm_AR2 of Port Interface IG_DateTm_AR2_enxma1ckviqh65j7cvct42pzp
    Datum und Uhrzeit (degraded)

  Eng_Rs_EngCtrl_Pr2 of Port Interface IG_Eng_Rs_EngCtrl_Pr2_4n60ch9vybmdsjmau9b34jbxs
    Motoransprechverhalten Engine Control (degraded)

  Ign_Stat_Pr2 of Port Interface IG_Ign_Stat_Pr2_cth0s7zr563ygac7uhcvj9ji9
    Zuendungsstatus (degraded)

  Odo of Port Interface IF_Odo
    Kilometerstand (fuer alle, FFFFFEh: Signal ungueltig)

  PN14_EOL_Disp_Rq of Port Interface IF_PN14_EOL_Disp_Rq
    Ansteuerung Bandende-Anzeigen

  PN14_SupBat_Stat of Port Interface IG_PN14_SupBat_Stat_11j4rxo0m2xh60rnncesieiwe
    Bordnetz 14V Status Verbraucherbatterie (degraded)

  RevGr_Engg of Port Interface IF_RevGr_Engg
    Rueckwaertsgang eingelegt

  TPM_Actv_Rq_V2 of Port Interface IF_TPM_Actv_Rq_V2
    Anforderung Reifendruckkontrolle aktivieren

  VehSpd_Disp of Port Interface IF_VehSpd_Disp
    Angezeigte Geschwindigkeit (ohne Zeigerdaempfung)

  WhlPlsCnt_TPM_Pr2 of Port Interface IG_WhlPlsCnt_TPM_Pr2_1v9lk8wpu9a407u123syn2zjx
    Radimpuls-Ringzaehler fuer TPM (degraded)


 Operation Prototypes:
 =====================
  OP_GetZomAbsCompFL of Port Interface PI_GetZomData
    Get compensated ABS Sticks front left  0...95

  GetOperatingHours of Port Interface OHDS_GetOperatingHours
    GetOperatingHours


 Runnable Entities:
 ==================
  RCtApHufTPMSmgr_RdIgnStat
    Klemme

  RCtApHufTPMSmgr_RdOdo
    read data from Odometer

  RCtApHufTPMSmgr_TimeOutIgnStat
    Klemme

  RCtApHufTPMSmgr_WrBusMsg
    write tire temperatur 2 CAN

 *********************************************************************************************************************/

#include "Rte_CtApHufTPMSmgr.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "HMI_handlerX.h" /*CRS_1211_130_156*/
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
//#include "uswarn_Ifx.h"
#include "HMI_handlerX.h"
#include "tel_time_filterX.h"
#include "tel_statisticX.h"
#include "filling_detectionX.h"
#include "Dem_IntEvtId.h"
#include "ComStack_Types.h" //NetworkHandleType
#include "CanSM_Cfg.h" //CanSM_BorCounterType
#include "SensorLoBat.h"
#include "Appl_Dcm.h"
#include "SensorMeasError.h"
#include "EcuM_Generated_Types.h"

#if E2E_ENABLE
#include "HufE2EWrapper.h"
#endif
/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/

#define Off (0U)
#define On (1U)

#define cV_MIN_PAL             (uint8) 20 // Minimum vehicle speed for Wheel transmission

//#define SWTest4AS   // TEST DEFINE FOR CAL TEST a.s.o.
uint8 ucLedState1=0;
extern void TP0(uint8 ucSet); /*CtCdHufTPMSrfd.h*/
/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/
boolean LearningWheelPosActiveSM( void );
static void UpdateCanMState(void);
//void GetVehicleDrivingState(uint8*  ucDrivingStateTemp);
static void GetZOMInfos2BeLogged(void);
static uint8 ucPassPalFrameFilter(uint32 ulID, uint8 ucFrameCounter );
boolean GETbCalPminInvalidCAL( void );
boolean GETbCalReqCAL( void );
boolean GETbCalNotAck4PlausiCheckMFA( void );
void CheckDTCInactiveERR(void);
void InitIDOM(void);


void PUTucPrefFront(uint8 x); /*CRS_1211_130_251*/
uint8 GETucPrefFront(void);		/*CRS_1211_130_251*/
void PUTucPrefRear(uint8 x);	/*CRS_1211_130_251*/
uint8 GETucPrefRear(void);		/*CRS_1211_130_251*/


void PUTucPosComparePressure(uint8 x, uint8 i);
uint8 GETucPosComparePressure(uint8 i);
//CRS_1211_130_249 void PUTucPosComparePressureNVM(void);
void PUTscIdCalTemperatur(sint8 x, uint8 i);
sint8 GETscIdCalTemperatur(uint8 i);

//void PUTscPosCalTemperatur(sint8 x, uint8 i);
//sint8 GETscPosCalTemperatur(uint8 i);
//CRS_1211_130_249 void PUTscIdCalTemperaturNVM(void);
//CRS_1211_130_249 void PUTscPosCalTemperaturNVM(void);

void PUTulLastCalMileage(uint32 x);
uint32 GETulLastCalMileage(void);

//void PUTscAverageFillTemperatur(sint8 x);
//CRS_1211_130_249 void PUTscAverageFillTemperaturNVM(sint8 x);
//sint8 GETscAverageFillTemperatur(void);


void PUTulKmStand4AutoCAL(uint32 i);
uint32 GETulKmStand4AutoCAL(void);

//boolean bGetBitCalNotAckStateOfRam( uint8 ucBitMask );
//void PUTucCalNotAckState2Ram(uint8 x);
//uint8 GETucCalNotAckStateOfRam(void);
void SetBitCalNotAckState2Ram( uint8 ucBitMask );
void SetBitCalRequestState2Ram( uint8 ucBitMask );
//CRS_1211_130_249 void PUTucCalNotAckState2Nvm(void); /*CRS_1211_130_240*/


void PUTucCalRequestState2Ram(uint8 x);
void ClearBitCalRequestState( uint8 ucBitMask );
uint8 GETucCalRequestStateOfRam(void);
uint8 bGETucCalRequestState( uint8 ucBitMask );
//CRS_1211_130_249 uint8 ucGETCalRequestStates( uint8 ucBitMask );
//CRS_1211_130_249 void PUTucCalRequestState2Nvm(void);

uint8 ucCheckLOW_PRESS_ReState(void);
uint8 ucCheckAllRePcalMinDPmanualMFD(void);


void ClearAllReCnt4FD(void);
/*CRS_1211_130_335*/
uint8 GETucRErecCounter4FDVL( void );
uint8 GETucRErecCounter4FDVR( void );
uint8 GETucRErecCounter4FDHL( void );
uint8 GETucRErecCounter4FDHR( void );

void PUTucRErecCounter4FDVL( uint8 );
void PUTucRErecCounter4FDVR( uint8 );
void PUTucRErecCounter4FDHL( uint8 );
void PUTucRErecCounter4FDHR( uint8 );

void INCucRErecCounter4FDVL( void );
void INCucRErecCounter4FDVR( void );
void INCucRErecCounter4FDHL( void );
void INCucRErecCounter4FDHR( void );
/*CRS_1211_130_335*/
void PUTucTimer4MsgDispRq(uint8 x);
uint8 GETucTimer4MsgDispRq(void);
void DECucTimer4MsgDispRq(void);

void PUTushFDtimeout(uint16);
uint16 GETushFDtimeout(void);
void DECushFDtimeout(void);

void PUTushSupervisoryTimerFD(uint16);
uint16 GETushSupervisoryTimerFD(void);
void DECushSupervisoryTimerFD(void);

void PUTucOnceCheckMissingRE4FD(uint8);
uint8 GETucOnceCheckMissingRE4FD(void);

void ReplayLastREvalue2Walgo(void);
void CountCoastModeClampCycle(void);

void PUTucFDtimerStop(uint8);
uint16 GETucFDtimerStop(void);

/* uint16 ushGetBetriebszustandBZ( uint16 ushBitMask ) */
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/
 extern debugTelStruct tDebugTelStruct;
 extern debugTelStructPos tdebugTelStructPosFL;
 extern debugTelStructPos tdebugTelStructPosFR;
 extern debugTelStructPos tdebugTelStructPosRL;
 extern debugTelStructPos tdebugTelStructPosRR;
 extern void SetClamp15State(uint8);
 extern void Nm_DisableCommunication(uint8);
 extern void Nm_EnableCommunication(uint8);
 extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType( P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SessionCtrlType);
 extern uint8 ui8GetComptoirRepare(void);
 extern uint8 GETucMeasurementStateOfRam(void);

 extern void PUTucCoastModeContCount2Ram(uint8);
 extern uint8 GETucCoastModeContCountOfRam(void);
 extern void PUTucCoastModeContCount2Nvm(void);
 //extern void DcmFillingDetectionMFD(void);
 //extern void ReplayLastREvalue2Walgo(void);

 extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(Dem_EventIdType       EventId, Dem_EventStatusType   EventStatus);
 extern void Appl_CanSM_BusOffBegin( NetworkHandleType CanSm_NetworkHandle, CanSM_BorCounterType CanSM_BufOffNotificationCounter);
 extern void Appl_CanSM_BusOffEnd( NetworkHandleType CanSm_NetworkHandle);
 extern void TPMS_NVM_ActivateWriteAll(void);

 extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_ReleasePOST_RUN(EcuM_UserType User_t);
 extern FUNC(Std_ReturnType, ECUM_API_CODE) EcuM_GetState(P2VAR(EcuM_StateType, AUTOMATIC, ECUM_APPL_DATA) state);

/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/
 DT_tEnvData tEnvDataToSend;
 uint8 bRvsGearUsed, ucRvsGearCnt;
 uint8 ucRecEvent=0;
 uint8 ucReCnt4Cal;
 uint8 ucReCnt4Test=0;
 uint8 ucRErecCounter4FDVL; /*CRS_1211_130_058 precondition 4 cal: 3 or more REdata received*/
 uint8 ucRErecCounter4FDVR; /*CRS_1211_130_058 precondition 4 cal: 3 or more REdata received*/
 uint8 ucRErecCounter4FDHL; /*CRS_1211_130_058 precondition 4 cal: 3 or more REdata received*/
 uint8 ucRErecCounter4FDHR; /*CRS_1211_130_058 precondition 4 cal: 3 or more REdata received*/
 uint8 ucTmpPiso4Cal;
 //uint8 ucCnt4DP_FILL_DFL;
 //uint8 ucCnt4DP_FILL_IFL;

 uint8 ucFillingDetectedState;

 uint32 ulKmStand4AutoCal; /*current mileage value 4 start first Acalibration and mileage value 4 last Mcalibration*/ 


/* global variables */
 DT_auRfStruct tReTelData;
 uint32 ulTelID, ulTelTimeStamp;
 uint8 ucTelType, ucTelPal, ucTelP, ucTelT, ucTelAvgRSSI, ucNoiseLevel;
 uint8 ucTimer4MsgDispRq; /*Kein echter 5sec Timer, wird hier vom CAN Sekundentakt abgeleitet!!*/
 uint16 ushFDtimeout; /* 9min Filling Detection timeout timer!*/
 uint16 ushSupervisoryTimerFD; /*ushSupervisoryTimerFD 4 output 2 CAN Mesurement Interface*/
 uint8 ucOnceCheckMissingRE4FD; // check once RE Missing in MFD + AFD
 uint8 ucLTSmode;
 uint8 ucFDtimerStop;
 
 uint8 ucEspDelayTime = 0;

 boolean bOnce = FALSE;

  void SetCodNvMBlockNewDataFlag(boolean);
  static boolean bWrCodNVMBlock = FALSE;
  static void AlignCodBlockRaM2NvM(void);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * Used AUTOSAR Data Types
 *
 **********************************************************************************************************************
 *
 * Primitive Types:
 * ================
 * Boolean: Boolean (standard type)
 * DC_BOOL: Boolean
 * DC_U16: Integer in interval [0...65535]
 * DC_U32: Integer in interval [0...4294967295]
 * DC_U8: Integer in interval [0...255]
 * DT_ucKweight: Integer in interval [0...255]
 * DT_ushWAState: Integer in interval [0...65535]
 * DT_ushWarnOut: Integer in interval [0...65535]
 * Rsrv02: Integer in interval [0...3]
 * Rsrv04: Integer in interval [0...15]
 * Rsrv08: Integer in interval [0...255]
 * SInt8: Integer in interval [-128...127] (standard type)
 * UInt16: Integer in interval [0...65535] (standard type)
 * UInt32: Integer in interval [0...4294967295] (standard type)
 * UInt8: Integer in interval [0...255] (standard type)
 * c04_0_15_1_SNA_na: Integer in interval [0...15]
 *   Unit: [NoUnit], Factor: 1, Offset: 0
 * c08_CRC_woSNA: Integer in interval [0...255]
 * c08_UInt_SNA_na: Integer in interval [0...255]
 *
 * Enumeration Types:
 * ==================
 * ComM_ModeType: Enumeration of integer in interval [0...2] with enumerators
 *   COMM_NO_COMMUNICATION (0U)
 *   COMM_SILENT_COMMUNICATION (1U)
 *   COMM_FULL_COMMUNICATION (2U)
 * NvM_RequestResultType: Enumeration of integer in interval [0...5] with enumerators
 *   NVM_REQ_OK (0U)
 *   NVM_REQ_NOT_OK (1U)
 *   NVM_REQ_PENDING (2U)
 *   NVM_REQ_INTEGRITY_FAILED (3U)
 *   NVM_REQ_BLOCK_SKIPPED (4U)
 *   NVM_REQ_NV_INVALIDATED (5U)
 * c02_BatCutSw_Stat: Enumeration of integer in interval [0...3] with enumerators
 *   I_C02_BATCUTSW_STAT_CLS (0U)
 *   I_C02_BATCUTSW_STAT_PREOPN (1U)
 *   I_C02_BATCUTSW_STAT_OPN (2U)
 *   I_C02_BATCUTSW_STAT_SNA (3U)
 * c02_Disengg_Engg: Enumeration of integer in interval [0...3] with enumerators
 *   I_C02_DISENGG_ENGG_DISENGG (0U)
 *   I_C02_DISENGG_ENGG_ENGG (1U)
 *   I_C02_DISENGG_ENGG_NDEF2 (2U)
 *   I_C02_DISENGG_ENGG_SNA (3U)
 * c02_TPM_Actv_Rq_V2: Enumeration of integer in interval [0...3] with enumerators
 *   I_C02_TPM_ACTV_RQ_V2_IDLE (0U)
 *   I_C02_TPM_ACTV_RQ_V2_ACTIVATE (1U)
 *   I_C02_TPM_ACTV_RQ_V2_SNA (3U)
 * c02_Tire_Stat: Enumeration of integer in interval [0...3] with enumerators
 *   I_C02_TIRE_STAT_NORMAL (0U)
 *   I_C02_TIRE_STAT_SOFT_WARN (1U)
 *   I_C02_TIRE_STAT_LOW_PRESS (2U)
 *   I_C02_TIRE_STAT_DEFLATION (3U)
 * c02_Tire_Temp: Enumeration of integer in interval [0...3] with enumerators
 *   I_C02_TIRE_TEMP_NORMAL (0U)
 *   I_C02_TIRE_TEMP_WARM (1U)
 *   I_C02_TIRE_TEMP_HOT (2U)
 *   I_C02_TIRE_TEMP_SNA (3U)
 * c03_DateTm_Stat: Enumeration of integer in interval [0...7] with enumerators
 *   I_C03_DATETM_STAT_INVALID (0U)
 *   I_C03_DATETM_STAT_INIT (1U)
 *   I_C03_DATETM_STAT_PLAUSIBLE (2U)
 *   I_C03_DATETM_STAT_NEW (3U)
 *   I_C03_DATETM_STAT_DIAG (4U)
 *   I_C03_DATETM_STAT_INCOMPLETE (5U)
 *   I_C03_DATETM_STAT_SNA (7U)
 * c03_EOL_Disp_Rq: Enumeration of integer in interval [0...7] with enumerators
 *   I_C03_EOL_DISP_RQ_IDLE (0U)
 *   I_C03_EOL_DISP_RQ_IOD_MEAS (1U)
 *   I_C03_EOL_DISP_RQ_IOD_ERR (2U)
 *   I_C03_EOL_DISP_RQ_CHRG_BAT (3U)
 *   I_C03_EOL_DISP_RQ_BAT_NCHRG (4U)
 *   I_C03_EOL_DISP_RQ_SNA (7U)
 * c03_EngRun_Stat: Enumeration of integer in interval [0...7] with enumerators
 *   I_C03_ENGRUN_STAT_STOP (0U)
 *   I_C03_ENGRUN_STAT_START (1U)
 *   I_C03_ENGRUN_STAT_IDLE_UNSTBL (2U)
 *   I_C03_ENGRUN_STAT_IDLE_STBL (3U)
 *   I_C03_ENGRUN_STAT_UNLIMITED (4U)
 *   I_C03_ENGRUN_STAT_LIMITED (5U)
 *   I_C03_ENGRUN_STAT_NDEF6 (6U)
 *   I_C03_ENGRUN_STAT_SNA (7U)
 * c03_ISw_Stat: Enumeration of integer in interval [0...7] with enumerators
 *   I_C03_ISW_STAT_IGN_LOCK (0U)
 *   I_C03_ISW_STAT_IGN_OFF (1U)
 *   I_C03_ISW_STAT_IGN_ACC (2U)
 *   I_C03_ISW_STAT_IGN_ON (4U)
 *   I_C03_ISW_STAT_IGN_START (5U)
 *   I_C03_ISW_STAT_SNA (7U)
 * c03_TPM_Stat: Enumeration of integer in interval [0...7] with enumerators
 *   I_C03_TPM_STAT_ACTIVE (0U)
 *   I_C03_TPM_STAT_WAIT (1U)
 *   I_C03_TPM_STAT_ERROR (2U)
 *   I_C03_TPM_STAT_NO_SENSORS (3U)
 *   I_C03_TPM_STAT_SNA (7U)
 * c03_TPM_WarnDisp_Rq: Enumeration of integer in interval [0...7] with enumerators
 *   I_C03_TPM_WARNDISP_RQ_NO_WARN (0U)
 *   I_C03_TPM_WARNDISP_RQ_SOFT (1U)
 *   I_C03_TPM_WARNDISP_RQ_LOW_P (2U)
 *   I_C03_TPM_WARNDISP_RQ_FAST (3U)
 *   I_C03_TPM_WARNDISP_RQ_SNA (7U)
 * c03_Tire_Temp_WarnDisp: Enumeration of integer in interval [0...7] with enumerators
 *   I_C03_TIRE_TEMP_WARNDISP_NO_MESS (0U)
 *   I_C03_TIRE_TEMP_WARNDISP_OVERHEAT (1U)
 *   I_C03_TIRE_TEMP_WARNDISP_REDUCE_SPEED (2U)
 *   I_C03_TIRE_TEMP_WARNDISP_SNA (7U)
 * c04_TPM_MsgDisp_Rq: Enumeration of integer in interval [0...15] with enumerators
 *   I_C04_TPM_MSGDISP_RQ_NO_MESS (0U)
 *   I_C04_TPM_MSGDISP_RQ_UNPLAUSIBLE (1U)
 *   I_C04_TPM_MSGDISP_RQ_NO_SENSORS (2U)
 *   I_C04_TPM_MSGDISP_RQ_ERROR (3U)
 *   I_C04_TPM_MSGDISP_RQ_TNA (4U)
 *   I_C04_TPM_MSGDISP_RQ_WE_MISS (5U)
 *   I_C04_TPM_MSGDISP_RQ_RESTART (6U)
 *   I_C04_TPM_MSGDISP_RQ_SNA (15U)
 * c08_Days_1_31_1: Enumeration of integer in interval [1...255] with enumerators
 *   I_C08_DAYS_1_31_1_SNA (255U)
 *   Unit: [Days], Factor: 1, Offset: 0
 * c08_Impulses_0_254_1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_IMPULSES_0_254_1_SNA (255U)
 *   Unit: [Impulses], Factor: 1, Offset: 0
 * c08_Months_1_12_1: Enumeration of integer in interval [1...255] with enumerators
 *   I_C08_MONTHS_1_12_1_SNA (255U)
 *   Unit: [Months], Factor: 1, Offset: 0
 * c08_V_0_25k4_0k1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_V_0_25K4_0K1_SNA (255U)
 *   Unit: [V], Factor: 0.1, Offset: 0
 * c08_WakeupRsn_TPM: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_WAKEUPRSN_TPM_NETWORK (0U)
 *   I_C08_WAKEUPRSN_TPM_SNA (255U)
 * c08_Years_0_99_1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_YEARS_0_99_1_SNA (255U)
 *   Unit: [Years], Factor: 1, Offset: 0
 * c08_degC_m40_85_0k5: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_DEGC_M40_85_0K5_SNA (255U)
 *   Unit: [deg. C], Factor: 0.5, Offset: -40
 * c08_degC_m50_204_1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_DEGC_M50_204_1_SNA (255U)
 *   Unit: [deg. C], Factor: 1, Offset: -50
 * c08_hPa_0_1980_7k8: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_HPA_0_1980_7K8_SNA (255U)
 *   Unit: [hPa], Factor: 7.79527559055118, Offset: 0
 * c08_h_0_23_1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_H_0_23_1_SNA (255U)
 *   Unit: [h], Factor: 1, Offset: 0
 * c08_kPa_0_632d5_2d5: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_KPA_0_632D5_2D5_NO_IND (254U)
 *   I_C08_KPA_0_632D5_2D5_SNA (255U)
 *   Unit: [kPa], Factor: 2.5, Offset: 0
 * c08_min_0_59_1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_MIN_0_59_1_SNA (255U)
 *   Unit: [min], Factor: 1, Offset: 0
 * c08_ms_0_254_1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_MS_0_254_1_SNA (255U)
 *   Unit: [ms], Factor: 1, Offset: 0
 * c08_s_0_59_1: Enumeration of integer in interval [0...255] with enumerators
 *   I_C08_S_0_59_1_SNA (255U)
 *   Unit: [s], Factor: 1, Offset: 0
 * c12_km_p_h_0_409k4_0k1: Enumeration of integer in interval [0...4095] with enumerators
 *   I_C12_KM_P_H_0_409K4_0K1_SNA (4095U)
 *   Unit: [km/h], Factor: 0.1, Offset: 0
 * c24_km_0_999999k9_0k1: Enumeration of integer in interval [0...16777215] with enumerators
 *   I_C24_KM_0_999999K9_0K1_SNA (16777215U)
 *   Unit: [km], Factor: 0.1, Offset: 0
 *
 * Array Types:
 * ============
 * ARR_08_UInt_noSNA_8: Array with 8 element(s) of type c08_UInt_SNA_na
 * DT_auRfStruct: Array with 34 element(s) of type UInt8
 * DT_aucPalAbsDelayTimeParam: Array with 2 element(s) of type UInt8
 * DT_aucPosComparePressure: Array with 4 element(s) of type UInt8
 * DT_tNvMReservedBytes: Array with 20 element(s) of type UInt8
 * NvM_DestPtr: Array with 65535 element(s) of type UInt8
 *
 * Record Types:
 * =============
 * DT_tCalNvMBlock: Record with elements
 *   aucPosComparePressure of type DT_aucPosComparePressure
 *   ulLastCalMileage of type UInt32
 *   ucPrefFront of type UInt8
 *   ucPrefRear of type UInt8
 *   scTref of type SInt8
 *   ucCalNotAckState of type UInt8
 *   ucCalRequestState of type UInt8
 *   tCalReserved of type DT_tNvMReservedBytes
 * DT_tCodNvMBlock: Record with elements
 *   tLogicalDataPalCod of type DT_tLogicalDataPalCod
 *   tParaTempWarnCod of type DT_tParaTempWarnCod
 *   ucPcalMinVaRelativCod of type UInt8
 *   ucPcalMinHaRelativCod of type UInt8
 *   aucPalAbsDelayTimeParam of type DT_aucPalAbsDelayTimeParam
 *   ucMeasurementOnOffCod of type UInt8
 *   ucCoastModeCtrlCount of type UInt8
 *   ucKweight of type DT_ucKweight
 *   tCodReserved of type DT_tNvMReservedBytes
 * DT_tData2Alloc: Record with elements
 *   ushTimeStamp of type UInt16
 *   ulID of type UInt32
 *   ucTelType of type UInt8
 *   ucPalData of type UInt8
 *   ucFrameCounter of type UInt8
 *   ushAbsStickFL of type UInt16
 *   ushAbsStickFR of type UInt16
 *   ushAbsStickRL of type UInt16
 *   ushAbsStickRR of type UInt16
 * DT_tData2Warn: Record with elements
 *   ulID of type UInt32
 *   ucP of type UInt8
 *   ucT of type UInt8
 *   ucZomPos of type UInt8
 *   ucTxTrigger of type UInt8
 * DT_tEnvData: Record with elements
 *   ucKlState of type UInt8
 *   ucTempOut of type UInt8
 *   ushVehSpeed of type UInt16
 *   ucPressOut of type UInt8
 *   ucEngStat of type UInt8
 *   ucIgnOnStartProc of type UInt8
 * DT_tLogicalDataPalCod: Record with elements
 *   ucMinWarnThreshold of type UInt8
 *   ucAutoFillDetectionOnOff of type UInt8
 *   ucT_Soft of type UInt8
 *   ucPercent_Soft of type UInt8
 *   ucT_Hard of type UInt8
 *   ucPercent_Hard of type UInt8
 *   ucTempWarnOnOff of type UInt8
 * DT_tParaTempWarnCod: Record with elements
 *   ucV1 of type UInt8
 *   ucV2 of type UInt8
 *   ucV3 of type UInt8
 *   scT0 of type SInt8
 *   scT1 of type SInt8
 *   scT2 of type SInt8
 *   ushHC_MAX of type UInt16
 * REC_DateTm_AR2_f0ifkphxunpp94u3ro8qn5tdm: Record with elements
 *   DateTmDay of type c08_Days_1_31_1
 *   DateTmHour of type c08_h_0_23_1
 *   DateTmMinute of type c08_min_0_59_1
 *   DateTmMonth of type c08_Months_1_12_1
 *   DateTmSecond of type c08_s_0_59_1
 *   DateTmStat of type c03_DateTm_Stat
 *   DateTmYear of type c08_Years_0_99_1
 * REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy: Record with elements
 *   EngRun_Stat of type c03_EngRun_Stat
 * REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno: Record with elements
 *   ISw_Stat of type c03_ISw_Stat
 *   Ign_On_StartProc_Inact of type DC_BOOL
 * REC_PN14_SupBat_Stat_2is6fi0meeac78nkn35zc5ui3: Record with elements
 *   PN14_SupBatCutSw_Stat of type c02_BatCutSw_Stat
 *   PN14_SupBat_Volt of type c08_V_0_25k4_0k1
 * REC_RefPress: Record with elements
 *   RefPress_Front of type c08_kPa_0_632d5_2d5
 *   RefPress_Rear of type c08_kPa_0_632d5_2d5
 * REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt: Record with elements
 *   CRC_TPM_Lmp_On_Rq_Pr2 of type c08_CRC_woSNA
 *   Rsrv1_TPM_Lmp_On_Rq_Pr2 of type Rsrv02
 *   SQC_TPM_Lmp_On_Rq_Pr2 of type c04_0_15_1_SNA_na
 *   TPM_IndLmp_On_Rq of type DC_BOOL
 *   TPM_MalfLmp_On_Rq of type DC_BOOL
 * REC_TPM_Lmp_On_Rq_old: Record with elements
 *   TPM_IndLmp_On_Rq_old of type DC_BOOL
 *   TPM_MalfLmp_On_Rq_old of type DC_BOOL
 * REC_Tire_Stat_V2: Record with elements
 *   Press_Disp_Avl of type DC_BOOL
 *   TirePress_FL of type c08_kPa_0_632d5_2d5
 *   TirePress_FR of type c08_kPa_0_632d5_2d5
 *   TirePress_RL of type c08_kPa_0_632d5_2d5
 *   TirePress_RR of type c08_kPa_0_632d5_2d5
 *   TireStat_FL of type c02_Tire_Stat
 *   TireStat_FR of type c02_Tire_Stat
 *   TireStat_RL of type c02_Tire_Stat
 *   TireStat_RR of type c02_Tire_Stat
 *   TPM_MsgDisp_Rq of type c04_TPM_MsgDisp_Rq
 *   TPM_Stat of type c03_TPM_Stat
 *   TPM_WarnDisp_Rq of type c03_TPM_WarnDisp_Rq
 * REC_Tire_Temp_V2: Record with elements
 *   Tire_Temp_Stat_FL of type c02_Tire_Temp
 *   Tire_Temp_Stat_FR of type c02_Tire_Temp
 *   Tire_Temp_Stat_RL of type c02_Tire_Temp
 *   Tire_Temp_Stat_RR of type c02_Tire_Temp
 *   Tire_Temp_WarnDisp_Rq of type c03_Tire_Temp_WarnDisp
 *   TireTemp_FL of type c08_degC_m50_204_1
 *   TireTemp_FR of type c08_degC_m50_204_1
 *   TireTemp_RL of type c08_degC_m50_204_1
 *   TireTemp_RR of type c08_degC_m50_204_1
 * REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx: Record with elements
 *   CRC_WhlPlsCnt_TPM_Pr2 of type c08_CRC_woSNA
 *   Rsrv2_WhlPlsCnt_TPM_Pr2 of type Rsrv08
 *   SQC_WhlPlsCnt_TPM_Pr2 of type c04_0_15_1_SNA_na
 *   WhlPlsCnt_FL of type c08_Impulses_0_254_1
 *   WhlPlsCnt_FR of type c08_Impulses_0_254_1
 *   WhlPlsCnt_RL of type c08_Impulses_0_254_1
 *   WhlPlsCnt_RR of type c08_Impulses_0_254_1
 *   WhlPlsCnt_TmStmp of type c08_ms_0_254_1
 *   Rsrv1_WhlPlsCnt_TPM_Pr2 of type Rsrv04
 *
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *
 * APIs which are accessible from all runnable entities of the SW-C
 *
 **********************************************************************************************************************
 * Per-Instance Memory:
 * ====================
 *   DT_tCalNvMBlock *Rte_Pim_Pim_tCalNvMBlock(void)
 *   DT_tCodNvMBlock *Rte_Pim_Pim_tCodNvMBlock(void)
 *
 * Calibration Parameters:
 * =======================
 *   SW-C local Calibration Parameters:
 *   ----------------------------------
 *   DT_tCalNvMBlock *Rte_CData_Cal_tCalNvMBlock_DefaultValue(void)
 *   DT_tCodNvMBlock *Rte_CData_Cal_tCodNvMBlock_DefaultValue(void)
 *
 *********************************************************************************************************************/


#define RTE_START_SEC_CTAPHUFTPMSMGR_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_ControlEcuStandbyTimer
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 1s
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ControlEcuStandbyTimer(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_ControlEcuStandbyTimer
 *********************************************************************************************************************/

 UpdateStanbyTimer(tEnvDataToSend.ucKlState, tEnvDataToSend.ushVehSpeed, cV_MIN);
 UpdateParkingTimer(tEnvDataToSend.ushVehSpeed);
 UpdateTelStatInfo(tEnvDataToSend.ushVehSpeed, cV_MIN); //update wheel status. 
 UpdateFzzCurrentLearnMode(); // update current learn mode
 UpdateFzzDTcEnableCond(); // upsate

	FillingDetectionAFDII(); /*CRS_1211_130_172*/
	AlignCodBlockRaM2NvM(); //synchr coding data with NvM			
	 
 /*collect debug variable in 1 sec time interval */
 GetDebugVar2beLogged();
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_GenInternalClock
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_GenInternalClock(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_GenInternalClock
 *********************************************************************************************************************/
	
 IncrInternMsTimer(); // update internal timer

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_Init
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed once after the RTE is started
 *
 **********************************************************************************************************************
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(Boolean RamBlockStatus)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_GetErrorStatus(NvM_RequestResultType *ErrorStatus)
 *     Synchronous Service Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(Boolean RamBlockStatus)
 *     Synchronous Service Invocation. Timeout: None
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_WriteBlock(const UInt8 *DstPtr)
#else
 *   Std_ReturnType Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_WriteBlock(const NvM_DestPtr *DstPtr)
#endif
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_NvMService_AC3_SRBS_Defs_E_NOT_OK
 *   Std_ReturnType Rte_Call_UR_ComMUser_HMI_GetCurrentComMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *   Std_ReturnType Rte_Call_UR_ComMUser_HMI_GetRequestedMode(ComM_ModeType *ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_NOT_OK
 *   Std_ReturnType Rte_Call_UR_ComMUser_HMI_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_Init(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_Init
 *********************************************************************************************************************/

	InitBZ();
	InitZK();
	InitABS();

  InitTelStatInfo(); // init tel statistic infos
	InitTxBusMsg(); // init bus msg
  InitFilterTime(); // init telegramm filter
  

	//init Fahrzeugszustand
	//ucDrivingState = cFAHRZEUG_FAEHRT;
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

	ucTelType = 0;
	ulTelTimeStamp = 0;
	ulTelID = 0; 
	ucTelPal = 0;
	ucTelP = 0;
	ucTelT = 0;
	ucTelAvgRSSI = 0;
	ucNoiseLevel = 0;

	PUTucTimer4MsgDispRq(0); /* Timer 4 Kal Request*/
	PUTushFDtimeout(0); /* 9sec timeout 4 calibration*/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdDateTm
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <DateTm_AR2> of PortPrototype <R_DateTm_AR2>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdDateTm(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdDateTm
 *********************************************************************************************************************/
  ClearFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdEngCtrl
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <Eng_Rs_EngCtrl_Pr2> of PortPrototype <R_Eng_Rs_EngCtrl_Pr2>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2(REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEngCtrl(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdEngCtrl
 *********************************************************************************************************************/
  REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy data;
  Rte_Read_R_Eng_Rs_EngCtrl_Pr2_Eng_Rs_EngCtrl_Pr2(&data);
  if( (data.EngRun_Stat == I_C03_ENGRUN_STAT_STOP) || (data.EngRun_Stat == I_C03_ENGRUN_STAT_SNA))
  {
    tEnvDataToSend.ucEngStat = cEngStat_STOPPED;
  }
  else if( (data.EngRun_Stat == I_C03_ENGRUN_STAT_START) || (data.EngRun_Stat == I_C03_ENGRUN_STAT_IDLE_UNSTBL))
  {
    tEnvDataToSend.ucEngStat = cEngStat_STARTING;
  }
  else if( (data.EngRun_Stat == I_C03_ENGRUN_STAT_IDLE_STBL) || (data.EngRun_Stat == I_C03_ENGRUN_STAT_UNLIMITED) || (data.EngRun_Stat == I_C03_ENGRUN_STAT_LIMITED))
  {
    tEnvDataToSend.ucEngStat = cEngStat_RUNNING;
  }
  SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
  ClearFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdEnvPressure
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <AirPress_Outsd> of PortPrototype <R_AirPress_Outsd>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_AirPress_Outsd_AirPress_Outsd(c08_hPa_0_1980_7k8 *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEnvPressure(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdEnvPressure
 *********************************************************************************************************************/
  c08_hPa_0_1980_7k8 ucPressOut;
  Rte_Read_R_AirPress_Outsd_AirPress_Outsd(&ucPressOut);
  tEnvDataToSend.ucPressOut = ucPressOut; //ToDo: GL convert to Huf type
  ClearFzzSignalTimeOutState(cFZZ_PRESS_OUT_TIMEOUT);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdEnvTemperature
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <AirTemp_Outsd_Disp> of PortPrototype <R_AirTemp_Outsd_Disp>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp(c08_degC_m40_85_0k5 *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PP_EnvData_DE_tEnvData(const DT_tEnvData *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdEnvTemperature(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdEnvTemperature
 *********************************************************************************************************************/
  c08_degC_m40_85_0k5 tmpAussenTemp;
  Rte_Read_R_AirTemp_Outsd_Disp_AirTemp_Outsd_Disp(&tmpAussenTemp);
  
  ClearFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT); // clear basic info timeout state
  if(tmpAussenTemp < I_C08_DEGC_M40_85_0K5_SNA)
  {
    /* CAN outside temperature: -40 : 0.5 : 87.5 in °C*/
    tEnvDataToSend.ucTempOut = (uint8)((tmpAussenTemp>>1) - 40);
    Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
    SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
    ClearFzzSignalUnplausibleState(cFZZ_AIRTEMP_OUT_IMPLAU); // clear implausible state
  }
  else
  {
    SetFzzSignalImplauState(cFZZ_AIRTEMP_OUT_IMPLAU); // set implausible state
  }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdGrBac
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <RevGr_Engg> of PortPrototype <R_RevGr_Engg>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_RevGr_Engg_RevGr_Engg(c02_Disengg_Engg *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdGrBac(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdGrBac
 *********************************************************************************************************************/
	c02_Disengg_Engg data;
	Rte_Read_R_RevGr_Engg_RevGr_Engg(&data);
	if (data ==I_C02_DISENGG_ENGG_ENGG)
  {
    if( (bRvsGearUsed == 0) && (ucRvsGearCnt < 0xFF))
    {
        ucRvsGearCnt++; // count numbers of reverse driving
    }
		bRvsGearUsed = 1;
	}
	else
  {
		bRvsGearUsed = 0;
  }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdIgnStat
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <Ign_Stat_Pr2> of PortPrototype <R_Ign_Stat_Pr2>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_Ign_Stat_Pr2_Ign_Stat_Pr2(REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PP_EnvData_DE_tEnvData(const DT_tEnvData *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_ComMUser_HMI_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdIgnStat(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdIgnStat
 *********************************************************************************************************************/
  REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno tmpKLstate;
  //ComM_ModeType ComMode, RqComMode;
  //uint8 temp;

  Rte_Read_R_Ign_Stat_Pr2_Ign_Stat_Pr2(&tmpKLstate);
  /* use this function to transform from CAN to warnmodule */
  if( (tmpKLstate.ISw_Stat == I_C03_ISW_STAT_IGN_ON) || (tmpKLstate.ISw_Stat == I_C03_ISW_STAT_IGN_START) )
  //if(tmpKLstate.Ign_On_StartProc_Inact == TRUE)
  {
    tEnvDataToSend.ucKlState = On;

  }
  else
  {
    if(tEnvDataToSend.ucKlState != Off)
    { 
      CountCoastModeClampCycle();
    }

    tEnvDataToSend.ucKlState = Off;
  }

  tEnvDataToSend.ucIgnOnStartProc = tmpKLstate.Ign_On_StartProc_Inact;
  /* use this function to transform from CAN to warnmodule */ 
  Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);

  /* send environment data to VEhicle state manager */
  SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
  ClearFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT); //clear internal timeout state 
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdOdo
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <Odo> of PortPrototype <R_Odo>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_Odo_Odo(c24_km_0_999999k9_0k1 *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdOdo(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdOdo
 *********************************************************************************************************************/
c24_km_0_999999k9_0k1 temp;

Rte_Read_CtApHufTPMSmgr_R_Odo_Odo(&temp);

PUTulKmStand4AutoCAL(temp);
ClearFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT); // clear basic info timeout state

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdPN14EOLDispRq
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <PN14_EOL_Disp_Rq> of PortPrototype <R_PN14_EOL_Disp_Rq>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq(c03_EOL_Disp_Rq *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdPN14EOLDispRq(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdPN14EOLDispRq
 *********************************************************************************************************************/

  c03_EOL_Disp_Rq value;

  if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE )
  {
    Rte_Read_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq(&value);
    
    if( (value == I_C03_EOL_DISP_RQ_IOD_MEAS) || (value == I_C03_EOL_DISP_RQ_IOD_ERR) )
    {
      /* quiescent current on demand - ECU asleep immediately after detected ignition off and the can bus falls asleep */
      SkipStanbyTimer();
    }
  }

   bOnce = FALSE; /* ready for timeout */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdSupPN14BatStat
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <PN14_SupBat_Stat> of PortPrototype <R_PN14_SupBat_Stat>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdSupPN14BatStat(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdSupPN14BatStat
 *********************************************************************************************************************/
  ClearFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdTpmActvRq
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <TPM_Actv_Rq_V2> of PortPrototype <R_TPM_Actv_Rq_V2>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2(c02_TPM_Actv_Rq_V2 *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApHufTPMSmgr_RdTpmActvRq_IRV_TpmActvRq_TpmMsgDispRq(Boolean data)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdTpmActvRq(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdTpmActvRq
 *********************************************************************************************************************/

	c02_TPM_Actv_Rq_V2 temp;
	
	Rte_Read_R_TPM_Actv_Rq_V2_TPM_Actv_Rq_V2(&temp);

  ClearFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT); // clear time out state
  if (temp < I_C02_TPM_ACTV_RQ_V2_SNA)
  {
	  if (temp ==I_C02_TPM_ACTV_RQ_V2_ACTIVATE)  // CRS_1211_130_080 && (bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == FALSE )) /* CRS_1211_130_054)*/
	  {
#ifndef FD_CONTROLS_FALLBACK		
      if (!(GETbWrnPMin_FL () || GETbWrnPMin_FR () || GETbWrnPMin_RL () || GETbWrnPMin_RR ())) // OIL #1049 aus Erprobung: Provisorische Zuordnung (Fallback), MFD sortiert Drücke bei bestehender P_min_tire Warnung um. Sperrung der Neusortierung bei P_min_tire
      {
      ClearPWP();
      Check4PWP();
      }
#endif
      FillingDetectionMFD(TRUE); /* CRS_1211_130_312 Ansteuern der RESTART(6) Ausgabe NUR bei TASTENDRUCK*/

	  }
    ClearFzzSignalUnplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU); // clear implausible state
  }
  else
  {
    SetFzzSignalImplauState(cFZZ_IC_A3_TPM_ACTV_IMPLAU); // set implausible state
  }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdVehSpeed
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <VehSpd_Disp> of PortPrototype <R_VehSpd_Disp>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_VehSpd_Disp_VehSpd_Disp(c12_km_p_h_0_409k4_0k1 *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PP_EnvData_DE_tEnvData(const DT_tEnvData *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdVehSpeed(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdVehSpeed
 *********************************************************************************************************************/

	c12_km_p_h_0_409k4_0k1 data;
	
	Rte_Read_R_VehSpd_Disp_VehSpd_Disp(&data);

  ClearFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT); // clear basic info timeout state
	/* use this function to transform from CAN to warnmodule */
	if (data < c12_km_p_h_0_409k4_0k1_UpperLimit)
	{
    ClearFzzSignalUnplausibleState(cFZZ_VEH_SPEED_IMPLAU);
		tEnvDataToSend.ushVehSpeed = (uint16)(data/10); //km/h
		Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);

		/* send environment data to VEhicle state manager */
		SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
	}
  else
  {
    SetFzzSignalImplauState(cFZZ_VEH_SPEED_IMPLAU);
    tEnvDataToSend.ushVehSpeed = 0; //assume 0 km/h
    Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
    /* send environment data to VEhicle state manager */
    SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
    
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_RdWhlPlsCnt
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <WhlPlsCnt_TPM_Pr2> of PortPrototype <R_WhlPlsCnt_TPM_Pr2>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2(REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *   uint32 E2EPW_Read_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2(REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx *data)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_RdWhlPlsCnt(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_RdWhlPlsCnt
 *********************************************************************************************************************/
	 uint32 refTime;
   uint8 ucAbsTime;
   //uint8 ucMSB;
	 REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx tWheelPlsMsg;
	 uint16 ushTESTABStick[4];

	 Rte_Read_R_WhlPlsCnt_TPM_Pr2_WhlPlsCnt_TPM_Pr2(&tWheelPlsMsg); //read whlpls message

#if 0 //E2E_ENABLE Notes: @@GL: CRC check on received messanges not asked by DAIMLER 
	 if (ucHufE2EWrapperCheckWhlPlsCnt((uint8*)&tWheelPlsMsg) == TRUE)
	 {
#endif
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

   /*-------------Compensate ABS timestamp-----------------------------------*/
  ucAbsTime = (uint8)tWheelPlsMsg.WhlPlsCnt_TmStmp;

  GetSystemOperatingTime(&refTime);
  //Rte_Call_R_OHDS_GetOperatingHours_GetOperatingHours(&refTime, &ucMSB, NULL_PTR); // get current operating time
  // compute delta time
  // we assume hier that ucAbsTime cannot be higher than 0x7F;
  if(GetOpTimeMethodCurrent()==OP_TIME_METHOD_OHDS)
  {
    if ( ((uint8)(refTime & 0x0000007F)) > ucAbsTime)
    {
      ucEspDelayTime = ((uint8)(refTime & 0x0000007F)) - ucAbsTime;
    }
    else
    {
      ucEspDelayTime = 0x80 - ucAbsTime + ((uint8)(refTime & 0x0000007F)) ;
    }
  }
  else
  {
    ucEspDelayTime = GetPalAbsConstantDelay();
  }
#if 1 // this is used only when Whlpls message contents reliable time information
  // correct reftime
  if ( refTime < ucEspDelayTime)
  {
    refTime = 0xFFFFFFFF - ucEspDelayTime + refTime + 1;
  }
  else
  {
    refTime -= ucEspDelayTime;
  }
#else
  //GetInternMSTime(&refTime);
   ucEspDelayTime = 0;
#endif

   /*-------------Check ABS signal plausibility-----------------------------------*/
   if ((uint8)tWheelPlsMsg.WhlPlsCnt_FL != I_C08_IMPULSES_0_254_1_SNA)
   {
     ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_FL_IMPLAU);
   }
   else
   {
     SetFzzSignalImplauState(cFZZ_WHLPLS_FL_IMPLAU);
     ReNewABSRef();
   }
   //check signal plausibility
   if ((uint8)tWheelPlsMsg.WhlPlsCnt_FR != I_C08_IMPULSES_0_254_1_SNA)
   {
     ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_FR_IMPLAU);
   }
   else
   {
     SetFzzSignalImplauState(cFZZ_WHLPLS_FR_IMPLAU);
     ReNewABSRef();
   }
      //check signal plausibility
   if ((uint8)tWheelPlsMsg.WhlPlsCnt_RL != I_C08_IMPULSES_0_254_1_SNA)
   {
     ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_RL_IMPLAU); // clear 
   }
   else
   {
     SetFzzSignalImplauState(cFZZ_WHLPLS_RL_IMPLAU);
     ReNewABSRef();
   }
      //check signal plausibility
   if ((uint8)tWheelPlsMsg.WhlPlsCnt_RR != I_C08_IMPULSES_0_254_1_SNA)
   {
     ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_RR_IMPLAU);
   } 
   else
   {
     SetFzzSignalImplauState(cFZZ_WHLPLS_RR_IMPLAU);
     ReNewABSRef();
   }
   //check signal plausibility
   if ((uint8)tWheelPlsMsg.WhlPlsCnt_TmStmp != I_C08_MS_0_254_1_SNA)
   {
     ClearFzzSignalUnplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU);
   }
   else
   {
     SetFzzSignalImplauState(cFZZ_TRACTION_SYSTEM_IMPLAU);
   }

   /*-----------send whls pulse variable to datamanager------------------------------------------ */
  PutABS((uint16)refTime, ushTESTABStick);
  ClearFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT); //clear time out bit

  /*------------------------------------------------------------------------*/
	#if !(USE_VEH_DIR_INFO)
	 /* update car motion state */
	if (bCarAbsStickStandstill()){
	// if(EnvDataToSend.EnvRecordVehicleSpeed==0){
		 if( bGetBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE) ){// && ((refTime-ulLastStandStillTime) < 1000) ) {
			//ucDrivingState = cFAHRZEUG_STEHT;
			ClearBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE);
		 }
	 }
	 else{
		 if (bRvsGearUsed == 0){
      ClearBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);
			if (!bGetBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE)){//(ucDrivingState != cFAHRZEUG_FAEHRT){
				if (bResetAbsRefPoint())
					ReNewABSRef();
				SetBitFahrzeugzustandFZZ(cVEH_ABSSTICKS_MOVE);//ucDrivingState = cFAHRZEUG_FAEHRT;
			}
		 }
		 else{
			 if(!bGetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT)){//(ucDrivingState != cRUECKWAERTSFAHRT){
				if (bResetAbsRefPoint())
					ReNewABSRef();
			SetBitFahrzeugzustandFZZ(cRUECKWAERTSFAHRT);//	ucDrivingState = cRUECKWAERTSFAHRT;		
			 }
		 }
	 }
	#endif
#if 0 // E2E_ENABLE Notes: @@GL: CRC check on received messanges not asked by DAIMLER 
	 }else{
		 //@@ ToDo:GL implement what to do in case in invcorect CRC
	 }
#endif
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_ReceiveTelData
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <DE_auRfStruct> of PortPrototype <PP_RfStructIn>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Read_PP_RfStructIn_DE_auRfStruct(UInt8 *data)
#else
 *   Std_ReturnType Rte_Read_PP_RfStructIn_DE_auRfStruct(DT_auRfStruct *data)
#endif
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Write_PP_RfStructOut_DE_auRfStruct(const UInt8 *data)
#else
 *   Std_ReturnType Rte_Write_PP_RfStructOut_DE_auRfStruct(const DT_auRfStruct *data)
#endif
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_PP_Data2Walloc_OP_SendData2Walloc(const DT_tData2Alloc *tData2Alloc)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_Data2Warn_OP_SendTelData2WarnHdlr(const DT_tData2Warn *tData2Warn)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetWANonVolatileData_OP_GetHistWPOfID(UInt32 ulID, UInt8 *ucZomPos)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_R_OHDS_GetOperatingHours_GetOperatingHours(DC_U32 *value, DC_U8 *valueMsb, DC_U8 *status)
 *     Synchronous Server Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_OHDS_GetOperatingHours_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveTelData(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_ReceiveTelData
 *********************************************************************************************************************/
 uint16 ushLinABStick[4];
 uint16 ushTimeStamp;
 DT_tData2Alloc tReData4Alloc;
 DT_tData2Warn tData2Warn;
 uint8 ucZomPos, ucTxTrigger,ucLTS; /* LTS mode  CRS_1211_130_245*/
 sint8 scTireTemp;
 uint8 ucLastTirePressure, ucStatusField0, ucStatusField1;
 uint16 ushlookBackTime;
 uint8 ucReTel4FD=TRUE; /* CRS_1211_130_235*/
 Rte_Read_PP_RfStructIn_DE_auRfStruct(&tReTelData);

 /* increment reveive event counter */
 ucRecEvent++;

 /*
 0 timestemp
 1 timestemp
 2 timestemp
 3 timestemp
 4 avgRssi
 5 teltype
 6 telID
 7 telID
 8 telID
 9 telID
 10 P
 11 T
 12 Pal
 */
 /* following variables are available in all telegrams types */
 ucTelType = tReTelData[5];
 ulTelTimeStamp = ( (tReTelData[0]<<0) + (tReTelData[1]<<8) + (tReTelData[2]<<16) + (tReTelData[3]<<24) );
 if (PAL_TEL_CST_DELAY_TIME < ulTelTimeStamp)
 {
    ulTelTimeStamp -= PAL_TEL_CST_DELAY_TIME;
 }
 else
 {
    ulTelTimeStamp = 0xFFFFFFFF - PAL_TEL_CST_DELAY_TIME + ulTelTimeStamp + 1;
 }
 ushTimeStamp = (uint16) ulTelTimeStamp;
 ulTelID =  ( (tReTelData[6]<<24) + (tReTelData[7]<<16) + (tReTelData[8]<<8) + (tReTelData[9]<<0) );
 ucTelAvgRSSI = tReTelData[30]; // get avg RSSI
 ucNoiseLevel = tReTelData[4]; // get noise level
 //ucDeltaPStatus4AFD=(tReTelData[14]&0xC0)>>6; // get delta P 4 AFD function

  if ((ucTelType == cTelTypeSELPAL) || (ucTelType == cTelTypeSELPAL1))
  {
    /*following variables are not available for trigerred telegrams */
    ucTelPal = tReTelData[12];
    ucTelP = tReTelData[10];
    ucTelT = tReTelData[11];
    ucStatusField0 = tReTelData[13];
    ucStatusField1 = tReTelData[14];
		ucLTS = (ucStatusField1&0x03);
    ucTxTrigger = (ucStatusField1&0xC0)>>6;
  }
  else if ((ucTelType == cTelTypeAK35def) || (ucTelType == cTelTypeAK35defLMA) || (ucTelType == cTelTypeAK35defLF))
  {
    ucTelPal = 0;
    ucTelP = tReTelData[10];
    ucTelT = tReTelData[11];
    ucStatusField0 = 0;
    ucStatusField1 = 0;
		ucLTS = 0;
    ucTxTrigger = 0;
  }
  else
  {
    ucTelPal = 0;
    ucTelP = 0x00; //not valid
    ucTelT = 0x00; //not valid
    ucStatusField0 = 0;
    ucStatusField1 = 0;
		ucLTS = 0;
    ucTxTrigger = 0;
  }

 if(ucPassTimeFilter(ulTelID, ucTelType, ulTelTimeStamp)) // pass telegramm through time filter
 {   
   Rte_Write_PP_RfStructOut_DE_auRfStruct((const DT_auRfStruct*) &tReTelData); // send data to Diag module
   if ( (ucTelType == 0x00) || (ucTelType == 0x01) || (ucTelType == 0x03) || (ucTelType == 0x20)  || (ucTelType == 0x23) || (ucTelType == 0xC3) || (ucTelType == 0xC1) || (ucTelType == 0xCA) )
   {
     BuildTelStatistics(ulTelID, ucTelP, ucTelT, ulTelTimeStamp, bSensorDefect (ulTelID,ucTelType,ucTelP,ucTelT)); // pass telegramm through statistic module
   }
   if(!bSensorDefect (ulTelID,ucTelType,ucTelP,ucTelT) ) // only send valid telegramm through the application
   {
     /*--------------------------------------------Trigger Walloc module ---------------------------------------------------------------------------*/
     if ((ucTelType == cTelTypeSELPAL) || (ucTelType == cTelTypeSELPAL1) || (ucTelType == cTelTypeAK35def) || (ucTelType == cTelTypeAK35defLMA))
     {	   
       /* only PAL telegramms are  forwarded to Wheel Allocation module */
      if (LearningWheelPosActiveSM() == TRUE) 
      {
	      /* fixe log file used  */
	      ushlookBackTime = (ucTelPal>2) ? (ucTelPal-2)*5 :  10;
	      /* Linearize abs signal according to telegram time stamp */
	      if (ushTimeStamp < ushlookBackTime)
	      {
		      LinABS(0xFFFF- ushlookBackTime + ushTimeStamp);
	      }
	      else
	      {
		      LinABS(ushTimeStamp - ushlookBackTime);
	      }

	      /* Get interpolated ABS sticks*/
	      GetLinABS(ushLinABStick);
  
	      /*
	      * Räder müssen eingelernt werden, solange:
	      * - Radpositionsbestimmung noch nicht abgeschlossen
	      * - Fahrzeug fährt
	      */
        /* Trigger Walloc module, only to build some statistics*/
        tReData4Alloc.ulID =  ulTelID;    // read telegramm ID
        tReData4Alloc.ucPalData = ucTelPal;
        tReData4Alloc.ushTimeStamp = (uint16)ushTimeStamp;
        tReData4Alloc.ucTelType = ucTelType;
        tReData4Alloc.ucFrameCounter = ucStatusField0;
        tReData4Alloc.ushAbsStickFL = ushLinABStick[0];
        tReData4Alloc.ushAbsStickFR = ushLinABStick[1];
        tReData4Alloc.ushAbsStickRL = ushLinABStick[2];
        tReData4Alloc.ushAbsStickRR = ushLinABStick[3];
	      //Rte_Write_PP_Data2Alloc_DE_tData2Alloc(&tReData4Alloc);
        Rte_Call_PP_Data2Walloc_OP_SendData2Walloc(&tReData4Alloc);
      }
     }

    /*--------------------------------------------Trigger WARnhandler module ---------------------------------------------------------------------------*/
    /*  only telegrams of type 0x23 0x03 can be warned, 0x00  are not expected*/
	  if( (ucGetColOfID(&ulTelID)<cMaxLR)  && ( (ucTelType == cTelTypeSELPAL) || (ucTelType == cTelTypeSELPAL1) || (ucTelType == cTelTypeAK35def) || (ucTelType == cTelTypeAK35defLMA))  
      && (bGetSensorStateMissing(ucGetColOfID(&ulTelID))!= TRUE) )
	  {
		  /* Trigger Warnmodul */
		  tData2Warn.ucP = ucGetLastReceivedPress(ulTelID);
		  tData2Warn.ucT = ucGetLastReceivedTemp(ulTelID);
		  tData2Warn.ulID = ulTelID;    // read telegramm ID
		  tData2Warn.ucTxTrigger = ucTxTrigger;

		  tData2Warn.ucZomPos = ucGetColOfID(&ulTelID);
			/*
			* Reifendruck nur bei eigenen Rädern überwachen
			*/
      Rte_Call_PP_Data2Warn_OP_SendTelData2WarnHdlr(&tData2Warn);
			//Rte_Send_PP_Data2Warn_DE_tData2Warn(&tData2Warn);
			//Rte_Write_PP_Data2Warn_DE_tData2Warn(&tData2Warn);
			ucReTel4FD=TRUE; /* CRS_1211_130_235*/
	  }
		else
		{
			ucReTel4FD=FALSE;/* CRS_1211_130_235*/
		}

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/
    /* RFtelegram (scheduled transmission) received from prelearned ID during ignition on  --> stanby timer = 0  see TPMS logic PAL2 v1.2 section 8.2*/
    if ( (ucGetColOfID(&ulTelID)<cAnzRad) && (tEnvDataToSend.ucKlState == TRUE) && ( ucTxTrigger== 3))
    {
	    ResetStanbyTimer();
    }


    if ( (ucTelType == cTelTypeSELPAL) || (ucTelType == cTelTypeSELPAL1) || (ucTelType == cTelTypeAK35def) || (ucTelType == cTelTypeAK35defLMA))
    {
      /* @@AS wenn System nicht zugeordnet wird ucZomPos=0x08 ????????????????*/
      Rte_Call_PP_GetWANonVolatileData_OP_GetHistWPOfID(ulTelID, &ucZomPos);

      // PWP: provisional wheel position implementation START
      if (ucGetColOfID(&ulTelID)<cMaxLR)
      {
#ifndef FD_CONTROLS_FALLBACK	
        Check4PWP ();
#endif
        if (cRadPosHR < ucZomPos)
        {
          ucZomPos = USEui8PWPofHistCol(ucGetColOfID(&ulTelID));
        }
      }
      // PWP: provisional wheel position implementation END


      if((cRadPosHR >= ucZomPos) && (ucReTel4FD == TRUE))/* CRS_1211_130_235*/
      {

        /******************************************************************************************************************/
        /*AFD function 5 Filling Detection Start reason III (3) Delta-p telegram received from prelearnt sensor		      */
        FillingDetectionAFDIII(ucTxTrigger);
        /******************************************************************************************************************/

        // update tire pressure and temperature
        if (ucZomPos == cRadPosVL)
        {
					scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc); /*CRS_1211_130_265*/
					//ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /*CRS_1211_130_214*/
					//ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/*CRS_1211_130_361*/	
          /*********************** cCAL_MANUAL_ACTIV Filling detection MFD ****************************************************************/
					ClearBitInNoCheckPmin4StopFD(cFD_Pmin_FL);/*CRS_1211_130_358 Freigabe der Prüfung von P_MIN immediately */							
					if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )) 
						|| ((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) ))
					{
						ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/* CRS_1211_130_370 siehe DP_AUTO */
						if((ucLastTirePressure != 0xFF) && (ucLastTirePressure != 0x00))/*CRS_1211_130_214*/
						{
							//INCucRErecCounter4FDVL(); /* CRS_1211_130_300 das zählen der Drucktelegramme sofort, Ergebnis cZO_FINISH usw */
							//FD_CalcAverageP4MFD(GETucRErecCounter4FDVL(),ucLastTirePressure,ucGetColOfID(&ulTelID));	/*CRS_1211_130_310*/	
							if(GETucRErecCounter4FDVL() < ucGetAvgCntr4FD(ulTelID))  /*CRS_1211_130_361*/
							{
								PUTucRErecCounter4FDVL(ucGetAvgCntr4FD(ulTelID));/*CRS_1211_130_361*/
							}
							PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID)); /* CRS_1211_130_361 neu Prelativ , alt Pabsolut */
							PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID)); /*CRS_1211_130_361 P relativ*/
							PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID)); /*CRS_1211_130_055 cal temperatur storage in ID ZOM POS without average!*/ 
						}
						/*********************** cCAL_AKTIV_AUTOMATIC Filling detection AFD****************************************************************/
						/************ 01.12.2016 CRS_1211_130_239  (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ) entfernen!!!*******************/
						if((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) )
						{
							ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /* CRS_1211_130_370 CRS_1211_130_364 --> Für AFD Kontrolle NICHT ucGetAvgPress4FD(ulTelID); verwenden!!*/												
							FD_HandleReceivedReRadPosVL4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS); /*CRS_1211_130_335 */
						}
					}	/* Hier Entfernung der Funktion "FD_UpdateComparePressure4NewId" nicht erst warten auf nächsten Empfang! siehe FD*/		
        }
        else if (ucZomPos == cRadPosVR){
          /*scTireTemp = (signed) (ucTelT-ucPalTempNormFACTORc);*/
					scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc); /*CRS_1211_130_265*/
  				//ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /*CRS_1211_130_214*/
					//ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/*CRS_1211_130_361*/
          /*********************** cCAL_MANUAL_ACTIV ****************************************************************/
					ClearBitInNoCheckPmin4StopFD(cFD_Pmin_FR);/*CRS_1211_130_358 Freigabe der Prüfung von P_MIN immediately */							
          //if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE) 	/*to discuss CRS_1211_130_189 SPECIAL_LEARN and COMPLETE LEARN finished ??*/			  
          //if((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )) /*@@AS cal request + Kfz faehrt v>20kmh? CRS_1211_130_065  */
					if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ))
						||((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) ) )
					{
						ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/* CRS_1211_130_370 siehe DP_AUTO */
						if((ucLastTirePressure != 0xFF) && (ucLastTirePressure != 0x00))/*CRS_1211_130_214*/            
						{
							//INCucRErecCounter4FDVR();
						  //FD_CalcAverageP4MFD(GETucRErecCounter4FDVR(),ucLastTirePressure,ucGetColOfID(&ulTelID));	/*CRS_1211_130_310*/
							if(GETucRErecCounter4FDVR() < ucGetAvgCntr4FD(ulTelID))  /*CRS_1211_130_361*/
							{
								PUTucRErecCounter4FDVR(ucGetAvgCntr4FD(ulTelID));/*CRS_1211_130_361*/
							}	
							PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID)); /* CRS_1211_130_361 neu Prelativ , alt Pabsolut */
							PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID)); /*CRS_1211_130_361 P relativ*/
							PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID)); /*CRS_1211_130_055 cal temperatur storage in ID ZOM POS without average!*/ 
						}
		        /*********************** cCAL_AKTIV_AUTOMATIC ****************************************************************/
						/** 01.12.2016 CRS_1211_130_239  (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ) entfernen!!!********/
						if((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) ) 
						{
							ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /* CRS_1211_130_370 CRS_1211_130_364 --> Für AFD Kontrolle NICHT ucGetAvgPress4FD(ulTelID); verwenden!!*/												
							FD_HandleReceivedReRadPosVR4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS); /*CRS_1211_130_335 */
						}
					}	/* Hier Entfernung der Funktion "FD_UpdateComparePressure4NewId" nicht erst warten auf nächsten Empfang! siehe FD*/		
        }
        else if (ucZomPos == cRadPosHL){
          /*scTireTemp = (signed) (ucTelT-ucPalTempNormFACTORc);*/
					scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc); /*CRS_1211_130_265*/
					//ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /*CRS_1211_130_214*/
					//ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/*CRS_1211_130_361*/
          /*********************** cCAL_MANUAL_ACTIV ****************************************************************/
					ClearBitInNoCheckPmin4StopFD(cFD_Pmin_RL);/*CRS_1211_130_358 Freigabe der Prüfung von P_MIN immediately */							 
          //if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE) 	/* to discuss CRS_1211_130_189 SPECIAL_LEARN and COMPLETE LEARN finished ??*/			  
					//if((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )) /*@@AS cal request + Kfz faehrt v>20kmh? CRS_1211_130_065  */
					if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ))
						||((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) ))/*CRS_1211_130_369*/
					{
						ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/*CRS_1211_130_370 siehe DP_AUTO */
						if((ucLastTirePressure != 0xFF) && (ucLastTirePressure != 0x00))/*CRS_1211_130_214*/            
						{
							//INCucRErecCounter4FDHL();
							//FD_CalcAverageP4MFD(GETucRErecCounter4FDHL(),ucLastTirePressure, ucGetColOfID(&ulTelID));/*CRS_1211_130_310*/
							if( GETucRErecCounter4FDHL() < ucGetAvgCntr4FD(ulTelID))  /*CRS_1211_130_361*/
							{
								PUTucRErecCounter4FDHL(ucGetAvgCntr4FD(ulTelID));/*CRS_1211_130_361*/
							}
							PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID)); /* CRS_1211_130_361 neu Prelativ , alt Pabsolut */
							PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID)); /*CRS_1211_130_361 P relativ*/
							PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID)); /*CRS_1211_130_055 cal temperatur storage in ID ZOM POS without average!*/ 
						}
						/*********************** cCAL_AKTIV_AUTOMATIC ****************************************************************/
						/** 01.12.2016 CRS_1211_130_239  (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ) entfernen!!!********/
						if((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) )
						{
							ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /*CRS_1211_130_370 CRS_1211_130_370 CRS_1211_130_364 AFD Kontrolle NICHT ucGetAvgPress4FD(ulTelID); verwenden!!*/								
							FD_HandleReceivedReRadPosHL4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS); /*CRS_1211_130_335 */
						}
					}	/* Hier Entfernung der Funktion "FD_UpdateComparePressure4NewId" nicht erst warten auf nächsten Empfang! siehe FD*/		
				}
        else if  (ucZomPos == cRadPosHR){
          /*scTireTemp = (signed) (ucTelT-ucPalTempNormFACTORc);*/
					scTireTemp = (signed) (ucGetLastReceivedTemp(ulTelID) - ucPalTempNormFACTOR4Calc); /*CRS_1211_130_265*/
					//ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /*CRS_1211_130_214*/
					//ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/*CRS_1211_130_361*/
          /*********************** cCAL_MANUAL_ACTIV ****************************************************************/	
					ClearBitInNoCheckPmin4StopFD(cFD_Pmin_RR);/*CRS_1211_130_358 Freigabe der Prüfung von P_MIN immediately */			
          //if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE) 	/* to discuss CRS_1211_130_189 SPECIAL_LEARN and COMPLETE LEARN finished ??*/			  
					
					//if((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )) /*@@AS cal request + Kfz faehrt v>20kmh? CRS_1211_130_065  */
					if(((bGETucCalRequestState(cCAL_MANUAL_ACTIV)) && (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ))
						||((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) ))
					{
						ucLastTirePressure = ucGetAvgPress4FD(ulTelID);/*CRS_1211_130_370*/
						if((ucLastTirePressure != 0xFF) && (ucLastTirePressure != 0x00))/*CRS_1211_130_214*/            
						{
							//INCucRErecCounter4FDHR();	
							//FD_CalcAverageP4MFD(GETucRErecCounter4FDHR(),ucLastTirePressure,ucGetColOfID(&ulTelID)); /*CRS_1211_130_310*/
							if(GETucRErecCounter4FDHR() < ucGetAvgCntr4FD(ulTelID))  /*CRS_1211_130_361*/
							{
								PUTucRErecCounter4FDHR(ucGetAvgCntr4FD(ulTelID));/*CRS_1211_130_361*/
							}							
							PUTucIdCalPressure(ucLastTirePressure,ucGetColOfID(&ulTelID)); /* CRS_1211_130_361 neu Prelativ , alt Pabsolut */
							PUTuiStoragePaverege4CompareValue(((uint16)ucLastTirePressure),ucGetColOfID(&ulTelID)); /*CRS_1211_130_361 P relativ*/ 
							PUTscIdCalTemperatur(scTireTemp,ucGetColOfID(&ulTelID)); /*CRS_1211_130_055 cal temperatur storage in ID ZOM POS without average!*/ 
						}
											
						/*********************** cCAL_AKTIV_AUTOMATIC ****************************************************************/
						/** 01.12.2016 CRS_1211_130_239  (bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE ) entfernen!!!********/
						if((bGETucCalRequestState(cCAL_AUTO_ACTIV)) && (GETushFDtimeout() > 0) )
						{
							ucLastTirePressure = ucGetLastReceivedPress(ulTelID); /*CRS_1211_130_370  CRS_1211_130_364 --> Für AFD Kontrolle NICHT ucGetAvgPress4FD(ulTelID); verwenden!!*/												
							FD_HandleReceivedReRadPosHR4AFD(ucLastTirePressure,scTireTemp,ucGetColOfID(&ulTelID),ucLTS); /*CRS_1211_130_335 */
						}
					}	/* Hier Entfernung der Funktion "FD_UpdateComparePressure4NewId" nicht erst warten auf nächsten Empfang! siehe FD*/		
        }
      }
    }
    }
    }
    GetZOMInfos2BeLogged(); // send telegramm data
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_ReceiveWAState
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <DE_ushWAState> of PortPrototype <PP_WAState>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_PP_WAState_DE_ushWAState(DT_ushWAState *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_PP_GetRecHistIDs_OP_GetRecHistIDs(UInt8 *ucRecHistID)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetWaTOErrorCode_OP_GetWaTOErrorCode(UInt8 *ucWaToErr, UInt8 ucColOfID)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveWAState(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_ReceiveWAState
 *********************************************************************************************************************/
  DT_ushWAState ushWaState;
  //DT_tData2Warn tData2Warn;	
  //uint8 ucWaErr;
  //uint8 idx;
  Rte_Read_PP_WAState_DE_ushWAState(&ushWaState);

  if ((ushWaState & cWAChange) > 0)
  {
    ClearBitBetriebszustandBZ( cEIGENRAD | cZUGEORDNET ); /* clear bits in case at least 1 new ID is detected */
    ClearTelStatisticsStruct((ushWaState & cWAChange)>>4);// reset telegramm statistics for new learned IDs
    //@@GL set zustandkennung here ?
  }

  if ( ((ushWaState>>8) & cTO) == cTO) /* WA Timeout ? */
  {
    SetBitBetriebszustandBZ(cZO_TIMEOUT);
  }
  else
  {
    ClearBitBetriebszustandBZ(cZO_TIMEOUT);
  }

  if ( ((ushWaState>>8) & cErrorActive) == cErrorActive) /* WA Error ? */
  {
    ClearBitBetriebszustandBZ( cZO_ERROR | cAL_RUNNING );//| cER_FINISH);
    SetBitBetriebszustandBZ(cZO_ERROR);
    //Rte_Call_PP_GetWaTOErrorCode_OP_GetWaTOErrorCode(&ucWaErr);
    /*if (ucWaErr == cFallback2History)
    {
    SetBitBetriebszustandBZ(cZO_Fallback2Hist);
    }*/
    if ( (ushWaState & cWAStateER) == cWAStateER) /* ER-Erkennung abgeschlossen ? */
    {
      SetBitBetriebszustandBZ( cER_FINISH );
    }
    if ( ((ushWaState>>8) & cTZG) == cTZG) /* WA Timeout ? */
    {
      SetBitBetriebszustandBZ(cTEILZUGEORDNET);
    }
  }
  else 
  {
    ClearBitBetriebszustandBZ( cZO_ERROR | cTEILZUGEORDNET);
    if ( (ushWaState & cWAStateZO) == cWAStateZO) /* ZG reached already ? */
    {
      SetBitBetriebszustandBZ( cER_FINISH | cZO_FINISH);
      ClearBitBetriebszustandBZ( cAL_RUNNING );
    }
    else if ( (ushWaState & cWAStateER) == cWAStateER) /* ER-Erkennung abgeschlossen ? */
    {
      SetBitBetriebszustandBZ( cER_FINISH );
      ClearBitBetriebszustandBZ( cZO_FINISH );
    }
    else
    { /* if ( (ucWaState & cWAStateER) == cWAStateER) */
      ClearBitBetriebszustandBZ( cER_FINISH | cZO_FINISH );

      if( (ushWaState & cWAStateActive) == cWAStateActive )
      {
        SetBitBetriebszustandBZ( cAL_RUNNING );
      }else
      { /* if( (ucWaState & cWAStateActive) == cWAStateActive ) */
        ClearBitBetriebszustandBZ( cAL_RUNNING );
      } /* if( (ucWaState & cWAStateActive) == cWAStateActive ) */
    } /* if ( (ucWaState & cWAStateER) == cWAStateER) */
  } /* if ( (ucWaState & cWAStateZO) == cWAStateZO) */

  if ((ushWaState & (cWAIDChanged | cWAWPChanged )) > 0)  // for any changes in WA better check necessity of RefPressure reload
  {    
    ReplayLastREvalue2Walgo(); /*CRS_1211_130_183 immediately update walgo all RE value  CRS_1211_032_121*/

    /****************************************************PRIO AFD 19min und AFD NEW ID ????????******/
		//CRS_1211_130_267 ClearBitCalRequestState(cCAL_AUTO_ENABLE2);/* clear startbit for AFDII and  NEXT drive  with Kl.15 cycle*/
    //CRS_1211_130_267 ClearBitCalRequestState(cCAL_AUTO_ACTIV);
    //PUTushCalTimeout(0); /* CRS_1211_130_204 KEIN RESET es kann eine MFD bereits aktiv sein !! siehe OPL#288  */
    /*********************************************************/
		/*CRS_1211_130_267 ist AFDII aktiv werden sowieso die Compare value neu gesetzt*/
		if ((ushWaState & (cWAIDChanged)) > 0)  /*CRS_1211_130_279/ 280  0x00F0  checker for NEW ID only,  update compare value*/ 
		{

		/* NEU nach SW WorkShop 23.02.17 DMC20076 : egal ob MFD oder AFD aktiv, sichere die  Compare Werte! */
		/*Papenb. KW45 Test FB CRS_1211_130_353 AUCH bei aktiver AFDIII Abruch organisieren!! */
			if((bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE ) &&  (bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE )
			|| ((bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE ) &&  (bGETucCalRequestState(cCAL_AUTO_ACTIV) == TRUE )))
			{
					PUTushFDtimeout(0); /* Position vorhanden CRS_1211_130_287 zuruecksetzen */
					PUTucFDtimerStop(TRUE); /*CRS_1211_130_337 Vorzeitiger FD Timeout*/
					SetBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD ); /* CRS_1211_130_346 set Look bit for start AFDII in next drive*/
			}
			//ClearAllReCnt4FD(); /*wenn AFDII aktiv, dann AFD beenden, wenn MFD aktiv MFD weiterlaufen lassen, die Telegramzaehler zuruecksetzen!*/
			SetBitCalRequestState2Ram(cCAL_AUTO_NEW_ID);/*CRS_1211_130_294 mit cCAL_AUTO_NEW_ID werden die Compare Werte gesichert! */
			ClearBitCalRequestState(cCAL_AUTO_ACTIV); /*Hier nicht "cCAL_RE_MISSING_NAK" löschen, da "Filling Not Detected" gesetzt werden muss!*/
		}
    ZomChangedWuInfoDcm(ushWaState);  /* new info of ZOM sorted Data for DCM */

#ifndef FD_CONTROLS_FALLBACK
    ClearPWP();
    if ((ushWaState & cWAStateER) == cWAStateER) // OIL #1129 in the WBT we trust  && (!(0x0200 == ushWaState)))
      Check4PWP (); // rebuild PWPs as soon as possible
#endif

  }
  else if (cAL_Error == ui8GetALState())
  {
    ReplayLastREvalue2Walgo ();
  }


#ifdef Test_LOG_ENABLE
  //GetZOMInfos2BeLogged();
#endif
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_ReceiveWarnOut
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceivedEvent for DataElementPrototype <DE_ushWarnOut> of PortPrototype <PP_WarnOut>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_PP_WarnOut_DE_ushWarnOut(DT_ushWarnOut *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Client/Server Interfaces:
 * =========================
 *   Server Invocation:
 *   ------------------
 *   Std_ReturnType Rte_Call_PP_GetWANonVolatileData_OP_GetHistID(UInt8 ucCol, UInt32 *ulID)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetWANonVolatileData_OP_GetHistWPOfID(UInt32 ulID, UInt8 *ucZomPos)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetWANonVolatileData_OP_GetWPOfCol(UInt8 ucCol, UInt8 *ucWP)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn(UInt8 pos, UInt8 *ucWheelPosWarn)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetWarningVectors_OP_GETushWarnstatus1WN(UInt16 *ushWarnOUtTM)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFL(UInt8 ucIdx, UInt16 *ushAbsSumCorr)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFR(UInt8 ucIdx, UInt16 *ushAbsSumCorr)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRL(UInt8 ucIdx, UInt16 *ushAbsSumCorr)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRR(UInt8 ucIdx, UInt16 *ushAbsSumCorr)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsCompFL(UInt8 ucIdx, UInt8 *ucAbsCompStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsCompFR(UInt8 ucIdx, UInt8 *ucAbsCompStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsCompRL(UInt8 ucIdx, UInt8 *ucAbsCompStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsCompRR(UInt8 ucIdx, UInt8 *ucAbsCompStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsLinFL(UInt8 ucIdx, UInt16 *ushAbsLinStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsLinFR(UInt8 ucIdx, UInt16 *ushAbsLinStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsLinRL(UInt8 ucIdx, UInt16 *ushAbsLinStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomAbsLinRR(UInt8 ucIdx, UInt16 *ushAbsLinStick)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomID(UInt8 ucIdx, UInt32 *ucZomID)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomPosOfID(UInt32 ulID, UInt8 *ucPos)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomStatisticTelCounter(UInt8 ucIdx, UInt8 *ucRetVal)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomStatus(UInt8 ucIdx, UInt8 *ucZomStatus)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrLearnBit(UInt8 ucIdx, UInt8 *ucRetVal)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrNoLearnBit(UInt8 ucIdx, UInt8 *ucRetVal)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoCorr(UInt8 ucIdx, UInt8 *ucRetVal)
 *     Synchronous Server Invocation. Timeout: None
 *   Std_ReturnType Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoLearnMode(UInt8 ucIdx, UInt8 *ucRetVal)
 *     Synchronous Server Invocation. Timeout: None
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_ReceiveWarnOut(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_ReceiveWarnOut
 *********************************************************************************************************************/
  //DT_ushWarnOut ushWarnOut;
  uint8 ucCol;
	//Rte_Read_PP_WarnOut_DE_ushWarnOut(&ushWarnOut);

  /*PAL logic  document V1.3 Section 6.8.2  Hold off = 0 if at least one pressure bolow P_MIN_TIRE */
  ucCol = ucGetColOfID(&ulTelID);
  if ( (ucCol < cMaxLR) && (ui8GetWarntypeOfHistCol(cDAG_PMin_WN,ucCol) == 0xFF))
  {
    SetPminDetected(TRUE);
  }
  else{
    SetPminDetected(FALSE);
  }

 

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_SI_GetInternalClock
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered by server invocation for OperationPrototype <OP_GetInternalClock> of PortPrototype <SI_GetInternalClock>
 *
 **********************************************************************************************************************
 *
 * Runnable prototype:
 * ===================
 *   void RCtApHufTPMSmgr_SI_GetInternalClock(UInt32 *ulInternalCLock)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_SI_GetInternalClock(P2VAR(UInt32, AUTOMATIC, RTE_CTAPHUFTPMSMGR_APPL_VAR) ulInternalCLock) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_SI_GetInternalClock
 *********************************************************************************************************************/
 GetInternMSTime(ulInternalCLock);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutEngCtrl
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <Eng_Rs_EngCtrl_Pr2> of PortPrototype <R_Eng_Rs_EngCtrl_Pr2>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutEngCtrl(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutEngCtrl
 *********************************************************************************************************************/
 SetFzzSignalTimeOutState(cFZZ_ENG_CTRL_TIMEOUT);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutEnvPressure
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <AirPress_Outsd> of PortPrototype <R_AirPress_Outsd>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutEnvPressure(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutEnvPressure
 *********************************************************************************************************************/
 SetFzzSignalTimeOutState(cFZZ_PRESS_OUT_TIMEOUT);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutIcBasicInfo
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <AirTemp_Outsd_Disp> of PortPrototype <R_AirTemp_Outsd_Disp>
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <Odo> of PortPrototype <R_Odo>
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <VehSpd_Disp> of PortPrototype <R_VehSpd_Disp>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcBasicInfo(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutIcBasicInfo
 *********************************************************************************************************************/
  
  tEnvDataToSend.ushVehSpeed = 0; //assume 0 km/h
  Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
  /* send environment data to VEhicle state manager */
  SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);

  SetFzzSignalTimeOutState(cFZZ_IC_BASIC_INFO_TIMEOUT);
  //ClearFzzSignalUnplausibleState(cFZZ_VEH_SPEED_IMPLAU | cFZZ_AIRTEMP_OUT_IMPLAU);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutIcDateTime
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <DateTm_AR2> of PortPrototype <R_DateTm_AR2>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcDateTime(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutIcDateTime
 *********************************************************************************************************************/
 SetFzzSignalTimeOutState(cFZZ_IC_DATE_TIME_TIMEOUT);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutIcSettings
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <TPM_Actv_Rq_V2> of PortPrototype <R_TPM_Actv_Rq_V2>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIcSettings(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutIcSettings
 *********************************************************************************************************************/
 
  SetFzzSignalTimeOutState(cFZZ_IC_SETTINGS_TIMEOUT);
  //ClearFzzSignalUnplausibleState(cFZZ_IC_A3_TPM_ACTV_IMPLAU); // clear implausible state
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutIgnStat
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <Ign_Stat_Pr2> of PortPrototype <R_Ign_Stat_Pr2>
 *
 **********************************************************************************************************************
 *
 * Input Interfaces:
 * =================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Read_R_Ign_Stat_Pr2_Ign_Stat_Pr2(REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_PP_EnvData_DE_tEnvData(const DT_tEnvData *data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 * Service Calls:
 * ==============
 *   Service Invocation:
 *   -------------------
 *   Std_ReturnType Rte_Call_UR_ComMUser_HMI_RequestComMode(ComM_ModeType ComMode)
 *     Synchronous Service Invocation. Timeout: None
 *     Returned Application Errors: RTE_E_ComM_UserRequest_E_MODE_LIMITATION, RTE_E_ComM_UserRequest_E_NOT_OK
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutIgnStat(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutIgnStat
 *********************************************************************************************************************/
  tEnvDataToSend.ucKlState = Off;
  /* use this function to transform from CAN to warnmodule */ 
  Rte_Write_PP_EnvData_DE_tEnvData(&tEnvDataToSend);
  
  /* send environment data to VEhicle state manager */
  SendEnvData2VehStateMgr((uint8*)&tEnvDataToSend);
  SetFzzSignalTimeOutState(cFZZ_IGN_VEH_STAT_TIMEOUT);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutPN14EOLDispRq
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <PN14_EOL_Disp_Rq> of PortPrototype <R_PN14_EOL_Disp_Rq>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutPN14EOLDispRq(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutPN14EOLDispRq
 *********************************************************************************************************************/
  
  c03_EOL_Disp_Rq value;

  Rte_Read_R_PN14_EOL_Disp_Rq_PN14_EOL_Disp_Rq(&value);
    
  if( (bOnce==FALSE) && ((value == I_C03_EOL_DISP_RQ_IOD_MEAS) || (value == I_C03_EOL_DISP_RQ_IOD_ERR)) )
  {
    /* requirement is: set to init value if CAN timeout happens */
    ResetStanbyTimer();
    bOnce = TRUE; /* just do it once each reset cycle */
  }

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutSupPN14BatStat
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <PN14_SupBat_Stat> of PortPrototype <R_PN14_SupBat_Stat>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutSupPN14BatStat(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutSupPN14BatStat
 *********************************************************************************************************************/
 SetFzzSignalTimeOutState(cFZZ_PN14_STAT_TIMEOUT);

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_TimeOutWhlPlsCnt
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on DataReceiveErrorEvent for DataElementPrototype <WhlPlsCnt_TPM_Pr2> of PortPrototype <R_WhlPlsCnt_TPM_Pr2>
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_TimeOutWhlPlsCnt(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_TimeOutWhlPlsCnt
 *********************************************************************************************************************/
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
  //Rte_Call_R_OHDS_GetOperatingHours_GetOperatingHours(&refTime, NULL_PTR, NULL_PTR);

  PutABS((uint16)refTime, ushTESTABStick);
  SetFzzSignalTimeOutState(cFZZ_WHLPLS_CNT_TIMEOUT);
  //ClearFzzSignalUnplausibleState(cFZZ_WHLPLS_FL_IMPLAU | cFZZ_WHLPLS_FR_IMPLAU | cFZZ_WHLPLS_RL_IMPLAU | cFZZ_WHLPLS_RR_IMPLAU | cFZZ_TRACTION_SYSTEM_IMPLAU);
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_WrBusMsg
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 1s
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
 *   Std_ReturnType Rte_Write_P_Awake_Diag_Actv_Awake_Diag_Actv(DC_BOOL data)
 *   Std_ReturnType Rte_Write_P_Awake_Ignition_On_Awake_Ignition_On(DC_BOOL data)
 *   Std_ReturnType Rte_Write_P_Awake_NwSt_Awake_NwSt(DC_BOOL data)
 *   Std_ReturnType Rte_Write_P_Awake_Warn_Actv_Awake_Warn_Actv(DC_BOOL data)
 *   Std_ReturnType Rte_Write_P_RefPress_RefPress(const REC_RefPress *data)
 *   Std_ReturnType Rte_Write_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2(const REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt *data)
 *   Std_ReturnType Rte_Write_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old(const REC_TPM_Lmp_On_Rq_old *data)
 *   Std_ReturnType Rte_Write_P_Tire_Stat_V2_Tire_Stat_V2(const REC_Tire_Stat_V2 *data)
 *   Std_ReturnType Rte_Write_P_Tire_Temp_V2_Tire_Temp_V2(const REC_Tire_Temp_V2 *data)
 *   Std_ReturnType Rte_Write_P_WakeupRsn_TPM_WakeupRsn_TPM(c08_WakeupRsn_TPM data)
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *   uint32 E2EPW_Write_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2(REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt *data)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrBusMsg(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_WrBusMsg
 *********************************************************************************************************************/
    /*------------------update TPM Display RQ ------------------------------------------------------------------*/
	if(( bGETucCalRequestState(cCAL_MSG2DISP) == TRUE) && (GETucTimer4MsgDispRq() != 0 )) /* CRS_1211_130_052 manual KAL.*/
	{
    setTireStatMsgDispRestart(); //sgDisptTireStat.TPM_MsgDisp_Rq = I_C04_TPM_MSGDISP_RQ_RESTART;
		/*CR_1211_130_051 clear warning message and warning lamp immediately for 5sec CAN message ONLY! */
	}
	else
	{
	  clearTireStatMsgDispRestart();
		
		/*@@AS Hier den zyklischen Aufruf von CLEAR vermeiden! NVM Abgleich!!*/
		//if( bGETucCalRequestState(cCAL_MSG2DISP) == TRUE)
		//{
			ClearBitCalRequestState(cCAL_MSG2DISP); /* 5sec Timer ucTimer4MsgDispRq  empty*/
		//}
  }

  /*------------------------------reset warnmodule----------------------------------------------------------------*/
  //@@TODO GL move this to a separate function
  if (bGetBitBetriebszustandBZ(cZO_ERROR | cZO_TIMEOUT))
	{  
    NewPositionsUSWIF( (uint8 *)GETpucStartAdrWPorPWP() ); // send new position to warning module
  }
  else if (bGetBitBetriebszustandBZ(cZO_FINISH))
  {
    NewPositionsUSWIF( (uint8 *)GETpucStartAdrWPorPWP() ); // send new position to warning module
  }

  /*-------------------------------------enable / disable measurement------------------------------------------------------*/
  if (GETucMeasurementStateOfRam() == TRUE)
	{
	  Com_IpduGroupStart(Com_PduGrp_TxMess_TPM_HMI, TRUE);
	}	
	else{
	  Com_IpduGroupStop(Com_PduGrp_TxMess_TPM_HMI);
  }

	UpdateTxBusMsg();
	UpdateCanMState();

  //-----------------------------
	Rte_Write_P_RefPress_RefPress(pGetHmiRefPress());
	// add CRC protection
#if E2E_ENABLE
	ucHufE2EWrapperProtectTireState2((uint8*) pGetTpmLmpOnRq());
#endif
	//
	Rte_Write_P_TPM_Lmp_On_Rq_Pr2_TPM_Lmp_On_Rq_Pr2(pGetTpmLmpOnRq());
	Rte_Write_P_TPM_Lmp_On_Rq_old_TPM_Lmp_On_Rq_old(pGetTpmLmpOnRqOld());
	Rte_Write_P_Tire_Stat_V2_Tire_Stat_V2(pGetTireStat());
	Rte_Write_P_Tire_Temp_V2_Tire_Temp_V2(pGetTireTemp());

	/* Network managenment messages */
	Rte_Write_P_WakeupRsn_TPM_WakeupRsn_TPM(ucGetHMIWakeUpRsn());
	Rte_Write_P_Awake_Diag_Actv_Awake_Diag_Actv(bGetHMIAwakeDiagActv());
  Rte_Write_P_Awake_Ignition_On_Awake_Ignition_On(bGetHMIAwakeIgnitionOn());
  Rte_Write_P_Awake_NwSt_Awake_NwSt(bGetHMIAwakeNwSt());
  Rte_Write_P_Awake_Warn_Actv_Awake_Warn_Actv(bGetHMIAwakeWarnActv());

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_WrDisplayMsg
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 10ms
 *
 **********************************************************************************************************************
 *
 * Output Interfaces:
 * ==================
 *   Explicit S/R API:
 *   -----------------
#ifdef RTE_PTR2ARRAYBASETYPE_PASSING
 *   Std_ReturnType Rte_Write_P_Meas_TPM_1_Meas_XX(const c08_UInt_SNA_na *data)
#else
 *   Std_ReturnType Rte_Write_P_Meas_TPM_1_Meas_XX(const ARR_08_UInt_noSNA_8 *data)
#endif
 *
 *   E2E Protection Wrapper API:
 *   ---------------------------
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrDisplayMsg(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_WrDisplayMsg
 *********************************************************************************************************************/

  ARR_08_UInt_noSNA_8 tHufDevMsg;
  DT_HufDisplay temp;
  
  /*-------------------------------------enable / disable measurement------------------------------------------------------*/
  if (GETucMeasurementStateOfRam() == TRUE)
	{
    // do nothing in case the queue is empty
    if (ucTraceGetDataFromQueue( &temp ))//Rte_Receive_PpHufDisplay_HufDisplay(&tHufDisplay) == E_OK)
    {
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

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}

/**********************************************************************************************************************
 *
 * Runnable Entity Name: RCtApHufTPMSmgr_WrTpmMsgDispRq
 *
 *---------------------------------------------------------------------------------------------------------------------
 *
 * Executed if at least one of the following trigger conditions occurred:
 *   - triggered on TimingEvent every 1s
 *
 **********************************************************************************************************************
 *
 * Inter Runnable Variables:
 * =========================
 *   Explicit Read Access:
 *   ---------------------
 *   Boolean Rte_IrvRead_RCtApHufTPMSmgr_WrTpmMsgDispRq_IRV_TpmActvRq_TpmMsgDispRq(void)
 *
 *   Explicit Write Access:
 *   ----------------------
 *   void Rte_IrvWrite_RCtApHufTPMSmgr_WrTpmMsgDispRq_IRV_TpmActvRq_TpmMsgDispRq(Boolean data)
 *
 *********************************************************************************************************************/

FUNC(void, RTE_CTAPHUFTPMSMGR_APPL_CODE) RCtApHufTPMSmgr_WrTpmMsgDispRq(void) /* PRQA S 0850 */ /* MD_MSR_19.8 */
{
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of runnable implementation >>             DO NOT CHANGE THIS COMMENT!
 * Symbol: RCtApHufTPMSmgr_WrTpmMsgDispRq
 *********************************************************************************************************************/
//REC_Tire_Stat_V2 tmp;
uint8 ucRtn=FALSE;

/** 5.6.2 Storing compare value after warning message P&T of THIS TIRE! ***********************************************/
		//14.10.16Frage an W.K.: Hier werden bei Warnung die CompValue sofort mit dem erst gültigen Wert gesetzt! 
		FD_UpdateComparePressureAtWarning(GetucTPM_WarnDisp_Rq()); 
/*********************************************************************/
  if( GETucTimer4MsgDispRq()  > 0) /* MFD only! display 5sec timer for Mcalibration only */
	{
 		//ucPMinWarn4AS=GETucMinWarnThresholdOfRam(); /*commented out to avoid warning, variable not used*/
		//ucTimer4MsgDispRq--;		
		DECucTimer4MsgDispRq();

		if(GETucTimer4MsgDispRq() == FALSE)
		{
			/* NACHLADEN der Druckwerte z.B. Pmin CRS_1211_130_176*/
			/* bei Neuinitialisierung an dieser Stelle werden Warnungen ausgegeben LOW PRESSURE*/
		 ReplayLastREvalue2Walgo();
 		}
	}
/********************************************************************************************/
/* 9 min CAL timer management and manual+ auto  filling detection check after 1 or 3 telegrams received */
/********************************************************************************************/
	if( GETushFDtimeout()  > 0)
  {
		if(bGetBitFahrzeugzustandFZZ( cKFZFAEHRT_20KMH ) == TRUE )/*CRS_1211_130_171 Papenburg: CalTimer dec nur bei Kfz fährt*/
    {
			DECushFDtimeout();
			DECushSupervisoryTimerFD();	
		}

   /*CRS_1211_130_060 calibration finish before timeout end ? */
		if((bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) && (GETucTimer4MsgDispRq() == FALSE)) /*AFD Timer4MsgDis =0 allways MFD+AFD activ!*/
		{
			if(FD_FlowChartFct1CheckPmin() == TRUE) /* CRS_1211_130_335 MFD+AFD! according flow chart function1:check Pmin result=FALSE-> FD aborted  */
			{
				if(FD_FlowChartFct1CheckMissingRE() == TRUE) /* CRS_1211_130_335 MFD+AFD! according flow chart function1:check Sensormissing result=FALSE-> FD aborted  */
				{
					if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE) /*MFD  CAL started ??????? */
					{
						/***************************************************************************************************/	
						/************************ MFD 3 ReData from all positions received *********************************/
						FD_Check3RePlausiSetMilage4FinishedMFD(); /*CRS_1211_130_335 */
						/************************ MFD 3 ReData from all positions received *********************************/
						/***************************************************************************************************/	
					}
					else
					{
						/***************************************************************************************************/	
						/************************ AFD 3 ReData from all positions received *********************************/
						FD_Check3ReAndUpdatePifWarnLampOnOffDefOrInf2Re4FinishedAFD(); /*CRS_1211_130_335 */
						/************************ AFD 3 ReData from all positions received *********************************/
						/***************************************************************************************************/	
					}
				} /* OIL#1322 RE Missing und NEW ID -> RE Missing= FD Aborted <-->  NEW ID update compare pressure!*/
			}
		}
	}
  else
	{
		/***************************************************************************************************************/
		/*timeout = 0  5.2. Abort filling detection [1] [2] [3] ACHTUNG! DMC20073 Test mit RESET ist ushCalTimeout=0!! */
		/* CRS_1211_130_335*/

		ucRtn=FALSE; /* FALSE = Echte Timeout Beahndlung*/
		if(bGETucCalRequestState(cCAL_MANUAL_ACTIV) == TRUE) /*MFD?*/
		{
			if(GETucFDtimerStop() == FALSE) /* CRS_1211_130_337 FALSE=Echter Timeout kein vorzeitiger Abbruch! */
			{
				if(GETushSupervisoryTimerFD() == GETushFDtimeout()) /* 5sec Hosenträger NUR für ECHTEN FD Timeout*/
				{
					PUTushSupervisoryTimerFD(6); /* Hosentraeger 5sec  */
					/*SetBitFillingDetectionStateFD(0x10); @@ AS TEST */
					ucRtn=TRUE;
				}
				else
				{
					/* Achtung,  GETushSupervisoryTimerFD kann einen Wert >6  haben ! Vorzeitiger FD Abruch!!*/
					if(	GETushSupervisoryTimerFD() > 1 )
					{	
						DECushSupervisoryTimerFD();
						ucRtn=TRUE; /* Für Prüfung im Nachlauf*/
					}
					else
					{
						ucRtn=FALSE; /* Nachlauf und Prüfung stopp! MFD Timeout siehe OIL#1310 mit bGetBitBetriebszustandBZ(cZO_TIMEOUT) == FALSE !!!*/ 
					}
				}
				if((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE ) && ((ui8GetALState() == cAL_Stored) || (ui8GetALState() == cAL_OK) || (Getui8ColPWPActive() != FALSE))) /*TRUE = FB Mode*/
				{
					if(ucRtn==TRUE) /*Prüfung im Nachlauf!! */
					{
						if(FD_UpdateIDvalue4MFD() == TRUE) /* CRS_1211_130_335*/
						{
							if(FD_FlowChartFct1() == TRUE) /* CRS_1211_130_335 MFD+AFD! according flow chart function1: check Pmin +Sensormissing and set result  */
							{
								FD_Check3RePlausiSetMilage4FinishedMFD(); /*CRS_1211_130_335 TRUE=MFD okay*/
							}	
							else
							{
								ucRtn=FALSE; /* Pmin oder Sensor missing gesetzt FD stopp [cCAL_REQUEST=FALSE] */
							}
						}
					}
				}			
				else
				{
					/*09.02.2018 MFD Timeout siehe OIL#1310 mit bGetBitBetriebszustandBZ(cZO_TIMEOUT) == FALSE !!!*/ 
				}			
			}
		}
		if(ucRtn==FALSE)
		{
		/****************************************************************************************************************************/
		/* SONDERFALL																																																								*/
		/* MFD aktiv ABER nicht beendet, auch nicht Timeout!! KL.15AUS oder KL15 bleibt EIN, SOFTreset und KL.15EIN --> Start der MFD*/
		/* MFD:+FDTimeout z.B. NUR 3RE's senden -->PUTucFDtimerStop(TRUE): 2.Durchlauf ist GETucFDtimerStop=TRUE! CAL_ABORT_REASON_2_3)*/
		/*****************************************************************************************************************************/
			if((bGetBitBetriebszustandBZ(cCAL_REQUEST) == TRUE) && (GETucTimer4MsgDispRq() == FALSE)) /*calibration activ! allways and MsgDispRq 0sec!! CRS_1211_130_087*/
			{
				/* AFD Soft Reset? Starte MFD NEU ?? ****************************/
				/* && Kl.15 on, Anzeige muss sichtbar sein CRS_1211_130_293 */
				/* && CRS_1211_130_155 first auto filling detection         */
				/* CRS_1211_130_350 Abfragen zusammengefaßt!*/

				if(( ushGetCurrentECUParkingTime() >= cT_STANBY )
					&& (bGetBitFahrzeugzustandFZZ( cKL_15_EIN )	== TRUE)
					&& (bGETucCalRequestState(cCAL_MANUAL_ACTIV)== TRUE)
					&& (bGETucCalRequestState(cCAL_AUTO_FIRST)	== TRUE))	
				{
					ClearBitBetriebszustandBZ(cCAL_REQUEST); 
					FillingDetectionMFD(FALSE);/*CRS_1211_130_312 starte und initialisiere die MFD NEU!! ABER ohne RESTART[6) Anzeige siehe Aussage WK SW WorkShop 12.04.2017 */
				}
				else 
				{
				/* AFD * KEIN Soft Reset	*********************************************************************************************/
				/* jetzt echte Timoutbehandlung!*/
				/* Prüfung des Betriebszustandes auf  cZO_TIMEOUT-Bit und cZO_FINISH-Bit optional cZO_ERROR-Bit */
				/* 1.) cZO_TIMEOUT=1 und cZO_FINISH=0 und cZO_ERROR=1 --> Sensor Missing */
				//if((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE) ||  (bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)) /*CRS_1211_130_337*/
				/* CRS_1211_130_337 Echter Timeout FALSE= kein vorzeitiger Abbruch!  CRS_1211_130_356 NEW ID??*/
					if((GETucFDtimerStop() == FALSE) && (bGETucCalRequestState(cCAL_AUTO_NEW_ID) == FALSE)) 
					{
						if((bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE) ||  (bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)) /*CRS_1211_130_337*/
						{
							if(bGetBitBetriebszustandBZ(cZO_TIMEOUT) == TRUE)
							{		
								if(GETushSupervisoryTimerFD() == GETushFDtimeout()) /* 5sec Hosenträger NUR für ECHTEN FD Timeout*/
								{
									PUTushSupervisoryTimerFD(6); /* Hosentraeger 5sec  */
									/*SetBitFillingDetectionStateFD(0x20); @@ AS TEST */
								}
								else
								{
									if(	GETushSupervisoryTimerFD() > 1 )
									{	
										DECushSupervisoryTimerFD();
										if(bGetBitBetriebszustandBZ(cZO_FINISH) == TRUE)	
										{
											PUTucFDtimerStop(TRUE); /* ZO Finish UND ZO Timeout --> ALLES i.O.!*/
										}
									}
									else
									{
										PUTucFDtimerStop(TRUE); /*ZO Timeout OHNE ZO Finish also ERROR z.b. RE missing*/
									}
								}
							}
							else
							{
								PUTucFDtimerStop(TRUE); /* ZO Finish ohne ZO Timeout --> ALLES i.O.!*/
							}
						}
					}
					else /* Vorzeitiegr Abbruch! oder ZO Timeout OHNE und MIT ZO Finish oder NUR  ZO Timeout also ERROR z.b. RE missing*/
					{
						if(FD_FlowChartFct1() == TRUE) /* CRS_1211_130_343 FD_AbortFillingDetectionmit cCAL_P_MIN_TIRE_NAK und cCAL_RE_MISSING_NAK --> TRUE = kein Pmin und Kein RE missing! Bereits während FD gesetzt!*/
						{
							if(bGETucCalRequestState(cCAL_AUTO_NEW_ID) == TRUE)	/*CRS_1211_130_287 timeout ist auf 0 gesetzt aufgrund von 	cCAL_AUTO_NEW_ID*/		
							{
								FD_AbortFillingDetection(cCAL_AUTO_NEW_ID); /* AFD: Abort reason in Fill_detect_start_reason2_3 0x00*/
							}
							else
							{
								/* AS 09.02.2018  OIL#1309+OIL#1310: Auch die MFD landet hier!! z.B. NO_LEARN mit ECU_C_ZOM_Tio=175 und MFD Neustart mit Ausfall einer oder 3RE's!!!*/
								/* Hier ID spezifische AFD Behandlung einbauen*/
								/* cZO_TIMEOUT-Bit und cZO_FINISH-Bit: 10= ZO_Timeout=Fehlerfall; 01=ZO_ Finish=Gutfall; 11= Gutfall im ZO Timeout */
								/* if( ZO_FINISH) NEIN --> 5sec warten und cZO_TIMEOUT prüfen! */
								/* CRS_1211_130_337*/
								FD_AbortFillingDetection(cCAL_ABORT_REASON_2_3); /* AFD: Abort reason in Fill_detect_start_reason2_3 0x00*/
							}
						}
					}
					/* hier Ende der echte Timoutbehandlung!*/
					/*****************************************************************************************************************************/
				}
			}
			else /*CRS_1211_130_356*/
			{
				/*****************************************************************************************************************************/
				/* Start Update Compare value for receive NEW ID!*/
				if(bGETucCalRequestState(cCAL_AUTO_NEW_ID) == TRUE)	/*CRS_1211_130_356 timeout ist auf 0 gesetzt aufgrund von cCAL_AUTO_NEW_ID*/		
				{
					//SetState2FillingDetectionStateFD((Get_FD_STATUS()+1)); /* AS TEST!!!  4 UPDATE cmp value*/		
					
					ucRtn=FD_LoadIdValues4UpdateCompareValue(); /* TRUE= all ZOpos or FBMpos are available!*/
					if(ucRtn == TRUE) /*CRS_1211_130_356 warte bis die Druckwerte vorhanden sind */
					{
						ClearBitCalRequestState(cCAL_AUTO_NEW_ID);
					}
					else
					{
						if((bGETucCalRequestState(cCAL_AUTO_ENABLE2) == TRUE ) || (bGETucCalRequestState(cCAL_AUTO_ENABLE3) == TRUE ))
						{
							ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2); /*CRS_1211_130_353 AFDII oder AFDIII aktiv-> rücksetzen. ACHTUNG bei NEW ID ist "cCAL_AUTO_ACTIV" bereits gelöscht!*/							
							if(ucRtn == FALSE) /*FALSE*/
							{						
								SetBitFillingDetectionStateFD(cFILLING_NOT_DETECTED); /* CRS_1211_130_283 und TEST für ID bezogenen FD!*/
								//ClearBitCalRequestState(cCAL_AUTO_ENABLE3 | cCAL_AUTO_ENABLE2); /*CRS_1211_130_353 AFDII oder AFDIII aktiv-> rücksetzen. ACHTUNG bei NEW ID ist "cCAL_AUTO_ACTIV" bereits gelöscht!*/
							}
							else /*cRadPosUkw FBM*/
							{
								SetState2FillingDetectionStateFD(cFILLING_DETECT_ABORTED);/* AFD only CRS_1211_130_274*/
								SetState2AbortReasonFD(cFD_FBM_ACTIV); /*CRS_1211_130_323 AFD only OIL#1079  #  OIL#954 SW Workshop KW13 Stopp AFD once*/
								SetBitCalNotAckState2Ram(cCAL_FBM_ACTIV_NAK); /*CRS_1211_130_275 Stopp AFD once*/
							}
						}
					}
				}
				/* END Update Compare value for receive NEW ID!*/
				/*****************************************************************************************************************************/
			}
		}
	}

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of runnable implementation >>               DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
}


#define RTE_STOP_SEC_CTAPHUFTPMSMGR_APPL_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of function definition area >>            DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
void Appl_CanSM_BusOffBegin( NetworkHandleType CanSm_NetworkHandle, CanSM_BorCounterType CanSM_BufOffNotificationCounter)
{
  SetFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network);
}

void Appl_CanSM_BusOffEnd( NetworkHandleType CanSm_NetworkHandle)
{
  ClearFzzSignalTimeOutState(cFZZ_CANSM_BUSOFF_Network);
}


boolean LearningWheelPosActiveSM( void )
{
boolean bLearnActive = FALSE;

//GetVehicleDrivingState(&ucTempDrivingState);

if (bGetBitFahrzeugzustandFZZ(cFAHRZEUG_FAEHRT))//( ucTempDrivingState == cFAHRZEUG_FAEHRT)
{
	/*
	* Fahrzeug fährt
	*/
	 
	if( bGetBitBetriebszustandBZ( cZO_FINISH) == FALSE )
	{
		/*
		* Radpositionen nicht bestätigt
		*/
		if( bGetBitBetriebszustandBZ( cZO_TIMEOUT ) == FALSE )
		{
			/*
			* Timeout Radpositionserkennung nicht abgelaufen
			*/
			bLearnActive = TRUE;
		}else{ /* if( bGetBitBetriebszustandBZ( cZO_TIMEOUT ) == FALSE ) */
			/*
			* Timeout Radpositionserkennung abgelaufen
			*/
			bLearnActive = FALSE;
		} /* if( bGetBitBetriebszustandBZ( cZO_TIMEOUT ) == FALSE ) */
	}else{ /* if( bGetBitBetriebszustandBZ( cWA_FINISH ) == FALSE ) */
		/*
		* Radpositionen bestätigt
		*/
		bLearnActive = FALSE;
	} /* if( bGetBitBetriebszustandBZ( cWA_FINISH ) == FALSE ) */
}else{ /* if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE ) */
		/*
		* Fahrzeug steht oder fährt rückwärts
		*/
		bLearnActive = FALSE;
} /* if( bGetBitFahrzeugzustandFZZ( cFAHRZEUG_FAEHRT ) == TRUE ) */

return( bLearnActive );
}

/*
void GetVehicleDrivingState(uint8*  ucDrivingStateTemp)
{
	*ucDrivingStateTemp = ucDrivingState;
}*/



static void GetZOMInfos2BeLogged(){
  uint8 ucIDPosInZom;
  uint16 i; //ushLinABStick[4];
  uint8 ucTemp1, ucTemp2;
  debugTelStructPos *tdebugTelStructPos;
  debutTelWallocStruct tDebutTelWallocStruct;




    /* get current status of counters*/
    Rte_Call_PP_GetZomData_OP_GetZomPosOfID(ulTelID, &ucIDPosInZom);
    //ucIDPosInZom = ucGetZOMPosOfID(&ulID);
    //if (ucIDPosInZom<cSumWE ){
    tDebugTelStruct.ulID = ulTelID;
    tDebugTelStruct.ucIDPosInZom = ucIDPosInZom;//ucTelStatGetIDPosInTable(ulTelID); // position in table
    tDebugTelStruct.ulTimeStamp = ulTelTimeStamp;
    tDebugTelStruct.ucPAL = ucTelPal;
    tDebugTelStruct.ucP = ucGetLastReceivedPress(ulTelID);
    tDebugTelStruct.ucT = ucGetLastReceivedTemp(ulTelID);
    tDebugTelStruct.ucAvgRssi = ucTelAvgRSSI;
    tDebugTelStruct.ucTelType = ucTelType;
		
    tDebugTelStruct.ucTelByte00 = tReTelData[5];//ucTelType;
    tDebugTelStruct.ucTelByte01 = tReTelData[6];//(uint8) (ulID>>24);
    tDebugTelStruct.ucTelByte02 = tReTelData[7];//(uint8) (ulID>>16);
    tDebugTelStruct.ucTelByte03 = tReTelData[8];//(uint8) (ulID>>8);
    tDebugTelStruct.ucTelByte04 = tReTelData[9];//(uint8) (ulID>>0);
    tDebugTelStruct.ucTelByte05 = tReTelData[10];//ucP;
    tDebugTelStruct.ucTelByte06 = tReTelData[11];//ucT;
    tDebugTelStruct.ucTelByte07 = tReTelData[12];//ucPAL;
    tDebugTelStruct.ucTelByte08 = tReTelData[13];//(uint8) (ushStatusField>>8);
    tDebugTelStruct.ucTelByte09 = tReTelData[14];//(uint8) ushStatusField;
		
    GETDAGWrnLvlOfIdCol(ucGetColOfID(&tDebugTelStruct.ulID), (uint8*)&tDebugTelStruct.ushPref_WTPmin); // ucWT_DHW, ucWT_Pmin, ucWT_HW, ucWT_WW
    //tDebugTelStruct.ushPref_WTPmin = ui8GetWrnLvlPMin();
    //tDebugTelStruct.ushPref_WTDHW = ui8GetWrnLvlDHW();
    //tDebugTelStruct.ushPref_WTHW = ui8GetWrnLvlHard();
    //tDebugTelStruct.ushPref_WTWW = ui8GetWrnLvlSoft();
    tDebugTelStruct.ushTref_WTHW = 0xFF;
    tDebugTelStruct.ushTref_WTWW = 0xFF;
    //Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoLearnMode(ucIDPosInZom, &tDebugTelStruct.ucZomToothTelCtNoLearnMode);
    tDebugTelStruct.ECU_C_RecBlocks = ui8GetComptoirRepare();

    if (ucGetColOfID(&ulTelID)<4)
    {
      tDebugTelStruct.ucPcompCurrID = ui8GetPRelComp2Tref((sint8)(tDebugTelStruct.ucT-ucPalTempNormFACTORc), ucGetColOfID(&ulTelID));
      tDebugTelStruct.ucPrefCurrID = ui8GetPRefRel(ucGetColOfID(&ulTelID));
      tDebugTelStruct.ucTrefCurrID = i8GetTref(ucGetColOfID(&ulTelID));
    }else
    {
      tDebugTelStruct.ucPcompCurrID = 0xFF;
      tDebugTelStruct.ucPrefCurrID = 0xFF;
      tDebugTelStruct.ucTrefCurrID = 0xFF;
    }


    if ( GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) < cAnzRad) 
    {
      if ( GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) == cRadPosVL) // ID is localised
      {
        tdebugTelStructPos = &tdebugTelStructPosFL;
      }
      else if ( GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) == cRadPosVR) // ID is localised
      {
          tdebugTelStructPos = &tdebugTelStructPosFR;
      }
      else if ( GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) == cRadPosHL) // ID is localised
      {
          tdebugTelStructPos = &tdebugTelStructPosRL;
      }
      else //if ( GetCurUsedWPOfCol(ucGetColOfID(&ulTelID)) == cRadPosHR) // ID is localised
      {
          tdebugTelStructPos = &tdebugTelStructPosRR;
      }

      //tdebugTelStructPos->ulID = ulTelID;
      //tdebugTelStructPos->ucP = ucGetLastReceivedPress(ulTelID);
      //tdebugTelStructPos->ucT = ucGetLastReceivedTemp(ulTelID);
      //tdebugTelStructPos->ucPref = ui8GetPRefRel(ucGetColOfID(&ulTelID));
      //tdebugTelStructPos->ucTref = i8GetTref(ucGetColOfID(&ulTelID));
      //tdebugTelStructPos->ucWT_DHW = ui8GetWrnLvlDHW();
      //tdebugTelStructPos->ucWT_Pmin = ui8GetWrnLvlPMin();
      //tdebugTelStructPos->ucWT_HW = ui8GetWrnLvlHard();
      //tdebugTelStructPos->ucWT_WW = ui8GetWrnLvlSoft();
      tdebugTelStructPos->ucEcuRFRSSI = ucTelAvgRSSI;
      //tdebugTelStructPos->ucEcuLoBatCnt = (GETtSensorBatInfOfRam(ucGetColOfID(&ulTelID))).ui8Count;
    }

    tDebugTelStruct.ucRecEvent = ucRecEvent;

    Rte_Call_PP_GetZomData_OP_GetZomPosOfID(ulTelID, &ucIDPosInZom);
    Rte_Call_PP_GetZomData_OP_GetZomStatisticTelCounter(ucIDPosInZom, &tDebutTelWallocStruct.ucZomStatTelCounter);
    tDebutTelWallocStruct.ucZomToothTelCtLearnBit = ucGetZomTelCtLearnBit(ucIDPosInZom);
    Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrLearnBit(ucIDPosInZom, &ucTemp1);
    Rte_Call_PP_GetZomData_OP_GetZomToothTelCtCorrNoLearnBit(ucIDPosInZom, &ucTemp2);
    tDebutTelWallocStruct.ucZomToothTelCtCorr = ((ucTemp1 + ucTemp2) < 0xFF) ? (ucTemp1 + ucTemp2) : 0xFF; //avoid overflow
    Rte_Call_PP_GetZomData_OP_GetZomToothTelCtrNoCorr(ucIDPosInZom, &tDebutTelWallocStruct.ucZomToothTelCtrNoCorr);
    ucTemp1 = tDebutTelWallocStruct.ucZomToothTelCtCorr;
    ucTemp2 = tDebutTelWallocStruct.ucZomToothTelCtrNoCorr;
    tDebutTelWallocStruct.ucZomToothTelCtNoLearnMode = (ucTelStatGetLastRxBlocs(ulTelID) > (ucTemp1 + ucTemp2)) ? (ucTelStatGetLastRxBlocs(ulTelID) - ucTemp1 - ucTemp2) : 0;
    Rte_Call_PP_GetZomData_OP_GetZomStatus(ucIDPosInZom, &tDebutTelWallocStruct.ucZomStatus); //ucGetZomStatus(ucIDPosInZom);

	  Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFL(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumFL);
	  Rte_Call_PP_GetZomData_OP_GetAbsSumCorrFR(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumFR);
	  Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRL(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumRL);
	  Rte_Call_PP_GetZomData_OP_GetAbsSumCorrRR(ucIDPosInZom, &tDebutTelWallocStruct.ushZomAbsSumRR);
	  /* Get interpolated ABS sticks*/

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

  //-----------------------------------------
	/* re init struc */
	for (i=0;i<sizeof(tDebugTelStruct);i++){
		*((uint8*)&tDebugTelStruct + i) = 0;
	}

}


boolean GETbCalPminInvalidCAL( void )
{
	return FALSE;
}

boolean GETbCalReqCAL( void )
{
  if((Rte_Pim_Pim_tCalNvMBlock()->ucCalRequestState & cCAL_MANUAL_ACTIV) !=0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

/* SOFT or HARD Reset: reconstruct content 4 BZ Bit "cCAL_MFD_PLAUS_ERROR" */
boolean GETbCalNotAck4PlausiCheckMFA( void )
{
	if((Rte_Pim_Pim_tCalNvMBlock()->ucCalNotAckState & 0x0F) == cCAL_VALID)
	{
       return FALSE; 
	}
	else
	{
       return TRUE; 
	}
}




void CheckDTCInactiveERR()
{
	//printf("\n Call CheckDTCInactiveERR");
}

void InitIDOM(void)
{
	//printf("\n Call InitIDOM");
}


/******************************************************************/
/*Start Variant Coding  [22/2E  02 A3] CR_1211_032_103            */
/**************** front axis FA - VA ******************************/
void PUTucPcalMinVaRelativCod2Ram(uint8 x) /*CRS_1211_130_268 */
{
  Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinVaRelativCod = (x);
  //Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinVaAbsCod = (x);
}


uint8 GETucPcalMinVaRelativCodOfRam(void) /*CRS_1211_130_268 */
{
  return Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinVaRelativCod;
	//return Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinVaAbsCod;
}


void PUTucPcalMinVaRelativCod2Nvm()/*CRS_1211_130_268 */
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}
/**************** rear axis RA - HA ******************************/
void PUTucPcalMinHaRelativCod2Ram(uint8 x)/*CRS_1211_130_268 */
{
  Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinHaRelativCod = (x);
	//Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinHaAbsCod = (x);
}

uint8 GETucPcalMinHaRelativCodOfRam(void)/*CRS_1211_130_268 */
{
  return Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinHaRelativCod;
	//return Rte_Pim_Pim_tCodNvMBlock()->ucPcalMinHaAbsCod;
}


void PUTucPcalMinHaRelativCod2Nvm()/*CRS_1211_130_268 */
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

/*End Variant Coding  [22/2E  02 A3] CR_1211_032_103 */
/***********************************************************************************************/
/***** 4x POS specific Compare Pressure 4 automatic calibration  *****/

uint8 GETucPosComparePressure(uint8 i) /*CRS_1211_130_252*/
{
  
  uint8 ui8ret = 0;

  if( i < cAnzRad )
  {
    ui8ret = ( *((uint8*)&Rte_Pim_Pim_tCalNvMBlock()->aucPosComparePressure + i) );
  }
  else
  {
    ui8ret = 0x00;
  }
	return ui8ret;

}

void PUTucPosComparePressure(uint8 x, uint8 i)  /*CRS_1211_130_252*/
{
  NvM_RequestResultType ErrorStatus;

  if( i < cAnzRad)
  {
    /* reset WU reception state */
    *((uint8*)&Rte_Pim_Pim_tCalNvMBlock()->aucPosComparePressure + i) = x;
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
    if (ErrorStatus  != NVM_REQ_PENDING)
    {
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE); /*Kl.15off->2NVM*/
    }
  }
}

//CRS_1211_130_249
//void PUTucPosComparePressureNVM()/*CRS_1211_130_077*/
//{
//  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_PosComparePressure_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_PosComparePressure());
//}

/***** 4x POS specific Compare Pressure 4 automatic calibration  *****/
/***********************************************************************************************/

void PUTulKmStand4AutoCAL(uint32 ulKmStand)
{
	ulKmStand4AutoCal= ulKmStand/10; /*CRS_1211_130_102*/
}

uint32 GETulKmStand4AutoCAL(void)
{
	return ulKmStand4AutoCal;
}

/* **********************************************************************************************/
/* FD: Last filling detection storage mileage value*/

void PUTulLastCalMileage(uint32 x)
{
  NvM_RequestResultType ErrorStatus;

  Rte_Pim_Pim_tCalNvMBlock()->ulLastCalMileage = (x);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_GetErrorStatus(&ErrorStatus); /* to avoid multi requests */
  if (ErrorStatus  != NVM_REQ_PENDING)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCalNvMBlock_SetRamBlockStatus(TRUE);/*Kl.15off->2NVM*/
  }
}

uint32 GETulLastCalMileage()
{
	return Rte_Pim_Pim_tCalNvMBlock()->ulLastCalMileage;
}
/* FD: Last filling detection storage mileage value*/
/* **********************************************************************************************/
/* FD: AverageFillTemperatur storage */

#ifdef FDasNewNVMdata

void PUTscAverageFillTemperatur(sint8 x)
{
	*(sint8*)Rte_Pim_Pim_AverageFillTemperatur() = (x);
}

void PUTscAverageFillTemperaturNVM(sint8 x)
{
	//Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_AverageFillTemperatur_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_AverageFillTemperatur()); 
}

sint8 GETscAverageFillTemperatur()
{
	//return *(sint8*)Rte_Pim_Pim_AverageFillTemperatur(); 
}

/* FD: AverageFillTemperatur storage */
/* **********************************************************************************************/


void PUTucPfillFront(uint8 ucP)
{
  //*(uint8*)Rte_Pim_Pim_PfillFront() = (ucP);
  //Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_PfillFront_SetRamBlockStatus(TRUE);  //@AS bitte Implementireung noch mal überprüfen
}

void PUTucPfillFront2NVM(void)/* CRS_1211_130_185 */
{
	//Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_PfillFront_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_PfillFront());  //@AS bitte Implementireung noch mal überprüfen
}

uint8 GETucPfillFront(void)
{
  return *(uint8*)Rte_Pim_Pim_PfillFront();
}

void PUTucTfillFront(sint8 scT)
{
  //*(sint8*)Rte_Pim_Pim_TfillVA() = (scT);
  //Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_TfillVA_SetRamBlockStatus(TRUE);  //@AS bitte Implementireung noch mal überprüfen
}

void PUTucTfillFront2NVM(void)/* CRS_1211_130_185 */
{
	//Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_TfillVA_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_TfillVA());  //@AS bitte Implementireung noch mal überprüfen
}


sint8 GETucTfillFront(void)
{
  //return *(sint8*)Rte_Pim_Pim_TfillVA();  //@AS bitte Implementireung noch mal überprüfen
}

void PUTucPfillRear(uint8 ucP)
{
  //*(uint8*)Rte_Pim_Pim_PfillRear() = (ucP);
 // Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_PfillRear_SetRamBlockStatus(TRUE);  //@AS bitte Implementireung noch mal überprüfen
}

void PUTucPfillRear2NVM(void)/* CRS_1211_130_185 */
{
	//Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_PfillRear_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_PfillRear());  //@AS bitte Implementireung noch mal überprüfen
}

uint8 GETucPfillRear(void)
{
  return *(uint8*)Rte_Pim_Pim_PfillRear();
}

void PUTucTfillRear(sint8 scT)
{
  //*(sint8*)Rte_Pim_Pim_TfillHA() = (scT);
  //Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_TfillHA_SetRamBlockStatus(TRUE);  //@AS bitte Implementireung noch mal überprüfen
}

void PUTucTfillRear2NVM(void)/* CRS_1211_130_185 */
{
	//Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_TfillHA_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_TfillHA()); //@AS bitte Implementireung noch mal überprüfen
}

sint8 GETucTfillRear(void)
{
  return *(sint8*)Rte_Pim_Pim_TfillHA();
}
#endif
/*-------------------------------------------------------------------------------------------------
** uint8 ucCheckLOW_PRESS_ReState(void)
**/
/*
** Description
**/
/*
** Purpose:             Kalibrierung: MANUAL and AUTO 1.Check warning?
**															HMI: TireStat_XX =LOW_PRESS (it's HW+Pmin)
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:              
**
** Output:             Result: TRUE/FALSE
** ------------------------------------------------------------------------------------------------
**/

uint8 ucCheckLOW_PRESS_ReState(void)
{
	uint8 ucRtn = FALSE;
		/*(MFA2:CRS_1211_130_214  CR_1211_130_053) Check HW or Pmin positionsspezifisch */
	 	/****** FL ***********/
		if(GETbWrnPMin_FL()) /* HW or Pmin FL? */
		{
			ucRtn+=cFD_Pmin_FL; /*0x01 M_Acalibration stopp*/
			/*ucRtn=TRUE; M_Acalibration stopp*/
		}
		/****** FR ***********/
    if(GETbWrnPMin_FR()) /* HW or Pmin FR? */
		{
			ucRtn+=cFD_Pmin_FR; /*0x02 M_Acalibration stopp*/
		}
		/****** RL ***********/
		if(GETbWrnPMin_RL()) /* HW or Pmin RL? */
		{
			ucRtn+=cFD_Pmin_RL; /*0x04 M_Acalibration stopp*/
		}
		/****** RR ***********/
 		if(GETbWrnPMin_RR()) /* HW or Pmin RR? */
		{
			ucRtn+=cFD_Pmin_RR; /*0x08 M_Acalibration stopp*/
		}
		if( GETbWrnPMin_UK())  /* HW or Pmin ? but position unknow!? */
		{
			ucRtn+=cFD_Pmin_UK; /* 0xF0 M_Acalibration stopp*/
		}
	return ucRtn;
}

/*-------------------------------------------------------------------------------------------------
** uint8 ucCheckAllRePcalMinDPmanualMFD(void)
**/
/*
** Description
**/
/*
** Purpose:             Kalibrierung: Plausibility Check 5.5.1 Minimum Pressure DP_MANUAL All RE's
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:              
**
** Output:             Result: TRUE/FALSE
** ------------------------------------------------------------------------------------------------
**/

uint8 ucCheckAllRePcalMinDPmanualMFD(void)
{
	
  uint8 ucColOfIdVL,ucColOfIdVR,ucColOfIdHL, ucColOfIdHR;  /* CRS_1211_130_338 */
	uint8 i;
	uint8 ucRtn=FALSE;

	for( i = 0; i < cAnzRad; i++ ) /*i=ZOMPOS*/
	{
		switch (GETucWPorPWPofHistCol(i)) /* CRS_1211_130_338 */
		{
			case cRadPosVL: 
						ucColOfIdVL=i; /*ZOM/COLpos of cRadPosVL*/
			break;
			case cRadPosVR: 
   					ucColOfIdVR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHL: 
						ucColOfIdHL=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			case cRadPosHR: 
  					ucColOfIdHR=i; /*ZOM/COLpos of cRadPosVR*/
			break;
			default:
			{
				ucRtn = TRUE;				
			}
		}
	}
	if(ucRtn == FALSE)
	{
		/*	CRS_1211_130_338 */
		if ( GETucStoragePaverege4CompareValue(ucColOfIdVL) < (GETucPcalMinVaRelativCodOfRam() - cDP_MANUAL)) /*CRS_1211_130_214logical data PAL: P_MIN_TIRE_4CAL  2,9bar!*/
		{
			ucRtn=TRUE; /*Abort manual filling detection*/
		}
		if ( GETucStoragePaverege4CompareValue(ucColOfIdVR) < (GETucPcalMinVaRelativCodOfRam() - cDP_MANUAL)) /*CRS_1211_130_2147 logical data PAL: P_MIN_TIRE_4CAL  2,9bar!*/
		{
			ucRtn=TRUE; /*Abort manual filling detection*/
		}
		if ( GETucStoragePaverege4CompareValue(ucColOfIdHL) < (GETucPcalMinHaRelativCodOfRam() - cDP_MANUAL)) /*CRS_1211_130_214 logical data PAL: P_MIN_TIRE_4CAL  2,9bar!*/
		{
			ucRtn=TRUE; /*Abort manual filling detection*/
		}
		if ( GETucStoragePaverege4CompareValue(ucColOfIdHR) < (GETucPcalMinHaRelativCodOfRam() - cDP_MANUAL)) /*CRS_1211_130_214 logical data PAL: P_MIN_TIRE_4CAL  2,9bar!*/
		{
			ucRtn=TRUE; /*Abort manual filling detection*/
		}
	}
	else /*KEINE DP_MANUAl Prüfung!!! */
	{
		ucRtn = FALSE;
	}
	return ucRtn;
}

/************************************************************************************************//**
 * \brief interface used by FD
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void ClearAllReCnt4FD(void)
{
  ucRErecCounter4FDVL=FALSE;
	ucRErecCounter4FDVR=FALSE;
	ucRErecCounter4FDHL=FALSE;
	ucRErecCounter4FDHR=FALSE;

}

/************************************************************************************************//**
 * \brief interface used by FD
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] TRUE or FALSE OLD: ucTmp4CalVL ucTmp4CalVR ucTmp4CalHL ucTmp4CalHR
 *
 * \return:  TRUE: RE[vl,vr,hl,hr] receive counter != zero (filling detection receive counter)
 * \return: FALSE: RE[vl,vr,hl,hr] receive counter == zero (filling detection receive counter)
 *
 *------------------------------------------------------------------------------------------------
 */
uint8 GetOneReCnt4FD(void)
{
  
uint8 ucRtn = FALSE;

	if(ucRErecCounter4FDVL != 0)
	{
		ucRtn=TRUE;
	}
	if(ucRErecCounter4FDVR != 0)
	{
		ucRtn=TRUE;
	}
	if(ucRErecCounter4FDHL != 0)
	{
		ucRtn=TRUE;
	}
	if(ucRErecCounter4FDHR != 0)
	{
		ucRtn=TRUE;
	}	
  return ucRtn;
}




/************************************************************************************************//**
 * \brief interface used by FD
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
			
uint8 GETucRErecCounter4FDVL(void)
{
	return ucRErecCounter4FDVL;
}

uint8 GETucRErecCounter4FDVR(void)
{
	return ucRErecCounter4FDVR;
}

uint8 GETucRErecCounter4FDHL(void)
{
	return ucRErecCounter4FDHL;
}

uint8 GETucRErecCounter4FDHR(void)
{
	return ucRErecCounter4FDHR;
}
/************************************************************************************************//**
 * \brief interface used by FD
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void PUTucRErecCounter4FDVL(uint8 x)
{
	ucRErecCounter4FDVL = x;
}

void PUTucRErecCounter4FDVR(uint8 x)
{
	ucRErecCounter4FDVR = x;
}
void PUTucRErecCounter4FDHL(uint8 x)
{
	ucRErecCounter4FDHL = x;
}
void PUTucRErecCounter4FDHR(uint8 x)
{
	ucRErecCounter4FDHR = x;
}

/************************************************************************************************//**
 * \brief interface used by FD
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void INCucRErecCounter4FDVL(void)
{
	ucRErecCounter4FDVL++;
}
void INCucRErecCounter4FDVR(void)
{
	ucRErecCounter4FDVR++;
}
void INCucRErecCounter4FDHL(void)
{
	ucRErecCounter4FDHL++;
}
void INCucRErecCounter4FDHR(void)
{
	ucRErecCounter4FDHR++;
}
/************************************************************************************************//**
 * \brief interface used by FD
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void PUTucTimer4MsgDispRq(uint8 x)
	{
  ucTimer4MsgDispRq = x;
	}
				
uint8 GETucTimer4MsgDispRq(void)
		{
	return ucTimer4MsgDispRq;
	}
			
void DECucTimer4MsgDispRq(void)
{
	if(ucTimer4MsgDispRq != 0)
	{
		ucTimer4MsgDispRq--;
	}

}

void PUTushFDtimeout(uint16 x)
{
	ushFDtimeout = x;
}

uint16 GETushFDtimeout(void)
{
	return ushFDtimeout;
	}

void DECushFDtimeout(void)
{
	if(ushFDtimeout != 0)
	{
		ushFDtimeout--;
	}

}
void PUTushSupervisoryTimerFD(uint16 x)
{
  ushSupervisoryTimerFD = x;
}

uint16 GETushSupervisoryTimerFD(void)
{
	return ushSupervisoryTimerFD;
}

void DECushSupervisoryTimerFD(void)
{
	if(ushSupervisoryTimerFD != 0)
	{
		ushSupervisoryTimerFD--;
	}
}


void PUTucOnceCheckMissingRE4FD(uint8 x)
	{
  ucOnceCheckMissingRE4FD = x;
}

uint8 GETucOnceCheckMissingRE4FD(void)
{
	return ucOnceCheckMissingRE4FD;
}

void PUTucFDtimerStop(uint8 x) /*CRS_1211_130_335 +340*/
{
	ucFDtimerStop = x;
}

uint16 GETucFDtimerStop(void) /*CRS_1211_130_335 +340*/
{
	return ucFDtimerStop;
	}



/*End Value 4 Kalibrierung  CR_1211_130_050 */
/* **********************************************************************************************/

/* **********************************************************************************************/
/*Start Variant Coding  [22/2E  02 A2] Measurement On Off CR_1211_032_102 */


void PUTucMeasurementState2Ram(uint8 x)
{
  //*(uint8*) Rte_Pim_Pim_MeasurementOnOffCod()= (x);

  Rte_Pim_Pim_tCodNvMBlock()->ucMeasurementOnOffCod = (x);
}
uint8 GETucMeasurementStateOfRam(void)
{
  //return (*(uint8*) Rte_Pim_Pim_MeasurementOnOffCod());
  return Rte_Pim_Pim_tCodNvMBlock()->ucMeasurementOnOffCod;
}

void PUTucMeasurementState2Nvm()
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTucMeasurementStateNvm2Ram()
{
   //Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_MeasurementOnOffCod_ReadBlock((const NvM_DestPtr*) Rte_Pim_Pim_MeasurementOnOffCod()); @@GL BugFixes 20151218
}

/*Ende Variant Coding  [22/2E  02 A2] Measurement On Off CR_1211_032_102 */
/* **********************************************************************************************/

/* **********************************************************************************************/
/*Start stored data  [22/2E  0271] CoastMode Control */

void PUTucCoastModeContCount2Ram(uint8 x)
{
  Rte_Pim_Pim_tCodNvMBlock()->ucCoastModeCtrlCount = x;
  //*(uint8*) Rte_Pim_Pim_CoastModeContCount()= (x);
}

uint8 GETucCoastModeContCountOfRam(void)
{
  /* number of ignition cycles for which Coastmode is bypassed */
  return Rte_Pim_Pim_tCodNvMBlock()->ucCoastModeCtrlCount;
  //return (*(uint8*) Rte_Pim_Pim_CoastModeContCount());
}

void PUTucCoastModeContCount2Nvm()
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

/*Ende stored data   [22/2E  0271] CoastMode Control */
/* **********************************************************************************************/


/* **********************************************************************************************/
/*Start Variant Coding  [22/2E  02 A4] TPM logical data PAL Read/Write CR_1211_032_104 */

/*@@AS Umsetzung wie tData2Warn.ucTxTrigger = (ucStatusField1&0xC0)>>6;*/
/*tLogicalDataPalCod.ucMinWarnThreshold    */
/*   ucMinWarnThreshold of type UInt8
*   ucAutoFillDetectionOnOff of type UInt8
*   ucT_Soft of type UInt8
*   ucPercent_Soft of type UInt8
*   ucT_Hard of type UInt8
*   ucPercent_Hard of type UInt8
*   ucTempWarnOnOff of type UInt8*/

void PUTucMinWarnThreshold2Ram(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod())= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucMinWarnThreshold = x;
}

uint8 GETucMinWarnThresholdOfRam()
{
  //return (*(uint8*) Rte_Pim_Pim_tLogicalDataPalCod());
  return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucMinWarnThreshold;
}

void PUTucAutoFillDetectionOnOff2Ram(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 1)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucAutoFillDetectionOnOff = x;
}
uint8 GETucAutoFillDetectionOnOffOfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 1) );
  return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucAutoFillDetectionOnOff;
}

void PUTucT_Soft2Ram(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 2)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Soft = x;
}
uint8 GETucT_SoftOfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 2) );
  return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Soft;
}

void PUTucPercent_Soft2Ram(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 3)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Soft = x;
}
uint8 GETucPercent_SoftOfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 3) );
  return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Soft;
}

void PUTucT_Hard2Ram(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 4)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Hard = x;
}
uint8 GETucT_HardOfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 4) );
  return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucT_Hard;
}

void PUTucPercent_Hard2Ram(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 5)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Hard = x;
}
uint8 GETucPercent_HardOfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 5) );
  return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucPercent_Hard;
}

void PUTucTempWarnOnOff2Ram(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 6)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucTempWarnOnOff = x;
}
uint8 GETucTempWarnOnOffOfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tLogicalDataPalCod() + 6) );
  return Rte_Pim_Pim_tCodNvMBlock()->tLogicalDataPalCod.ucTempWarnOnOff;
}



void PUTLogicalDataPalCod2Nvm()
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTLogicalDataPalCodNvm2Ram()
{
  //Rte_Call_PS_Rte_NvmBlock_CtApHufTPMSwnh_SnNvMPimLogicalDataPalCod_ReadBlock((const NvM_DestPtr*) Rte_Pim_Pim_tLogicalDataPalCod()); @@GL BugFixes 20151218
}

/*Ende Variant Coding  [22/2E  02 A4] Measurement On Off CR_1211_032_104 */
/* **********************************************************************************************/

/* **********************************************************************************************/
/*Start Variant Coding  [22/2E  02 A5] TPM TemperaturWarning Read/Write CR_1211_032_105 */

/*@@AS Umsetzung wie tData2Warn.ucTxTrigger = (ucStatusField1&0xC0)>>6;*/
/* DT_tParaTempWarnCod: Record with elements
*   ucV1 of type UInt8
*   ucV2 of type UInt8
*   ucV3 of type UInt8
*   ucT0 of type UInt8
*   ucT1 of type UInt8
*   ucT2 of type UInt8
*   ushHC_MAX of type UInt16*/

void PUTucV1ToRam(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tParaTempWarnCod())= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV1 = x;
}
uint8 GETucV1OfRam()
{
  //return (*(uint8*) Rte_Pim_Pim_tParaTempWarnCod());
  return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV1;
}

uint16 GETushV1()
{
  //return ((uint16)(*(uint8*) Rte_Pim_Pim_tParaTempWarnCod()));
  return (uint16) Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV1;
}


void PUTucV2ToRam(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 1)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV2 = x;
}
uint8 GETucV2OfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 1) );
  return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV2;
}

uint16 GETushV2()
{
  //return ((uint16) (*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 1) ));
  return (uint16) Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV2;
}
void PUTucV3ToRam(uint8 x)
{
  //*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 2)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV3 = x;
}
uint8 GETucV3OfRam()
{
  //return (*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 2) );
  return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV3;
}

uint16 GETushV3()
{
  //return ((uint16)(*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 2) ));
  return (uint16)Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ucV3;
}

/*(MFA2: CRS_1211_032_107) Temperatur value fot TempWarning -> datatype sint8!*/
void PUTscT0ToRam(sint8 x)
{
  //*((sint8*) Rte_Pim_Pim_tParaTempWarnCod() + 3)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT0 = x;
}
sint8 GETscT0OfRam()
{
  //return (*((sint8*) Rte_Pim_Pim_tParaTempWarnCod() + 3) );
  return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT0;
}
void PUTscT1ToRam(sint8 x)
{
  //*((sint8*) Rte_Pim_Pim_tParaTempWarnCod() + 4)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT1 = x;
}
sint8 GETscT1OfRam()
{
  //return (*((sint8*) Rte_Pim_Pim_tParaTempWarnCod() + 4) );
  return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT1;
}
void PUTscT2ToRam(sint8 x)
{
  //*((sint8*) Rte_Pim_Pim_tParaTempWarnCod() + 5)= (x);
  Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT2 = x;
}
sint8 GETscT2OfRam()
{
  //return (*((sint8*) Rte_Pim_Pim_tParaTempWarnCod() + 5) );
  return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.scT2;
}


void PUTushHCmaxToRam(uint8 x , uint8 y)
{

  //*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 6)= (y); /*intel Byte to word Ablage!!*/
  //*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 7)= (x); /*intel Byte to word Ablage!!*/
  Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX = (uint16)(x<<8) + (uint16)y; /*intel Byte to word Ablage!!*/

}

uint16 GETushHCmax()
{
  //uint16 ushHCmax;

  //ushHCmax=(*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 7) );
  //ushHCmax<<=8;
  //ushHCmax+=(*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 6) );
  return Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX;

  //return (ushHCmax);
}



uint8 GETucHCmaxOfRamHbyte()
{
  //return (*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 7) );
  return (uint8)(Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX>>8);
}


uint8 GETucHCmaxOfRamLbyte()
{
  //return (*((uint8*) Rte_Pim_Pim_tParaTempWarnCod() + 6) );
  return (uint8)(Rte_Pim_Pim_tCodNvMBlock()->tParaTempWarnCod.ushHC_MAX);
}

void PUTTempWarnCod2Nvm()
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

void PUTTempWarnCodNvm2Ram()
{
  //Rte_Call_PS_Rte_NvmBlock_CtApHufTPMSwnh_SnNvMPimParaTempWarnCod_ReadBlock((const NvM_DestPtr*) Rte_Pim_Pim_tParaTempWarnCod()); @@GL BugFixes 20151218
}


void PUTucKweight2Ram(uint8 x)
{
  //*(uint8*) Rte_Pim_Pim_ucKweight() = (x);
  Rte_Pim_Pim_tCodNvMBlock()->ucKweight = x;
}

void PUTucKweight2Nvm()
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

uint8 GETucKweightOfRam()
{
  uint8 Ret;

  //Ret = (*(uint8*) Rte_Pim_Pim_ucKweight());
  Ret = Rte_Pim_Pim_tCodNvMBlock()->ucKweight;
  if(Ret > 100) /* more than 100% is not possible */
  {
    Ret = 100;
  }

  return ( Ret );
}

void PUTucKweightNvm2Ram()
{
  /* ucKweight Initwert soll 0x1E sein */
  //Rte_Call_PS_Rte_NvmBlock_CtApHufTPMSwnh_Pim_ucKweight_ReadBlock((const NvM_DestPtr*) Rte_Pim_Pim_ucKweight()); @@GL BugFixes 20151218
}

//set the flag indicating whether of not new coding Data are available
void SetCodNvMBlockNewDataFlag(boolean bNewDataFlag)
{
  bWrCodNVMBlock = (boolean) bNewDataFlag;
}

//get the flag indicating whether of not new coding Data are available
boolean bGetCodNvMBlockNewDataFlag(void)
{
  return (boolean)bWrCodNVMBlock;
}

// synchr RAM data to the NVM. Function should be called cyclically
void AlignCodBlockRaM2NvM(void)
{
  NvM_RequestResultType ErrorStatus;
  if(bGetCodNvMBlockNewDataFlag() == TRUE)
  {
    Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_GetErrorStatus(&ErrorStatus);
    if (ErrorStatus  != NVM_REQ_PENDING)
    {
      Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_WriteBlock((const NvM_DestPtr*) Rte_Pim_Pim_tCodNvMBlock());
      SetCodNvMBlockNewDataFlag(FALSE);
    }
  }
}

void PUTucLqi2Ram(uint8 x)
{
  *((uint8*)&Rte_Pim_Pim_tCodNvMBlock()->tCodReserved + 0) = x;  /* take Byte 0 of reserved NVM space */
}

void PUTucLqi2Nvm(void)
{
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

uint8 GETucLqiOfRam(void){
  uint8 ui8Ret = 0;
  ui8Ret = *((uint8*)&Rte_Pim_Pim_tCodNvMBlock()->tCodReserved + 0);
  return ui8Ret;
}
  
/* **********************************************************************************************/
/*Start Function 4 Calibration CR_1211_130_XXX */



#if 0
/*-------------------------------------------------------------------------------------------------
** uint8 GetPabsLowestFromLastCAL(void)
**/
/*
** Description
**/
/*
** Purpose:             Sucht den niedrigsten Druck VA oder HA der letzten Kalibrierungn
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:              without
**
** Output:             Druckwert
** ------------------------------------------------------------------------------------------------
**/
uint8 GetPabsLowestFromLastCAL(void) // returns lowest absolut pressure from axis
 {
    
	uint8 ui8Plowest;
	/*TEST Average pressure*/ 
	ui8Plowest= GETucPosCalPressure(cRadPosVL); /* load ID Average pressure of all 3 received RE's and storage in PosCalPressure + Warnhandler */
	if(GETucPosCalPressure(cRadPosVR)< ui8Plowest)
	{
		ui8Plowest= GETucPosCalPressure(cRadPosVR);
	}

	if(GETucPosCalPressure(cRadPosHL)< ui8Plowest)
	{
		ui8Plowest= GETucPosCalPressure(cRadPosHL);
	}
	if(GETucPosCalPressure(cRadPosHR)< ui8Plowest)
	{
		ui8Plowest= GETucPosCalPressure(cRadPosHR);
	}
    return (ui8Plowest);
 }

/*-------------------------------------------------------------------------------------------------
** SetWalgo2PabsLowestFromLastCAL(void)
**/
/*
** Description
**/
/*
** Purpose:             Sucht den niedrigsten Druck VA oder HA und initialisiere den USWALGO
**                      
**
** ------------------------------------------------------------------------------------------------
** Input:              without
**
** Output:             without
** ------------------------------------------------------------------------------------------------
**/
void SetWalgo2PabsLowestFromLastCAL(void) // returns lowest absolut pressure from axis
{
    
	uint8 ui8Plowest;
	sint8 si8T;
	/*TEST Average pressure*/ 
	ui8Plowest= GETucPosCalPressure(cRadPosVL); /* load ID Average pressure of all 3 received RE's and storage in PosCalPressure + Warnhandler */
	si8T= GETscPosCalTemperatur(cRadPosVL); 
   
	if(GETucPosCalPressure(cRadPosVR)< ui8Plowest)
	{
		ui8Plowest= GETucPosCalPressure(cRadPosVR);
		si8T= GETscPosCalTemperatur(cRadPosVR); 
	}

	if(GETucPosCalPressure(cRadPosHL)< ui8Plowest)
	{
		ui8Plowest= GETucPosCalPressure(cRadPosHL);
		si8T= GETscPosCalTemperatur(cRadPosHL); 
	}
	if(GETucPosCalPressure(cRadPosHR)< ui8Plowest)
	{
		ui8Plowest= GETucPosCalPressure(cRadPosHR);
		si8T= GETscPosCalTemperatur(cRadPosHR); 
	}
 

	CfgReInitSingleUSWIF(ui8Plowest,si8T,cRadPosVL); /*Pabsmin +T 2  WarnAlgo*/
	CfgReInitSingleUSWIF(ui8Plowest,si8T,cRadPosVR); /*Pabsmin +T 2  WarnAlgo*/
	CfgReInitSingleUSWIF(ui8Plowest,si8T,cRadPosHL); /*Pabsmin +T 2  WarnAlgo*/
	CfgReInitSingleUSWIF(ui8Plowest,si8T,cRadPosHR); /*Pabsmin +T 2  WarnAlgo*/

	}
#endif 
/*End Function 4 Calibration CR_1211_130_XXX */
/* **********************************************************************************************/

/************************************************************************************************//**
 * \brief does telegram filtering for PAL2, only 1 from 3 Frames is forwarded
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ulID curent telegram ID
 * \param [in] ucFrameCounterRaw curent frame counter
 * \param [inout] aucFrameCounter Buffer containing all received telegrams
 *
 * \return ucRet 0x00 Passed 0x01 Failed
 *
 *------------------------------------------------------------------------------------------------
 */
uint8 ucPassPalFrameFilter(uint32 ulID, uint8 ucFrameCounterRaw )
{
  uint8 ucLastFrameCntr, ucColOfID, ucDiff, ucFrameCounter;
	uint8 ucIx,ucRet = 0;  // filter closed by default

  ucFrameCounter = (0x1F & ucFrameCounterRaw); // ucFrameCounter max value is 0x1F acc. to PAL spec

	if (ucFrameCounter != 0)
	{
		ucIx = ucGetZOMPosOfID((uint32 *) &ulID);

		if (ucIx < cSumWE)
		{
			if(ucFrameCounter != ucGetZOMPalFrameCounter(ucIx))
			{
				ucRet = 1;

        // update missed telegramm counter
        ucColOfID = ucGetColOfID (&ulID);
        if (ucColOfID < 4) // history ID??
        {
          ucLastFrameCntr = ucGetZOMPalFrameCounter(ucIx);
          ucDiff = (( ucFrameCounter>ucLastFrameCntr)? (ucFrameCounter-ucLastFrameCntr): (0x1F - ucLastFrameCntr + ucFrameCounter));
          ucDiff = ucDiff; // avoid warnings
          //aucEcuMissedCntr[ucColOfID] += (ucDiff-1);
        }
			}
		}
		else
		{
			ucRet = 1; 
			//aucFrameCounter[ucIx] = ucFrameCounter;
		}

	}
	return (ucRet);
}


/************************************************************************************************//**
 * \brief upsdate _CanM state according to the last clamb status
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
static void UpdateCanMState()
{
  ComM_ModeType ComMode;
  Dcm_SesCtrlType CurSession;
  EcuM_StateType  EcuM_State;            /* EcuM RUN mode state */

  Dcm_GetSesCtrlType( &CurSession);

  if((tEnvDataToSend.ucKlState==FALSE) && (CurSession==DCM_DEFAULT_SESSION))
  {/* shut dowm ECU after the stanby time ellapsed --> 20 min */
#if (ECU_SHUTDOWN_ENABLE) // not enable at the Pappenburg tests, because coast mode not fully tested
    Rte_Call_UR_ComMUser_HMI_GetCurrentComMode(&ComMode);
    if (ComMode != COMM_NO_COMMUNICATION )
    {
      Rte_Call_UR_ComMUser_HMI_RequestComMode(COMM_NO_COMMUNICATION);
    }
#endif
  }

  if(bStanbyTimerElapsed())
  {
   //CRS_1211_080_002 TimerWTinit(); stops SW and HW timer see TPMS logic 1.3 6.6.1 u. 2 "The Softwarning_Timer is also cleared by an ECU hard reset or at the end of Coast Mode before the ECU switches off."
  
    /* check EcuM state */
    (void)EcuM_GetState(&EcuM_State);
    if( EcuM_State == ECUM_STATE_APP_POST_RUN )
    {
      EcuM_ReleasePOST_RUN(EcuM_EcuMUserConfig_FirstUser);
    }
  }


}



/************************************************************************************************//**
 * \brief interface used by DCM
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void DcmFillingDetectionMFD(void)
{
  FillingDetectionMFD(TRUE); /* CRS_1211_130_312 START der MFD mit Ansteueren (TRUE) der RESTART(6) Anzeige!*/
}

/************************************************************************************************//**
 * \brief interface used  CRS_1211_032_121
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void ReplayLastREvalue2Walgo(void)
{

  DT_tData2Warn tData2Warn;	
  uint8 i;

  /* NACHLADEN der Druckwerte z.B. Pmin CRS_1211_130_176*/
  /* bei Neuinitialisierung an dieser Stelle werden Warnungen ausgegeben LOW PRESSURE*/
  for (i = 0; i < cMaxLR; i++)  /*CRS_1211_130_093 immediately update walgo all RE value */
  {
    if(ucGetLastReceivedPress(ulGetID(i)) != 0xFF) /* RE Missing??  control!*/
    {
      tData2Warn.ucP = ucGetLastReceivedPress(ulGetID(i));  /*CRS_1211_130_268 relativ pressure always*/
      tData2Warn.ucT = ucGetLastReceivedTemp(ulGetID(i));// + ucPalTempNormOFFSETc; /*CRS_1211_130_200*/
      tData2Warn.ucTxTrigger = 0x01;							/*alternativ*/
      tData2Warn.ulID = ulGetID(i);								/*this not necessarry, ID will never being consumed in walgo */
      tData2Warn.ucZomPos = i;
      Rte_Call_PP_Data2Warn_OP_SendTelData2WarnHdlr(&tData2Warn);
    }
  }
}


/************************************************************************************************//**
 * \brief count down clamp cycle for coast mode control
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 *
 *------------------------------------------------------------------------------------------------
 */
void CountCoastModeClampCycle(void)
{
  uint8 uctempClampCnt;

    uctempClampCnt = GETucCoastModeContCountOfRam();
    
    if(uctempClampCnt>0)
    {

      /* stanby mode: disabled: ECU asleep immediately after detected ignition off and the can bus falls asleep */
      SkipStanbyTimer();

      uctempClampCnt--;  /* count down each clamp cycle */

      PUTucCoastModeContCount2Ram( uctempClampCnt );

      PUTucCoastModeContCount2Nvm();
    }
    else
    {
      TPMS_NVM_ActivateWriteAll(); /* at coast mode, start NVM doing immediately */
    }
}



/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of function definition area >>              DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0777:  MISRA rule: 5.1
     Reason:     The defined RTE naming convention may result in identifiers with more than 31 characters. The compliance to this rule is under user's control.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       Ambiguous identifiers can lead to compiler errors / warnings.
     Prevention: Verified during compile time. If the compiler reports an error / warning. The user has to rename the objects to be unique within the significant characters.

   MD_Rte_0779:  MISRA rule: 5.1
     Reason:     The defined RTE naming convention may result in identifiers with more than 31 characters. The compliance to this rule is under user's control.
                 This is covered in the MISRA C compliance section of the Rte specification.
     Risk:       Ambiguous identifiers can lead to compiler errors / warnings.
     Prevention: Verified during compile time. If the compiler reports an error / warning. The user has to rename the objects to be unique within the significant characters.

*/
