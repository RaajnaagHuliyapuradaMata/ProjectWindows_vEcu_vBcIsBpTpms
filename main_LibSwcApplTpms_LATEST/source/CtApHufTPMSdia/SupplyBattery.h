

#ifndef _SUPPLYBATTERY_H
# define _SUPPLYBATTERY_H

#include "Platform_Types.h"

#define cKL30_HIGH_LIMIT            (uint16) 160
#define cKL30_LOW_LIMIT               (uint16) 90
#define cKL30_LOW_LOW_LIMIT         (uint16) 75

#define cKL30_HIGH_LIMIT_RES      (uint16) 155
#define cKL30_LOW_LIMIT_RES         (uint16) 95

#define cKL30_HIGH_LIMIT_KAZ      (uint8) 75
#define cKL30_LOW_LIMIT_KAZ         (uint8) 75
#define cKL30_LOW_LOW_LIMIT_KAZ   (uint8) 2

#define cPN14_SUPBAT_INVALID                  (uint8) 255

#define cPN14_SUPBAT_HIGH_LIMIT               (uint8) 160
#define cPN14_SUPBAT_LOW_LIMIT               (uint8) 90
#define cPN14_SUPBAT_LOW_LOW_LIMIT         (uint8) 75

#define cPN14_SUPBAT_HIGH_LIMIT_RES         (uint8) 155
#define cPN14_SUPBAT_LOW_LIMIT_RES         (uint8) 95

#define cPN14_SUPBAT_HIGH_LIMIT_KAZ         (uint8) 75
#define cPN14_SUPBAT_LOW_LIMIT_KAZ         (uint8) 75
#define cPN14_SUPBAT_LOW_LOW_LIMIT_KAZ   (uint8) 2

void CheckADCvalue4Kl30Diagnostic(uint16);
void CheckPN14SupBatState4SupplybatterieDiagnostic(uint8);
uint8 GetEvKl30DiagUnterSpgFZZ(void);

#endif