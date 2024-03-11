

#ifndef _OSEKASM_H
#define _OSEKASM_H

#if defined __cplusplus
extern "C"
{
#endif

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

#ifndef osdNOASM

asm osuint32 osCheckIntDisabled(void){
%lab _osCheckIntDisabledExit
   stsr  PSW, r10                 -- r10 = PSW
   andi  0x20, r10, r10           -- r10 = r10 & 0x20
   cmp   r0, r10                  -- compare r10 != 0
   bne   _osCheckIntDisabledExit  -- if r10 != 0 then branch to _osCheckIntDisabledExit
   stsr  PMR, r10                 -- r10 = PMR
   mov   osdSystemLevelMask, r11  -- r11 = osdSystemLevelMask
   cmp   r11, r10                 -- compare r10 >= r11
   bnl   _osCheckIntDisabledExit  -- if r10 >= r11 then branch to _osCheckIntDisabledExit
   mov   r0, r10                  -- r10 = 0
_osCheckIntDisabledExit:
}

asm void osSetICRxMask(osuint32 addr){
%con addr
   stsr    PSW, r12    -- r12 = PSW
   di                  -- disable interrupts
   mov     addr, r11   -- r11 = addr
   set1    7, 0[r11]   -- set bit 8 at address = r11
   syncm               -- sync memory
   ldsr    r12, PSW    -- PSW = r12
%reg addr
   stsr    PSW, r12    -- r12 = PSW
   di                  -- disable interrupts
   set1    7, 0[addr]  -- set bit 8 at address = addr
   syncm               -- sync memory
   ldsr    r12, PSW    -- PSW = r12
%error
}

asm void osClearICRxMask(osuint32 addr){
%con addr
   stsr    PSW, r12    -- r12 = PSW
   di                  -- disable interrupts
   mov     addr, r11   -- r11 = addr
   clr1    7, 0[r11]   -- clear bit 8 at address = r11
   syncm               -- sync memory
   ldsr    r12, PSW    -- PSW = r12
%reg addr
   stsr    PSW, r12    -- r12 = PSW
   di                  -- disable interrupts
   clr1    7, 0[addr]  -- clear bit 8 at address = addr
   syncm               -- sync memory
   ldsr    r12, PSW    -- PSW = r12
%error
}

asm osuint32 osGetSPR(osuint32 regID, osuint32 groupID){
%con regID %con groupID
   stsr   regID, r10, groupID  -- r10 = SPR
%error
}

asm void osSetSPR(osuint32 regID, osuint32 groupID, osuint32 value){
%con regID %con groupID %con value
   mov    value, r11                -- r11 = value
   ldsr   r11, regID, groupID       -- SPR = r11
%con regID %con groupID %reg value
   ldsr   value, regID, groupID     -- SPR = value
%error
}

asm osuint32 osGetPSW(void){
   stsr   PSW, r10  -- r10 = PSW
}

asm void osSetPSW(osuint32 value){
%reg value
   ldsr   value, PSW  -- PSW = value
%con value
   mov    value, r11  -- r11 = value
   ldsr   r11, PSW    -- PSW = r11
%error
}

asm osuint32 osGetEIPSW(void){
   stsr   EIPSW, r10  -- r10 = EIPSW
}

asm void osSetEIPSW(osuint32 value){
%reg value
   ldsr   value, EIPSW  -- EIPSW = value
%con value
   mov    value, r11    -- r11 = value
   ldsr   r11, EIPSW    -- EIPSW = r11
%error
}

asm void osDispatch(void){
   nop                          -- improve interrupt latency
   trap 0                       -- trap exception
}

asm osuint8 osGetHighPrioBit(osuint32 pattern){
%con pattern
   mov    pattern, r10  -- r10 = pattern
   sch1l  r10, r10      -- get first bit from left which is set
   addi   -1, r10, r10  -- adjust position
%mem pattern
   ld.w   pattern, r10  -- r10 = pattern
   sch1l  r10, r10      -- get first bit from left which is set
   addi   -1, r10, r10  -- adjust position
%reg pattern
   sch1l  pattern, r10  -- get first bit from left which is set
   addi   -1, r10, r10  -- adjust position
%error
}

asm osuint32 osGetCurrentSP(void){
   mov   sp, r10  -- r10 = sp -> return value = sp
}

asm osuint32 osGetDisableGlobal(void){
   stsr  PSW, r10        -- r10 = PSW
   di                    -- disable global interrupts
   andi  0x20, r10, r10  -- r10 = r10 & 0x20
}

asm osuint32 osGetIntDisableFlag(void){
   stsr  PSW, r10        -- r10 = PSW
   andi  0x20, r10, r10  -- r10 = r10 & 0x20
}

asm osuint32 osGetIntDisableFlagEIPSW(void){
   stsr  EIPSW, r10      -- r10 = EIPSW
   andi  0x20, r10, r10  -- r10 = r10 & 0x20
}

asm osuint32 osGetDisableGlobalEIPSW(void){
   stsr  EIPSW, r11      -- r11 = EIPSW
   andi  0x20, r11, r10  -- r10 = r11 & 0x20
   ori   0x20, r11, r11  -- r11 = r11 | 0x20
   ldsr  r11, EIPSW      -- EIPSW = r11
}

asm void osEnableGlobalEIPSW(void){
   stsr  EIPSW, r11       -- r11 = EIPSW
   mov   0xFFFFFFDF, r12  -- r12 = 0xFFFFFFDF
   and   r12, r11         -- r11 = r11 & r12
   ldsr  r11, EIPSW       -- EIPSW = r11
}

asm osuint8 osAsmGetISPR(void){
   stsr   ISPR, r10  -- r10 = ISPR
}

asm osuint8 osAsmGetPMR(void){
   stsr   PMR, r10  -- r10 = PMR
}

asm void osSetPMR(osIntLevelType pattern){
%reg pattern
   stsr    PSW, r12      -- r12 = PSW
   di                    -- disable interrupts
   ldsr    pattern, PMR  -- PMR = pattern
   ldsr    r12, PSW      -- PSW = r12
%mem pattern
   stsr    PSW, r12      -- r12 = PSW
   di                    -- disable interrupts
   ld.w    pattern, r11  -- r11 = pattern
   ldsr    r11, PMR      -- PMR = r11
   ldsr    r12, PSW      -- PSW = r12
%error
}

asm osIntLevelType osGetLevelPMR(void){
   stsr    PSW, r12          -- r12 = PSW
   di                        -- disable interrupts
   stsr    PMR, r10          -- r10 = PMR
   mov     osdPMRHiBit, r11  -- r11 = osdPMRHiBit
   or      r11, r10          -- r10 = r10 | r11
   sch1r   r10, r10          -- get first bit from right which is set
   addi    -1, r10, r10      -- adjust position
   ldsr    r12, PSW          -- PSW = r12
}

asm osIntLevelType osGetLevelISPR(void){
   stsr    PSW, r12          -- r12 = PSW
   di                        -- disable interrupts
   stsr    ISPR, r10         -- r10 = ISPR
   mov     osdPMRHiBit, r11  -- r11 = osdPMRHiBit
   or      r11, r10          -- r10 = r10 | r11
   sch1r   r10, r10          -- get first bit from right which is set
   addi    -1, r10, r10      -- adjust position
   ldsr    r12, PSW          -- PSW = r12
}

asm void osSetLevelPMR(osIntLevelType prioLevel){
%reg prioLevel
   stsr    PSW, r12        -- r12 = PSW
   di                      -- disable interrupts
   mov     osdPMRMask, r11 -- r11 = osdPMRMask
   shr     prioLevel, r11  -- r11 = r11 >> prioLevel
   shl     prioLevel, r11  -- r11 = r11 << prioLevel
   ldsr    r11, PMR        -- PMR = prioLevel
   ldsr    r12, PSW        -- PSW = r12
%mem prioLevel
   stsr    PSW, r12        -- r12 = PSW
   di                      -- disable interrupts
   mov     osdPMRMask, r11 -- r11 = osdPMRMask
   ld.w    prioLevel, r10  -- r10 = prioLevel
   shr     r10, r11        -- r11 = r11 >> r10 = r11 >> prioLevel
   shl     r10, r11        -- r11 = r11 << r10 = r11 << prioLevel
   ldsr    r11, PMR        -- PMR = r11
   ldsr    r12, PSW        -- PSW = r12
%error
}

asm void osSetTaskLevel(void){
   stsr    PSW, r12  -- r12 = PSW
   di                -- disable interrupts
   ldsr    r0, PMR   -- PMR = r0 = 0
   ldsr    r12, PSW  -- PSW = r12
}

asm void osSetSystemLevel(void){
   stsr    PSW, r12                 -- r12 = PSW
   di                               -- disable interrupts
   mov     osdSystemLevelMask, r11  -- r11 = osdSystemLevelMask
   ldsr    r11, PMR                 -- PMR = r11
   ldsr    r12, PSW                 -- PSW = r12
}

asm osuint32 osGetDisableLevel(void){
   stsr    PSW, r12                 -- r12 = PSW
   di                               -- disable interrupts
   stsr    PMR, r10                 -- r10 = PMR
   mov     osdSystemLevelMask, r11  -- r11 = osdSystemLevelMask
   or      r10, r11                 -- r11 |= r10
   ldsr    r11, PMR                 -- PMR = r11
   ldsr    r12, PSW                 -- PSW = r12
}

asm void osRestoreLevel(void){
   stsr    PSW, r12                  -- r12 = PSW
   di                                -- disable interrupts

   mov     _ptrToSavedIntLevel_c0, r11  -- r11 = ptrToSavedIntLevel
   ld.w    0[r11], r11               -- r11 = *(uint32)r11 = &osCtrlVarsCore0.LockIsNotNeeded.ossSavedIntLevel
   ld.w    0[r11], r11               -- r11 = *(uint32)r11 = osCtrlVarsCore0.LockIsNotNeeded.ossSavedIntLevel
   ldsr    r11, PMR                  -- PMR = r11
   ldsr    r12, PSW                  -- PSW = r12
}

asm void osRestoreLevelNested(void){
   stsr    PSW, r12                        -- r12 = PSW
   di                                      -- disable interrupts

   mov     _ptrToSavedIntLevelNested_c0, r11  -- r11 = ptrToSavedIntLevelNested
   ld.w    0[r11], r11                     -- r11 = *(uint32*)r11 = &osCtrlVarsCore0.LockIsNotNeeded.ossSavedIntLevelNested
   ld.w    0[r11], r11                     -- r11 = *(uint32*)r11 = osCtrlVarsCore0.LockIsNotNeeded.ossSavedIntLevelNested
   ldsr    r11, PMR                        -- PMR = r11
   ldsr    r12, PSW                        -- PSW = r12
}

asm osuint32 osGetStackPattern(void){
   stsr   MPLA0, r10   -- r10 = MPLA0         -> get stack bottom address
   ld.w   0[r10], r10  -- r10 = *(uint32*)r10 -> get value at stack bottom address
}

#endif

#if defined __cplusplus
}
#endif

#endif

