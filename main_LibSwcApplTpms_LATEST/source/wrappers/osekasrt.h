

#ifndef _OSEKASRT_H
#define _OSEKASRT_H

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

#define osd_FILE_Cast

#if osdErrorHook
#define osAssertFailed_(x) osOwnCcb->LockIsNotNeeded.ossLastError = (osuint16) (x); osAssertFailed()
#else
#define osAssertFailed_(x) osAssertFailed()
#endif

#if((STATUS_LEVEL == EXTENDED_STATUS) && (osdEnableAssertions))
#define osSysErrAssertFailed(x)  {\
                                    osDisableGlobal();\
                                    osAssertFailed_(x);\
                                 }

#define osSysErrAssert(p, x) if((p) == 0)\
                                 {\
                                    osSysErrAssertFailed(x)\
                                 }
#else
#define osSysErrAssert(p, x)
#define osSysErrAssertFailed(x)
#endif

#if osdErrorHook
#define osAPIError(x, y)                                    \
      osOwnCcb->LockIsNotNeeded.ossLastError = (osuint16) (y); \
      osErrorHook((StatusType) (x))
#else
#define osAPIError(x, y)
#endif
#endif

