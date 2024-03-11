



#include <E2E_P02.h>       
#include <SCrc_CRC8H2F.h>  



#if(defined E2EP02_CRC_STARTVALUE) 
#error E2EP02_CRC_STARTVALUE is already defined
#endif 


#define E2EP02_CRC_STARTVALUE 0xFFU

#if(defined E2EP02_COUNTER_MAX) 
#error E2EP02_COUNTER_MAX is already defined
#endif 


#define E2EP02_COUNTER_MAX 15U

#if(defined E2EP02_DATALENGTH_MAX) 
#error E2EP02_DATALENGTH_MAX is already defined
#endif 


#define E2EP02_DATALENGTH_MAX 2048U

#if(defined E2EP02_DATALENGTH_MIN) 
#error E2EP02_DATALENGTH_MIN is already defined
#endif 


#define E2EP02_DATALENGTH_MIN 16U





#define E2E_START_SEC_CODE
#include <MemMap.h>


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectNullPtrChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectConfigParamChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config
);


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectStateParamChecks
(
   CONSTP2CONST(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State
);


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckNullPtrChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckConfigParamChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config
);


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02CheckStateParamChecks
(
   CONSTP2CONST(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State
);


static FUNC(uint8, E2E_CODE) E2E_EB_CalculateCrc
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data,
   const uint8 Counter
);


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02Protect
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2VAR(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);


static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02Check
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2VAR(E2E_P02ReceiverStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
);







FUNC(Std_ReturnType, E2E_CODE) E2E_P02Protect
(
   P2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   P2VAR(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   Std_ReturnType RetVal;

   if(E2E_EB_P02ProtectNullPtrChecks(Config, State, Data) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if(E2E_EB_P02ProtectConfigParamChecks(Config) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2E_EB_P02ProtectStateParamChecks(State) != E_OK)
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

   if(E2E_EB_P02CheckNullPtrChecks(Config, State, Data) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if(E2E_EB_P02CheckConfigParamChecks(Config) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2E_EB_P02CheckStateParamChecks(State) != E_OK)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else
   {
      RetVal = E2E_EB_P02Check(Config, State, Data);
   }

   return RetVal;
}



static FUNC(Std_ReturnType, E2E_CODE) E2E_EB_P02ProtectNullPtrChecks
(
   CONSTP2CONST(E2E_P02ConfigType, AUTOMATIC, E2E_APPL_CONST) Config,
   CONSTP2CONST(E2E_P02SenderStateType, AUTOMATIC, E2E_APPL_DATA) State,
   CONSTP2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) Data
)
{
   Std_ReturnType RetVal;

   
   if(NULL_PTR == Config)
   {
      RetVal = E_NOT_OK;
   }
   else if(NULL_PTR == State)
   {
      RetVal = E_NOT_OK;
   }
   else if(NULL_PTR == Data)
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

   
   
   
   
   if(E2EP02_DATALENGTH_MAX < Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_DATALENGTH_MIN > Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(0U != (Config->DataLength % 8U))
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

   
   if(E2EP02_COUNTER_MAX < State->Counter)
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

   
   if(NULL_PTR == Config)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if(NULL_PTR == State)
   {
      RetVal = E2E_E_INPUTERR_NULL;
   }
   else if(NULL_PTR == Data)
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

   
   if(E2EP02_COUNTER_MAX < Config->MaxDeltaCounterInit)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_DATALENGTH_MAX < Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_DATALENGTH_MIN > Config->DataLength)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(0U != (Config->DataLength % 8U))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_COUNTER_MAX < Config->SyncCounterInit)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_COUNTER_MAX < Config->MaxNoNewOrRepeatedData)
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

   
   
   if(E2EP02_COUNTER_MAX < State->LastValidCounter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_COUNTER_MAX < State->MaxDeltaCounter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if((TRUE != State->WaitForFirstData) && (FALSE != State->WaitForFirstData))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if((TRUE != State->NewDataAvailable) && (FALSE != State->NewDataAvailable))
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_COUNTER_MAX < State->SyncCounter)
   {
      RetVal = E2E_E_INPUTERR_WRONG;
   }
   else if(E2EP02_COUNTER_MAX < State->NoNewOrRepeatedDataCounter)
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
   
   if(E2EP02_COUNTER_MAX > State->Counter)
   {
      State->Counter++;
   }
   else
   {
      State->Counter = 0U;
   }

   
   Data[1] &= 0xF0U;
   Data[1] |= State->Counter & 0x0FU;

   
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
   if(E2EP02_COUNTER_MAX > State->MaxDeltaCounter)
   {
      
      State->MaxDeltaCounter++;
   }

   if(TRUE == State->NewDataAvailable)
   {
      const uint8 ReceivedCounter = Data[1] & 0x0FU;

      
      if(E2E_EB_CalculateCrc(Config, Data, ReceivedCounter) == Data[0])
      {
         
         if(TRUE == State->WaitForFirstData)
         {
            
            State->WaitForFirstData = FALSE;
            State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
            State->LastValidCounter = ReceivedCounter;
            State->Status = E2E_P02STATUS_INITIAL;
         }
         else
         {
            
            const uint8 DeltaCounter = (ReceivedCounter >= State->LastValidCounter) ?
               (uint8)(ReceivedCounter - State->LastValidCounter) :
               (uint8)((ReceivedCounter + E2EP02_COUNTER_MAX + 1U) - State->LastValidCounter);

            if(DeltaCounter > State->MaxDeltaCounter)
            {
               
               State->NoNewOrRepeatedDataCounter = 0U;
               
               State->SyncCounter = Config->SyncCounterInit;
               
               if(0U < Config->SyncCounterInit)
               {
                  State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
                  State->LastValidCounter = ReceivedCounter;
               }
               
               State->Status = E2E_P02STATUS_WRONGSEQUENCE;
            }
            else if(1U < DeltaCounter)
            {
               
               State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
               State->LastValidCounter = ReceivedCounter;
               State->LostData = DeltaCounter - 1U;
               if(Config->MaxNoNewOrRepeatedData >= State->NoNewOrRepeatedDataCounter)
               {
                  
                  if(0U < State->SyncCounter)
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
                  
                  State->SyncCounter = Config->SyncCounterInit;
                  State->Status = E2E_P02STATUS_SYNC;
               }
               State->NoNewOrRepeatedDataCounter = 0U;
            }
            else if(1U == DeltaCounter)
            {
               
               State->MaxDeltaCounter = Config->MaxDeltaCounterInit;
               State->LastValidCounter = ReceivedCounter;
               State->LostData = 0U;
               if(Config->MaxNoNewOrRepeatedData >= State->NoNewOrRepeatedDataCounter)
               {
                  
                  if(0U < State->SyncCounter)
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
                  
                  State->SyncCounter = Config->SyncCounterInit;
                  State->Status = E2E_P02STATUS_SYNC;
               }
               State->NoNewOrRepeatedDataCounter = 0U;
            }
            else 
            {
               
               
               if(E2EP02_COUNTER_MAX > State->NoNewOrRepeatedDataCounter)
               {
                  State->NoNewOrRepeatedDataCounter++;
               }
               State->Status = E2E_P02STATUS_REPEATED;
            }
         }
      }
      else
      {
         
         State->Status = E2E_P02STATUS_WRONGCRC;
      }
   }
   else
   {
      
      if(E2EP02_COUNTER_MAX > State->NoNewOrRepeatedDataCounter)
      {
         State->NoNewOrRepeatedDataCounter++;
      }
      
      State->Status = E2E_P02STATUS_NONEWDATA;
   }

   return E2E_E_OK;
}

#define E2E_STOP_SEC_CODE
#include <MemMap.h>


