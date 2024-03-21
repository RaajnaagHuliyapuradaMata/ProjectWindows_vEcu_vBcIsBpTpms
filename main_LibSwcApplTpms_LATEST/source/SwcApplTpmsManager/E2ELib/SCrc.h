

#if(!defined SCRC_H)
#define SCRC_H

#include <Std_Types.h>
#include <SCrc_LocalSrcCfg.h>

#if(defined SCRC_VENDOR_ID)
#error SCRC_VENDOR_ID is already defined
#endif

#define SCRC_VENDOR_ID         1U

#if(defined SCRC_SW_MAJOR_VERSION)
#error SCRC_SW_MAJOR_VERSION already defined
#endif

#define SCRC_SW_MAJOR_VERSION  2U

#if(defined SCRC_SW_MINOR_VERSION)
#error SCRC_SW_MINOR_VERSION already defined
#endif

#define SCRC_SW_MINOR_VERSION  0U

#if(defined SCRC_SW_PATCH_VERSION)
#error SCRC_SW_PATCH_VERSION already defined
#endif

#define SCRC_SW_PATCH_VERSION  2U

#endif

