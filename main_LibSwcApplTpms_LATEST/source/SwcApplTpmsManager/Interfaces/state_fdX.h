#pragma once

#define cFD_DEFAULT                        ((uint8) 0x00)
#define cMFD_RUNNING                        ((uint8) 0x01)
#define cAFD_RUNNING2                      ((uint8) 0x02)
#define cAFD_RUNNING3                      ((uint8) 0x03)
#define cFILLING_DETECTED                  ((uint8) 0x04)
#define cFILLING_UNPLAUSIBLE            ((uint8) 0x05)
#define cFILLING_DETECT_ABORTED         ((uint8) 0x06)
#define cFILLING_NOT_DETECTED            ((uint8) 0x07)
#define cFD_MILEAGE2SMALL                  ((uint8) 0x08)
#define cFD_ACTIV_WARNING                  ((uint8) 0x09)
#define cFD_LTS30DAYS                        ((uint8) 0x0A)
#define cFD_RE_POS_CHANGE                  ((uint8) 0x0B)
#define cFD_INDEX_10                        ((uint8) 0x10)
#define cFD_INDEX_20                        ((uint8) 0x20)
#define cFD_INDEX_30                        ((uint8) 0x30)
#define cFD_DP_AUTO                            ((uint8) 0x01)
#define cFD_TIRE2HOT                        ((uint8) 0x02)
#define cFD_DP_STABI                        ((uint8) 0x03)
#define cFD_P_MIN_TIRE                     ((uint8) 0x04)
#define cFD_MISSING_SENSOR               ((uint8) 0x05)
#define cFD_TIMEOUT                           ((uint8) 0x06)
#define cFD_FBM_ACTIV                        ((uint8) 0x07)
#define cFD_LEFT_RIGHT_DIFFERENCE      ((uint8) 0x01)
#define cFD_ABSOLUTE_PRESSURE_DIFF    ((uint8) 0x03)
#define cFD_DP_MANUAL                        ((uint8) 0x04)
#define cFD_FALL_BACK_NOPOS               ((uint8) 0x05)
#define cFLAG_VL                              ((uint8) 0x01)
#define cFLAG_VR                               ((uint8) 0x02)
#define cFLAG_HL                               ((uint8) 0x04)
#define cFLAG_HR                               ((uint8) 0x08)

extern void ClearNewIdColXMem4FD(uint8);
extern uint8 GetNewIdColX4FD(uint8);
extern void  SetIdCol0New4FD(uint8);
extern uint8 GetIdCol0New4FD(void);
extern void  SetIdCol1New4FD(uint8);
extern uint8 GetIdCol1New4FD(void);
extern void  SetIdCol2New4FD(uint8);
extern uint8 GetIdCol2New4FD(void);
extern void  SetIdCol3New4FD(uint8);
extern uint8 GetIdCol3New4FD(void);
extern uint8 Get_FD_STATUS(void);
extern void SetBitFillingDetectionStateFD(uint8);
extern void ClearBitFillingDetectionStateFD(uint8);
extern boolean bGetBitFillingDetectionStateFD(uint8);
extern void SetState2FillingDetectionStateFD(uint8);
extern void ClearFillingDetectionStateFD(void);
extern uint8 Get_FD_ABORT_REASON(void );
extern void SetBitAbortReasonFD(uint8);
extern void ClearBitAbortReasonFD(uint8);
extern void SetState2AbortReasonFD(uint8);
extern void ClearAbortReasonFD(void);
extern uint8 Get_FD_PLAUSIBILITY_FAILURE(void );
extern void ClearPlausiFailureLeftRightAbsFD(void);
extern void SetBitPlausiFailureFD(uint8);
extern void ClearBitPlausiFailureFD(uint8);
extern void SetState2PlausiFailureFD(uint8);
extern void ClearPlausiFailureFD(void);
