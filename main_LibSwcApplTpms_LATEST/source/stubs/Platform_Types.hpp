#pragma once
/******************************************************************************/
/* File              : Platform_Types.h                                       */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/*******************************************************************************
Platform types for
--------------------------------------------------------------------------------
Vendor          : NXP
Platform Family : S32K
Platform        : ???
Derivative      : ???
*******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define FALSE                                                                 0u
#define TRUE                                                                  1u
#define COMMONASR_RH850_IMPL_PLATFORMTYPES_VERSION                        0x0102 /*TBD: Change to NXP S32K??? */
#define COMMONASR_RH850_IMPL_PLATFORMTYPES_RELEASE_VERSION                  0x00 /*TBD: Change to NXP S32K??? */
#define PLATFORM_VENDOR_ID                                                   30u
#define PLATFORM_MODULE_ID                                                  199u
#define PLATFORM_AR_MAJOR_VERSION                                           (2u)
#define PLATFORM_AR_MINOR_VERSION                                           (2u)
#define PLATFORM_AR_PATCH_VERSION                                           (1u)
#define PLATFORM_SW_MAJOR_VERSION                                           (1u)
#define PLATFORM_SW_MINOR_VERSION                                           (2u)
#define PLATFORM_SW_PATCH_VERSION                                           (0u)
#define CPU_TYPE_8                                                            8u
#define CPU_TYPE_16                                                          16u
#define CPU_TYPE_32                                                          32u
#define MSB_FIRST                                                             0u
#define LSB_FIRST                                                             1u
#define HIGH_BYTE_FIRST                                                       0u
#define LOW_BYTE_FIRST                                                        1u

#define CPU_TYPE                                                     CPU_TYPE_32
#define CPU_BIT_ORDER                                                  LSB_FIRST
#define CPU_BYTE_ORDER                                            LOW_BYTE_FIRST

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef unsigned char                                                   boolean;
typedef signed char                                                       sint8;
typedef unsigned char                                                     uint8;
typedef signed short                                                     sint16;
typedef unsigned short                                                   uint16;
typedef signed long                                                      sint32;
typedef unsigned long                                                    uint32;
typedef signed int                                                  sint8_least;
typedef unsigned int                                                uint8_least;
typedef signed int                                                 sint16_least;
typedef unsigned int                                               uint16_least;
typedef signed int                                                 sint32_least;
typedef unsigned int                                               uint32_least;

#if defined(__ghs__) && !defined(__LLONG_BIT)
#else
#define PLATFORM_SUPPORT_SINT64_UINT64
typedef   signed long long                                               sint64;
typedef unsigned long long                                               uint64;
#endif

#if defined(__ghs__) && defined(__NoFloat__)
#else
typedef float                                                           float32;
typedef double                                                          float64;
#endif

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

