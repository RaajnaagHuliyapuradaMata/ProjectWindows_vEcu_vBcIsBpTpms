

#if !defined(DEM_CFG_H)
#define DEM_CFG_H

#define DIAG_ASRDEM_GENTOOL_GENY_MAJOR_VERSION 0x03u
#define DIAG_ASRDEM_GENTOOL_GENY_MINOR_VERSION 0x14u
#define DIAG_ASRDEM_GENTOOL_GENY_PATCH_VERSION 0x01u

#define DEM_VERSION_INFO_API                 STD_OFF
#define DEM_DEV_ERROR_DETECT                 STD_OFF
#define DEM_CRC_CHECK                        STD_OFF
#define DEM_DAIMLER_AMD_RUNTIME_MEASUREMENT  STD_OFF
#define DEM_MAX_NUMBER_OF_EVENTS             65535
#define DEM_TYPE_OF_ORIGIN_SUPPORTED         5
#define DEM_ENABLE_WARNINGINDICATOR_STATUS   STD_OFF
#define DEM_ENABLE_PENDINGDTC_STATUS         STD_OFF
#define DEM_OPERATION_CYCLE_STATUS_STORAGE   STD_OFF
#define DEM_ENABLE_TIME_BASED_DEBOUNCE       STD_ON
#define DEM_STATUS_BIT_STORAGE_TEST_FAILED   STD_ON
#define DEM_STATUS_BIT_STORAGE_CONFIRMED_DTC STD_OFF
#if ! defined (V_USE_DUMMY_STATEMENT)
# error "The define V_USE_DUMMY_STATEMENT shall be defined either in Compiler_Cfg.h or as parameter for the Compiler"
#elif   (V_USE_DUMMY_STATEMENT == STD_OFF)
#define DEM_IGNORE_UNUSED_ARG(arg)
#else
#define DEM_IGNORE_UNUSED_ARG(arg)           ((void)(arg))
#endif

#define DEM_CONFIG_VARIANT                   1

#define DEM_USE_FIM_NOTIFICATION_API         STD_OFF
#define DEM_USE_NVM                          STD_ON
#define DEM_NVM_WRITE_AFTER_CLEAR            STD_OFF
#define DEM_NVM_WRITE_AFTER_CONFIRM          STD_OFF
#define DEM_SUPPORT_OCCURRENCE_COUNTER       STD_OFF
#define DEM_REDUCED_DCM_ARGUMENT_CHECK       STD_ON
#define DEM_REMOVE_NEEDLESS_AUTOSAR_API      STD_ON
#define DEM_REMOVE_1908_SUBFUNC_SUPPORT      STD_ON
#define DEM_SUPPORT_MULTIPLE_CONFIG          STD_OFF
#define DEM_SUPPORT_VARIANT_HANDLING         STD_OFF
#define DEM_PREINIT_HAS_CONFIG_PARAM         STD_OFF
#define DEM_SUPPORT_SUPPRESS_DTC             STD_OFF
#define DEM_SUPPORT_GET_EVENT_ID_API         STD_ON
#define DEM_SUPPORT_CLEAREVENTALLOWED        STD_OFF
#define DEM_CLEARDTC_TASKSPLIT               0
#define DEM_SUPPORT_OPERATING_HOURS          STD_ON
#define DEM_USE_OHDS                         STD_ON
#define DEM_SUPPORT_MIRROR_MEMORY            STD_ON
#define DEM_SL_NONE                          0
#define DEM_SL_ECU_LEVEL                     1
#define DEM_SL_NETWORK_COMM_WITH_CLAMP15     2
#define DEM_SL_NETWORK_COMM_NO_CLAMP15       3
#define DEM_SL_POWER_DISTRIBUTION            4

#define DEM_USE_RTE                          STD_OFF

typedef VAR(uint16, TYPEDEF) Dem_TimeBasedDebounceTimerType;

#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
#if MAGIC_NUMBER != 268053767
      #error "The magic number of the generated file <C:\_TSS\DAG\MFA2\Target\Appl\GenData\Dem_Cfg.h> is different. Please check time and date of generated files!"
#endif
#else
#define MAGIC_NUMBER 268053767
#endif
#endif
#endif
