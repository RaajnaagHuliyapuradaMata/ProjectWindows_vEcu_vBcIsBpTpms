#pragma once
/******************************************************************************/
/* File              : infRteSwcApplTpms_HmiHandler.hpp                       */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "infSwcApplTpmsSMRte.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
/* state_bz_X.h */
#define cER_FINISH            ((uint16) 0x0001)
#define cBZ_Frei0             ((uint16) 0x0002)
#define cAL_RUNNING           ((uint16) 0x0004)
#define cEIGENRAD             ((uint16) 0x0008)
#define cZUGEORDNET           ((uint16) 0x0010)
#define cZO_Fallback2Hist     ((uint16) 0x0020)
#define cHIST_PRELOAD         ((uint16) 0x0040)
#define cZO_FINISH            ((uint16) 0x0080)
#define cCAL_REQUEST          ((uint16) 0x0100)
#define cCAL_MFD_PLAUSI_ERROR ((uint16) 0x0200)
#define cCAL_AFD_PLAUSI_ERROR ((uint16) 0x0400)
#define cDTC_INACTIVE         ((uint16) 0x0800)
#define cZO_TIMEOUT           ((uint16) 0x1000)
#define cZO_ERROR             ((uint16) 0x2000)
#define cTEILZUGEORDNET       ((uint16) 0x4000)
#define cCAL_FINISH           ((uint16) 0x8000)
#define cBZ_ALLE_BITS         ((uint16) 0xffff)
extern boolean bGetBitBetriebszustandBZ(uint16 ushBitMask);

/* state_fzzX.h */
#define cKL_15_EIN            ((uint16) 0x0001)
#define cRS_VTHRES            ((uint16) 0x0002)
extern boolean bGetBitFahrzeugzustandFZZ(uint16 ushBitMask);

/* TEL_STATISTIC_X.h */
#define FAILURE_MODE_ok             0U
#define FAILURE_MODE_soWE           1U
#define FAILURE_MODE_noWE           2U
#define FAILURE_MODE_RfInterference 3U
extern uint8   ucGetFailureState      (void);
extern boolean bCheckHistIDReception1 (void);
extern boolean bGetSensorStateMissing (uint8  ucColOfID);
extern uint8   ucGetLastReceivedPress (uint32 ulTelID);
extern uint8   ucGetLastReceivedTemp  (uint32 ulTelID);

#define cHiStateTZG ((uint8) 0x04)
#define cHiStateZG  ((uint8) 0x02)
#define cHiStateER  ((uint8) 0x01)

#define cAL_OK      ((uint8) 100)
#define cAL_Stored  ((uint8)   1)
#define cAL_Unknown ((uint8)   2)
#define cAL_Error   ((uint8)   3)
extern uint8         ui8GetALState      (void);
extern uint8 USEui8PWPofHistCol (uint8 ui8HistCol);
extern unsigned long ulGetID            (uint8 ucIx);
extern uint8 ucGetColOfWP       (uint8 ucIx);
extern uint8 ucGetWPOfCol       (uint8 ucIx);

/* TSSMsg.c */
extern uint8 GetucTPM_WarnDisp_Rq(void);

/* tss_stdx.h */
#define cRadPosVL ((uint8) 0)
#define cRadPosVR ((uint8) 1)
#define cRadPosHL ((uint8) 2)
#define cRadPosHR ((uint8) 3)

/* DAG_TVWarn.c */
extern uint8 ui8OvrHeatWrnIsActive (void);
extern uint8 ui8GetTempColeurWP_FL (void);
extern uint8 ui8GetTempColeurWP_FR (void);
extern uint8 ui8GetTempColeurWP_RL (void);
extern uint8 ui8GetTempColeurWP_RR (void);

/* filling_detection.h */
extern uint8 GETucMinWarnThresholdOfRam(void);

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
typedef uint16 UInt16;
#define UInt16_LowerLimit (    0U)
#define UInt16_UpperLimit (65535U)
#define RTE_E_OK          (    0U)
#define RTE_E_INVALID     (    1U)
FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETucHiWarnstatus1WN_Operation(P2VAR(UInt16, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ushWarnOUtTM);
#define Rte_Call_PP_GetWarningVectors_OP_GETushWarnstatus1WN(arg1) /*(*/RCtApHufTPMSwnh_GETucHiWarnstatus1WN_Operation(arg1)/*, ((Std_ReturnType)RTE_E_OK))*/

typedef uint8 UInt8;
#define UInt8_LowerLimit (  0U)
#define UInt8_UpperLimit (255U)
FUNC(void, RTE_CTAPHUFTPMSWNH_APPL_CODE) RCtApHufTPMSwnh_GETaucWheelPosWarn_Operation(UInt8 pos, P2VAR(UInt8, AUTOMATIC, RTE_CTAPHUFTPMSWNH_APPL_VAR) ucWheelPosWarn);
#define Rte_Call_PP_GetWarningVectors_OP_GETaucWheelPosWarn(arg1, arg2) /*(*/RCtApHufTPMSwnh_GETaucWheelPosWarn_Operation(arg1, arg2)/*, ((Std_ReturnType)RTE_E_OK))*/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint8 c08_kPa_0_632d5_2d5;
#define c08_kPa_0_632d5_2d5_LowerLimit                                    (  0U)
#define c08_kPa_0_632d5_2d5_UpperLimit                                    (255U)
#define Rte_InvalidValue_c08_kPa_0_632d5_2d5                              (255U)
#define InvalidValue_c08_kPa_0_632d5_2d5                                  (255U)
#ifndef I_C08_KPA_0_632D5_2D5_NO_IND
#define I_C08_KPA_0_632D5_2D5_NO_IND                                      (254U)
#endif
#ifndef I_C08_KPA_0_632D5_2D5_SNA
#define I_C08_KPA_0_632D5_2D5_SNA                                         (255U)
#endif

typedef uint8   c08_CRC_woSNA;
typedef uint8   Rsrv02;
typedef uint8   c04_0_15_1_SNA_na;
typedef boolean DC_BOOL;

typedef uint8 c02_Tire_Stat;
#define c02_Tire_Stat_LowerLimit                                            (0U)
#define c02_Tire_Stat_UpperLimit                                            (3U)
#ifndef I_C02_TIRE_STAT_NORMAL
#define I_C02_TIRE_STAT_NORMAL                                              (0U)
#endif
#ifndef I_C02_TIRE_STAT_SOFT_WARN
#define I_C02_TIRE_STAT_SOFT_WARN                                           (1U)
#endif
#ifndef I_C02_TIRE_STAT_LOW_PRESS
#define I_C02_TIRE_STAT_LOW_PRESS                                           (2U)
#endif
#ifndef I_C02_TIRE_STAT_DEFLATION
#define I_C02_TIRE_STAT_DEFLATION                                           (3U)
#endif

typedef uint8 c04_TPM_MsgDisp_Rq;
#define c04_TPM_MsgDisp_Rq_LowerLimit                                      ( 0U)
#define c04_TPM_MsgDisp_Rq_UpperLimit                                      (15U)
#define Rte_InvalidValue_c04_TPM_MsgDisp_Rq                                (15U)
#define InvalidValue_c04_TPM_MsgDisp_Rq                                    (15U)
#ifndef I_C04_TPM_MSGDISP_RQ_NO_MESS
#define I_C04_TPM_MSGDISP_RQ_NO_MESS                                       ( 0U)
#endif
#ifndef I_C04_TPM_MSGDISP_RQ_UNPLAUSIBLE
#define I_C04_TPM_MSGDISP_RQ_UNPLAUSIBLE                                   ( 1U)
#endif
#ifndef I_C04_TPM_MSGDISP_RQ_NO_SENSORS
#define I_C04_TPM_MSGDISP_RQ_NO_SENSORS                                    ( 2U)
#endif
#ifndef I_C04_TPM_MSGDISP_RQ_ERROR
#define I_C04_TPM_MSGDISP_RQ_ERROR                                         ( 3U)
#endif
#ifndef I_C04_TPM_MSGDISP_RQ_TNA
#define I_C04_TPM_MSGDISP_RQ_TNA                                           ( 4U)
#endif
#ifndef I_C04_TPM_MSGDISP_RQ_WE_MISS
#define I_C04_TPM_MSGDISP_RQ_WE_MISS                                       ( 5U)
#endif
#ifndef I_C04_TPM_MSGDISP_RQ_RESTART
#define I_C04_TPM_MSGDISP_RQ_RESTART                                       ( 6U)
#endif
#ifndef I_C04_TPM_MSGDISP_RQ_SNA
#define I_C04_TPM_MSGDISP_RQ_SNA                                           (15U)
#endif

typedef uint8 c03_TPM_Stat;
#define c03_TPM_Stat_LowerLimit                                             (0U)
#define c03_TPM_Stat_UpperLimit                                             (7U)
#define Rte_InvalidValue_c03_TPM_Stat                                       (7U)
#define InvalidValue_c03_TPM_Stat                                           (7U)
#ifndef I_C03_TPM_STAT_ACTIVE
#define I_C03_TPM_STAT_ACTIVE                                               (0U)
#endif
#ifndef I_C03_TPM_STAT_WAIT
#define I_C03_TPM_STAT_WAIT                                                 (1U)
#endif
#ifndef I_C03_TPM_STAT_ERROR
#define I_C03_TPM_STAT_ERROR                                                (2U)
#endif
#ifndef I_C03_TPM_STAT_NO_SENSORS
#define I_C03_TPM_STAT_NO_SENSORS                                           (3U)
#endif
#ifndef I_C03_TPM_STAT_SNA
#define I_C03_TPM_STAT_SNA                                                  (7U)
#endif

typedef uint8 c03_TPM_WarnDisp_Rq;
#define c03_TPM_WarnDisp_Rq_LowerLimit                                      (0U)
#define c03_TPM_WarnDisp_Rq_UpperLimit                                      (7U)
#define Rte_InvalidValue_c03_TPM_WarnDisp_Rq                                (7U)
#define InvalidValue_c03_TPM_WarnDisp_Rq                                    (7U)
#ifndef I_C03_TPM_WARNDISP_RQ_NO_WARN
#define I_C03_TPM_WARNDISP_RQ_NO_WARN                                       (0U)
#endif
#ifndef I_C03_TPM_WARNDISP_RQ_SOFT
#define I_C03_TPM_WARNDISP_RQ_SOFT                                          (1U)
#endif
#ifndef I_C03_TPM_WARNDISP_RQ_LOW_P
#define I_C03_TPM_WARNDISP_RQ_LOW_P                                         (2U)
#endif
#ifndef I_C03_TPM_WARNDISP_RQ_FAST
#define I_C03_TPM_WARNDISP_RQ_FAST                                          (3U)
#endif
#ifndef I_C03_TPM_WARNDISP_RQ_SNA
#define I_C03_TPM_WARNDISP_RQ_SNA                                           (7U)
#endif

typedef uint8 c02_Tire_Temp;
#define c02_Tire_Temp_LowerLimit                                            (0U)
#define c02_Tire_Temp_UpperLimit                                            (3U)
#define Rte_InvalidValue_c02_Tire_Temp                                      (3U)
#define InvalidValue_c02_Tire_Temp                                          (3U)
#ifndef I_C02_TIRE_TEMP_NORMAL
#define I_C02_TIRE_TEMP_NORMAL                                              (0U)
#endif
#ifndef I_C02_TIRE_TEMP_WARM
#define I_C02_TIRE_TEMP_WARM                                                (1U)
#endif
#ifndef I_C02_TIRE_TEMP_HOT
#define I_C02_TIRE_TEMP_HOT                                                 (2U)
#endif
#ifndef I_C02_TIRE_TEMP_SNA
#define I_C02_TIRE_TEMP_SNA                                                 (3U)
#endif

typedef uint8 c03_Tire_Temp_WarnDisp;
#define c03_Tire_Temp_WarnDisp_LowerLimit                                   (0U)
#define c03_Tire_Temp_WarnDisp_UpperLimit                                   (7U)
#define Rte_InvalidValue_c03_Tire_Temp_WarnDisp                             (7U)
#define InvalidValue_c03_Tire_Temp_WarnDisp                                 (7U)
#ifndef I_C03_TIRE_TEMP_WARNDISP_NO_MESS
#define I_C03_TIRE_TEMP_WARNDISP_NO_MESS                                    (0U)
#endif
#ifndef I_C03_TIRE_TEMP_WARNDISP_OVERHEAT
#define I_C03_TIRE_TEMP_WARNDISP_OVERHEAT                                   (1U)
#endif
#ifndef I_C03_TIRE_TEMP_WARNDISP_REDUCE_SPEED
#define I_C03_TIRE_TEMP_WARNDISP_REDUCE_SPEED                               (2U)
#endif
#ifndef I_C03_TIRE_TEMP_WARNDISP_SNA
#define I_C03_TIRE_TEMP_WARNDISP_SNA                                        (7U)
#endif

typedef uint8 c08_degC_m50_204_1;
#define c08_degC_m50_204_1_LowerLimit                                     (  0U)
#define c08_degC_m50_204_1_UpperLimit                                     (255U)
#define Rte_InvalidValue_c08_degC_m50_204_1                               (255U)
#define InvalidValue_c08_degC_m50_204_1                                   (255U)
#ifndef I_C08_DEGC_M50_204_1_SNA
#define I_C08_DEGC_M50_204_1_SNA                                          (255U)
#endif

typedef uint8 c08_WakeupRsn_TPM;
#define c08_WakeupRsn_TPM_LowerLimit                                      (  0U)
#define c08_WakeupRsn_TPM_UpperLimit                                      (255U)
#define Rte_InvalidValue_c08_WakeupRsn_TPM                                (255U)
#define InvalidValue_c08_WakeupRsn_TPM                                    (255U)
#ifndef I_C08_WAKEUPRSN_TPM_NETWORK
#define I_C08_WAKEUPRSN_TPM_NETWORK                                       (  0U)
#endif
#ifndef I_C08_WAKEUPRSN_TPM_SNA
#define I_C08_WAKEUPRSN_TPM_SNA                                           (255U)
#endif

typedef struct{
   c08_kPa_0_632d5_2d5 RefPress_Front;
   c08_kPa_0_632d5_2d5 RefPress_Rear;
}REC_RefPress;

typedef struct{
   c08_CRC_woSNA     CRC_TPM_Lmp_On_Rq_Pr2;
   Rsrv02            Rsrv1_TPM_Lmp_On_Rq_Pr2;
   c04_0_15_1_SNA_na SQC_TPM_Lmp_On_Rq_Pr2;
   DC_BOOL           TPM_IndLmp_On_Rq;
   DC_BOOL           TPM_MalfLmp_On_Rq;
}REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt;

typedef struct{
   DC_BOOL TPM_IndLmp_On_Rq_old;
   DC_BOOL TPM_MalfLmp_On_Rq_old;
}REC_TPM_Lmp_On_Rq_old;

typedef struct{
   DC_BOOL             Press_Disp_Avl;
   c08_kPa_0_632d5_2d5 TirePress_FL;
   c08_kPa_0_632d5_2d5 TirePress_FR;
   c08_kPa_0_632d5_2d5 TirePress_RL;
   c08_kPa_0_632d5_2d5 TirePress_RR;
   c02_Tire_Stat       TireStat_FL;
   c02_Tire_Stat       TireStat_FR;
   c02_Tire_Stat       TireStat_RL;
   c02_Tire_Stat       TireStat_RR;
   c04_TPM_MsgDisp_Rq  TPM_MsgDisp_Rq;
   c03_TPM_Stat        TPM_Stat;
   c03_TPM_WarnDisp_Rq TPM_WarnDisp_Rq;
}REC_Tire_Stat_V2;

typedef struct{
   c02_Tire_Temp          Tire_Temp_Stat_FL;
   c02_Tire_Temp          Tire_Temp_Stat_FR;
   c02_Tire_Temp          Tire_Temp_Stat_RL;
   c02_Tire_Temp          Tire_Temp_Stat_RR;
   c03_Tire_Temp_WarnDisp Tire_Temp_WarnDisp_Rq;
   c08_degC_m50_204_1     TireTemp_FL;
   c08_degC_m50_204_1     TireTemp_FR;
   c08_degC_m50_204_1     TireTemp_RL;
   c08_degC_m50_204_1     TireTemp_RR;
}REC_Tire_Temp_V2;

/* DCM */
typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_SesCtrlType;
#define DCM_DEFAULT_SESSION                                          0x01u
#define DCM_PROGRAMMING_SESSION                                      0x02u
#define DCM_EXTENDED_DIAGNOSTIC_SESSION                              0x03u
#define DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION                         0x04u
#define HUF_TEST_LOAD                                                0x60u
#define DCM_ALL_SESSION_LEVEL                                        0xFFu

/* DEM */
#define Dem_DEM_IND_SC8_RELEVANT 0
#define Dem_DEM_IND_MALFLAMP     1
#define Dem_DEM_IND_ECUFAILURE   2
typedef uint16 Dem_EventIdType;
typedef uint8  Dem_IndicatorIdType;
typedef uint8  Dem_IndicatorStatusType;

/* ECUM */
#define ECUM_GEN_SHUTDOWN_TARGET_PORT /*<ECUM_GEN_SHUTDOWN_TARGET_PORT/>*/ (STD_OFF)
#define ECUM_GEN_STATE_REQUEST_PORT   /*<ECUM_GEN_STATE_REQUEST_PORT/>  */ (STD_OFF)
#if((ECUM_GEN_SHUTDOWN_TARGET_PORT == STD_OFF) && (ECUM_GEN_STATE_REQUEST_PORT == STD_OFF))
typedef uint8 EcuM_StateType;
#define ECUM_SUBSTATE_MASK                                          (0x0Fu)
#define ECUM_STATE_STARTUP                                          (0x10u)
#define ECUM_STATE_STARTUP_ONE                                      (0x11u)
#define ECUM_STATE_STARTUP_TWO                                      (0x12u)
#define ECUM_STATE_WAKEUP                                           (0x20u)
#define ECUM_STATE_WAKEUP_ONE                                       (0x21u)
#define ECUM_STATE_WAKEUP_VALIDATION                                (0x22u)
#define ECUM_STATE_WAKEUP_REACTION                                  (0x23u)
#define ECUM_STATE_WAKEUP_TWO                                       (0x24u)
#define ECUM_STATE_WAKEUP_WAKESLEEP                                 (0x25u)
#define ECUM_STATE_WAKEUP_TTII                                      (0x26u)
#define ECUM_STATE_RUN                                              (0x30u)
#define ECUM_STATE_APP_RUN                                          (0x32u)
#define ECUM_STATE_APP_POST_RUN                                     (0x33u)
#define ECUM_STATE_SHUTDOWN                                         (0x40u)
#define ECUM_STATE_PREP_SHUTDOWN                                    (0x44u)
#define ECUM_STATE_GO_SLEEP                                         (0x49u)
#define ECUM_STATE_GO_OFF_ONE                                       (0x4Du)
#define ECUM_STATE_GO_OFF_TWO                                       (0x4Eu)
#define ECUM_STATE_SLEEP                                            (0x50u)
#define ECUM_STATE_RESET                                            (0x90u)
#define ECUM_STATE_OFF                                              (0x80u)
#define ECUM_STATE_ERROR                                            (0xFFu)
#endif

/* Nm / Com */
typedef enum{
      NM_STATE_UNINIT                = 0u
   ,  NM_STATE_BUS_SLEEP             = 1u
   ,  NM_STATE_PREPARE_BUS_SLEEP     = 2u
   ,  NM_STATE_READY_SLEEP           = 3u
   ,  NM_STATE_NORMAL_OPERATION      = 4u
   ,  NM_STATE_REPEAT_MESSAGE        = 5u
   ,  NM_STATE_SYNCHRONIZE           = 6u
   ,  NM_STATE_WAIT_CHECK_ACTIVATION = 7u
   ,  NM_STATE_WAIT_NETWORK_STARTUP  = 8u
   ,  NM_STATE_BUS_OFF               = 9u
}Nm_StateType;
typedef enum{
      NM_MODE_BUS_SLEEP         = 0u
   ,  NM_MODE_PREPARE_BUS_SLEEP = 1u
   ,  NM_MODE_SYNCHRONIZE       = 2u
   ,  NM_MODE_NETWORK           = 3u
}Nm_ModeType;
typedef uint8 Nm_ReturnType;
typedef uint8 NetworkHandleType;
extern FUNC(Nm_ReturnType, NM_CODE) Nm_GetState(CONST(NetworkHandleType, AUTOMATIC) nmChannelHandle, CONSTP2VAR(Nm_StateType, AUTOMATIC, NM_APPL_VAR) nmStatePtr, CONSTP2VAR(Nm_ModeType, AUTOMATIC, NM_APPL_VAR) nmModePtr);

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

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

