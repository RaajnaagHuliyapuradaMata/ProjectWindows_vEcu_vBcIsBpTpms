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
 *          File:  Rte_MemMap.h
 *     Workspace:  C:/_TSS/DAG/MFA2/Target/Config/Developer/HufTPMS_G6_F1L.dev
 *   ECU-Project:  TPM
 *  Generated at:  Fri Dec 15 13:11:50 2017
 *
 *     Generator:  MICROSAR RTE Generator Version 2.27.0
 *                 RTE Core Version 1.6.0
 *       License:  License CBD1500122 valid for Huf Electronics Bretten GmbH Package: MSR Daimler SLP10 Micro: R7F7010133AFP Compiler: Green Hills 6.1.4
 *
 *   Description:  RTE Memory Mapping header file
 *********************************************************************************************************************/

/* PRQA S 0883 EOF */ /* MD_Rte_0883 */

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of version logging area >>                DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of version logging area >>                  DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * RTE specific defines
 *********************************************************************************************************************/

/* open sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CODE
# undef RTE_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef RTE_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef RTE_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_VAR_ZERO_INIT_8BIT
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_VAR_ZERO_INIT_8BIT
# undef RTE_START_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_8BIT
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_VAR_INIT_UNSPECIFIED
# undef RTE_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CONST_UNSPECIFIED
# undef RTE_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_APPL_CODE
# undef RTE_START_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* close sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CODE
# undef RTE_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef RTE_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef RTE_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_VAR_ZERO_INIT_8BIT
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_VAR_ZERO_INIT_8BIT
# undef RTE_STOP_SEC_VAR_ZERO_INIT_8BIT /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef RTE_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CONST_UNSPECIFIED
# undef RTE_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_APPL_CODE
# undef RTE_STOP_SEC_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/



/**********************************************************************************************************************
 * SW-C specific defines
 *********************************************************************************************************************/

/* open sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_COMM_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_COMM_APPL_CODE
# undef RTE_START_SEC_COMM_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CTAPHUFTPMSDIA_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CTAPHUFTPMSDIA_APPL_CODE
# undef RTE_START_SEC_CTAPHUFTPMSDIA_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_START_SEC_CODE
# undef CtApHufTPMSdia_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_START_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSdia_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSdia_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSdia_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSdia_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CTAPHUFTPMSMGR_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CTAPHUFTPMSMGR_APPL_CODE
# undef RTE_START_SEC_CTAPHUFTPMSMGR_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_START_SEC_CODE
# undef CtApHufTPMSmgr_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_START_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSmgr_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSmgr_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSmgr_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSmgr_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CTAPHUFTPMSROE_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CTAPHUFTPMSROE_APPL_CODE
# undef RTE_START_SEC_CTAPHUFTPMSROE_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_START_SEC_CODE
# undef CtApHufTPMSroe_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_START_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSroe_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSroe_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSroe_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSroe_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CTAPHUFTPMSWNH_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CTAPHUFTPMSWNH_APPL_CODE
# undef RTE_START_SEC_CTAPHUFTPMSWNH_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_START_SEC_CODE
# undef CtApHufTPMSwnh_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_START_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSwnh_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSwnh_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSwnh_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSwnh_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE
# undef RTE_START_SEC_CTAPHUFTPMSWPA_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_START_SEC_CODE
# undef CtApHufTPMSwpa_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_START_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSwpa_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSwpa_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSwpa_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSwpa_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CTCDHUFTPMSRFD_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CTCDHUFTPMSRFD_APPL_CODE
# undef RTE_START_SEC_CTCDHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_START_SEC_CODE
# undef CtCdHufTPMSrfd_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_NVM_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_NVM_APPL_CODE
# undef RTE_START_SEC_NVM_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_OHDSCANSLAVE_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_OHDSCANSLAVE_APPL_CODE
# undef RTE_START_SEC_OHDSCANSLAVE_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_START_SEC_CODE
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_START_SEC_CODE
# undef OHDSCanSlave_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_START_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_START_SEC_CONST_UNSPECIFIED
# undef OHDSCanSlave_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_START_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef OHDSCanSlave_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_START_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_START_SEC_VAR_INIT_UNSPECIFIED
# undef OHDSCanSlave_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef OHDSCanSlave_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* close sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_COMM_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_COMM_APPL_CODE
# undef RTE_STOP_SEC_COMM_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CTAPHUFTPMSDIA_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CTAPHUFTPMSDIA_APPL_CODE
# undef RTE_STOP_SEC_CTAPHUFTPMSDIA_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_STOP_SEC_CODE
# undef CtApHufTPMSdia_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_STOP_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSdia_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSdia_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSdia_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSdia_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSdia_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CTAPHUFTPMSMGR_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CTAPHUFTPMSMGR_APPL_CODE
# undef RTE_STOP_SEC_CTAPHUFTPMSMGR_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_STOP_SEC_CODE
# undef CtApHufTPMSmgr_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_STOP_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSmgr_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSmgr_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSmgr_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSmgr_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSmgr_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CTAPHUFTPMSROE_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CTAPHUFTPMSROE_APPL_CODE
# undef RTE_STOP_SEC_CTAPHUFTPMSROE_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_STOP_SEC_CODE
# undef CtApHufTPMSroe_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_STOP_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSroe_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSroe_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSroe_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSroe_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSroe_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CTAPHUFTPMSWNH_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CTAPHUFTPMSWNH_APPL_CODE
# undef RTE_STOP_SEC_CTAPHUFTPMSWNH_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_STOP_SEC_CODE
# undef CtApHufTPMSwnh_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_STOP_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSwnh_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSwnh_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSwnh_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwnh_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSwnh_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE
# undef RTE_STOP_SEC_CTAPHUFTPMSWPA_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_STOP_SEC_CODE
# undef CtApHufTPMSwpa_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_STOP_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSwpa_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSwpa_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSwpa_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtApHufTPMSwpa_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSwpa_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CTCDHUFTPMSRFD_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CTCDHUFTPMSRFD_APPL_CODE
# undef RTE_STOP_SEC_CTCDHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_STOP_SEC_CODE
# undef CtCdHufTPMSrfd_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef CtCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_NVM_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_NVM_APPL_CODE
# undef RTE_STOP_SEC_NVM_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_OHDSCANSLAVE_APPL_CODE
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_OHDSCANSLAVE_APPL_CODE
# undef RTE_STOP_SEC_OHDSCANSLAVE_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_STOP_SEC_CODE
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_STOP_SEC_CODE
# undef OHDSCanSlave_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_STOP_SEC_CONST_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_STOP_SEC_CONST_UNSPECIFIED
# undef OHDSCanSlave_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef OHDSCanSlave_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_STOP_SEC_VAR_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef OHDSCanSlave_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef OHDSCanSlave_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef OHDSCanSlave_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Calibration Parameter specific defines
 *********************************************************************************************************************/

/* open sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
# undef RTE_START_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/* close sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED
# undef RTE_STOP_SEC_CONST_DEFAULT_RTE_CDATA_GROUP_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/



/**********************************************************************************************************************
 * Per-Instance Memory specific defines
 *********************************************************************************************************************/

/* open sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!         << Start of memory mapping implementation >>         DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_START_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_START_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
# undef RTE_START_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/* close sections */
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!        << Start of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_STOP_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
 *********************************************************************************************************************/

#ifdef RTE_STOP_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED
# undef RTE_STOP_SEC_VAR_DEFAULT_RTE_PIM_GROUP_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!          << End of memory mapping implementation >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/



#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_START_SEC_CODE)  ************/

#ifdef CtCdHufTPMSrfd_START_SEC_CODE
# undef CtCdHufTPMSrfd_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_STOP_SEC_CTCDHUFTPMSRFD_APPL_CODE)  ****/

#ifdef RTE_STOP_SEC_CTCDHUFTPMSRFD_APPL_CODE
# undef RTE_STOP_SEC_CTCDHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_STOP_SEC_CODE)  *************/

#ifdef CtCdHufTPMSrfd_STOP_SEC_CODE
# undef CtCdHufTPMSrfd_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED)  */

#ifdef CtCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED
# undef CtCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_START_SEC_CTCDHUFTPMSRFD_APPL_CODE)  ***/

#ifdef RTE_START_SEC_CTCDHUFTPMSRFD_APPL_CODE
# undef RTE_START_SEC_CTCDHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif


#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_CONST_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_CONST_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_INIT_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_CODE)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_CODE
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_CONST_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_CONST_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_STOP_SEC_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CODE)  */

#ifdef RTE_STOP_SEC_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CODE
# undef RTE_STOP_SEC_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_CODE)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_CODE
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_START_SEC_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CODE)  */

#ifdef RTE_START_SEC_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CODE
# undef RTE_START_SEC_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CDD_OHDS_ClockSync_SlaveCAN_V1_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif


#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_START_SEC_CTAPHUFTPMSRFD_APPL_CODE)  ***/

#ifdef RTE_START_SEC_CTAPHUFTPMSRFD_APPL_CODE
# undef RTE_START_SEC_CTAPHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CtApHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CtApHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_STOP_SEC_CTAPHUFTPMSRFD_APPL_CODE)  ****/

#ifdef RTE_STOP_SEC_CTAPHUFTPMSRFD_APPL_CODE
# undef RTE_STOP_SEC_CTAPHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_START_SEC_CONST_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_START_SEC_CONST_UNSPECIFIED
# undef CtApHufTPMSrfd_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_STOP_SEC_CODE)  *************/

#ifdef CtApHufTPMSrfd_STOP_SEC_CODE
# undef CtApHufTPMSrfd_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_START_SEC_CODE)  ************/

#ifdef CtApHufTPMSrfd_START_SEC_CODE
# undef CtApHufTPMSrfd_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CtApHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CtApHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED
# undef CtApHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif


#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_START_SEC_CODE)  ************/

#ifdef CpCdHufTPMSrfd_START_SEC_CODE
# undef CpCdHufTPMSrfd_START_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED
# undef CpCdHufTPMSrfd_STOP_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_START_SEC_CPCDHUFTPMSRFD_APPL_CODE)  ***/

#ifdef RTE_START_SEC_CPCDHUFTPMSRFD_APPL_CODE
# undef RTE_START_SEC_CPCDHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED
# undef CpCdHufTPMSrfd_START_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_CONST_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED
# undef CpCdHufTPMSrfd_START_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_NOINIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CpCdHufTPMSrfd_STOP_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_STOP_SEC_CODE)  *************/

#ifdef CpCdHufTPMSrfd_STOP_SEC_CODE
# undef CpCdHufTPMSrfd_STOP_SEC_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED
# undef CpCdHufTPMSrfd_START_SEC_VAR_ZERO_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_ZERO_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED
# undef CpCdHufTPMSrfd_STOP_SEC_CONST_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CONST
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:RTE_STOP_SEC_CPCDHUFTPMSRFD_APPL_CODE)  ****/

#ifdef RTE_STOP_SEC_CPCDHUFTPMSRFD_APPL_CODE
# undef RTE_STOP_SEC_CPCDHUFTPMSRFD_APPL_CODE /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_CODE
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED
# undef CpCdHufTPMSrfd_START_SEC_VAR_INIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define START_SEC_VAR_INIT_UNSPECIFIED
#endif

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: memory mapping implementation:CpCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED)  */

#ifdef CpCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED
# undef CpCdHufTPMSrfd_STOP_SEC_VAR_NOINIT_UNSPECIFIED /* PRQA S 0841 */ /* MD_MSR_19.6 */
# define STOP_SEC_VAR
#endif

/***  End of saved code  ************************************************************************************/
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER /* PRQA S 0828 */ /* MD_MSR_1.1_828 */
# ifdef RTE_MAGIC_NUMBER
#  if RTE_MAGIC_NUMBER != 1513305418
#   error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Rte_MemMap.h> is different. Please check time and date of the generated RTE files!"
#  endif
# else
#  define RTE_MAGIC_NUMBER 1513305418
# endif  /* RTE_MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

/**********************************************************************************************************************
 MISRA 2004 violations and justifications
 *********************************************************************************************************************/

/* module specific MISRA deviations:
   MD_Rte_0883:  MISRA rule: 19.15
     Reason:     AUTOSAR SWS Memory Mapping requires inclusion of MemMap.h multiple times in a file in order to
                 select appropriate #pragma directives.
     Risk:       MemMap.h is provided by the integrator, hence many risks may occur, caused by wrong implementation of this file.
     Prevention: The integrator strictly has to adhere to the definitions of the AUTOSAR SWS Memory Mapping. Extensions to
                 the file not described in the SWS may not be put into MemMap.h. This has to be verified by code inspection.

*/
