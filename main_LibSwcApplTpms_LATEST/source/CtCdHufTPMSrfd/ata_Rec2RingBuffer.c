/************************************************************************************************************
* (c) Beru Electronics GmbH      Abteilung BES       2007
* (c) Huf  Electronics GmbH      Abteilung ENTS4     2014
************************************************************************************************************/
/************************************************************************************************************
* Project:       Reifendruckkontrolle TPMS (TPMS = tyre pressure monitor system)
*
* $Archive: C:\_TSS\DAG\MFA2\Target\SWC\Source\CtCdHufTPMSrfd\ata_Rec2RingBuffer.c $
*
* File Status:   compiled           - (under construction, compiled etc.)
*
************************************************************************************************************/
/************************************************************************************************************
* Author:
*
* Initials     Name                           Company
* --------     --------------------------     --------------------------------------------------------------
* pb           Peter Brand                    Huf  Electronics GmbH (BEE1) 2014 ...
* as           Andreas Schubert               Huf  Electronics GmbH (ENTS4) 2014 ... 
************************************************************************************************************/
/************************************************************************************************************
* Global Description
* ==================
*
*
*
************************************************************************************************************/
/************************************************************************************************************
* Modul Description
* =================
*
* Purpose:
*
* rf telegram buffer
*
************************************************************************************************************/
/************************************************************************************************************
* Modul Abbreviation:
* ===================
*
*
************************************************************************************************************/
/************************************************************************************************************
* Glossary
* ========
*
*
************************************************************************************************************/


/************************************************************************************************************
*                                             include
************************************************************************************************************/
#include "Platform_Types.h" /*BSW types.h*/ 
#include "Spi.h" /*BSW */
#include "ata_Rec2RingBuffer_X.h"
#include "Rte_CtCdHufTPMSrfd.h"
#include "internal_clockX.h"
#include "CtCdHufTPMSrfd.h" // for testpoints - only for debug

extern void csig0_4ATAinit(void);
extern DT_auRfStruct aucRfStruct;

/************************************************************************************************************
*                                             macro
************************************************************************************************************/
//#define TestTPx  /* TestPin enable for time mesurament
#define cMODE1_TEL   (uint8) 0x01    /* Maske zum dedektieren von Mode2 und 3 Telegrammen */
#define cDefConfRBuf (uint8) 0x00    /* no overwrite mode active - no error tels */

#define cATAok       (uint8) 0x00    /* Atmel receiver has no error */
#define cATAhasError (uint8) 0xFF    /* Atmel receiver is erroneous */
#define cCountsOfErr (uint8) 0x64    /* count tolerance */

//#define RFChipTest_Instrument // ToDo: must be deactivated for delivery !!
/************************************************************************************************************
*                                            typedef
************************************************************************************************************/



/************************************************************************************************************
*                                    data (Modulglobal) - ROM
************************************************************************************************************/



/************************************************************************************************************
*                                    data (Modulglobal) - RAM
************************************************************************************************************/

uint8 ui8TelCt = 0;
//static uint8 ucErrorCode = 0;
//static uint8 ucSMState = 0;
static uint8 uiErrorCNT = 0;
uint8 ucCrcPassedTel; // Counter for telegrams with valid CRC
uint8 ucCrcFailedTel; // Counter for telegrams with invalid CRC

static union ringbuffer tBufferData[cBUFFER_SIZE];   /* Ringpuffer-Array: Datenstruktur siehe Ringbuffer.h */

/*
Puffer-Zustands-Register: Beschreibt bitweise den Zustand des Puffers.

ucBCR = MSB 0 X X X X X X LSB
Bit 8 tbd                                     | | | | | | |
1 = Nur HF-Telegramme in Mode2 speichern -----' | | | | | |
1 = HF-Telegramm in Mode2 gespeichert-----------' | | | | |
1 = HF-Telegramm mit Fehlern gespeichert----------' | | | |
1 = Lesezugriff aktiviert---------------------------' | | |
1 = Schreibzugriff aktiviert--------------------------' | |
1 = Speicherung fehlerhafter Telegramme erlauben--------' |
1 = Überschreibmodus, wenn Puffer voll--------------------'
*/

struct para{
  uint8 ucBCR;
  uint8 ucWrTelPos;          /* Schreibposition im Puffer */
  uint8 ucRdTelPos;          /* Leseposition im Puffer */
  uint8 ucWrTelPosSearch;    /* Schreibposition für Mode2 und Fehlertelegramme */
  uint8 ucWrError;           /* Merker Schreibposition für HF-Error-Telegramme */
  uint8 ucOrCt;              /* Überlaufzähler: Zählt Überläufe des Puffers (0x00...0xFF) */
  uint8 bBufferOverrun;      /* Puffer-Überlauf-Flag */
};

static struct para tPara;

static uint8 ui8RepairCnt = (uint8) 0;
/************************************************************************************************************
*                                       data (global) - ROM
************************************************************************************************************/



/************************************************************************************************************
*                                       data (global) - RAM
************************************************************************************************************/



/***********************************************************************************************************
*                                 prototype (local functions - private)
***********************************************************************************************************/
uint8 appBuild8CRC(const uint8 *pui8Buffer, uint8 ui8MessageLen, uint8 ui8BitsInFirstByte, uint8 ui8Polynom, uint8 ui8CrcStartValue);

static void PosWrPointerRB(signed char);
static void PosRdPointerRB(signed char);

static uint8 ui8RepairMessage(struct rfstruct * p2Tel, uint8 ui8TeLen);
static uint8 ui8GetLenOfTelType(uint8 ui8TelType);

/***********************************************************************************************************
*                                 prototype (local functions - public)
***********************************************************************************************************/



/************************************************************************************************************
*                               prototype (external functions - interface)
************************************************************************************************************/


/************************************************************************************************************
*                                            implementation
************************************************************************************************************/

/************************************************************************************************************
*                                            private functions
************************************************************************************************************/


/************************************************************************************************************
* Function:          void PosWrPointerRB(signed char cIncDec)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Positioniert den Schreib-Zeiger des Ringpuffers. Inkrementiert bzw. dekrementiert den
*                    Zeiger anhand des übergebenen Parameters.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         signed char cIncDec - Anzahl Inkremente (Vorzeichenbehaftet)
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/

static void PosWrPointerRB(signed char cIncDec)
{
  tPara.ucWrTelPos += cIncDec;
  if ( (cIncDec>=0) && (tPara.ucWrTelPos >= cBUFFER_SIZE) )   /* increment */
  {
    tPara.ucWrTelPos = 0;                                    /* overflow */
  }
  else if(tPara.ucWrTelPos>=cBUFFER_SIZE)                     /* decrement */
  {
    tPara.ucWrTelPos = cBUFFER_SIZE - 1;                      /* underflow */
  }
}

/************************************************************************************************************
* Function:          void PosRdPointerRB(signed char cIncDec)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Positioniert den Lese-Zeiger des Ringpuffers. Inkrementiert bzw. dekrementiert den
*                    Zeiger anhand des übergebenen Parameters.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         signed char cIncDec - Anzahl Inkremente (Vorzeichenbehaftet)
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/

static void PosRdPointerRB(signed char cIncDec)
{

  tPara.ucBCR &= ~cMODE2_TEL_IN_BUFFER;

  /* increment */
  tPara.ucRdTelPos += cIncDec;

  if ( (cIncDec >= 0) && (tPara.ucRdTelPos >= cBUFFER_SIZE) )   /* increment */
  {
    tPara.ucRdTelPos = 0;                                       /* overflow */
  }
  else if (tPara.ucRdTelPos>=cBUFFER_SIZE)                      /* decrement */
  {
    tPara.ucRdTelPos = cBUFFER_SIZE - 1;                        /* underflow */
  }
}

/************************************************************************************************************
* Function:          void GetRB(uint8 * pDataOut)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Liefert nächtest Telegramm im Ringpuffer. Über das Konstanten-Array caucOutputMapping[]
*                    wird festgelegt, welche Daten über den Datenzeiger pDataOut zurückgegeben werden.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         Ausgabepuffer strucktur AK35Tel.ucType ...
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            initialization state uint8 GetRB( tRecRFTelType (* pDataOut))->CR_1211_150_022
*
************************************************************************************************************/
uint8 StartAtaRec(uint8 ucPathNServNr)
{
  uint8 i;
  uint8 ucAtaInitSate=TRUE; /*CR_1211_150_022*/

  if( rf_ata5785_init() == TRUE )  /*CR_1211_150_021*/
  {

    SetServNPath(ucPathNServNr);
    for(i=0; i<sizeof(tRecRFTelData); i++) /* for Transmit to CAN */
    {
      tRecRFTel.ucByteAccess[i] = 0x55;
    }
  }
  else
  {
    ucAtaInitSate=FALSE; /* Please start reinit event*/
  }

  return ucAtaInitSate;/*CR_1211_150_022*/
}
/************************************************************************************************************
*                                            public functions
************************************************************************************************************/
/************************************************************************************************************
* Function:          void InitRB(void)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Initialisierung des Ringpuffers.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         union ringbuffer * tData - Zu speicherndes Datenpaket
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/
void InitRB(void)
{
  uint8 i, j;

  tPara.ucWrTelPos=0;
  tPara.ucWrTelPosSearch=0;
  tPara.ucRdTelPos=0;
  tPara.ucWrError=cBUFFER_SIZE;
  tPara.ucBCR=cOVERWRITE_MODE;
  tPara.bBufferOverrun=0;
  tPara.ucOrCt=0;

  for(i=0; i<cBUFFER_SIZE; i++)
  {
    for(j=0; j<(uint8) sizeof(tPreBuf); j++)
    {
      tBufferData[i].byte[j]=0x00;
    }
  }

}


/************************************************************************************************************
* Function:          void GetRB(uint8 * pDataOut)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Liefert nächtest Telegramm im Ringpuffer. Über das Konstanten-Array caucOutputMapping[]
*                    wird festgelegt, welche Daten über den Datenzeiger pDataOut zurückgegeben werden.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         Ausgabepuffer strucktur AK35Tel.ucType ...
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            nonevoid GetRB( tRecRFTelType (* pDataOut))
*
************************************************************************************************************/
void GetRB( void)
{
  uint8 i;

  tPara.ucBCR |= cREAD_ACCESS_ACTIVE;    /* Leserechte für Ringpuffer setzen */
  tRecRFTel.AK35Data.ulTime=  tBufferData[tPara.ucRdTelPos].Tel .ulTimeInMsec;
#ifdef V24_64F1L   
  WordIn4AsciiBytesToV24(tBufferData[tPara.ucRdTelPos].Tel .ushTimeInMsec); /*send data to uart v24*/
#endif
  //pDataOut->RecRFAK35Tel.ucAVRS = tBufferData[tPara.ucRdTelPos].Tel.ucRssi[0];
  //tRecRFTel.AK35Data.ucAVRS = tBufferData[tPara.ucRdTelPos].Tel.ucRssi[0];
  tRecRFTel.AK35Data.ucNoise = tBufferData[tPara.ucRdTelPos].Tel.ucRssiNoise; /*CR_1211_150_010*/
#ifdef V24_64F1L
  RLIN30_send_byte(0x20); /*Leerzeichen 4 Exel */
  ByteIn2AsciiToV24(tBufferData[tPara.ucRdTelPos].Tel.ucRssi[0]); /*send data to uart v24*/
  RLIN30_send_byte(0x20); /*Leerzeichen 4 Exel */
#endif


  for(i=0; i<(uint8) (RB_DATA_LEN); i++) // RB_DATA_LEN=24 copy timestamp + tel dat + tel rssi
  {
    //pDataOut->RecRFTel.aucTel[i] = tBufferData[tPara.ucRdTelPos].Tel.ucByte[i];
    //pDataOut->RecRFAK35Tel.aucTel[i] = tBufferData[tPara.ucRdTelPos].Tel.ucByte[i];

    tRecRFTel.AK35Data.aucTel[i] = tBufferData[tPara.ucRdTelPos].Tel.ucByte[i];
#ifdef V24_64F1L
    if(i==1)
      RLIN30_send_byte(0x20); /*Leerzeichen 4 Exel 4Byte ID*/
    if(i==5)
      RLIN30_send_byte(0x20); /*Leerzeichen 4 Exel 20Byte Data*/
    ByteIn2AsciiToV24(tBufferData[tPara.ucRdTelPos].Tel.ucByte[i]); /*send data to uart v24*/
#endif


  }
  //RLIN30_send_byte(0x20); /*Leerzeichen 4 Exel */
  for(i=0; i<(uint8) (RB_RS_BUF_LEN); i++) // RB_RS_BUF_LEN=6 copy timestamp + tel dat RB_DATA_LEN =24Bytes + tel rssi 6Bytes
  {
    //pDataOut->RecRFTel.aucTel[i] = tBufferData[tPara.ucRdTelPos].Tel.ucByte[i];
    //pDataOut->RecRFAK35Tel.aucTel[i] = tBufferData[tPara.ucRdTelPos].Tel.ucByte[i];

    tRecRFTel.AK35Data.aucTel[RB_DATA_LEN +i ] = tBufferData[tPara.ucRdTelPos].Tel.ucRssi[i];
#ifdef V24_64F1L
    RLIN30_send_byte(0x20); /*Leerzeichen 4 Exel */
    ByteIn2AsciiToV24(tBufferData[tPara.ucRdTelPos].Tel.ucByte[i]); /*send data to uart v24*/
#endif
  }

  PosRdPointerRB(1);                     /* Lesezeiger des Ringpuffers inkrementieren */
  if(tPara.bBufferOverrun)               /* BufferOverRun-Flag gesetzt? */
  {
    PosWrPointerRB(1);                   /* Schreibzeiger des Ringpuffers inkrementieren */
    tPara.bBufferOverrun=0;          /* BufferOverRun-Flag zurücksetzen */
  }


  for(i=0; i<sizeof(aucRfStruct); i++) // RB_RS_BUF_LEN=6 copy timestamp + tel dat RB_DATA_LEN =24Bytes + tel rssi 6Bytes
  {
    aucRfStruct[i] = tRecRFTel.ucByteAccess[i];
  }
  tPara.ucBCR&=~cREAD_ACCESS_ACTIVE;     /* Clear Read Access in BCR */
}

/************************************************************************************************************
* Function:          uint8 PutRB(union ringbuffer * tData)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Schreibt ein empfangenes HF-Telegramm in den Ringpuffer.
*                    WARNING: this function probably runs in a ISR1 context !!
* ----------------------------------------------------------------------------------------------------------
** SW_Requirements: {variable ring buffer size E90D5A7F-46D7-4ab3-8CC3-D51DD568CE5C}
*
* Parameter:         union ringbuffer * tData - Zu speicherndes Datenpaket
*
* Input (global):    * pucInBuf points to byte array w/ length cBUFFER_SLOTEL_LEN, that contains new telgram data (Data and RSS as well)
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/

void PutRB(struct rfstruct * tRfBuf)
{
  uint8 i,ucTop;

  if (tPara.bBufferOverrun == 0)   /* Kein Pufferüberläuf dedektiert */
  {
    //TP0 (1);
    
    tPara.ucBCR |= cWRITE_MODE;        /* Schreibzugriff setzen */

    tPara.ucWrTelPosSearch = tPara.ucWrTelPos;    // no more overwrite functionality

    ucTop = (tRfBuf->level>RB_DATA_LEN) ? RB_DATA_LEN:tRfBuf->level;
    for (i=0; i<ucTop ; i++) // // wr data val to RB full up rest w/ 0
    {
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucByte[i] = tRfBuf->buffer[i];
    }
    for (i=ucTop; i<(uint8) RB_DATA_LEN ; i++) // write all data bytes + rssi bytes
    {
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucByte[i] = 0;
    }
    for (i=0; i<((tRfBuf->rssilvl>RB_RS_BUF_LEN) ? RB_RS_BUF_LEN:tRfBuf->rssilvl ); i++) // wr RS val to RB full up rest w/ 0
    {
      //tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssi[i] = tRfBuf->rssibuf[i];
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssi[i] = tRfBuf->rssibuf[tRfBuf->rssilvl - i - 1]; /*CR_1211_150_010*/
    }
    tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssiNoise = tRfBuf->rssibuf[0];/*CR_1211_150_010*/

    for (i=((tRfBuf->rssilvl>RB_RS_BUF_LEN) ? RB_RS_BUF_LEN:tRfBuf->rssilvl) ; i<(uint8) RB_RS_BUF_LEN ; i++) // write all data bytes + rssi bytes
    {
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssi[i] = 0;
    }
    tBufferData[tPara.ucWrTelPosSearch].Tel.ucByte[RB_DATA_LEN-1] = tRfBuf->level;
    tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssi[RB_RS_BUF_LEN -1] = tRfBuf->rssilvl;
    /*@as F1L BSWWERT=111 TEST Hier muss später der Timerwert SYSTEM Uhr für den Zeitstempel  gespeichert werden!!!!*/

    GetSystemOperatingTime(&tBufferData[tPara.ucWrTelPosSearch].Tel.ulTimeInMsec); // get system time


    tPara.ucBCR &= ~cWRITE_MODE;                /* Schreibzugriff zurücksetzen */

    if (tPara.ucWrTelPosSearch == tPara.ucWrTelPos)   /* Gefundene Schreibposition = aktuelle Schreibposition */
    {
      PosWrPointerRB(1);                 /* Schreibposition inkrementieren */
    }

    if (tPara.ucWrTelPos == tPara.ucRdTelPos)         /* Puffer ist leer oder läuft über */
    {   /* Telegramm wurde noch nicht gesendet => Überlauf */
      tPara.ucOrCt++;                          /* Überlaufzähler hochzählen */
      if (tPara.ucBCR & cOVERWRITE_MODE)       /* Überschreibmode ist aktiv */
      {
        if (tPara.ucBCR & cREAD_ACCESS_ACTIVE) /* Lesezugriff auf der selben Pufferstelle => Schreibschutz */
        {
          tPara.bBufferOverrun = 1;
          PosWrPointerRB(-1);
        }
        else                             /* Telegramm überschreiben */
        {
          PosRdPointerRB(1);
        }
      }
      else   /* Normal Mode: Schreibzugriff gesperrt. Beim nächsten Lesezugriff tPara.bBufferOverrun-Bit zurücksetzen*/
      {
        tPara.bBufferOverrun = 1;
        PosWrPointerRB(-1);
      }
    }
    // TP0 (0);
  }
  else        /* Kein Schreibzugriff erlaubt bis nächstes Telegramm gelesen wurde */
  {
    tPara.ucOrCt++;
  }
}




/************************************************************************************************************
* Function:          uint8 GetBufferStateRB(void)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Berechnet die Anzahl von Telegrammen im Ringpuffer und speichert diese im aktuellen
*                    Telegramm.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         none
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/
uint8 GetBufferStateRB(void)
{
  uint8 tmp;

#ifdef TestTPx
  TP0(0); /*TEST: set Test Pin0 TP0 to L at CPU Port9_0  CPUpin 45 */
#endif
  if(tPara.ucWrTelPos>=tPara.ucRdTelPos)
  {
    /*return (tPara.ucWrTelPos-tPara.ucRdTelPos);*/
    tmp=(tPara.ucWrTelPos-tPara.ucRdTelPos);
  }
  else
  {
    /*return (cBUFFER_SIZE-tPara.ucRdTelPos+tPara.ucWrTelPos);*/
    tmp=(cBUFFER_SIZE-tPara.ucRdTelPos+tPara.ucWrTelPos);
  }


  return tmp;
}


/************************************************************************************************************
* Function:          void SetBitBufferConditionRegisterRB(uint8 ucBitMask)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Interfacefunktion für die Variable tPara.ucBCR.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         uint8 ucBitMask - Bitmaske
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/
void SetBitBufferConditionRegisterRB(uint8 ucBitMask)
{
  tPara.ucBCR|=ucBitMask;
}






/************************************************************************************************************
* Function:          void ClearBitBufferConditionRegisterRB(uint8 ucBitMask)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Interfacefunktion für die Variable tPara.ucBCR.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         uint8 ucBitMask - Bitmaske
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/
void ClearBitBufferConditionRegisterRB(uint8 ucBitMask)
{
  tPara.ucBCR&=~ucBitMask;
}


/************************************************************************************************************
*                                            interface functions
************************************************************************************************************/
/************************************************************************************************************
* Function:          void ConfigRingBufferCC(void)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Konfiguriert Ringpuffer mit Übergabeparametern von CPU.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:                     ucConfRBuf = MSB 0 X X X X X X LSB
| | | | | | |
1 = Nur HF-Telegramme in Mode2 speichern-----' | | | | | |
| | | | |
' | | | |
' | | |
' | |
1 = Speicherung fehlerhafter Telegramme erlauben-------' |
1 = Überschreibmodus, wenn Puffer voll-------------------'

*
* Input (global):    none
*
* Output (global):   none
*
* Return:            none
*
************************************************************************************************************/

void ConfigRingBufferCC(uint8 ucConfRBuf)
{
  if ((uint8) 0 == ucConfRBuf)
  {
    ucConfRBuf = cDefConfRBuf; /* configure per default */
  }

  /* "Buffer Over Write"-Mode aktivieren? */
  if((ucConfRBuf & 0x01))
  {
    SetBitBufferConditionRegisterRB(cOVERWRITE_MODE);
  }
  else
  {
    ClearBitBufferConditionRegisterRB(cOVERWRITE_MODE);
  }

  /* Speicherung von fehlerhaften Telegrammen zulassen? */
  if((ucConfRBuf & 0x02))
  {
    SetBitBufferConditionRegisterRB(cSAVE_ERROR_TEL);
  }
  else
  {
    ClearBitBufferConditionRegisterRB(cSAVE_ERROR_TEL);
  }

  /* Nur Telegramm in Mode 2 speichern? */
  if((ucConfRBuf & 0x80))
  {
    SetBitBufferConditionRegisterRB(cSAVE_MODE2_ONLY);
  }
  else
  {
    ClearBitBufferConditionRegisterRB(cSAVE_MODE2_ONLY);
  }
}


/************************************************************************************************************
* Function:          void ChkAtaRecive(void)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Prüft den Atmel HF Empfänger Interrupt auf Empfangsereignisse 
*                    Hollt die Telegramm ab und legt diese im Ringpuffer ab.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         none
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            Telegrammzähler ui8TelCt
*
************************************************************************************************************/

void ChkAtaRecive(void)
{
  uint8 ui8MessageLen;
  uint8 ui8Polynom = 0x2F;
  uint8 ui8CrcStartValue = 0xAA;
  uint8 ui8BitsInFirstByte = 8U;
#ifdef RFChipTest_Instrument
  static uint8 ui8ReIniAfterXTels = 0;
#endif

  csig0_4ATAinit();
  rf_ata5785_get_events( rf.events );

  if (   ((rf.events[3]&rf.channel) == rf.channel)   && 
         (((rf.events[1]&0x07) == 0x07) || ((rf.events[1]&0x70) == 0x70))    
#ifdef RFChipTest_Instrument
      && !(ui8ReIniAfterXTels++ == 30)     
#endif
         )  // cfg = activated one && OK events on path B or A
  {
    rf_ata5785_read_rx_buf( rf.buffer, &(rf.level) );
    rf_ata5785_read_rssi_buf( rf.rssibuf, &(rf.rssilvl) );
    ui8TelCt++;

    if(rf.level > 3)
    {
      ui8MessageLen = ui8GetLenOfTelType(rf.buffer [0]);

      if(appBuild8CRC(rf. buffer, ui8MessageLen-1, ui8BitsInFirstByte, ui8Polynom, ui8CrcStartValue) != rf.buffer[ui8MessageLen-1])
      {
        ucCrcFailedTel++;
        if (ui8RepairMessage((struct rfstruct *) &rf , ui8MessageLen) > 0)
        {
          rf.buffer [0] = (uint8) 0;    // repaired message is treated as AK def tel type allways for only ID,p and T is validated
          rf.level = (uint8) 8;         // has len of AKdef per def
          ui8RepairCnt++;
          PutRB((struct rfstruct *) &rf);
        }
      }
      else
      {
        PutRB((struct rfstruct *) &rf);
        ucCrcPassedTel++;
      }
    }
    else
    {
      ucCrcFailedTel++;
    }

    //uiErrorCNT = (uint8) 0;

    SetServNPath(rf.channel);
  }
  else 
  {
    if ((rf.events[0] & 0x80)     // sys error ?
#ifdef  RFChipTest_Instrument
      || (0 < ui8ReIniAfterXTels) // emulated syserror
#endif
      )
    {
#ifdef RFChipTest_Instrument
      ui8ReIniAfterXTels = 0;
#endif
      if(uiErrorCNT<0xFF)
      {
        uiErrorCNT++;
      }
      ReInitAfterError(); // OIL #642 receiver chip MCU RAM config content might be corrupted - so better init anew
    }
    else
    {
      SetServNPath(rf.channel);
    }
  }
}






/************************************************************************************************************
* Function:          uint8 ChkAtaError(void)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           check ATA errors and make error handling
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         none
*
* Input (global):    uiErrorCNT
*
* Output (global):   none
*
* Return:            0x00: everthing is fine
*
************************************************************************************************************/

uint8 ChkAtaError(void)
{
  uint8 ret = cATAok;

  if ( uiErrorCNT > cCountsOfErr)   /* makes it tolerant  */
  {
    ////Spi_Init(SpiDriver); /*@RENESAS BSW F1L out of order */
    //csig0_4ATAinit();
    //
    ///* be aware of PWRON is set when changing operation mode. This could launch SYS_ERR */
    //rf_ata5785_set_mode( (rf.mode & 0xFC), rf.channel ); /* only at idle mode SRAM and register are readable */
    ////ucErrorCode = rf_ata5785_read_error_code();
    ////ucSMState = rf_ata5785_read_SM_state();
    //rf_ata5785_set_mode( rf.mode, rf.channel ); /* back to receive mode */

    //csig0_disable(); /* without disable SPI*/
    ////Spi_Cancel(SPI_ZERO); /*@RENESAS BSW F1L out of order*/

    uiErrorCNT = (uint8) 0; /* reset CNT to make RET once */
    ret = cATAhasError;
  }
  
  return ret;
}








/************************************************************************************************************
* Function:          void GetRB(uint8 * pDataOut)
*
*
* Typ:               public
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           Liefert nächtest Telegramm im Ringpuffer. Über das Konstanten-Array caucOutputMapping[]
*                    wird festgelegt, welche Daten über den Datenzeiger pDataOut zurückgegeben werden.
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         Ausgabepuffer strucktur AK35Tel.ucType ...
*
* Input (global):    none
*
* Output (global):   none
*
* Return:            nonevoid GetRB( tRecRFTelType (* pDataOut))
*
************************************************************************************************************/
void RestartAtaRec(uint8 ucPathNServNr)
{

  //Spi_Init(SPI_ZERO); /*@RENESAS BSW F1L out of order */
  csig0_4ATAinit();
  WaitHard(1000); /*ATA4MFA RH850 1ms*/
  rf_ata5785_get_events(rf.events);
  WaitHard(1000); /*ATA4MFA RH850 1ms*/
  rf.mode = 0x00; // set idele mode
  rf.channel = 0x00;
  rf_ata5785_set_mode( rf.mode, rf.channel );
  WaitHard(2000); /*ATA4MFA RH850 2ms*/
  //Spi_Cancel(SPI_ZERO); /*@RENESAS BSW F1L out of order */
  //csig0_disable(); /* disable SPI*/
  SetServNPath(ucPathNServNr);
}
/*!***********************************************************************************************
* Computes the ATM8 CRC 8-bit checksum for a specified messages 
*
* \Param   - UINT8 pui8buffer - the byte buffer
*          - UINT8 ui8MessageLen - the total number of bytes on which the CRC will be performed
*          - UINT8 ui8BitsInFirstByte how many bits have to be handled from first byte (if 8 than we are aligned)
*          - UINT8 ui8Polynom - desired polynom to calculate 
*          - UINT8 ui8CrcStartValue - Start value for CRC
*
* \Return        - ui8CRC - the 1 byte CRC checksum of the message
*                  
* \Note          - Be careful Buffer must be bigger than lenght
*
***************************************************************************************************/
uint8 appBuild8CRC(const uint8 *pui8Buffer, uint8 ui8MessageLen, uint8 ui8BitsInFirstByte, uint8 ui8Polynom, uint8 ui8CrcStartValue)
{
  /* init the register with zero  (mandatory to be zero)*/
  uint8 ui8CRC = ui8CrcStartValue;

  if ( 0 == ui8MessageLen ) // parameter check
  {
    return ( ui8CRC );
  }

  do
  {
    uint8 ui8BitNumber = 0x00U;
    uint8 byteContent = ( pui8Buffer[0] << ( 8 - ui8BitsInFirstByte ) );

    if( 1U < ui8MessageLen )
    {/*not last byte*/
      byteContent |= ( pui8Buffer[1] >> ( ui8BitsInFirstByte ) );
      ui8BitNumber = 8U;
    }
    else
    {/*last byte*/
      ui8BitNumber = ui8BitsInFirstByte;
    }

    /* bring the next byte into the remainder and XOR it with the CRC */
    ui8CRC ^= byteContent;
    do
    {
      if( 0 != ( ( 0x80U ) & ( ui8CRC ) ) )
      {
        ui8CRC = (uint8) ( ( ui8CRC << 1U ) ^ ( ui8Polynom ) );
      }
      else
      {
        ui8CRC = (uint8) ( ( ui8CRC << 1U ) );
      }
      ui8BitNumber--;
    }while( 0 != ui8BitNumber );

    /*go to next element*/
    pui8Buffer++;
    ui8MessageLen--;
  }while( 0 != ui8MessageLen );

  return ( ui8CRC );

}

static uint8 ui8RepairMessage(struct rfstruct * p2Tel, uint8 ui8TeLen)
{
  const uint8 ui8MinLen = 7;
  const uint8 ui8MaxLen = 13;

  uint8 i,j;

  if (ui8TeLen < ui8MinLen)
    return ((uint8) 0);
  else if (ui8TeLen > ui8MaxLen )
    return ((uint8) 0);  // TODO: pb we might have >1 tel in rf buffer...process also 2nd telegram
  else
  {  // potential candidate 2 repair
    for ( i = 0; i < cBUFFER_SIZE ; i++)  // we search all the slots also the consumed ones
    {
      for (j = 1 ; j < ui8MinLen; j++)
      {
        if ( p2Tel -> buffer[j] != tBufferData [i].Tel .ucByte [j])
          break;
      }

      if (ui8MinLen == j)
        return ((uint8) 0xFF);
    }
  }

  return ((uint8) 0);  //failed
}

uint8 ui8GetComptoirRepare(void)
{
  return (ui8RepairCnt );
}

static uint8 ui8GetLenOfTelType(uint8 ui8TelType)
{
  uint8 ui8Ret = (rf.level>RB_DATA_LEN) ? RB_DATA_LEN:rf.level;

  switch (ui8TelType)
  {
  case 0:
  case 1:
  case 0x20:
    ui8Ret = (uint8) 8;
    break;
  case 0x03:
  case 0x23:
    ui8Ret = (uint8) 11;
    break;
  default:
    break;
  }

  return (ui8Ret);
}


/************************************************************************************************************
* Function:          uint8 ui8GetErrorCnt(void)
*
*
* Typ:               Interface
*
* ----------------------------------------------------------------------------------------------------------
*
* Purpose:           return consecutive counts of ATA errors
*
* ----------------------------------------------------------------------------------------------------------
*
* Parameter:         none
*
* Input (global):    uiErrorCNT
*
* Output (global):   none
*
* Return:            uiErrorCNT
*
************************************************************************************************************/
uint8 ui8GetErrorCnt(void)
{
  return uiErrorCNT;
}

void PutErrorCnt(uint8 x)
{
  uiErrorCNT = x;
}

// InitRFTelBufferW0x55ForWhatSoEver purpose:
// TBD some kind of great mud
void InitRFTelBufferW0x55ForWhatSoEver(void)
{
  uint8 i;
  for(i=0; i<sizeof(tRecRFTelData); i++) /* for Transmit to CAN */
  {
    tRecRFTel.ucByteAccess[i] = 0x55;
  }
}
/************************************************************************************************************
*                                            Private Functions
************************************************************************************************************/


