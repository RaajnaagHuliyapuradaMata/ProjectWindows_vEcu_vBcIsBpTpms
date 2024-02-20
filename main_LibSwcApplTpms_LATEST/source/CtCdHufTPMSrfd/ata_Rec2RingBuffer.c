

#include "Platform_Types.h"
#include "Spi.h"
#include "ata_Rec2RingBuffer_X.h"
#include "Rte_CtCdHufTPMSrfd.h"
#include "internal_clockX.h"
#include "CtCdHufTPMSrfd.h"

extern void csig0_4ATAinit(void);
extern DT_auRfStruct aucRfStruct;
 #define cMODE1_TEL   (uint8) 0x01
#define cDefConfRBuf (uint8) 0x00

#define cATAok       (uint8) 0x00
#define cATAhasError (uint8) 0xFF
#define cCountsOfErr (uint8) 0x64

uint8 ui8TelCt = 0;
 static uint8 uiErrorCNT = 0;
uint8 ucCrcPassedTel;
 uint8 ucCrcFailedTel;

static union ringbuffer tBufferData[cBUFFER_SIZE];

struct para{
  uint8 ucBCR;
  uint8 ucWrTelPos;
  uint8 ucRdTelPos;
  uint8 ucWrTelPosSearch;
  uint8 ucWrError;
  uint8 ucOrCt;
  uint8 bBufferOverrun;
};

static struct para tPara;

static uint8 ui8RepairCnt = (uint8) 0;

uint8 appBuild8CRC(const uint8 *pui8Buffer, uint8 ui8MessageLen, uint8 ui8BitsInFirstByte, uint8 ui8Polynom, uint8 ui8CrcStartValue);

static void PosWrPointerRB(signed char);
static void PosRdPointerRB(signed char);

static uint8 ui8RepairMessage(struct rfstruct * p2Tel, uint8 ui8TeLen);
static uint8 ui8GetLenOfTelType(uint8 ui8TelType);

static void PosWrPointerRB(signed char cIncDec)
{
  tPara.ucWrTelPos += cIncDec;
  if ( (cIncDec>=0) && (tPara.ucWrTelPos >= cBUFFER_SIZE) )
  {
    tPara.ucWrTelPos = 0;
  }
  else if(tPara.ucWrTelPos>=cBUFFER_SIZE)
  {
    tPara.ucWrTelPos = cBUFFER_SIZE - 1;
  }
}

static void PosRdPointerRB(signed char cIncDec)
{

  tPara.ucBCR &= ~cMODE2_TEL_IN_BUFFER;

  tPara.ucRdTelPos += cIncDec;

  if ( (cIncDec >= 0) && (tPara.ucRdTelPos >= cBUFFER_SIZE) )
  {
    tPara.ucRdTelPos = 0;
  }
  else if (tPara.ucRdTelPos>=cBUFFER_SIZE)
  {
    tPara.ucRdTelPos = cBUFFER_SIZE - 1;
  }
}

uint8 StartAtaRec(uint8 ucPathNServNr)
{
  uint8 i;
  uint8 ucAtaInitSate=TRUE;

  if( rf_ata5785_init() == TRUE )
  {

    SetServNPath(ucPathNServNr);
    for(i=0; i<sizeof(tRecRFTelData); i++)
    {
      tRecRFTel.ucByteAccess[i] = 0x55;
    }
  }
  else
  {
    ucAtaInitSate=FALSE;
  }

  return ucAtaInitSate;
}

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

void GetRB( void)
{
  uint8 i;

  tPara.ucBCR |= cREAD_ACCESS_ACTIVE;
  tRecRFTel.AK35Data.ulTime=  tBufferData[tPara.ucRdTelPos].Tel .ulTimeInMsec;
#ifdef V24_64F1L
  WordIn4AsciiBytesToV24(tBufferData[tPara.ucRdTelPos].Tel .ushTimeInMsec);
#endif
   tRecRFTel.AK35Data.ucNoise = tBufferData[tPara.ucRdTelPos].Tel.ucRssiNoise;
#ifdef V24_64F1L
  RLIN30_send_byte(0x20);
  ByteIn2AsciiToV24(tBufferData[tPara.ucRdTelPos].Tel.ucRssi[0]);
  RLIN30_send_byte(0x20);
#endif

  for(i=0; i<(uint8) (RB_DATA_LEN); i++)
   {

    tRecRFTel.AK35Data.aucTel[i] = tBufferData[tPara.ucRdTelPos].Tel.ucByte[i];
#ifdef V24_64F1L
    if(i==1)
      RLIN30_send_byte(0x20);
    if(i==5)
      RLIN30_send_byte(0x20);
    ByteIn2AsciiToV24(tBufferData[tPara.ucRdTelPos].Tel.ucByte[i]);
#endif

  }
  for(i=0; i<(uint8) (RB_RS_BUF_LEN); i++)
   {

    tRecRFTel.AK35Data.aucTel[RB_DATA_LEN +i ] = tBufferData[tPara.ucRdTelPos].Tel.ucRssi[i];
#ifdef V24_64F1L
    RLIN30_send_byte(0x20);
    ByteIn2AsciiToV24(tBufferData[tPara.ucRdTelPos].Tel.ucByte[i]);
#endif
  }

  PosRdPointerRB(1);
  if(tPara.bBufferOverrun)
  {
    PosWrPointerRB(1);
    tPara.bBufferOverrun=0;
  }

  for(i=0; i<sizeof(aucRfStruct); i++)
   {
    aucRfStruct[i] = tRecRFTel.ucByteAccess[i];
  }
  tPara.ucBCR&=~cREAD_ACCESS_ACTIVE;
}

void PutRB(struct rfstruct * tRfBuf)
{
  uint8 i,ucTop;

  if (tPara.bBufferOverrun == 0)
  {
    tPara.ucBCR |= cWRITE_MODE;

    tPara.ucWrTelPosSearch = tPara.ucWrTelPos;

    ucTop = (tRfBuf->level>RB_DATA_LEN) ? RB_DATA_LEN:tRfBuf->level;
    for (i=0; i<ucTop ; i++)
      {
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucByte[i] = tRfBuf->buffer[i];
    }
    for (i=ucTop; i<(uint8) RB_DATA_LEN ; i++)
     {
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucByte[i] = 0;
    }
    for (i=0; i<((tRfBuf->rssilvl>RB_RS_BUF_LEN) ? RB_RS_BUF_LEN:tRfBuf->rssilvl ); i++)
     {
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssi[i] = tRfBuf->rssibuf[tRfBuf->rssilvl - i - 1];
    }
    tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssiNoise = tRfBuf->rssibuf[0];

    for (i=((tRfBuf->rssilvl>RB_RS_BUF_LEN) ? RB_RS_BUF_LEN:tRfBuf->rssilvl) ; i<(uint8) RB_RS_BUF_LEN ; i++)
     {
      tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssi[i] = 0;
    }
    tBufferData[tPara.ucWrTelPosSearch].Tel.ucByte[RB_DATA_LEN-1] = tRfBuf->level;
    tBufferData[tPara.ucWrTelPosSearch].Tel.ucRssi[RB_RS_BUF_LEN -1] = tRfBuf->rssilvl;

    GetSystemOperatingTime(&tBufferData[tPara.ucWrTelPosSearch].Tel.ulTimeInMsec);

    tPara.ucBCR &= ~cWRITE_MODE;

    if (tPara.ucWrTelPosSearch == tPara.ucWrTelPos)
    {
      PosWrPointerRB(1);
    }

    if (tPara.ucWrTelPos == tPara.ucRdTelPos)
    {
      tPara.ucOrCt++;
      if (tPara.ucBCR & cOVERWRITE_MODE)
      {
        if (tPara.ucBCR & cREAD_ACCESS_ACTIVE)
        {
          tPara.bBufferOverrun = 1;
          PosWrPointerRB(-1);
        }
        else
        {
          PosRdPointerRB(1);
        }
      }
      else
      {
        tPara.bBufferOverrun = 1;
        PosWrPointerRB(-1);
      }
    }
  }
  else
  {
    tPara.ucOrCt++;
  }
}

uint8 GetBufferStateRB(void)
{
  uint8 tmp;

#ifdef TestTPx
  TP0(0);
#endif
  if(tPara.ucWrTelPos>=tPara.ucRdTelPos)
  {

    tmp=(tPara.ucWrTelPos-tPara.ucRdTelPos);
  }
  else
  {

    tmp=(cBUFFER_SIZE-tPara.ucRdTelPos+tPara.ucWrTelPos);
  }

  return tmp;
}

void SetBitBufferConditionRegisterRB(uint8 ucBitMask)
{
  tPara.ucBCR|=ucBitMask;
}

void ClearBitBufferConditionRegisterRB(uint8 ucBitMask)
{
  tPara.ucBCR&=~ucBitMask;
}

void ConfigRingBufferCC(uint8 ucConfRBuf)
{
  if ((uint8) 0 == ucConfRBuf)
  {
    ucConfRBuf = cDefConfRBuf;
  }

  if((ucConfRBuf & 0x01))
  {
    SetBitBufferConditionRegisterRB(cOVERWRITE_MODE);
  }
  else
  {
    ClearBitBufferConditionRegisterRB(cOVERWRITE_MODE);
  }

  if((ucConfRBuf & 0x02))
  {
    SetBitBufferConditionRegisterRB(cSAVE_ERROR_TEL);
  }
  else
  {
    ClearBitBufferConditionRegisterRB(cSAVE_ERROR_TEL);
  }

  if((ucConfRBuf & 0x80))
  {
    SetBitBufferConditionRegisterRB(cSAVE_MODE2_ONLY);
  }
  else
  {
    ClearBitBufferConditionRegisterRB(cSAVE_MODE2_ONLY);
  }
}

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
         )
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
          rf.buffer [0] = (uint8) 0;
           rf.level = (uint8) 8;
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

    SetServNPath(rf.channel);
  }
  else
  {
    if ((rf.events[0] & 0x80)
 #ifdef  RFChipTest_Instrument
      || (0 < ui8ReIniAfterXTels)
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
      ReInitAfterError();
     }
    else
    {
      SetServNPath(rf.channel);
    }
  }
}

uint8 ChkAtaError(void)
{
  uint8 ret = cATAok;

  if ( uiErrorCNT > cCountsOfErr)
  {

    uiErrorCNT = (uint8) 0;
    ret = cATAhasError;
  }

  return ret;
}

void RestartAtaRec(uint8 ucPathNServNr)
{
   csig0_4ATAinit();
  WaitHard(1000);
  rf_ata5785_get_events(rf.events);
  WaitHard(1000);
  rf.mode = 0x00;
   rf.channel = 0x00;
  rf_ata5785_set_mode( rf.mode, rf.channel );
  WaitHard(2000);
   SetServNPath(ucPathNServNr);
}

uint8 appBuild8CRC(const uint8 *pui8Buffer, uint8 ui8MessageLen, uint8 ui8BitsInFirstByte, uint8 ui8Polynom, uint8 ui8CrcStartValue)
{

  uint8 ui8CRC = ui8CrcStartValue;

  if ( 0 == ui8MessageLen )
   {
    return ( ui8CRC );
  }

  do
  {
    uint8 ui8BitNumber = 0x00U;
    uint8 byteContent = ( pui8Buffer[0] << ( 8 - ui8BitsInFirstByte ) );

    if( 1U < ui8MessageLen )
    {
      byteContent |= ( pui8Buffer[1] >> ( ui8BitsInFirstByte ) );
      ui8BitNumber = 8U;
    }
    else
    {
      ui8BitNumber = ui8BitsInFirstByte;
    }

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
    return ((uint8) 0);
   else
  {
     for ( i = 0; i < cBUFFER_SIZE ; i++)
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

  return ((uint8) 0);
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

uint8 ui8GetErrorCnt(void)
{
  return uiErrorCNT;
}

void PutErrorCnt(uint8 x)
{
  uiErrorCNT = x;
}

 void InitRFTelBufferW0x55ForWhatSoEver(void)
{
  uint8 i;
  for(i=0; i<sizeof(tRecRFTelData); i++)
  {
    tRecRFTel.ucByteAccess[i] = 0x55;
  }
}

