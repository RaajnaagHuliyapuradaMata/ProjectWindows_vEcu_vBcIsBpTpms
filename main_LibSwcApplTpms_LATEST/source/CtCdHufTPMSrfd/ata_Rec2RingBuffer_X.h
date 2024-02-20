

#ifndef _RINGBUFFER_X_H
#define _RINGBUFFER_X_H

#include "ata_dev_5785.h"
#include "GlobData.h"

#define cBUFFER_SIZE           10

#define cOVERWRITE_MODE        (unsigned char) 0x01
#define cSAVE_ERROR_TEL        (unsigned char) 0x02
#define cWRITE_MODE            (unsigned char) 0x04
#define cREAD_ACCESS_ACTIVE    (unsigned char) 0x08
#define cERROR_TEL_IN_BUFFER   (unsigned char) 0x10
#define cMODE2_TEL_IN_BUFFER   (unsigned char) 0x20
#define cSAVE_MODE2_ONLY       (unsigned char) 0x40

typedef struct {
    uint32 ulTimeInMsec;
    uint8  ucByte[RB_DATA_LEN];
     uint8  ucRssiNoise;
   uint8  ucRssi[RB_RS_BUF_LEN];
 } tPreBuf;

union ringbuffer
{
  tPreBuf Tel;
  uint8 byte[(uint8) sizeof(tPreBuf)];
};

extern void InitRB(void);
void SetAtaRec(uint8 ucSetData);
extern uint8 StartAtaRec(uint8 ucServNr);
extern void PutRB(struct rfstruct * tRfBuf);
extern void ChkAtaRecive(void);
extern uint8 ChkAtaError(void);
 extern void GetRB(void);
extern unsigned char GetBufferStateRB(void);
extern void ConfigRingBufferCC(unsigned char);
extern unsigned char GetBitBufferConditionRegisterRB(unsigned char ucBitMask);
extern uint8 ui8GetComptoirRepare(void);
extern uint8 ui8GetErrorCnt(void);
extern uint8 ui8GetAtaErrRecNVM(void);
extern void PutAtaErrRecNVM(uint8);

#endif
