
#ifndef _USWARNDEFH
#define _USWARNDEFH

extern unsigned char  ucGetWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx);
extern void ClearWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx);
extern unsigned char ucSetWarnBitWN(unsigned char ucIdX, unsigned char ucWarnTypeIx);
extern unsigned char ucPfT(unsigned short ushM, unsigned short ushTabs);

extern unsigned char ucGetWarnType(unsigned char ucWarnTypeIx);
extern void USWPostInit(void);

extern unsigned short ui16MIsoRel(unsigned char ucPrel, signed char scT);

struct Byte
{
   unsigned char Lo;
   unsigned char Hi;
};

union tWB16
{
   struct Byte uc;
   unsigned short ush;
};

struct SollDat
{
  unsigned char ucPSoll;
  signed char scTSoll;
  unsigned short ushMSoll;
};

struct HFTelIntern
{
      unsigned char ucId;
    unsigned char ucP;
    signed char scTWE;
    unsigned char ucLifeTime;
    unsigned char ucState;
    unsigned short ushVehicleSpeed;
    signed char scTa;
    unsigned char ucKLState;
};

union HFTelAccess
{
  struct HFTelIntern tHF;
  unsigned char ucByte[(unsigned char) sizeof(struct HFTelIntern)];
};

struct LocalWarnDat
{
  union HFTelAccess tHFD;
  struct SollDat tSD;
   unsigned char ucCurWarnLevel;
  unsigned char PRefMin;
  unsigned char ucResetLvl;
};

#define ucPResInMBarc  25
#define uc1Barc (unsigned char) 40
#define ush273Kelvinc 273
#define sc40Gradc 40
#define scMinus20Gradc -20

#define ucIsoClearc (unsigned char) 0x20
#define ucNegHysc    (unsigned char) 0x80
#define ucPRecResetc (unsigned char) 0x02
#define ucUSCodec (unsigned char) 0x04
#define ucCtryMaskc (unsigned char) 0x0C

#endif
