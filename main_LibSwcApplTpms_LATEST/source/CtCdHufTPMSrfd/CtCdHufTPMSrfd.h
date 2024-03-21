

#ifndef CtCdHufTPMSrfd_H
#define CtCdHufTPMSrfd_H

void RFD_CsAta(uint8 ucSet);
void RFD_PwrAta(uint8 ucSet);
void RFD_Pwr3Pin4Ata(uint8 ucSet);
void FastPWR_3Pin4_ATA(uint8 ucSet);
extern uint8 GetPort4Frequenz433(void);
void TP0(uint8 ucSet);
void TP1(uint8 ucSet);
void TP2(uint8 ucSet);
void TP3(uint8 ucSet);

extern void ReInitAfterError(void);

#endif
