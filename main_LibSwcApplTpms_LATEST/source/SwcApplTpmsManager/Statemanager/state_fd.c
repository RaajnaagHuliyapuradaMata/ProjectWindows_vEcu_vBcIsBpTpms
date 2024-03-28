

#include "state_fd.h"
#define cFD_LEFT_RIGHT_DIFFERENCE      ((uint8) 0x01)
#define cFD_ABSOLUTE_PRESSURE_DIFF    ((uint8) 0x03)

void SetBitFillingDetectionStateFD(uint8);
void ClearBitFillingDetectionStateFD(uint8);
boolean bGetBitFillingDetectionStateFD(uint8);
uint8 Get_FD_STATUS(void);
void SetState2FillingDetectionStateFD(uint8);
void ClearFillingDetectionStateFD(void);
uint8 Get_FD_ABORT_REASON(void);
void SetBitAbortReasonFD(uint8);
void ClearBitAbortReasonFD(uint8);
void SetState2AbortReasonFD(uint8);
void ClearAbortReasonFD(void);
uint8 Get_FD_PLAUSIBILITY_FAILURE(void);
uint8 GetFD_PlausiFailure(void);
void SetState2PlausiFailureFD(uint8);
void ClearPlausiFailureLeftRightAbsFD(void);

void ClearPlausiFailureFD(void);

void  SetIdCol0New4FD(uint8);
uint8 GetIdCol0New4FD(void);
void  SetIdCol1New4FD(uint8);
uint8 GetIdCol1New4FD(void);
void  SetIdCol2New4FD(uint8);
uint8 GetIdCol2New4FD(void);
void  SetIdCol3New4FD(uint8);
uint8 GetIdCol3New4FD(void);

uint8 GetNewIdColX4FD(uint8);
uint8 ChkNewIdColX4FD(void);
void ClearNewIdColXMem4FD(uint8);

void SetBitFillingDetectionStateFD( uint8 ucBitMask ){
   ucFD_Status |= ucBitMask;
}

void ClearBitFillingDetectionStateFD( uint8 ucBitMask ){
   ucFD_Status &= ~ucBitMask;
}

boolean bGetBitFillingDetectionStateFD( uint8 ucBitMask ){
   return (boolean) ((ucFD_Status & ucBitMask) != 0 );
}

uint8 Get_FD_STATUS(void ){
   return ucFD_Status;
}

void SetState2FillingDetectionStateFD( uint8 ucState ){
   ucFD_Status = ucState;
}

void ClearFillingDetectionStateFD(void){
   ucFD_Status = FALSE;
}

uint8 Get_FD_ABORT_REASON(void){
   return ucFD_AbortReason;
}

void SetBitAbortReasonFD( uint8 ucBitMask ){
   ucFD_AbortReason |= ucBitMask;
}

void ClearBitAbortReasonFD( uint8 ucBitMask ){
   ucFD_AbortReason &= ~ucBitMask;
}

void SetState2AbortReasonFD( uint8 ucState ){
   ucFD_AbortReason = ucState;
}

void ClearAbortReasonFD(){
   ucFD_AbortReason =FALSE;
}

uint8 Get_FD_PLAUSIBILITY_FAILURE(void ){
   return ucFD_PlausiFailure;
}

void SetState2PlausiFailureFD( uint8 ucState ){
   ucFD_PlausiFailure = ucState;
}

void ClearPlausiFailureLeftRightAbsFD(void){
  ucFD_PlausiFailure &= ~cFD_ABSOLUTE_PRESSURE_DIFF;
   ucFD_PlausiFailure &= ~cFD_LEFT_RIGHT_DIFFERENCE;
}

void ClearPlausiFailureFD(void){
   ucFD_PlausiFailure =FALSE;
}

void SetIdCol0New4FD( uint8 ucCol ){
   ucIdCol0New4FD = ucCol;
}

uint8 GetIdCol0New4FD(void){
   return ucIdCol0New4FD;
}

void SetIdCol1New4FD( uint8 ucCol ){
   ucIdCol1New4FD = ucCol;
}

uint8 GetIdCol1New4FD(void){
   return ucIdCol1New4FD;
}

void SetIdCol2New4FD( uint8 ucCol ){
   ucIdCol2New4FD =ucCol;
}

uint8 GetIdCol2New4FD(void){
   return ucIdCol2New4FD;
}

void SetIdCol3New4FD( uint8 ucCol ){
   ucIdCol3New4FD = ucCol;
}

uint8 GetIdCol3New4FD(void){
   return ucIdCol3New4FD;
}

uint8 GetNewIdColX4FD( uint8 ucCol ){

uint8 ucReturnValue=FALSE;
  switch (ucCol){
      case cZOMPos0:
               ucReturnValue = ucIdCol0New4FD;
      break;
      case cZOMPos1:
               ucReturnValue = ucIdCol1New4FD;
      break;
      case cZOMPos2:
               ucReturnValue = ucIdCol2New4FD;
      break;
      case cZOMPos3:
              ucReturnValue = ucIdCol3New4FD;
      break;
      }

return ucReturnValue;
}

uint8 ChkNewIdColX4FD(void){
uint8 ucReturnValue=FALSE;
   if((ucIdCol0New4FD == TRUE) || (ucIdCol1New4FD == TRUE) || (ucIdCol2New4FD == TRUE) || (ucIdCol3New4FD == TRUE)){
      ucReturnValue=TRUE;
   }

return ucReturnValue;
}

void ClearNewIdColXMem4FD( uint8 ucCol ){

  switch (ucCol){
      case cZOMPos0:
               ucIdCol0New4FD=FALSE;
      break;
      case cZOMPos1:
               ucIdCol1New4FD=FALSE;
      break;
      case cZOMPos2:
               ucIdCol2New4FD=FALSE;
      break;
      case cZOMPos3:
              ucIdCol3New4FD=FALSE;
      break;
      }

}
