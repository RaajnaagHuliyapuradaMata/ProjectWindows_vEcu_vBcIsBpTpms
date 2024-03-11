

#if(!defined ECUM_GENERATED_TYPES_H)
# define ECUM_GENERATED_TYPES_H

# define ECUM_GENERATED_TYPES_MAJOR_VERSION    (7u)
# define ECUM_GENERATED_TYPES_MINOR_VERSION    (7u)
# define ECUM_GENERATED_TYPES_PATCH_VERSION    (0u)

# include "Std_Types.h"

 #include "Os.h"

 #include "ComStack_Types.h"

 #include "Rte_Type.h"

# define ECUM_COMM_USED                                               (0x01u)
# define ECUM_WDGM_USED                                               (0x02u)

# define ECUM_GEN_BOOT_TARGET_PORT                                     (STD_OFF)
# define ECUM_GEN_SHUTDOWN_TARGET_PORT                                 (STD_OFF)
# define ECUM_GEN_STATE_REQUEST_PORT                                   (STD_OFF)
# define ECUM_GEN_MODE_SWITCH_PORT                                     (STD_OFF)
# define ECUM_GEN_APPLICATION_MODE_PORT                                (STD_OFF)

typedef uint8 EcuM_ChannelHandleType;

typedef uint8 EcuM_ModeType;

# define ECUM_MODE_POST_RUN                                           (0)
# define ECUM_MODE_RUN                                                (1)
# define ECUM_MODE_SHUTDOWN                                           (2)
# define ECUM_MODE_SLEEP                                              (3)
# define ECUM_MODE_STARTUP                                            (4)
# define ECUM_MODE_WAKE_SLEEP                                         (5)

typedef uint32 EcuM_WakeupSourceType;

# define ECUM_WKSOURCE_NONE                                           (EcuM_WakeupSourceType)(0u)

#define EcuM_ECUM_WKSOURCE_POWER (EcuM_WakeupSourceType)(1u)
#define EcuM_ECUM_WKSOURCE_RESET (EcuM_WakeupSourceType)(2u)
#define EcuM_ECUM_WKSOURCE_INTERNAL_RESET (EcuM_WakeupSourceType)(4u)
#define EcuM_ECUM_WKSOURCE_INTERNAL_WDG (EcuM_WakeupSourceType)(8u)
#define EcuM_ECUM_WKSOURCE_EXTERNAL_WDG (EcuM_WakeupSourceType)(16u)
#define EcuM_HMI (EcuM_WakeupSourceType)(32u)

# define ECUM_WKSOURCE_ALL_SOURCES                                    (EcuM_WakeupSourceType) (~((EcuM_WakeupSourceType)0u))

typedef struct
{
  EcuM_WakeupSourceType wakeupSource;
  uint8 mcuMode;
  uint8 WatchdogMode_u8;
} EcuM_SleepModeConfigType;

# if((ECUM_GEN_SHUTDOWN_TARGET_PORT == STD_OFF) && (ECUM_GEN_STATE_REQUEST_PORT == STD_OFF))

  typedef uint8 EcuM_StateType;

#  define ECUM_SUBSTATE_MASK                                          (0x0Fu)
#  define ECUM_STATE_STARTUP                                          (0x10u)
#  define ECUM_STATE_STARTUP_ONE                                      (0x11u)
#  define ECUM_STATE_STARTUP_TWO                                      (0x12u)
#  define ECUM_STATE_WAKEUP                                           (0x20u)
#  define ECUM_STATE_WAKEUP_ONE                                       (0x21u)
#  define ECUM_STATE_WAKEUP_VALIDATION                                (0x22u)
#  define ECUM_STATE_WAKEUP_REACTION                                  (0x23u)
#  define ECUM_STATE_WAKEUP_TWO                                       (0x24u)
#  define ECUM_STATE_WAKEUP_WAKESLEEP                                 (0x25u)
#  define ECUM_STATE_WAKEUP_TTII                                      (0x26u)
#  define ECUM_STATE_RUN                                              (0x30u)
#  define ECUM_STATE_APP_RUN                                          (0x32u)
#  define ECUM_STATE_APP_POST_RUN                                     (0x33u)
#  define ECUM_STATE_SHUTDOWN                                         (0x40u)
#  define ECUM_STATE_PREP_SHUTDOWN                                    (0x44u)
#  define ECUM_STATE_GO_SLEEP                                         (0x49u)
#  define ECUM_STATE_GO_OFF_ONE                                       (0x4Du)
#  define ECUM_STATE_GO_OFF_TWO                                       (0x4Eu)
#  define ECUM_STATE_SLEEP                                            (0x50u)
#  define ECUM_STATE_RESET                                            (0x90u)
#  define ECUM_STATE_OFF                                              (0x80u)
#  define ECUM_STATE_ERROR                                            (0xFFu)

# endif

typedef uint8 EcuM_WakeupStatusType;

# define ECUM_WKSTATUS_NONE                                           (0u)
# define ECUM_WKSTATUS_PENDING                                        (1u)
# define ECUM_WKSTATUS_VALIDATED                                      (2u)
# define ECUM_WKSTATUS_EXPIRED                                        (3u)

typedef uint8 EcuM_WakeupReactionType;

# define ECUM_WKACT_RUN                                               (0u)
# define ECUM_WKACT_TTII                                              (2u)
# define ECUM_WKACT_SHUTDOWN                                          (3u)

# if(ECUM_GEN_BOOT_TARGET_PORT == STD_OFF)

  typedef uint8 EcuM_BootTargetType;

#  define ECUM_BOOT_TARGET_APP                                        (0u)
#  define ECUM_BOOT_TARGET_BOOTLOADER                                 (1u)

# endif

# if(ECUM_GEN_STATE_REQUEST_PORT == STD_OFF)

typedef uint8 EcuM_UserType;

# endif

# if(ECUM_GEN_APPLICATION_MODE_PORT == STD_OFF)

typedef uint8 EcuM_AppModeType;

# endif

#define EcuM_EcuMUserConfig_FirstUser (1u)

#define EcuM_EcuMSleepMode (0u)

#define EcuM_TPMSAppMode (OsAppMode)

typedef uint16 EcuM_TTII_DivisorType;
typedef uint16 EcuM_SelfRequestPeriodType;
typedef uint16 EcuM_WakeupTimeoutType;

typedef struct
{
  EcuM_WakeupTimeoutType EcuM_WakeupTimeoutLeft_t;
  EcuM_WakeupTimeoutType EcuM_CheckWakeupTimeoutLeft_t;
  uint8 EcuM_WakeupValState_u8;
  uint8 EcuM_WakeupChkState_u8;
} EcuM_WakeupTimeoutCtrlType;

# define ECUM_WKS_TIMEOUT_STATE_STOPPED                               (0)
# define ECUM_WKS_TIMEOUT_STATE_STARTED                               (1)

typedef struct
{
  EcuM_StateType DefaultState_t;
  uint8 DefaultSleepMode_u8;
} EcuM_DefaultShutdownTargetType;

typedef CONSTP2CONST(struct EcuM_WakeupSourceDefType, TYPEDEF, ECUM_APPL_CONFIG) EcuM_WakeupSourceDefPtrType;

typedef uint8 EcuM_IntFunctionCallType;

# define ECUM_CALL_MCU_PERFORM_RESET                                  (0u)
# define ECUM_CALL_SCHM_INIT                                          (1u)
# define ECUM_CALL_DEM_INIT                                           (2u)
# define ECUM_CALL_DEM_SHUTDOWN                                       (3u)
# define ECUM_CALL_COMM_DEINIT                                        (4u)
# define ECUM_CALL_NVM_READALL                                        (5u)
# define ECUM_CALL_NVM_WRITEALL                                       (6u)
# define ECUM_CALL_NVM_CANCEL_WRITEALL                                (7u)
# define ECUM_CALL_RTE_START                                          (8u)
# define ECUM_CALL_RTE_STOP                                           (9u)
# define ECUM_CALL_OS_SHUTDOWN_OS                                     (10u)
# define ECUM_CALL_OS_GET_RES_SCHEDULER                               (11u)
# define ECUM_CALL_OS_RELEASE_RES_SCHEDULER                           (12u)
# define ECUM_CALL_COMM_RUN_MODE_IND                                  (13u)

typedef P2FUNC (void, ECUM_CODE, EcuM_DriverInitListFuncType)(void);
typedef P2FUNC (void, ECUM_CODE, EcuM_ModeSwitchEventFuncType)(uint8 modeEvent_u8);

typedef struct
{

  uint32 EcuM_GeneratorVersion;

  CONSTP2CONST(EcuM_SleepModeConfigType, ECUM_VAR_NOINIT, ECUM_APPL_CONFIG) SleepModeList_pt;

  EcuM_WakeupSourceDefPtrType WakeupSourceList_pt;

  CONSTP2CONST(uint8, ECUM_VAR_NOINIT, ECUM_APPL_CONFIG) WatchdogManagerModes_pau8;

  CONSTP2CONST(uint8, ECUM_VAR_NOINIT, ECUM_APPL_CONFIG) CallId_au8;

  CONSTP2CONST(uint8, ECUM_VAR_NOINIT, ECUM_APPL_CONFIG) TTII_DivisorList_pt;

  CONSTP2CONST(uint8, ECUM_VAR_NOINIT, ECUM_APPL_CONFIG) TTII_SuccesorList_pt;
  EcuM_ModeSwitchEventFuncType ModeEventFunction_pt;
  EcuM_DriverInitListFuncType DriverInitListOne;
  EcuM_DriverInitListFuncType DriverInitListTwo;
  EcuM_DriverInitListFuncType DriverInitListThree;
  EcuM_DriverInitListFuncType DriverRestart;
  uint32 MaxWakeupSourceValue_u32;
  EcuM_AppModeType DefaultAppMode_t;
  EcuM_DefaultShutdownTargetType DefaultShutdownTarget_t;
  EcuM_SelfRequestPeriodType  SelfRequestPeriod_t;
  uint8 MaxNumberOfWakeupSources_u8;
  uint8 MaxEcuMUsersCount_u8;
  uint8 MaxUsersCount_u8;
  uint8 MaxComMUsersCount_u8;
  uint8 MaxSleepModes_u8;
  uint8 Max_TTII_SleepModes_u8;
  uint8 UsedModules_u8;
} EcuM_PbcfgConfigType;

typedef EcuM_PbcfgConfigType EcuM_ConfigType;

typedef P2VAR(EcuM_ConfigType, TYPEDEF, ECUM_APPL_CONFIG) EcuM_ConfigRefType;

#endif

