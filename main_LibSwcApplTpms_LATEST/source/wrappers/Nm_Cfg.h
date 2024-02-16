/* -----------------------------------------------------------------------------
  Filename:    Nm_Cfg.h
  Description: Toolversion: 19.00.32.01.50.01.22.00.00.00
               
               Serial Number: CBD1500122
               Customer Info: Huf Electronics Bretten GmbH
                              Package: MSR Daimler SLP10
                              Micro: R7F7010133AFP
                              Compiler: Green Hills 6.1.4
               
               
               Generator Fwk   : GENy 
               Generator Module: Nm
               
               Configuration   : C:\_TSS\DAG\MFA2\Target\Config\ECUC\HufTPMS_G6_F1L.ecuc.vdsxml
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    F1L
               
               Channel "HMI":
                       Databasefile: 
                       Bussystem:    CAN
                       Manufacturer: DaimlerChrysler
                       Node:         CanStateManagerConfiguration

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(NM_CFG_H)
#define NM_CFG_H

#include "ComStack_Types.h"
#include "NmStack_Types.h"
#define NM_ASRNMIFDLL_VERSION                0x0225u
#define NM_ASRNMIFDLL_RELEASE_VERSION        0x01u
#define NM_NUMBER_OF_SYS_CHANNELS            1u
#define NM_NUMBER_OF_NM_CHANNELS             1u
/* NmChannelId symbolic name defines */
#define Nm_HMI                               0u
/* Nm instance properties */
/* START of Checksum include for
  - NmPrecompileCRC */
#define NM_BUSNM_CANNM_ENABLED STD_ON
#define NM_BUSNM_FRNM_ENABLED STD_OFF
#define NM_ENABLE_CHANNELTYPE_CANNM
/* END of Checksum include for
  - NmPrecompileCRC */

/* Options */
/* START of Checksum include for
  - NmPrecompileCRC */
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
/* LT Options */


/* Integration */
#define NM_USE_DUMMY_STATEMENT STD_ON

/* END of Checksum include for
  - NmPrecompileCRC */

/* CRC check */
/* START of Checksum include for
  - NmPrecompileCRC */
#define NM_CRC_CHECK                         STD_OFF
/* END of Checksum include for
  - NmPrecompileCRC */

#define NM_PRECOMPILE_CRC                    (uint32) 0xDBBC99D5u
/* AMD Runtime Measurement */
/* START of Checksum include for
  - NmPrecompileCRC */
#define NM_AMD_RUNTIME_MEASUREMENT STD_OFF
/* END of Checksum include for
  - NmPrecompileCRC */

/* Coordinator support */
/* START of Checksum include for
  - NmPrecompileCRC */
#define NM_COORDINATOR_SUPPORT_ENABLED STD_OFF
#define NM_OSEK_SUPPORT_ENABLED STD_OFF
/* END of Checksum include for
  - NmPrecompileCRC */


/* Callbacks to Upper Layer */
/* Notification that a NM timeout error occurred */

/* --------------------- Data Types and Structures --------------------- */
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
/* Define dummy Config prototype */
typedef uint8 Nm_ConfigType;
#else
# if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
#  define NM_CHANNEL_IDX              (channel)
# else
#  define NM_CHANNEL_IDX              (nmChannelHandle)
# endif

# define NM_RM_BSM     ((uint8)0x01)
# define NM_RM_PBSM    ((uint8)0x02)
# define NM_NO_RM      ((uint8)0x04)
# define NM_NO_RS      ((uint8)0x08)
# define NM_RM_RS      ((uint8)0x10)
# define NM_RM_NO      ((uint8)0x20)

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
#   define NM_SUPPRESSNOTIFYSTART     ((uint8)0x00)
#   define NM_NOTIFYSTARTSLEEP        ((uint8)0x01)
#   define NM_NOTIFYSTARTPREPSLEEP    ((uint8)0x02)
#  endif
# endif

/* Type that identifies a bus specific channel */
typedef enum {
  NM_BUSNM_CANNM      = 0x00u,
  NM_BUSNM_FRNM       = 0x01u,
  NM_BUSNM_LINNM      = 0x02u,
# if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
  NM_BUSNM_OSEKNM     = 0x03u,
  NM_BUSNM_CANOSEKNM  = 0x04u,
# endif
# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
  NM_BUSNM_NMFIATB    = 0x05u,
# endif
# if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
  NM_BUSNM_NMFIATC    = 0x06u,
# endif
  NM_BUSNM_UNDEF      = 0xFFu
} Nm_BusNmType;

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* Type that identifies if a channel shall be coordinated or not */
typedef enum {
  NM_COORD_SEL            = 0x00,
  NM_COORD_SYN_ACTIVE     = 0x01
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  ,NM_COORD_SYN_PASSIVE   = 0x02
#  endif
} Nm_SyncNmType;

/* Type for storing network requests */
#  if ( NM_NUMBER_OF_NM_CHANNELS <= 32 )
typedef uint32 Nm_NetworkCoordType;
#  else
#   error: "NM Interface configuration error: NM Interface with Coordinator Support ON does not support more than 32 channels!"
#  endif
# endif

# if defined ( NM_GW_EXT_ENABLED )
/* Pointer type to partial network information */
typedef P2CONST( uint8, NM_CONST, NM_CONST ) Nm_MapPartEcuPtrType;
# endif

# if defined ( NM_GW_EXT_ENABLED ) || ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* State type for gateway / coordination handling */
typedef enum
{
  NM_UNINITIALIZED            = 0u,
  NM_AWAKE                    = 1u,
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  NM_SLEEP_WAITANNOUNCESLEEP  = 2u,
#  endif
#  if ( defined ( NM_GW_EXT_ENABLED ) && defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM ) ) \
  || ( ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) && ( NM_OSEK_SUPPORT_ENABLED == STD_ON ) )
  NM_SLEEP_WAITTOKEN          = 3u,
  NM_SLEEP_WAITTOKENLOSS      = 4u,
#  endif
  NM_SLEEP_WAITSLEEP          = 5u
} Nm_NetCoordStateType;

/* Type of the timer/counters. */
typedef uint16 Nm_TimerCounterType;
# endif

/* Structures for channel specific configuration parameters */
typedef struct
{
# if defined ( NM_GW_EXT_ENABLED )
  Nm_MapPartEcuPtrType  NM_PART_ECU_TO_ID_PTR;
  Nm_MapPartEcuPtrType  NM_PART_ECU_TO_ACTCH_PTR;
# endif
  Nm_BusNmType          NM_BUS_TYPE;                        /* Bus NM type for the respective instance of the NM */
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  uint16                NM_SHUTDOWN_TIME;                   /* Channel specific shutdown time */
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  uint16                NM_MSG_CYCLE_TIME;                  /* Channel specific message cycle time */
#  endif
# endif
# if defined ( NM_GW_EXT_ENABLED )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
  uint16                NM_SHUTDOWN_TIME;                   /* Channel specific shutdown time */
  uint16                NM_MAX_SHUTDOWN_TIME;               /* Channel specific Maximum NM shutdown time for CAN-OSEK Channels */
#  endif
  uint16                NM_MAX_MSG_CYCLE_TIME;              /* Channel specific message cycle time */
  uint8                 NM_NUMBER_OF_PART_ECUS;             /* Channel specific number of relevant ECUs for GW algorithm */
# endif
  uint8                 NM_CHANNEL_ID;                      /* Channel ID configured for the respective instance of the NM */
} Nm_LChannelConfigType;

/* Structure for module configuration parameters */
typedef struct
{
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
  uint8  NM_MAIN_FUNCTION_PERIOD;         /* Call cycle of Nm_MainFunction */
# endif
  uint8  NM_NUMBER_OF_CHANNELS;           /* Number of NM Channels */
  uint8  NM_NUMBER_OF_SYSTEM_CHANNELS;    /* Number of System Channels */
# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
  uint8  NM_COORD_ID;                     /* Coordination Priority */
# endif
# if defined ( NM_ONM_EXT_INIT )
  uint8  NM_ONM_EXT_INIT_STATE;           /* OSEK NM extended init state */
# endif
} Nm_LConfigType;

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* Structure for post-build (multi-config) configuration parameters */
typedef P2CONST(Nm_SyncNmType, NM_CONST, NM_CONST ) Nm_PbChannelConfigPtrType;
# endif

typedef struct {
# if defined ( NM_USE_EXTENDED_ASR_VERSION_CHECK )
  uint32 Nm_GeneratorVersion;
# endif
# if ( NM_CRC_CHECK == STD_ON )
  uint32 Nm_Cfg_PrecompileCRC;
# endif
# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
  Nm_PbChannelConfigPtrType Nm_PbChannelConfigPtr;
  uint16 NM_COORD_SHUTDOWN_TIME;
#  if ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
  uint8 NM_SYNC_ONM_CHANNEL_ID;
#  endif
# endif
  uint16 NM_MAGIC_NUMBER;
} Nm_ConfigType;

#endif /* else NM_MACRO_LAYER_OPT_ENABLED */

#if defined ( NM_ENABLE_COMM21_SUPPORT )
typedef Nm_ConfigType Nm_BusNm_ConfigType;
#endif

/* --------------------- Configuration Data Prototypes --------------------- */
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

#define NM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if defined ( NM_CFG_VAR_POST_COMP_ENABLED ) || ( NM_NUMBER_OF_NM_CHANNELS != NM_NUMBER_OF_SYS_CHANNELS )
/* Channel indirection: System Channel handle to NM channel handle */
extern CONST( NetworkHandleType, NM_CONST ) Nm_SystemToNmChannelInd[NM_NUMBER_OF_SYS_CHANNELS];
# endif

/* Channel Configuration of Generic Network Management. */
extern CONST( Nm_LChannelConfigType, NM_CONST ) Nm_LChannelConfiguration[NM_NUMBER_OF_NM_CHANNELS];

#define NM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#define NM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Configuration of Network Management Interface */
extern CONST( Nm_LConfigType, NM_CONST ) Nm_LConfiguration;

#define NM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* else NM_MACRO_LAYER_OPT_ENABLED */

/* --------------------- Module Data Prototypes --------------------- */
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

/* ----------- Local 8 Bit Data definitions without initialization need ----------- */
#define NM_START_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || defined ( NM_GW_EXT_ENABLED )
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NotifyNetworkStart[NM_NUMBER_OF_NM_CHANNELS];
#  endif
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkStarted[NM_NUMBER_OF_NM_CHANNELS];
# endif

# if defined ( NM_GW_EXT_ENABLED )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_RemoteSleepFilter[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_RemoteWakeupFilter[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkRequested[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_NetworkRestartFlag[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT ) Nm_WakeupDetected[NM_NUMBER_OF_NM_CHANNELS];
# endif

# if defined ( NM_ENABLE_COORD_SYNC_SUPPORT ) || ( NM_OSEK_SUPPORT_ENABLED == STD_ON )
#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_AbortSleep_BusNm[1];
#  else
#   if defined ( NM_GW_EXT_ENABLED )
extern VAR( uint8, NM_VAR_NOINIT ) Nm_AbortSleep_BusNm[NM_NUMBER_OF_NM_CHANNELS];
#   endif
#  endif
# endif

#define NM_STOP_SEC_VAR_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if defined ( NM_ONM_STATE_CHANGE_IND )
/* ----------- Local Data definitions with unspecified size without initialization need ----------- */
#define NM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

/* Current Nm State of the OSEK NM used for state change notifications */
extern VAR( Nm_StateType, NM_VAR_NOINIT ) Nm_OnmState[NM_NUMBER_OF_NM_CHANNELS];

/* Requested Nm State if outside Bus Sleep and Wait Bus Sleep */
extern VAR( Nm_StateType, NM_VAR_NOINIT ) Nm_OnmNetworkRequested[NM_NUMBER_OF_NM_CHANNELS];

#define NM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif /* defined ( NM_ONM_STATE_CHANGE_IND ) */

# if defined ( NM_GW_EXT_ENABLED ) || defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
/* ----------- Local 8 Bit Data definitions with frequent access without initialization need ----------- */
#define NM_START_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  if defined ( NM_GW_EXT_ENABLED )
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_PartEcuActiveChannels[NM_NUMBER_OF_NM_CHANNELS];
#   if ( NM_BUSNM_CANNM_ENABLED == STD_ON )
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_PartEcuReqChannels[NM_NUMBER_OF_NM_CHANNELS];
#   endif
#  endif

#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_CoordActiveInd[NM_NUMBER_OF_NM_CHANNELS];
extern VAR( uint8, NM_VAR_NOINIT_FAST ) Nm_CoordSleepInd[NM_NUMBER_OF_NM_CHANNELS];
#  endif

#define NM_STOP_SEC_VAR_FAST_NOINIT_8BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

/* ----------- Local 16 Bit Data definitions with frequent access without initialization need ----------- */
#define NM_START_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if defined ( NM_GW_EXT_ENABLED )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_ChannelActiveTimer[NM_NUMBER_OF_NM_CHANNELS];
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON ) || \
  ( defined (NM_GW_EXT_ENABLED) && defined (NM_ENABLE_CHANNELTYPE_CANOSEKNM) )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_DelayTimer[NM_NUMBER_OF_NM_CHANNELS];
#  if defined ( NM_ENABLE_CHANNELTYPE_CANOSEKNM )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST ) Nm_DelayTimer_OsekNm[NM_NUMBER_OF_NM_CHANNELS];
#  endif
# endif

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
extern VAR( Nm_TimerCounterType, NM_VAR_NOINIT_FAST) Nm_CoordTimeoutTimer[NM_NUMBER_OF_NM_CHANNELS];
#  endif
# endif

#define NM_STOP_SEC_VAR_FAST_NOINIT_16BIT
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

# if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* ----------- Local Data definitions with unspecified size frequent access without initialization need ----------- */
#define NM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

extern VAR( Nm_NetworkCoordType, NM_VAR_NOINIT_FAST ) Nm_NetworkRequested;
extern VAR( Nm_NetworkCoordType, NM_VAR_NOINIT_FAST ) Nm_NetworkRestartFlag;
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
extern VAR( boolean, NM_VAR_NOINIT_FAST ) Nm_CoordChannel[NM_NUMBER_OF_NM_CHANNELS];
#  endif

/* Pointer to (Postbuild) Channel Configuration */
extern P2CONST( Nm_ConfigType, NM_VAR_NOINIT_FAST, NM_CONST ) Nm_PbConfigPtr;

#define NM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

# if defined ( NM_GW_EXT_ENABLED ) || ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* ----------- Local Data definitions with unspecified size frequent access with initialization need ----------- */
#define NM_START_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */

#  if defined ( NM_GW_EXT_ENABLED )
/* NM Gateway State */
extern VAR( Nm_NetCoordStateType, NM_VAR_ZERO_INIT_FAST ) Nm_NetCoordState[NM_NUMBER_OF_NM_CHANNELS];
#  endif

#  if ( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
/* NM Coordinator State */
extern VAR( Nm_NetCoordStateType, NM_VAR_ZERO_INIT_FAST ) Nm_NetCoordState[1];
#  endif

#define NM_STOP_SEC_VAR_FAST_ZERO_INIT_UNSPECIFIED
#include "MemMap.h"  /* PRQA S 5087 */ /* MD_MSR_19.1 */
# endif

#endif /* else NM_MACRO_LAYER_OPT_ENABLED */
/* Generated Configuration declarations */
#define NM_START_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"

extern CONST(Nm_ConfigType, NM_CONST) Nm_Configuration0;

#define NM_STOP_SEC_CONST_UNSPECIFIED
/* PRQA S 5087 1 */ /* MD_MSR_19.1 */
#include "MemMap.h"


#define Nm_Configuration                     Nm_Configuration0


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 268053767
      #error "The magic number of the generated file <C:\_TSS\DAG\MFA2\Target\Appl\GenData\Nm_Cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 268053767
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* NM_CFG_H */
