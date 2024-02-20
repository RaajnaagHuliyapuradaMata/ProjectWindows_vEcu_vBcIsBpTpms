
#ifndef OHDSCANSLAVE_H
#define OHDSCANSLAVE_H

#include "OHDSCanSlave_Config.h"

#define OHDSCANSLAVE_VENDOR_ID            (0x001Eu)
#define OHDSCANSLAVE_MODULE_ID            (255u)
#define OHDSCANSLAVE_SW_MAJOR_VERSION     (0x02u)
#define OHDSCANSLAVE_SW_MINOR_VERSION     (0x01u)
#define OHDSCANSLAVE_SW_PATCH_VERSION     (0x01u)

#define OHDSCANSLAVE_E_UNINIT              (0x01u)
#define OHDSCANSLAVE_E_PARAM               (0x02u)
#define OHDSCANSLAVE_E_NOTSUPPORTED        (0x03u)
#define OHDSCANSLAVE_E_TIMERINIT           (0x04u)

#define OHDSCANSLAVE_MAINFUNCTION_SID      (0x01u)
#define OHDSCANSLAVE_RXINDICATION_SID      (0x02u)
#define OHDSCANSLAVE_GETOHUINT16_SID       (0x03u)
#define OHDSCANSLAVE_GETOH_SID             (0x04u)
#define OHDSCANSLAVE_DEM_GETOH_SID         (0x05u)
#define OHDSCANSLAVE_TXCONFIRMATION_SID    (0x06u)
#define OHDSCANSLAVE_INIT_SID              (0x07u)
#define OHDSCANSLAVE_INITMEMORY_SID        (0x08u)

#define OHDSCANSLAVE_REPORTERROR_MODULEID  (25110u)

#define OHDSCANSLAVE_CANSIGNAL_MSGLENGTH                       8u

#define OHDSCanSlave_GetCanSignal_Type(bufferPtr)              ((uint8)(bufferPtr)[0])
#define OHDSCanSlave_CanSignal_IsSyncMsg(bufferPtr)            (OHDSCanSlave_GetCanSignal_Type(bufferPtr) == 0x20u)
#define OHDSCanSlave_CanSignal_IsFupMsg(bufferPtr)             (OHDSCanSlave_GetCanSignal_Type(bufferPtr) == 0x28u)

#define OHDSCanSlave_GetCanSignal_SQC(bufferPtr)               ((bufferPtr)[2] & 0x0fu)

#define OHDSCanSlave_GetCanSignal_TimeDomain(bufferPtr)        ((uint8)(((bufferPtr)[2] & 0xf0u) >> 4u))

#define OHDSCanSlave_GetCanSignal_SEC(bufferPtr)   (((uint32)((uint32)((bufferPtr)[4] & 0x1Fu) << 24u) & 0xff000000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[5]          << 16u) &   0xff0000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[6]          <<  8u) &     0xff00u) | \
                                                    ((uint32)          (bufferPtr)[7]))

#define OHDSCanSlave_GetCanSignal_NS(bufferPtr)    (((uint32)((uint32) (bufferPtr)[4]          << 24u) & 0xff000000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[5]          << 16u) &   0xff0000u) | \
                                                    ((uint32)((uint32) (bufferPtr)[6]          <<  8u) &     0xff00u) | \
                                                    ((uint32)          (bufferPtr)[7]))

#define OHDSCanSlave_GetCanData_US0_SignalBits(bufferPtr)  ((uint8)(((bufferPtr)[3] & 0xf0u) >> 4u))

#define OHDSCanSlave_GetCanSignal_OVS(bufferPtr)   ((uint8)((bufferPtr)[3] & 0x03u))

#define OHDSCanSlave_GetCanSignal_SGW(bufferPtr)   ((uint8)(((bufferPtr)[3] & 0x04u) >> 2u))

#define OHDS_START_SEC_CODE
#include "MemMap.h"

FUNC(void, OHDS_CODE) OHDSCanSlave_InitMemory( void );

FUNC(void, OHDS_CODE) OHDSCanSlave_Init( void );

FUNC(void, OHDS_CODE) OHDSCanSlave_MainFunction( void );

#if (OHDSCANSLAVE_VERSION_INFO_API == STD_ON)

FUNC(void, OHDS_CODE) OHDSCanSlave_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo );

#endif

#define OHDS_STOP_SEC_CODE
#include "MemMap.h"

#endif
