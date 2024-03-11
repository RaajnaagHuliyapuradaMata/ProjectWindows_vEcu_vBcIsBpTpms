

#if defined(DEM_TYPES_H)
#else
#define DEM_TYPES_H

#if defined(DEM_CFG_H) || defined(__DEM_CFG_H__)
#else
#error "Wrong #include sequence: Please include \"Dem_Cfg.h\" before including file \"Dem_Types.h\""
#endif

#if(DEM_USE_RTE == STD_ON)
#include "Rte_Type.h"
#endif

#define DEM_NVDATA_PATTERN_SIZE                         4

#if defined(RTE_VENDOR_ID)
# if(RTE_VENDOR_ID == 0x1Eu)
#   define DEM_USE_RTE_FROM_VECTOR  STD_ON
# else
#   define DEM_USE_RTE_FROM_VECTOR  STD_OFF
# endif
#else
#  define DEM_USE_RTE_FROM_VECTOR  STD_OFF
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_DTCStatusMaskType)))
typedef uint8 Dem_DTCStatusMaskType;
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_DTCType)))
typedef uint32 Dem_DTCType;
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_DTCKindType)))
typedef uint8 Dem_DTCKindType;
#define DEM_DTC_KIND_ALL_DTCS                             0x01
#define DEM_DTC_KIND_EMISSION_REL_DTCS                    0x02
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_EventIdType)))
# if(DEM_MAX_NUMBER_OF_EVENTS <= 255)
typedef uint8  Dem_EventIdType;
# else
typedef uint16 Dem_EventIdType;
# endif
#endif

typedef P2VAR(Dem_EventIdType, TYPEDEF, DEM_VAR_NOINIT) Dem_EventIdPtrType;

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_EventStatusExtendedType)))
typedef uint8 Dem_EventStatusExtendedType;
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_FaultDetectionCounterType)))
typedef sint8 Dem_FaultDetectionCounterType;
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_EventStatusType)))
typedef uint8 Dem_EventStatusType;
#define DEM_EVENT_STATUS_PASSED                           0x00
#define DEM_EVENT_STATUS_FAILED                           0x01
#define DEM_EVENT_STATUS_PREPASSED                        0x02
#define DEM_EVENT_STATUS_PREFAILED                        0x03
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_IndicatorStatusType)))
typedef uint8 Dem_IndicatorStatusType;
#define DEM_INDICATOR_OFF                                 0x00
#define DEM_INDICATOR_CONTINUOUS                          0x01
#define DEM_INDICATOR_BLINKING                            0x02
#define DEM_INDICATOR_BLINK_CONT                          0x03
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_InitMonitorKindType)))
typedef uint8 Dem_InitMonitorKindType;
#define DEM_INIT_MONITOR_CLEAR                            0x01
#define DEM_INIT_MONITOR_RESTART                          0x02
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_OperationCycleIdType)))
typedef uint8 Dem_OperationCycleIdType;
#endif

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_OperationCycleStateType)))
typedef uint8 Dem_OperationCycleStateType;
#define DEM_CYCLE_STATE_START                             0x01
#define DEM_CYCLE_STATE_END                               0x02
#endif
#define DEM_CYCLE_STATE_START_BLOCKED                     0xFF

#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_MaxDataValueType)))
typedef uint8 Dem_MaxDataValueType[];
#endif
#if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_MaxExtendedDataRecordType)))
typedef uint8 Dem_MaxExtendedDataRecordType[];
#endif

#if(DEM_SUPPORT_SUPPRESS_DTC == STD_ON)
# if(DEM_USE_RTE == STD_OFF) || ((DEM_USE_RTE == STD_ON) && (DEM_USE_RTE_FROM_VECTOR == STD_ON) && (! defined(Rte_TypeDef_Dem_SuppressDTCStatusType)))
typedef uint8 Dem_SuppressDTCStatusType;
# define DEM_SUPPRESS_DTC_OFF                              0u
# define DEM_SUPPRESS_DTC_ON                               1u
# endif
#endif

typedef uint8 Dem_EnableConditionStateType;

typedef uint8 Dem_DTCOriginType;
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY                     0x01
#define DEM_DTC_ORIGIN_MIRROR_MEMORY                      0x02
#define DEM_DTC_ORIGIN_PERMANENT                          0x03
#define DEM_DTC_ORIGIN_SECONDARY_MEMORY                   0x04

#define DEM_IGNITION                                      0
#define DEM_OBD_DCY                                       1
#define DEM_WARMUP                                        2
#define DEM_POWER                                         3

typedef uint8 Dem_ViewIdType;

typedef uint8 Dem_DtcStatusByteType;

#define DEM_EVENTSTATUSEXT_CLEARED_DTC                    0x50

typedef uint8 Dem_DtcInternalStatusType;

#define DEM_GET_FFDATA_ID_ALL                             0xffffu

typedef uint32 Dem_DTCGroupType;
#define DEM_DTC_GROUP_EMISSION_REL_DTCS                   0x000000uL

#define DEM_DTC_GROUP_ALL_DTCS                            0xffffffuL

typedef uint8 Dem_DTCGroupKindType;
#define DEM_DTC_GROUPKIND_EMISSION_REL                    (uint8)(1u<<0)
#define DEM_DTC_GROUPKIND_POWERTRAIN                      (uint8)(1u<<1)
#define DEM_DTC_GROUPKIND_CHASSIS                         (uint8)(1u<<2)
#define DEM_DTC_GROUPKIND_BODY                            (uint8)(1u<<3)
#define DEM_DTC_GROUPKIND_NETWORK_COM                     (uint8)(1u<<4)
#define DEM_DTC_GROUPKIND_ALL_DTCS                        (uint8)(0xffu)

typedef struct Dem_DTCGroupMappingTypeTag
{
  Dem_DTCGroupKindType  GroupKind;
  Dem_DTCType           DTCnumber;
} Dem_DTCGroupMappingType;

typedef uint8 Dem_DTCRequestType;
#define DEM_FIRST_FAILED_DTC                              0x01
#define DEM_MOST_RECENT_FAILED_DTC                        0x02
#define DEM_FIRST_DET_CONFIRMED_DTC                       0x03
#define DEM_MOST_REC_DET_CONFIRMED_DTC                    0x04

typedef uint8 Dem_EventPriorityType;
typedef uint8 Dem_DataByteType;
typedef uint8 Dem_IndicatorIdType;

typedef uint16 Dem_NvMBlockIdType;

typedef uint8 Dem_FilterWithSeverityType;
#define DEM_FILTER_WITH_SEVERITY_YES                      0x00
#define DEM_FILTER_WITH_SEVERITY_NO                       0x01

typedef uint8 Dem_DTCSeverityType;
#define DEM_SEVERITY_NO_SEVERITY                          0x00
#define DEM_SEVERITY_MAINTENANCE_ONLY                     0x20
#define DEM_SEVERITY_CHECK_AT_NEXT_HALT                   0x40
#define DEM_SEVERITY_CHECK_IMMEDIATELY                    0x80

typedef uint8 Dem_ReturnSetDTCFilterType;
#define DEM_FILTER_ACCEPTED                               0x00
#define DEM_WRONG_FILTER                                  0x01

typedef uint8 Dem_FilterForFaultDetectionCounterType;
#define DEM_FILTER_FOR_FDC_YES                            0x00
#define DEM_FILTER_FOR_FDC_NO                             0x01

typedef uint8 Dem_ReturnSetViewFilterType;
#define DEM_VIEW_ID_ACCEPTED                              0x00
#define DEM_WRONG_ID                                      0x01

typedef uint8 Dem_ReturnGetStatusOfDTCType;
#define DEM_STATUS_OK                                     0x00
#define DEM_STATUS_WRONG_DTC                              0x01
#define DEM_STATUS_WRONG_DTCORIGIN                        0x02
#define DEM_STATUS_WRONG_DTCKIND                          0x03
#define DEM_STATUS_FAILED                                 0x04

typedef uint8 Dem_ReturnGetNextFilteredDTCType;
#define DEM_FILTERED_OK                                   0x00
#define DEM_FILTERED_NO_MATCHING_DTC                      0x01
#define DEM_FILTERED_WRONG_DTCKIND                        0x02

typedef uint8 Dem_ReturnGetNumberOfFilteredDTCType;
#define DEM_NUMBER_OK                                     0x00
#define DEM_NUMBER_FAILED                                 0x01
#define DEM_NUMBER_PENDING                                0x02

typedef uint8 Dem_ReturnClearDTCType;
#define DEM_CLEAR_OK                                      0x00
#define DEM_CLEAR_WRONG_DTC                               0x01
#define DEM_CLEAR_WRONG_DTCORIGIN                         0x02
#define DEM_CLEAR_WRONG_DTCKIND                           0x03
#define DEM_CLEAR_FAILED                                  0x04
#define DEM_DTC_PENDING                                   0x05

typedef uint8 Dem_ReturnControlDTCStorageType;
#define DEM_CONTROL_DTC_STORAGE_OK                        0x00
#define DEM_CONTROL_DTC_STORAGE_N_OK                      0x01
#define DEM_CONTROL_DTC_WRONG_DTCGROUP                    0x02

typedef uint8 Dem_ReturnControlEventUpdateType;
#define DEM_CONTROL_EVENT_UPDATE_OK                       0x00
#define DEM_CONTROL_EVENT_UPDATE_N_OK                     0x01
#define DEM_CONTROL_EVENT_WRONG_DTCGROUP                  0x02

typedef uint8 Dem_ReturnGetDTCOfFreezeFrameRecordType;
#define DEM_GET_DTCOFFF_OK                                0x00
#define DEM_GET_DTCOFFF_WRONG_RECORD                      0x01
#define DEM_GET_DTCOFFF_NO_DTC_FOR_RECORD                 0x02
#define DEM_GET_DTCOFFF_WRONG_DTCKIND                     0x03

typedef uint8 Dem_ReturnGetFreezeFrameDataIdentifierByDTCType;
#define DEM_GET_ID_OK                                     0x00
#define DEM_GET_ID_WRONG_DTC                              0x01
#define DEM_GET_ID_WRONG_DTCORIGIN                        0x02
#define DEM_GET_ID_WRONG_DTCKIND                          0x03
#define DEM_GET_ID_WRONG_FF_TYPE                          0x04

typedef uint8 Dem_ReturnGetExtendedDataRecordByDTCType;
#define DEM_RECORD_OK                                     0x00
#define DEM_RECORD_WRONG_DTC                              0x01
#define DEM_RECORD_WRONG_DTCORIGIN                        0x02
#define DEM_RECORD_WRONG_DTCKIND                          0x03
#define DEM_RECORD_WRONG_NUMBER                           0x04
#define DEM_RECORD_WRONG_BUFFERSIZE                       0x05

#define DEM_GET_DTCOFEVENT_NO_DTC_AVAILABLE               0x02

typedef uint8 Dem_ReturnGetDTCByOccurrenceTimeType;
#define DEM_OCCURR_OK                                     0x00
#define DEM_OCCURR_WRONG_DTCKIND                          0x01
#define DEM_OCCURR_FAILED                                 0x02

typedef uint8 Dem_ReturnGetFreezeFrameDataByDTCType;
#define DEM_GET_FFDATABYDTC_OK                            0x00
#define DEM_GET_FFDATABYDTC_WRONG_DTC                     0x01
#define DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN               0x02
#define DEM_GET_FFDATABYDTC_WRONG_DTCKIND                 0x03
#define DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER            0x04
#define DEM_GET_FFDATABYDTC_WRONG_DATAID                  0x05
#define DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE              0x06

typedef uint8 Dem_ReturnGetSizeOfExtendedDataRecordByDTCType;
#define DEM_GET_SIZEOFEDRBYDTC_OK                         0x00
#define DEM_GET_SIZEOFEDRBYDTC_W_DTC                      0x01
#define DEM_GET_SIZEOFEDRBYDTC_W_DTCOR                    0x02
#define DEM_GET_SIZEOFEDRBYDTC_W_DTCKI                    0x03
#define DEM_GET_SIZEOFEDRBYDTC_W_RNUM                     0x04

typedef uint8 Dem_ReturnGetSizeOfFreezeFrameType;
#define DEM_GET_SIZEOFFF_OK                               0x00
#define DEM_GET_SIZEOFFF_WRONG_DTC                        0x01
#define DEM_GET_SIZEOFFF_WRONG_DTCOR                      0x02
#define DEM_GET_SIZEOFFF_WRONG_DTCKIND                    0x03
#define DEM_GET_SIZEOFFF_WRONG_RNUM                       0x04

typedef uint8 Dem_ReturnGetViewIDOfDTCType;
#define DEM_VIEWID_OK                                     0x00
#define DEM_VIEWID_WRONG_DTC                              0x01
#define DEM_VIEWID_WRONG_DTCKIND                          0x02

typedef uint8 Dem_ReturnGetSeverityOfDTCType;
#define DEM_GET_SEVERITYOFDTC_OK                          0x00
#define DEM_GET_SEVERITYOFDTC_WRONG_DTC                   0x01
#define DEM_GET_SEVERITYOFDTC_WRONG_DTCORIGIN             0x02
#define DEM_GET_SEVERITYOFDTC_NOSEVERITY                  0x03

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_InitMonitorFPtrType) (Dem_InitMonitorKindType InitMonitorKind);
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_ClearAllowedFPtrType)(P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) Allowed);

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetDataValueByDataIdentifierType) (P2VAR(Dem_MaxDataValueType, AUTOMATIC, DEM_APPL_DATA) );
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_GetExtDataRecordFPtrType) (P2VAR(Dem_MaxExtendedDataRecordType, AUTOMATIC, DEM_APPL_DATA) );

typedef uint16 Dem_TriggerOnEventIndexType;
typedef uint16 Dem_TriggerOnDTCIndexType;

typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_TriggerFunctionType) (Dem_EventStatusExtendedType EventStatusOld, Dem_EventStatusExtendedType EventStatusNew);
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_TriggerDTCFunctionType) (Dem_DTCType DTC, Dem_DTCKindType DTCKind, Dem_DTCStatusMaskType DTCStatusOld, Dem_DTCStatusMaskType DTCStatusNew);

typedef P2CONST(uint16, TYPEDEF, DEM_PBCFG) Dem_RecordDIDAddrType;

typedef uint8 Dem_HistInterrogationRecordType[3];

typedef struct
{
  union
  {
    Dem_EventIdType           EventIdentifier;
    Dem_OperationCycleIdType  CycleId;
    struct
    {
      Dem_DTCGroupKindType  BitcodedDtcGroup;
      Dem_DTCOriginType     DTCOrigin;
    } dtc;
  } arg;
  uint8 Action;
} Dem_AQElementType;

#if(DEM_SUPPORT_MULTIPLE_CONFIG == STD_ON) || (DEM_SUPPORT_VARIANT_HANDLING == STD_ON) || (DEM_PREINIT_HAS_CONFIG_PARAM == STD_ON)

typedef struct
{
  uint32 ConfigurationMask;
} Dem_ConfigType;
#endif

#endif
