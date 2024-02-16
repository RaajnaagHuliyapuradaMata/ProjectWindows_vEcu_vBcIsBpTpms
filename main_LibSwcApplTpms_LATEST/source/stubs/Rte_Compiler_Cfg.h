/******************************************************************************/
/* File              : Rte_Compiler_Cfg.h                                     */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/
#ifndef _RTE_COMPILER_CFG_H
#define _RTE_COMPILER_CFG_H

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#define Test_LOG_ENABLE
#define USE_VEH_DIR_INFO 0U
#define ABS_SIG_SIZE_ONEBYTE 1U
#define _M_IX86
#define ECU_SHUTDOWN_ENABLE 1U
#define Gildas_Debug_Warnung 0U
#define E2E_ENABLE 1U
#define RE_SIMULATION_ENABLE 1U
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of include and declaration area >>          DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * RTE specific defines
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CODE
 *********************************************************************************************************************/

/* used for code */
# define RTE_CODE

/* used for all global or static variables that are not initialized by the startup code of the compiler */
# define RTE_VAR_NOINIT

/* used for global or static variables that are initialized with zero by the startup code of the compiler or in Rte_InitMemory */
# define RTE_VAR_ZERO_INIT

/* used for global or static variables that are initialized by the startup code of the compiler or in Rte_InitMemory */
# define RTE_VAR_INIT

/* used for global or static constants */
# define RTE_CONST

/* used for references on application data (variables or constants) */
# define RTE_APPL_DATA

/* used for references on application variables */
# define RTE_APPL_VAR

/* used for references on application functions */
# define RTE_APPL_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * SW-C specific defines
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_COMM_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_COMM_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_COMM_APPL_DATA

/* used for references on application functions */
# define RTE_COMM_APPL_CODE

/* used for references on application constants */
# define RTE_COMM_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CTAPHUFTPMSDIA_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_CTAPHUFTPMSDIA_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTAPHUFTPMSDIA_APPL_DATA

/* used for references on application functions */
# define RTE_CTAPHUFTPMSDIA_APPL_CODE

/* used for references on application constants */
# define RTE_CTAPHUFTPMSDIA_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_CODE
 *********************************************************************************************************************/

/* used for SWC specific code */
# define CtApHufTPMSdia_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_CONST
 *********************************************************************************************************************/

/* used for global or static SWC specific constants */
# define CtApHufTPMSdia_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSdia_VAR
 *********************************************************************************************************************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtApHufTPMSdia_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtApHufTPMSdia_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtApHufTPMSdia_VAR_ZERO_INIT

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CTAPHUFTPMSMGR_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_CTAPHUFTPMSMGR_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTAPHUFTPMSMGR_APPL_DATA

/* used for references on application functions */
# define RTE_CTAPHUFTPMSMGR_APPL_CODE

/* used for references on application constants */
# define RTE_CTAPHUFTPMSMGR_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_CODE
 *********************************************************************************************************************/

/* used for SWC specific code */
# define CtApHufTPMSmgr_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_CONST
 *********************************************************************************************************************/

/* used for global or static SWC specific constants */
# define CtApHufTPMSmgr_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSmgr_VAR
 *********************************************************************************************************************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtApHufTPMSmgr_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtApHufTPMSmgr_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtApHufTPMSmgr_VAR_ZERO_INIT

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CTAPHUFTPMSROE_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_CTAPHUFTPMSROE_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTAPHUFTPMSROE_APPL_DATA

/* used for references on application functions */
# define RTE_CTAPHUFTPMSROE_APPL_CODE

/* used for references on application constants */
# define RTE_CTAPHUFTPMSROE_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_CODE
 *********************************************************************************************************************/

/* used for SWC specific code */
# define CtApHufTPMSroe_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_CONST
 *********************************************************************************************************************/

/* used for global or static SWC specific constants */
# define CtApHufTPMSroe_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSroe_VAR
 *********************************************************************************************************************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtApHufTPMSroe_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtApHufTPMSroe_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtApHufTPMSroe_VAR_ZERO_INIT

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CTAPHUFTPMSWNH_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_CTAPHUFTPMSWNH_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTAPHUFTPMSWNH_APPL_DATA

/* used for references on application functions */
# define RTE_CTAPHUFTPMSWNH_APPL_CODE

/* used for references on application constants */
# define RTE_CTAPHUFTPMSWNH_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_CODE
 *********************************************************************************************************************/

/* used for SWC specific code */
# define CtApHufTPMSwnh_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_CONST
 *********************************************************************************************************************/

/* used for global or static SWC specific constants */
# define CtApHufTPMSwnh_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwnh_VAR
 *********************************************************************************************************************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtApHufTPMSwnh_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtApHufTPMSwnh_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtApHufTPMSwnh_VAR_ZERO_INIT

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CTAPHUFTPMSWPA_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_CTAPHUFTPMSWPA_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTAPHUFTPMSWPA_APPL_DATA

/* used for references on application functions */
# define RTE_CTAPHUFTPMSWPA_APPL_CODE

/* used for references on application constants */
# define RTE_CTAPHUFTPMSWPA_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_CODE
 *********************************************************************************************************************/

/* used for SWC specific code */
# define CtApHufTPMSwpa_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_CONST
 *********************************************************************************************************************/

/* used for global or static SWC specific constants */
# define CtApHufTPMSwpa_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtApHufTPMSwpa_VAR
 *********************************************************************************************************************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtApHufTPMSwpa_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtApHufTPMSwpa_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtApHufTPMSwpa_VAR_ZERO_INIT

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CTCDHUFTPMSRFD_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_CTCDHUFTPMSRFD_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTCDHUFTPMSRFD_APPL_DATA

/* used for references on application functions */
# define RTE_CTCDHUFTPMSRFD_APPL_CODE

/* used for references on application constants */
# define RTE_CTCDHUFTPMSRFD_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_CODE
 *********************************************************************************************************************/

/* used for SWC specific code */
# define CtCdHufTPMSrfd_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_CONST
 *********************************************************************************************************************/

/* used for global or static SWC specific constants */
# define CtCdHufTPMSrfd_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: CtCdHufTPMSrfd_VAR
 *********************************************************************************************************************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtCdHufTPMSrfd_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtCdHufTPMSrfd_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtCdHufTPMSrfd_VAR_ZERO_INIT

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_NVM_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_NVM_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_NVM_APPL_DATA

/* used for references on application functions */
# define RTE_NVM_APPL_CODE

/* used for references on application constants */
# define RTE_NVM_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_OHDSCANSLAVE_APPL
 *********************************************************************************************************************/

/* used for references on application variables */
# define RTE_OHDSCANSLAVE_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_OHDSCANSLAVE_APPL_DATA

/* used for references on application functions */
# define RTE_OHDSCANSLAVE_APPL_CODE

/* used for references on application constants */
# define RTE_OHDSCANSLAVE_APPL_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_CODE
 *********************************************************************************************************************/

/* used for SWC specific code */
# define OHDSCanSlave_CODE

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_CONST
 *********************************************************************************************************************/

/* used for global or static SWC specific constants */
# define OHDSCanSlave_CONST

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: OHDSCanSlave_VAR
 *********************************************************************************************************************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define OHDSCanSlave_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define OHDSCanSlave_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define OHDSCanSlave_VAR_ZERO_INIT

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Calibration Parameter specific defines
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_CONST_DEFAULT_RTE_CDATA_GROUP
 *********************************************************************************************************************/

# define RTE_CONST_DEFAULT_RTE_CDATA_GROUP

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Per-Instance Memory specific defines
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!     << Start of compiler abstraction implementation >>       DO NOT CHANGE THIS COMMENT!
 * Symbol: RTE_VAR_DEFAULT_RTE_PIM_GROUP
 *********************************************************************************************************************/

# define RTE_VAR_DEFAULT_RTE_PIM_GROUP

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!      << End of compiler abstraction implementation >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of removed code area >>                   DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/



#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:RTE_CTCDHUFTPMSRFD_APPL)  ************/

/* used for references on application variables */
# define RTE_CTCDHUFTPMSRFD_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTCDHUFTPMSRFD_APPL_DATA

/* used for references on application functions */
# define RTE_CTCDHUFTPMSRFD_APPL_CODE

/* used for references on application constants */
# define RTE_CTCDHUFTPMSRFD_APPL_CONST

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CtCdHufTPMSrfd_CODE)  ****************/

/* used for SWC specific code */
# define CtCdHufTPMSrfd_CODE

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CtCdHufTPMSrfd_CONST)  ***************/

/* used for global or static SWC specific constants */
# define CtCdHufTPMSrfd_CONST

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CtCdHufTPMSrfd_VAR)  *****************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtCdHufTPMSrfd_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtCdHufTPMSrfd_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtCdHufTPMSrfd_VAR_ZERO_INIT

/***  End of saved code  ************************************************************************************/
#endif


#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_CODE)  */

/* used for SWC specific code */
# define CDD_OHDS_ClockSync_SlaveCAN_V1_CODE

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:RTE_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL)  */

/* used for references on application variables */
# define RTE_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_DATA

/* used for references on application functions */
# define RTE_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CODE

/* used for references on application constants */
# define RTE_CDD_OHDS_CLOCKSYNC_SLAVECAN_V1_APPL_CONST

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_VAR)  */

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CDD_OHDS_ClockSync_SlaveCAN_V1_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CDD_OHDS_ClockSync_SlaveCAN_V1_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CDD_OHDS_ClockSync_SlaveCAN_V1_VAR_ZERO_INIT

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CDD_OHDS_ClockSync_SlaveCAN_V1_CONST)  */

/* used for global or static SWC specific constants */
# define CDD_OHDS_ClockSync_SlaveCAN_V1_CONST

/***  End of saved code  ************************************************************************************/
#endif


#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CtApHufTPMSrfd_VAR)  *****************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CtApHufTPMSrfd_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CtApHufTPMSrfd_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CtApHufTPMSrfd_VAR_ZERO_INIT

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:RTE_CTAPHUFTPMSRFD_APPL)  ************/

/* used for references on application variables */
# define RTE_CTAPHUFTPMSRFD_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CTAPHUFTPMSRFD_APPL_DATA

/* used for references on application functions */
# define RTE_CTAPHUFTPMSRFD_APPL_CODE

/* used for references on application constants */
# define RTE_CTAPHUFTPMSRFD_APPL_CONST

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CtApHufTPMSrfd_CONST)  ***************/

/* used for global or static SWC specific constants */
# define CtApHufTPMSrfd_CONST

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CtApHufTPMSrfd_CODE)  ****************/

/* used for SWC specific code */
# define CtApHufTPMSrfd_CODE

/***  End of saved code  ************************************************************************************/
#endif


#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CpCdHufTPMSrfd_CONST)  ***************/

/* used for global or static SWC specific constants */
# define CpCdHufTPMSrfd_CONST

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:RTE_CPCDHUFTPMSRFD_APPL)  ************/

/* used for references on application variables */
# define RTE_CPCDHUFTPMSRFD_APPL_VAR

/* used for references on application data (constants or variables) */
# define RTE_CPCDHUFTPMSRFD_APPL_DATA

/* used for references on application functions */
# define RTE_CPCDHUFTPMSRFD_APPL_CODE

/* used for references on application constants */
# define RTE_CPCDHUFTPMSRFD_APPL_CONST

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CpCdHufTPMSrfd_VAR)  *****************/

/* used for all global or static SWC specific variables that are not initialized by the startup code of the compiler */
# define CpCdHufTPMSrfd_VAR_NOINIT

/* used for global or static SWC specific variables that are initialized by the startup code of the compiler */
# define CpCdHufTPMSrfd_VAR_INIT

/* used for global or static SWC specific variables that are initialized with zero by the startup code of the compiler */
# define CpCdHufTPMSrfd_VAR_ZERO_INIT

/***  End of saved code  ************************************************************************************/
#endif

#if 0
/***  Start of saved code (symbol: compiler abstraction implementation:CpCdHufTPMSrfd_CODE)  ****************/

/* used for SWC specific code */
# define CpCdHufTPMSrfd_CODE

/***  End of saved code  ************************************************************************************/
#endif

/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << End of removed code area >>                     DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/

/* begin Fileversion check */
# ifndef SKIP_MAGIC_NUMBER /* PRQA S 0828 */ /* MD_MSR_1.1_828 */
#  ifdef RTE_MAGIC_NUMBER
#   if RTE_MAGIC_NUMBER != 1513305418
#    error "The magic number of the generated file <C:/_TSS/DAG/MFA2/Target/Appl/GenData/Rte/Rte_Compiler_Cfg.h> is different. Please check time and date of the generated RTE files!"
#   endif
#  else
#   define RTE_MAGIC_NUMBER 1513305418
#  endif  /* RTE_MAGIC_NUMBER */
# endif  /* SKIP_MAGIC_NUMBER */
/* end Fileversion check */

#endif /* _RTE_COMPILER_CFG_H */
