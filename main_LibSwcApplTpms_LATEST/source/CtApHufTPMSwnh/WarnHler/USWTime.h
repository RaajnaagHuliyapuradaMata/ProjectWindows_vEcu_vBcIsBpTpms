/***************************************************************************************************
(c) Beru Electronics GmbH     BEE1     01/2003
================================================================================================

project:       TSS VW PQ46

file name:     USWTime.h

file status:   under construction

------------------------------------------------------------------------------------------------

author:        Peter Brand                Beru Electronics GmbH

intials:       pb


Modul Description

Global description:
prototypes, consts, data used by MORE the 1 submodule of  uswarnmodul and cannot be allocated to a
specific submodul.
Only uswarnmodul internal use!!



Modul Modification

changes in 2003

02.06.2003 pb - 1st established

***************************************************************************************************/

/*
Declaration
*/
/*
Include
*/


/*************************************************************
Prototypes
*/

/*************************************************************
Macros
*/

/*
Data
*/
#ifndef USWTime_H
#define USWTime_H
extern void ResetUSWTime(void);
extern void StopFilterSTWT( void );
extern unsigned char ucStartFilterSTWT( unsigned short);
extern unsigned char ucStartFilterHDWT(  unsigned short);
extern void StopFilterHDWT( void );
extern uint8 ui8HWTimerExpired(void);
extern uint8 ui8SWTimerExpired(void);
extern uint8 ui8KL15OFFnXsec(void);
#endif
/*
Implementation
*/
