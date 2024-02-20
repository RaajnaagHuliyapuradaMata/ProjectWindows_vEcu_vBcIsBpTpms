

#ifndef _state_fzz_H
#define _state_fzz_H

#include "tss_stdx.h"
static uint16 ushFahrzeugzustand;

static uint16 ushFzzCanSignalImplauState;
static uint16 ushFzzCanSignalTimeOutState;
static uint8 ucFzzState4MessageMemory;
static uint8 ucGlobWarnState4MessageMemory;

static boolean bChangeVehicleStandsStillFZZ(void);

#endif

