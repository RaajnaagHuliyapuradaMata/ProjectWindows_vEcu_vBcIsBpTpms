

#ifndef _OSEKCOV_H
#define _OSEKCOV_H

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

#if defined osdEnableCoverage

   #define osdCoverageArraySize ((1453 / 8) + 1)

   osqRAM0 extern osqRAM1 osqRAM2 volatile osuint8 osqRAM3 osCoverage[osdCoverageArraySize];

   #define COVER(x)                                   osCoverage[(x) >> 3U] |= (0x1U << ((x) & 0x7U));
   #define ELSEWITHCOVER(x)                           else { COVER(x) }

   #define IFCOVER(expr1,x1,x2)                       { if((expr1)==osdTRUE) { COVER(x1) } else { COVER(x2) } }

   #define IF2ORCOVER(expr1,expr2,x1,x2,x3)           { if(((expr1)==osdFALSE) && ((expr2)==osdFALSE)) { COVER(x1) } \
                                                        if(((expr1)==osdFALSE) && ((expr2)==osdTRUE )) { COVER(x2) } \
                                                        if(((expr1)==osdTRUE )                       ) { COVER(x3) } }

   #define IF2ANDCOVER(expr1,expr2,x1,x2,x3)          { if(((expr1)==osdTRUE ) && ((expr2)==osdTRUE )) { COVER(x1) } \
                                                        if(((expr1)==osdTRUE ) && ((expr2)==osdFALSE)) { COVER(x2) } \
                                                        if(((expr1)==osdFALSE)                       ) { COVER(x3) } }

   #define IF3ORCOVER(expr1,expr2,expr3,x1,x2,x3,x4)  { if(((expr1)==osdFALSE) && ((expr2)==osdFALSE) && ((expr3)==osdFALSE)) { COVER(x1) } \
                                                        if(((expr1)==osdFALSE) && ((expr2)==osdFALSE) && ((expr3)==osdTRUE )) { COVER(x2) } \
                                                        if(((expr1)==osdFALSE) && ((expr2)==osdTRUE )                       ) { COVER(x3) } \
                                                        if(((expr1)==osdTRUE )                                              ) { COVER(x4) } }

   #define IF3ANDCOVER(expr1,expr2,expr3,x1,x2,x3,x4) { if(((expr1)==osdTRUE ) && ((expr2)==osdTRUE ) && ((expr3)==osdTRUE )) { COVER(x1) } \
                                                        if(((expr1)==osdTRUE ) && ((expr2)==osdTRUE ) && ((expr3)==osdFALSE)) { COVER(x2) } \
                                                        if(((expr1)==osdTRUE ) && ((expr2)==osdFALSE)                       ) { COVER(x3) } \
                                                        if(((expr1)==osdFALSE)                                              ) { COVER(x4) } }

#else

   #define COVER(x)
   #define ELSEWITHCOVER(x)
   #define IFCOVER(expr1,x1,x2)
   #define IF2ORCOVER(expr1,expr2,x1,x2,x3)
   #define IF2ANDCOVER(expr1,expr2,x1,x2,x3)
   #define IF3ORCOVER(expr1,expr2,expr3,x1,x2,x3,x4)
   #define IF3ANDCOVER(expr1,expr2,expr3,x1,x2,x3,x4)
#endif

#endif

