/**
 * \file
 *
 * \brief AUTOSAR E2EP02
 *
 * This file contains the implementation of the AUTOSAR
 * module E2EP02.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <E2E_P02.h>       /* E2E Profile 2         */
#include <SCrc_CRC8H2F.h>  /* SCrc routine CRC8H2F  */

/*==================[macros]=================================================*/

#if (defined E2EP02_CRC_STARTVALUE) /* to prevent double declaration */
#error E2EP02_CRC_STARTVALUE is already defined
#endif /* #if (defined E2EP02_CRC_STARTVALUE) */

/** \brief Start value for Crc calculation */
#define E2EP02_CRC_STARTVALUE 0xFFU

#if (defined E2EP02_COUNTER_MAX) /* to prevent double declaration */
#error E2EP02_COUNTER_MAX is already defined
#endif /* #if (defined E2EP02_COUNTER_MAX) */

/** \brief Maximum allowed counter value for E2E Profile 02 */
#define E2EP02_COUNTER_MAX 15U

#if (defined E2EP02_DATALENGTH_MAX) /* to prevent double declaration */
#error E2EP02_DATALENGTH_MAX is already defined
#endif /* #if (defined E2EP02_DATALENGTH_MAX) */

/** \brief Maximum allowed data length for E2E Profile 02 in bits */
#define E2EP02_DATALENGTH_MAX 2048U

#if (defined E2EP02_DATALENGTH_MIN) /* to prevent double declaration */
#error E2EP02_DATALENGTH_MIN is already defined
#endif /* #if (defined E2EP02_DATALENGTH_MIN) */

/** \brief Minimum allowed data length for E2E Profile 02 in bits
 * shall be a multiple of 8 */
#define E2EP02_DATALENGTH_MIN 16U

/*==================[type definitions]=======================================*/

/*==================[internal function declarations]=========================*/

#define E2E_START_SEC_CODE
#include <MemMap.h>

/**
 * \brief Perform null pointer checks of the input parameters of the Protect function
 *
 * \param[in] Config Pointer to static configuration.
 * \param[in] State  Pointer to port/data communication state.
 * \param[in] Data   Pointer to Data to be protected.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectNullPtrChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);

/**
 * \brief Perform input parameter checks of the Config parameter of the Protect function
 *
 * \param[in] Config Pointer to static configuration.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectConfigParamChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config
);

/**
 * \brief Perform input parameter checks of the State parameter of the Protect function
 *
 * \param[in] State  Pointer to port/data communication state.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectStateParamChecks
(
   CONSTP2CONST(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State
);

/**
 * \brief Perform null pointer checks of the input parameters of the Check function
 *
 * \param[in] Config Pointer to static configuration.
 * \param[in] State  Pointer to port/data communication state.
 * \param[in] Data   Pointer to Data to be protected.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckNullPtrChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);

/**
 * \brief Perform input parameter checks of the Config parameter of the Check function
 *
 * \param[in] Config Pointer to static configuration.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckConfigParamChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config
);

/**
 * \brief Perform input parameter checks of the State parameter of the Check function
 *
 * \param[in] State  Pointer to port/data communication state.
 *
 * \return Result of input parameter check
 * \retval E_OK all input parameter are valid
 * \retval E_NOT_OK At least on input parameter is invalid
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckStateParamChecks
(
   CONSTP2CONST(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State
);

/**
 * \brief Calculate the Crc value
 *
 * \param[in] Config  Pointer to static configuration.
 * \param[in] Data    Pointer to Data to be protected.
 * \param[in] Counter Rx / Tx Counter for retrieving the counter-specific DataId
 *
 * \pre All input parameters are valid
 *
 * \return Crc value
 */
static FUNC(uint8, E2E_CODE) E2E_EB_CalculateCrc
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data,
   const uint8 Counter
);

/**
 * \brief Protects the array/buffer to be transmitted using the E2E Profile P02.
 *
 * \param[in]     Config Pointer to static configuration.
 * \param[in,out] State  Pointer to port/data communication state.
 * \param[in,out] Data   Pointer to Data to be protected.
 *
 * \pre All input parameters are valid
 *
 * \return Function execution success status
 * \retval E2E_E_INPUTERR_NULL At least one pointer parameter is a NULL pointer.
 * \retval E2E_E_INPUTERR_WRONG At least one input parameter is erroneous.
 * \retval E2E_E_OK Function completed successfully.
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02Protect
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2VAR(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);

/**
 * \brief Check the received Data using the E2E Profile P02.
 *
 * \param[in]     Config Pointer to static configuration.
 * \param[in,out] State  Pointer to port/data communication state.
 * \param[in,out] Data   Pointer to Data to be protected.
 *
 * \pre All input parameters are valid
 *
 * \return Function execution success status
 * \retval E2E_E_INPUTERR_NULL At least one pointer parameter is a NULL pointer.
 * \retval E2E_E_INPUTERR_WRONG At least one input parameter is erroneous.
 * \retval E2E_E_OK Function completed successfully.
 */
static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02Check
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2VAR(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);

/*==================[internal constants]=====================================*/

/*==================[internal data]==========================================*/

/*==================[external function definition]=========================*/

FUNC(Std_ReturnType, E2E_CODE) E2E_P02Protect
(
   P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   P2VAR(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   Std_ReturnType RetVal;

   if (E2E_EB_P02ProtectNullPtrChecks(Config, State, Data) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if (E2E_EB_P02ProtectConfigParamChecks(Config) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2E_EB_P02ProtectStateParamChecks(State) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      RetVal = E2E_EB_P02Protect(Config, State, Data);
   }

   return RetVal;
}


FUNC(Std_ReturnType, E2E_CODE) E2E_P02Check
(
   P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   P2VAR(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   Std_ReturnType RetVal;

   if (E2E_EB_P02CheckNullPtrChecks(Config, State, Data) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if (E2E_EB_P02CheckConfigParamChecks(Config) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2E_EB_P02CheckStateParamChecks(State) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      RetVal = E2E_EB_P02Check(Config, State, Data);
   }

   return RetVal;
}

/*==================[internal function definition]===========================*/

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectNullPtrChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   Std_ReturnType RetVal;

   /* null pointer checks */
   if (NULL_PTR == Config)
   {
      RetVal = E_NOT_OK;
   }
   else if (NULL_PTR == State)
   {
      RetVal = E_NOT_OK;
   }
   else if (NULL_PTR == Data)
   {
      RetVal = E_NOT_OK;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectConfigParamChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config
)
{
   Std_ReturnType RetVal;

   /* sanity and input checks: E2E_P02ConfigType */
   /* Config->MaxDeltaCounterInit requires no check since it is not read */
   /* Config->MaxNoNewOrRepeatedData requires no check since it is not read */
   /* Config->SyncCounterInit requires no check since it is not read */
   if (E2EP02_DATALENGTH_MAX < Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_DATALENGTH_MIN > Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (0U != (Config->DataLength % 8U))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectStateParamChecks
(
   CONSTP2CONST(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
   Std_ReturnType RetVal;

   /* sanity and input checks: E2E_P02SenderStateType */
   if (E2EP02_COUNTER_MAX < State->Counter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckNullPtrChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   Std_ReturnType RetVal;

   /* null pointer checks */
   if (NULL_PTR == Config)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if (NULL_PTR == State)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if (NULL_PTR == Data)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckConfigParamChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config
)
{
   Std_ReturnType RetVal;

   /* sanity and input checks: E2E_P02ConfigType */
   if (E2EP02_COUNTER_MAX < Config->MaxDeltaCounterInit)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_DATALENGTH_MAX < Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_DATALENGTH_MIN > Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (0U != (Config->DataLength % 8U))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_COUNTER_MAX < Config->SyncCounterInit)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_COUNTER_MAX < Config->MaxNoNewOrRepeatedData)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckStateParamChecks
(
   CONSTP2CONST(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State
)
{
   Std_ReturnType RetVal;

   /* sanity and input checks: E2E_P02ReceiverStateType */
   /* State->Status requires no check since it is not read (only written) */
   if (E2EP02_COUNTER_MAX < State->LastValidCounter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_COUNTER_MAX < State->MaxDeltaCounter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if ((TRUE != State->WaitForFirstData) && (FALSE != State->WaitForFirstData))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if ((TRUE != State->NewDataAvailable) && (FALSE != State->NewDataAvailable))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_COUNTER_MAX < State->SyncCounter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if (E2EP02_COUNTER_MAX < State->NoNewOrRepeatedDataCounter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      RetVal = E_OK;
   }

   return RetVal;
}

static FUNC(uint8, E2E_CODE) E2E_EB_CalculateCrc
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data,
   const uint8 Counter
)
{
   const uint8 ArrayLength = (uint8)(Config->DataLength / 8U);
   P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataId =
         &(Config->DataIDList[Counter]);
   uint8 Crc;

   Crc = SCrc_CalculateCRC8H2F(&Data[1],
                              (uint32)ArrayLength - 1U,
                              E2EP02_CRC_STARTVALUE,
                              TRUE);
   Crc = SCrc_CalculateCRC8H2F(DataId,
                              1U,
                              Crc,
                              FALSE);

   return Crc;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02Protect
(
   P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   P2VAR(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   /* update sequence counter modulo 16 */
   if (E2EP02_COUNTER_MAX > State->Counter)
   {
      State->Counter++;
   }
   else
   {
      State->Counter = 0U;
   }

   /* write sequence counter to first nibble of byte 1 */
   Data[1] &= 0xF0U;
   Data[1] |= State->Counter & 0x0FU;

   /* calculate CRC and write CRC to byte 0 */
   Data[0] = E2E_EB_CalculateCrc(Config, Data, State->Counter);

   return E2E_E_OK;
}

static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02Check
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2VAR(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   if (E2EP02_COUNTER_MAX > State->MaxDeltaCounter)
   {
      /* MaxDeltaCounter is incremented effectively only
       * if no valid message (CRC or counter not OK) has been
       * received (as it will be reset to the initial value if the
       * received message is valid) */
      State->MaxDeltaCounter++;
   }

   if (TRUE == State->NewDataAvailable)
   {
      const uint8 ReceivedCounter = Data[1] & 0x0FU;

      /* check CRC */
      if (E2E_EB_CalculateCrc(Config, Data, ReceivedCounter) == Data[0])
      {
         /* correct CRC */
         if (TRUE == State->WaitForFirstData)
         {
            /* first data received since init or reinit
             * (sequence counter cannot be checked) */
            State->WaitForFirstData = FALSE;
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter;
            State->Status = E2E_P02STATUS_INITIAL;
         }
         else
         {
            /* check sequence counter */
            const uint8 DeltaCounter = (ReceivedCounter >= State->LastValidCounter) ?
               (uint8)(ReceivedCounter - State->LastValidCounter) :
               (uint8)((ReceivedCounter + E2EP02_COUNTER_MAX + 1U) - State->LastValidCounter);

            if (DeltaCounter > State->MaxDeltaCounter)
            {
               /* An unexpected behavior of the counter was detected,
                * so a statement about missing or repeated Data makes no sense anymore */
               State->NoNewOrRepeatedDataCounter = 0U;
               /* Ensure a deterministic behavior of
                * the detected communication errors. */
               State->SyncCounter = Config->SyncCounterInit;
               /* A configured SyncCounterInit value of 0 ensures
                * backward compatibility to ASR 4.0 Rev 3 */
               if (0U < Config->SyncCounterInit)
               {
                  State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
                  State->LastValidCounter = ReceivedCounter;
               }
               /* counter too big, i.e. too many data in the sequence
                * have been probably lost since the last correct/initial
                * reception. */
               State->Status = E2E_P02STATUS_WRONGSEQUENCE;
            }
            else if (1U < DeltaCounter)
            {
               /* the Counter is incremented by DeltaCounter
                * (1 <= DeltaCounter <= MaxDeltaCounter), i.e.
                * some Data in the sequence have been probably lost since
                * the last correct/initial reception, but this is within
                * the configured tolerance range. */
               State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
               State->LastValidCounter = ReceivedCounter;
               State->LostData = DeltaCounter - 1U;
               if (Config->MaxNoNewOrRepeatedData >= State->NoNewOrRepeatedDataCounter)
               {
                  /* Number of missing or repeated Data is tolerated,
                   * so return status OKSOMELOST or SYNC if a re-synchronization
                   * process is ongoing. */
                  if (0U < State->SyncCounter)
                  {
                     State->SyncCounter--;
                     State->Status = E2E_P02STATUS_SYNC;
                  }
                  else
                  {
                     State->Status = E2E_P02STATUS_OKSOMELOST;
                  }
               }
               else
               {
                  /* The limit of missing or repeated Data exceeded
                   * => start re-synchronization handling for a deterministic behavior */
                  State->SyncCounter = Config->SyncCounterInit;
                  State->Status = E2E_P02STATUS_SYNC;
               }
               State->NoNewOrRepeatedDataCounter = 0U;
            }
            else if (1U == DeltaCounter)
            {
               /* the Counter is incremented by 1, i.e. no Data has
                * been lost since the last correct data reception. */
               State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
               State->LastValidCounter = ReceivedCounter;
               State->LostData = 0U;
               if (Config->MaxNoNewOrRepeatedData >= State->NoNewOrRepeatedDataCounter)
               {
                  /* Number of missing or repeated Data is tolerated,
                   * so return status OK or SYNC if a re-synchronization
                   * process is ongoing. */
                  if (0U < State->SyncCounter)
                  {
                     State->SyncCounter--;
                     State->Status = E2E_P02STATUS_SYNC;
                  }
                  else
                  {
                     State->Status = E2E_P02STATUS_OK;
                  }
               }
               else
               {
                  /* The limit of missing or repeated Data exceeded
                   * => start re-synchronization handling for a deterministic behavior */
                  State->SyncCounter = Config->SyncCounterInit;
                  State->Status = E2E_P02STATUS_SYNC;
               }
               State->NoNewOrRepeatedDataCounter = 0U;
            }
            else /* DeltaCounter == 0U */
            {
               /* the counter is identical, i.e. data has already been
                * received (repeated message) */
               /* Increment counter for consecutively missing or repeated Data */
               if (E2EP02_COUNTER_MAX > State->NoNewOrRepeatedDataCounter)
               {
                  State->NoNewOrRepeatedDataCounter++;
               }
               State->Status = E2E_P02STATUS_REPEATED;
            }
         }
      }
      else
      {
         /* wrong CRC */
         State->Status = E2E_P02STATUS_WRONGCRC;
      }
   }
   else
   {
      /* Increment counter for consecutively missing or repeated Data */
      if (E2EP02_COUNTER_MAX > State->NoNewOrRepeatedDataCounter)
      {
         State->NoNewOrRepeatedDataCounter++;
      }
      /* no new data available since the last call */
      State->Status = E2E_P02STATUS_NONEWDATA;
   }

   return E2E_E_OK;
}

#define E2E_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]============================================*/
