/************************************************************************************************************
 * (c) Beru Electronics GmbH      Abteilung BES       2007
 * (c) Huf  Electronics GmbH      Abteilung ENTS4     2014
 ************************************************************************************************************/
/************************************************************************************************************
 * Project:       Reifendruckkontrolle TSPM (TPMS = tyre pressure monitor system)
 *
 * $Archive: C:\_TSS\DAG\MFA2\Target\SWC\Source\CtCdHufTPMSrfd\ata_Rec2RingBuffer_X.h $
 *
 * File Status:   compiled           - (under construction, compiled etc.)
 *
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * rh           Ralf Hanke                     Beru Electronics GmbH (BES)   2007
 * pb           Peter Brand                    Huf  Electronics GmbH (ENTS4) 2014 ...
 * as           Andreas Schubert               Huf  Electronics GmbH (ENTS4) 2014 ... 
 ************************************************************************************************************/
/************************************************************************************************************
 * Author:
 *
 * Initials     Name                           Company
 * --------     --------------------------     --------------------------------------------------------------
 * rh           Ralf Hanke                     Beru Electronics GmbH (BES)
 *
 ************************************************************************************************************/
#ifndef _RINGBUFFER_X_H /* [0] */
#define _RINGBUFFER_X_H

#include "ata_dev_5785.h"
#include "GlobData.h"

/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
#define cBUFFER_SIZE           10          // Total ringbuffer slots

/* Masken für Puffer-Zustands-Register */
#define cOVERWRITE_MODE        (unsigned char) 0x01        /* Überschreibmodus aktiv */
#define cSAVE_ERROR_TEL        (unsigned char) 0x02        /* Fehlerhafte Telegramme speichern */
#define cWRITE_MODE            (unsigned char) 0x04        /* Schreibmode aktiv */
#define cREAD_ACCESS_ACTIVE    (unsigned char) 0x08        /* Leserechte setzen */
#define cERROR_TEL_IN_BUFFER   (unsigned char) 0x10        /* Mind. ein Tel mit HF-Empfangs-Fehlern im Ringpuffer gespeichert */
#define cMODE2_TEL_IN_BUFFER   (unsigned char) 0x20        /* Mind. ein Tel im Mode2 im Ringpuffer gespeichert */
#define cSAVE_MODE2_ONLY       (unsigned char) 0x40        /* Nur HF-Telegramme in Mode2 im Puffer speichern */

//#define RB_DATA_LEN (unsigned char) 24
//#define RB_RS_BUF_LEN (unsigned char) 6


/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/

/*
 Ringbuffer Datenstruktur

*/
typedef struct {
    uint32 ulTimeInMsec;
    uint8  ucByte[RB_DATA_LEN];      //24
    uint8  ucRssiNoise;
	uint8  ucRssi[RB_RS_BUF_LEN];    //6  is smaller than RF_RS_BUF_LEN 
} tPreBuf;

/* Union für Byteweisen Zugriff auf Ringbuffer Datenstruktur */
union ringbuffer
{
  tPreBuf Tel;
  uint8 byte[(uint8) sizeof(tPreBuf)];
};


/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - public)
 ***********************************************************************************************************/
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/
extern void InitRB(void);
void SetAtaRec(uint8 ucSetData);
extern uint8 StartAtaRec(uint8 ucServNr); /*CR_1211_150_022*/
extern void PutRB(struct rfstruct * tRfBuf);
extern void ChkAtaRecive(void);
extern uint8 ChkAtaError(void);
//extern void GetRB(tRecRFTelType * pucDat);
//extern void GetRB(uint8 *);
extern void GetRB(void);
extern unsigned char GetBufferStateRB(void);
extern void ConfigRingBufferCC(unsigned char);
extern unsigned char GetBitBufferConditionRegisterRB(unsigned char ucBitMask);
extern uint8 ui8GetComptoirRepare(void);
extern uint8 ui8GetErrorCnt(void);
extern uint8 ui8GetAtaErrRecNVM(void);
extern void PutAtaErrRecNVM(uint8);

#endif /* #ifndef _RINGBUFFER_X_H */ /* [0] */
