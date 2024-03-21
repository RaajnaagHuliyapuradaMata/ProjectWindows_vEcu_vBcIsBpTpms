

#ifndef _eecatc_ifX_H
#define _eecatc_ifX_H

#include "tss_stdx.h"
struct tBitfeldKATC
 {
    boolean b7;
     boolean b6;
     boolean b5;
     boolean b4;
     boolean b3;
     boolean b2;
     boolean b1;
     boolean b0;
     boolean b15;
     boolean b14;
     boolean b13;
     boolean b12;
     boolean b11;
     boolean b10;
     boolean b9;
     boolean b8;
 };
 typedef struct typedef_struct_tMirroredRamCatC2Decl
{
  uint16 ushGutEmpfCnt[5];
  uint16 ushMissedCnt[5];

  uint16 ushResetCnt;

#if(BERU_BAUREIHE_BMW_PL4_ENABLE == ON)
  uint8 ucReserved[8];
#endif

}tMirroredRamCatC2Decl;

typedef struct typedef_struct_tMirroredRamCatC5Decl
{
  uint8 ucWAParaByte[sizeof(WAParameter)];

  uint8 ucId1e;
  uint8 ucId2e[22];
  uint8 ucId3e[1];
  uint8 ucId4e;
  uint8 ucId5e[2];
  uint8 ucId6e[8];

  uint8 ucReserved[8];

}tMirroredRamCatC5Decl;

extern void InitEECATC2( void );

extern void InitEECATC5( void );

extern void PUTushMissedCntEE( uint16 , uint8 );
extern uint16 GETushMissedCntEE( uint8 );

extern void PUTushGutEmpfCntEE( uint16 , uint8 );
extern uint16 GETushGutEmpfCntEE( uint8 );

extern void PUTucFolgeAusfallCntEE( uint8 , uint8 );
extern uint8 GETucFolgeAusfallCntEE( uint8 );

extern uint8 GETucCalRequestEE( void );
extern void PUTucCalRequestEE( uint8 );

extern uint8 GETucCalNotAckEE( void );
extern void PUTucCalNotAckEE( uint8 );

extern uint8 GETucId1e( void );
extern void PUTucId1e( uint8 );
extern uint8 GETucId2e( uint8 );
extern void PUTucId2e( uint8, uint8 );
extern uint8 GETucId3e( uint8 );
extern void PUTucId3e( uint8, uint8 );
extern uint8 GETucId4e( void );
extern void PUTucId4e( uint8 );
extern uint8 GETucId5e( uint8 );
extern void PUTucId5e( uint8, uint8 );
extern uint8 GETucId6e( uint8);
extern void PUTucId6e( uint8, uint8 );

extern void PUTtWAparam(uint8 , uint8 );
extern uint8 GETtWAparam(uint8 );
#endif
