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

#ifndef ATA_DEV_8515_H
#define ATA_DEV_8515_H

/***********************************************************************************************************************
* File Name    : (ata_dev_8515.h)
* Version      : (v0.1)
* Device(s)    : (OmegaII ata5785)
* OS           : (if applicable)
* H/W Platform : (ATAB5831A-V1.0)
* Description  : (Low Level drivers for the OmegaII RF receiver)
***********************************************************************************************************************/

/***********************************************************************************************************************
* Included Header Files
***********************************************************************************************************************/

// RF Port
#define RF_PORT  PORTD
#define RF_PIN   PIND
#define RF_DDR   DDRD

#define RF_IRQ_CHNL      0
#define RF_NPWRON1_CHNL  5
#define RF_NRES_CHNL     7
#define RF_DAT_BUF_LEN 24
#define RF_RS_BUF_LEN 24


/***********************************************************************************************************************
* Typedef Definitions
***********************************************************************************************************************/
struct rfstruct 
{
	unsigned char rom;
	unsigned char level;
	unsigned char rssilvl;
	unsigned char events[4];
	unsigned char buffer[RF_DAT_BUF_LEN];
	unsigned char rssibuf[RF_RS_BUF_LEN];
	unsigned char mode;
	unsigned char channel;
};

/***********************************************************************************************************************
* Exported Global Variable Declarations
* - Note: Each declaration should be preceded by "extern" keyword
***********************************************************************************************************************/
extern uint8 ucIRQ_ATA_activ;
extern struct rfstruct  rf;
extern unsigned char ucMISOdata[4];

/***********************************************************************************************************************
* Global Function Prototypes (Declarations)
***********************************************************************************************************************/
void csig0_disable(void);
void csig0_enable(void);
void csig0_4ATAinit(void);

void WaitHard(unsigned long ulTicks);
void rf_ata5785_deinit(void);
uint8 rf_ata5785_init( void ); /* CR_1211_150_021 Fkt. changed with return value*/
void rf_ata5785_init_demo( void );
unsigned char rf_ata5785_read_version( void );
void rf_ata5785_get_events( unsigned char buf[] );
void rf_ata5785_set_mode( unsigned char mode, unsigned char channel );
unsigned char rf_ata5785_read_rx_level( void );
unsigned char rf_ata5785_read_rssi_level( void );
void rf_ata5785_read_rx_buf( unsigned char buf[], unsigned char *len );
void rf_ata5785_read_rssi_buf( unsigned char buf[], unsigned char *len );
void rf_ata5785_write_tx_buf( unsigned char buf[], unsigned char len );
void rf_ata5785_write_sram(const unsigned char data[]);
void rf_ata5785_set_watchdog(const unsigned char data[] );
unsigned char check_sensor_type(void);
void SetServNPath( unsigned char ui8SrvNPath );
unsigned char rf_ata5785_read_SM_state( void );
unsigned char rf_ata5785_read_error_code( void );
void rf_ata5785_OFF_command( void );
void rf_ata5785_StartInitSM(void);
uint8 rf_ata5785_InitSM(void);

/***********************************************************************************************************************
* History
* : DD.MM.YYYY  Version  Description
* : 24.04.2013  0.1      Created initial structure
*
***********************************************************************************************************************/

#endif
