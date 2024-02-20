

#if !defined(__COMSTACK_TYPES_H__)
#define __COMSTACK_TYPES_H__

# include "Std_Types.h"

# define COMMONASR__COMMON_IMPL_COMSTACKTYPES_VERSION 0x0305
# define COMMONASR__COMMON_IMPL_COMSTACKTYPES_RELEASE_VERSION 0x01

#  define COMSTACKTYPE_AR_MAJOR_VERSION       (2u)
#  define COMSTACKTYPE_AR_MINOR_VERSION       (2u)
#  define COMSTACKTYPE_AR_PATCH_VERSION       (1u)

# define COMSTACKTYPE_SW_MAJOR_VERSION       (3u)
# define COMSTACKTYPE_SW_MINOR_VERSION       (5u)
# define COMSTACKTYPE_SW_PATCH_VERSION       (1u)

# define COMSTACKTYPE_VENDOR_ID              (30u)

# define NTFRSLT_OK                        0x00
# define NTFRSLT_E_NOT_OK                  0x01
# define NTFRSLT_E_TIMEOUT_A               0x02
# define NTFRSLT_E_TIMEOUT_BS              0x03
# define NTFRSLT_E_TIMEOUT_CR              0x04
# define NTFRSLT_E_WRONG_SN                0x05
# define NTFRSLT_E_INVALID_FS              0x06
# define NTFRSLT_E_UNEXP_PDU               0x07
# define NTFRSLT_E_WFT_OVRN                0x08
#  define NTFRSLT_E_NO_BUFFER              0x09
#  define NTFRSLT_E_CANCELATION_OK         0x0A
#  define NTFRSLT_E_CANCELATION_NOT_OK     0x0B

# define NTFRSLT_PARAMETER_OK              0x0D
# define NTFRSLT_E_PARAMETER_NOT_OK        0x0E
# define NTFRSLT_E_RX_ON                   0x0F
# define NTFRSLT_E_VALUE_NOT_OK            0x10

# define BUSTRCV_OK         0x00

# define BUSTRCV_E_OK       0x00
# define BUSTRCV_E_ERROR    0x01

# define TPPARAMTYPE_CANTP_STMIN                100u
# define TPPARAMTYPE_CANTP_BS                   101u

# define TPPARAMTYPE_FRTP_BC                    150u
# define TPPARAMTYPE_FRTP_BFS                   151u
# define TPPARAMTYPE_FRTP_MAX_WFT               152u
# define TPPARAMTYPE_FRTP_MAX_RETRIES           153u

# define TPPARAMTYPE_FRTP_TA                    160u
# define TPPARAMTYPE_FRTP_SA                    161u
# define TPPARAMTYPE_FRTP_NUM_TX_PDUS_TO_USE    162u
# define TPPARAMTYPE_FRTP_BW_LIMITATION         163u
# define TPPARAMTYPE_FRTP_MAX_TX_PDU_LEN        164u

typedef uint16 PduIdType;
typedef uint16 PduLengthType;

typedef  P2VAR(uint8, TYPEDEF, AUTOSAR_COMSTACKDATA) SduDataPtrType;
typedef struct
{
  SduDataPtrType SduDataPtr;
  PduLengthType SduLength;
} PduInfoType;

typedef enum
{
  BUFREQ_OK,
  BUFREQ_E_NOT_OK,
  BUFREQ_E_BUSY,
  BUFREQ_E_OVFL
} BufReq_ReturnType;

typedef uint8        NotifResultType;

typedef uint8        BusTrcvErrorType;

typedef uint8        NetworkHandleType;

typedef uint8        PNCHandleType;

typedef enum
{
  TP_DATACONF,
  TP_DATARETRY,
  TP_CONFPENDING,
  TP_NORETRY
} TpDataStateType;

typedef struct
{
  TpDataStateType TpDataState;
  PduLengthType TxTpDataCnt;
} RetryInfoType;

typedef uint8        TPParameterType;

#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 268053767
      #error "The magic number of the generated file <C:\_TSS\DAG\MFA2\Target\Appl\GenData\ComStack_Types.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 268053767
#endif
#endif

#endif
