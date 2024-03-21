

#if !defined (NM_H)
#define NM_H

#include "v_cfg.h"
#if defined ( VGEN_ENABLE_NM_OSEK_D ) && !defined ( VGEN_ENABLE_IF_ASRIFCAN )
#include "NmIf_Cfg.h"
#else
#include "Nm_Cfg.h"
#endif
#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#include "ComM_Nm.h"
#if( NM_BUSNM_CANNM_ENABLED == STD_ON )
#include "CanNm.h"
#endif
#if( NM_BUSNM_FRNM_ENABLED == STD_ON )
#include "FrNm.h"
#endif
#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )
#include "NmFiatB.h"
#endif
#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )
#include "NmFiatC.h"
#endif
#endif

#if(  (NM_STACKTYPES_MAJOR_VERSION != (0x02u)) \
    || (NM_STACKTYPES_MINOR_VERSION != (0x27u)) \
    || (NM_STACKTYPES_PATCH_VERSION != (0x01u)))
# error "Vendor specific version numbers of NmStackTypes.h and Nm.h are inconsistent!"
#endif

#define NM_ASRNMIF_VERSION          (0x0227u)
#define NM_ASRNMIF_RELEASE_VERSION    (0x01u)

#define NM_VENDOR_ID              (30u)
#define NM_MODULE_ID              (29u)

#define NM_AR_MAJOR_VERSION       (0x01u)
#define NM_AR_MINOR_VERSION       (0x00u)
#define NM_AR_PATCH_VERSION       (0x01u)

#define NM_SW_MAJOR_VERSION       (NM_ASRNMIF_VERSION >> 8u)
#define NM_SW_MINOR_VERSION       (NM_ASRNMIF_VERSION & 0x00FFu)
#define NM_SW_PATCH_VERSION       (NM_ASRNMIF_RELEASE_VERSION)

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else

#define NM_INIT_ID                                 (0x00u)
#define NM_PASSIVESTARTUP_ID                       (0x01u)
#if(NM_PASSIVE_MODE_ENABLED == STD_OFF )
#define NM_NETWORKREQUEST_ID                      (0x02u)
#define NM_NETWORKRELEASE_ID                      (0x03u)
#endif
#if( NM_COM_CONTROL_ENABLED == STD_ON )
#define NM_DISABLENMCOMMUNICATION_ID              (0x04u)
#define NM_ENABLENMCOMMUNICATION_ID               (0x05u)
#endif
#if( NM_USER_DATA_ENABLED == STD_ON )
#  if(NM_PASSIVE_MODE_ENABLED == STD_OFF )
#define NM_SETUSERDATA_ID                        (0x06u)
#endif
#define NM_GETUSERDATA_ID                         (0x07u)
#endif
#if( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
#define NM_GETPDUDATA_ID                          (0x08u)
#endif
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
#define NM_REPEATMESSAGEREQUEST_ID                (0x09u)
#endif
#if( NM_NODE_ID_ENABLED == STD_ON )
#define NM_GETNODEIDENTIFIER_ID                   (0x0Au)
#define NM_GETLOCALNODEIDENTIFIER_ID              (0x0Bu)
#endif
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#define NM_CHECKREMOTESLEEPIND_ID                 (0x0Du)
#endif
#define NM_GETSTATE_ID                             (0x0Eu)
#if( NM_VERSION_INFO_API == STD_ON )
#define NM_GETVERSIONINFO_ID                      (0x0Fu)
#endif
#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
#define NM_MAINFUNCTION_ID                        (0x10u)
#endif

#if( NM_DEV_ERROR_DETECT == STD_ON )
#define NM_E_NO_INIT                  ((uint8)0x01u)
#define NM_E_INVALID_CHANNEL          ((uint8)0x02u)
#define NM_E_INIT_FAILED              ((uint8)0x03u)
#define NM_E_NULL_POINTER             ((uint8)0x13u)
#  if defined ( NM_ENABLE_COORD_SYNC_SUPPORT )
#define NM_E_PRIORITY_COLLISION      ((uint8)0x20u)
#define NM_E_SLEEPBIT_ERROR          ((uint8)0x21u)
#endif
#endif
#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )

#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )

#  if( (NM_ASRNMCLASSB_FIAT_VERSION < (0x0100u)) \
      || ( (NM_ASRNMCLASSB_FIAT_VERSION == (0x0100u)) && (NM_ASRNMCLASSB_FIAT_RELEASE_VERSION < (0x00u)) ) )
#error "NmFiatB has to be provided at least with version 1.00.00"
#endif
#endif

#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )

#  if( (NM_ASRNMPWRTRAIN_FIAT_VERSION < (0x0100u)) \
      || ( (NM_ASRNMPWRTRAIN_FIAT_VERSION == (0x0100u)) && (NM_ASRNMPWRTRAIN_FIAT_RELEASE_VERSION < (0x00u)) ) )
#error "NmFiatC has to be provided at least with version 1.00.00"
#endif
#endif
#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )

#if( NM_BUSNM_CANNM_ENABLED == STD_ON )

#define NmCallBusNmFunction( function, channel )                              CanNm_##function( (channel) )

#define NmCallBusNmFunction_1_Param( function, channel, param )               CanNm_##function( (channel), (param) )

#define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )      CanNm_##function( (channel), (param1), (param2) )
#else
#  if( NM_BUSNM_FRNM_ENABLED == STD_ON )

#define NmCallBusNmFunction( function, channel )                             FrNm_##function( (channel) )

#define NmCallBusNmFunction_1_Param( function, channel, param )              FrNm_##function( (channel), (param) )

#define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )     FrNm_##function( (channel), (param1), (param2) )
#else
#if defined ( NM_ENABLE_CHANNELTYPE_NMFIATB )

#    define NmCallBusNmFunction( function, channel )                            NmFiatB_##function( (channel) )

#    define NmCallBusNmFunction_1_Param( function, channel, param )             NmFiatB_##function( (channel), (param) )

#    define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )    NmFiatB_##function( (channel), (param1), (param2) )
#   else
#    if defined ( NM_ENABLE_CHANNELTYPE_NMFIATC )

#     define NmCallBusNmFunction( function, channel )                           NmFiatC_##function( (channel) )

#     define NmCallBusNmFunction_1_Param( function, channel, param )            NmFiatC_##function( (channel), (param) )

#     define NmCallBusNmFunction_2_Param( function, channel, param1, param2 )   NmFiatC_##function( (channel), (param1), (param2) )
#    else
#     error "NM configuration error: Macro Layer Optimization enabled but no corresponding BusNm found!"
#    endif
#endif
#endif
#endif

#define Nm_Init( cfgPtr )

#define Nm_InitMemory()

#if( NM_VERSION_INFO_API == STD_ON )
#define Nm_GetVersionInfo( NmVerInfoPtr )    { if( (NmVerInfoPtr) != NULL_PTR ) { \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->vendorID = (uint16)NM_VENDOR_ID; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->moduleID = (uint8) NM_MODULE_ID; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->instanceID = (uint8)0x00u; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->sw_major_version = (uint8)NM_SW_MAJOR_VERSION; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->sw_minor_version = (uint8)NM_SW_MINOR_VERSION; \
                                                   ((Std_VersionInfoType*)(NmVerInfoPtr))->sw_patch_version = (uint8)NM_SW_PATCH_VERSION; \
                                                 } \
                                               }
#endif

#define Nm_PassiveStartUp( channel )                                     (NmCallBusNmFunction( PassiveStartUp, (channel) ))
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF )

#define Nm_NetworkRequest( channel )                                    (NmCallBusNmFunction( NetworkRequest, (channel) ))

#define Nm_NetworkRelease( channel )                                    (NmCallBusNmFunction( NetworkRelease, (channel) ))
#endif
#if( NM_USER_DATA_ENABLED == STD_ON )
#  if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_ENABLED == STD_OFF )

#define Nm_SetUserData( channel,  nmUserDataPtr )                      (NmCallBusNmFunction_1_Param( SetUserData, (channel), (nmUserDataPtr) ))
#endif

#define Nm_GetUserData( channel,  nmUserDataPtr )                       (NmCallBusNmFunction_1_Param( GetUserData, (channel), (nmUserDataPtr) ))
#endif
#if( NM_NODE_ID_ENABLED == STD_ON )

#define Nm_GetNodeIdentifier( channel,  nmNodeIdPtr )                   (NmCallBusNmFunction_1_Param( GetNodeIdentifier, (channel), (nmNodeIdPtr) ))

#define Nm_GetLocalNodeIdentifier( channel,  nmNodeIdPtr )              (NmCallBusNmFunction_1_Param( GetLocalNodeIdentifier, (channel), (nmNodeIdPtr) ))
#endif
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )

#define Nm_RepeatMessageRequest( channel )                              (NmCallBusNmFunction( RepeatMessageRequest, (channel) ))
#endif
#if( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )

#define Nm_GetPduData( channel, nmPduDataPtr )                          (NmCallBusNmFunction_1_Param( GetPduData, (channel), (nmPduDataPtr) ))
#endif
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )

#define Nm_CheckRemoteSleepIndication( channel,  nmRemoteSleepIndPtr )  (NmCallBusNmFunction_1_Param( CheckRemoteSleepIndication, (channel), (nmRemoteSleepIndPtr) ))
#endif

#define Nm_GetState( channel,  nmStatePtr, nmModePtr )                   (NmCallBusNmFunction_2_Param( GetState, (channel), (nmStatePtr), (nmModePtr) ))
#if( NM_COM_CONTROL_ENABLED == STD_ON )
#  if( NM_BUSNM_FRNM_ENABLED == STD_ON ) || ( NM_PASSIVE_MODE_ENABLED == STD_ON )

#define Nm_EnableCommunication( channel )                              (NM_E_NOT_EXECUTED)
#define Nm_DisableCommunication( channel )                             (NM_E_NOT_EXECUTED)
#else

#define Nm_EnableCommunication( channel )                              (NmCallBusNmFunction( EnableCommunication, (channel) ))

#define Nm_DisableCommunication( channel )                             (NmCallBusNmFunction( DisableCommunication, (channel) ))
#endif
#endif

#define Nm_NetworkStartIndication( channel )                             (ComM_Nm_NetworkStartIndication( (channel) ))

#define Nm_NetworkMode( channel )                                        (ComM_Nm_NetworkMode( (channel) ))
#if( NM_BUSNM_FRNM_ENABLED == STD_ON )
#else

#define Nm_PrepareBusSleepMode( channel )                               (ComM_Nm_PrepareBusSleepMode( (channel) ))
#endif

#define Nm_BusSleepMode( channel )                                       (ComM_Nm_BusSleepMode( (channel) ))

#if( NM_STATE_CHANGE_IND_ENABLED == STD_ON )
#  if defined ( UL_Nm_StateChangeNotification )

#define Nm_StateChangeNotification( channel, prevState, currState )    UL_Nm_StateChangeNotification( channel, prevState, currState )
#else
#define Nm_StateChangeNotification( channel, prevState, currState )
#endif
#endif
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
#  if defined ( UL_Nm_RemoteSleepIndication )

#define Nm_RemoteSleepIndication( channel )                            UL_Nm_RemoteSleepIndication( channel )
#else
#define Nm_RemoteSleepIndication( channel )
#endif
#  if defined ( UL_Nm_RemoteSleepCancellation )

#define Nm_RemoteSleepCancellation( channel )                          UL_Nm_RemoteSleepCancellation( channel )
#else
#define Nm_RemoteSleepCancellation( channel )
#endif
#endif
#if( NM_PDU_RX_INDICATION_ENABLED == STD_ON )
#  if defined ( UL_Nm_PduRxIndication )

#define Nm_PduRxIndication( channel )                                  UL_Nm_PduRxIndication( channel )
#else
#define Nm_PduRxIndication( channel )
#endif
#endif
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
#  if defined ( UL_Nm_RepeatMessageIndication )

#define Nm_RepeatMessageIndication( channel )                          UL_Nm_RepeatMessageIndication( channel )
#else
#define Nm_RepeatMessageIndication( channel )
#endif
#endif
#if( NM_PASSIVE_MODE_ENABLED == STD_OFF )
#  if defined ( UL_Nm_TxTimeoutException )

#define Nm_TxTimeoutException( channel )                               UL_Nm_TxTimeoutException( channel )
#else
#define Nm_TxTimeoutException( channel )
#endif
#endif
#if( NM_CAR_WAKE_UP_RX_ENABLED == STD_ON )
#  if defined ( UL_Nm_CarWakeUpIndication )

#define Nm_CarWakeUpIndication( channel )                              UL_Nm_CarWakeUpIndication( channel )
#else
#define Nm_CarWakeUpIndication( channel )
#endif
#endif
#endif

#if defined ( NM_MACRO_LAYER_OPT_ENABLED )
#else
#define NM_START_SEC_CONST_8BIT
#include "MemMap.h"

extern CONST(uint8, NM_CONST) Nm_MainVersion;
extern CONST(uint8, NM_CONST) Nm_SubVersion;
extern CONST(uint8, NM_CONST) Nm_ReleaseVersion;

#define NM_STOP_SEC_CONST_8BIT
#include "MemMap.h"

#define NM_START_SEC_CODE
#include "MemMap.h"

extern FUNC( void, NM_CODE ) Nm_Init( P2CONST( Nm_ConfigType, AUTOMATIC, NM_CONST ) nmConfigPtr );
#if( NM_VERSION_INFO_API == STD_ON )
extern FUNC( void, NM_CODE ) Nm_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, NM_APPL_VAR ) NmVerInfoPtr );
#endif

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_MainFunction( void );
#endif

extern FUNC( Nm_ReturnType, NM_CODE ) Nm_PassiveStartUp( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );

#if( NM_PASSIVE_MODE_ENABLED == STD_OFF )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_NetworkRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_NetworkRelease( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
#endif

#if( NM_USER_DATA_ENABLED == STD_ON )
#  if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_COM_USER_DATA_ENABLED == STD_OFF )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_SetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2CONST( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr );
#endif

extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetUserData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmUserDataPtr );
#endif

#if( NM_NODE_ID_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr );
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetLocalNodeIdentifier( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmNodeIdPtr );
#endif

#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_NODE_DETECTION_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_RepeatMessageRequest( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
#endif

#if( ( NM_NODE_ID_ENABLED == STD_ON ) || ( NM_USER_DATA_ENABLED == STD_ON ) )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetPduData( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( uint8, AUTOMATIC, NM_APPL_VAR ) nmPduDataPtr );
#endif

#if( NM_PASSIVE_MODE_ENABLED == STD_OFF ) && ( NM_REMOTE_SLEEP_IND_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_CheckRemoteSleepIndication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( boolean, AUTOMATIC, NM_APPL_VAR ) nmRemoteSleepIndPtr );
#endif

extern FUNC( Nm_ReturnType, NM_CODE ) Nm_GetState( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle, CONSTP2VAR( Nm_StateType, AUTOMATIC, NM_APPL_VAR ) nmStatePtr, CONSTP2VAR( Nm_ModeType, AUTOMATIC, NM_APPL_VAR ) nmModePtr );

#if( NM_COM_CONTROL_ENABLED == STD_ON )
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_EnableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
extern FUNC( Nm_ReturnType, NM_CODE ) Nm_DisableCommunication( CONST( NetworkHandleType, AUTOMATIC ) nmChannelHandle );
#endif

#if( NM_COORDINATOR_SUPPORT_ENABLED == STD_ON )
extern FUNC( void, NM_CODE ) Nm_InitMemory( void );
#else
#define Nm_InitMemory()
#endif

#define NM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

