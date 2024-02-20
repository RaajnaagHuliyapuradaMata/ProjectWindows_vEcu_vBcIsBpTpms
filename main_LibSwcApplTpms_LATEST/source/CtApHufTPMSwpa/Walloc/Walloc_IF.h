

#ifdef WAEEIFACE_H

#else

#include "Compiler_Cfg.h"
#include "cd_decoder_x.h"
#include "abs_linX.h"

#define WAEEIFACE_H

#define cWAParameter 8
#define cHistorySet1 9
#define cHistoryWPSet1 12

typedef tPreBuf tRFTelType;

#define cMaxTeLen sizeof(tRFTelType)

extern void GetWADataEE(unsigned char, unsigned char *, unsigned char);
extern void PutWADataEE(unsigned char, unsigned char *, unsigned char);

extern void WAStatusChangedEvent(unsigned short);
extern unsigned short ushGetABSingleTick(unsigned char ucIx);
extern unsigned char ucGetABSTick(unsigned short * );

extern unsigned char ucGetSpeed(void);
extern unsigned char ucNoWheelSensorMounted(void);

extern void SetWaData2NvmFlag(void);

extern unsigned char bGetABSSignalDTCActive(void);

extern unsigned char ucDAG_LQIParameter(void);

#endif
