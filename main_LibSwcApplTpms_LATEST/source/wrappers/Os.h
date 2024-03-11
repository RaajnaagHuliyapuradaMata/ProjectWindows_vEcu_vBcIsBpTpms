

#ifndef _OS_H
#define _OS_H

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
 #include "Os_Cfg.h"
#else
 #include <Os_Cfg.h>
#endif

#if(osdTypeHeaderInclude != 0)
 #if defined USE_QUOTE_INCLUDES
  #include "Std_Types.h"
  #include "Rte_Type.h"
 #else
  #include <Std_Types.h>
  #include <Rte_Type.h>
 #endif
#endif

#if defined __cplusplus
extern "C"
{
#endif

 #if(osdUseTrustedFunctionStubs != 0) || (osdNeedIOCTypes != 0)
  #if defined USE_QUOTE_INCLUDES
   #include "usrostyp.h"
  #else
   #include <usrostyp.h>
  #endif
 #endif

#if defined __cplusplus
}
#endif

#endif

