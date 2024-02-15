/***********************************************************************************************************************
* Copyright (c) 2012 Atmel Corporation. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
* following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*    disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
*    following disclaimer in the documentation and/or other materials provided with the distribution.
*
* 3. The name of Atmel may not be used to endorse or promote products derived from this software without specific
*    prior written permission.
*
* 4. This software may only be redistributed and used in connection with an Atmel microcontroller product.
*
* THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
* THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE EXPRESSLY AND
* SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : (ata_dev_5785.c)
* Version      : (v0.1)
* Device(s)    : (ATA5785)
* OS           : (if applicable)
* H/W Platform : (ATAB5831A-V1.0)
* Description  : (Low Level drivers for the OmegaII RF receiver)
***********************************************************************************************************************/

/***********************************************************************************************************************
* Included Header Files
***********************************************************************************************************************/
#include "Platform_Types.h" /*BSW types.h*/ 
#include "Spi.h" /*BSW */
#include "CtCdHufTPMSrfd.h"


#include "ata_dev_5785.h"
#include "ata5785_sram.h"
#include "ata_Rec2RingBuffer.h"

#include "RH850F1L_dvf.h"

/***********************************************************************************************************************
* Macro (#define) Definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
* Type (typedef) Definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
* Global Constant Definitions
* - These can be accessed by functions outside this file
* - Note: Each global constant should be made "extern" in the associated header file
***********************************************************************************************************************/

/***********************************************************************************************************************
* Local/Private Function Prototypes (Declarations)
* - Prototypes for functions visible only to this module
* - Note: Each prototype should be preceded by "static" keyword
***********************************************************************************************************************/
static void rf_ata5785_system_reset( void ) ;
uint8 active_xfer_spi(uint8 ucByteValue);
//void csig0_disable(void);
//void csig0_enable(void);
//void csig0_4ATAinit(void);
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

/***********************************************************************************************************************
* Global Variable Definitions
* - These can be accessed by functions outside this file
* - Note: Each global variable should be made "extern" in the associated header
* file
***********************************************************************************************************************/
uint8 ucMISOdata[4];

struct rfstruct  rf;

// Pre-Load temp value with T=25°C (val=25+50=75)
uint8 rf_tempMeas_cfg[] = {
	0x02,     // addr_h
	0xC3,     // addr_l
	0x01,     // length
	0x4B      // tempMeas
};

// set systemConfig; disable SFIFI interrupts
uint8 rf_sysConf_rd[] = {
	0x02,     // addr_h
	0xE5,     // addr_l
	0x01,     // length
  0x0c      // systemConfig, 0x0C = SFIFO_OFL_UFL_RX_disable and DFIFO_OFL_UFL_RX_disable
};

static void (*fp2IniState) (void) = ataIni1st;
/***********************************************************************************************************************
* Private Constant Definitions
* - These can be accessed across functions within this file
* - Note: Each definition should be preceded by "static" keyword
***********************************************************************************************************************/


/***********************************************************************************************************************
* Private Variable Definitions
* - These can be accessed across functions within this file
* - Note: Each definition should be preceded by "static" keyword
***********************************************************************************************************************/


/***********************************************************************************************************************
* Local/Private Functions
***********************************************************************************************************************/
static void select_ata5785(void)/* ATA4StarterKit*/
{
    RFD_CsAta(1); /*CS LOW aktiv --> 1=low!!! F1L BSW in order*/
    WaitHard(47); /*4RH850 47us*/
}

static void release_ata5785(void) /* ATA4StarterKit*/
{
    WaitHard(36);/*4RH850 36us*/
	RFD_CsAta(0); /*CS LOW aktiv --> 0=high!!! F1L BSW in order*/
    WaitHard(17);/*4RH850 17us*/
}

/***********************************************************************************************************************
* Function Name:
* Description :
* Arguments : none
* Return Value : none
***********************************************************************************************************************/


/***********************************************************************************************************************
* Global Functions
* - Note: Each global function should have a prototype (declaration) in the the associated header file
***********************************************************************************************************************/
/*****************************************************************************
** Function:    void WaitHard(ulTicks) in µs MAX FFFFFFF=4294967295µs
** Description: This function wait hart time in micro seconds  
**              (Starter KIT with 80Mhz Clock Time!)
** Parameter:   None
** Return:      None
******************************************************************************/
void WaitHard(unsigned long ulTicks)
{
    //ulTicks=(ulTicks*10)-5;
    ulTicks=(ulTicks*12);
    while(ulTicks !=0)
	{
	  ulTicks--;
	}    /* An dieser Stelle hart warten! */

}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_deinit Projekt: precondition for appl reflash
* Description :     De Initialize: Disable SPI,  
* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_deinit(void)
{
  MKP11 = H; /* mask P11 INT -> IsrIntP11func() interrupt processing is disabled */

  RFD_CsAta(0); /*CS LOW aktiv --> 0=high!!! Chip Select disable CS  PIN: P10_5 */ 
  csig0_disable(); /* disable SPI*/
  
  RFD_Pwr3Pin4Ata(0);/*@as F1L BSW ATMEL->Power off*/
  fp2IniState = ataIni1st ;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_init Projekt: TransRaLF
* Description :     Initialize the data structures

	// rf_init_spi for IO pin initialisation
	// -------- rf device io ----------------------------------------------------------------
    //                                                     RH850SKid  RH850Ziel
    // set port pins: PB5:   RF NSS       out high (PB5)   (P0_11)    (P10_5)
	//                 PD3:   PWRON        out low  (PB4)  (P11_11)   (P10_14)
	//                 PB2:   SPI MOSI     out ---  (PB2)  (P0_12)    (P10_6)
	//                 PB3:   SPI MISO     in  ---  (PB3)  (P0_13)    (P10_8)
	//                 PB1:   SPI SCK      out ---  (PB1)  (P0_14)    (P10_7)
	//                 PD7:   RF NRES      out high (PC0)    -          -
	//                 PD5:   RF NPWRON1   in  high (PC1)    -          -
	//                 PD0:   RF IRQ       in  low  (PB6)  (P11_9)    (P10_11)

* Arguments :       none
* Return Value :    none
***********************************************************************************************************************/
uint8 rf_ata5785_init(void) /*CR_1211_150_021 Fkt. changed with return value*/
{
    uint8 i;
    uint16 ushTO = 10000; /*CR_1211_150_021 @@AS Testergebnis value 4 SPI i.O.: ushTO=53xxx  / old init value: 60000*/

    RFD_Pwr3Pin4Ata(0);/*@as F1L BSW ATMEL->Power off*/
    //FastPWR_3Pin4_ATA(0);/* 64pin CPU CR_0850_000_006*/
    WaitHard(10000); /*ATA4MFA RH850 10ms*/
    //Setup rf structure
    rf.rom = 0;
    rf.level = 0;
    rf.rssilvl = 0;
    rf.mode = 0;
    rf.channel = 0;
    rf.events[0] = 0;
    rf.events[1] = 0;
    rf.events[2] = 0;
    rf.events[3] = 0;
    // RF_DAT_BUF_LEN=24// alt error: rf.buffer hat 24 Bytes -> for(i=0; i<32; i++)
    for(i=0; i<RF_DAT_BUF_LEN; i++)
    {
        rf.buffer[i] = 0;
        rf.rssibuf[i] = 0;
    }

    csig0_4ATAinit();     /*ATA4MFA DisableSPI ist in der INIT Fkt. included */
    RFD_Pwr3Pin4Ata(1);   /*@as F1L BSW ATMEL->Power on Port10_Bit14*/
    //FastPWR_3Pin4_ATA(1);/* 64pin CPU CR_0850_000_006*/

    WaitHard(5000);       /*RH850 1ms ATA4MFA*/
	ucIRQ_ATA_activ=0;    /*clear  Port10 IRQ activ member  */
    /*"System Reset" configures the watchdog with the minimum timeout period and waits for a watchdog reset in an endless loop.*/
   	rf_ata5785_system_reset(); /* events.system=0x15; events.events=0x00 --> GPIO_G_IRQ Kurz (Th=76us) High, dann =low! */

    /* it's not allowed to get INTP11 till this time, because INT processing could leads to error */
    MKP11 = L;  /* enable IsrIntP11func() interrupt processing */

	/**********************************************************************************************/
	/* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
	/* PORT10Pin11 Port IRQ falling edge or timeout */
	/**********************************************************************************************/
    while((ucIRQ_ATA_activ!=1) && (ushTO--)); /*PORT10Pin11 Port IRQ falling edge or timeout */
	
	if(ushTO != 0xFFFF) // OIL #484 Fota's finding: after the loop above was left for 0 == ushTO--, than now ushTO is 0xFFFF
  {
    ucIRQ_ATA_activ=0;

    /* 2 Fkt im TransRaLF*/
    rf_ata5785_get_events( rf.events );
    rf.rom = rf_ata5785_read_version();

    // configure device
    rf_ata5785_write_sram(rf_idCtrl_cfg);
    rf_ata5785_write_sram(rf_events_cfg);
    // set watchdog
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
    // set temperature measurement value to 25°C
    rf_ata5785_write_sram(rf_tempMeas_cfg);
    // set systemConfig: disable SFIFO interrupts
    rf_ata5785_write_sram(rf_sysConf_rd);

    // CR_0850_000_001 Atmel 19.05.2015 JB set CKL_OUT to PortB0
    rf_ata5785_write_sram(rf_disableClock_cfg);
    rf_ata5785_write_sram(rf_setClockDivider_cfg);
    rf_ata5785_write_sram(rf_reenableClock_cfg);


    /* 2 Fkt im ATMEL EVAL Board!*/
    //rf.rom = rf_ata5785_read_version();
    //rf_ata5785_get_events( rf.events );

    // set idle mode
    rf.mode = 0x00;
    rf.channel = 0x00;
    rf_ata5785_set_mode( rf.mode, rf.channel );
    WaitHard(5000); /*RH850 5ms ATA4MFA*/
    rf_ata5785_get_events( rf.events );

    // Fkt im ATMEL EVAL Board! set polling mode
    /*rf.mode = 0x23;
    rf.channel = 0x00;
    rf_ata5785_set_mode( rf.mode, rf.channel );
    //_delay_ms(5);
    WaitHard(5000);
    rf_ata5785_get_events( rf.events ); */

#ifdef MCAL_F1L
    Spi_Cancel(SPI_ZERO); /*@RENESAS BSW F1L out of order */
#else
    csig0_disable(); /* disable SPI*/
#endif
    return TRUE;  /*CR_1211_150_021*/

  }
	else
  {

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
uint8 rf_ata5785_read_version( void )
{
uint8 rtn=FALSE; /*CRS_1211_500_486*/
	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr=0x13;
	Spi_WriteIB(0, (uint8 *) &ptr);	// events.system
	Spi_AsyncTransmit(0);
	ptr=Spi_GetHWUnitStatus(0);
	Spi_ReadIB(0, (uint8 *) &ptr);	

	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr);	// events.events
	rtn = Spi_WriteIB(0, (uint8 *) &ptr);	// ROM version
	Spi_WriteIB(0, (uint8 *) &ptr);	// Flash version high
	Spi_WriteIB(0, (uint8 *) &ptr);	// flash version low
	Spi_WriteIB(0, (uint8 *) &ptr);	// customer version

#else  /*MCAL_F1L*/
  active_xfer_spi( 0x13 );	// events.system
  active_xfer_spi( 0x00 );	// events.events
	rtn = active_xfer_spi( 0x00 );	// ROM version
	active_xfer_spi( 0x00 );	// Flash version high
	active_xfer_spi( 0x00 );	// flash version low
	active_xfer_spi( 0x00 );	// customer version

#endif /*MCAL_F1L*/

	// release NSS for ata5785
	release_ata5785();

	return rtn;
}


/***********************************************************************************************************************
* Function Name:    rf_ata5785_get_events
* Description :     Read and clear event bytes
* Arguments :       buffer pointer
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_get_events( uint8 buf[] )
{
uint8 ptr;
	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L	
	ptr=0x04;
	buf[0] = Spi_WriteIB(0, (uint8 *) &ptr);// events.system
	ptr=0x00;
	buf[1] = Spi_WriteIB(0, (uint8 *) &ptr);	// events.events
	buf[2] = Spi_WriteIB(0, (uint8 *) &ptr);	// events.power
	buf[3] = Spi_WriteIB(0, (uint8 *) &ptr);	// events.config

#else  /*MCAL_F1L*/
	ptr=0x04;
	buf[0] = active_xfer_spi(ptr);
	ptr=0x00;
	buf[1] = active_xfer_spi(ptr);
	buf[2] = active_xfer_spi(ptr);
	buf[3] = active_xfer_spi(ptr);


#endif  /*MCAL_F1L*/
	// release NSS for ata5785
	release_ata5785();

	return;
}


/***********************************************************************************************************************
* Function Name:    rf_ata5785_set_mode
* Description :     set operating mode
* Arguments :       mode and channel
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_set_mode( uint8 mode, uint8 channel )
{
	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
	uint8 ptr;

  ptr=0x0D; /*events.system*/
	Spi_WriteIB( 0, (uint8 *) &ptr );	// events.system
	
	Spi_WriteIB(0, (uint8 *) &mode );	// events.events
	
	Spi_WriteIB( 0, (uint8 *) &channel );	// dummy

#else
	active_xfer_spi( 0x0D );	// events.system
	active_xfer_spi( mode );	// events.events
	active_xfer_spi( channel );	// dummy


#endif
	// release NSS for ata5785
	release_ata5785();

	return;
}


/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rx_level
* Description :     Read rx buffer level
* Arguments :       none
* Return Value :    rx buffer level
***********************************************************************************************************************/
uint8 rf_ata5785_read_rx_level( void )
{
uint8 rtn;
	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

	ptr=0x01;
	Spi_WriteIB(0, (uint8 *) &ptr);
	//Spi_WriteIB( 0x01 );	 events.system
	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr);
	//Spi_WriteIB( 0x00 );	 events.events
	
	rtn=Spi_WriteIB(0, (uint8 *) &ptr);
	//rtn = Spi_WriteIB( 0x00 );	 bytes
#else
	active_xfer_spi( 0x01 );	// events.system
	active_xfer_spi( 0x00 );	// events.events
	rtn = active_xfer_spi( 0x00 );	// bytes
#endif
	// release NSS for ata5785
	release_ata5785();

	return rtn;
}


/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rssi_level
* Description :     Read rssi buffer level
* Arguments :       none
* Return Value :    rssi buffer level
***********************************************************************************************************************/
uint8 rf_ata5785_read_rssi_level( void )
{
uint8 rtn;

	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

	ptr=0x03;
	Spi_WriteIB(0, (uint8 *) &ptr); /* 0x03*/
	//Spi_WriteIB( 0x03 );	// events.system
	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr );	/* 0x00*/
	rtn = Spi_WriteIB(0, (uint8 *) &ptr );	/* 0x00*/
#else
	active_xfer_spi( 0x03 );	// events.system
	active_xfer_spi( 0x00 );	// events.events
	rtn = active_xfer_spi( 0x00 );	// bytes
#endif
	// release NSS for ata5785
	release_ata5785();

	return rtn;
}


/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rx_buf
* Description :     Read rx buffer
* Arguments :       buffer pointer and length
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_read_rx_buf( uint8 buf[], uint8 *len )
{
uint8 i;

	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

	ptr=0x01;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.system
	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.events
	*len = Spi_WriteIB(0, (uint8 *) &ptr );	// bytes
	// release NSS for ata5785
	release_ata5785();

	select_ata5785();
	ptr=0x06;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.system
	Spi_WriteIB(0,  len );	// events.events
	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr );	// dummy

	for(i=0; i<*len; i++)
	{
		buf[i] = Spi_WriteIB(0, (uint8 *) &ptr );
	}
#else
	active_xfer_spi( 0x01 );	// events.system
	active_xfer_spi( 0x00 );	// events.events
	*len = active_xfer_spi( 0x00 );	// bytes
	// release NSS for ata5785
	release_ata5785();

	select_ata5785();
	active_xfer_spi( 0x06 );	// events.system
	active_xfer_spi( *len );	// events.events
	active_xfer_spi( 0x00 );	// dummy

	for(i=0; i<*len; i++)
	{
		buf[i] = active_xfer_spi( 0x00 );
	}
#endif
	// release NSS for ata5785
	release_ata5785();
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_read_rssi_buf
* Description :     Read rssi buffer
* Arguments :       buffer pointer and length
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_read_rssi_buf( uint8 buf[], uint8 *len )
{
uint8 i;
	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;
	ptr=0x03;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.system
	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.events
	*len = Spi_WriteIB(0, (uint8 *) &ptr );	// bytes
	// release NSS for ata5785
	release_ata5785();

	// set NSS for ata5785
	select_ata5785();
	ptr=0x05;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.system
	Spi_WriteIB(0, len );    // events.events
	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr );	// dummy
	for(i=0; i<*len; i++)
	{
		buf[i] = Spi_WriteIB(0, (uint8 *) &ptr );
	}

#else
	active_xfer_spi( 0x03 );	// events.system
	active_xfer_spi( 0x00 );	// events.events
	*len = active_xfer_spi( 0x00 );	// bytes
	// release NSS for ata5785
	release_ata5785();

	// set NSS for ata5785
	select_ata5785();
	active_xfer_spi( 0x05 );	// events.system
	active_xfer_spi( *len );    // events.events
	active_xfer_spi( 0x00 );	// dummy
	for(i=0; i<*len; i++)
	{
		buf[i] = active_xfer_spi( 0x00 );
	}

#endif

	// release NSS for ata5785
	release_ata5785();

	return;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_write_tx_buf
* Description :     Write tx buffer
* Arguments :       buffer pointer and length
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_write_tx_buf( uint8 buf[], uint8 len )
{
uint8 i;
	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
  uint8 ptr;

	ptr=0x06;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.system
	ptr=len;
	Spi_WriteIB(0, (uint8 *) &ptr );	    // events.events
	ptr=0x00;
	Spi_WriteIB(0, (uint8 *) &ptr );	// dummy

	for(i=0; i<len; i++)
	{
		ptr=buf[i];
		Spi_WriteIB(0, (uint8 *) &ptr );
	}
#else
	active_xfer_spi( 0x06 );	// events.system
	active_xfer_spi( len );	    // events.events
	active_xfer_spi( 0x00 );	// dummy

	for(i=0; i<len; i++)
	{
		active_xfer_spi( buf[i] );
	}


#endif

	// release NSS for ata5785
	release_ata5785();

	return;
}

/***********************************************************************************************************************
* Function Name:    rf_ata5785_write_sram
* Description :     Write into sram or register
* Arguments :       buffer pointer
* Return Value :    none
***********************************************************************************************************************/
void rf_ata5785_write_sram(const uint8 data[])
{
  uint8 i;
  uint8 length;
  uint8 offset;
  uint8 ptr;

  union
  {
    unsigned short   ui;
    uint8  uc[2];
  } addr;

  // write to SRAM or register:
  // TX = <0x07>, <length>, <addr high>, <addr low>, <data>, ...
  // RX = <ev1>,  <ev2>,    <dum>,       <dum>,      <0x00>
#define SRAM_BUFFER_SIZE 32

  addr.ui = (unsigned short) data[0];
  addr.ui<<= 8;
  addr.ui += (unsigned short) data[1];
  length = data[2];
  offset = 3;

  do
  {
    if(length <= SRAM_BUFFER_SIZE)
    {
      select_ata5785();

#ifdef MCAL_F1L			
      ptr=0x07;
      Spi_WriteIB(0, (uint8 *) &ptr );
      ptr=length;
      Spi_WriteIB(0, (uint8 *) &ptr );   // length
      ptr=(uint8) (addr.ui>>8);
      Spi_WriteIB(0, (uint8 *) &ptr );  // addr high
      ptr=(uint8) addr.ui;
      Spi_WriteIB(0, (uint8 *) &ptr );  // addr low

      for(i=0; i<length; i++)
      {
        ptr=data[i+offset];
        Spi_WriteIB(0, (uint8 *) &ptr );
      }
      release_ata5785();
      length = 0;
    }
    else
    {
      select_ata5785();
      ptr=0x07;
      Spi_WriteIB(0, (uint8 *) &ptr ); 
      ptr=SRAM_BUFFER_SIZE;
      Spi_WriteIB(0, (uint8 *) &ptr ); 	// length
      ptr=(uint8) (addr.ui>>8);
      Spi_WriteIB(0, (uint8 *) &ptr );    // addr high
      ptr=(uint8) addr.ui; 
      Spi_WriteIB(0, (uint8 *) &ptr );    // addr low
      for(i=0; i<SRAM_BUFFER_SIZE; i++)
      {	
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
      active_xfer_spi(ptr);   // length
      ptr=(uint8) (addr.ui>>8);
      active_xfer_spi(ptr); // addr high
      ptr=(uint8) addr.ui;
      active_xfer_spi(ptr);  // addr low

      for(i=0; i<length; i++)
      {
        ptr=data[i+offset];
        active_xfer_spi(ptr);
      }
      release_ata5785();
      length = 0;
    }
    else
    {
      select_ata5785();
      ptr=0x07;
      active_xfer_spi(ptr);
      ptr=SRAM_BUFFER_SIZE;
      active_xfer_spi(ptr); 	// length
      ptr=(uint8) (addr.ui>>8);
      active_xfer_spi(ptr);    // addr high
      ptr=(uint8) addr.ui; 
      active_xfer_spi(ptr);    // addr low
      for(i=0; i<SRAM_BUFFER_SIZE; i++)
      {	
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
void rf_ata5785_set_watchdog(const uint8 data[] )
{
uint8 ptr;
	// set NSS for ata5785
	select_ata5785();
#ifdef MCAL_F1L
	ptr=0x10;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.system
	ptr=data[0];
	Spi_WriteIB(0, (uint8 *) &ptr );    // events.events
#else
	ptr=0x10;
	active_xfer_spi(ptr);
	ptr=data[0];
    active_xfer_spi(ptr);
#endif
	// release NSS for ata5785
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
uint8 check_sensor_type(void)
{
	unsigned int tcount;
   uint8 tmp=0;

	// check for 433MHz RX mode
	rf.mode = 0xA2;
	rf.channel = 0x83;

	Spi_Init(SPI_ZERO); /*@as F1L BSW */
	//csig0_4ATAinit();
	rf_ata5785_set_mode( rf.mode, rf.channel );
	
	//DisableSPI();
	Spi_Cancel(SPI_ZERO); /* @as F1L BSW */
	//csig0_disable(); /* ATA4StarterKit*/

  tcount = 0;
	do
	{
	  //WaitHard(cWAIT_10_MS);
	  WaitHard(10000); /*ATA4MFA RH850 10ms*/
	  //if (ucGetRF_IRQ_ExtRec () == 0) break;
	  
	 /**********************************************************************************************/
	 /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
	 /* PORT IRQ*/
	 // if (ucGetRF_IRQ_ATA() == 0) break;
	
	} while (tcount++ < 500);

 	//csig0_init(); /* ATA4StarterKit 1.DisableSPI 2.INI 3. EnableSPI*/
	Spi_Init(SPI_ZERO); /*@as F1L BSW */
	//csig0_4ATAinit();
	rf_ata5785_get_events( rf.events );
	//WaitHard(cWAIT_1_MSEC);
	WaitHard(1000); /*ATA4MFA RH850 1ms*/
	// set idle mode
	rf.mode = 0x00;
	rf.channel = 0x00;
	rf_ata5785_set_mode( rf.mode, rf.channel );
	//WaitHard(cWAIT_2_MSEC);
	WaitHard(2000); /*ATA4MFA RH850 2ms*/
	
	//DisableSPI();
	Spi_Cancel(SPI_ZERO); /* @as F1L BSW */
	//csig0_disable(); /* ATA4StarterKit*/
	if(((rf.events[3]&0x83) == 0x83) && ((rf.events[1]&0x07) == 0x07)) /*return 1;*/
   {
     tmp=1;
   }
   else
   {
	// check for 315MHz RX mode
	rf.mode = 0xA2;
	rf.channel = 0x84;

	//csig0_init(); /* ATA4StarterKit 1.DisableSPI 2.INI 3. EnableSPI*/
	
	Spi_Init(SPI_ZERO); /*@as F1L BSW */
	//csig0_4ATAinit();
	rf_ata5785_set_mode( rf.mode, rf.channel );
	//DisableSPI();
	Spi_Cancel(SPI_ZERO); /* @as F1L BSW */
	//csig0_disable(); /* ATA4StarterKit*/
	tcount = 0;
	do
	{
		//WaitHard(cWAIT_10_MS);
		WaitHard(10000); /*ATA4MFA RH850 10ms*/
		//if (ucGetRF_IRQ_ExtRec () == 0) break;
		
		/**********************************************************************************************/
	    /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
	    /* PORT IRQ*/
		//if (ucGetRF_IRQ_ATA() == 0) break;
	
	
	} while (tcount++ < 500);

	//csig0_init(); /* ATA4StarterKit 1.DisableSPI 2.INI 3. EnableSPI*/
	Spi_Init(SPI_ZERO); /*@as F1L BSW */
	//csig0_4ATAinit();
	rf_ata5785_get_events( rf.events );
	//WaitHard(cWAIT_1_MSEC);
	WaitHard(1000); /*ATA4MFA RH850 1ms*/
	// set idle mode
	rf.mode = 0x00;
	rf.channel = 0x00;
	rf_ata5785_set_mode( rf.mode, rf.channel );
	//WaitHard(cWAIT_2_MSEC);
	WaitHard(2000); /*ATA4MFA RH850 2ms*/
	//DisableSPI();
	Spi_Cancel(SPI_ZERO); /* @as F1L BSW */
	//csig0_disable(); /* ATA4StarterKit*/
     if(((rf.events[3]&0x84) == 0x84) && ((rf.events[1]&0x07) == 0x07))  /* return (2u);*/
     {
        tmp=2;
     }

   }
	// tmp=0 --> set default polling mode
	return (tmp);
}

#else
/***********************************************************************************************************************
* Function Name:    check_sensor_type
* Description :     check for sensor type
* Arguments :       none
* Return Value :    sensor type
***********************************************************************************************************************/
uint8 check_sensor_type(void)
{
	unsigned int tcount;
   uint8 tmp=0;

	// check for 433MHz RX mode
	rf.mode = 0xA2;
	rf.channel = 0x83;

	csig0_4ATAinit();
	rf_ata5785_set_mode( rf.mode, rf.channel );
	
	//DisableSPI();
	csig0_disable(); /* ATA4StarterKit*/

  tcount = 0;
	do
	{
	  //WaitHard(cWAIT_10_MS);
	  WaitHard(10000); /*ATA4MFA RH850 10ms*/
	  //if (ucGetRF_IRQ_ExtRec () == 0) break;
	  
	 /**********************************************************************************************/
	 /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
	 /* PORT IRQ*/
	 // if (ucGetRF_IRQ_ATA() == 0) break;
	
	} while (tcount++ < 500);

 	//csig0_init(); /* ATA4StarterKit 1.DisableSPI 2.INI 3. EnableSPI*/
	
	csig0_4ATAinit();
	rf_ata5785_get_events( rf.events );
	//WaitHard(cWAIT_1_MSEC);
	WaitHard(1000); /*ATA4MFA RH850 1ms*/
	// set idle mode
	rf.mode = 0x00;
	rf.channel = 0x00;
	rf_ata5785_set_mode( rf.mode, rf.channel );
	//WaitHard(cWAIT_2_MSEC);
	WaitHard(2000); /*ATA4MFA RH850 2ms*/
	
	//DisableSPI();
	csig0_disable(); /* ATA4StarterKit*/
	if(((rf.events[3]&0x83) == 0x83) && ((rf.events[1]&0x07) == 0x07)) /*return 1;*/
   {
     tmp=1;
   }
   else
   {
	// check for 315MHz RX mode
	rf.mode = 0xA2;
	rf.channel = 0x84;

	//csig0_init(); /* ATA4StarterKit 1.DisableSPI 2.INI 3. EnableSPI*/
	csig0_4ATAinit();
	rf_ata5785_set_mode( rf.mode, rf.channel );
	//DisableSPI();
	csig0_disable(); /* ATA4StarterKit*/
	tcount = 0;
	do
	{
		//WaitHard(cWAIT_10_MS);
		WaitHard(10000); /*ATA4MFA RH850 10ms*/
		//if (ucGetRF_IRQ_ExtRec () == 0) break;
		
		/**********************************************************************************************/
	    /* @as F1L BSW Hier muss der TriggerEvent von Dem ATA PORT Interrupt implementiert werden !!!!*/
	    /* PORT IRQ*/
		//if (ucGetRF_IRQ_ATA() == 0) break;
	
	
	} while (tcount++ < 500);

	//csig0_init(); /* ATA4StarterKit 1.DisableSPI 2.INI 3. EnableSPI*/
	csig0_4ATAinit();
	rf_ata5785_get_events( rf.events );
	//WaitHard(cWAIT_1_MSEC);
	WaitHard(1000); /*ATA4MFA RH850 1ms*/
	// set idle mode
	rf.mode = 0x00;
	rf.channel = 0x00;
	rf_ata5785_set_mode( rf.mode, rf.channel );
	//WaitHard(cWAIT_2_MSEC);
	WaitHard(2000); /*ATA4MFA RH850 2ms*/
	//DisableSPI();
	csig0_disable(); /* ATA4StarterKit*/
     if(((rf.events[3]&0x84) == 0x84) && ((rf.events[1]&0x07) == 0x07))  /* return (2u);*/
     {
        tmp=2;
     }

   }
	// tmp=0 --> set default polling mode
	return (tmp);
}


#endif

/***********************************************************************************************************************
* Function Name:    rf_ata5785_system_reset
* Description :     rf_ata5785_system_reset
* Arguments :       none
* Return Value :    reset
***********************************************************************************************************************/
static void rf_ata5785_system_reset( void )    //The SPI command “System Reset” configures the watchdog with the minimum timeout period and waits for a watchdog reset in an endless loop
{
uint8 ptr;	
	
	 select_ata5785(); /*CS for ATA and wait 47µs */
	
#ifdef MCAL_F1L
	 
   if(Spi_GetHWUnitStatus(0)==SPI_IDLE)
	{ 
	ptr=0x15;
	ucMISOdata[0]=Spi_WriteIB(0, (uint8 *) &ptr );		// events.system
	Spi_AsyncTransmit(0);
	
	}
	//if(Spi_GetHWUnitStatus(0)==SPI_IDLE)
	//ptr=Spi_GetSequenceResult(0);	
	
	//while( ptr&0x80 != 0x80);
	//{
	//ptr=Spi_GetSequenceResult(0);	
	//}
	//Spi_ReadIB(0, (uint8 *) &ptr);	
	
	if(Spi_GetHWUnitStatus(0)==SPI_IDLE)
	{
	ptr=0x00;
	ucMISOdata[1]=Spi_WriteIB(0, (uint8 *) &ptr );	   // events.events
    Spi_AsyncTransmit(0);
	}
	//ptr=Spi_GetSequenceResult(0);	
	//while( ptr!=0x00)
	//{
	//ptr=Spi_GetSequenceResult(0);	
	//}
	//Spi_ReadIB(0, (uint8 *) &ptr);	

#else
 
	ptr=0x15;
	ucMISOdata[0]=active_xfer_spi( ptr );	// events.system
	ptr=0x00;
	ucMISOdata[1]=active_xfer_spi( ptr );  // events.events
#endif
	
	ucMISOdata[3]=0x01; /*Transmit 2 V24 in main.c*/
	// release NSS for ata5785
	
	
	release_ata5785(); /*i.o. 4  ATA4StarterKit*/

	return;
}
/***********************************************************************************************************************
* Function Name:    SetServNPath
* Description :     SetServNPath
* Arguments :       none
* Return Value :    
***********************************************************************************************************************/
void SetServNPath( uint8 ui8SrvNPath )
{
#ifdef MCAL_F1L   
    //csig0_init(); /* ATA4StarterKit 1.DisableSPI 2.INI 3. EnableSPI*/
    Spi_Init(SPI_ZERO); /*@as F1L BSW */
#else
	csig0_4ATAinit();
#endif

    if (ui8SrvNPath == rf.channel)  // reactivation
    {
        //MFA2: CR_0850_000_002
        rf.mode = 0x12; // 7.4.8 System Mode: No RF_CAL + No VCO_TUNE necessary + IDLEMode=(XTO)+OperationMode=RXmode
        //rf.mode = 0x02; // 7.4.8 System Mode: No RF_CAL + No VCO_TUNE necessary + IDLEMode=(RC)+OperationMode=RXmode
    }
    else
    {
        //MFA2: CR_0850_000_002
        rf.mode = 0xB2;  // 7.4.8 System Mode: RF_CAL + VCO_TUNE  + IDLEMode=(XTO)+OperationMode=RXmode
        //rf.mode = 0xA2;  // 7.4.8 System Mode: RF_CAL + VCO_TUNE + IDLEMode =(RC)+OperationMode=RXmode
        rf.channel = ui8SrvNPath;
    }

    rf_ata5785_set_mode(rf.mode, rf.channel );
#ifdef MCAL_F1L    
	//DisableSPI();
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
uint8 rf_ata5785_read_error_code( void )
{
uint8 rtn;
uint8 ptr;	
    select_ata5785();
#ifdef MCAL_F1L 
	
	ptr=0x08;
    Spi_WriteIB(0, (uint8 *) &ptr );	// events.system
    ptr=0x01;
	Spi_WriteIB(0, (uint8 *) &ptr );	// events.events
    ptr=0x02;
	Spi_WriteIB(0, (uint8 *) &ptr );// hi-byte adr
    ptr=0xF4;
	Spi_WriteIB(0, (uint8 *) &ptr );	// lo-byte adr
    ptr=0x00;
	rtn = Spi_WriteIB(0, (uint8 *) &ptr );	// error code
#else
	
	ptr=0x08;
    active_xfer_spi( ptr );	// events.system
    ptr=0x01;
	active_xfer_spi( ptr );	// events.events
    ptr=0x02;
	active_xfer_spi( ptr );// hi-byte adr
    ptr=0xF4;
	active_xfer_spi( ptr );	// lo-byte adr
    ptr=0x00;
	active_xfer_spi( ptr );	// dummy
    ptr=0x00;
	rtn = active_xfer_spi( ptr );  // return data is error code
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
uint8 rf_ata5785_read_SM_state( void )
{
uint8 rtn;
uint8 ptr;
    select_ata5785();
#ifdef MCAL_F1L 

	ptr=0x08;
    Spi_WriteIB(0, (uint8 *) &ptr );// events.system
	ptr=0x01;
    Spi_WriteIB(0, (uint8 *) &ptr );	// events.events
	ptr=0x02;
    Spi_WriteIB(0, (uint8 *) &ptr );	// hi-byte adr
	ptr=0xF5;
    Spi_WriteIB(0, (uint8 *) &ptr );	// lo-byte adr
	ptr=0x00;
    rtn = Spi_WriteIB(0, (uint8 *) &ptr );	// error code
#else

	ptr=0x08;
    active_xfer_spi( ptr );// events.system
	ptr=0x01;
    active_xfer_spi( ptr );	// events.events
	ptr=0x02;
    active_xfer_spi( ptr );	// hi-byte adr
	ptr=0xF5;
    active_xfer_spi( ptr );	// lo-byte adr
	ptr=0x00;
    active_xfer_spi( ptr );	// dummy
	ptr=0x00;
    rtn = active_xfer_spi( ptr );  // return data is error code

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
void rf_ata5785_OFF_command( void )
{
uint8 ptr;

    select_ata5785();
#ifdef MCAL_F1L

	ptr=0x18;
    Spi_WriteIB(0, (uint8 *) &ptr );// events.system
	ptr=0x00;
    Spi_WriteIB(0, (uint8 *) &ptr );	// events.events

#else

	ptr=0x18;
    active_xfer_spi( ptr );// events.system
	ptr=0x00;
    active_xfer_spi( ptr );	// events.events

#endif
    release_ata5785();

}

// rf_ata5785_InitSM purpose:
// ata 5785 receiver chip initialization via spi and control signals:
// set port pins:  PB5:   RF NSS       out high (PB5)  (P0_11)    (P10_5)
//                 PD3:   PWRON        out low  (PB4)  (P11_11)   (P10_14)
//                 PB2:   SPI MOSI     out ---  (PB2)  (P0_12)    (P10_6)
//                 PB3:   SPI MISO     in  ---  (PB3)  (P0_13)    (P10_8)
//                 PB1:   SPI SCK      out ---  (PB1)  (P0_14)    (P10_7)
//                 PD0:   RF IRQ       in  low  (PB6)  (P11_9)    (P10_11)
// implementation as fine SM called in defined time cycles 
// timing: max cycle runtime < 5msec, complete init scenario app. 500msec
// returns > 0 if initialization is sucessfully finished
uint8 rf_ata5785_InitSM(void)
{
  fp2IniState ();
  if(ataInitialized == fp2IniState)
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}

void rf_ata5785_StartInitSM(void)
{
  fp2IniState = ataIni1st ;
}

static void ataIni1st(void)
{
  uint8 i;

  RFD_Pwr3Pin4Ata(0);/*@as F1L BSW ATMEL->Power off*/  
  rf.rom = 0; // init data struct used for receiver chip communication
  rf.level = 0;
  rf.rssilvl = 0;
  rf.mode = 0;
  rf.channel = 0;
  rf.events[0] = 0;
  rf.events[1] = 0;
  rf.events[2] = 0;
  rf.events[3] = 0;
  for(i=((uint8) 0); i<RF_DAT_BUF_LEN; i++)
  {
    rf.buffer[i] = (uint8) 0;
    rf.rssibuf[i] = (uint8) 0;
  }

  fp2IniState = ataIniPwrOn ;
}

static void ataIniPwrOn(void)
{
  csig0_4ATAinit();     /*ATA4MFA DisableSPI ist in der INIT Fkt. included */
  RFD_Pwr3Pin4Ata(1);   /*@as F1L BSW ATMEL->Power on Port10_Bit14*/
  fp2IniState = ataInitSysRes ;
}

static void ataInitSysRes(void)
{
  ucIRQ_ATA_activ=0;    /*clear  Port10 IRQ activ member  */
  rf_ata5785_system_reset();  /*"System Reset" configures the watchdog with the minimum timeout period and waits for a watchdog reset in an endless loop.*/

  /* it's not allowed to get INTP11 till this time, because INT processing could leads to error */
  MKP11 = L;  /* enable IsrIntP11func() interrupt processing */
  fp2IniState = ataIniWtResetEvent;
}

static void ataIniWtResetEvent(void)
{
  static uint8 tOCtIn50msec = (uint8) 3;

  if (0 < tOCtIn50msec)
  {
    tOCtIn50msec--;
    if (1 == ucIRQ_ATA_activ)
    {
      ucIRQ_ATA_activ = 0;
      tOCtIn50msec = (uint8) 3;
      fp2IniState = ataIniSeq1;

      rf_ata5785_get_events( rf.events );
      rf.rom = rf_ata5785_read_version();

      rf_ata5785_write_sram(rf_idCtrl_cfg);
    }
  }
  else
  {
    tOCtIn50msec = (uint8) 3;
    fp2IniState = ataIni1st;
    csig0_disable();
  }
}

static void ataIniSeq1(void)
{
  rf_ata5785_write_sram(rf_events_cfg);
  // set watchdog
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

static void ataIniSeq2(void)
{
  rf_ata5785_write_sram(rf_temperatureCalibration_cfg);
  rf_ata5785_write_sram(rf_trxCalibConfiguration_cfg);
  rf_ata5785_write_sram(rf_sleepModeConfig_cfg);
  rf_ata5785_write_sram(rf_frcCalibrationConfiguration_cfg);
  rf_ata5785_write_sram(rf_pollConfig_cfg);
  rf_ata5785_write_sram(rf_calib_srcRes_cfg);
  rf_ata5785_write_sram(rf_calib_srcCorVal_cfg);

  fp2IniState = ataIniSeq3;
}

static void ataIniSeq3(void)
{
  rf_ata5785_write_sram(rf_sramService3_cfg);
  fp2IniState = ataIniSeq4;
}

static void ataIniSeq4(void)
{
  rf_ata5785_write_sram(rf_sramService4_cfg);
  fp2IniState = ataIniSeq5;
}

static void ataIniSeq5(void)
{
  rf_ata5785_write_sram(rf_gapMode_cfg);
  rf_ata5785_write_sram(rf_eomConfig_cfg);
  // set temperature measurement value to 25°C
  rf_ata5785_write_sram(rf_tempMeas_cfg);
  // set systemConfig: disable SFIFO interrupts
  rf_ata5785_write_sram(rf_sysConf_rd);

  rf_ata5785_write_sram(rf_disableClock_cfg);
  rf_ata5785_write_sram(rf_setClockDivider_cfg);
  rf_ata5785_write_sram(rf_reenableClock_cfg);

  // set idle mode
  rf.mode = 0x00;
  rf.channel = 0x00;
  rf_ata5785_set_mode( rf.mode, rf.channel );
  fp2IniState = ataIniSeq6;
}

static void ataIniSeq6(void)
{
  rf_ata5785_get_events( rf.events );
  csig0_disable();
  fp2IniState = ataIniStartService;
}

static void ataIniStartService(void)
{
  if(GetPort4Frequenz433() == TRUE)
  {
    SetServNPath(0x83); /*SERVICE 3 == 433MHz */
  }
  else
  {
    SetServNPath(0x84); /*SERVICE 4 == 315MHz */
  }
  
  fp2IniState = ataInitialized;
}

void ataInitialized(void)
{
}

/***********************************************************************************************************************
* History
* : DD.MM.YYYY  Version  Description
* : 24.04.2013  0.1      Created initial structure
*
***********************************************************************************************************************/


