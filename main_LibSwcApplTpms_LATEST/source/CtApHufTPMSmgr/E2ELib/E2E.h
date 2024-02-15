/**
 * \file
 *
 * \brief AUTOSAR E2E
 *
 * This file contains the implementation of the AUTOSAR
 * module E2E.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined E2E_H)
#define E2E_H

/*==================[inclusions]=============================================*/

#include <Std_Types.h>          /* AUTOSAR standard types             */
#include <Platform_Types.h>     /* Autosar platform specific type declarations */

/*==================[macros]=================================================*/

/*------------------[E2E Error Classification]-------------------------------*/

#if (defined E2E_E_INPUTERR_NULL) /* to prevent double declaration */
#error E2E_E_INPUTERR_NULL is already defined
#endif

/** \brief At least one pointer parameter is a NULL pointer. */
#define E2E_E_INPUTERR_NULL 0x13U

#if (defined E2E_E_INPUTERR_WRONG) /* to prevent double declaration */
#error E2E_E_INPUTERR_WRONG is already defined
#endif

/** \brief At least one input parameter is erroneous (e.g. out of range) */
#define E2E_E_INPUTERR_WRONG 0x17U

#if (defined E2E_E_INTERR) /* to prevent double declaration */
#error E2E_E_INTERR is already defined
#endif

/**
 * \brief An internal library error has occurred.
 *
 * An internal library error has occurred. (e.g. error detected by program flow monitoring,
 * violated invariant or postcondition)
 */
#define E2E_E_INTERR 0x19U

#if (defined E2E_E_OK) /* to prevent double declaration */
#error E2E_E_OK is already defined
#endif

/* \brief Function completed successfully. */
#define E2E_E_OK 0U

#if (defined E2E_E_INVALID) /* to prevent double declaration */
#error E2E_E_INVALID is already defined
#endif

/* \brief Invalid value passed to function. */
#define E2E_E_INVALID 0xFFU

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined E2E_VENDOR_ID) /* to prevent double declaration */
#error E2E_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define E2E_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined E2E_MODULE_ID) /* to prevent double declaration */
#error E2E_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define E2E_MODULE_ID         207U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined E2E_AR_RELEASE_MAJOR_VERSION) /* to prevent double declaration */
#error E2E_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define E2E_AR_RELEASE_MAJOR_VERSION  4U

#if (defined E2E_AR_RELEASE_MINOR_VERSION) /* to prevent double declaration */
#error E2E_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define E2E_AR_RELEASE_MINOR_VERSION  0U

#if (defined E2E_AR_RELEASE_REVISION_VERSION) /* to prevent double declaration */
#error E2E_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define E2E_AR_RELEASE_REVISION_VERSION  3U

/*------------------[AUTOSAR specification version identification]----------*/

#if (defined E2E_AR_MAJOR_VERSION) /* to prevent double declaration */
#error E2E_AR_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR specification major version */
#define E2E_AR_MAJOR_VERSION  2U

#if (defined E2E_AR_MINOR_VERSION) /* to prevent double declaration */
#error E2E_AR_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR specification minor version */
#define E2E_AR_MINOR_VERSION  0U

#if (defined E2E_AR_PATCH_VERSION) /* to prevent double declaration */
#error E2E_AR_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR specification patch version */
#define E2E_AR_PATCH_VERSION  0U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined E2E_SW_MAJOR_VERSION) /* to prevent double declaration */
#error E2E_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define E2E_SW_MAJOR_VERSION  2U

#if (defined E2E_SW_MINOR_VERSION) /* to prevent double declaration */
#error E2E_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define E2E_SW_MINOR_VERSION  0U

#if (defined E2E_SW_PATCH_VERSION) /* to prevent double declaration */
#error E2E_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define E2E_SW_PATCH_VERSION  1U


/*==================[type definitions]=======================================*/

/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[external function declarations]=========================*/


#define E2E_START_SEC_CODE
#include <MemMap.h>

/** \brief Return the modules version information
 *
 * This service returns the version information of this module. The version
 * information includes:
 * - Module Id
 * - Vendor Id
 * - Vendor specific version numbers
 *
 * \param[out] VersionInfo Pointer where to store the version information of this module
 *
 * \ServiceID{0x14}
 * \Reentrancy{Reentrant}
 * \Synchronicity{Synchronous}
 */
extern FUNC(void, E2E_CODE) E2E_GetVersionInfo
(
   P2VAR(Std_VersionInfoType, AUTOMATIC, E2E_APPL_DATA) VersionInfo
);

#define E2E_STOP_SEC_CODE
#include <MemMap.h>

#endif /* if !defined( E2E_H ) */
/*==================[end of file]============================================*/
