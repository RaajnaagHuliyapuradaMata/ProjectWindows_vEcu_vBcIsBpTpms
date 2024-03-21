

#ifdef AEC_INT
void SetFrontBack(uint8 ucFrontIx, uint8 ucBackIx);

void SetFBPACM(uint8 ucFrontIx, uint8 ucBackIx,uint8 ucWrong);
void SetFBACM(uint8 ucFrontID, uint8 ucBackID,uint8 ucWrong);
 void ResetBadWayCheck(void);

#else
#ifdef CONCEPT4
extern uint16 ushMofID(uint8 ucIx);
extern uint16 ushDistInMSec(uint8 ucIx1, uint8 ucIx2);
extern uint8 ucGetBiggerM(uint8 ucIx1,uint8 ucIx2);
extern uint16 ushGetTruECt(tRFTelType * ptInputWA, uint8 ucIx);
extern void Concept4Op2(uint8 ucIx, uint16 ushCurECt);
#endif
extern void Concept5pb8(uint8 ucID, tRFTelType * ptInputWA);
extern uint8 ucEarlyEnd(uint8 ucIx);
extern void SetFrontBack(uint8 ucFrontIx, uint8 ucBackIx);
extern void SetFBPACM(uint8 ucFrontIx, uint8 ucBackIx,uint8 ucWrong);
extern void SetFBACM(uint8 ucFrontID, uint8 ucBackID,uint8 ucWrong);
 extern void ResetACM(void);
extern void CtACM(uint8 ucID1, uint8 ucID2);
extern uint8 ucAutoACM(void);
extern uint8 ucEarlyEnd(uint8 ucIx);
uint8 ucAutoACM(void);

extern uint8 ucDirectionDetection(uint8 ucLeRiMinDistance);
extern uint8 ucAxisDetection(void);
extern uint8 ucWPConsistent(void);

extern void BadWayCheck(uint8 ucPeaks, uint16 ushTime);
extern void ResetBadWayCheck(void);
extern void PutushMaxAxDist( uint16 ushVal);
extern void PutushMinAxDist( uint16 ushVal);
#endif
