

#include "state_bz.h"
#include "state_bzX.h"
  #include "wallocX.h"

extern boolean GETbCalPminInvalidCAL( void );
extern boolean GETbCalReqCAL( void );
extern boolean GETbCalNotAck4PlausiCheckMFA( void );
extern void CheckDTCInactiveERR(void);
extern void InitIDOM(void);
extern uint8 ucGetHistoryState(void);

void InitBZ( void )
{
  uint8 ucWAState;

  if( GETbCalReqCAL() == TRUE )
  {
    SetBitBetriebszustandBZ(cCAL_REQUEST);
    InitIDOM();
  }

  (void) CheckDTCInactiveERR();

  ClearBitBetriebszustandBZ( cER_FINISH | cAL_RUNNING | cEIGENRAD | cZUGEORDNET | cHIST_PRELOAD | cZO_FINISH | cZO_TIMEOUT | cZO_ERROR | cTEILZUGEORDNET | cZO_Fallback2Hist);

  ucWAState =  ucGetHistoryState();
  if( (ucWAState & cHiStateZG) == cHiStateZG )
  {
    SetBitBetriebszustandBZ( cEIGENRAD | cZUGEORDNET | cHIST_PRELOAD );
  }
  else if( (ucWAState & cHiStateER) == cHiStateER )
  {
    SetBitBetriebszustandBZ( cEIGENRAD | cHIST_PRELOAD );
  }
}

void SetBitBetriebszustandBZ( uint16 ushBitMask )
{
   ushBetriebszustand |= ushBitMask;
}

void ClearBitBetriebszustandBZ( uint16 ushBitMask )
{
   ushBetriebszustand &= ~ushBitMask;
}

boolean bGetBitBetriebszustandBZ( uint16 ushBitMask )
{
   return (boolean) ((ushBetriebszustand & ushBitMask) != 0 );
}

uint16 ushGetBetriebszustandBZ( uint16 ushBitMask )
{
   return (ushBetriebszustand & ushBitMask);
}

uint8 ucGetBetriebszustandHByte(void)
{
return ((uint8) (ushBetriebszustand >>8));
}

uint8 ucGetBetriebszustandLByte(void)
{
return (( uint8) (ushBetriebszustand & 0x00FF ));
}

