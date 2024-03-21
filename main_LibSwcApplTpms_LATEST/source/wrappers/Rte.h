#ifndef _RTE_H
#define _RTE_H

#define RTE_SW_MAJOR_VERSION (0x02U)
#define RTE_SW_MINOR_VERSION (0x1bU)
#define RTE_SW_PATCH_VERSION (0x00U)

#define RTE_VENDOR_ID (0x001EU)

#define RTE_AR_MAJOR_VERSION (0x02U)
#define RTE_AR_MINOR_VERSION (0x05U)
#define RTE_AR_PATCH_VERSION (0x00U)

#ifdef RTE_ENABLE_USER_DATATYPES
#include "Rte_UserTypes.h"
#endif

#if !defined (TYPEDEF) && defined (AUTOMATIC)
#define TYPEDEF AUTOMATIC
#endif

#if !defined (FUNC_P2CONST)
#define FUNC_P2CONST(rettype, ptrclass, memclass) FUNC(P2CONST(rettype, AUTOMATIC, ptrclass), memclass)
#endif

#define RTE_E_OK               (0U)
#define RTE_E_INVALID          (1U)

#define RTE_E_LOST_DATA        (64U)
#define RTE_E_MAX_AGE_EXCEEDED (64U)

#define RTE_E_COM_STOPPED      (128U)
#define RTE_E_COMMS_ERROR      (128U)
#define RTE_E_TIMEOUT          (129U)
#define RTE_E_LIMIT            (130U)
#define RTE_E_NO_DATA          (131U)
#define RTE_E_TRANSMIT_ACK     (132U)
#define RTE_E_NEVER_RECEIVED   (133U)

#ifndef RTE_USE_COM_SIGNAL_PREFIX
#define RTE_USE_COM_SIGNAL_PREFIX
#endif

#ifndef SKIP_MAGIC_NUMBER
#ifdef RTE_MAGIC_NUMBER
#if RTE_MAGIC_NUMBER != 1513305418
#error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Rte.h> is different. Please check time and date of the generated RTE files!"
#endif
#else
#define RTE_MAGIC_NUMBER 1513305418
#endif
#endif
#endif
