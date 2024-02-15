// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      SRAM Service 3 Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_sramService3_cfg[] = {
    0x03,     // addr_h
    0x1C,     // addr_l
    0x8D,     // length
    0x0A,     // CHCR
    0x02,     // CHDN
    0x15,     // CHSTARTFILTER
    0x63,     // DMCDA
    0x3F,     // DMCDB
    0xCB,     // DMCRA
    0x8B,     // DMCRB
    0x13,     // DMDRA
    0x13,     // DMDRB
    0x25,     // DMMA
    0x22,     // DMMB
    0x1F,     // EOT1A
    0x1F,     // EOT1B
    0x1F,     // EOT2A
    0x1F,     // EOT2B
    0x0F,     // EOT3A
    0x2F,     // EOT3B
    0x00,     // FEANT
    0x07,     // FEAT
    0x2B,     // FEPAC
    0x1F,     // FEVCO
    0x07,     // FEVCT
    0x00,     // FREQoffset0
    0x00,     // FREQoffset1
    0xA1,     // TXDEVA0
    0x00,     // TXDEVA1
    0xA1,     // TXDEVB0
    0x00,     // TXDEVB1
    0x86,     // GACDIVA0
    0x00,     // GACDIVA1
    0x86,     // GACDIVB0
    0x00,     // GACDIVB1
    0xE2,     // IF0
    0x09,     // IF1
    0x18,     // RDOCR
    0x88,     // rssiSysConf
    0x0E,     // rxSetPathA0
    0x60,     // rxSetPathA1
    0x0E,     // rxSetPathB0
    0x40,     // rxSetPathB1
    0x11,     // rxSysEvent
    0x2C,     // rxSysSet
    0xA6,     // SFIDA0
    0x55,     // SFIDA1
    0x55,     // SFIDA2
    0x55,     // SFIDA3
    0xA6,     // SFIDB0
    0x55,     // SFIDB1
    0x55,     // SFIDB2
    0x55,     // SFIDB3
    0x0F,     // SFIDCA
    0x07,     // SFIDCB
    0x10,     // SFIDLA
    0x08,     // SFIDLB
    0x3F,     // SOT1A
    0x31,     // SOT1B
    0x2F,     // SOT2A
    0x2F,     // SOT2B
    0xC0,     // SOTtimeOutA
    0xA9,     // SOTtimeOutB
    0xB7,     // SYCA
    0xF2,     // SYCB
    0x60,     // TDFCRA
    0x60,     // TDFCRB
    0x8C,     // TMUL
    0x00,     // trxSysConf
    0x95,     // TXDRA0
    0x01,     // TXDRA1
    0x95,     // TXDRB0
    0x01,     // TXDRB1
    0x01,     // txSetPathA0
    0x00,     // txSetPathA1
    0x01,     // txSetPathB0
    0x00,     // txSetPathB1
    0x00,     // txSysEventA
    0x00,     // txSysEventB
    0x00,     // txPreambleSysEventA
    0x00,     // txPreambleSysEventB
    0xC0,     // WCOtimeOutA
    0xA9,     // WCOtimeOutB
    0x55,     // WUPA0
    0x55,     // WUPA1
    0x55,     // WUPA2
    0x55,     // WUPA3
    0xA6,     // WUPB0
    0x55,     // WUPB1
    0x55,     // WUPB2
    0x55,     // WUPB3
    0x10,     // WUPLA
    0x0C,     // WUPLB
    0x0F,     // WUPTA
    0x0B,     // WUPTB
    0x1D,     // RXCPA0
    0x00,     // RXCPA1
    0xFF,     // RXCIA0
    0xFF,     // RXCIA1
    0x00,     // RXSBA
    0x00,     // RXTLA0
    0x00,     // RXTLA1
    0x1D,     // RXCPB0
    0x00,     // RXCPB1
    0xFF,     // RXCIB0
    0xFF,     // RXCIB1
    0x00,     // RXSBB
    0x5A,     // RXTLB0
    0x00,     // RXTLB1
    0xAA,     // RXBC1
    0x62,     // TMCR2A
    0x62,     // TMCR2B
    0xCF,     // TMSSCA
    0xCF,     // TMSSCB
    0x00,     // TMTLA0
    0x00,     // TMTLA1
    0x00,     // TMTLB0
    0x00,     // TMTLB1
    0x1D,     // TMCPA0
    0x00,     // TMCPA1
    0x1D,     // TMCPB0
    0x00,     // TMCPB1
    0x00,     // TMCIA0
    0x00,     // TMCIA1
    0x00,     // TMCIB0
    0x00,     // TMCIB1
    0x00,     // TMCSBA
    0x00,     // TMCSBB
    0x09,     // RSSC
    0xE3,     // FEFREQ0
    0xB7,     // FEFREQ1
    0x01,     // FEFREQ2
    0x81,     // FEMS
    0x03,     // FECR
    0xE3,     // FEFREQ0
    0xB7,     // FEFREQ1
    0x01,     // FEFREQ2
    0x81,     // FEMS
    0x03,     // FECR
    0xE3,     // FEFREQ0
    0xB7,     // FEFREQ1
    0x01,     // FEFREQ2
    0x81,     // FEMS
    0x03      // FECR
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      SRAM Service 4 Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_sramService4_cfg[] = {
    0x03,     // addr_h
    0xA9,     // addr_l
    0x8D,     // length
    0x0A,     // CHCR
    0x22,     // CHDN
    0x15,     // CHSTARTFILTER
    0x63,     // DMCDA
    0x3F,     // DMCDB
    0xCB,     // DMCRA
    0x8B,     // DMCRB
    0x13,     // DMDRA
    0x13,     // DMDRB
    0x25,     // DMMA
    0x22,     // DMMB
    0x1F,     // EOT1A
    0x1F,     // EOT1B
    0x1F,     // EOT2A
    0x1F,     // EOT2B
    0x0F,     // EOT3A
    0x2F,     // EOT3B
    0x00,     // FEANT
    0x07,     // FEAT
    0x2B,     // FEPAC
    0xFC,     // FEVCO
    0x0A,     // FEVCT
    0x00,     // FREQoffset0
    0x00,     // FREQoffset1
    0xA1,     // TXDEVA0
    0x00,     // TXDEVA1
    0xA1,     // TXDEVB0
    0x00,     // TXDEVB1
    0x86,     // GACDIVA0
    0x00,     // GACDIVA1
    0x86,     // GACDIVB0
    0x00,     // GACDIVB1
    0x1D,     // IF0
    0x0A,     // IF1
    0x18,     // RDOCR
    0x88,     // rssiSysConf
    0x0E,     // rxSetPathA0
    0x60,     // rxSetPathA1
    0x0E,     // rxSetPathB0
    0x40,     // rxSetPathB1
    0x11,     // rxSysEvent
    0x2C,     // rxSysSet
    0xA6,     // SFIDA0
    0x55,     // SFIDA1
    0x55,     // SFIDA2
    0x55,     // SFIDA3
    0xA6,     // SFIDB0
    0x55,     // SFIDB1
    0x55,     // SFIDB2
    0x55,     // SFIDB3
    0x0F,     // SFIDCA
    0x07,     // SFIDCB
    0x10,     // SFIDLA
    0x08,     // SFIDLB
    0x3F,     // SOT1A
    0x31,     // SOT1B
    0x2F,     // SOT2A
    0x2F,     // SOT2B
    0xC0,     // SOTtimeOutA
    0xA9,     // SOTtimeOutB
    0xB7,     // SYCA
    0xF2,     // SYCB
    0x60,     // TDFCRA
    0x60,     // TDFCRB
    0x65,     // TMUL
    0x00,     // trxSysConf
    0x95,     // TXDRA0
    0x01,     // TXDRA1
    0x95,     // TXDRB0
    0x01,     // TXDRB1
    0x01,     // txSetPathA0
    0x00,     // txSetPathA1
    0x01,     // txSetPathB0
    0x00,     // txSetPathB1
    0x00,     // txSysEventA
    0x00,     // txSysEventB
    0x00,     // txPreambleSysEventA
    0x00,     // txPreambleSysEventB
    0xC0,     // WCOtimeOutA
    0xA9,     // WCOtimeOutB
    0x55,     // WUPA0
    0x55,     // WUPA1
    0x55,     // WUPA2
    0x55,     // WUPA3
    0xA6,     // WUPB0
    0x55,     // WUPB1
    0x55,     // WUPB2
    0x55,     // WUPB3
    0x10,     // WUPLA
    0x0C,     // WUPLB
    0x0F,     // WUPTA
    0x0B,     // WUPTB
    0x1D,     // RXCPA0
    0x00,     // RXCPA1
    0xFF,     // RXCIA0
    0xFF,     // RXCIA1
    0x00,     // RXSBA
    0x00,     // RXTLA0
    0x00,     // RXTLA1
    0x1D,     // RXCPB0
    0x00,     // RXCPB1
    0xFF,     // RXCIB0
    0xFF,     // RXCIB1
    0x00,     // RXSBB
    0x5A,     // RXTLB0
    0x00,     // RXTLB1
    0xAA,     // RXBC1
    0x62,     // TMCR2A
    0x62,     // TMCR2B
    0xCF,     // TMSSCA
    0xCF,     // TMSSCB
    0x00,     // TMTLA0
    0x00,     // TMTLA1
    0x00,     // TMTLB0
    0x00,     // TMTLB1
    0x1D,     // TMCPA0
    0x00,     // TMCPA1
    0x1D,     // TMCPB0
    0x00,     // TMCPB1
    0x00,     // TMCIA0
    0x00,     // TMCIA1
    0x00,     // TMCIB0
    0x00,     // TMCIB1
    0x00,     // TMCSBA
    0x00,     // TMCSBB
    0x09,     // RSSC
    0x21,     // FEFREQ0
    0x66,     // FEFREQ1
    0x00,     // FEFREQ2
    0x60,     // FEMS
    0x09,     // FECR
    0x21,     // FEFREQ0
    0x66,     // FEFREQ1
    0x00,     // FEFREQ2
    0x60,     // FEMS
    0x09,     // FECR
    0x21,     // FEFREQ0
    0x66,     // FEFREQ1
    0x00,     // FEFREQ2
    0x60,     // FEMS
    0x09      // FECR
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      ID Scan Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_idCtrl_cfg[] = {
    0x04,     // addr_h
    0x6C,     // addr_l
    0x5B,     // length
    0x06,     // idEna
    0x12,     // idByte0
    0x34,     // idByte1
    0x56,     // idByte2
    0x78,     // idByte3
    0x83,     // idCtrl0
    0x01,     // idByte4
    0x23,     // idByte5
    0x45,     // idByte6
    0x67,     // idByte7
    0x83,     // idCtrl1
    0x60,     // idByte8
    0x00,     // idByte9
    0x66,     // idByte10
    0x74,     // idByte11
    0x83,     // idCtrl2
    0x60,     // idByte12
    0x00,     // idByte13
    0x66,     // idByte14
    0x7D,     // idByte15
    0x83,     // idCtrl3
    0x31,     // idByte16
    0xEE,     // idByte17
    0x0D,     // idByte18
    0xFE,     // idByte19
    0x83,     // idCtrl4
    0x31,     // idByte20
    0xED,     // idByte21
    0xE0,     // idByte22
    0xFF,     // idByte23
    0x83,     // idCtrl5
    0xFF,     // idByte24
    0xFF,     // idByte25
    0xFF,     // idByte26
    0xFF,     // idByte27
    0x83,     // idCtrl6
    0xFF,     // idByte28
    0xFF,     // idByte29
    0xFF,     // idByte30
    0xFF,     // idByte31
    0x83,     // idCtrl7
    0xFF,     // idByte32
    0xFF,     // idByte33
    0xFF,     // idByte34
    0xFF,     // idByte35
    0x83,     // idCtrl8
    0xFF,     // idByte36
    0xFF,     // idByte37
    0xFF,     // idByte38
    0xFF,     // idByte39
    0x83,     // idCtrl9
    0xFF,     // idByte40
    0xFF,     // idByte41
    0xFF,     // idByte42
    0xFF,     // idByte43
    0x83,     // idCtrl10
    0xFF,     // idByte44
    0xFF,     // idByte45
    0xFF,     // idByte46
    0xFF,     // idByte47
    0x83,     // idCtrl11
    0xFF,     // idByte48
    0xFF,     // idByte49
    0xFF,     // idByte50
    0xFF,     // idByte51
    0x83,     // idCtrl12
    0xFF,     // idByte52
    0xFF,     // idByte53
    0xFF,     // idByte54
    0xFF,     // idByte55
    0x83,     // idCtrl13
    0xFF,     // idByte56
    0xFF,     // idByte57
    0xFF,     // idByte58
    0xFF,     // idByte59
    0x83,     // idCtrl14
    0xFF,     // idByte60
    0xFF,     // idByte61
    0xFF,     // idByte62
    0xFF,     // idByte63
    0x83,     // idCtrl15
    0xFF,     // idByte64
    0xFF,     // idByte65
    0xFF,     // idByte66
    0xFF,     // idByte67
    0x83,     // idCtrl16
    0xFF,     // idByte68
    0xFF,     // idByte69
    0xFF,     // idByte70
    0xFF,     // idByte71
    0x83      // idCtrl17
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Sleep Mode Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_sleepModeConfig_cfg[] = {
    0x02,     // addr_h
    0xEB,     // addr_l
    0x01,     // length
    0x86      // sleepModeConf
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Event Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_events_cfg[] = {
    0x02,     // addr_h
    0x0D,     // addr_l
    0x03,     // length
    0x00,     // pinEventConf
    0xC0,     // sysEventConf
    0x00      // cmdRdyConf
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Watchdog Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_watchdog_cfg[] = {
    0x10,    // SET_WATCHDOG_CMD_ID
    0x03     // WDTCR
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Debug Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_dbgsw_cfg[] = {
    0x01,     // addr_h
    0x56,     // addr_l
    0x01,     // length
    0x00      // DBGSW
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  AVEN: This Bit is accessible for LNAEN Low Noise Amplifier Enable @as  CR_0850_000_007
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned char rf_supcr_cfg[] = {
    0x00,     // addr_h
    0xCB,     // addr_l
    0x01,     // length
    0x20      // SUPCR: Bit5=1 AVEN=1
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  LNAEN: Low Noise Amplifier Enable @as  CR_0850_000_007
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned char rf_feen_cfg[] = {
    0x01,     // addr_h
    0x01,     // addr_l
    0x01,     // length
    0x08      // FEEN: Bit3=1 LNAEN=1
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      IO Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_PORTB_cfg[] = {
    0x00,     // addr_h
    0x27,     // addr_l
    0x01,     // length
    0x68      // confPORTB
};
uint8 rf_PORTC_cfg[] = {
    0x00,     // addr_h
    0x2A,     // addr_l
    0x01,     // length
    0x1B      // confPORTC
};
uint8 rf_DDRB_cfg[] = {
    0x00,     // addr_h
    0x26,     // addr_l
    0x01,     // length
    0xC8      // confDDRB
};
uint8 rf_DDRC_cfg[] = {
    0x00,     // addr_h
    0x29,     // addr_l
    0x01,     // length
    0x24      // confDDRC
};
uint8 rf_PCICR_cfg[] = {
    0x00,     // addr_h
    0x46,     // addr_l
    0x01,     // length
    0x03      // confPCICR
};
uint8 rf_PCMSK0_cfg[] = {
    0x00,     // addr_h
    0x6C,     // addr_l
    0x01,     // length
    0x20      // confPCMSK0
};
uint8 rf_PCMSK1_cfg[] = {
    0x00,     // addr_h
    0x6D,     // addr_l
    0x01,     // length
    0x00      // confPCMSK1
};
uint8 rf_MCUCR_cfg[] = {
    0x00,     // addr_h
    0x2E,     // addr_l
    0x01,     // length
    0x08      // confMCUCR
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Calibration Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_temperatureCalibration_cfg[] = {
    0x02,     // addr_h
    0xC7,     // addr_l
    0x17,     // length
    0x00,     // tempCal0
    0x07,     // tempCal1
    0x0C,     // tempCal2
    0x0E,     // tempCal3
    0x0F,     // tempCal4
    0x0E,     // tempCal5
    0x0C,     // tempCal6
    0x09,     // tempCal7
    0x05,     // tempCal8
    0x01,     // tempCal9
    0xFC,     // tempCal10
    0xF7,     // tempCal11
    0xF3,     // tempCal12
    0xEF,     // tempCal13
    0xEB,     // tempCal14
    0xE9,     // tempCal15
    0xE8,     // tempCal16
    0xE9,     // tempCal17
    0xEC,     // tempCal18
    0xF0,     // tempCal19
    0xF7,     // tempCal20
    0x01,     // tempCal21
    0x0D      // tempCal22
};
uint8 rf_trxCalibConfiguration_cfg[] = {
    0x02,     // addr_h
    0xDE,     // addr_l
    0x03,     // length
    0x00,     // calConf1
    0xA0,     // calConf2
    0x00      // selfChk
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Polling Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_pollConfig_cfg[] = {
    0x02,     // addr_h
    0xF6,     // addr_l
    0x22,     // length
    0xA4,     // confT1COR
    0x10,     // confT1MR
    0x00,     // pollLoopConf0
    0x00,     // pollLoopSCconf0
    0x00,     // pollLoopConf1
    0x00,     // pollLoopSCconf1
    0x00,     // pollLoopConf2
    0x00,     // pollLoopSCconf2
    0x00,     // pollLoopConf3
    0x00,     // pollLoopSCconf3
    0x00,     // pollLoopConf4
    0x11,     // pollLoopSCconf4
    0x00,     // pollLoopConf5
    0x21,     // pollLoopSCconf5
    0x00,     // pollLoopConf6
    0x00,     // pollLoopSCconf6
    0x00,     // pollLoopConf7
    0x00,     // pollLoopSCconf7
    0x00,     // pollLoopConf8
    0x00,     // pollLoopSCconf8
    0x00,     // pollLoopConf9
    0x00,     // pollLoopSCconf9
    0x00,     // pollLoopConf10
    0x00,     // pollLoopSCconf10
    0x00,     // pollLoopConf11
    0x00,     // pollLoopSCconf11
    0x00,     // pollLoopConf12
    0x00,     // pollLoopSCconf12
    0x00,     // pollLoopConf13
    0x00,     // pollLoopSCconf13
    0x00,     // pollLoopConf14
    0x00,     // pollLoopSCconf14
    0x00,     // pollLoopConf15
    0x00      // pollLoopSCconf15
};
uint8 rf_calib_srcRes_cfg[] = {
    0x02,     // addr_h
    0xC4,     // addr_l
    0x01,     // length
    0xA4      // confT1COR
};
uint8 rf_calib_srcCorVal_cfg[] = {
    0x02,     // addr_h
    0xC5,     // addr_l
    0x01,     // length
    0xA4      // confT1COR
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      FRC calibration Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_frcCalibrationConfiguration_cfg[] = {
    0x02,     // addr_h
    0xE1,     // addr_l
    0x01,     // length
    0xCC      // frcCalibGate
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Gap Mode Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_gapMode_cfg[] = {
    0x04,     // addr_h
    0xFB,     // addr_l
    0x14,     // length
    0x00,     // gapLengthService0PathA
    0x00,     // gapLengthService0PathB
    0x00,     // gapLengthService1PathA
    0x00,     // gapLengthService1PathB
    0x00,     // gapLengthService2PathA
    0x00,     // gapLengthService2PathB
    0x00,     // gapLengthService3PathA
    0x00,     // gapLengthService3PathB
    0x00,     // gapLengthService4PathA
    0x00,     // gapLengthService4PathB
    0x00,     // rxModeLengthService0PathA
    0x00,     // rxModeLengthService0PathB
    0x00,     // rxModeLengthService1PathA
    0x00,     // rxModeLengthService1PathB
    0x00,     // rxModeLengthService2PathA
    0x00,     // rxModeLengthService2PathB
    0x00,     // rxModeLengthService3PathA
    0x00,     // rxModeLengthService3PathB
    0x00,     // rxModeLengthService4PathA
    0x00      // rxModeLengthService4PathB
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Gap Mode Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_eomConfig_cfg[] = {
    0x05,     // addr_h
    0x13,     // addr_l
    0x06,     // length
    0x00,     // endOfMessageConfig
    0x00,     // endOfMessageConfig0
    0x00,     // endOfMessageConfig1
    0x00,     // endOfMessageConfig2
    0x00,     // endOfMessageConfig3
    0x00      // endOfMessageConfig4
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      Clock Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_disableClock_cfg[] = {
    0x00,     // addr_h
    0xC4,     // addr_l
    0x01,     // length
    0x00      // clkConfig
};
uint8 rf_setClockDivider_cfg[] = {
    0x00,     // addr_h
    0xC3,     // addr_l
    0x01,     // length
    0x04      // clkOutDiv
};
uint8 rf_reenableClock_cfg[] = {
    0x00,     // addr_h
    0xC4,     // addr_l
    0x01,     // length
    0x03      // clkConfig[3:0]
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                      RX Active Configuration
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint8 rf_sysEvent_cfg[] = {
    0x02,     // addr_h
    0x0E,     // addr_l
    0x01,     // length
    0xC0      // sysEventConf
};

