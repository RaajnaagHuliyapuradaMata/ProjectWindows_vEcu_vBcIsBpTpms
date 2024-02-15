/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2015  by Huf Electronics Bretten GmbH                               All rights reserved.
 *
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  CtCdHufTPMSdia.h ( ComplexDevice Treiber for diagnostic) 
 *    Component:  -
 *       Module:     -
 *    Generator:  - 
 *
 *  Description:  This File is a 
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  MISRA VIOLATIONS
 *  -------------------------------------------------------------------------------------------------------------------
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Andreas Schubert          AS         Huf Electronics Bretten GmbH
 *  
 * 
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version   Date        Author  Change Id     Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  01.00.00  2016-08-03  AS                    Initial creation
 
 *********************************************************************************************************************/



/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
//#include "Rte_MemMap.h"
#include "fee_types.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#ifndef CtCdHufTPMSdia_H
#define CtCdHufTPMSdia_H
 

/* 4 ROM/FLASH Diagnose CRS_1211_050_019 */
#define START_FLASHADD4APPL 			0x00010000u /*flash!*/
/*Addresse Block20 MagicBytes 0x0007 7E00 Nicht in die Checksummen Berechnung einbauen!!*/
#define FLASH4APPL_BLOCK_LENGTH		0x07FFFu /*32KB Length*/
/*as_TestFlashChecksumme #define END_FLASHADD4APPL					0x00077DFDu  *//*flash!*/
#define END_FLASHADD4APPL					0x00077DFEu /*flash!*/

//#define CHECKSUMM_ADD_IN_APPL			0x000106B0u /* ALT !!Applikation Checksum after compiling siehe GlobData.h*/
#define CHECKSUMM_ADD_IN_APPL			0x00077DFEu /* NEU ab DMC20062*/
/* 4 ROM/FLASH DignoseCRS_1211_050_019 21.11.2016 as mit TP03 ausgemessen: 0x80=76µs=128Bytes  0x40=44µs=64Bytes*/
#define READ_BYTES4CHKInTask			0x40u /*200msTask 512KB Flash: 0x0F=16Bytes=109min//0x20=32Bytes=54min//0x40=64Bytes=27min//0x80=128Byte=13min 0xFF=255Bytes=7min*/
/* 4 RAM Diagnose CRS_1211_050_022 */
#define RAM_START_ADDRESS					0xFEDF8000u /*RAM Start address!*/
#define KEINE_RAM_ADDRESS					0x001F8000u /*KEINE RAM address! code Flash memory 4 RAM Diagnose Test!*/
#define RAM_DESTROY_CELL					0xFEDFFFF0u /*RAM defekt address 4 1.Test!*/
#define RAM_BLOCK_LENGTH					0x08000u /*32KB Length*/
#define RAM_ALIGEMENT_LENGTH			0x02000u /*32KB 0x8000 / 4 Length*/
#define RAM_END_ADDRESS						0xFEE00000u /*RAM end address!*/
#define RAM_TESTENDE_ID						0xFEE55555u /*RAM end ID address!*/


/* activation memory 97Bytes */
#define cStartByteNrInAM_Block1   2u /*Block1 [2..20]  mit]0,1] Byte0=WriteIndex, Byte1=ReadIndex*/
#define cStartByteNrInAM_Block2   21u /*Block1 [21...39] */
#define cStartByteNrInAM_Block3   40u /*Block1 [40...58] */
#define cStartByteNrInAM_Block4   59u /*Block1 [59...77]  */
#define cStartByteNrInAM_Block5   78u /*Block1 [78...96]  */

#define cReadByteNrAM_Block1			0u  /*2u+0u=  2u Block1 [ 2...20]  mit]0,1] Byte0=WriteIndex, Byte1=ReadIndex*/
#define cReadByteNrAM_Block2			19u /*2u+19u=21u Block1 [21...39] */
#define cReadByteNrAM_Block3			38u /*2u+38u=40u Block1 [40...58] */
#define cReadByteNrAM_Block4			57u /*2u+57u=59u Block1 [59...77] */
#define cReadByteNrAM_Block5			76u /*2u+76u=78u Block1 [78...96] */

#define cBytes4ActivationMemory		19u /*5x19= in cdd 20BYTES a Block TPMS SW IndexByte=ccdActivationByte + cddResultByte*/

/* message memory PAL 82Bytes*/
#define cStartByteNrInMM_PAL_Block1   2u /*Block1 [2..17]  mit]0,1] Byte0=WriteIndex, Byte1=ReadIndex*/
#define cStartByteNrInMM_PAL_Block2   18u /*Block1 [18...33] */
#define cStartByteNrInMM_PAL_Block3   34u /*Block1 [34...49] */
#define cStartByteNrInMM_PAL_Block4   50u /*Block1 [50...65]  */
#define cStartByteNrInMM_PAL_Block5   66u /*Block1 [66...81]  */

#define cReadByteNrMM_PAL_Block1			0u /*2u+0u=2u Block1 [2..17]  mit]0,1] Byte0=WriteIndex, Byte1=ReadIndex*/
#define cReadByteNrMM_PAL_Block2			16u /*Block1 [18...33] */
#define cReadByteNrMM_PAL_Block3			32u /*Block1 [34...49] */
#define cReadByteNrMM_PAL_Block4			48u /*Block1 [50...65]  */
#define cReadByteNrMM_PAL_Block5			64u /*Block1 [66...81]  */

#define cBytes4MessagenMemoryPAL			16u /*5x16= 80BYTES a Block TPMS SW +2Bytes IndexByte=ccdActivationByte + cddResultByte*/


/* TempWarn message memory  82Bytes*/
#define cStartByteNrInMM_TempWarn_Block1		2u /*Block1 [2..17]  mit]0,1] Byte0=WriteIndex, Byte1=ReadIndex*/
#define cStartByteNrInMM_TempWarn_Block2		18u /*Block1 [18...33] */
#define cStartByteNrInMM_TempWarn_Block3		34u /*Block1 [34...49] */
#define cStartByteNrInMM_TempWarn_Block4		50u /*Block1 [50...65]  */
#define cStartByteNrInMM_TempWarn_Block5		66u /*Block1 [66...81]  */

#define cReadByteNrMM_TempWarn_Block1				0u /*2u+0u=2u Block1 [2..17]  mit]0,1] Byte0=WriteIndex, Byte1=ReadIndex*/
#define cReadByteNrMM_TempWarn_Block2				16u /*Block1 [18...33] */
#define cReadByteNrMM_TempWarn_Block3				32u /*Block1 [34...49] */
#define cReadByteNrMM_TempWarn_Block4				48u /*Block1 [50...65]  */
#define cReadByteNrMM_TempWarn_Block5				64u /*Block1 [66...81]  */

#define cBytes4TempWarnMessagenMemoryPAL		16u /*5x16= 80BYTES a Block TPMS SW +2Bytes IndexByte=ccdActivationByte + cddResultByte*/

#define NOREASON 0x00u
#define ROMCHECK 0x01u
#define RAMCHECK 0x02u
#define EEPCHECK 0x03u
#define RECCHECK 0x04u

/********************************************************************************************************************************/

void WriteFIFOActivationMemory(uint8 , uint8);

/********************** BLOCK0 NVM 4 Activation Memory AM0 FD ID= 0x247 *********************************************************/
/********************** Write and Read Index ************************************************************************************/
uint8 GETucAM_ReadIndex(void);
void PUTucAM_ReadIndex(uint8);
uint8 GETucAM_WriteIndex(void);
void PUTucAM_WriteIndex(uint8 value);
/********************** Write and Read in Index X *******************************************************************************/
uint8 GETucActivationMemoryX(uint8 x);
void PUTucActivationMemoryX(uint8 value, uint8 index );
void ClearActivationMemoryX(void);
void PutActivationMemory2NVM(void);

/********************************************************************************************************************************/
void WriteFIFOMessageMemoryPAL(uint8 , uint8);
uint8 ReadLastPosAndWarnStateFromMMPAL(uint8);
/*******************************************************************************************************************************/
/********************** BLOCK0 NVM 4 Activation Memory AM0 FD ID= 0x245 *********************************************************/
/********************** Write and Read Index ************************************************************************************/
uint8 GETucMM_PAL_ReadIndex(void);
void PUTucMM_PAL_ReadIndex(uint8);
uint8 GETucMM_PAL_WriteIndex(void);
void PUTucMM_PAL_WriteIndex(uint8 value);
/********************** Write and Read in Index X *******************************************************************************/
uint8 GETucMM_PALX(uint8 x);
void PUTucMM_PALX(uint8 value, uint8 index );
void ClearMM_PALX(void);
void PutMessageMemoryPAL2NVM(void);


/********************************************************************************************************************************/
void WriteFIFOTempWarnMM(uint8);
/*******************************************************************************************************************************/
/********************** BLOCK0 NVM 4 Activation Memory AM0 FD ID= 0x24D *********************************************************/
/********************** Write and Read Index ************************************************************************************/
uint8 GETucMM_TempWarn_ReadIndex(void);
void PUTucMM_TempWarn_ReadIndex(uint8);
uint8 GETucMM_TempWarn_WriteIndex(void);
void PUTucMM_TempWarn_WriteIndex(uint8 value);
/********************** Write and Read in Index X *******************************************************************************/
uint8 GETucMM_TempWarnX(uint8 x);
void PUTucMM_TempWarnX(uint8 value, uint8 index );
void ClearMM_TempWarnX(void);
void PutTempWarnMessageMemory2NVM(void);


/********************NVM Access of EVC data *************************************************************************************/
uint8 GETtEvcCfgBitsOfRam(uint8);
void PUTtEvcCfgBits2Ram(uint8, uint8);
void PUTtEvcCfgBits2NVM(void);


void PUTucUnexpectedEcuResetCnt(uint8);
void PUTucUnexpectedEcuResetCnt2Nvm(void);
uint8 GETucUnexpectedEcuResetCnt(void);
void ClearUnexResCnt(void);
void DoUnexResCnt(void);
void UnDoUnexResCnt(void);

void CopyNvmData(uint16 Length, uint8*, const uint8*);

void PutEcuInternalFailure(uint8 ui8FailureNum);
uint8 GETui8EcuInternalFailure(void);

uint8 GETucSNRlongTerm(uint8);
void PUTucSNRlongTerm(uint8 x, uint8 idx);


Fee_ErrorCallbackReturnType Appl_CriticalErrorCallback(uint8 partitionId, Fee_SectorErrorType err);

extern void ConfigTestPin(void); 
extern void TP3_AS(uint8);
extern void ReStart4SetValue2ActivationMemAFD(void); /*CRS_1211_130_376*/
extern void UpdateHMICurrentTireStat4MM(void);

/*******************************************************************************************************************************/

/********************************************************************************************************************************/
/********************************************************************************************************************************/
 
 
 
 
 #endif
