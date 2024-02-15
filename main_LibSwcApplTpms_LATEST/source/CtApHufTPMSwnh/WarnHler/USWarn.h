/*
(c) Beru Electronics GmbH     BEE1     11/2002
================================================================================================

project:       TSS VW PQ46

file name:     USWarn.h

file status:   under construction

------------------------------------------------------------------------------------------------

author:        Peter Brand                Beru Electronics GmbH

intials:       pb

*/
#ifndef _USWARNDEFH
#define _USWARNDEFH
/*
Modul Description
*/
/*
Global description:
headerfile for uswarn.c
Purpose:

*/
/*
Modul Modification
*/
/*
changes in 2002
*/
/*
21.11.2002 pb - 1st established

*/
/*
Declaration
*/
/*
Include
*/

/*
Prototypes
*/

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
		unsigned char ucId;			  /* 0..ucSumWEc 0 */
    unsigned char ucP;			  /* 0..255, pressure value in ucPResInMBarc 1 */
    signed char scTWE;			  /* -40..80, temperature WE in centigrade 2 */
    unsigned char ucLifeTime;	/* remaining lifeTime in months 3 */
    unsigned char ucState;		/* 1 normal sendmode of  WE, 2 fast with pressure loss 4 */
    unsigned short ushVehicleSpeed;/* 0..65535 speed in 1 km/h 5 */
    signed char scTa;			    /* -40..80 outside temperature in centigrade 7 */
    unsigned char ucKLState;	/* bit0 = kl15, bit1 = kl61 8 */
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
/*
Macros
*/

/* general settings */
#define ucPResInMBarc  25
#define uc1Barc (unsigned char) 40 /* ((1000) / (ucPResInMBarc)) */
#define ush273Kelvinc 273
#define sc40Gradc 40 /* 1/centigrade */
#define scMinus20Gradc -20 /* 1/centigrade */


/* ucWarnState bit interpretation */
#define ucIsoClearc (unsigned char) 0x20
#define ucNegHysc    (unsigned char) 0x80  /*in ucWarnStateWN only*/
#define ucPRecResetc (unsigned char) 0x02  /*in ucWarnStateWN only*/
#define ucUSCodec (unsigned char) 0x04
#define ucCtryMaskc (unsigned char) 0x0C



/*
Data
*/


/*
Implementation
*/

#endif /*_USWARNDEFH*/
