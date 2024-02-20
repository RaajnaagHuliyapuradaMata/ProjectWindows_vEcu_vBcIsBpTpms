#ifndef _HMI_HANDLER_X_H
# define _HMI_HANDLER_X_H

#include "Platform_Types.h"
#include "Compiler_Cfg.h"
#include "rte_type.h"

void UpdateTxBusMsg(void);
void InitTxBusMsg (void);
void setTireStatMsgDispRestart(void);
void clearTireStatMsgDispRestart(void);
void setHmiGlobalSensorState(uint8 ucSensorState);

void    updateHoldOff4Pmin(void);
void    updateHoldOffWarning(void);
boolean bHoldOffWarningEnabled(void);
void    SetPminDetected(boolean ucInput);
boolean GetPminDetected(void);

void setHMITirePress(uint8 ucPos, uint8 ucRawPressVal);
void setHMITireTemp(uint8 ucPos, uint8 ucRawTempVal);
extern uint8 ucGetHMICurrentTirePress(uint8 ucPos);
extern uint8 ucGetHMICurrentTireStat(uint8 ucPos);
extern uint8 ucGetHMICurrentTireTemp(uint8 ucPos);
extern uint8 ucGetHMICurrentTireTempStat(uint8 ucPos);

extern uint8 ucGetHMITPMMsgDisp(void);
extern uint8 ucGetHMITPMStat(void);
extern uint8 ucGetHMITPMWarnDisp(void);
extern DC_BOOL bGetHMITPMIndLmpOn(void);
extern DC_BOOL bGetHMITPMMalfLmpOn(void);
extern DC_BOOL bGetHMITirePressAvlBit(void);
extern uint8 ucGetHMITireTempWarnDisp(void);

extern REC_TPM_Lmp_On_Rq_Pr2_cp6wyrd9cg7ec7y2w3khz1gyt* pGetTpmLmpOnRq(void);
extern REC_TPM_Lmp_On_Rq_old*                           pGetTpmLmpOnRqOld(void);
extern REC_Tire_Stat_V2*                                pGetTireStat(void);
extern REC_Tire_Temp_V2*                                pGetTireTemp(void);
extern REC_RefPress*                                    pGetHmiRefPress(void);

uint8   ucGetHMIWakeUpRsn(void);
boolean bGetHMIAwakeDiagActv(void);
boolean bGetHMIAwakeIgnitionOn(void);
boolean bGetHMIAwakeNwSt(void);
uint8   bGetHMIAwakeWarnActv(void);
void    InitHMIAfterKL15On(void);
void    InitHMIAfterKL15Off(void);
void    InitHMIAfterSetIDsOverDiag(void);
void    ClearTPM_StatNoSensors(void);
void    ClearTPM_StatSensorsMissing(void);
void    ClearTPM_MsgDispRqSensorsMissing(void);
void    ClearTPM_MsgDispRqNoSensors(void);
uint8   GetCurUsedWPOfCol(uint8 ucCol);

#endif
