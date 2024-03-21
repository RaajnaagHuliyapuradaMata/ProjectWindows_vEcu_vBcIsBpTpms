

#if !defined(NM_CFG_H)
#define NM_CFG_H

#include "ComStack_Types.h"
#include "NmStack_Types.h"
#define NM_ASRNMIFDLL_VERSION                0x0225u
#define NM_ASRNMIFDLL_RELEASE_VERSION        0x01u
#define NM_NUMBER_OF_SYS_CHANNELS            1u
#define NM_NUMBER_OF_NM_CHANNELS             1u

#define Nm_HMI                               0u

#define NM_BUSNM_CANNM_ENABLED STD_ON
#define NM_BUSNM_FRNM_ENABLED STD_OFF
#define NM_ENABLE_CHANNELTYPE_CANNM

#define NM_COM_CONTROL_ENABLED STD_ON
#define NM_VERSION_INFO_API STD_OFF
#define NM_USER_DATA_ENABLED STD_ON
#define NM_NODE_DETECTION_ENABLED STD_ON
#define NM_NODE_ID_ENABLED STD_ON
#define NM_PASSIVE_MODE_ENABLED STD_OFF
#define NM_PDU_RX_INDICATION_ENABLED STD_OFF
#define NM_STATE_CHANGE_IND_ENABLED STD_OFF
#define NM_REMOTE_SLEEP_IND_ENABLED STD_OFF
#define NM_BUS_SYNCHRONIZATION_ENABLED STD_OFF
#define NM_DEV_ERROR_DETECT STD_OFF
#define NM_PROD_ERROR_DETECT STD_ON
#define NM_COM_USER_DATA_ENABLED STD_ON
#define NM_CAR_WAKE_UP_RX_ENABLED STD_OFF

#define NM_USE_DUMMY_STATEMENT STD_ON

#define NM_CRC_CHECK                         STD_OFF

#define NM_PRECOMPILE_CRC                    (uint32) 0xDBBC99D5u

#define NM_AMD_RUNTIME_MEASUREMENT STD_OFF

#define NM_COORDINATOR_SUPPORT_ENABLED STD_OFF
#define NM_OSEK_SUPPORT_ENABLED STD_OFF

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )

typedef uint8 Nm_ConfigType;
#else
#if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#define NM_CHANNEL_IDX              (channel)
#else
#define NM_CHANNEL_IDX              (nmChannelHandle)
#endif

#define NM_RM_BSM     ((uint8)0x01)
#define NM_RM_PBSM    ((uint8)0x02)
#define NM_NO_RM      ((uint8)0x04)
#define NM_NO_RS      ((uint8)0x08)
#define NM_RM_RS      ((uint8)0x10)
#define NM_RM_NO      ((uint8)0x20)

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#define NM_SUPPRESSNOTIFYSTART     ((uint8)0x00)
#define NM_NOTIFYSTARTSLEEP        ((uint8)0x01)
#define NM_NOTIFYSTARTPREPSLEEP    ((uint8)0x02)
#endif
#endif

typedef enum {
  NM_BUSNM_CANNM      = 0x00u,
  NM_BUSNM_FRNM       = 0x01u,
  NM_BUSNM_LINNM      = 0x02u,
#if( NM_OSEK_SUPPORT_ENABLED == STD_ON )
  NM_BUSNM_OSEKNM     = 0x03u,
  NM_BUSNM_CANOSEKNM  = 0x04u,
#endif
#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
  NM_BUSNM_NMFIATB    = 0x05u,
#endif
#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  NM_BUSNM_NMFIATC    = 0x06u,
#endif
  NM_BUSNM_UNDEF      = 0xFFu
}Nm_BusNmType;

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )

typedef enum {
  NM_COORD_SEL            = 0x00,
  NM_COORD_SYN_ACTIVE     = 0x01
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  ,NM_COORD_SYN_PASSIVE   = 0x02
#endif
}Nm_SyncNmType;

#  if( NM_NUMBER_OF_NM_CHANNELS <= 32 )
typedef uint32 Nm_NetworkCoordType;
#else
#error: "NM Interface configuration error: NM Interface with Coordinator Support ON does not support more than 32 channels!"
#endif
#endif

#if defined ( NM_GW_EXT_ENABLED )

typedef P2CONST( uint8, NM_CONST, NM_CONST ) Nm_MapPartEcuPtrType;
#endif

#if defined ( NM_GW_EXT_ENABLED ) || ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )

typedef enum{
  NM_UNINITIALIZED            = 0u,
  NM_AWAKE                    = 1u,
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  NM_SLEEP_WAITANNOUNCESLEEP  = 2u,
#endif
#  if( defined ( NM_GW_EXT_ENABLED ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) ) \
  || ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
  NM_SLEEP_WAITTOKEN          = 3u,
  NM_SLEEP_WAITTOKENLOSS      = 4u,
#endif
  NM_SLEEP_WAITSLEEP          = 5u
}Nm_NetCoordStateType;

typedef uint16 Nm_TimerCounterType;
#endif

typedef struct{
#if defined ( NM_GW_EXT_ENABLED )
  Nm_MapPartEcuPtrType  NM_PART_ECU_TO_ID_PTR;
  Nm_MapPartEcuPtrType  NM_PART_ECU_TO_ACTCH_PTR;
#endif
  Nm_BusNmType          NM_BUS_TYPE;
#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  uint16                NM_SHUTDOWN_TIME;
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  uint16                NM_MSG_CYCLE_TIME;
#endif
#endif
#if defined ( NM_GW_EXT_ENABLED )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  uint16                NM_SHUTDOWN_TIME;
  uint16                NM_MAX_SHUTDOWN_TIME;
#endif
  uint16                NM_MAX_MSG_CYCLE_TIME;
  uint8                 NM_NUMBER_OF_PART_ECUS;
#endif
  uint8                 NM_CHANNEL_ID;
}Nm_LChannelConfigType;

typedef struct{
#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
  uint8  NM_MAIN_FUNCTION_PERIOD;
#endif
  uint8  NM_NUMBER_OF_CHANNELS;
  uint8  NM_NUMBER_OF_SYSTEM_CHANNELS;
#if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  uint8  NM_COORD_ID;
#endif
#if defined ( NM_ONM_EXT_INIT )
  uint8  NM_ONM_EXT_INIT_STATE;
#endif
}Nm_LConfigType;

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )

typedef P2CONST(Nm_SyncNmType, NM_CONST, NM_CONST ) Nm_PbChannelConfigPtrType;
#endif

typedef struct{
#if defined ( NM_USE_EXTENDED_ASR_VERSION_CHECK )
  uint32 Nm_GeneratorVersion;
#endif
#if( NM_CRC_CHECK == STD_ON )
  uint32 Nm_Cfg_PrecompileCRC;
#endif
#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  Nm_PbChannelConfigPtrType Nm_PbChannelConfigPtr;
  uint16 NM_COORD_SHUTDOWN_TIME;
#  if( NM_OSEK_SUPPORT_ENABLED == STD_ON )
  uint8 NM_SYNC_ONM_CHANNEL_ID;
#endif
#endif
  uint16 NM_MAGIC_NUMBER;
}Nm_ConfigType;
#endif

#if defined ( NM_ENABLE_COMM21_SUPPORT )
typedef Nm_ConfigType Nm_BusNm_ConfigType;
#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

#define NM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )

extern CONST( NetworkHandleType, NM_CONST ) Nm_SystemToNmChannelInd[NM_NUMBER_OF_SYS_CHANNELS];
#endif

extern CONST( Nm_LChannelConfigType, NM_CONST ) Nm_LChannelConfiguration[NM_NUMBER_OF_NM_CHANNELS];

#define NM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

extern CONST( Nm_LConfigType, NM_CONST ) Nm_LConfiguration;

#define NM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

#define NM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NotifyNetworkStart[NM_NUMBER_OF_NM_CHANNELS];
#endif
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkStarted[NM_NUMBER_OF_NM_CHANNELS];
#endif

#if defined ( NM_GW_EXT_ENABLED )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_RemoteSleepFilter[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_RemoteWakeupFilter[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkRequested[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkRestartFlag[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_WakeupDetected[NM_NUMBER_OF_NM_CHANNELS];
#endif

#if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#  if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_AbortSleep_BusNm[1];
#else
#if defined ( NM_GW_EXT_ENABLED )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_AbortSleep_BusNm[NM_NUMBER_OF_NM_CHANNELS];
#endif
#endif
#endif

#define NM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"

#if defined ( NM_ONM_STATE_CHANGE_IND )

#define NM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"

extern VAR( Nm_StateType, NM_VAR_NOINIT ) Nm_OnmState[NM_NUMBER_OF_NM_CHANNELS];

extern VAR( Nm_StateType, NM_VAR_NOINIT ) Nm_OnmNetworkRequested[NM_NUMBER_OF_NM_CHANNELS];

#define NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if defined ( NM_GW_EXT_ENABLED ) || defined ( NM_ENABLE_COORD_SYNC_SUPPORT )

#define NM_START_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"

#  if defined ( NM_GW_EXT_ENABLED )
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_PartEcuActiveChannels[NM_NUMBER_OF_NM_CHANNELS];
#if( NM_BUSNM_CANNM_ENABLED == STD_ON )
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_PartEcuReqChannels[NM_NUMBER_OF_NM_CHANNELS];
#endif
#endif

#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_CoordActiveInd[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_CoordSleepInd[NM_NUMBER_OF_NM_CHANNELS];
#endif

#define NM_STOP_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"
#endif

#define NM_START_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"

#if defined ( NM_GW_EXT_ENABLED )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_ChannelActiveTimer[NM_NUMBER_OF_NM_CHANNELS];
#endif

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || \
  ( defined (NM_GW_EXT_ENABLED) && defined (NM_ENABLE_CHANNELTYPE_CANOSEKNM) )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_DelayTimer[NM_NUMBER_OF_NM_CHANNELS];
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_DelayTimer_OsekNm[NM_NUMBER_OF_NM_CHANNELS];
#endif
#endif

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST) Nm_CoordTimeoutTimer[NM_NUMBER_OF_NM_CHANNELS];
#endif
#endif

#define NM_STOP_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )

#define NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"

extern VAR( Nm_NetworkCoordType, NM_VAR_NOINIT_FAST ) Nm_NetworkRequested;
extern VAR( Nm_NetworkCoordType, NM_VAR_NOINIT_FAST ) Nm_NetworkRestartFlag;
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
extern VAR( boolean, NM_VAR_NOINIT_FAST ) Nm_CoordChannel[NM_NUMBER_OF_NM_CHANNELS];
#endif

extern P2CONST( Nm_ConfigType, NM_VAR_NOINIT_FAST, NM_CONST ) Nm_PbConfigPtr;

#define NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if defined ( NM_GW_EXT_ENABLED ) || ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )

#define NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"

#  if defined ( NM_GW_EXT_ENABLED )

extern VAR( Nm_NetCoordStateType, NM_VAR_ZERO_INIT_FAST ) Nm_NetCoordState[NM_NUMBER_OF_NM_CHANNELS];
#endif

#  if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )

extern VAR( Nm_NetCoordStateType, NM_VAR_ZERO_INIT_FAST ) Nm_NetCoordState[1];
#endif

#define NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#define NM_START_SEC_CONST_UNSPECIFIED

#include "MemMap.h"

extern CONST(Nm_ConfigType, NM_CONST) Nm_Configuration0;

#define NM_STOP_SEC_CONST_UNSPECIFIED

#include "MemMap.h"

#define Nm_Configuration                     Nm_Configuration0

#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
#if MAGIC_NUMBER != 268053767
      #error "The magic number of the generated file <C:\_TSS\DAG\MFA2\Target\Appl\GenData\Nm_Cfg.h> is different. Please check time and date of generated files!"
#endif
#else
#define MAGIC_NUMBER 268053767
#endif
#endif
#endif
