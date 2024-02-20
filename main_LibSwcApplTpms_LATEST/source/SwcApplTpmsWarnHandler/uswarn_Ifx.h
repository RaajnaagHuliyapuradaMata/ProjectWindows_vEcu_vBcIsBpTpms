

#ifndef _uswarn_if_X_H
#define _uswarn_if_X_H

#include "wntypepar.h"
#include "uswarnX.h"

extern void UpdateDAGsOldOff(void);

extern void GetRatValOfId(uint8 uiHistCol, struct SollDat * p2RatVal);

extern const uint8 * GETpui82SysWP(void);

extern void CtFPLTimer(void);

extern uint8 Getui8PrefMinOfId(uint8 histCol);

extern uint8 Getui8AtmosphericP(void);

#endif

