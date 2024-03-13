

#include "Platform_Types.h"
#include "Spi.h"
#include "CtCdHufTPMSrfd.h"

#include "ata_dev_5785.h"
#include "ata5785_sram.h"
#include "ata_Rec2RingBuffer.h"

#include "RH850F1L_dvf.h"

static void rf_ata5785_system_reset( void ) ;
uint8 active_xfer_spi(uint8 ucByteValue);
 static void ataIni1st(void);
static void ataIniPwrOn(void);
static void ataInitSysRes(void);
static void ataIniWtResetEvent(void);
static void ataIniSeq1(void);
static void ataIniSeq2(void);
static void ataIniSeq3(void);
static void ataIniSeq4(void);
static void ataIniSeq5(void);
static void ataIniSeq6(void);
static void ataIniStartService(void);
static void ataInitialized(void);

uint8 ucMISOdata[4];

struct rfstruct  rf;
 uint8 rf_tempMeas_cfg[] = {
   0x02,
    0xC3,
    0x01,
    0x4B
 };
 uint8 rf_sysConf_rd[] = {
   0x02,
    0xE5,
    0x01,
   0x0c
 };

static void (*fp2IniState) (void) = ataIni1st;

static void select_ata5785(void){
    RFD_CsAta(1);
    WaitHard(47);
}

static void release_ata5785(void){
    WaitHard(36);
   RFD_CsAta(0);
    WaitHard(17);
}

void WaitHard(uint32 ulTicks){
    ulTicks=(ulTicks*12);
    while(ulTicks !=0){
     ulTicks--;
   }

}

void rf_ata5785_deinit(void){
  MKP11 = H;

  RFD_CsAta(0);
  csig0_disable();

  RFD_Pwr3Pin4Ata(0);
  fp2IniState = ataIni1st ;
}

uint8 rf_ata5785_init(void){
    uint8 i;
    uint16 ushTO = 10000;

    RFD_Pwr3Pin4Ata(0);
    WaitHard(10000);
    rf.rom = 0;
    rf.level = 0;
    rf.rssilvl = 0;
    rf.mode = 0;
    rf.channel = 0;
    rf.events[0] = 0;
    rf.events[1] = 0;
    rf.events[2] = 0;
    rf.events[3] = 0;
    for(i=0; i<RF_DAT_BUF_LEN; i++){
        rf.buffer[i] = 0;
        rf.rssibuf[i] = 0;
    }

    csig0_4ATAinit();
    RFD_Pwr3Pin4Ata(1);
    WaitHard(5000);
   ucIRQ_ATA_activ=0;

      rf_ata5785_system_reset();

    MKP11 = L;

    while((ucIRQ_ATA_activ!=1) && (ushTO--));

   if(ushTO != 0xFFFF){
    ucIRQ_ATA_activ=0;

    /* 2 Fkt im TransRaLF*/
    rf_ata5785_get_events( rf.events );
    rf.rom = rf_ata5785_read_version();
     rf_ata5785_write_sram(rf_idCtrl_cfg);
    rf_ata5785_write_sram(rf_events_cfg);
    rf_ata5785_set_watchdog(rf_watchdog_cfg);
    rf_ata5785_write_sram(rf_dbgsw_cfg);
    rf_ata5785_write_sram(rf_PORTB_cfg);
    rf_ata5785_write_sram(rf_DDRB_cfg);
    rf_ata5785_write_sram(rf_PORTC_cfg);
    rf_ata5785_write_sram(rf_DDRC_cfg);
    rf_ata5785_write_sram(rf_PCMSK0_cfg);
    rf_ata5785_write_sram(rf_PCMSK1_cfg);
    rf_ata5785_write_sram(rf_PCICR_cfg);
    rf_ata5785_write_sram(rf_MCUCR_cfg);
    rf_ata5785_write_sram(rf_temperatureCalibration_cfg);
    rf_ata5785_write_sram(rf_trxCalibConfiguration_cfg);
    rf_ata5785_write_sram(rf_sleepModeConfig_cfg);
    rf_ata5785_write_sram(rf_frcCalibrationConfiguration_cfg);
    rf_ata5785_write_sram(rf_pollConfig_cfg);
    rf_ata5785_write_sram(rf_calib_srcRes_cfg);
    rf_ata5785_write_sram(rf_calib_srcCorVal_cfg);
    rf_ata5785_write_sram(rf_sramService3_cfg);
    rf_ata5785_write_sram(rf_sramService4_cfg);
    rf_ata5785_write_sram(rf_gapMode_cfg);
    rf_ata5785_write_sram(rf_eomConfig_cfg);
    rf_ata5785_write_sram(rf_tempMeas_cfg);
    rf_ata5785_write_sram(rf_sysConf_rd);
     rf_ata5785_write_sram(rf_disableClock_cfg);
    rf_ata5785_write_sram(rf_setClockDivider_cfg);
    rf_ata5785_write_sram(rf_reenableClock_cfg);

    /* 2 Fkt im ATMEL EVAL Board!*/
      rf.mode = 0x00;
    rf.channel = 0x00;
    rf_ata5785_set_mode( rf.mode, rf.channel );
    WaitHard(5000); /*RH850 5ms ATA4MFA*/
    rf_ata5785_get_events( rf.events );
     /*rf.mode = 0x23;
    rf.channel = 0x00;
    rf_ata5785_set_mode( rf.mode, rf.channel );     WaitHard(5000);
    rf_ata5785_get_events( rf.events ); */

#ifdef MCAL_F1L
    Spi_Cancel(SPI_ZERO); /*@RENESAS BSW F1L out of order */
#else
    csig0_disable(); /* disable SPI*/
#endif
    return TRUE;  /*CR_1211_150_021*/

  }
   else{

#ifdef MCAL_F1L
    Spi_Cancel(SPI_ZERO); /*@RENESAS BSW F1L out of order */
#else
    csig0_disable(); /* disable SPI*/
#endif

    return FALSE;  /*CR_1211_150_021*/

  }

}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_version
* Description :     Read firmware version information
* Arguments :       none
* Return Value :    firmware version
***********************************************************************************************************************/
uint8 rf_ata5785_read_version( void ){
   uint8 rtn=FALSE;

   select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr=0x13;
   Spi_WriteIB(0, (uint8 *) &ptr);
    Spi_AsyncTransmit(0);
   ptr=Spi_GetHWUnitStatus(0);
   Spi_ReadIB(0, (uint8 *) &ptr);

   ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr);
    rtn = Spi_WriteIB(0, (uint8 *) &ptr);
    Spi_WriteIB(0, (uint8 *) &ptr);
    Spi_WriteIB(0, (uint8 *) &ptr);
    Spi_WriteIB(0, (uint8 *) &ptr);

#else  /*MCAL_F1L*/
  active_xfer_spi( 0x13 );
   active_xfer_spi( 0x00 );
    rtn = active_xfer_spi( 0x00 );
    active_xfer_spi( 0x00 );
    active_xfer_spi( 0x00 );
    active_xfer_spi( 0x00 );

#endif /*MCAL_F1L*/
    release_ata5785();

   return rtn;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_get_events
* Description :     Read and clear event bytes
* Arguments :       buffer pointer
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_get_events( uint8 buf[] ){
   uint8 ptr;
   select_ata5785();
#ifdef MCAL_F1L
   ptr=0x04;
   buf[0] = Spi_WriteIB(0, (uint8 *) &ptr);
    ptr=0x00;
   buf[1] = Spi_WriteIB(0, (uint8 *) &ptr);
    buf[2] = Spi_WriteIB(0, (uint8 *) &ptr);
    buf[3] = Spi_WriteIB(0, (uint8 *) &ptr);

#else  /*MCAL_F1L*/
   ptr=0x04;
   buf[0] = active_xfer_spi(ptr);
   ptr=0x00;
   buf[1] = active_xfer_spi(ptr);
   buf[2] = active_xfer_spi(ptr);
   buf[3] = active_xfer_spi(ptr);

#endif
   release_ata5785();

   return;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_set_mode
* Description :     set operating mode
* Arguments :       mode and channel
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_set_mode( uint8 mode, uint8 channel ){
   select_ata5785();
#ifdef MCAL_F1L
   uint8 ptr;

  ptr=0x0D; /*events.system*/
   Spi_WriteIB( 0, (uint8 *) &ptr );

   Spi_WriteIB(0, (uint8 *) &mode );

   Spi_WriteIB( 0, (uint8 *) &channel );

#else
   active_xfer_spi( 0x0D );
    active_xfer_spi( mode );
    active_xfer_spi( channel );

#endif
   release_ata5785();

   return;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rx_level
* Description :     Read rx buffer level
* Arguments :       none
* Return Value :    rx buffer level
***********************************************************************************************************************/
uint8 rf_ata5785_read_rx_level( void ){
uint8 rtn;
   select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

   ptr=0x01;
   Spi_WriteIB(0, (uint8 *) &ptr);
   ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr);
   rtn=Spi_WriteIB(0, (uint8 *) &ptr);
#else
   active_xfer_spi( 0x01 );
    active_xfer_spi( 0x00 );
    rtn = active_xfer_spi( 0x00 );
 #endif
   release_ata5785();

   return rtn;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rssi_level
* Description :     Read rssi buffer level
* Arguments :       none
* Return Value :    rssi buffer level
***********************************************************************************************************************/
uint8 rf_ata5785_read_rssi_level( void ){
uint8 rtn;
    select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

   ptr=0x03;
   Spi_WriteIB(0, (uint8 *) &ptr); /* 0x03*/
   ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr );   /* 0x00*/
   rtn = Spi_WriteIB(0, (uint8 *) &ptr );   /* 0x00*/
#else
   active_xfer_spi( 0x03 );
    active_xfer_spi( 0x00 );
    rtn = active_xfer_spi( 0x00 );
 #endif
   release_ata5785();

   return rtn;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rx_buf
* Description :     Read rx buffer
* Arguments :       buffer pointer and length
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_read_rx_buf( uint8 buf[], uint8 *len ){
uint8 i;
    select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

   ptr=0x01;
   Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr );
    *len = Spi_WriteIB(0, (uint8 *) &ptr );
    release_ata5785();

   select_ata5785();
   ptr=0x06;
   Spi_WriteIB(0, (uint8 *) &ptr );
    Spi_WriteIB(0,  len );
    ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr );

   for(i=0; i<*len; i++){
      buf[i] = Spi_WriteIB(0, (uint8 *) &ptr );
   }
#else
   active_xfer_spi( 0x01 );
    active_xfer_spi( 0x00 );
    *len = active_xfer_spi( 0x00 );
    release_ata5785();

   select_ata5785();
   active_xfer_spi( 0x06 );
    active_xfer_spi( *len );
    active_xfer_spi( 0x00 );

   for(i=0; i<*len; i++){
      buf[i] = active_xfer_spi( 0x00 );
   }
#endif
   release_ata5785();
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rssi_buf
* Description :     Read rssi buffer
* Arguments :       buffer pointer and length
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_read_rssi_buf( uint8 buf[], uint8 *len ){
uint8 i;
   select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;
   ptr=0x03;
   Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr );
    *len = Spi_WriteIB(0, (uint8 *) &ptr );
    release_ata5785();
    select_ata5785();
   ptr=0x05;
   Spi_WriteIB(0, (uint8 *) &ptr );
    Spi_WriteIB(0, len );
    ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr );
    for(i=0; i<*len; i++){
      buf[i] = Spi_WriteIB(0, (uint8 *) &ptr );
   }

#else
   active_xfer_spi( 0x03 );
    active_xfer_spi( 0x00 );
    *len = active_xfer_spi( 0x00 );
    release_ata5785();
    select_ata5785();
   active_xfer_spi( 0x05 );
    active_xfer_spi( *len );
    active_xfer_spi( 0x00 );
    for(i=0; i<*len; i++){
      buf[i] = active_xfer_spi( 0x00 );
   }

#endif
    release_ata5785();

   return;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_write_tx_buf
* Description :     Write tx buffer
* Arguments :       buffer pointer and length
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_write_tx_buf( uint8 buf[], uint8 len ){
uint8 i;
   select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

   ptr=0x06;
   Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=len;
   Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0x00;
   Spi_WriteIB(0, (uint8 *) &ptr );

   for(i=0; i<len; i++){
      ptr=buf[i];
      Spi_WriteIB(0, (uint8 *) &ptr );
   }
#else
   active_xfer_spi( 0x06 );
    active_xfer_spi( len );
    active_xfer_spi( 0x00 );

   for(i=0; i<len; i++){
      active_xfer_spi( buf[i] );
   }

#endif
    release_ata5785();

   return;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_write_sram
* Description :     Write into sram or register
* Arguments :       buffer pointer
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_write_sram(const uint8 data[]){
  uint8 i;
  uint8 length;
  uint8 offset;
  uint8 ptr;

  union
  {
    uint16   ui;
    uint8  uc[2];
  } addr;

#define SRAM_BUFFER_SIZE 32

  addr.ui = (uint16) data[0];
  addr.ui<<= 8;
  addr.ui += (uint16) data[1];
  length = data[2];
  offset = 3;

  do
  {
    if(length <= SRAM_BUFFER_SIZE){
      select_ata5785();

#ifdef MCAL_F1L
      ptr=0x07;
      Spi_WriteIB(0, (uint8 *) &ptr );
      ptr=length;
      Spi_WriteIB(0, (uint8 *) &ptr );
       ptr=(uint8) (addr.ui>>8);
      Spi_WriteIB(0, (uint8 *) &ptr );
       ptr=(uint8) addr.ui;
      Spi_WriteIB(0, (uint8 *) &ptr );

      for(i=0; i<length; i++){
        ptr=data[i+offset];
        Spi_WriteIB(0, (uint8 *) &ptr );
      }
      release_ata5785();
      length = 0;
    }
    else{
      select_ata5785();
      ptr=0x07;
      Spi_WriteIB(0, (uint8 *) &ptr );
      ptr=SRAM_BUFFER_SIZE;
      Spi_WriteIB(0, (uint8 *) &ptr );
       ptr=(uint8) (addr.ui>>8);
      Spi_WriteIB(0, (uint8 *) &ptr );
       ptr=(uint8) addr.ui;
      Spi_WriteIB(0, (uint8 *) &ptr );
       for(i=0; i<SRAM_BUFFER_SIZE; i++){
        ptr=data[i+offset];
        Spi_WriteIB(0, (uint8 *) &ptr );
      }
      release_ata5785();
      addr.ui += SRAM_BUFFER_SIZE;
      length -= SRAM_BUFFER_SIZE;
      offset += SRAM_BUFFER_SIZE;
    }
#else
      ptr=0x07;
      active_xfer_spi(ptr);
      ptr=length;
      active_xfer_spi(ptr);
       ptr=(uint8) (addr.ui>>8);
      active_xfer_spi(ptr);
       ptr=(uint8) addr.ui;
      active_xfer_spi(ptr);

      for(i=0; i<length; i++){
        ptr=data[i+offset];
        active_xfer_spi(ptr);
      }
      release_ata5785();
      length = 0;
    }
    else{
      select_ata5785();
      ptr=0x07;
      active_xfer_spi(ptr);
      ptr=SRAM_BUFFER_SIZE;
      active_xfer_spi(ptr);
       ptr=(uint8) (addr.ui>>8);
      active_xfer_spi(ptr);
       ptr=(uint8) addr.ui;
      active_xfer_spi(ptr);
       for(i=0; i<SRAM_BUFFER_SIZE; i++){
        ptr=data[i+offset];
        active_xfer_spi(ptr);
      }
      release_ata5785();
      addr.ui += SRAM_BUFFER_SIZE;
      length -= SRAM_BUFFER_SIZE;
      offset += SRAM_BUFFER_SIZE;
    }

#endif

  } while(length > 0);

  return;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_set_watchdog
* Description :     Write tx buffer
* Arguments :       buffer pointer and length
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_set_watchdog(const uint8 data[] ){
uint8 ptr;
   select_ata5785();
#ifdef MCAL_F1L
   ptr=0x10;
   Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=data[0];
   Spi_WriteIB(0, (uint8 *) &ptr );
 #else
   ptr=0x10;
   active_xfer_spi(ptr);
   ptr=data[0];
    active_xfer_spi(ptr);
#endif
   release_ata5785();

   return;
}
#ifdef MCAL_F1L

/***********************************************************************************************************************
* Function Name:    check_sensor_type
* Description :     check for sensor type
* Arguments :       none
* Return Value :    sensor type
***********************************************************************************************************************/
uint8 check_sensor_type(void){
   unsigned int tcount;
   uint8 tmp=0;
    rf.mode = 0xA2;
   rf.channel = 0x83;

   Spi_Init(SPI_ZERO);
   rf_ata5785_set_mode( rf.mode, rf.channel );
    Spi_Cancel(SPI_ZERO); /* @as F1L BSW */
  tcount = 0;
   do
   {
     WaitHard(10000); /*ATA4MFA RH850 10ms*/
    /**********************************************************************************************/
    /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
    /* PORT IRQ*/
   } while (tcount++ < 500);
    Spi_Init(SPI_ZERO);
    rf_ata5785_get_events( rf.events );
    WaitHard(1000);
    rf.mode = 0x00;
   rf.channel = 0x00;
   rf_ata5785_set_mode( rf.mode, rf.channel );
   WaitHard(2000); /*ATA4MFA RH850 2ms*/
    Spi_Cancel(SPI_ZERO);
   if(((rf.events[3]&0x83) == 0x83) && ((rf.events[1]&0x07) == 0x07)) /*return 1;*/
   {
     tmp=1;
   }
   else{
   rf.mode = 0xA2;
   rf.channel = 0x84;

   Spi_Init(SPI_ZERO);
   rf_ata5785_set_mode( rf.mode, rf.channel );
   Spi_Cancel(SPI_ZERO);
   tcount = 0;
   do
   {
      WaitHard(10000); /*ATA4MFA RH850 10ms*/
      /**********************************************************************************************/
       /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
       /* PORT IRQ*/
   } while (tcount++ < 500);
    Spi_Init(SPI_ZERO);
    rf_ata5785_get_events( rf.events );
    WaitHard(1000);
    rf.mode = 0x00;
   rf.channel = 0x00;
   rf_ata5785_set_mode( rf.mode, rf.channel );
   WaitHard(2000);
   Spi_Cancel(SPI_ZERO);
   if(((rf.events[3]&0x84) == 0x84) && ((rf.events[1]&0x07) == 0x07)){
        tmp=2;
     }

   }
   return (tmp);
}

#else
/***********************************************************************************************************************
* Function Name:    check_sensor_type
* Description :     check for sensor type
* Arguments :       none
* Return Value :    sensor type
***********************************************************************************************************************/
uint8 check_sensor_type(void){
   unsigned int tcount;
   uint8 tmp=0;
    rf.mode = 0xA2;
   rf.channel = 0x83;

   csig0_4ATAinit();
   rf_ata5785_set_mode( rf.mode, rf.channel );
    csig0_disable(); /* ATA4StarterKit*/

  tcount = 0;
   do
   {
     WaitHard(10000); /*ATA4MFA RH850 10ms*/
    /**********************************************************************************************/
    /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
    /* PORT IRQ*/
   } while (tcount++ < 500);

   csig0_4ATAinit();
   rf_ata5785_get_events( rf.events );
   WaitHard(1000);
   rf.mode = 0x00;
   rf.channel = 0x00;
   rf_ata5785_set_mode( rf.mode, rf.channel );
   WaitHard(2000);
    csig0_disable(); /* ATA4StarterKit*/
   if(((rf.events[3]&0x83) == 0x83) && ((rf.events[1]&0x07) == 0x07)) /*return 1;*/
   {
     tmp=1;
   }
   else{
   rf.mode = 0xA2;
   rf.channel = 0x84;
    csig0_4ATAinit();
   rf_ata5785_set_mode( rf.mode, rf.channel );
   csig0_disable(); /* ATA4StarterKit*/
   tcount = 0;
   do
   {
      WaitHard(10000);
      /**********************************************************************************************/
       /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
       /* PORT IRQ*/
   } while (tcount++ < 500);
    csig0_4ATAinit();
   rf_ata5785_get_events( rf.events );
   WaitHard(1000);
   rf.mode = 0x00;
   rf.channel = 0x00;
   rf_ata5785_set_mode( rf.mode, rf.channel );
   WaitHard(2000);
   csig0_disable();
     if(((rf.events[3]&0x84) == 0x84) && ((rf.events[1]&0x07) == 0x07))  /* return (2u);*/
     {
        tmp=2;
     }

   }
   return (tmp);
}

#endif

/***********************************************************************************************************************
* Function Name:    rf_ata5785_system_reset
* Description :     rf_ata5785_system_reset
* Arguments :       none
* Return Value :    reset
***********************************************************************************************************************/
static void rf_ata5785_system_reset( void ){
uint8 ptr;

    select_ata5785(); /*CS for ATA and wait 47µs */

#ifdef MCAL_F1L

   if(Spi_GetHWUnitStatus(0)==SPI_IDLE){
   ptr=0x15;
   ucMISOdata[0]=Spi_WriteIB(0, (uint8 *) &ptr );
    Spi_AsyncTransmit(0);

   }

     if(Spi_GetHWUnitStatus(0)==SPI_IDLE){
   ptr=0x00;
   ucMISOdata[1]=Spi_WriteIB(0, (uint8 *) &ptr );
     Spi_AsyncTransmit(0);
   }

#else

   ptr=0x15;
   ucMISOdata[0]=active_xfer_spi( ptr );
    ptr=0x00;
   ucMISOdata[1]=active_xfer_spi( ptr );
 #endif

   ucMISOdata[3]=0x01; /*Transmit 2 V24 in main.c*/
   release_ata5785(); /*i.o. 4  ATA4StarterKit*/

   return;
}
/***********************************************************************************************************************
* Function Name:    SetServNPath
* Description :     SetServNPath
* Arguments :       none
* Return Value :
***********************************************************************************************************************/
void SetServNPath( uint8 ui8SrvNPath ){
#ifdef MCAL_F1L
   Spi_Init(SPI_ZERO);
#else
   csig0_4ATAinit();
#endif

    if(ui8SrvNPath == rf.channel){
        rf.mode = 0x12;
     }
    else{
        rf.mode = 0xB2;
         rf.channel = ui8SrvNPath;
    }

    rf_ata5785_set_mode(rf.mode, rf.channel );
#ifdef MCAL_F1L
   Spi_Cancel(SPI_ZERO); /* @as F1L BSW */
#else
   csig0_disable(); /* ATA4StarterKit*/
#endif

}
/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_error_code
* Description :     rf_ata5785_read_error_code
* Arguments :       none
* Return Value :
***********************************************************************************************************************/
uint8 rf_ata5785_read_error_code( void ){
uint8 rtn;
uint8 ptr;
    select_ata5785();
#ifdef MCAL_F1L

   ptr=0x08;
    Spi_WriteIB(0, (uint8 *) &ptr );
     ptr=0x01;
   Spi_WriteIB(0, (uint8 *) &ptr );
     ptr=0x02;
   Spi_WriteIB(0, (uint8 *) &ptr );
     ptr=0xF4;
   Spi_WriteIB(0, (uint8 *) &ptr );
     ptr=0x00;
   rtn = Spi_WriteIB(0, (uint8 *) &ptr );
 #else

   ptr=0x08;
    active_xfer_spi( ptr );
     ptr=0x01;
   active_xfer_spi( ptr );
     ptr=0x02;
   active_xfer_spi( ptr );
     ptr=0xF4;
   active_xfer_spi( ptr );
     ptr=0x00;
   active_xfer_spi( ptr );
     ptr=0x00;
   rtn = active_xfer_spi( ptr );
 #endif
    release_ata5785();
    return rtn;
}
/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_SM_state
* Description :     rf_ata5785_read_SM_state
* Arguments :       none
* Return Value :
***********************************************************************************************************************/
uint8 rf_ata5785_read_SM_state( void ){
uint8 rtn;
uint8 ptr;
    select_ata5785();
#ifdef MCAL_F1L

   ptr=0x08;
    Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0x01;
    Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0x02;
    Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0xF5;
    Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0x00;
    rtn = Spi_WriteIB(0, (uint8 *) &ptr );
 #else

   ptr=0x08;
    active_xfer_spi( ptr );
    ptr=0x01;
    active_xfer_spi( ptr );
    ptr=0x02;
    active_xfer_spi( ptr );
    ptr=0xF5;
    active_xfer_spi( ptr );
    ptr=0x00;
    active_xfer_spi( ptr );
    ptr=0x00;
    rtn = active_xfer_spi( ptr );

#endif
    release_ata5785();

    return rtn;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_OFF_command
* Description :     rf_ata5785_OFF_command
* Arguments :       none
* Return Value :
***********************************************************************************************************************/
void rf_ata5785_OFF_command( void ){
uint8 ptr;

    select_ata5785();
#ifdef MCAL_F1L

   ptr=0x18;
    Spi_WriteIB(0, (uint8 *) &ptr );
    ptr=0x00;
    Spi_WriteIB(0, (uint8 *) &ptr );

#else

   ptr=0x18;
    active_xfer_spi( ptr );
    ptr=0x00;
    active_xfer_spi( ptr );

#endif
    release_ata5785();

}

     uint8 rf_ata5785_InitSM(void){
  fp2IniState ();
  if(ataInitialized == fp2IniState){
    return TRUE;
  }
  else{
    return FALSE;
  }
}

void rf_ata5785_StartInitSM(void){
  fp2IniState = ataIni1st ;
}

static void ataIni1st(void){
  uint8 i;

  RFD_Pwr3Pin4Ata(0);/*@as F1L BSW ATMEL->Power off*/
  rf.rom = 0;
   rf.level = 0;
  rf.rssilvl = 0;
  rf.mode = 0;
  rf.channel = 0;
  rf.events[0] = 0;
  rf.events[1] = 0;
  rf.events[2] = 0;
  rf.events[3] = 0;
  for(i=((uint8) 0); i<RF_DAT_BUF_LEN; i++){
    rf.buffer[i] = (uint8) 0;
    rf.rssibuf[i] = (uint8) 0;
  }

  fp2IniState = ataIniPwrOn ;
}

static void ataIniPwrOn(void){
  csig0_4ATAinit();     /*ATA4MFA DisableSPI ist in der INIT Fkt. included */
  RFD_Pwr3Pin4Ata(1);   /*@as F1L BSW ATMEL->Power on Port10_Bit14*/
  fp2IniState = ataInitSysRes ;
}

static void ataInitSysRes(void){
  ucIRQ_ATA_activ=0;    /*clear  Port10 IRQ activ member  */
  rf_ata5785_system_reset();  /*"System Reset" configures the watchdog with the minimum timeout period and waits for a watchdog reset in an endless loop.*/

  /* it's not allowed to get INTP11 till this time, because INT processing could leads to error */
  MKP11 = L;
  fp2IniState = ataIniWtResetEvent;
}

static void ataIniWtResetEvent(void){
  static uint8 tOCtIn50msec = (uint8) 3;

  if(0 < tOCtIn50msec){
    tOCtIn50msec--;
    if(1 == ucIRQ_ATA_activ){
      ucIRQ_ATA_activ = 0;
      tOCtIn50msec = (uint8) 3;
      fp2IniState = ataIniSeq1;

      rf_ata5785_get_events( rf.events );
      rf.rom = rf_ata5785_read_version();

      rf_ata5785_write_sram(rf_idCtrl_cfg);
    }
  }
  else{
    tOCtIn50msec = (uint8) 3;
    fp2IniState = ataIni1st;
    csig0_disable();
  }
}

static void ataIniSeq1(void){
  rf_ata5785_write_sram(rf_events_cfg);
  rf_ata5785_set_watchdog(rf_watchdog_cfg);
  rf_ata5785_write_sram(rf_dbgsw_cfg);
  rf_ata5785_write_sram(rf_PORTB_cfg);
  rf_ata5785_write_sram(rf_DDRB_cfg);
  rf_ata5785_write_sram(rf_PORTC_cfg);
  rf_ata5785_write_sram(rf_DDRC_cfg);
  rf_ata5785_write_sram(rf_PCMSK0_cfg);
  rf_ata5785_write_sram(rf_PCMSK1_cfg);
  rf_ata5785_write_sram(rf_PCICR_cfg);
  rf_ata5785_write_sram(rf_MCUCR_cfg);

  fp2IniState = ataIniSeq2;
}

static void ataIniSeq2(void){
  rf_ata5785_write_sram(rf_temperatureCalibration_cfg);
  rf_ata5785_write_sram(rf_trxCalibConfiguration_cfg);
  rf_ata5785_write_sram(rf_sleepModeConfig_cfg);
  rf_ata5785_write_sram(rf_frcCalibrationConfiguration_cfg);
  rf_ata5785_write_sram(rf_pollConfig_cfg);
  rf_ata5785_write_sram(rf_calib_srcRes_cfg);
  rf_ata5785_write_sram(rf_calib_srcCorVal_cfg);

  fp2IniState = ataIniSeq3;
}

static void ataIniSeq3(void){
  rf_ata5785_write_sram(rf_sramService3_cfg);
  fp2IniState = ataIniSeq4;
}

static void ataIniSeq4(void){
  rf_ata5785_write_sram(rf_sramService4_cfg);
  fp2IniState = ataIniSeq5;
}

static void ataIniSeq5(void){
  rf_ata5785_write_sram(rf_gapMode_cfg);
  rf_ata5785_write_sram(rf_eomConfig_cfg);
  rf_ata5785_write_sram(rf_tempMeas_cfg);
  rf_ata5785_write_sram(rf_sysConf_rd);

  rf_ata5785_write_sram(rf_disableClock_cfg);
  rf_ata5785_write_sram(rf_setClockDivider_cfg);
  rf_ata5785_write_sram(rf_reenableClock_cfg);
   rf.mode = 0x00;
  rf.channel = 0x00;
  rf_ata5785_set_mode( rf.mode, rf.channel );
  fp2IniState = ataIniSeq6;
}

static void ataIniSeq6(void){
  rf_ata5785_get_events( rf.events );
  csig0_disable();
  fp2IniState = ataIniStartService;
}

static void ataIniStartService(void){
  if(GetPort4Frequenz433() == TRUE){
    SetServNPath(0x83);
  }
  else{
    SetServNPath(0x84);
  }

  fp2IniState = ataInitialized;
}

void ataInitialized(void){
}

