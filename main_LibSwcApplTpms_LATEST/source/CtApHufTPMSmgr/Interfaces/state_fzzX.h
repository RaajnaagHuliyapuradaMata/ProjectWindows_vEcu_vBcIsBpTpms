#ifndef _state_fzz_X_H
#define _state_fzz_X_H

#define cKL_15_EIN            ((uint16) 0x0001)
#define cRS_VTHRES            ((uint16) 0x0002)
#define cFAHRZEUG_FAEHRT      ((uint16) 0x0004)
#define cRUECKWAERTSFAHRT     ((uint16) 0x0008)
#define cVEH_ABSSTICKS_MOVE   ((uint16) 0x0010)
#define cKFZFAEHRT_20KMH      ((uint16) 0x0020)
#define cKFZPARKING_START_AFD ((uint16) 0x0040)
#define cENG_STARTING         ((uint16) 0x0200)
#define cENG_RUNNING          ((uint16) 0x0400)
#define cFAILURE_MONITORING   ((uint16) 0x0800)

#define cTPMS433Mhz                  ((uint16) 0x1000)
#define cTPMS315Mhz                ((uint16) 0x2000)
#define cKL30_UNTERSPG            ((uint16) 0x4000)
#define cKL30_UEBERSPG            ((uint16) 0x8000)
#define cFZZ_ALLE_BITS        ((uint16) 0xffff)

#define cFZZ_WHLPLS_FL_IMPLAU     ((uint16) 0x0001)
#define cFZZ_WHLPLS_FR_IMPLAU     ((uint16) 0x0002)
#define cFZZ_WHLPLS_RL_IMPLAU     ((uint16) 0x0004)
#define cFZZ_WHLPLS_RR_IMPLAU     ((uint16) 0x0008)

#define cFZZ_TRACTION_SYSTEM_IMPLAU     ((uint16) 0x0010)
#define cFZZ_VEH_SPEED_IMPLAU           ((uint16) 0x0020)
#define cFZZ_AIRTEMP_OUT_IMPLAU         ((uint16) 0x0040)
#define cFZZ_IC_A3_TPM_ACTV_IMPLAU      ((uint16) 0x0080)
#define cALL_CAN_SIGNALS                ((uint16) 0xffff)

#define cFZZ_WHLPLS_CNT_TIMEOUT       ((uint16) 0x0001)
#define cFZZ_IGN_VEH_STAT_TIMEOUT     ((uint16) 0x0002)
#define cFZZ_ENG_CTRL_TIMEOUT         ((uint16) 0x0004)
#define cFZZ_PRESS_OUT_TIMEOUT        ((uint16) 0x0008)
#define cFZZ_PN14_STAT_TIMEOUT        ((uint16) 0x0010)
#define cFZZ_IC_BASIC_INFO_TIMEOUT    ((uint16) 0x0020)
#define cFZZ_IC_DATE_TIME_TIMEOUT     ((uint16) 0x0040)
#define cFZZ_IC_SETTINGS_TIMEOUT      ((uint16) 0x0080)
#define cFZZ_CANSM_BUSOFF_Network     ((uint16) 0x0100)

typedef enum HufEngStat
{
  cEngStat_STOPPED,
  cEngStat_STARTING,
  cEngStat_RUNNING,
}HufEngStat;

extern void InitFZZ( void );

extern void SetBitFahrzeugzustandFZZ( uint16 );
extern void ClearBitFahrzeugzustandFZZ( uint16 );
extern boolean bGetBitFahrzeugzustandFZZ( uint16 );
extern uint16 ushGetFahrzeugzustandFZZ( uint16 );

extern void EvTerminal15OnFZZ( void );
extern void EvTerminal15OffFZZ( void );

extern void EvVehicleRollingFZZ( void );
extern void EvVehicleSpeed4CalFZZ( void );
extern void EvVehicleStandsStillFZZ( void );
extern void EvVehicleNoSpeed4CalFZZ( void );

extern void EvKl30DiagUeberSpgFZZ( void );
extern void EvKl30DiagNoUeberSpgFZZ( void );

extern void EvKl30DiagUnterSpgFZZ( void );
extern void EvKl30DiagNoUnterSpgFZZ( void );

extern void EvTPMS433MhzFZZ( void );
extern void EvTPMS315MhzFZZ( void );

extern void EvReDiagActiveFZZ( void );
extern void EvReDiagInactiveFZZ( void );

extern void EvEngineRunningFZZ( void );
extern void EvEngineStopedFZZ( void );
extern void EvEngineStartingFZZ(void);

extern void EvDriveDirectionForwardFZZ( void );
extern void EvDriveDirectionBackwardFZZ( void );

extern uint32 GETulKilometersFZZ( void );
extern uint32 GETulSysTimeFZZ( void );
extern sint8 GETscOutdoorTemperatureFZZ( void );
extern uint16 GETushSpeedFZZ( void );

extern uint8 ucGetEcuStopCntr(void);
extern void SendEnvData2VehStateMgr(uint8*);
extern void UpdateFzzCurrentLearnMode(void);
extern void UpdateFzzDTcEnableCond(void);
extern uint8 ucGetFzzCurrentLearnMode(void);

extern void ClearFzzSignalUnplausibleState(uint16);
extern void ClearFzzSignalUnplausibleCntr(uint16 ushBitMask);
extern boolean bGetFzzSignalEnableDtcSetCond(uint16);
extern void SetFzzSignalImplauState(uint16);
extern void InitFzzignalMonitor(void);
extern boolean bGetFzzEnableImplauDtcInstruCluster(void);
extern void ClearFzzSignalTimeOutState(uint16 ushBitMask);
extern void SetFzzSignalTimeOutState(uint16 ushBitMask);
extern boolean bGetFzzCanSignalImplausibleState(uint16 ushBitMask);
  uint8  bGetABSSignalDTCActive(void);

uint8  bGetKl30HighDTCActive(void);
uint8  bGetKl30LowDTCActive(void);
uint8  bGetPN14SupbatHighDTCActive(void);
uint8  bGetPN14SupbatLowDTCActive(void);

extern void SetFzzState4MM(uint8 state);
extern uint8 GetFzzState4MM(void);
extern void SetGlobWarnState4MM(uint8 state);
extern uint8 GetGlobWarnState4MM(void);

#endif

