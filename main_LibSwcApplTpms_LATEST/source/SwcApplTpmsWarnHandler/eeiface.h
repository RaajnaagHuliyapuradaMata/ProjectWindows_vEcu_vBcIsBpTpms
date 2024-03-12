#ifndef EEIFACE_H
#define EEIFACE_H

extern void GetDataEE(uint8, uint8 *, uint8);
extern void PutDataEE(uint8, const uint8 *, uint8);

#ifndef pb_ModulTest_02062003

#else
extern void ResetEEPROM(void);
extern void PRINT_EepromUsage(void);
#endif

#endif
