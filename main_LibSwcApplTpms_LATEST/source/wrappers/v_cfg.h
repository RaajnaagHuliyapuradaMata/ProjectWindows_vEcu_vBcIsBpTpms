

#if !defined(__V_CFG_H__)
#define __V_CFG_H__

#ifndef VGEN_GENY
#define VGEN_GENY
#endif

#ifndef GENy
#define GENy
#endif

#ifndef SUPPLIER_CANBEDDED
#define SUPPLIER_CANBEDDED                   30
#endif

#ifndef V_OSTYPE_AUTOSAR
#define V_OSTYPE_AUTOSAR
#endif

#ifndef C_CPUTYPE_32BIT
#define C_CPUTYPE_32BIT
#endif

#ifndef V_CPUTYPE_BITARRAY_32BIT
#define V_CPUTYPE_BITARRAY_32BIT
#endif

#ifndef C_CPUTYPE_LITTLEENDIAN
#define C_CPUTYPE_LITTLEENDIAN
#endif

#ifndef C_CPUTYPE_BITORDER_LSB2MSB
#define C_CPUTYPE_BITORDER_LSB2MSB
#endif

#ifndef V_DISABLE_USE_DUMMY_FUNCTIONS
#define V_DISABLE_USE_DUMMY_FUNCTIONS
#endif

#ifndef V_ENABLE_USE_DUMMY_STATEMENT
#define V_ENABLE_USE_DUMMY_STATEMENT
#endif

#ifndef C_COMP_GHS_RH850_RSCAN
#define C_COMP_GHS_RH850_RSCAN
#endif

#ifndef V_CPU_RH850
#define V_CPU_RH850
#endif

#ifndef V_COMP_GHS
#define V_COMP_GHS
#endif

#ifndef V_COMP_GHS_RH850
#define V_COMP_GHS_RH850
#endif

#ifndef V_PROCESSOR_F1L
#define V_PROCESSOR_F1L
#endif

#ifndef C_PROCESSOR_F1L
#define C_PROCESSOR_F1L
#endif

#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef VSTD_ENABLE_OSEK_INTCTRL
#define VSTD_ENABLE_OSEK_INTCTRL
#endif

#ifndef VSTD_DISABLE_DEBUG_SUPPORT
#define VSTD_DISABLE_DEBUG_SUPPORT
#endif

#ifndef VSTD_ENABLE_LIBRARY_FUNCTIONS
#define VSTD_ENABLE_LIBRARY_FUNCTIONS
#endif

#define VGEN_ENABLE_SYSSERVICE_ASRBSWM
#define VGEN_ENABLE_CCL_ASRCOMM
#define VGEN_ENABLE_SYSSERVICE_ASRECUM
#define VGEN_ENABLE_SYSSERVICE_ASRDET
#define VGEN_ENABLE_DIAG_ASRDEM
#define VGEN_ENABLE_DIAG_ASRDCM
#define VGEN_ENABLE_CAN_DRV
#define C_ENABLE_CAN_CHANNELS
#define V_BUSTYPE_CAN
#define VGEN_ENABLE_IF_ASRIFCAN
#define VGEN_ENABLE_GW_ASRPDUR
#define VGEN_ENABLE_IL_ASRCOM
#define VGEN_ENABLE_CCL_ASRSMCAN
#define VGEN_ENABLE_DRVCANTRANS_TJA1043ASR
#ifndef VGEN_ENABLE_DRVCANTRANS
#define VGEN_ENABLE_DRVCANTRANS
#endif

#define VGEN_ENABLE_NM_ASR_IF
#define VGEN_ENABLE_NM_ASR_CAN
#define VGEN_ENABLE_TP_ASRTPCAN

#ifndef kVNumberOfIdentities
#define kVNumberOfIdentities                 1
#endif

#ifndef tVIdentityMsk
#define tVIdentityMsk                        vuint8
#endif

#ifndef kVIdentityEcuMConfiguration
#define kVIdentityEcuMConfiguration          (vuint8) 0
#endif

#ifndef VSetActiveIdentity
#define VSetActiveIdentity(identityLog)
#endif

#ifndef V_ACTIVE_IDENTITY_MSK
#define V_ACTIVE_IDENTITY_MSK                1
#endif

#ifndef V_ACTIVE_IDENTITY_LOG
#define V_ACTIVE_IDENTITY_LOG                0
#endif

#ifndef V_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define V_ATOMIC_BIT_ACCESS_IN_BITFIELD      STD_OFF
#endif

#ifndef V_ATOMIC_VARIABLE_ACCESS
#define V_ATOMIC_VARIABLE_ACCESS             16
#endif

#ifndef C_CLIENT_DBAG
#define C_CLIENT_DBAG
#endif

#ifndef __CanStateManagerConfiguration__
#define __CanStateManagerConfiguration__
#endif

#ifndef kComNumberOfNodes
#define kComNumberOfNodes                    kVNumberOfIdentities
#endif

#ifndef ComSetCurrentECU
#define ComSetCurrentECU                     VSetActiveIdentity
#endif

#ifndef comMultipleECUCurrent
#define comMultipleECUCurrent                vActiveIdentityLog
#endif

#ifndef V_ENABLE_CAN_ASR_ABSTRACTION
#define V_ENABLE_CAN_ASR_ABSTRACTION
#endif

#ifndef VGEN_ENABLE_VSTDLIB
#define VGEN_ENABLE_VSTDLIB
#endif

#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
#if MAGIC_NUMBER != 268053767
      #error "The magic number of the generated file <C:\_TSS\DAG\MFA2\Target\Appl\GenData\v_cfg.h> is different. Please check time and date of generated files!"
#endif
#else
#define MAGIC_NUMBER 268053767
#endif
#endif
#endif
