
#ifndef OHDSCANSLAVE_CONFIG_H
#define OHDSCANSLAVE_CONFIG_H

#include "ComStack_Types.h"

#define OHDSCANSLAVE_CONFIG_VERSION         (0x010201u)

#define OHDSCANSLAVE_CYCLETIME               (10000u)

#define OHDSCANSLAVE_TIMER_MAX               (0xFFFFFFFFu)

#define OHDSCANSLAVE_TIMER_NS_PER_TICK       (125u)

#define OHDSCanSlave_Sync_DataID {225u,102u,230u,107u,235u,112u,240u,117u,245u,122u,250u,127u,4u,132u,9u,137u}

#define OHDSCanSlave_Fup_DataID {143u,78u,13u,199u,134u,69u,4u,190u,125u,60u,246u,181u,116u,51u,237u,172u}

#define OHDSCANSLAVE_VERSION_INFO_API        (STD_ON)

#define OHDSCANSLAVE_DEV_ERROR_DETECT        (STD_ON)

#define OHDSCANSLAVE_E2E_AR322SUPPORT       (STD_ON)

#endif
