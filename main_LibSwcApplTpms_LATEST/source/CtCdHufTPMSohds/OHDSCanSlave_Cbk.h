
#if !defined(OHDSCANSLAVE_CBK_H)
#define OHDSCANSLAVE_CBK_H

#define OHDS_START_SEC_CODE
#include "MemMap.h"

FUNC(void, OHDS_CODE) OHDSCanSlave_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, OHDS_APPL_VAR) PduInfoPtr);

FUNC(void, OHDS_CODE) OHDSCanSlave_TxConfirmation(PduIdType TxPduId);

#define OHDS_STOP_SEC_CODE
#include "MemMap.h"

#endif
