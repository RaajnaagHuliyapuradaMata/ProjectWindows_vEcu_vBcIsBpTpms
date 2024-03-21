

#ifndef _OSDERIVATIVES_H
#define _OSDERIVATIVES_H

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

#if defined USE_QUOTE_INCLUDES
#include "tcb.h"
#else
#include <tcb.h>
#endif

#ifdef osdRH850_E1L
#if defined USE_QUOTE_INCLUDES
#include "osRH850_E1L.h"
#else
#include <osRH850_E1L.h>
#endif
#endif

#ifdef osdRH850_E1M
#if defined USE_QUOTE_INCLUDES
#include "osRH850_E1M.h"
#else
#include <osRH850_E1M.h>
#endif
#endif

#ifdef osdRH850_F1L
#if defined USE_QUOTE_INCLUDES
#include "osRH850_F1L.h"
#else
#include <osRH850_F1L.h>
#endif
#endif

#ifdef osdRH850_F1M
#if defined USE_QUOTE_INCLUDES
#include "osRH850_F1M.h"
#else
#include <osRH850_F1M.h>
#endif
#endif

#ifdef osdRH850_F1H
#if defined USE_QUOTE_INCLUDES
#include "osRH850_F1H.h"
#else
#include <osRH850_F1H.h>
#endif
#endif

#ifdef osdRH850_D1L
#if defined USE_QUOTE_INCLUDES
#include "osRH850_D1L.h"
#else
#include <osRH850_D1L.h>
#endif
#endif

#ifdef osdRH850_D1M
#if defined USE_QUOTE_INCLUDES
#include "osRH850_D1M.h"
#else
#include <osRH850_D1M.h>
#endif
#endif

#ifdef osdRH850_P1M
#if defined USE_QUOTE_INCLUDES
#include "osRH850_P1M.h"
#else
#include <osRH850_P1M.h>
#endif
#endif

#if defined __cplusplus
}
#endif
#endif

