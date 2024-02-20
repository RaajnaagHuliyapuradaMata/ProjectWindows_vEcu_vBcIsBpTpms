
#ifndef EEIFACE_H
#define EEIFACE_H

extern void GetDataEE(unsigned char, unsigned char *, unsigned char);
extern void PutDataEE(unsigned char, const unsigned char *, unsigned char);

#ifndef pb_ModulTest_02062003

#else
extern void ResetEEPROM(void);
extern void PRINT_EepromUsage(void);
#endif

#endif
