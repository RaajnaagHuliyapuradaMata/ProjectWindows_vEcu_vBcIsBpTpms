

#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

void InitRB(void);
uint8 StartAtaRec(uint8 ucServNr);
void SetAtaRec(uint8 ucSetData);
uint8 CheckAtaRec(void);
extern void ChkAtaRecive(void);
uint8 ChkAtaError(void);
uint8 GetBufferStateRB(void);
void GetRB( void);
void RestartAtaRec(uint8 ucPathNServNr);
extern void PutRB(struct rfstruct * tRfBuf);
uint8 ui8GetErrorCnt(void);
extern void InitRFTelBufferW0x55ForWhatSoEver(void);
#endif
