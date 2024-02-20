

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
   unsigned char rom;
   unsigned char level;
   unsigned char rssilvl;
   unsigned char events[4];
   unsigned char buffer[RF_DAT_BUF_LEN];
   unsigned char rssibuf[RF_RS_BUF_LEN];
   unsigned char mode;
   unsigned char channel;
};

extern uint8 ucIRQ_ATA_activ;
extern struct rfstruct  rf;
extern unsigned char ucMISOdata[4];

void csig0_disable(void);
void csig0_enable(void);
void csig0_4ATAinit(void);

void WaitHard(unsigned long ulTicks);
void rf_ata5785_deinit(void);
uint8 rf_ata5785_init( void );
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

#endif
