#pragma once

#if defined __cplusplus
extern "C"
{
#endif

#if defined USE_QUOTE_INCLUDES
#include "vrm.h"
#else
#include <vrm.h>
#endif

#define osdVrmMajRelNum 1
#define osdVrmMinRelNum 1

#if defined USE_QUOTE_INCLUDES
#include "vrm.h"
#else
#include <vrm.h>
#endif

#ifndef osdNOASM
extern osuint32       osCheckIntDisabled(void);
extern void           osSetICRxMask(osuint32 addr);
extern void           osClearICRxMask(osuint32 addr);
extern osuint32       osGetSPR(osuint32 regID, osuint32 groupID);
extern void           osSetSPR(osuint32 regID, osuint32 groupID, osuint32 value);
extern osuint32       osGetPSW(void);
extern void           osSetPSW(osuint32 value);
extern osuint32       osGetEIPSW(void);
extern void           osSetEIPSW(osuint32 value);
extern void           osDispatch(void);
extern osuint8        osGetHighPrioBit(osuint32 pattern);
extern osuint32       osGetCurrentSP(void);
extern osuint32       osGetDisableGlobal(void);
extern osuint32       osGetIntDisableFlag(void);
extern osuint32       osGetIntDisableFlagEIPSW(void);
extern osuint32       osGetDisableGlobalEIPSW(void);
extern void           osEnableGlobalEIPSW(void);
extern osuint8        osAsmGetISPR(void);
extern osuint8        osAsmGetPMR(void);
extern void           osSetPMR(osIntLevelType pattern);
extern osIntLevelType osGetLevelPMR(void);
extern osIntLevelType osGetLevelISPR(void);
extern void           osSetLevelPMR(osIntLevelType prioLevel);
extern void           osSetTaskLevel(void);
extern void           osSetSystemLevel(void);
extern osuint32       osGetDisableLevel(void);
extern void           osRestoreLevel(void);
extern void           osRestoreLevelNested(void);
extern osuint32       osGetStackPattern(void);
#endif

#if defined __cplusplus
}
#endif
