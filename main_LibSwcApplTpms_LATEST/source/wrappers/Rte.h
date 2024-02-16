/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  Copyright (c) 2006-2015 by Vector Informatik GmbH.                                             All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *          File:  Rte.h
 *     Workspace:  C:/_TSS/DAG/MFA2/Target/Config/Developer/HufTPMS_G6_F1L.dev
 *   ECU-Project:  TPM
 *  Generated at:  Fri Dec 15 13:11:50 2017
 *
 *     Generator:  MICROSAR RTE Generator Version 2.27.0
 *                 RTE Core Version 1.6.0
 *       License:  License CBD1500122 valid for Huf Electronics Bretten GmbH Package: MSR Daimler SLP10 Micro: R7F7010133AFP Compiler: Green Hills 6.1.4
 *
 *   Description:  Header file containing RTE types
 *********************************************************************************************************************/

/* double include prevention */

#ifndef _RTE_H
# define _RTE_H

# define RTE_SW_MAJOR_VERSION (0x02U)
# define RTE_SW_MINOR_VERSION (0x1bU)
# define RTE_SW_PATCH_VERSION (0x00U)

# define RTE_VENDOR_ID (0x001EU)

# define RTE_AR_MAJOR_VERSION (0x02U)
# define RTE_AR_MINOR_VERSION (0x05U)
# define RTE_AR_PATCH_VERSION (0x00U)

# include "Std_Types.h"

# ifdef RTE_ENABLE_USER_DATATYPES
#  include "Rte_UserTypes.h"
# endif

# if !defined (TYPEDEF) && defined (AUTOMATIC)
#  define TYPEDEF AUTOMATIC
# endif

# if !defined (FUNC_P2CONST)
#  define FUNC_P2CONST(rettype, ptrclass, memclass) FUNC(P2CONST(rettype, AUTOMATIC, ptrclass), memclass) /* PRQA S 3453 */ /* MD_MSR_19.7 */
# endif

/* Note: application errors are in the range between 1-63
         overlayed error (ORed with application errors) is 64
         structural errors are in the range between 128-256 */

/* common errors */
# define RTE_E_OK               (0U)
# define RTE_E_INVALID          (1U)

/* overlayed errors */
# define RTE_E_LOST_DATA        (64U)
# define RTE_E_MAX_AGE_EXCEEDED (64U)

/* immediate infrastructure errors */
# define RTE_E_COM_STOPPED      (128U)
# define RTE_E_COMMS_ERROR      (128U)  /* AUTOSAR 2.1 compatibility */
# define RTE_E_TIMEOUT          (129U)
# define RTE_E_LIMIT            (130U)
# define RTE_E_NO_DATA          (131U)
# define RTE_E_TRANSMIT_ACK     (132U)
# define RTE_E_NEVER_RECEIVED   (133U)

# ifndef RTE_USE_COM_SIGNAL_PREFIX
#  define RTE_USE_COM_SIGNAL_PREFIX
# endif

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER /* PRQA S 0828 */ /* MD_MSR_1.1_828 */
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1513305418
#    error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Rte.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1513305418
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_H */
