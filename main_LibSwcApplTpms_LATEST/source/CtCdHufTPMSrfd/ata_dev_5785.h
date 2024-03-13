

#ifndef ATA_DEV_8515_H
#define ATA_DEV_8515_H
#define RF_PORT  PORTD
#define RF_PIN   PIND
#define RF_DDR   DDRD

#define RF_IRQ_CHNL      0
#define RF_NPWRON1_CHNL  5
#define RF_NRES_CHNL     7
#define RF_DAT_BUF_LEN 24
#define RF_RS_BUF_LEN 24

struct rfstruct
{
   uint8 rom;
   uint8 level;
   uint8 rssilvl;
   uint8 events[4];
   uint8 buffer[RF_DAT_BUF_LEN];
   uint8 rssibuf[RF_RS_BUF_LEN];
   uint8 mode;
   uint8 channel;
};

extern uint8 ucIRQ_ATA_activ;
extern struct rfstruct  rf;
extern uint8 ucMISOdata[4];

void csig0_disable(void);
void csig0_enable(void);
void csig0_4ATAinit(void);

void WaitHard(uint32 ulTicks);
void rf_ata5785_deinit(void);
uint8 rf_ata5785_init( void );
void rf_ata5785_init_demo( void );
uint8 rf_ata5785_read_version( void );
void rf_ata5785_get_events( uint8 buf[] );
void rf_ata5785_set_mode( uint8 mode, uint8 channel );
uint8 rf_ata5785_read_rx_level( void );
uint8 rf_ata5785_read_rssi_level( void );
void rf_ata5785_read_rx_buf( uint8 buf[], uint8 *len );
void rf_ata5785_read_rssi_buf( uint8 buf[], uint8 *len );
void rf_ata5785_write_tx_buf( uint8 buf[], uint8 len );
void rf_ata5785_write_sram(const uint8 data[]);
void rf_ata5785_set_watchdog(const uint8 data[] );
uint8 check_sensor_type(void);
void SetServNPath( uint8 ui8SrvNPath );
uint8 rf_ata5785_read_SM_state( void );
uint8 rf_ata5785_read_error_code( void );
void rf_ata5785_OFF_command( void );
void rf_ata5785_StartInitSM(void);
uint8 rf_ata5785_InitSM(void);

#endif
