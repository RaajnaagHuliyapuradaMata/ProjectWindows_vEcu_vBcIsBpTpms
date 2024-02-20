

#include "state_zk.h"
 #include "state_zkX.h"

extern boolean GETbCalPminInvalidCAL( void );

void InitZK( void )
{
  ClearBitZustandskennungZK( cZK_ALLE_BITS );

  SetCalNotAckZK();
 }

void SetBitZustandskennungZK( uint16 ushBitMask )
{
   ushZustandskennung |= ushBitMask;
}

void ClearBitZustandskennungZK( uint16 ushBitMask )
{
   ushZustandskennung &= ~ushBitMask;
}

boolean bGetBitZustandskennungZK( uint16 ushBitMask )
{
   return (boolean) ((ushZustandskennung & ushBitMask) != 0 );
}

uint16 ushGetZustandskennungZK( uint16 ushBitMask )
{
   return (ushZustandskennung & ushBitMask);
}

void SetChangedBit4WP( uint8 ucWP)
{

  switch (ucWP)
  {
    case (uint8) 0:
    {
      ushZustandskennung |= cPOS_CHANGED_VL;
      break;
    }
    case (uint8) 1:
    {
      ushZustandskennung |= cPOS_CHANGED_VR;
      break;
    }
    case (uint8) 2:
    {
      ushZustandskennung |= cPOS_CHANGED_HL;
      break;
    }
    case (uint8) 3:
    {
      ushZustandskennung |= cPOS_CHANGED_HR;
      break;
    }
    default:
    {
      ushZustandskennung |= (cPOS_CHANGED_VL | cPOS_CHANGED_VR | cPOS_CHANGED_HL| cPOS_CHANGED_HR);
      break;
    }
  }

}

void SetCalNotAckZK( void )
{
#ifdef cal_plausi_axes_invalid_110606
  if( GETbCalVaInvalidCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_P_VA_INVALID );
  }else{
    ClearBitZustandskennungZK( cCAL_P_VA_INVALID );
  }

  if( GETbCalHaInvalidCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_P_HA_INVALID );
  }else{
    ClearBitZustandskennungZK( cCAL_P_HA_INVALID );
  }
#endif

  if( GETbCalPminInvalidCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_P_MIN_INVALID );
  }else{
    ClearBitZustandskennungZK( cCAL_P_MIN_INVALID );
  }

#ifdef cal_EvCalTimeout_110606
  if( GETbCalTioCAL() == TRUE )
  {
    SetBitZustandskennungZK( cCAL_TIO );
  }else{
    ClearBitZustandskennungZK( cCAL_TIO );
  }
#endif
}

