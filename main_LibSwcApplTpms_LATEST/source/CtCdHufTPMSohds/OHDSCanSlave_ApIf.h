
#ifndef OHDSCANSLAVE_APIF_H
#define OHDSCANSLAVE_APIF_H

#include "OHDSCanSlave_Config.h"

#define OHDS_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHoursUint16( P2VAR(uint16, AUTOMATIC, OHDS_APPL_VAR) value,
                                                                      P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status );

FUNC(Std_ReturnType, OHDS_CODE) OHDSCanSlave_GetOperatingHours( P2VAR(uint32, AUTOMATIC, OHDS_APPL_VAR) value,
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) valueMsb,
                                                                P2VAR(uint8, AUTOMATIC, OHDS_APPL_VAR) status );

#define OHDS_STOP_SEC_CODE
#include "MemMap.h"

#endif
