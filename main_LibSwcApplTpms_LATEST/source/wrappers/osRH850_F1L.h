

#ifndef _OSRH850_F1L_H
#define _OSRH850_F1L_H

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

#define osdOSTMBaseAddr   0xFFEC0000UL

#define osdICRBASE0       0xFFFF9000UL
#define osdICRBASE1       0xFFFFA000UL
#define osdIMRBASE0       0xFFFF90F0UL
#define osdIMRBASE1       0xFFFFA400UL

#define osdMPUSupportInSVMode 0

#if defined USE_QUOTE_INCLUDES
#include "osINTC2.h"
#else
#include <osINTC2.h>
#endif

#define osSysGetCoreID()  0
#define osHwCoreID()      osdOnCore

#if defined __cplusplus
}
#endif
#endif

