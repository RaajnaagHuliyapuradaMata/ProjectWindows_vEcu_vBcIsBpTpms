#pragma once
/******************************************************************************/
/* File              : Compiler.hpp                                           */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Compiler_Cfg.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define COMMONASR_RH850_IMPL_COMPABSTRACT_VERSION 0x0101
#define COMMONASR_RH850_IMPL_COMPABSTRACT_RELEASE_VERSION                   0x01
#define COMPILER_VENDOR_ID                                                   30u
#define COMPILER_MODULE_ID                                                  198u
#define COMPILER_AR_MAJOR_VERSION                                           (2u)
#define COMPILER_AR_MINOR_VERSION                                           (1u)
#define COMPILER_AR_PATCH_VERSION                                           (0u)
#define COMPILER_SW_MAJOR_VERSION                                           (1u)
#define COMPILER_SW_MINOR_VERSION                                           (1u)
#define COMPILER_SW_PATCH_VERSION                                           (1u)
#define _GREENHILLS_C_RH850_
#define AUTOMATIC
#define TYPEDEF

#ifndef NULL_PTR
#define NULL_PTR                                                     ((void *)0)
#endif

#define STATIC                                                            static
#define INLINE                                                          __inline
#define LOCAL_INLINE                                               static inline
#define FUNC(rettype, memclass) rettype
#define FUNC_P2CONST(rettype, ptrclass, memclass)                 const rettype*
#define FUNC_P2VAR(rettype, ptrclass, memclass)                         rettype*
#define P2VAR(ptrtype, memclass, ptrclass)                              ptrtype*
#define P2CONST(ptrtype, memclass, ptrclass)                      const ptrtype*
#define CONSTP2VAR(ptrtype, memclass, ptrclass)                   ptrtype *const
#define CONSTP2CONST(ptrtype, memclass, ptrclass)           const ptrtype *const
#define P2FUNC(rettype, ptrclass, fctname)                    rettype (*fctname)
#define CONSTP2FUNC(rettype, ptrclass, fctname)         rettype (*const fctname)
#define CONST(type, memclass)                                         const type
#define VAR(vartype, memclass)                                           vartype

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

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

