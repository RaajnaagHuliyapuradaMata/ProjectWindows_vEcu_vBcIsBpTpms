

#if !defined (NM_STACK_TYPES_H)
#define NM_STACK_TYPES_H

#include "Std_Types.h"

#define NM_STACKTYPES_MAJOR_VERSION   (0x02u)
#define NM_STACKTYPES_MINOR_VERSION   (0x27u)
#define NM_STACKTYPES_PATCH_VERSION   (0x01u)

#define NM_COORD_BIT_PRIO_POS         (1u)
#define NM_COORD_BIT_SLEEP            (0x08u)
#define NM_COORD_BIT_PRIO_MASK        (0x06u)
#define NM_COORD_BIT_MASK             (0x0Eu)
#define NM_COORD_BIT_INV_MASK         (0xF1u)

#define NM_E_OK                       ((uint8)E_OK)
#define NM_E_NOT_OK                   ((uint8)E_NOT_OK)
#define NM_E_NOT_EXECUTED             ((uint8)2u)

typedef uint8 Nm_ReturnType;

typedef enum
{
  NM_STATE_UNINIT                 = 0u,
  NM_STATE_BUS_SLEEP              = 1u,
  NM_STATE_PREPARE_BUS_SLEEP      = 2u,
  NM_STATE_READY_SLEEP            = 3u,
  NM_STATE_NORMAL_OPERATION       = 4u,
  NM_STATE_REPEAT_MESSAGE         = 5u,
  NM_STATE_SYNCHRONIZE            = 6u,
  NM_STATE_WAIT_CHECK_ACTIVATION  = 7u,
  NM_STATE_WAIT_NETWORK_STARTUP   = 8u,
  NM_STATE_BUS_OFF                = 9u
} Nm_StateType;

typedef enum
{
  NM_MODE_BUS_SLEEP           = 0u,
  NM_MODE_PREPARE_BUS_SLEEP   = 1u,
  NM_MODE_SYNCHRONIZE         = 2u,
  NM_MODE_NETWORK             = 3u
} Nm_ModeType;

#endif

