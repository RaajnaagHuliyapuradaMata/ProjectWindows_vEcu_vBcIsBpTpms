#pragma once
/******************************************************************************/
/* File              : Std_Types.hpp                                          */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define STD_TYPES_VENDOR_ID                                                (30u)
#define STD_TYPES_MODULE_ID                                               (197u)
#define COMMONASR__COMMON_IMPL_STDTYPES_VERSION                           0x0304
#define COMMONASR__COMMON_IMPL_STDTYPES_RELEASE_VERSION                     0x04
#define STD_TYPES_AR_MAJOR_VERSION                                          (1u)
#define STD_TYPES_AR_MINOR_VERSION                                          (2u)
#define STD_TYPES_AR_PATCH_VERSION                                          (0u)
#define STD_TYPES_SW_MAJOR_VERSION                                          (3u)
#define STD_TYPES_SW_MINOR_VERSION                                          (4u)
#define STD_TYPES_SW_PATCH_VERSION                                          (4u)

#define STD_VENDOR_ID                                        STD_TYPES_VENDOR_ID
#define STD_MODULE_ID                                        STD_TYPES_MODULE_ID
#define STD_AR_MAJOR_VERSION                          STD_TYPES_AR_MAJOR_VERSION
#define STD_AR_MINOR_VERSION                          STD_TYPES_AR_MINOR_VERSION
#define STD_AR_PATCH_VERSION                          STD_TYPES_AR_PATCH_VERSION
#define STD_SW_MAJOR_VERSION                          STD_TYPES_SW_MAJOR_VERSION
#define STD_SW_MINOR_VERSION                          STD_TYPES_SW_MINOR_VERSION
#define STD_SW_PATCH_VERSION                          STD_TYPES_SW_PATCH_VERSION

#define STD_HIGH                                                              1u
#define STD_LOW                                                               0u
#define STD_ACTIVE                                                            1u
#define STD_IDLE                                                              0u
#define STD_ON                                                                1u
#define STD_OFF                                                               0u
#define E_OK                                                    ((StatusType)0U)
#define E_NOT_OK                                                ((StatusType)1U)
#define E_PENDING                                                             2u

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Platform_Types.hpp"
#include "Compiler.hpp"

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef uint8 StatusType;
typedef uint8 Std_ReturnType;

typedef struct{
   uint16 vendorID;
   uint16 moduleID;
   uint8  instanceID;
   uint8  sw_major_version;
   uint8  sw_minor_version;
   uint8  sw_patch_version;
}Std_VersionInfoType;

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
