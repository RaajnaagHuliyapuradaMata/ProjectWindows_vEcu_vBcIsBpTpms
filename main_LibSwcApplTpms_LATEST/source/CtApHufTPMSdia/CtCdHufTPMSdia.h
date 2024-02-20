
#include "fee_types.h"

#ifndef CtCdHufTPMSdia_H
#define CtCdHufTPMSdia_H

#define START_FLASHADD4APPL          0x00010000u

#define FLASH4APPL_BLOCK_LENGTH      0x07FFFu

#define END_FLASHADD4APPL               0x00077DFEu

#define CHECKSUMM_ADD_IN_APPL         0x00077DFEu

#define READ_BYTES4CHKInTask         0x40u

#define RAM_START_ADDRESS               0xFEDF8000u
#define KEINE_RAM_ADDRESS               0x001F8000u
#define RAM_DESTROY_CELL               0xFEDFFFF0u
#define RAM_BLOCK_LENGTH               0x08000u
#define RAM_ALIGEMENT_LENGTH         0x02000u
#define RAM_END_ADDRESS                  0xFEE00000u
#define RAM_TESTENDE_ID                  0xFEE55555u

#define cStartByteNrInAM_Block1   2u
#define cStartByteNrInAM_Block2   21u
#define cStartByteNrInAM_Block3   40u
#define cStartByteNrInAM_Block4   59u
#define cStartByteNrInAM_Block5   78u

#define cReadByteNrAM_Block1         0u
#define cReadByteNrAM_Block2         19u
#define cReadByteNrAM_Block3         38u
#define cReadByteNrAM_Block4         57u
#define cReadByteNrAM_Block5         76u

#define cBytes4ActivationMemory      19u

#define cStartByteNrInMM_PAL_Block1   2u
#define cStartByteNrInMM_PAL_Block2   18u
#define cStartByteNrInMM_PAL_Block3   34u
#define cStartByteNrInMM_PAL_Block4   50u
#define cStartByteNrInMM_PAL_Block5   66u

#define cReadByteNrMM_PAL_Block1         0u
#define cReadByteNrMM_PAL_Block2         16u
#define cReadByteNrMM_PAL_Block3         32u
#define cReadByteNrMM_PAL_Block4         48u
#define cReadByteNrMM_PAL_Block5         64u

#define cBytes4MessagenMemoryPAL         16u

#define cStartByteNrInMM_TempWarn_Block1      2u
#define cStartByteNrInMM_TempWarn_Block2      18u
#define cStartByteNrInMM_TempWarn_Block3      34u
#define cStartByteNrInMM_TempWarn_Block4      50u
#define cStartByteNrInMM_TempWarn_Block5      66u

#define cReadByteNrMM_TempWarn_Block1            0u
#define cReadByteNrMM_TempWarn_Block2            16u
#define cReadByteNrMM_TempWarn_Block3            32u
#define cReadByteNrMM_TempWarn_Block4            48u
#define cReadByteNrMM_TempWarn_Block5            64u

#define cBytes4TempWarnMessagenMemoryPAL      16u

#define NOREASON 0x00u
#define ROMCHECK 0x01u
#define RAMCHECK 0x02u
#define EEPCHECK 0x03u
#define RECCHECK 0x04u

void WriteFIFOActivationMemory(uint8 , uint8);

uint8 GETucAM_ReadIndex(void);
void PUTucAM_ReadIndex(uint8);
uint8 GETucAM_WriteIndex(void);
void PUTucAM_WriteIndex(uint8 value);

uint8 GETucActivationMemoryX(uint8 x);
void PUTucActivationMemoryX(uint8 value, uint8 index );
void ClearActivationMemoryX(void);
void PutActivationMemory2NVM(void);

void WriteFIFOMessageMemoryPAL(uint8 , uint8);
uint8 ReadLastPosAndWarnStateFromMMPAL(uint8);

uint8 GETucMM_PAL_ReadIndex(void);
void PUTucMM_PAL_ReadIndex(uint8);
uint8 GETucMM_PAL_WriteIndex(void);
void PUTucMM_PAL_WriteIndex(uint8 value);

uint8 GETucMM_PALX(uint8 x);
void PUTucMM_PALX(uint8 value, uint8 index );
void ClearMM_PALX(void);
void PutMessageMemoryPAL2NVM(void);

void WriteFIFOTempWarnMM(uint8);

uint8 GETucMM_TempWarn_ReadIndex(void);
void PUTucMM_TempWarn_ReadIndex(uint8);
uint8 GETucMM_TempWarn_WriteIndex(void);
void PUTucMM_TempWarn_WriteIndex(uint8 value);

uint8 GETucMM_TempWarnX(uint8 x);
void PUTucMM_TempWarnX(uint8 value, uint8 index );
void ClearMM_TempWarnX(void);
void PutTempWarnMessageMemory2NVM(void);

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
extern void ReStart4SetValue2ActivationMemAFD(void);
extern void UpdateHMICurrentTireStat4MM(void);

 #endif
