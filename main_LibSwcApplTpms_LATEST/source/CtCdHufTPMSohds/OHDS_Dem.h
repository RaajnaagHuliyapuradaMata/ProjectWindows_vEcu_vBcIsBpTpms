
#ifndef OHDS_DEM_H
#define OHDS_DEM_H

#include "OHDSCanSlave_Config.h"

#define OHDS_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OHDS_CODE) OHDS_Dem_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value,
                                                            P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status );

#if(OHDSCANSLAVE_VERSION_INFO_API == STD_ON)

FUNC(void, OHDS_CODE) OHDS_Dem_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, OHDS_APPL_VAR) versionInfo );
#endif

#define OHDS_STOP_SEC_CODE
#include "MemMap.h"
#endif
