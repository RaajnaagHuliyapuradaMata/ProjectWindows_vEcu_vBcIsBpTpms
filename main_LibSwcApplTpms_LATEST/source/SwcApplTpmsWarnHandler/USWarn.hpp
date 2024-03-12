#pragma once
/******************************************************************************/
/* File              : USWarn.hpp                                             */
/* Author            : Nagaraja HULIYAPURADA MATA                             */
/* Copyright (c)2024 : All rights reserved.                                   */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ucPResInMBarc   25

/*
#define ush273Kelvinc   273
#define sc40Gradc       40
#define scMinus20Gradc -20
#define ucIsoClearc  (uint8) 0x20
#define ucNegHysc    (uint8) 0x80
#define ucPRecResetc (uint8) 0x02
#define ucUSCodec    (uint8) 0x04
#define ucCtryMaskc  (uint8) 0x0C

extern uint8 ucGetWarnType(uint8 ucWarnTypeIx);

struct Byte{
   uint8 Lo;
   uint8 Hi;
};

union tWB16{
   struct Byte uc;
   uint16 ush;
};

*/

struct HFTelIntern{
   uint8  ucId;
   uint8  ucP;
   sint8  scTWE;
   uint8  ucLifeTime;
   uint8  ucState;
   uint16 ushVehicleSpeed;
   sint8  scTa;
   uint8  ucKLState;
};

union HFTelAccess{
   struct HFTelIntern tHF;
   uint8              ucByte[(uint8) sizeof(struct HFTelIntern)];
};

struct SollDat{
   uint8  ucPSoll;
   sint8  scTSoll;
   uint16 ushMSoll;
};

struct LocalWarnDat{
   union  HFTelAccess tHFD;
   struct SollDat     tSD;
   uint8              ucCurWarnLevel;
   uint8              PRefMin;
   uint8              ucResetLvl;
};

extern void   ClearWarnBitWN (uint8  ucIdX, uint8  ucWarnTypeIx);
extern uint8  ucPfT          (uint16 ushM,  uint16 ushTabs);
extern uint8  ucGetWarnBitWN (uint8  ucIdX, uint8  ucWarnTypeIx);
extern uint8  ucSetWarnBitWN (uint8  ucIdX, uint8  ucWarnTypeIx);
extern uint16 ushMIso        (uint8  ucP,   sint8  scT);
