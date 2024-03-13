

#ifndef _HUFE2EWRAPPER_H
#define _HUFE2EWRAPPER_H

#include "Platform_Types.h"
#include "Compiler_Cfg.h"
#include "E2E_P02.h"

 void HufE2EWrapperInit(void);
 uint8 ucHufE2EWrapperCheckWhlPlsCnt(uint8* data);
 uint8 ucHufE2EWrapperProtectTireState2(uint8* data);

#endif
