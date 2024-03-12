

#ifndef _PAL_LOCATE_STATISTIC_H
# define _PAL_LOCATE_STATISTIC_H

#include "Platform_Types.h"

void PutPalLocateStatistics2Ram(void);
void PutPalStatsLastCycleWU2Ram(void);
uint8* GetPalLocateStatistics(void);
uint8 GetucFullLocFailureCnt(void);
uint8* GetPalStatsLastCycleWU(uint8 ucColPos);
uint8* GetPalStatsLongTermWU(uint8 ucColPos);
void ClearPalLocateStatistics(void);
void ClearStatsLastCycleWU(void);
void ClearStatsLongTermWU(void);
void ClearStatsLongTermWUx(uint8 j);
void ClearStatsLastCycleWUx(uint8 j);

#endif