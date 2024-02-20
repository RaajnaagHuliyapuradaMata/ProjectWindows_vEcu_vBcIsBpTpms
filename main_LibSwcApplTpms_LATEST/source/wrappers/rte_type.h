

#ifndef _RTE_TYPE_H
# define _RTE_TYPE_H

# include "Rte.h"

# define Rte_TypeDef_Boolean
typedef boolean Boolean;

# define Rte_TypeDef_ComM_InhibitionStatusType
typedef uint8 ComM_InhibitionStatusType;
# define ComM_InhibitionStatusType_LowerLimit (0U)
# define ComM_InhibitionStatusType_UpperLimit (0U)

# define Rte_TypeDef_ComM_NetworkHandleType
typedef uint8 ComM_NetworkHandleType;
# define ComM_NetworkHandleType_LowerLimit (0U)
# define ComM_NetworkHandleType_UpperLimit (255U)

# define Rte_TypeDef_ComM_UserHandleType
typedef uint8 ComM_UserHandleType;
# define ComM_UserHandleType_LowerLimit (0U)
# define ComM_UserHandleType_UpperLimit (255U)

# define Rte_TypeDef_DC_BOOL
typedef boolean DC_BOOL;

# define Rte_TypeDef_DC_U16
typedef uint16 DC_U16;
# define DC_U16_LowerLimit (0U)
# define DC_U16_UpperLimit (65535U)

# define Rte_TypeDef_DC_U32
typedef uint32 DC_U32;
# define DC_U32_LowerLimit (0U)
# define DC_U32_UpperLimit (4294967295U)

# define Rte_TypeDef_DC_U8
typedef uint8 DC_U8;
# define DC_U8_LowerLimit (0U)
# define DC_U8_UpperLimit (255U)

# define Rte_TypeDef_DT_ucKweight
typedef uint8 DT_ucKweight;
# define DT_ucKweight_LowerLimit (0U)
# define DT_ucKweight_UpperLimit (255U)

# define Rte_TypeDef_DT_ucPosOfID
typedef uint8 DT_ucPosOfID;
# define DT_ucPosOfID_LowerLimit (0U)
# define DT_ucPosOfID_UpperLimit (255U)

# define Rte_TypeDef_DT_ulID
typedef uint32 DT_ulID;
# define DT_ulID_LowerLimit (0U)
# define DT_ulID_UpperLimit (4294967295U)

# define Rte_TypeDef_DT_ushWAState
typedef uint16 DT_ushWAState;
# define DT_ushWAState_LowerLimit (0U)
# define DT_ushWAState_UpperLimit (65535U)

# define Rte_TypeDef_DT_ushWarnOut
typedef uint16 DT_ushWarnOut;
# define DT_ushWarnOut_LowerLimit (0U)
# define DT_ushWarnOut_UpperLimit (65535U)

# define Rte_TypeDef_NvM_BlockIdType
typedef uint16 NvM_BlockIdType;
# define NvM_BlockIdType_LowerLimit (1U)
# define NvM_BlockIdType_UpperLimit (32767U)

# define Rte_TypeDef_Rsrv02
typedef uint8 Rsrv02;
# define Rsrv02_LowerLimit (0U)
# define Rsrv02_UpperLimit (3U)

# define Rte_TypeDef_Rsrv04
typedef uint8 Rsrv04;
# define Rsrv04_LowerLimit (0U)
# define Rsrv04_UpperLimit (15U)

# define Rte_TypeDef_Rsrv08
typedef uint8 Rsrv08;
# define Rsrv08_LowerLimit (0U)
# define Rsrv08_UpperLimit (255U)

# define Rte_TypeDef_SInt8
typedef sint8 SInt8;
# define SInt8_LowerLimit (-128)
# define SInt8_UpperLimit (127)

# define Rte_TypeDef_UInt16
typedef uint16 UInt16;
# define UInt16_LowerLimit (0U)
# define UInt16_UpperLimit (65535U)

# define Rte_TypeDef_UInt32
typedef uint32 UInt32;
# define UInt32_LowerLimit (0U)
# define UInt32_UpperLimit (4294967295U)

# define Rte_TypeDef_UInt8
typedef uint8 UInt8;
# define UInt8_LowerLimit (0U)
# define UInt8_UpperLimit (255U)

# define Rte_TypeDef_c04_0_15_1_SNA_na
typedef uint8 c04_0_15_1_SNA_na;
# define c04_0_15_1_SNA_na_LowerLimit (0U)
# define c04_0_15_1_SNA_na_UpperLimit (15U)

# define Rte_TypeDef_c08_0_255_1_SNA_na
typedef uint8 c08_0_255_1_SNA_na;
# define c08_0_255_1_SNA_na_LowerLimit (0U)
# define c08_0_255_1_SNA_na_UpperLimit (255U)

# define Rte_TypeDef_c08_CRC_woSNA
typedef uint8 c08_CRC_woSNA;
# define c08_CRC_woSNA_LowerLimit (0U)
# define c08_CRC_woSNA_UpperLimit (255U)

# define Rte_TypeDef_c08_UInt_SNA_na
typedef uint8 c08_UInt_SNA_na;
# define c08_UInt_SNA_na_LowerLimit (0U)
# define c08_UInt_SNA_na_UpperLimit (255U)

# define Rte_TypeDef_c24_0_16777215_1_SNA_na
typedef uint32 c24_0_16777215_1_SNA_na;
# define c24_0_16777215_1_SNA_na_LowerLimit (0U)
# define c24_0_16777215_1_SNA_na_UpperLimit (16777215U)

# define Rte_TypeDef_c32_0_4294967295_1_SNA_na
typedef uint32 c32_0_4294967295_1_SNA_na;
# define c32_0_4294967295_1_SNA_na_LowerLimit (0U)
# define c32_0_4294967295_1_SNA_na_UpperLimit (4294967295U)

# define Rte_TypeDef_ComM_ModeType
typedef uint8 ComM_ModeType;
# define ComM_ModeType_LowerLimit (0U)
# define ComM_ModeType_UpperLimit (2U)
# ifndef COMM_NO_COMMUNICATION
#  define COMM_NO_COMMUNICATION (0U)
# endif
# ifndef COMM_SILENT_COMMUNICATION
#  define COMM_SILENT_COMMUNICATION (1U)
# endif
# ifndef COMM_FULL_COMMUNICATION
#  define COMM_FULL_COMMUNICATION (2U)
# endif

# define Rte_TypeDef_NvM_RequestResultType
typedef uint8 NvM_RequestResultType;
# define NvM_RequestResultType_LowerLimit (0U)
# define NvM_RequestResultType_UpperLimit (5U)
# ifndef NVM_REQ_OK
#  define NVM_REQ_OK (0U)
# endif
# ifndef NVM_REQ_NOT_OK
#  define NVM_REQ_NOT_OK (1U)
# endif
# ifndef NVM_REQ_PENDING
#  define NVM_REQ_PENDING (2U)
# endif
# ifndef NVM_REQ_INTEGRITY_FAILED
#  define NVM_REQ_INTEGRITY_FAILED (3U)
# endif
# ifndef NVM_REQ_BLOCK_SKIPPED
#  define NVM_REQ_BLOCK_SKIPPED (4U)
# endif
# ifndef NVM_REQ_NV_INVALIDATED
#  define NVM_REQ_NV_INVALIDATED (5U)
# endif

# define Rte_TypeDef_c02_BatCutSw_Stat
typedef uint8 c02_BatCutSw_Stat;
# define c02_BatCutSw_Stat_LowerLimit (0U)
# define c02_BatCutSw_Stat_UpperLimit (3U)
# define Rte_InvalidValue_c02_BatCutSw_Stat (3U)
# define InvalidValue_c02_BatCutSw_Stat (3U)
# ifndef I_C02_BATCUTSW_STAT_CLS
#  define I_C02_BATCUTSW_STAT_CLS (0U)
# endif
# ifndef I_C02_BATCUTSW_STAT_PREOPN
#  define I_C02_BATCUTSW_STAT_PREOPN (1U)
# endif
# ifndef I_C02_BATCUTSW_STAT_OPN
#  define I_C02_BATCUTSW_STAT_OPN (2U)
# endif
# ifndef I_C02_BATCUTSW_STAT_SNA
#  define I_C02_BATCUTSW_STAT_SNA (3U)
# endif

# define Rte_TypeDef_c02_Disengg_Engg
typedef uint8 c02_Disengg_Engg;
# define c02_Disengg_Engg_LowerLimit (0U)
# define c02_Disengg_Engg_UpperLimit (3U)
# define Rte_InvalidValue_c02_Disengg_Engg (3U)
# define InvalidValue_c02_Disengg_Engg (3U)
# ifndef I_C02_DISENGG_ENGG_DISENGG
#  define I_C02_DISENGG_ENGG_DISENGG (0U)
# endif
# ifndef I_C02_DISENGG_ENGG_ENGG
#  define I_C02_DISENGG_ENGG_ENGG (1U)
# endif
# ifndef I_C02_DISENGG_ENGG_NDEF2
#  define I_C02_DISENGG_ENGG_NDEF2 (2U)
# endif
# ifndef I_C02_DISENGG_ENGG_SNA
#  define I_C02_DISENGG_ENGG_SNA (3U)
# endif

# define Rte_TypeDef_c02_EVC_Stat
typedef uint8 c02_EVC_Stat;
# define c02_EVC_Stat_LowerLimit (0U)
# define c02_EVC_Stat_UpperLimit (3U)
# define Rte_InvalidValue_c02_EVC_Stat (3U)
# define InvalidValue_c02_EVC_Stat (3U)
# ifndef I_C02_EVC_STAT_NDEF0
#  define I_C02_EVC_STAT_NDEF0 (0U)
# endif
# ifndef I_C02_EVC_STAT_PROG
#  define I_C02_EVC_STAT_PROG (1U)
# endif
# ifndef I_C02_EVC_STAT_REQ
#  define I_C02_EVC_STAT_REQ (2U)
# endif
# ifndef I_C02_EVC_STAT_SNA
#  define I_C02_EVC_STAT_SNA (3U)
# endif

# define Rte_TypeDef_c02_TPM_Actv_Rq_V2
typedef uint8 c02_TPM_Actv_Rq_V2;
# define c02_TPM_Actv_Rq_V2_LowerLimit (0U)
# define c02_TPM_Actv_Rq_V2_UpperLimit (3U)
# define Rte_InvalidValue_c02_TPM_Actv_Rq_V2 (3U)
# define InvalidValue_c02_TPM_Actv_Rq_V2 (3U)
# ifndef I_C02_TPM_ACTV_RQ_V2_IDLE
#  define I_C02_TPM_ACTV_RQ_V2_IDLE (0U)
# endif
# ifndef I_C02_TPM_ACTV_RQ_V2_ACTIVATE
#  define I_C02_TPM_ACTV_RQ_V2_ACTIVATE (1U)
# endif
# ifndef I_C02_TPM_ACTV_RQ_V2_SNA
#  define I_C02_TPM_ACTV_RQ_V2_SNA (3U)
# endif

# define Rte_TypeDef_c02_Tire_Stat
typedef uint8 c02_Tire_Stat;
# define c02_Tire_Stat_LowerLimit (0U)
# define c02_Tire_Stat_UpperLimit (3U)
# ifndef I_C02_TIRE_STAT_NORMAL
#  define I_C02_TIRE_STAT_NORMAL (0U)
# endif
# ifndef I_C02_TIRE_STAT_SOFT_WARN
#  define I_C02_TIRE_STAT_SOFT_WARN (1U)
# endif
# ifndef I_C02_TIRE_STAT_LOW_PRESS
#  define I_C02_TIRE_STAT_LOW_PRESS (2U)
# endif
# ifndef I_C02_TIRE_STAT_DEFLATION
#  define I_C02_TIRE_STAT_DEFLATION (3U)
# endif

# define Rte_TypeDef_c02_Tire_Temp
typedef uint8 c02_Tire_Temp;
# define c02_Tire_Temp_LowerLimit (0U)
# define c02_Tire_Temp_UpperLimit (3U)
# define Rte_InvalidValue_c02_Tire_Temp (3U)
# define InvalidValue_c02_Tire_Temp (3U)
# ifndef I_C02_TIRE_TEMP_NORMAL
#  define I_C02_TIRE_TEMP_NORMAL (0U)
# endif
# ifndef I_C02_TIRE_TEMP_WARM
#  define I_C02_TIRE_TEMP_WARM (1U)
# endif
# ifndef I_C02_TIRE_TEMP_HOT
#  define I_C02_TIRE_TEMP_HOT (2U)
# endif
# ifndef I_C02_TIRE_TEMP_SNA
#  define I_C02_TIRE_TEMP_SNA (3U)
# endif

# define Rte_TypeDef_c02_TransMd_Stat
typedef uint8 c02_TransMd_Stat;
# define c02_TransMd_Stat_LowerLimit (0U)
# define c02_TransMd_Stat_UpperLimit (3U)
# define Rte_InvalidValue_c02_TransMd_Stat (3U)
# define InvalidValue_c02_TransMd_Stat (3U)
# ifndef I_C02_TRANSMD_STAT_OFF
#  define I_C02_TRANSMD_STAT_OFF (0U)
# endif
# ifndef I_C02_TRANSMD_STAT_TEMP_OFF
#  define I_C02_TRANSMD_STAT_TEMP_OFF (1U)
# endif
# ifndef I_C02_TRANSMD_STAT_ACTV
#  define I_C02_TRANSMD_STAT_ACTV (2U)
# endif
# ifndef I_C02_TRANSMD_STAT_SNA
#  define I_C02_TRANSMD_STAT_SNA (3U)
# endif

# define Rte_TypeDef_c03_DateTm_Stat
typedef uint8 c03_DateTm_Stat;
# define c03_DateTm_Stat_LowerLimit (0U)
# define c03_DateTm_Stat_UpperLimit (7U)
# define Rte_InvalidValue_c03_DateTm_Stat (7U)
# define InvalidValue_c03_DateTm_Stat (7U)
# ifndef I_C03_DATETM_STAT_INVALID
#  define I_C03_DATETM_STAT_INVALID (0U)
# endif
# ifndef I_C03_DATETM_STAT_INIT
#  define I_C03_DATETM_STAT_INIT (1U)
# endif
# ifndef I_C03_DATETM_STAT_PLAUSIBLE
#  define I_C03_DATETM_STAT_PLAUSIBLE (2U)
# endif
# ifndef I_C03_DATETM_STAT_NEW
#  define I_C03_DATETM_STAT_NEW (3U)
# endif
# ifndef I_C03_DATETM_STAT_DIAG
#  define I_C03_DATETM_STAT_DIAG (4U)
# endif
# ifndef I_C03_DATETM_STAT_INCOMPLETE
#  define I_C03_DATETM_STAT_INCOMPLETE (5U)
# endif
# ifndef I_C03_DATETM_STAT_SNA
#  define I_C03_DATETM_STAT_SNA (7U)
# endif

# define Rte_TypeDef_c03_EOL_Disp_Rq
typedef uint8 c03_EOL_Disp_Rq;
# define c03_EOL_Disp_Rq_LowerLimit (0U)
# define c03_EOL_Disp_Rq_UpperLimit (7U)
# define Rte_InvalidValue_c03_EOL_Disp_Rq (7U)
# define InvalidValue_c03_EOL_Disp_Rq (7U)
# ifndef I_C03_EOL_DISP_RQ_IDLE
#  define I_C03_EOL_DISP_RQ_IDLE (0U)
# endif
# ifndef I_C03_EOL_DISP_RQ_IOD_MEAS
#  define I_C03_EOL_DISP_RQ_IOD_MEAS (1U)
# endif
# ifndef I_C03_EOL_DISP_RQ_IOD_ERR
#  define I_C03_EOL_DISP_RQ_IOD_ERR (2U)
# endif
# ifndef I_C03_EOL_DISP_RQ_CHRG_BAT
#  define I_C03_EOL_DISP_RQ_CHRG_BAT (3U)
# endif
# ifndef I_C03_EOL_DISP_RQ_BAT_NCHRG
#  define I_C03_EOL_DISP_RQ_BAT_NCHRG (4U)
# endif
# ifndef I_C03_EOL_DISP_RQ_SNA
#  define I_C03_EOL_DISP_RQ_SNA (7U)
# endif

# define Rte_TypeDef_c03_EVC_TPM_Style
typedef uint8 c03_EVC_TPM_Style;
# define c03_EVC_TPM_Style_LowerLimit (0U)
# define c03_EVC_TPM_Style_UpperLimit (7U)
# ifndef I_C03_EVC_TPM_STYLE_INFLPRESSCTRL_LOW
#  define I_C03_EVC_TPM_STYLE_INFLPRESSCTRL_LOW (0U)
# endif
# ifndef I_C03_EVC_TPM_STYLE_INFLPRESSCTRL_HIGHMID
#  define I_C03_EVC_TPM_STYLE_INFLPRESSCTRL_HIGHMID (1U)
# endif
# ifndef I_C03_EVC_TPM_STYLE_RUNFLATIND
#  define I_C03_EVC_TPM_STYLE_RUNFLATIND (2U)
# endif
# ifndef I_C03_EVC_TPM_STYLE_OTHER
#  define I_C03_EVC_TPM_STYLE_OTHER (7U)
# endif

# define Rte_TypeDef_c03_EngRun_Stat
typedef uint8 c03_EngRun_Stat;
# define c03_EngRun_Stat_LowerLimit (0U)
# define c03_EngRun_Stat_UpperLimit (7U)
# define Rte_InvalidValue_c03_EngRun_Stat (7U)
# define InvalidValue_c03_EngRun_Stat (7U)
# ifndef I_C03_ENGRUN_STAT_STOP
#  define I_C03_ENGRUN_STAT_STOP (0U)
# endif
# ifndef I_C03_ENGRUN_STAT_START
#  define I_C03_ENGRUN_STAT_START (1U)
# endif
# ifndef I_C03_ENGRUN_STAT_IDLE_UNSTBL
#  define I_C03_ENGRUN_STAT_IDLE_UNSTBL (2U)
# endif
# ifndef I_C03_ENGRUN_STAT_IDLE_STBL
#  define I_C03_ENGRUN_STAT_IDLE_STBL (3U)
# endif
# ifndef I_C03_ENGRUN_STAT_UNLIMITED
#  define I_C03_ENGRUN_STAT_UNLIMITED (4U)
# endif
# ifndef I_C03_ENGRUN_STAT_LIMITED
#  define I_C03_ENGRUN_STAT_LIMITED (5U)
# endif
# ifndef I_C03_ENGRUN_STAT_NDEF6
#  define I_C03_ENGRUN_STAT_NDEF6 (6U)
# endif
# ifndef I_C03_ENGRUN_STAT_SNA
#  define I_C03_ENGRUN_STAT_SNA (7U)
# endif

# define Rte_TypeDef_c03_ISw_Stat
typedef uint8 c03_ISw_Stat;
# define c03_ISw_Stat_LowerLimit (0U)
# define c03_ISw_Stat_UpperLimit (7U)
# define Rte_InvalidValue_c03_ISw_Stat (7U)
# define InvalidValue_c03_ISw_Stat (7U)
# ifndef I_C03_ISW_STAT_IGN_LOCK
#  define I_C03_ISW_STAT_IGN_LOCK (0U)
# endif
# ifndef I_C03_ISW_STAT_IGN_OFF
#  define I_C03_ISW_STAT_IGN_OFF (1U)
# endif
# ifndef I_C03_ISW_STAT_IGN_ACC
#  define I_C03_ISW_STAT_IGN_ACC (2U)
# endif
# ifndef I_C03_ISW_STAT_IGN_ON
#  define I_C03_ISW_STAT_IGN_ON (4U)
# endif
# ifndef I_C03_ISW_STAT_IGN_START
#  define I_C03_ISW_STAT_IGN_START (5U)
# endif
# ifndef I_C03_ISW_STAT_SNA
#  define I_C03_ISW_STAT_SNA (7U)
# endif

# define Rte_TypeDef_c03_TPM_Stat
typedef uint8 c03_TPM_Stat;
# define c03_TPM_Stat_LowerLimit (0U)
# define c03_TPM_Stat_UpperLimit (7U)
# define Rte_InvalidValue_c03_TPM_Stat (7U)
# define InvalidValue_c03_TPM_Stat (7U)
# ifndef I_C03_TPM_STAT_ACTIVE
#  define I_C03_TPM_STAT_ACTIVE (0U)
# endif
# ifndef I_C03_TPM_STAT_WAIT
#  define I_C03_TPM_STAT_WAIT (1U)
# endif
# ifndef I_C03_TPM_STAT_ERROR
#  define I_C03_TPM_STAT_ERROR (2U)
# endif
# ifndef I_C03_TPM_STAT_NO_SENSORS
#  define I_C03_TPM_STAT_NO_SENSORS (3U)
# endif
# ifndef I_C03_TPM_STAT_SNA
#  define I_C03_TPM_STAT_SNA (7U)
# endif

# define Rte_TypeDef_c03_TPM_WarnDisp_Rq
typedef uint8 c03_TPM_WarnDisp_Rq;
# define c03_TPM_WarnDisp_Rq_LowerLimit (0U)
# define c03_TPM_WarnDisp_Rq_UpperLimit (7U)
# define Rte_InvalidValue_c03_TPM_WarnDisp_Rq (7U)
# define InvalidValue_c03_TPM_WarnDisp_Rq (7U)
# ifndef I_C03_TPM_WARNDISP_RQ_NO_WARN
#  define I_C03_TPM_WARNDISP_RQ_NO_WARN (0U)
# endif
# ifndef I_C03_TPM_WARNDISP_RQ_SOFT
#  define I_C03_TPM_WARNDISP_RQ_SOFT (1U)
# endif
# ifndef I_C03_TPM_WARNDISP_RQ_LOW_P
#  define I_C03_TPM_WARNDISP_RQ_LOW_P (2U)
# endif
# ifndef I_C03_TPM_WARNDISP_RQ_FAST
#  define I_C03_TPM_WARNDISP_RQ_FAST (3U)
# endif
# ifndef I_C03_TPM_WARNDISP_RQ_SNA
#  define I_C03_TPM_WARNDISP_RQ_SNA (7U)
# endif

# define Rte_TypeDef_c03_Tire_Temp_WarnDisp
typedef uint8 c03_Tire_Temp_WarnDisp;
# define c03_Tire_Temp_WarnDisp_LowerLimit (0U)
# define c03_Tire_Temp_WarnDisp_UpperLimit (7U)
# define Rte_InvalidValue_c03_Tire_Temp_WarnDisp (7U)
# define InvalidValue_c03_Tire_Temp_WarnDisp (7U)
# ifndef I_C03_TIRE_TEMP_WARNDISP_NO_MESS
#  define I_C03_TIRE_TEMP_WARNDISP_NO_MESS (0U)
# endif
# ifndef I_C03_TIRE_TEMP_WARNDISP_OVERHEAT
#  define I_C03_TIRE_TEMP_WARNDISP_OVERHEAT (1U)
# endif
# ifndef I_C03_TIRE_TEMP_WARNDISP_REDUCE_SPEED
#  define I_C03_TIRE_TEMP_WARNDISP_REDUCE_SPEED (2U)
# endif
# ifndef I_C03_TIRE_TEMP_WARNDISP_SNA
#  define I_C03_TIRE_TEMP_WARNDISP_SNA (7U)
# endif

# define Rte_TypeDef_c04_TPM_MsgDisp_Rq
typedef uint8 c04_TPM_MsgDisp_Rq;
# define c04_TPM_MsgDisp_Rq_LowerLimit (0U)
# define c04_TPM_MsgDisp_Rq_UpperLimit (15U)
# define Rte_InvalidValue_c04_TPM_MsgDisp_Rq (15U)
# define InvalidValue_c04_TPM_MsgDisp_Rq (15U)
# ifndef I_C04_TPM_MSGDISP_RQ_NO_MESS
#  define I_C04_TPM_MSGDISP_RQ_NO_MESS (0U)
# endif
# ifndef I_C04_TPM_MSGDISP_RQ_UNPLAUSIBLE
#  define I_C04_TPM_MSGDISP_RQ_UNPLAUSIBLE (1U)
# endif
# ifndef I_C04_TPM_MSGDISP_RQ_NO_SENSORS
#  define I_C04_TPM_MSGDISP_RQ_NO_SENSORS (2U)
# endif
# ifndef I_C04_TPM_MSGDISP_RQ_ERROR
#  define I_C04_TPM_MSGDISP_RQ_ERROR (3U)
# endif
# ifndef I_C04_TPM_MSGDISP_RQ_TNA
#  define I_C04_TPM_MSGDISP_RQ_TNA (4U)
# endif
# ifndef I_C04_TPM_MSGDISP_RQ_WE_MISS
#  define I_C04_TPM_MSGDISP_RQ_WE_MISS (5U)
# endif
# ifndef I_C04_TPM_MSGDISP_RQ_RESTART
#  define I_C04_TPM_MSGDISP_RQ_RESTART (6U)
# endif
# ifndef I_C04_TPM_MSGDISP_RQ_SNA
#  define I_C04_TPM_MSGDISP_RQ_SNA (15U)
# endif

# define Rte_TypeDef_c05_EVC_BodyStyle
typedef uint8 c05_EVC_BodyStyle;
# define c05_EVC_BodyStyle_LowerLimit (0U)
# define c05_EVC_BodyStyle_UpperLimit (31U)
# ifndef I_C05_EVC_BODYSTYLE_FW
#  define I_C05_EVC_BODYSTYLE_FW (0U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FV
#  define I_C05_EVC_BODYSTYLE_FV (1U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FC
#  define I_C05_EVC_BODYSTYLE_FC (2U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FS
#  define I_C05_EVC_BODYSTYLE_FS (3U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FA
#  define I_C05_EVC_BODYSTYLE_FA (4U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FR
#  define I_C05_EVC_BODYSTYLE_FR (5U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FCL
#  define I_C05_EVC_BODYSTYLE_FCL (6U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FVV
#  define I_C05_EVC_BODYSTYLE_FVV (7U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FVF
#  define I_C05_EVC_BODYSTYLE_FVF (8U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FF
#  define I_C05_EVC_BODYSTYLE_FF (9U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FB
#  define I_C05_EVC_BODYSTYLE_FB (10U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FT
#  define I_C05_EVC_BODYSTYLE_FT (12U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FX
#  define I_C05_EVC_BODYSTYLE_FX (13U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FCLA
#  define I_C05_EVC_BODYSTYLE_FCLA (14U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FH
#  define I_C05_EVC_BODYSTYLE_FH (15U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FZ
#  define I_C05_EVC_BODYSTYLE_FZ (16U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_FN
#  define I_C05_EVC_BODYSTYLE_FN (17U)
# endif
# ifndef I_C05_EVC_BODYSTYLE_OTHER
#  define I_C05_EVC_BODYSTYLE_OTHER (31U)
# endif

# define Rte_TypeDef_c06_EVC_VehLine
typedef uint8 c06_EVC_VehLine;
# define c06_EVC_VehLine_LowerLimit (1U)
# define c06_EVC_VehLine_UpperLimit (63U)
# ifndef I_C06_EVC_VEHLINE_BR231
#  define I_C06_EVC_VEHLINE_BR231 (1U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR212
#  define I_C06_EVC_VEHLINE_BR212 (2U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR222
#  define I_C06_EVC_VEHLINE_BR222 (4U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR205
#  define I_C06_EVC_VEHLINE_BR205 (6U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR166
#  define I_C06_EVC_VEHLINE_BR166 (8U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR207
#  define I_C06_EVC_VEHLINE_BR207 (9U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR463
#  define I_C06_EVC_VEHLINE_BR463 (10U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR217
#  define I_C06_EVC_VEHLINE_BR217 (11U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR232
#  define I_C06_EVC_VEHLINE_BR232 (12U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR213
#  define I_C06_EVC_VEHLINE_BR213 (13U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR238
#  define I_C06_EVC_VEHLINE_BR238 (14U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR173
#  define I_C06_EVC_VEHLINE_BR173 (18U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR167
#  define I_C06_EVC_VEHLINE_BR167 (19U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR177
#  define I_C06_EVC_VEHLINE_BR177 (20U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR190
#  define I_C06_EVC_VEHLINE_BR190 (21U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR257
#  define I_C06_EVC_VEHLINE_BR257 (23U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR218
#  define I_C06_EVC_VEHLINE_BR218 (32U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR290
#  define I_C06_EVC_VEHLINE_BR290 (34U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR447
#  define I_C06_EVC_VEHLINE_BR447 (38U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR253
#  define I_C06_EVC_VEHLINE_BR253 (39U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR292
#  define I_C06_EVC_VEHLINE_BR292 (40U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR252
#  define I_C06_EVC_VEHLINE_BR252 (41U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR247
#  define I_C06_EVC_VEHLINE_BR247 (42U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR118
#  define I_C06_EVC_VEHLINE_BR118 (43U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR907
#  define I_C06_EVC_VEHLINE_BR907 (44U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR910
#  define I_C06_EVC_VEHLINE_BR910 (45U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR470
#  define I_C06_EVC_VEHLINE_BR470 (46U)
# endif
# ifndef I_C06_EVC_VEHLINE_BR293
#  define I_C06_EVC_VEHLINE_BR293 (47U)
# endif
# ifndef I_C06_EVC_VEHLINE_OTHER
#  define I_C06_EVC_VEHLINE_OTHER (63U)
# endif

# define Rte_TypeDef_c08_Days_1_31_1
typedef uint8 c08_Days_1_31_1;
# define c08_Days_1_31_1_LowerLimit (1U)
# define c08_Days_1_31_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_Days_1_31_1 (255U)
# define InvalidValue_c08_Days_1_31_1 (255U)
# ifndef I_C08_DAYS_1_31_1_SNA
#  define I_C08_DAYS_1_31_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_Impulses_0_254_1
typedef uint8 c08_Impulses_0_254_1;
# define c08_Impulses_0_254_1_LowerLimit (0U)
# define c08_Impulses_0_254_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_Impulses_0_254_1 (255U)
# define InvalidValue_c08_Impulses_0_254_1 (255U)
# ifndef I_C08_IMPULSES_0_254_1_SNA
#  define I_C08_IMPULSES_0_254_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_Months_1_12_1
typedef uint8 c08_Months_1_12_1;
# define c08_Months_1_12_1_LowerLimit (1U)
# define c08_Months_1_12_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_Months_1_12_1 (255U)
# define InvalidValue_c08_Months_1_12_1 (255U)
# ifndef I_C08_MONTHS_1_12_1_SNA
#  define I_C08_MONTHS_1_12_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_V_0_25k4_0k1
typedef uint8 c08_V_0_25k4_0k1;
# define c08_V_0_25k4_0k1_LowerLimit (0U)
# define c08_V_0_25k4_0k1_UpperLimit (255U)
# define Rte_InvalidValue_c08_V_0_25k4_0k1 (255U)
# define InvalidValue_c08_V_0_25k4_0k1 (255U)
# ifndef I_C08_V_0_25K4_0K1_SNA
#  define I_C08_V_0_25K4_0K1_SNA (255U)
# endif

# define Rte_TypeDef_c08_WakeupRsn_TPM
typedef uint8 c08_WakeupRsn_TPM;
# define c08_WakeupRsn_TPM_LowerLimit (0U)
# define c08_WakeupRsn_TPM_UpperLimit (255U)
# define Rte_InvalidValue_c08_WakeupRsn_TPM (255U)
# define InvalidValue_c08_WakeupRsn_TPM (255U)
# ifndef I_C08_WAKEUPRSN_TPM_NETWORK
#  define I_C08_WAKEUPRSN_TPM_NETWORK (0U)
# endif
# ifndef I_C08_WAKEUPRSN_TPM_SNA
#  define I_C08_WAKEUPRSN_TPM_SNA (255U)
# endif

# define Rte_TypeDef_c08_Years_0_99_1
typedef uint8 c08_Years_0_99_1;
# define c08_Years_0_99_1_LowerLimit (0U)
# define c08_Years_0_99_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_Years_0_99_1 (255U)
# define InvalidValue_c08_Years_0_99_1 (255U)
# ifndef I_C08_YEARS_0_99_1_SNA
#  define I_C08_YEARS_0_99_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_degC_m40_85_0k5
typedef uint8 c08_degC_m40_85_0k5;
# define c08_degC_m40_85_0k5_LowerLimit (0U)
# define c08_degC_m40_85_0k5_UpperLimit (255U)
# define Rte_InvalidValue_c08_degC_m40_85_0k5 (255U)
# define InvalidValue_c08_degC_m40_85_0k5 (255U)
# ifndef I_C08_DEGC_M40_85_0K5_SNA
#  define I_C08_DEGC_M40_85_0K5_SNA (255U)
# endif

# define Rte_TypeDef_c08_degC_m50_204_1
typedef uint8 c08_degC_m50_204_1;
# define c08_degC_m50_204_1_LowerLimit (0U)
# define c08_degC_m50_204_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_degC_m50_204_1 (255U)
# define InvalidValue_c08_degC_m50_204_1 (255U)
# ifndef I_C08_DEGC_M50_204_1_SNA
#  define I_C08_DEGC_M50_204_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_hPa_0_1980_7k8
typedef uint8 c08_hPa_0_1980_7k8;
# define c08_hPa_0_1980_7k8_LowerLimit (0U)
# define c08_hPa_0_1980_7k8_UpperLimit (255U)
# define Rte_InvalidValue_c08_hPa_0_1980_7k8 (255U)
# define InvalidValue_c08_hPa_0_1980_7k8 (255U)
# ifndef I_C08_HPA_0_1980_7K8_SNA
#  define I_C08_HPA_0_1980_7K8_SNA (255U)
# endif

# define Rte_TypeDef_c08_h_0_23_1
typedef uint8 c08_h_0_23_1;
# define c08_h_0_23_1_LowerLimit (0U)
# define c08_h_0_23_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_h_0_23_1 (255U)
# define InvalidValue_c08_h_0_23_1 (255U)
# ifndef I_C08_H_0_23_1_SNA
#  define I_C08_H_0_23_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_kPa_0_632d5_2d5
typedef uint8 c08_kPa_0_632d5_2d5;
# define c08_kPa_0_632d5_2d5_LowerLimit (0U)
# define c08_kPa_0_632d5_2d5_UpperLimit (255U)
# define Rte_InvalidValue_c08_kPa_0_632d5_2d5 (255U)
# define InvalidValue_c08_kPa_0_632d5_2d5 (255U)
# ifndef I_C08_KPA_0_632D5_2D5_NO_IND
#  define I_C08_KPA_0_632D5_2D5_NO_IND (254U)
# endif
# ifndef I_C08_KPA_0_632D5_2D5_SNA
#  define I_C08_KPA_0_632D5_2D5_SNA (255U)
# endif

# define Rte_TypeDef_c08_min_0_59_1
typedef uint8 c08_min_0_59_1;
# define c08_min_0_59_1_LowerLimit (0U)
# define c08_min_0_59_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_min_0_59_1 (255U)
# define InvalidValue_c08_min_0_59_1 (255U)
# ifndef I_C08_MIN_0_59_1_SNA
#  define I_C08_MIN_0_59_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_ms_0_254_1
typedef uint8 c08_ms_0_254_1;
# define c08_ms_0_254_1_LowerLimit (0U)
# define c08_ms_0_254_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_ms_0_254_1 (255U)
# define InvalidValue_c08_ms_0_254_1 (255U)
# ifndef I_C08_MS_0_254_1_SNA
#  define I_C08_MS_0_254_1_SNA (255U)
# endif

# define Rte_TypeDef_c08_s_0_59_1
typedef uint8 c08_s_0_59_1;
# define c08_s_0_59_1_LowerLimit (0U)
# define c08_s_0_59_1_UpperLimit (255U)
# define Rte_InvalidValue_c08_s_0_59_1 (255U)
# define InvalidValue_c08_s_0_59_1 (255U)
# ifndef I_C08_S_0_59_1_SNA
#  define I_C08_S_0_59_1_SNA (255U)
# endif

# define Rte_TypeDef_c12_km_p_h_0_409k4_0k1
typedef uint16 c12_km_p_h_0_409k4_0k1;
# define c12_km_p_h_0_409k4_0k1_LowerLimit (0U)
# define c12_km_p_h_0_409k4_0k1_UpperLimit (4095U)
# define Rte_InvalidValue_c12_km_p_h_0_409k4_0k1 (4095U)
# define InvalidValue_c12_km_p_h_0_409k4_0k1 (4095U)
# ifndef I_C12_KM_P_H_0_409K4_0K1_SNA
#  define I_C12_KM_P_H_0_409K4_0K1_SNA (4095U)
# endif

# define Rte_TypeDef_c24_km_0_999999k9_0k1
typedef uint32 c24_km_0_999999k9_0k1;
# define c24_km_0_999999k9_0k1_LowerLimit (0U)
# define c24_km_0_999999k9_0k1_UpperLimit (16777215U)
# define Rte_InvalidValue_c24_km_0_999999k9_0k1 (16777215U)
# define InvalidValue_c24_km_0_999999k9_0k1 (16777215U)
# ifndef I_C24_KM_0_999999K9_0K1_SNA
#  define I_C24_KM_0_999999K9_0K1_SNA (16777215U)
# endif

# define Rte_TypeDef_ARR_08_UInt_noSNA_8
typedef c08_UInt_SNA_na ARR_08_UInt_noSNA_8[8];

# define Rte_TypeDef_DT_TelStat
typedef UInt16 DT_TelStat[4];

# define Rte_TypeDef_DT_auRfStruct
typedef UInt8 DT_auRfStruct[34];

# define Rte_TypeDef_DT_aucActivationMemoryFD
typedef UInt8 DT_aucActivationMemoryFD[107];

# define Rte_TypeDef_DT_aucMessageMemoryPAL
typedef UInt8 DT_aucMessageMemoryPAL[84];

# define Rte_TypeDef_DT_aucPalAbsDelayTimeParam
typedef UInt8 DT_aucPalAbsDelayTimeParam[2];

# define Rte_TypeDef_DT_aucPalLocateStatistics
typedef UInt8 DT_aucPalLocateStatistics[15];

# define Rte_TypeDef_DT_aucPalStatsLastCycleWU
typedef UInt8 DT_aucPalStatsLastCycleWU[48];

# define Rte_TypeDef_DT_aucPalStatsLongTermWU
typedef UInt8 DT_aucPalStatsLongTermWU[56];

# define Rte_TypeDef_DT_aucPosComparePressure
typedef UInt8 DT_aucPosComparePressure[4];

# define Rte_TypeDef_DT_aucReceptionStateWuDCM
typedef UInt8 DT_aucReceptionStateWuDCM[4];

# define Rte_TypeDef_DT_aucSNRlongTerm
typedef UInt8 DT_aucSNRlongTerm[4];

# define Rte_TypeDef_DT_aucStatusInfoWuCounts
typedef UInt8 DT_aucStatusInfoWuCounts[8];

# define Rte_TypeDef_DT_aucStatusInfoWuFailReas
typedef UInt8 DT_aucStatusInfoWuFailReas[40];

# define Rte_TypeDef_DT_aucStatusInfoWuPrevPos
typedef UInt8 DT_aucStatusInfoWuPrevPos[4];

# define Rte_TypeDef_DT_aucStatusInfoWuSensFail
typedef UInt8 DT_aucStatusInfoWuSensFail[4];

# define Rte_TypeDef_DT_aucTempWarnMessageMemory
typedef UInt8 DT_aucTempWarnMessageMemory[84];

# define Rte_TypeDef_DT_aucWAHistWP
typedef DT_ucPosOfID DT_aucWAHistWP[4];

# define Rte_TypeDef_DT_aucWAParam
typedef UInt8 DT_aucWAParam[2];

# define Rte_TypeDef_DT_aucWheelStatus
typedef UInt8 DT_aucWheelStatus[5];

# define Rte_TypeDef_DT_aulWAHistID
typedef DT_ulID DT_aulWAHistID[4];

# define Rte_TypeDef_DT_tDiagTraceMem
typedef UInt8 DT_tDiagTraceMem[12];

# define Rte_TypeDef_DT_tEvcCfgBits
typedef UInt8 DT_tEvcCfgBits[10];

# define Rte_TypeDef_DT_tNvMReservedBytes
typedef UInt8 DT_tNvMReservedBytes[20];

# define Rte_TypeDef_DT_tSensorBatInfo
typedef UInt8 DT_tSensorBatInfo[44];

# define Rte_TypeDef_DT_ucGlobalWarnLevel
typedef UInt8 DT_ucGlobalWarnLevel[1];

# define Rte_TypeDef_NvM_DestPtr
typedef UInt8 NvM_DestPtr[65535];

# define Rte_TypeDef_DT_tData2Alloc
typedef struct
{
  UInt16 ushTimeStamp;
  UInt32 ulID;
  UInt8 ucTelType;
  UInt8 ucPalData;
  UInt8 ucFrameCounter;
  UInt16 ushAbsStickFL;
  UInt16 ushAbsStickFR;
  UInt16 ushAbsStickRL;
  UInt16 ushAbsStickRR;
} DT_tData2Alloc;

# define Rte_TypeDef_DT_tData2Warn
typedef struct
{
  UInt32 ulID;
  UInt8 ucP;
  UInt8 ucT;
  UInt8 ucZomPos;
  UInt8 ucTxTrigger;
} DT_tData2Warn;

# define Rte_TypeDef_DT_tEnvData
typedef struct
{
  UInt8 ucKlState;
  UInt8 ucTempOut;
  UInt16 ushVehSpeed;
  UInt8 ucPressOut;
  UInt8 ucEngStat;
  UInt8 ucIgnOnStartProc;
} DT_tEnvData;

# define Rte_TypeDef_DT_tLogicalDataPalCod
typedef struct
{
  UInt8 ucMinWarnThreshold;
  UInt8 ucAutoFillDetectionOnOff;
  UInt8 ucT_Soft;
  UInt8 ucPercent_Soft;
  UInt8 ucT_Hard;
  UInt8 ucPercent_Hard;
  UInt8 ucTempWarnOnOff;
} DT_tLogicalDataPalCod;

# define Rte_TypeDef_DT_tParaTempWarnCod
typedef struct
{
  UInt8 ucV1;
  UInt8 ucV2;
  UInt8 ucV3;
  SInt8 scT0;
  SInt8 scT1;
  SInt8 scT2;
  UInt16 ushHC_MAX;
} DT_tParaTempWarnCod;

# define Rte_TypeDef_REC_DateTm_AR2_f0ifkphxunpp94u3ro8qn5tdm
typedef struct
{
  c08_Days_1_31_1 DateTmDay;
  c08_h_0_23_1 DateTmHour;
  c08_min_0_59_1 DateTmMinute;
  c08_Months_1_12_1 DateTmMonth;
  c08_s_0_59_1 DateTmSecond;
  c03_DateTm_Stat DateTmStat;
  c08_Years_0_99_1 DateTmYear;
} REC_DateTm_AR2_f0ifkphxunpp94u3ro8qn5tdm;

# define Rte_TypeDef_REC_EVC_CfgBit_01_32_Pr2_d23bad5cnts3f65mtgoqoxmrz
typedef struct
{
  c02_EVC_Stat EVC_CfgBit_01_32_Stat;
  DC_BOOL EVC_1E_GuardLvl_B4_Avl;
  DC_BOOL EVC_1F_GuardLvl_B6_Avl;
  DC_BOOL EVC_20_GuardLvl_B7_Avl;
} REC_EVC_CfgBit_01_32_Pr2_d23bad5cnts3f65mtgoqoxmrz;

# define Rte_TypeDef_REC_EVC_CfgList_01_0C_Pr2_ah3rxaqpfvlnju8848jpspm9p
typedef struct
{
  c05_EVC_BodyStyle EVC_List02_BodyStyle;
  c02_EVC_Stat EVC_CfgList_01_0C_Stat;
  c03_EVC_TPM_Style EVC_List0A_TPM_Style;
  c06_EVC_VehLine EVC_List0C_VehLine;
} REC_EVC_CfgList_01_0C_Pr2_ah3rxaqpfvlnju8848jpspm9p;

# define Rte_TypeDef_REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy
typedef struct
{
  c03_EngRun_Stat EngRun_Stat;
} REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy;

# define Rte_TypeDef_REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno
typedef struct
{
  c03_ISw_Stat ISw_Stat;
  DC_BOOL Ign_On_StartProc_Inact;
} REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno;

# define Rte_TypeDef_REC_Ign_Stat_Pr2_b0ko81o0x5jgvwtduf99gvzi0
typedef struct
{
  c03_ISw_Stat ISw_Stat;
} REC_Ign_Stat_Pr2_b0ko81o0x5jgvwtduf99gvzi0;

# define Rte_TypeDef_REC_PN14_SupBat_Stat_2is6fi0meeac78nkn35zc5ui3
typedef struct
{
  c02_BatCutSw_Stat PN14_SupBatCutSw_Stat;
  c08_V_0_25k4_0k1 PN14_SupBat_Volt;
} REC_PN14_SupBat_Stat_2is6fi0meeac78nkn35zc5ui3;

# define Rte_TypeDef_REC_ROE_XX
typedef struct
{
  c24_0_16777215_1_SNA_na ROE_DTC_XX;
  c08_0_255_1_SNA_na ROE_DTC_Stat_XX;
  c32_0_4294967295_1_SNA_na ROE_Header_XX;
} REC_ROE_XX;

# define Rte_TypeDef_REC_RefPress
typedef struct
{
  c08_kPa_0_632d5_2d5 RefPress_Front;
  c08_kPa_0_632d5_2d5 RefPress_Rear;
} REC_RefPress;

# define Rte_TypeDef_REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt
typedef struct
{
  c08_CRC_woSNA CRC_TPM_Lmp_On_Rq_Pr2;
  Rsrv02 Rsrv1_TPM_Lmp_On_Rq_Pr2;
  c04_0_15_1_SNA_na SQC_TPM_Lmp_On_Rq_Pr2;
  DC_BOOL TPM_IndLmp_On_Rq;
  DC_BOOL TPM_MalfLmp_On_Rq;
} REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt;

# define Rte_TypeDef_REC_TPM_Lmp_On_Rq_old
typedef struct
{
  DC_BOOL TPM_IndLmp_On_Rq_old;
  DC_BOOL TPM_MalfLmp_On_Rq_old;
} REC_TPM_Lmp_On_Rq_old;

# define Rte_TypeDef_REC_Tire_Stat_V2
typedef struct
{
  DC_BOOL Press_Disp_Avl;
  c08_kPa_0_632d5_2d5 TirePress_FL;
  c08_kPa_0_632d5_2d5 TirePress_FR;
  c08_kPa_0_632d5_2d5 TirePress_RL;
  c08_kPa_0_632d5_2d5 TirePress_RR;
  c02_Tire_Stat TireStat_FL;
  c02_Tire_Stat TireStat_FR;
  c02_Tire_Stat TireStat_RL;
  c02_Tire_Stat TireStat_RR;
  c04_TPM_MsgDisp_Rq TPM_MsgDisp_Rq;
  c03_TPM_Stat TPM_Stat;
  c03_TPM_WarnDisp_Rq TPM_WarnDisp_Rq;
} REC_Tire_Stat_V2;

# define Rte_TypeDef_REC_Tire_Temp_V2
typedef struct
{
  c02_Tire_Temp Tire_Temp_Stat_FL;
  c02_Tire_Temp Tire_Temp_Stat_FR;
  c02_Tire_Temp Tire_Temp_Stat_RL;
  c02_Tire_Temp Tire_Temp_Stat_RR;
  c03_Tire_Temp_WarnDisp Tire_Temp_WarnDisp_Rq;
  c08_degC_m50_204_1 TireTemp_FL;
  c08_degC_m50_204_1 TireTemp_FR;
  c08_degC_m50_204_1 TireTemp_RL;
  c08_degC_m50_204_1 TireTemp_RR;
} REC_Tire_Temp_V2;

# define Rte_TypeDef_REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx
typedef struct
{
  c08_CRC_woSNA CRC_WhlPlsCnt_TPM_Pr2;
  Rsrv08 Rsrv2_WhlPlsCnt_TPM_Pr2;
  c04_0_15_1_SNA_na SQC_WhlPlsCnt_TPM_Pr2;
  c08_Impulses_0_254_1 WhlPlsCnt_FL;
  c08_Impulses_0_254_1 WhlPlsCnt_FR;
  c08_Impulses_0_254_1 WhlPlsCnt_RL;
  c08_Impulses_0_254_1 WhlPlsCnt_RR;
  c08_ms_0_254_1 WhlPlsCnt_TmStmp;
  Rsrv04 Rsrv1_WhlPlsCnt_TPM_Pr2;
} REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx;

# define Rte_TypeDef_DT_tCalNvMBlock
typedef struct
{
  DT_aucPosComparePressure aucPosComparePressure;
  UInt32 ulLastCalMileage;
  UInt8 ucPrefFront;
  UInt8 ucPrefRear;
  SInt8 scTref;
  UInt8 ucCalNotAckState;
  UInt8 ucCalRequestState;
  DT_tNvMReservedBytes tCalReserved;
} DT_tCalNvMBlock;

# define Rte_TypeDef_DT_tCodNvMBlock
typedef struct
{
  DT_tLogicalDataPalCod tLogicalDataPalCod;
  DT_tParaTempWarnCod tParaTempWarnCod;
  UInt8 ucPcalMinVaRelativCod;
  UInt8 ucPcalMinHaRelativCod;
  DT_aucPalAbsDelayTimeParam aucPalAbsDelayTimeParam;
  UInt8 ucMeasurementOnOffCod;
  UInt8 ucCoastModeCtrlCount;
  DT_ucKweight ucKweight;
  DT_tNvMReservedBytes tCodReserved;
} DT_tCodNvMBlock;

# define Rte_TypeDef_DT_tDiagNvMBlock0
typedef struct
{
  DT_aucSNRlongTerm aucSNRLongTerm;
  DT_aucReceptionStateWuDCM aucReceptionStateWuDCM;
  DT_tEvcCfgBits tEvcCfgBits;
  DT_aucPalStatsLastCycleWU aucPalStatsLastCycleWU;
  DT_aucPalLocateStatistics aucPalLocateStatistics;
  DT_aucPalStatsLongTermWU aucPalStatsLongTermWU;
  DT_TelStat ushTelStatMissedBlockSum;
  DT_TelStat ushTelStatRxBlocksSum;
  DT_aucStatusInfoWuPrevPos aucStatusInfoWuPrevPos;
  DT_aucStatusInfoWuCounts aucStatusInfoWuCounts;
  DT_aucStatusInfoWuFailReas aucStatusInfoWuFailReas;
  DT_aucStatusInfoWuSensFail aucStatusInfoWuSensFail;
} DT_tDiagNvMBlock0;

# define Rte_TypeDef_DT_tDiagNvMBlock1
typedef struct
{
  DT_tDiagTraceMem tDiagTraceMem;
  UInt8 ucUnexpectedEcuResetCnt;
  DT_tNvMReservedBytes tDiagReserved1;
} DT_tDiagNvMBlock1;

# define Rte_TypeDef_DT_tDiagNvMBlock2
typedef struct
{
  DT_tSensorBatInfo tSensorBatInfo;
  DT_aucMessageMemoryPAL aucMessageMemoryPAL;
  DT_aucTempWarnMessageMemory aucTempWarnMessageMemory;
} DT_tDiagNvMBlock2;

# define Rte_TypeDef_DT_tDiagNvMBlock3
typedef struct
{
  DT_aucActivationMemoryFD aucActivationMemoryFD;
  UInt8 ucAtaErrCnt;
  DT_tNvMReservedBytes tDiagReserved3;
} DT_tDiagNvMBlock3;

# define Rte_TypeDef_DT_tWallocNvMBlock
typedef struct
{
  DT_aucWAParam aucWAHistParam;
  DT_aucWAHistWP aucWAHistWP;
  DT_aucWAHistWP aucWAHistProvWP;
  DT_aulWAHistID aulWAHistID;
  UInt8 ucWAHistSensorState;
  DT_tNvMReservedBytes tWallocReserved;
} DT_tWallocNvMBlock;

# define Rte_TypeDef_DT_tWarnHdlrNvMBlock
typedef struct
{
  DT_ucGlobalWarnLevel ucGlobalWarnLevel;
  DT_aucWheelStatus aucWheelStatus;
  DT_tNvMReservedBytes tWarnReserved;
} DT_tWarnHdlrNvMBlock;

# ifndef RTE_SUPPRESS_UNUSED_DATATYPES

#  define Rte_TypeDef_DT_ucId
typedef uint8 DT_ucId;
#  define DT_ucId_LowerLimit (0U)
#  define DT_ucId_UpperLimit (255U)

#  define Rte_TypeDef_Double
typedef float64 Double;
#  define Double_LowerLimit (-DBL_MAX)
#  define Double_UpperLimit (DBL_MAX)

#  define Rte_TypeDef_Float
typedef float32 Float;
#  define Float_LowerLimit (-FLT_MAX)
#  define Float_UpperLimit (FLT_MAX)

#  define Rte_TypeDef_Rsrv01
typedef uint8 Rsrv01;
#  define Rsrv01_LowerLimit (0U)
#  define Rsrv01_UpperLimit (1U)

#  define Rte_TypeDef_SInt16
typedef sint16 SInt16;
#  define SInt16_LowerLimit (-32768)
#  define SInt16_UpperLimit (32767)

#  define Rte_TypeDef_SInt32
typedef sint32 SInt32;
#  define SInt32_LowerLimit (-2147483648)
#  define SInt32_UpperLimit (2147483647)

#  define Rte_TypeDef_SInt4
typedef sint8 SInt4;
#  define SInt4_LowerLimit (-8)
#  define SInt4_UpperLimit (7)

#  define Rte_TypeDef_UInt4
typedef uint8 UInt4;
#  define UInt4_LowerLimit (0U)
#  define UInt4_UpperLimit (15U)

#  define Rte_TypeDef_ucCoastModeContCount
typedef uint8 ucCoastModeContCount;
#  define ucCoastModeContCount_LowerLimit (0U)
#  define ucCoastModeContCount_UpperLimit (0U)

#  define Rte_TypeDef_c01_NoFault_KeptAwake
typedef uint8 c01_NoFault_KeptAwake;
#  define c01_NoFault_KeptAwake_LowerLimit (0U)
#  define c01_NoFault_KeptAwake_UpperLimit (1U)
#  ifndef I_C01_NOFAULT_KEPTAWAKE_NO_FLT
#   define I_C01_NOFAULT_KEPTAWAKE_NO_FLT (0U)
#  endif
#  ifndef I_C01_NOFAULT_KEPTAWAKE_BUS_FLT_KPT_AWAKE
#   define I_C01_NOFAULT_KEPTAWAKE_BUS_FLT_KPT_AWAKE (1U)
#  endif

#  define Rte_TypeDef_c01_UnitVehSpd
typedef uint8 c01_UnitVehSpd;
#  define c01_UnitVehSpd_LowerLimit (0U)
#  define c01_UnitVehSpd_UpperLimit (1U)
#  ifndef I_C01_UNITVEHSPD_KMH
#   define I_C01_UNITVEHSPD_KMH (0U)
#  endif
#  ifndef I_C01_UNITVEHSPD_MPH
#   define I_C01_UNITVEHSPD_MPH (1U)
#  endif

#  define Rte_TypeDef_c01_UnitVehSpd_IC
typedef uint8 c01_UnitVehSpd_IC;
#  define c01_UnitVehSpd_IC_LowerLimit (0U)
#  define c01_UnitVehSpd_IC_UpperLimit (1U)
#  ifndef I_C01_UNITVEHSPD_IC_KMH_KM
#   define I_C01_UNITVEHSPD_IC_KMH_KM (0U)
#  endif
#  ifndef I_C01_UNITVEHSPD_IC_MPH_MI
#   define I_C01_UNITVEHSPD_IC_MPH_MI (1U)
#  endif

#  define Rte_TypeDef_c02_ContEngRun_Stat
typedef uint8 c02_ContEngRun_Stat;
#  define c02_ContEngRun_Stat_LowerLimit (0U)
#  define c02_ContEngRun_Stat_UpperLimit (3U)
#  define Rte_InvalidValue_c02_ContEngRun_Stat (3U)
#  define InvalidValue_c02_ContEngRun_Stat (3U)
#  ifndef I_C02_CONTENGRUN_STAT_CONT_ENG_RUN_OFF
#   define I_C02_CONTENGRUN_STAT_CONT_ENG_RUN_OFF (0U)
#  endif
#  ifndef I_C02_CONTENGRUN_STAT_CONT_ENG_RUN_ON
#   define I_C02_CONTENGRUN_STAT_CONT_ENG_RUN_ON (1U)
#  endif
#  ifndef I_C02_CONTENGRUN_STAT_NDEF
#   define I_C02_CONTENGRUN_STAT_NDEF (2U)
#  endif
#  ifndef I_C02_CONTENGRUN_STAT_SNA
#   define I_C02_CONTENGRUN_STAT_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_CylCutoff_Stat
typedef uint8 c02_CylCutoff_Stat;
#  define c02_CylCutoff_Stat_LowerLimit (0U)
#  define c02_CylCutoff_Stat_UpperLimit (3U)
#  ifndef I_C02_CYLCUTOFF_STAT_NO_ZAS
#   define I_C02_CYLCUTOFF_STAT_NO_ZAS (0U)
#  endif
#  ifndef I_C02_CYLCUTOFF_STAT_ZAS_RQ
#   define I_C02_CYLCUTOFF_STAT_ZAS_RQ (1U)
#  endif
#  ifndef I_C02_CYLCUTOFF_STAT_ZAS_SHIFT
#   define I_C02_CYLCUTOFF_STAT_ZAS_SHIFT (2U)
#  endif
#  ifndef I_C02_CYLCUTOFF_STAT_ZAS_ACTV
#   define I_C02_CYLCUTOFF_STAT_ZAS_ACTV (3U)
#  endif

#  define Rte_TypeDef_c02_ESL_Lk_Rq
typedef uint8 c02_ESL_Lk_Rq;
#  define c02_ESL_Lk_Rq_LowerLimit (0U)
#  define c02_ESL_Lk_Rq_UpperLimit (3U)
#  ifndef I_C02_ESL_LK_RQ_DEFAULT
#   define I_C02_ESL_LK_RQ_DEFAULT (0U)
#  endif
#  ifndef I_C02_ESL_LK_RQ_ORC_RQ
#   define I_C02_ESL_LK_RQ_ORC_RQ (1U)
#  endif
#  ifndef I_C02_ESL_LK_RQ_SAM_F_RQ
#   define I_C02_ESL_LK_RQ_SAM_F_RQ (2U)
#  endif
#  ifndef I_C02_ESL_LK_RQ_ORC_SAM_F_RQ
#   define I_C02_ESL_LK_RQ_ORC_SAM_F_RQ (3U)
#  endif

#  define Rte_TypeDef_c02_EVC_AddEquip
typedef uint8 c02_EVC_AddEquip;
#  define c02_EVC_AddEquip_LowerLimit (0U)
#  define c02_EVC_AddEquip_UpperLimit (3U)
#  ifndef I_C02_EVC_ADDEQUIP_VAR_0
#   define I_C02_EVC_ADDEQUIP_VAR_0 (0U)
#  endif
#  ifndef I_C02_EVC_ADDEQUIP_OTHER
#   define I_C02_EVC_ADDEQUIP_OTHER (3U)
#  endif

#  define Rte_TypeDef_c02_FTW_On_Rq
typedef uint8 c02_FTW_On_Rq;
#  define c02_FTW_On_Rq_LowerLimit (0U)
#  define c02_FTW_On_Rq_UpperLimit (3U)
#  define Rte_InvalidValue_c02_FTW_On_Rq (3U)
#  define InvalidValue_c02_FTW_On_Rq (3U)
#  ifndef I_C02_FTW_ON_RQ_IDLE
#   define I_C02_FTW_ON_RQ_IDLE (0U)
#  endif
#  ifndef I_C02_FTW_ON_RQ_OFF
#   define I_C02_FTW_ON_RQ_OFF (1U)
#  endif
#  ifndef I_C02_FTW_ON_RQ_ON
#   define I_C02_FTW_ON_RQ_ON (2U)
#  endif
#  ifndef I_C02_FTW_ON_RQ_SNA
#   define I_C02_FTW_ON_RQ_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_Inact_Act
typedef uint8 c02_Inact_Act;
#  define c02_Inact_Act_LowerLimit (0U)
#  define c02_Inact_Act_UpperLimit (3U)
#  define Rte_InvalidValue_c02_Inact_Act (3U)
#  define InvalidValue_c02_Inact_Act (3U)
#  ifndef I_C02_INACT_ACT_INACTIVE
#   define I_C02_INACT_ACT_INACTIVE (0U)
#  endif
#  ifndef I_C02_INACT_ACT_ACTIVE
#   define I_C02_INACT_ACT_ACTIVE (1U)
#  endif
#  ifndef I_C02_INACT_ACT_NDEF2
#   define I_C02_INACT_ACT_NDEF2 (2U)
#  endif
#  ifndef I_C02_INACT_ACT_SNA
#   define I_C02_INACT_ACT_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_Ndef_NoExt_Ext
typedef uint8 c02_Ndef_NoExt_Ext;
#  define c02_Ndef_NoExt_Ext_LowerLimit (0U)
#  define c02_Ndef_NoExt_Ext_UpperLimit (3U)
#  define Rte_InvalidValue_c02_Ndef_NoExt_Ext (3U)
#  define InvalidValue_c02_Ndef_NoExt_Ext (3U)
#  ifndef I_C02_NDEF_NOEXT_EXT_NDEF0
#   define I_C02_NDEF_NOEXT_EXT_NDEF0 (0U)
#  endif
#  ifndef I_C02_NDEF_NOEXT_EXT_NO_EXT
#   define I_C02_NDEF_NOEXT_EXT_NO_EXT (1U)
#  endif
#  ifndef I_C02_NDEF_NOEXT_EXT_EXT
#   define I_C02_NDEF_NOEXT_EXT_EXT (2U)
#  endif
#  ifndef I_C02_NDEF_NOEXT_EXT_SNA
#   define I_C02_NDEF_NOEXT_EXT_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_NoDisp_Act_NAct
typedef uint8 c02_NoDisp_Act_NAct;
#  define c02_NoDisp_Act_NAct_LowerLimit (0U)
#  define c02_NoDisp_Act_NAct_UpperLimit (3U)
#  define Rte_InvalidValue_c02_NoDisp_Act_NAct (3U)
#  define InvalidValue_c02_NoDisp_Act_NAct (3U)
#  ifndef I_C02_NODISP_ACT_NACT_NO_DISP_RQ
#   define I_C02_NODISP_ACT_NACT_NO_DISP_RQ (0U)
#  endif
#  ifndef I_C02_NODISP_ACT_NACT_PRODMD_ACTV
#   define I_C02_NODISP_ACT_NACT_PRODMD_ACTV (1U)
#  endif
#  ifndef I_C02_NODISP_ACT_NACT_PRODMD_NOT_ACTV
#   define I_C02_NODISP_ACT_NACT_PRODMD_NOT_ACTV (2U)
#  endif
#  ifndef I_C02_NODISP_ACT_NACT_SNA
#   define I_C02_NODISP_ACT_NACT_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_OFC_Stat
typedef uint8 c02_OFC_Stat;
#  define c02_OFC_Stat_LowerLimit (0U)
#  define c02_OFC_Stat_UpperLimit (3U)
#  define Rte_InvalidValue_c02_OFC_Stat (3U)
#  define InvalidValue_c02_OFC_Stat (3U)
#  ifndef I_C02_OFC_STAT_IDLE
#   define I_C02_OFC_STAT_IDLE (0U)
#  endif
#  ifndef I_C02_OFC_STAT_FULL
#   define I_C02_OFC_STAT_FULL (1U)
#  endif
#  ifndef I_C02_OFC_STAT_PART
#   define I_C02_OFC_STAT_PART (2U)
#  endif
#  ifndef I_C02_OFC_STAT_SNA
#   define I_C02_OFC_STAT_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_Off_On
typedef uint8 c02_Off_On;
#  define c02_Off_On_LowerLimit (0U)
#  define c02_Off_On_UpperLimit (3U)
#  define Rte_InvalidValue_c02_Off_On (3U)
#  define InvalidValue_c02_Off_On (3U)
#  ifndef I_C02_OFF_ON_OFF
#   define I_C02_OFF_ON_OFF (0U)
#  endif
#  ifndef I_C02_OFF_ON_ON
#   define I_C02_OFF_ON_ON (1U)
#  endif
#  ifndef I_C02_OFF_ON_NDEF2
#   define I_C02_OFF_ON_NDEF2 (2U)
#  endif
#  ifndef I_C02_OFF_ON_SNA
#   define I_C02_OFF_ON_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_Preview_Md_Rq
typedef uint8 c02_Preview_Md_Rq;
#  define c02_Preview_Md_Rq_LowerLimit (0U)
#  define c02_Preview_Md_Rq_UpperLimit (3U)
#  define Rte_InvalidValue_c02_Preview_Md_Rq (3U)
#  define InvalidValue_c02_Preview_Md_Rq (3U)
#  ifndef I_C02_PREVIEW_MD_RQ_PREVIEW_ON
#   define I_C02_PREVIEW_MD_RQ_PREVIEW_ON (0U)
#  endif
#  ifndef I_C02_PREVIEW_MD_RQ_PREVIEW_OFF
#   define I_C02_PREVIEW_MD_RQ_PREVIEW_OFF (1U)
#  endif
#  ifndef I_C02_PREVIEW_MD_RQ_NDEF2
#   define I_C02_PREVIEW_MD_RQ_NDEF2 (2U)
#  endif
#  ifndef I_C02_PREVIEW_MD_RQ_SNA
#   define I_C02_PREVIEW_MD_RQ_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_RemSt_IgnCtrl_Info
typedef uint8 c02_RemSt_IgnCtrl_Info;
#  define c02_RemSt_IgnCtrl_Info_LowerLimit (0U)
#  define c02_RemSt_IgnCtrl_Info_UpperLimit (3U)
#  define Rte_InvalidValue_c02_RemSt_IgnCtrl_Info (3U)
#  define InvalidValue_c02_RemSt_IgnCtrl_Info (3U)
#  ifndef I_C02_REMST_IGNCTRL_INFO_NO_RQ
#   define I_C02_REMST_IGNCTRL_INFO_NO_RQ (0U)
#  endif
#  ifndef I_C02_REMST_IGNCTRL_INFO_PRECON
#   define I_C02_REMST_IGNCTRL_INFO_PRECON (1U)
#  endif
#  ifndef I_C02_REMST_IGNCTRL_INFO_BAT_CHRG
#   define I_C02_REMST_IGNCTRL_INFO_BAT_CHRG (2U)
#  endif
#  ifndef I_C02_REMST_IGNCTRL_INFO_SNA
#   define I_C02_REMST_IGNCTRL_INFO_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_SPCR_Conf
typedef uint8 c02_SPCR_Conf;
#  define c02_SPCR_Conf_LowerLimit (0U)
#  define c02_SPCR_Conf_UpperLimit (3U)
#  define Rte_InvalidValue_c02_SPCR_Conf (3U)
#  define InvalidValue_c02_SPCR_Conf (3U)
#  ifndef I_C02_SPCR_CONF_NOT_CONF
#   define I_C02_SPCR_CONF_NOT_CONF (0U)
#  endif
#  ifndef I_C02_SPCR_CONF_HOLD_NO_SBW
#   define I_C02_SPCR_CONF_HOLD_NO_SBW (1U)
#  endif
#  ifndef I_C02_SPCR_CONF_HOLD_AND_SBW
#   define I_C02_SPCR_CONF_HOLD_AND_SBW (2U)
#  endif
#  ifndef I_C02_SPCR_CONF_SNA
#   define I_C02_SPCR_CONF_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_Sleep_Local_Ext
typedef uint8 c02_Sleep_Local_Ext;
#  define c02_Sleep_Local_Ext_LowerLimit (0U)
#  define c02_Sleep_Local_Ext_UpperLimit (3U)
#  define Rte_InvalidValue_c02_Sleep_Local_Ext (3U)
#  define InvalidValue_c02_Sleep_Local_Ext (3U)
#  ifndef I_C02_SLEEP_LOCAL_EXT_SLEEP
#   define I_C02_SLEEP_LOCAL_EXT_SLEEP (0U)
#  endif
#  ifndef I_C02_SLEEP_LOCAL_EXT_LOCAL
#   define I_C02_SLEEP_LOCAL_EXT_LOCAL (1U)
#  endif
#  ifndef I_C02_SLEEP_LOCAL_EXT_EXT
#   define I_C02_SLEEP_LOCAL_EXT_EXT (2U)
#  endif
#  ifndef I_C02_SLEEP_LOCAL_EXT_SNA
#   define I_C02_SLEEP_LOCAL_EXT_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_StStyle
typedef uint8 c02_StStyle;
#  define c02_StStyle_LowerLimit (0U)
#  define c02_StStyle_UpperLimit (3U)
#  define Rte_InvalidValue_c02_StStyle (3U)
#  define InvalidValue_c02_StStyle (3U)
#  ifndef I_C02_STSTYLE_NDEF0
#   define I_C02_STSTYLE_NDEF0 (0U)
#  endif
#  ifndef I_C02_STSTYLE_LHD
#   define I_C02_STSTYLE_LHD (1U)
#  endif
#  ifndef I_C02_STSTYLE_RHD
#   define I_C02_STSTYLE_RHD (2U)
#  endif
#  ifndef I_C02_STSTYLE_SNA
#   define I_C02_STSTYLE_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_UnitPress_Rq
typedef uint8 c02_UnitPress_Rq;
#  define c02_UnitPress_Rq_LowerLimit (0U)
#  define c02_UnitPress_Rq_UpperLimit (3U)
#  define Rte_InvalidValue_c02_UnitPress_Rq (3U)
#  define InvalidValue_c02_UnitPress_Rq (3U)
#  ifndef I_C02_UNITPRESS_RQ_BAR
#   define I_C02_UNITPRESS_RQ_BAR (0U)
#  endif
#  ifndef I_C02_UNITPRESS_RQ_PSI
#   define I_C02_UNITPRESS_RQ_PSI (1U)
#  endif
#  ifndef I_C02_UNITPRESS_RQ_KPA
#   define I_C02_UNITPRESS_RQ_KPA (2U)
#  endif
#  ifndef I_C02_UNITPRESS_RQ_SNA
#   define I_C02_UNITPRESS_RQ_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_UnitTemp_Rq
typedef uint8 c02_UnitTemp_Rq;
#  define c02_UnitTemp_Rq_LowerLimit (0U)
#  define c02_UnitTemp_Rq_UpperLimit (3U)
#  define Rte_InvalidValue_c02_UnitTemp_Rq (3U)
#  define InvalidValue_c02_UnitTemp_Rq (3U)
#  ifndef I_C02_UNITTEMP_RQ_CELSIUS
#   define I_C02_UNITTEMP_RQ_CELSIUS (0U)
#  endif
#  ifndef I_C02_UNITTEMP_RQ_FAHRENHEIT
#   define I_C02_UNITTEMP_RQ_FAHRENHEIT (1U)
#  endif
#  ifndef I_C02_UNITTEMP_RQ_NDEF2
#   define I_C02_UNITTEMP_RQ_NDEF2 (2U)
#  endif
#  ifndef I_C02_UNITTEMP_RQ_SNA
#   define I_C02_UNITTEMP_RQ_SNA (3U)
#  endif

#  define Rte_TypeDef_c02_Vprzr_DryVnTmr_Stat
typedef uint8 c02_Vprzr_DryVnTmr_Stat;
#  define c02_Vprzr_DryVnTmr_Stat_LowerLimit (0U)
#  define c02_Vprzr_DryVnTmr_Stat_UpperLimit (3U)
#  define Rte_InvalidValue_c02_Vprzr_DryVnTmr_Stat (3U)
#  define InvalidValue_c02_Vprzr_DryVnTmr_Stat (3U)
#  ifndef I_C02_VPRZR_DRYVNTMR_STAT_INACTV
#   define I_C02_VPRZR_DRYVNTMR_STAT_INACTV (0U)
#  endif
#  ifndef I_C02_VPRZR_DRYVNTMR_STAT_ACTV
#   define I_C02_VPRZR_DRYVNTMR_STAT_ACTV (1U)
#  endif
#  ifndef I_C02_VPRZR_DRYVNTMR_STAT_EXPIRED
#   define I_C02_VPRZR_DRYVNTMR_STAT_EXPIRED (2U)
#  endif
#  ifndef I_C02_VPRZR_DRYVNTMR_STAT_SNA
#   define I_C02_VPRZR_DRYVNTMR_STAT_SNA (3U)
#  endif

#  define Rte_TypeDef_c03_EVC_HVAC_Style
typedef uint8 c03_EVC_HVAC_Style;
#  define c03_EVC_HVAC_Style_LowerLimit (0U)
#  define c03_EVC_HVAC_Style_UpperLimit (7U)
#  ifndef I_C03_EVC_HVAC_STYLE_AIRCOND
#   define I_C03_EVC_HVAC_STYLE_AIRCOND (0U)
#  endif
#  ifndef I_C03_EVC_HVAC_STYLE_AUTOCLIMATECTRL
#   define I_C03_EVC_HVAC_STYLE_AUTOCLIMATECTRL (1U)
#  endif
#  ifndef I_C03_EVC_HVAC_STYLE_OTHER
#   define I_C03_EVC_HVAC_STYLE_OTHER (7U)
#  endif

#  define Rte_TypeDef_c03_EVC_RoofStyle
typedef uint8 c03_EVC_RoofStyle;
#  define c03_EVC_RoofStyle_LowerLimit (0U)
#  define c03_EVC_RoofStyle_UpperLimit (7U)
#  ifndef I_C03_EVC_ROOFSTYLE_PANORAMAROOF
#   define I_C03_EVC_ROOFSTYLE_PANORAMAROOF (0U)
#  endif
#  ifndef I_C03_EVC_ROOFSTYLE_SUNROOF
#   define I_C03_EVC_ROOFSTYLE_SUNROOF (1U)
#  endif
#  ifndef I_C03_EVC_ROOFSTYLE_GLASS_VAR_TRANSP
#   define I_C03_EVC_ROOFSTYLE_GLASS_VAR_TRANSP (2U)
#  endif
#  ifndef I_C03_EVC_ROOFSTYLE_SOLAR_MODULE
#   define I_C03_EVC_ROOFSTYLE_SOLAR_MODULE (3U)
#  endif
#  ifndef I_C03_EVC_ROOFSTYLE_OTHER
#   define I_C03_EVC_ROOFSTYLE_OTHER (7U)
#  endif

#  define Rte_TypeDef_c03_ExtFanTempIC_State
typedef uint8 c03_ExtFanTempIC_State;
#  define c03_ExtFanTempIC_State_LowerLimit (0U)
#  define c03_ExtFanTempIC_State_UpperLimit (7U)
#  define Rte_InvalidValue_c03_ExtFanTempIC_State (7U)
#  define InvalidValue_c03_ExtFanTempIC_State (7U)
#  ifndef I_C03_EXTFANTEMPIC_STATE_NORMAL
#   define I_C03_EXTFANTEMPIC_STATE_NORMAL (0U)
#  endif
#  ifndef I_C03_EXTFANTEMPIC_STATE_INCREASED
#   define I_C03_EXTFANTEMPIC_STATE_INCREASED (1U)
#  endif
#  ifndef I_C03_EXTFANTEMPIC_STATE_CRITICAL
#   define I_C03_EXTFANTEMPIC_STATE_CRITICAL (2U)
#  endif
#  ifndef I_C03_EXTFANTEMPIC_STATE_CATASTROPHIC
#   define I_C03_EXTFANTEMPIC_STATE_CATASTROPHIC (3U)
#  endif
#  ifndef I_C03_EXTFANTEMPIC_STATE_SNA
#   define I_C03_EXTFANTEMPIC_STATE_SNA (7U)
#  endif

#  define Rte_TypeDef_c03_Mobile_Chrg_Rq
typedef uint8 c03_Mobile_Chrg_Rq;
#  define c03_Mobile_Chrg_Rq_LowerLimit (0U)
#  define c03_Mobile_Chrg_Rq_UpperLimit (3U)
#  define Rte_InvalidValue_c03_Mobile_Chrg_Rq (3U)
#  define InvalidValue_c03_Mobile_Chrg_Rq (3U)
#  ifndef I_C03_MOBILE_CHRG_RQ_DO_NOT_CHARGE
#   define I_C03_MOBILE_CHRG_RQ_DO_NOT_CHARGE (0U)
#  endif
#  ifndef I_C03_MOBILE_CHRG_RQ_CHARGE
#   define I_C03_MOBILE_CHRG_RQ_CHARGE (1U)
#  endif
#  ifndef I_C03_MOBILE_CHRG_RQ_NDEF2
#   define I_C03_MOBILE_CHRG_RQ_NDEF2 (2U)
#  endif
#  ifndef I_C03_MOBILE_CHRG_RQ_SNA
#   define I_C03_MOBILE_CHRG_RQ_SNA (3U)
#  endif

#  define Rte_TypeDef_c03_PN14_EHC_Prio_Rq
typedef uint8 c03_PN14_EHC_Prio_Rq;
#  define c03_PN14_EHC_Prio_Rq_LowerLimit (0U)
#  define c03_PN14_EHC_Prio_Rq_UpperLimit (7U)
#  define Rte_InvalidValue_c03_PN14_EHC_Prio_Rq (7U)
#  define InvalidValue_c03_PN14_EHC_Prio_Rq (7U)
#  ifndef I_C03_PN14_EHC_PRIO_RQ_OFF
#   define I_C03_PN14_EHC_PRIO_RQ_OFF (0U)
#  endif
#  ifndef I_C03_PN14_EHC_PRIO_RQ_EHC_PRIO1
#   define I_C03_PN14_EHC_PRIO_RQ_EHC_PRIO1 (1U)
#  endif
#  ifndef I_C03_PN14_EHC_PRIO_RQ_EHC_PRIO2
#   define I_C03_PN14_EHC_PRIO_RQ_EHC_PRIO2 (2U)
#  endif
#  ifndef I_C03_PN14_EHC_PRIO_RQ_EHC_PRIO3
#   define I_C03_PN14_EHC_PRIO_RQ_EHC_PRIO3 (3U)
#  endif
#  ifndef I_C03_PN14_EHC_PRIO_RQ_NDEF4
#   define I_C03_PN14_EHC_PRIO_RQ_NDEF4 (4U)
#  endif
#  ifndef I_C03_PN14_EHC_PRIO_RQ_NDEF5
#   define I_C03_PN14_EHC_PRIO_RQ_NDEF5 (5U)
#  endif
#  ifndef I_C03_PN14_EHC_PRIO_RQ_NDEF6
#   define I_C03_PN14_EHC_PRIO_RQ_NDEF6 (6U)
#  endif
#  ifndef I_C03_PN14_EHC_PRIO_RQ_SNA
#   define I_C03_PN14_EHC_PRIO_RQ_SNA (7U)
#  endif

#  define Rte_TypeDef_c03_TransMdDisp_Rq
typedef uint8 c03_TransMdDisp_Rq;
#  define c03_TransMdDisp_Rq_LowerLimit (0U)
#  define c03_TransMdDisp_Rq_UpperLimit (7U)
#  define Rte_InvalidValue_c03_TransMdDisp_Rq (7U)
#  define InvalidValue_c03_TransMdDisp_Rq (7U)
#  ifndef I_C03_TRANSMDDISP_RQ_NO_DISP_RQ
#   define I_C03_TRANSMDDISP_RQ_NO_DISP_RQ (0U)
#  endif
#  ifndef I_C03_TRANSMDDISP_RQ_ACTV_HI
#   define I_C03_TRANSMDDISP_RQ_ACTV_HI (1U)
#  endif
#  ifndef I_C03_TRANSMDDISP_RQ_ACTV_MID
#   define I_C03_TRANSMDDISP_RQ_ACTV_MID (2U)
#  endif
#  ifndef I_C03_TRANSMDDISP_RQ_ACTV_LO
#   define I_C03_TRANSMDDISP_RQ_ACTV_LO (3U)
#  endif
#  ifndef I_C03_TRANSMDDISP_RQ_ACTV_IDLE
#   define I_C03_TRANSMDDISP_RQ_ACTV_IDLE (4U)
#  endif
#  ifndef I_C03_TRANSMDDISP_RQ_TEMP_OFF
#   define I_C03_TRANSMDDISP_RQ_TEMP_OFF (5U)
#  endif
#  ifndef I_C03_TRANSMDDISP_RQ_NDEF
#   define I_C03_TRANSMDDISP_RQ_NDEF (6U)
#  endif
#  ifndef I_C03_TRANSMDDISP_RQ_SNA
#   define I_C03_TRANSMDDISP_RQ_SNA (7U)
#  endif

#  define Rte_TypeDef_c03_WeekDay_UA
typedef uint8 c03_WeekDay_UA;
#  define c03_WeekDay_UA_LowerLimit (0U)
#  define c03_WeekDay_UA_UpperLimit (7U)
#  ifndef I_C03_WEEKDAY_UA_MONDAY
#   define I_C03_WEEKDAY_UA_MONDAY (0U)
#  endif
#  ifndef I_C03_WEEKDAY_UA_TUESDAY
#   define I_C03_WEEKDAY_UA_TUESDAY (1U)
#  endif
#  ifndef I_C03_WEEKDAY_UA_WEDNESDAY
#   define I_C03_WEEKDAY_UA_WEDNESDAY (2U)
#  endif
#  ifndef I_C03_WEEKDAY_UA_THURSDAY
#   define I_C03_WEEKDAY_UA_THURSDAY (3U)
#  endif
#  ifndef I_C03_WEEKDAY_UA_FRIDAY
#   define I_C03_WEEKDAY_UA_FRIDAY (4U)
#  endif
#  ifndef I_C03_WEEKDAY_UA_SATURDAY
#   define I_C03_WEEKDAY_UA_SATURDAY (5U)
#  endif
#  ifndef I_C03_WEEKDAY_UA_SUNDAY
#   define I_C03_WEEKDAY_UA_SUNDAY (6U)
#  endif
#  ifndef I_C03_WEEKDAY_UA_UNAVAILABLE
#   define I_C03_WEEKDAY_UA_UNAVAILABLE (7U)
#  endif

#  define Rte_TypeDef_c04_0_7_1
typedef uint8 c04_0_7_1;
#  define c04_0_7_1_LowerLimit (0U)
#  define c04_0_7_1_UpperLimit (15U)
#  define Rte_InvalidValue_c04_0_7_1 (15U)
#  define InvalidValue_c04_0_7_1 (15U)
#  ifndef I_C04_0_7_1_SNA
#   define I_C04_0_7_1_SNA (15U)
#  endif

#  define Rte_TypeDef_c04_EVC_HL_Style
typedef uint8 c04_EVC_HL_Style;
#  define c04_EVC_HL_Style_LowerLimit (0U)
#  define c04_EVC_HL_Style_UpperLimit (15U)
#  ifndef I_C04_EVC_HL_STYLE_BI_XEN_RHT
#   define I_C04_EVC_HL_STYLE_BI_XEN_RHT (0U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_BI_XEN_LHT
#   define I_C04_EVC_HL_STYLE_BI_XEN_LHT (1U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_BI_XEN_ACURV_RHT
#   define I_C04_EVC_HL_STYLE_BI_XEN_ACURV_RHT (2U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_BI_XEN_ACURV_LHT
#   define I_C04_EVC_HL_STYLE_BI_XEN_ACURV_LHT (3U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_BI_XEN_INTLGT_RHT
#   define I_C04_EVC_HL_STYLE_BI_XEN_INTLGT_RHT (4U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_BI_XEN_INTLGT_LHT
#   define I_C04_EVC_HL_STYLE_BI_XEN_INTLGT_LHT (5U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_LED_STAT_LHT
#   define I_C04_EVC_HL_STYLE_LED_STAT_LHT (6U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_LED_STAT_RHT
#   define I_C04_EVC_HL_STYLE_LED_STAT_RHT (7U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_LED_DYN_SAE_RHT
#   define I_C04_EVC_HL_STYLE_LED_DYN_SAE_RHT (8U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_LED_DYN_LHT
#   define I_C04_EVC_HL_STYLE_LED_DYN_LHT (9U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_LED_DYN_RHT
#   define I_C04_EVC_HL_STYLE_LED_DYN_RHT (10U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_HEADLIGHT_LHT
#   define I_C04_EVC_HL_STYLE_HEADLIGHT_LHT (11U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_HEADLIGHT_RHT
#   define I_C04_EVC_HL_STYLE_HEADLIGHT_RHT (12U)
#  endif
#  ifndef I_C04_EVC_HL_STYLE_OTHER
#   define I_C04_EVC_HL_STYLE_OTHER (15U)
#  endif

#  define Rte_TypeDef_c04_EVC_TxStyle
typedef uint8 c04_EVC_TxStyle;
#  define c04_EVC_TxStyle_LowerLimit (0U)
#  define c04_EVC_TxStyle_UpperLimit (15U)
#  ifndef I_C04_EVC_TXSTYLE_MANUAL_6
#   define I_C04_EVC_TXSTYLE_MANUAL_6 (0U)
#  endif
#  ifndef I_C04_EVC_TXSTYLE_AUTOM_5
#   define I_C04_EVC_TXSTYLE_AUTOM_5 (1U)
#  endif
#  ifndef I_C04_EVC_TXSTYLE_AUTOM_7
#   define I_C04_EVC_TXSTYLE_AUTOM_7 (2U)
#  endif
#  ifndef I_C04_EVC_TXSTYLE_AUTOM_9
#   define I_C04_EVC_TXSTYLE_AUTOM_9 (3U)
#  endif
#  ifndef I_C04_EVC_TXSTYLE_MANUAL_6_NSG2
#   define I_C04_EVC_TXSTYLE_MANUAL_6_NSG2 (4U)
#  endif
#  ifndef I_C04_EVC_TXSTYLE_AUTOM_7_DCT
#   define I_C04_EVC_TXSTYLE_AUTOM_7_DCT (5U)
#  endif
#  ifndef I_C04_EVC_TXSTYLE_AUTOM_9_DCT
#   define I_C04_EVC_TXSTYLE_AUTOM_9_DCT (6U)
#  endif
#  ifndef I_C04_EVC_TXSTYLE_OTHER
#   define I_C04_EVC_TXSTYLE_OTHER (15U)
#  endif

#  define Rte_TypeDef_c05_EVC_HU_Style
typedef uint8 c05_EVC_HU_Style;
#  define c05_EVC_HU_Style_LowerLimit (0U)
#  define c05_EVC_HU_Style_UpperLimit (31U)
#  ifndef I_C05_EVC_HU_STYLE_CMD_APS
#   define I_C05_EVC_HU_STYLE_CMD_APS (0U)
#  endif
#  ifndef I_C05_EVC_HU_STYLE_AUDIO_20
#   define I_C05_EVC_HU_STYLE_AUDIO_20 (1U)
#  endif
#  ifndef I_C05_EVC_HU_STYLE_HU_USB
#   define I_C05_EVC_HU_STYLE_HU_USB (2U)
#  endif
#  ifndef I_C05_EVC_HU_STYLE_HU_USB_NTG45
#   define I_C05_EVC_HU_STYLE_HU_USB_NTG45 (3U)
#  endif
#  ifndef I_C05_EVC_HU_STYLE_OTHER
#   define I_C05_EVC_HU_STYLE_OTHER (31U)
#  endif

#  define Rte_TypeDef_c05_EVC_VehLineYear
typedef uint8 c05_EVC_VehLineYear;
#  define c05_EVC_VehLineYear_LowerLimit (0U)
#  define c05_EVC_VehLineYear_UpperLimit (31U)
#  define Rte_InvalidValue_c05_EVC_VehLineYear (31U)
#  define InvalidValue_c05_EVC_VehLineYear (31U)
#  ifndef I_C05_EVC_VEHLINEYEAR_SNA
#   define I_C05_EVC_VEHLINEYEAR_SNA (31U)
#  endif

#  define Rte_TypeDef_c07_0_111_1_SNA
typedef uint8 c07_0_111_1_SNA;
#  define c07_0_111_1_SNA_LowerLimit (0U)
#  define c07_0_111_1_SNA_UpperLimit (127U)
#  define Rte_InvalidValue_c07_0_111_1_SNA (127U)
#  define InvalidValue_c07_0_111_1_SNA (127U)
#  ifndef I_C07_0_111_1_SNA_SNA
#   define I_C07_0_111_1_SNA_SNA (127U)
#  endif

#  define Rte_TypeDef_c07_m64_62_1
typedef uint8 c07_m64_62_1;
#  define c07_m64_62_1_LowerLimit (0U)
#  define c07_m64_62_1_UpperLimit (127U)
#  define Rte_InvalidValue_c07_m64_62_1 (127U)
#  define InvalidValue_c07_m64_62_1 (127U)
#  ifndef I_C07_M64_62_1_SNA
#   define I_C07_M64_62_1_SNA (127U)
#  endif

#  define Rte_TypeDef_c07_per_0to100_1_SNA
typedef uint8 c07_per_0to100_1_SNA;
#  define c07_per_0to100_1_SNA_LowerLimit (0U)
#  define c07_per_0to100_1_SNA_UpperLimit (127U)
#  define Rte_InvalidValue_c07_per_0to100_1_SNA (127U)
#  define InvalidValue_c07_per_0to100_1_SNA (127U)
#  ifndef I_C07_PER_0TO100_1_SNA_SNA
#   define I_C07_PER_0TO100_1_SNA_SNA (127U)
#  endif

#  define Rte_TypeDef_c08_0_1k98_0k0078
typedef uint8 c08_0_1k98_0k0078;
#  define c08_0_1k98_0k0078_LowerLimit (0U)
#  define c08_0_1k98_0k0078_UpperLimit (255U)
#  define Rte_InvalidValue_c08_0_1k98_0k0078 (255U)
#  define InvalidValue_c08_0_1k98_0k0078 (255U)
#  ifndef I_C08_0_1K98_0K0078_SNA
#   define I_C08_0_1K98_0K0078_SNA (255U)
#  endif

#  define Rte_TypeDef_c08_1_6_0k01969
typedef uint8 c08_1_6_0k01969;
#  define c08_1_6_0k01969_LowerLimit (0U)
#  define c08_1_6_0k01969_UpperLimit (255U)
#  define Rte_InvalidValue_c08_1_6_0k01969 (255U)
#  define InvalidValue_c08_1_6_0k01969 (255U)
#  ifndef I_C08_1_6_0K01969_SNA
#   define I_C08_1_6_0K01969_SNA (255U)
#  endif

#  define Rte_TypeDef_c08_Days_0_100_1
typedef uint8 c08_Days_0_100_1;
#  define c08_Days_0_100_1_LowerLimit (0U)
#  define c08_Days_0_100_1_UpperLimit (255U)
#  define Rte_InvalidValue_c08_Days_0_100_1 (255U)
#  define InvalidValue_c08_Days_0_100_1 (255U)
#  ifndef I_C08_DAYS_0_100_1_SNA
#   define I_C08_DAYS_0_100_1_SNA (255U)
#  endif

#  define Rte_TypeDef_c08_EVC_Country
typedef uint8 c08_EVC_Country;
#  define c08_EVC_Country_LowerLimit (0U)
#  define c08_EVC_Country_UpperLimit (255U)
#  ifndef I_C08_EVC_COUNTRY_DEU
#   define I_C08_EVC_COUNTRY_DEU (0U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_DEU_IMPORT
#   define I_C08_EVC_COUNTRY_DEU_IMPORT (1U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_BEL
#   define I_C08_EVC_COUNTRY_BEL (20U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_DNK
#   define I_C08_EVC_COUNTRY_DNK (21U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_FRA
#   define I_C08_EVC_COUNTRY_FRA (22U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_GBR
#   define I_C08_EVC_COUNTRY_GBR (24U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_IRL
#   define I_C08_EVC_COUNTRY_IRL (25U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_ITA
#   define I_C08_EVC_COUNTRY_ITA (26U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_LUX
#   define I_C08_EVC_COUNTRY_LUX (28U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_NDL
#   define I_C08_EVC_COUNTRY_NDL (30U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_AUT
#   define I_C08_EVC_COUNTRY_AUT (31U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_PRT
#   define I_C08_EVC_COUNTRY_PRT (32U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_SWE
#   define I_C08_EVC_COUNTRY_SWE (33U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_CHE
#   define I_C08_EVC_COUNTRY_CHE (34U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_ESP
#   define I_C08_EVC_COUNTRY_ESP (35U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_ZAF
#   define I_C08_EVC_COUNTRY_ZAF (53U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_CAN
#   define I_C08_EVC_COUNTRY_CAN (70U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_USA
#   define I_C08_EVC_COUNTRY_USA (71U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_BHR
#   define I_C08_EVC_COUNTRY_BHR (90U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_QAT
#   define I_C08_EVC_COUNTRY_QAT (91U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_TWN
#   define I_C08_EVC_COUNTRY_TWN (92U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_CHN
#   define I_C08_EVC_COUNTRY_CHN (93U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_HKG
#   define I_C08_EVC_COUNTRY_HKG (94U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_MAC
#   define I_C08_EVC_COUNTRY_MAC (95U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_JPN
#   define I_C08_EVC_COUNTRY_JPN (96U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_KOR
#   define I_C08_EVC_COUNTRY_KOR (97U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_KWT
#   define I_C08_EVC_COUNTRY_KWT (98U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_MYS
#   define I_C08_EVC_COUNTRY_MYS (99U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_OMN
#   define I_C08_EVC_COUNTRY_OMN (100U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_MNG
#   define I_C08_EVC_COUNTRY_MNG (101U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_SAU
#   define I_C08_EVC_COUNTRY_SAU (102U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_SGP
#   define I_C08_EVC_COUNTRY_SGP (103U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_AE_AZ
#   define I_C08_EVC_COUNTRY_AE_AZ (104U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_THA
#   define I_C08_EVC_COUNTRY_THA (105U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_AE_DU
#   define I_C08_EVC_COUNTRY_AE_DU (106U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_AUS
#   define I_C08_EVC_COUNTRY_AUS (120U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_PNG
#   define I_C08_EVC_COUNTRY_PNG (122U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_NZL
#   define I_C08_EVC_COUNTRY_NZL (123U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_PYF
#   define I_C08_EVC_COUNTRY_PYF (126U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_NCL
#   define I_C08_EVC_COUNTRY_NCL (127U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_TON
#   define I_C08_EVC_COUNTRY_TON (128U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_WSM
#   define I_C08_EVC_COUNTRY_WSM (129U)
#  endif
#  ifndef I_C08_EVC_COUNTRY_OTHER
#   define I_C08_EVC_COUNTRY_OTHER (255U)
#  endif

#  define Rte_TypeDef_c08_EngStyle
typedef uint8 c08_EngStyle;
#  define c08_EngStyle_LowerLimit (0U)
#  define c08_EngStyle_UpperLimit (255U)
#  define Rte_InvalidValue_c08_EngStyle (255U)
#  define InvalidValue_c08_EngStyle (255U)
#  ifndef I_C08_ENGSTYLE_M275E55
#   define I_C08_ENGSTYLE_M275E55 (0U)
#  endif
#  ifndef I_C08_ENGSTYLE_M273E55
#   define I_C08_ENGSTYLE_M273E55 (1U)
#  endif
#  ifndef I_C08_ENGSTYLE_M273E46
#   define I_C08_ENGSTYLE_M273E46 (2U)
#  endif
#  ifndef I_C08_ENGSTYLE_M272E35
#   define I_C08_ENGSTYLE_M272E35 (3U)
#  endif
#  ifndef I_C08_ENGSTYLE_M272E30
#   define I_C08_ENGSTYLE_M272E30 (4U)
#  endif
#  ifndef I_C08_ENGSTYLE_M272E25
#   define I_C08_ENGSTYLE_M272E25 (5U)
#  endif
#  ifndef I_C08_ENGSTYLE_M272E35DE
#   define I_C08_ENGSTYLE_M272E35DE (9U)
#  endif
#  ifndef I_C08_ENGSTYLE_M271E18ML135ATT
#   define I_C08_ENGSTYLE_M271E18ML135ATT (12U)
#  endif
#  ifndef I_C08_ENGSTYLE_M271E18ML115ATT
#   define I_C08_ENGSTYLE_M271E18ML115ATT (13U)
#  endif
#  ifndef I_C08_ENGSTYLE_M272E35_224
#   define I_C08_ENGSTYLE_M272E35_224 (14U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E30GDEHLA
#   define I_C08_ENGSTYLE_M276E30GDEHLA (15U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E35DES
#   define I_C08_ENGSTYLE_M276E35DES (16U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E35DESRED
#   define I_C08_ENGSTYLE_M276E35DESRED (17U)
#  endif
#  ifndef I_C08_ENGSTYLE_M278E46DEHLA
#   define I_C08_ENGSTYLE_M278E46DEHLA (18U)
#  endif
#  ifndef I_C08_ENGSTYLE_M271E18LAEVO115
#   define I_C08_ENGSTYLE_M271E18LAEVO115 (19U)
#  endif
#  ifndef I_C08_ENGSTYLE_M271E18LAEVO150
#   define I_C08_ENGSTYLE_M271E18LAEVO150 (20U)
#  endif
#  ifndef I_C08_ENGSTYLE_M271E18LAEVO135
#   define I_C08_ENGSTYLE_M271E18LAEVO135 (21U)
#  endif
#  ifndef I_C08_ENGSTYLE_M270DE16
#   define I_C08_ENGSTYLE_M270DE16 (22U)
#  endif
#  ifndef I_C08_ENGSTYLE_M270DE16LA115
#   define I_C08_ENGSTYLE_M270DE16LA115 (23U)
#  endif
#  ifndef I_C08_ENGSTYLE_M270DE20LA155
#   define I_C08_ENGSTYLE_M270DE20LA155 (24U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E35DEH
#   define I_C08_ENGSTYLE_M276E35DEH (25U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E35DEHRED
#   define I_C08_ENGSTYLE_M276E35DEHRED (26U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E35DESLA
#   define I_C08_ENGSTYLE_M276E35DESLA (27U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DEH16LA115
#   define I_C08_ENGSTYLE_M274DEH16LA115 (28U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DEH20LA135
#   define I_C08_ENGSTYLE_M274DEH20LA135 (29U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DES20LA135
#   define I_C08_ENGSTYLE_M274DES20LA135 (30U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DEH20LA155
#   define I_C08_ENGSTYLE_M274DEH20LA155 (31U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DES20LA155
#   define I_C08_ENGSTYLE_M274DES20LA155 (32U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DEH20LA180
#   define I_C08_ENGSTYLE_M274DEH20LA180 (33U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DES20LA180
#   define I_C08_ENGSTYLE_M274DES20LA180 (34U)
#  endif
#  ifndef I_C08_ENGSTYLE_M277E60LA
#   define I_C08_ENGSTYLE_M277E60LA (35U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E30DEHLA245
#   define I_C08_ENGSTYLE_M276E30DEHLA245 (36U)
#  endif
#  ifndef I_C08_ENGSTYLE_M281E10_45
#   define I_C08_ENGSTYLE_M281E10_45 (37U)
#  endif
#  ifndef I_C08_ENGSTYLE_M281E10_51
#   define I_C08_ENGSTYLE_M281E10_51 (38U)
#  endif
#  ifndef I_C08_ENGSTYLE_M281DE09LA
#   define I_C08_ENGSTYLE_M281DE09LA (39U)
#  endif
#  ifndef I_C08_ENGSTYLE_M282DE12LA
#   define I_C08_ENGSTYLE_M282DE12LA (40U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E30DEHLARED
#   define I_C08_ENGSTYLE_M276E30DEHLARED (41U)
#  endif
#  ifndef I_C08_ENGSTYLE_M270DE20LA120
#   define I_C08_ENGSTYLE_M270DE20LA120 (42U)
#  endif
#  ifndef I_C08_ENGSTYLE_M270DE16LA70
#   define I_C08_ENGSTYLE_M270DE16LA70 (43U)
#  endif
#  ifndef I_C08_ENGSTYLE_M270DE20LA165
#   define I_C08_ENGSTYLE_M270DE20LA165 (44U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E35DESLA245
#   define I_C08_ENGSTYLE_M276E35DESLA245 (45U)
#  endif
#  ifndef I_C08_ENGSTYLE_M278DEH40LA320
#   define I_C08_ENGSTYLE_M278DEH40LA320 (46U)
#  endif
#  ifndef I_C08_ENGSTYLE_M176DEH40LA345
#   define I_C08_ENGSTYLE_M176DEH40LA345 (47U)
#  endif
#  ifndef I_C08_ENGSTYLE_M276E30DEHLA270
#   define I_C08_ENGSTYLE_M276E30DEHLA270 (48U)
#  endif
#  ifndef I_C08_ENGSTYLE_M176DEH40LA310
#   define I_C08_ENGSTYLE_M176DEH40LA310 (49U)
#  endif
#  ifndef I_C08_ENGSTYLE_M256DEH30LA
#   define I_C08_ENGSTYLE_M256DEH30LA (50U)
#  endif
#  ifndef I_C08_ENGSTYLE_M256DEHDES30LA
#   define I_C08_ENGSTYLE_M256DEHDES30LA (51U)
#  endif
#  ifndef I_C08_ENGSTYLE_M256DEHDES30LAPL
#   define I_C08_ENGSTYLE_M256DEHDES30LAPL (52U)
#  endif
#  ifndef I_C08_ENGSTYLE_M256DEHDES25LA
#   define I_C08_ENGSTYLE_M256DEHDES25LA (53U)
#  endif
#  ifndef I_C08_ENGSTYLE_M274DEH16LA90
#   define I_C08_ENGSTYLE_M274DEH16LA90 (54U)
#  endif
#  ifndef I_C08_ENGSTYLE_M264DEHLA
#   define I_C08_ENGSTYLE_M264DEHLA (55U)
#  endif
#  ifndef I_C08_ENGSTYLE_M260DEHLA
#   define I_C08_ENGSTYLE_M260DEHLA (56U)
#  endif
#  ifndef I_C08_ENGSTYLE_M176DEH40LA360
#   define I_C08_ENGSTYLE_M176DEH40LA360 (57U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM139DEHLA
#   define I_C08_ENGSTYLE_AMGM139DEHLA (107U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM177DEH40LA410
#   define I_C08_ENGSTYLE_AMGM177DEH40LA410 (108U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM177DEH40LA420
#   define I_C08_ENGSTYLE_AMGM177DEH40LA420 (109U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM177DEH40LA430
#   define I_C08_ENGSTYLE_AMGM177DEH40LA430 (110U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM177DEH40LA450
#   define I_C08_ENGSTYLE_AMGM177DEH40LA450 (111U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM178DEH40LA410
#   define I_C08_ENGSTYLE_AMGM178DEH40LA410 (112U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM178DEH40LA450
#   define I_C08_ENGSTYLE_AMGM178DEH40LA450 (113U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM178DEH40LA340
#   define I_C08_ENGSTYLE_AMGM178DEH40LA340 (114U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM177DEH40LA350
#   define I_C08_ENGSTYLE_AMGM177DEH40LA350 (115U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM178DEH40LA370
#   define I_C08_ENGSTYLE_AMGM178DEH40LA370 (116U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM177DEH40LA375
#   define I_C08_ENGSTYLE_AMGM177DEH40LA375 (117U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM279E60LA
#   define I_C08_ENGSTYLE_AMGM279E60LA (118U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM133DE20LA
#   define I_C08_ENGSTYLE_AMGM133DE20LA (119U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM159E63
#   define I_C08_ENGSTYLE_AMGM159E63 (120U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM152E55DE
#   define I_C08_ENGSTYLE_AMGM152E55DE (121U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM157E55DEHLA
#   define I_C08_ENGSTYLE_AMGM157E55DEHLA (122U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM156E63HP
#   define I_C08_ENGSTYLE_AMGM156E63HP (123U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM275E60LA
#   define I_C08_ENGSTYLE_AMGM275E60LA (124U)
#  endif
#  ifndef I_C08_ENGSTYLE_AMGM156E63
#   define I_C08_ENGSTYLE_AMGM156E63 (126U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM642DE30LA160
#   define I_C08_ENGSTYLE_OM642DE30LA160 (129U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM629DE40LA
#   define I_C08_ENGSTYLE_OM629DE40LA (130U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM642DE30LA140
#   define I_C08_ENGSTYLE_OM642DE30LA140 (131U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM646EVODE22LA125
#   define I_C08_ENGSTYLE_OM646EVODE22LA125 (132U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM646EVODE22LA100
#   define I_C08_ENGSTYLE_OM646EVODE22LA100 (133U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM646EVODE22LA85
#   define I_C08_ENGSTYLE_OM646EVODE22LA85 (134U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM651DE22LA150
#   define I_C08_ENGSTYLE_OM651DE22LA150 (135U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM651DE22LA125
#   define I_C08_ENGSTYLE_OM651DE22LA125 (136U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM651DE22LA100
#   define I_C08_ENGSTYLE_OM651DE22LA100 (137U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM651DE22LA80
#   define I_C08_ENGSTYLE_OM651DE22LA80 (138U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM642DE30LA185
#   define I_C08_ENGSTYLE_OM642DE30LA185 (139U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM651DE18LA80
#   define I_C08_ENGSTYLE_OM651DE18LA80 (140U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM651DE18LA100
#   define I_C08_ENGSTYLE_OM651DE18LA100 (141U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM607DE14LA66
#   define I_C08_ENGSTYLE_OM607DE14LA66 (142U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM607DE14LA81
#   define I_C08_ENGSTYLE_OM607DE14LA81 (143U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM622DE16LA96
#   define I_C08_ENGSTYLE_OM622DE16LA96 (144U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM622DE16LA118
#   define I_C08_ENGSTYLE_OM622DE16LA118 (145U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM626DE16LA96
#   define I_C08_ENGSTYLE_OM626DE16LA96 (146U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM626DE16LA118
#   define I_C08_ENGSTYLE_OM626DE16LA118 (147U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM654DE20LA
#   define I_C08_ENGSTYLE_OM654DE20LA (148U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM656DE30LA230
#   define I_C08_ENGSTYLE_OM656DE30LA230 (149U)
#  endif
#  ifndef I_C08_ENGSTYLE_OM608DE15LA
#   define I_C08_ENGSTYLE_OM608DE15LA (150U)
#  endif
#  ifndef I_C08_ENGSTYLE_SNA
#   define I_C08_ENGSTYLE_SNA (255U)
#  endif

#  define Rte_TypeDef_c08_degC_m40_214_1
typedef uint8 c08_degC_m40_214_1;
#  define c08_degC_m40_214_1_LowerLimit (0U)
#  define c08_degC_m40_214_1_UpperLimit (255U)
#  define Rte_InvalidValue_c08_degC_m40_214_1 (255U)
#  define InvalidValue_c08_degC_m40_214_1 (255U)
#  ifndef I_C08_DEGC_M40_214_1_SNA
#   define I_C08_DEGC_M40_214_1_SNA (255U)
#  endif

#  define Rte_TypeDef_c08_min_0_60_1
typedef uint8 c08_min_0_60_1;
#  define c08_min_0_60_1_LowerLimit (0U)
#  define c08_min_0_60_1_UpperLimit (255U)
#  define Rte_InvalidValue_c08_min_0_60_1 (255U)
#  define InvalidValue_c08_min_0_60_1 (255U)
#  ifndef I_C08_MIN_0_60_1_SNA
#   define I_C08_MIN_0_60_1_SNA (255U)
#  endif

#  define Rte_TypeDef_c11_A_m102k4_102k2_0k1
typedef uint16 c11_A_m102k4_102k2_0k1;
#  define c11_A_m102k4_102k2_0k1_LowerLimit (0U)
#  define c11_A_m102k4_102k2_0k1_UpperLimit (2047U)
#  define Rte_InvalidValue_c11_A_m102k4_102k2_0k1 (2047U)
#  define InvalidValue_c11_A_m102k4_102k2_0k1 (2047U)
#  ifndef I_C11_A_M102K4_102K2_0K1_SNA
#   define I_C11_A_M102K4_102K2_0K1_SNA (2047U)
#  endif

#  define Rte_TypeDef_c12_min_0_4094_1
typedef uint16 c12_min_0_4094_1;
#  define c12_min_0_4094_1_LowerLimit (0U)
#  define c12_min_0_4094_1_UpperLimit (4095U)
#  define Rte_InvalidValue_c12_min_0_4094_1 (4095U)
#  define InvalidValue_c12_min_0_4094_1 (4095U)
#  ifndef I_C12_MIN_0_4094_1_SNA
#   define I_C12_MIN_0_4094_1_SNA (4095U)
#  endif

#  define Rte_TypeDef_c13_A_m409k6_409k4_0k1
typedef uint16 c13_A_m409k6_409k4_0k1;
#  define c13_A_m409k6_409k4_0k1_LowerLimit (0U)
#  define c13_A_m409k6_409k4_0k1_UpperLimit (8191U)
#  define Rte_InvalidValue_c13_A_m409k6_409k4_0k1 (8191U)
#  define InvalidValue_c13_A_m409k6_409k4_0k1 (8191U)
#  ifndef I_C13_A_M409K6_409K4_0K1_SNA
#   define I_C13_A_M409K6_409K4_0K1_SNA (8191U)
#  endif

#  define Rte_TypeDef_c13_Nm_m500_1547k5_0k25
typedef uint16 c13_Nm_m500_1547k5_0k25;
#  define c13_Nm_m500_1547k5_0k25_LowerLimit (0U)
#  define c13_Nm_m500_1547k5_0k25_UpperLimit (8191U)
#  define Rte_InvalidValue_c13_Nm_m500_1547k5_0k25 (8191U)
#  define InvalidValue_c13_Nm_m500_1547k5_0k25 (8191U)
#  ifndef I_C13_NM_M500_1547K5_0K25_SNA
#   define I_C13_NM_M500_1547K5_0K25_SNA (8191U)
#  endif

#  define Rte_TypeDef_c14_rpm_0_16382_1
typedef uint16 c14_rpm_0_16382_1;
#  define c14_rpm_0_16382_1_LowerLimit (0U)
#  define c14_rpm_0_16382_1_UpperLimit (16383U)
#  define Rte_InvalidValue_c14_rpm_0_16382_1 (16383U)
#  define InvalidValue_c14_rpm_0_16382_1 (16383U)
#  ifndef I_C14_RPM_0_16382_1_SNA
#   define I_C14_RPM_0_16382_1_SNA (16383U)
#  endif

#  define Rte_TypeDef_c16_Days_0_65534_1
typedef uint16 c16_Days_0_65534_1;
#  define c16_Days_0_65534_1_LowerLimit (0U)
#  define c16_Days_0_65534_1_UpperLimit (65535U)
#  define Rte_InvalidValue_c16_Days_0_65534_1 (65535U)
#  define InvalidValue_c16_Days_0_65534_1 (65535U)
#  ifndef I_C16_DAYS_0_65534_1_SNA
#   define I_C16_DAYS_0_65534_1_SNA (65535U)
#  endif

#  define Rte_TypeDef_c16_ul_p_250ms_0_14200_0k21668
typedef uint16 c16_ul_p_250ms_0_14200_0k21668;
#  define c16_ul_p_250ms_0_14200_0k21668_LowerLimit (0U)
#  define c16_ul_p_250ms_0_14200_0k21668_UpperLimit (65535U)
#  define Rte_InvalidValue_c16_ul_p_250ms_0_14200_0k21668 (65535U)
#  define InvalidValue_c16_ul_p_250ms_0_14200_0k21668 (65535U)
#  ifndef I_C16_UL_P_250MS_0_14200_0K21668_SNA
#   define I_C16_UL_P_250MS_0_14200_0K21668_SNA (65535U)
#  endif

#  define Rte_TypeDef_DT_aucDiagStatusInfoWu
typedef UInt8 DT_aucDiagStatusInfoWu[48];

#  define Rte_TypeDef_DT_aucStatInfoDCM
typedef UInt8 DT_aucStatInfoDCM[4];

#  define Rte_TypeDef_DT_tDiagStatusInfoWU
typedef UInt8 DT_tDiagStatusInfoWU[12];

#  define Rte_TypeDef_REC_DateTm_AR2
typedef struct
{
  c08_Days_1_31_1 DateTmDay;
  c08_h_0_23_1 DateTmHour;
  c08_min_0_59_1 DateTmMinute;
  c08_Months_1_12_1 DateTmMonth;
  c08_s_0_59_1 DateTmSecond;
  c03_DateTm_Stat DateTmStat;
  c03_WeekDay_UA DateTmWeekday;
  c08_Years_0_99_1 DateTmYear;
} REC_DateTm_AR2;

#  define Rte_TypeDef_REC_EVC_CfgBit_01_32_Pr2
typedef struct
{
  c08_CRC_woSNA CRC_EVC_CfgBit_01_32_Pr2;
  c04_0_15_1_SNA_na SQC_EVC_CfgBit_01_32_Pr2;
  DC_BOOL EVC_27_HandsFreeAcc_Avl;
  DC_BOOL EVC_28_PlugInHyb_50kW_Avl;
  DC_BOOL EVC_29_Hyb_30kW_Avl;
  DC_BOOL EVC_2A_SeatElAdj_F_OprtnR_Avl;
  DC_BOOL EVC_2B_DSI_Sel_Avl;
  DC_BOOL EVC_2C_WC_VEDA_Avl;
  DC_BOOL EVC_2D_AutoSpdCtrl_Avl;
  DC_BOOL EVC_2F_RetrofitFuelcell_Avl;
  DC_BOOL EVC_30_AddEquip_Avl;
  DC_BOOL EVC_31_AddEquip_Avl;
  DC_BOOL EVC_32_AddEquip_Avl;
  DC_BOOL EVC_0D_4x2Drive_Avl;
  DC_BOOL EVC_0C_AllWheelDr_Avl;
  DC_BOOL EVC_18_AmbLgt_Avl;
  DC_BOOL EVC_12_AutRearDr_Avl;
  c02_EVC_Stat EVC_CfgBit_01_32_Stat;
  DC_BOOL EVC_15_DRLt_Avl;
  DC_BOOL EVC_19_ElDrPosnSel_Avl;
  DC_BOOL EVC_16_FogLmp_Avl;
  DC_BOOL EVC_09_FullHyb_Avl;
  DC_BOOL EVC_1E_GuardLvl_B4_Avl;
  DC_BOOL EVC_1F_GuardLvl_B6_Avl;
  DC_BOOL EVC_20_GuardLvl_B7_Avl;
  DC_BOOL EVC_25_HVAC_R_Avl;
  DC_BOOL EVC_1C_HghVTP_Avl;
  DC_BOOL EVC_24_ICH_Avl;
  DC_BOOL EVC_17_IL_Pk_Avl;
  DC_BOOL EVC_1A_IntSfProt_Avl;
  DC_BOOL EVC_10_KG_Avl;
  DC_BOOL EVC_23_PASS_Avl;
  DC_BOOL EVC_0A_Hyb_20kW_Avl;
  DC_BOOL EVC_11_AutTrunkLid_Avl;
  DC_BOOL EVC_0B_PlugInHyb_80kW_Avl;
  DC_BOOL EVC_0E_Presf_Avl;
  DC_BOOL EVC_21_Pullman_Avl;
  DC_BOOL EVC_13_PwrCls_Avl;
  DC_BOOL EVC_14_RainSens_Avl;
  DC_BOOL EVC_26_SSA_Avl;
  DC_BOOL EVC_1D_SecurityVer_Avl;
  DC_BOOL EVC_22_SpecClos_Avl;
  DC_BOOL EVC_0F_TrlrHtch_Avl;
  DC_BOOL EVC_1B_VTA_Avl;
  DC_BOOL EVC_05_Ver_Australia_Avl;
  DC_BOOL EVC_08_Ver_Canada_Avl;
  DC_BOOL EVC_06_Ver_China_Avl;
  DC_BOOL EVC_04_Ver_GulfStates_Avl;
  DC_BOOL EVC_03_Ver_Japan_Avl;
  DC_BOOL EVC_02_Ver_Mexico_Avl;
  DC_BOOL EVC_07_Ver_S_Korea_Avl;
  DC_BOOL EVC_01_Ver_USA_Avl;
  DC_BOOL EVC_2E_AddEquipBlock_Avl;
} REC_EVC_CfgBit_01_32_Pr2;

#  define Rte_TypeDef_REC_EVC_CfgList_01_0C_Pr2
typedef struct
{
  c08_CRC_woSNA CRC_EVC_CfgList_01_0C_Pr2;
  c05_EVC_BodyStyle EVC_List02_BodyStyle;
  c02_EVC_Stat EVC_CfgList_01_0C_Stat;
  c08_EVC_Country EVC_List08_Country;
  c04_EVC_HL_Style EVC_List04_HL_Style;
  c03_EVC_HVAC_Style EVC_List07_HVAC_Style;
  c03_EVC_RoofStyle EVC_List03_RoofStyle;
  c02_StStyle EVC_List01_StStyle;
  c03_EVC_TPM_Style EVC_List0A_TPM_Style;
  c04_EVC_TxStyle EVC_List05_TxStyle;
  c06_EVC_VehLine EVC_List0C_VehLine;
  c05_EVC_VehLineYear EVC_List06_VehLineYear;
  c04_0_15_1_SNA_na SQC_EVC_CfgList_01_0C_Pr2;
  c05_EVC_HU_Style EVC_List09_HU_Style;
  c02_EVC_AddEquip EVC_List0B_AddEquip;
} REC_EVC_CfgList_01_0C_Pr2;

#  define Rte_TypeDef_REC_Eng_Rs_EngCtrl_Pr2
typedef struct
{
  c08_EngStyle EngStyle;
  c13_Nm_m500_1547k5_0k25 EngTrq;
  DC_BOOL AddPwrCnsmr_On_Rq;
  c08_CRC_woSNA CRC_Eng_Rs_EngCtrl_Pr2;
  c14_rpm_0_16382_1 EngRPM;
  c03_EngRun_Stat EngRun_Stat;
  c08_0_1k98_0k0078 EngTrqMaxCorrFctr;
  DC_BOOL EngRPM_Sens_LHOM;
  c04_0_15_1_SNA_na SQC_Eng_Rs_EngCtrl_Pr2;
  Rsrv01 Rsrv2_Eng_Rs_EngCtrl_Pr2;
  c02_OFC_Stat OFC_Stat_PT;
  DC_BOOL EngTrqLmtd_Misfire;
} REC_Eng_Rs_EngCtrl_Pr2;

#  define Rte_TypeDef_REC_Eng_Rs_EngCtrl_Pr2_1ug7ce4nz8thso4to6nvxcc3e
typedef struct
{
  c08_EngStyle EngStyle;
  c03_EngRun_Stat EngRun_Stat;
} REC_Eng_Rs_EngCtrl_Pr2_1ug7ce4nz8thso4to6nvxcc3e;

#  define Rte_TypeDef_REC_Eng_Rs_EngCtrl_Pr2_b0ko81o0x5jgvwtduf99gvzi0
typedef struct
{
  c08_EngStyle EngStyle;
} REC_Eng_Rs_EngCtrl_Pr2_b0ko81o0x5jgvwtduf99gvzi0;

#  define Rte_TypeDef_REC_Ign_Stat_Pr2
typedef struct
{
  c03_ISw_Stat ISw_Stat;
  DC_BOOL Ign_On_StartProc_Inact;
  DC_BOOL KG_IgnCtrl_Actv;
  c08_CRC_woSNA CRC_Ign_Stat_Pr2;
  c04_0_15_1_SNA_na SQC_Ign_Stat_Pr2;
  c02_SPCR_Conf SPCR_Conf_EIS;
  DC_BOOL SPCR_AcustWarn_Rq_EIS;
  DC_BOOL SPCR_Flt_EIS;
  DC_BOOL TxPkPosn_Rq_SPCR_Enbl;
  DC_BOOL TxPkPosn_Emg_Rq;
  c02_ESL_Lk_Rq ESL_Lk_Rq;
  DC_BOOL TxPkPosn_Rq;
  DC_BOOL TxPkPosnAuto_Enbl;
  DC_BOOL KG_StartSw_Psd;
  DC_BOOL EngSt_Enbl_Rq_KG;
  DC_BOOL RemSt_IgnCtrl_Actv;
  c02_RemSt_IgnCtrl_Info RemSt_IgnCtrl_Info;
} REC_Ign_Stat_Pr2;

#  define Rte_TypeDef_REC_PN14_SupBat_Stat
typedef struct
{
  c02_BatCutSw_Stat PN14_SupBatCutSw_Stat;
  c11_A_m102k4_102k2_0k1 PN14_SupBat_Curr;
  c08_V_0_25k4_0k1 PN14_SupBat_Volt;
} REC_PN14_SupBat_Stat;

#  define Rte_TypeDef_REC_PN14_SupBat_Stat_b0ko81o0x5jgvwtduf99gvzi0
typedef struct
{
  c02_BatCutSw_Stat PN14_SupBatCutSw_Stat;
} REC_PN14_SupBat_Stat_b0ko81o0x5jgvwtduf99gvzi0;

#  define Rte_TypeDef_REC_PressureCal
typedef struct
{
  UInt8 RE_CalPressure1;
  UInt8 RE_CalPressure2;
  UInt8 RE_CalPressure3;
  UInt8 RE_CalPressure4;
} REC_PressureCal;

#  define Rte_TypeDef_REC_TPM_Lmp_On_Rq_Pr2
typedef struct
{
  c08_CRC_woSNA CRC_TPM_Lmp_On_Rq_Pr2;
  Rsrv02 Rsrv1_TPM_Lmp_On_Rq_Pr2;
  c04_0_15_1_SNA_na SQC_TPM_Lmp_On_Rq_Pr2;
  DC_BOOL TPM_IndLmp_On_Rq;
  DC_BOOL TPM_MalfLmp_On_Rq;
} REC_TPM_Lmp_On_Rq_Pr2;

#  define Rte_TypeDef_REC_WhlPlsCnt_TPM_Pr2
typedef struct
{
  c08_CRC_woSNA CRC_WhlPlsCnt_TPM_Pr2;
  Rsrv08 Rsrv2_WhlPlsCnt_TPM_Pr2;
  c04_0_15_1_SNA_na SQC_WhlPlsCnt_TPM_Pr2;
  c08_Impulses_0_254_1 WhlPlsCnt_FL;
  c08_Impulses_0_254_1 WhlPlsCnt_FR;
  c08_Impulses_0_254_1 WhlPlsCnt_RL;
  c08_Impulses_0_254_1 WhlPlsCnt_RR;
  c08_ms_0_254_1 WhlPlsCnt_TmStmp;
  Rsrv04 Rsrv1_WhlPlsCnt_TPM_Pr2;
} REC_WhlPlsCnt_TPM_Pr2;

# endif

# define RTE_START_SEC_CONST_UNSPECIFIED
# include "MemMap.h"

extern CONST(ARR_08_UInt_noSNA_8, RTE_CONST) Rte_XDIS_bzm3suyimc3lnij4fzlwpgwm4;

extern CONST(DT_auRfStruct, RTE_CONST) Rte_C_aucRfStruct;

extern CONST(DT_tEnvData, RTE_CONST) Rte_C_tEnvData;

extern CONST(REC_DateTm_AR2_f0ifkphxunpp94u3ro8qn5tdm, RTE_CONST) Rte_XDIS_8oeobqbbrmj8fyiongo6ax1xv;

extern CONST(REC_EVC_CfgBit_01_32_Pr2_d23bad5cnts3f65mtgoqoxmrz, RTE_CONST) Rte_XDIS_9rt50469dx6jveycvwiekru9s;

extern CONST(REC_EVC_CfgList_01_0C_Pr2_ah3rxaqpfvlnju8848jpspm9p, RTE_CONST) Rte_XDIS_69nqj71u0pbksk5hjvodygwvd;

extern CONST(REC_Eng_Rs_EngCtrl_Pr2_1j00gxu3p5exa8awg915k1zy, RTE_CONST) Rte_XDIS_b1gz9poycm6ddxgidqfjet2pv;

extern CONST(REC_Ign_Stat_Pr2_71njeubj9ico1p8v4pmslfcno, RTE_CONST) Rte_XDIS_a24im2m55sztow8orofz1re4l;

extern CONST(REC_Ign_Stat_Pr2_b0ko81o0x5jgvwtduf99gvzi0, RTE_CONST) Rte_XDIS_9d6x34bvkzvn1spi8e3620s3f;

extern CONST(REC_PN14_SupBat_Stat_2is6fi0meeac78nkn35zc5ui3, RTE_CONST) Rte_XDIS_63893tj3bpxgywawhjj46oa1d;

extern CONST(REC_ROE_XX, RTE_CONST) Rte_XDIS_cduaikm94dzygis49e7i8n2vd;

extern CONST(REC_RefPress, RTE_CONST) Rte_XDIS_5lnq4pgpv2f92y9v99h1532rc;

extern CONST(REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt, RTE_CONST) Rte_XDIS_agb15wb9uilg0ni8bte2ez7oc;

extern CONST(REC_TPM_Lmp_On_Rq_old, RTE_CONST) Rte_XDIS_1d7ph8epnzfwmb1z8ubz5caiq;

extern CONST(REC_Tire_Stat_V2, RTE_CONST) Rte_XDIS_c887fxti3dvrcxpco5w1om6lw;

extern CONST(REC_Tire_Temp_V2, RTE_CONST) Rte_XDIS_17gsj8drc9emz51ybjnyn4din;

extern CONST(REC_WhlPlsCnt_TPM_Pr2_5hishd08ma5z1luev78umdwvx, RTE_CONST) Rte_XDIS_3bcpjgb37kcc1t679g9053jt5;

# define RTE_STOP_SEC_CONST_UNSPECIFIED
# include "MemMap.h"

# ifdef RTE_MICROSAR_PIM_EXPORT

#  define RTE_START_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#  include "MemMap.h"

extern CONST(DT_tDiagNvMBlock0, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock0_DefaultValue;
extern CONST(DT_tDiagNvMBlock1, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock1_DefaultValue;
extern CONST(DT_tDiagNvMBlock2, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock2_DefaultValue;
extern CONST(DT_tDiagNvMBlock3, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock3_DefaultValue;
extern CONST(DT_tCalNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCalNvMBlock_DefaultValue;
extern CONST(DT_tCodNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCodNvMBlock_DefaultValue;
extern CONST(DT_tWarnHdlrNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSwnh_Cal_tWarnHdlrNvMBlock_DefaultValue;
extern CONST(DT_tWallocNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSwpa_Cal_tWallocNvMBlock_DefaultValue;

#  define RTE_STOP_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
#  include "MemMap.h"

extern VAR(DT_tDiagNvMBlock0, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock0;
extern VAR(DT_tDiagNvMBlock1, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock1;
extern VAR(DT_tDiagNvMBlock2, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock2;
extern VAR(DT_tDiagNvMBlock3, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSdia_Pim_tDiagNvMBlock3;
extern VAR(DT_tCalNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSmgr_Pim_tCalNvMBlock;
extern VAR(DT_tCodNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSmgr_Pim_tCodNvMBlock;
extern VAR(DT_tWarnHdlrNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSwnh_Pim_tWarnHdlrNvMBlock;
extern VAR(DT_tWallocNvMBlock, RTE_VAR_DEFAULT_RTE_PIM_GROUP) Rte_CpApHufTPMSwpa_Pim_tWallocNvMBlock;

#  define RTE_STOP_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
#  include "MemMap.h"

# endif

typedef unsigned int Rte_BitType;

# define RTE_STATE_UNINIT    (0U)
# define RTE_STATE_INIT      (1U)

# ifdef RTE_CORE

#  define RTE_START_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#  include "MemMap.h"

extern CONST(DT_tDiagNvMBlock0, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock0_DefaultValue;
extern CONST(DT_tDiagNvMBlock1, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock1_DefaultValue;
extern CONST(DT_tDiagNvMBlock2, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock2_DefaultValue;
extern CONST(DT_tDiagNvMBlock3, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSdia_Cal_tDiagNvMBlock3_DefaultValue;
extern CONST(DT_tCalNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCalNvMBlock_DefaultValue;
extern CONST(DT_tCodNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSmgr_Cal_tCodNvMBlock_DefaultValue;
extern CONST(DT_tWarnHdlrNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSwnh_Cal_tWarnHdlrNvMBlock_DefaultValue;
extern CONST(DT_tWallocNvMBlock, RTE_CONST_DEFAULT_RTE_CDATA_GROUP) Rte_CtApHufTPMSwpa_Cal_tWallocNvMBlock_DefaultValue;

#  define RTE_STOP_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

extern VAR(DT_tEnvData, RTE_VAR_NOINIT) Rte_CpApHufTPMSmgr_PP_EnvData_DE_tEnvData;
extern VAR(DT_auRfStruct, RTE_VAR_NOINIT) Rte_CpApHufTPMSmgr_PP_RfStructOut_DE_auRfStruct;
extern VAR(DT_ushWarnOut, RTE_VAR_NOINIT) Rte_CpApHufTPMSwnh_PP_WarnOut_DE_ushWarnOut;
extern VAR(DT_ushWAState, RTE_VAR_NOINIT) Rte_CpApHufTPMSwpa_PP_WAState_DE_ushWAState;
extern VAR(DT_auRfStruct, RTE_VAR_NOINIT) Rte_CpCdHufTPMSrfd_PP_RfStruct_DE_auRfStruct;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

typedef struct
{
  boolean Rte_RxTimeout_Com_AirPress_Outsd;
  boolean Rte_RxTimeout_Com_AirTemp_Outsd_Disp;
  boolean Rte_RxTimeout_Com_DidA_ExtTest_Pres;
  boolean Rte_RxTimeout_Com_Grp_DateTm_AR2_5h1zg0kdztpv8ox5dnrew2st8;
  boolean Rte_RxTimeout_Com_Grp_Eng_Rs_EngCtrl_Pr2_1g6e1wh7aspfj509n9mt9fl55;
  boolean Rte_RxTimeout_Com_Grp_Ign_Stat_Pr2_457i75qk4uen9ahb37ecxdhxz;
  boolean Rte_RxTimeout_Com_Grp_PN14_SupBat_Stat_aleu8fy7bsux9kh42xfztkzmi;
  boolean Rte_RxTimeout_Com_Grp_WhlPlsCnt_TPM_Pr2_ci3hi3ex1xdl3zn6k2mcbudsp;
  boolean Rte_RxTimeout_Com_Odo;
  boolean Rte_RxTimeout_Com_PN14_EOL_Disp_Rq;
  boolean Rte_RxTimeout_Com_RevGr_Engg;
  boolean Rte_RxTimeout_Com_TPM_Actv_Rq_V2;
  boolean Rte_RxTimeout_Com_VehSpd_Disp;
} Rte_RxTimeoutFlagsType;

#  define RTE_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#  include "MemMap.h"

extern VAR(Rte_RxTimeoutFlagsType, RTE_VAR_ZERO_INIT) Rte_RxTimeoutFlags;

#  define RTE_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

extern VAR(Boolean, RTE_VAR_NOINIT) Rte_Irv_CpApHufTPMSmgr_IRV_TpmActvRq_TpmMsgDispRq;

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

#  define RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#  include "MemMap.h"

# endif

# ifndef SKIP_MAGIC_NUMBER
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1513305418
#    error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Rte_Type.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1513305418
#  endif
# endif

#endif

