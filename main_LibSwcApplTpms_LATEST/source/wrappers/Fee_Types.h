#pragma once
/******************************************************************************/
/* File              : Fee_Types.h                                            */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/*#includeS                                                                  */
/******************************************************************************/
#define FEE_TYPES_MAJOR_VERSION                                             (8u)
#define FEE_TYPES_MINOR_VERSION                                             (0u)
#define FEE_TYPES_PATCH_VERSION                                             (1u)
#include "MemIf_Types.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define FEE_BLOCK_OVERHEAD                                                  (2u)
#define FEE_PAGE_OVERHEAD                                                   (0u)
#define FEE_E_INVALID_BLOCK_NO                                           (0x02u)
#define FEE_E_PARAM_DATABUFFERPTR                                        (0x10u)
#define FEE_E_PARAM_SECTOR_NUMBER                                        (0x11u)
#define FEE_E_PARAM_LENGTH_OFFSET                                        (0x12u)
#define FEE_E_BUSY                                                       (0x13u)
#define FEE_E_NO_INIT                                                    (0x14u)
#define FEE_E_PARAM_MODE                                                 (0x15u)
#define FEE_SID_INIT                                                     (0x00u)
#define FEE_SID_SETMODE                                                  (0x01u)
#define FEE_SID_READ                                                     (0x02u)
#define FEE_SID_WRITE                                                    (0x03u)
#define FEE_SID_CANCEL                                                   (0x04u)
#define FEE_SID_GETSTATUS                                                (0x05u)
#define FEE_SID_GETJOBRESULT                                             (0x06u)
#define FEE_SID_INVALIDATEBLOCK                                          (0x07u)
#define FEE_SID_GETVERSIONINFO                                           (0x08u)
#define FEE_SID_ERASEIMMEDIATEBLOCK                                      (0x09u)
#define FEE_SID_JOBENDNOTIFICATION                                       (0x10u)
#define FEE_SID_JOBERRORNOTIFICATION                                     (0x11u)
#define FEE_SID_MAINFUNCTION                                             (0x12u)
#define FEE_SID_GET_ERASE_CYCLE                                          (0x20u)
#define FEE_SID_GET_WRITE_CYCLE                                          (0x21u)
#define FEE_SID_GET_SECTOR_SWITCH_STATUS                                 (0x22u)
#define FEE_SID_FORCE_SECTOR_SWITCH                                      (0x23u)
#define FEE_SID_CONVERT_BLOCK_CONFIG                                     (0x24u)
#define FEE_SID_SUSPEND_WRITE                                            (0x30u)
#define FEE_SID_RESUME_WRITE                                             (0x31u)
#define FEE_SID_DISABLE_FSS                                              (0x32u)
#define FEE_SID_ENABLE_FSS                                               (0x33u)
#define FEE_ERRCBK_REJECT_WRITE                                           (0x0u)
#define FEE_ERRCBK_REJECT_ALL                                             (0x1u)
#define FEE_ERRCBK_RESOLVE_AUTOMATICALLY                                  (0x80)

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
typedef P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) Fee_UserDataPtrType;
typedef P2CONST(uint8, AUTOMATIC, FEE_APPL_DATA) Fee_UserDataConstPtrType;
typedef P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) Fee_UserData32PtrType;
typedef P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA) Fee_StdVersionInfoRefType;

typedef enum{
   FEE_SECTOR_SWITCH_IDLE,
   FEE_SECTOR_SWITCH_BLOCK_COPY,
   FEE_SECTOR_SWITCH_ERASE,
   FEE_SECTOR_SWITCH_UNINIT
}Fee_SectorSwitchStatusType;

typedef enum{
   FEE_SECTOR_OVERFLOW,
   FEE_SECTORS_CORRUPTED,
   FEE_SECTOR_FORMAT_FAILED,
   FEE_SECTOR_CRITICAL_FILL_LEVEL
}Fee_SectorErrorType;

typedef uint8 Fee_ErrorCallbackReturnType;
typedef P2CONST(struct Fee_PartitionConfigStruct, AUTOMATIC, FEE_APPL_CONFIG) Fee_PartitionConfigRefType;
typedef P2CONST(struct Fee_SectorConfigStruct,    AUTOMATIC, FEE_APPL_CONFIG) Fee_SectorConfigRefType;
typedef P2CONST(struct Fee_ConfigStruct,          AUTOMATIC, FEE_APPL_CONFIG) Fee_ConfigRefType;
typedef P2CONST(struct Fee_BlockConfigStruct,     AUTOMATIC, FEE_APPL_CONFIG) Fee_BlockConfigRefType;
typedef unsigned int  Fee_BitFieldType;
typedef   signed int  Fee_SignedBitfieldType;
typedef uint32        Fee_AddressType;
typedef uint32        Fee_LengthType;

struct Fee_BlockConfigStruct{
   uint16           LinktableIndex_u16;
   uint16           BlockPayloadSize_u16;
   Fee_BitFieldType NumberOfDatasets_u8          : 8;
   Fee_BitFieldType PartitionIndex               : 2;
   Fee_BitFieldType NumberOfInstancesExponent_u8 : 4;
   Fee_BitFieldType ImmediateData_bl             : 1;
   Fee_BitFieldType CriticalData_bl              : 1;
};

struct Fee_ConfigStruct{
   Fee_BlockConfigRefType     BlockConfig_at;
   Fee_PartitionConfigRefType PartitionConfig_at;
   uint16          Fee_NumberOfBlocks_u16;
   uint8           Fee_NumberOfPartitions_u8;
   uint8           Fee_DatasetSelectionBits_u8;
   boolean         Fee_ConfigurationIncomplete;
};

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

