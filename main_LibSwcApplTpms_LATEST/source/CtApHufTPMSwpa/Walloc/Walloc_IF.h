

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

extern void GetWADataEE(uint8, uint8 *, uint8);
extern void PutWADataEE(uint8, uint8 *, uint8);

extern void WAStatusChangedEvent(uint16);
extern uint16 ushGetABSingleTick(uint8 ucIx);
extern uint8 ucGetABSTick(uint16 * );

extern uint8 ucGetSpeed(void);
extern uint8 ucNoWheelSensorMounted(void);

extern void SetWaData2NvmFlag(void);

extern uint8 bGetABSSignalDTCActive(void);

extern uint8 ucDAG_LQIParameter(void);

#endif
