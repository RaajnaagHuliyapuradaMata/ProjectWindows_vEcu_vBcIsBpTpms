

#include "Rte_CtApHufTPMSdia.h"

#include "Adc.h"
#include "DEM.h"
#include "state_fzzX.h"
#include "SupplyBattery.h"

uint8 ucKl30_High_Set_KazCnt;
uint8 ucKl30_High_Reset_KazCnt;
uint8 ucKl30_Low_Set_KazCnt;
uint8 ucKl30_Low_Reset_KazCnt;

 uint8 ucPN14SupBat_High_Set_KazCnt;
uint8 ucPN14SupBat_High_Reset_KazCnt;
uint8 ucPN14SupBat_Low_Set_KazCnt;
uint8 ucPN14SupBat_Low_Reset_KazCnt;
void CheckADCvalue4Kl30Diagnostic(uint16 uiKl30Value){

   if( bGetBitFahrzeugzustandFZZ( cFAILURE_MONITORING ) == TRUE ){

      if(uiKl30Value > cKL30_HIGH_LIMIT){
         ucKl30_High_Set_KazCnt++;
         if(ucKl30_High_Set_KazCnt >= cKL30_HIGH_LIMIT_KAZ){
            if(ucKl30_High_Set_KazCnt == cKL30_HIGH_LIMIT_KAZ){

               EvKl30DiagUeberSpgFZZ();
               EvKl30DiagNoUnterSpgFZZ();
               ucKl30_High_Reset_KazCnt=0;
               Dem_SetEventStatus( Dem_DTC_0xa10e00, DEM_EVENT_STATUS_FAILED);
            }
            else
            {
               ucKl30_High_Set_KazCnt=cKL30_HIGH_LIMIT_KAZ;
            }
         }
         ucKl30_Low_Reset_KazCnt++;
         if(ucKl30_Low_Reset_KazCnt >= cKL30_LOW_LIMIT_KAZ){
            if(ucKl30_Low_Reset_KazCnt == cKL30_LOW_LIMIT_KAZ){
               EvKl30DiagNoUnterSpgFZZ();
               ucKl30_Low_Set_KazCnt=0;
               Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_PASSED);
            }
            else
            {
               ucKl30_Low_Reset_KazCnt = cKL30_LOW_LIMIT_KAZ;
            }
         }
      }
      else
      {
         if(uiKl30Value <= cKL30_HIGH_LIMIT_RES){
            ucKl30_High_Reset_KazCnt++;
            if(ucKl30_High_Reset_KazCnt >= cKL30_HIGH_LIMIT_KAZ){
               if(ucKl30_High_Reset_KazCnt == cKL30_HIGH_LIMIT_KAZ){
                  EvKl30DiagNoUeberSpgFZZ();
                  ucKl30_High_Set_KazCnt=0;
                  Dem_SetEventStatus( Dem_DTC_0xa10e00, DEM_EVENT_STATUS_PASSED);
               }
               else
               {
                  ucKl30_High_Reset_KazCnt = cKL30_HIGH_LIMIT_KAZ;
               }
            }
         }
         if(uiKl30Value >= cKL30_LOW_LIMIT_RES){
            ucKl30_Low_Reset_KazCnt++;
            if(ucKl30_Low_Reset_KazCnt >= cKL30_HIGH_LIMIT_KAZ){
               if(ucKl30_Low_Reset_KazCnt == cKL30_HIGH_LIMIT_KAZ){
                  EvKl30DiagNoUnterSpgFZZ();
                  ucKl30_Low_Set_KazCnt=0;
                  Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_PASSED);
               }
               else
               {
                  ucKl30_Low_Reset_KazCnt = cKL30_HIGH_LIMIT_KAZ;
               }
            }
         }
         if(uiKl30Value < cKL30_LOW_LIMIT){
            ucKl30_Low_Set_KazCnt++;
            if(ucKl30_Low_Set_KazCnt >= cKL30_LOW_LIMIT_KAZ){
               if(ucKl30_Low_Set_KazCnt == cKL30_LOW_LIMIT_KAZ){
                  EvKl30DiagUnterSpgFZZ();
                  ucKl30_Low_Reset_KazCnt=0;
            Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_FAILED);
               }
               else
               {
                  ucKl30_Low_Set_KazCnt=cKL30_LOW_LIMIT_KAZ;
               }
            }
         }
      }
      if((bGetKl30LowDTCActive() == TRUE) && (ucKl30_Low_Set_KazCnt==0)){
         Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_PASSED);
      }

      if((bGetKl30HighDTCActive() == TRUE) && (ucKl30_High_Set_KazCnt==0)){
         Dem_SetEventStatus( Dem_DTC_0xa10e00, DEM_EVENT_STATUS_PASSED);
      }

   }
   else
   {
      ucKl30_Low_Set_KazCnt=0;
      ucKl30_High_Set_KazCnt=0;
   }
}

void CheckPN14SupBatState4SupplybatterieDiagnostic(uint8 ucPN14SupBat_value){

   if( bGetBitFahrzeugzustandFZZ( cFAILURE_MONITORING ) == TRUE ){

      if(ucPN14SupBat_value != cPN14_SUPBAT_INVALID){

         if(ucPN14SupBat_value > cPN14_SUPBAT_HIGH_LIMIT){
            ucPN14SupBat_High_Set_KazCnt++;
            if(ucPN14SupBat_High_Set_KazCnt >= cPN14_SUPBAT_HIGH_LIMIT_KAZ){
               if(ucPN14SupBat_High_Set_KazCnt == cPN14_SUPBAT_HIGH_LIMIT_KAZ){
                  ucPN14SupBat_High_Reset_KazCnt=0;
                  Dem_SetEventStatus( Dem_DTC_0xa10b00, DEM_EVENT_STATUS_FAILED);
               }
               else
               {
                  ucPN14SupBat_High_Set_KazCnt=cPN14_SUPBAT_HIGH_LIMIT_KAZ;
               }
            }
            ucPN14SupBat_Low_Reset_KazCnt++;
            if(ucPN14SupBat_Low_Reset_KazCnt >= cPN14_SUPBAT_LOW_LIMIT_KAZ){
               if(ucPN14SupBat_Low_Reset_KazCnt == cPN14_SUPBAT_LOW_LIMIT_KAZ){
                  ucPN14SupBat_Low_Set_KazCnt=0;
                  Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_PASSED);
               }
               else
               {
                  ucPN14SupBat_Low_Reset_KazCnt = cPN14_SUPBAT_LOW_LIMIT_KAZ;
               }
            }
         }
         else
         {
            if(ucPN14SupBat_value < cPN14_SUPBAT_HIGH_LIMIT_RES){
               ucPN14SupBat_High_Reset_KazCnt++;
               if(ucPN14SupBat_High_Reset_KazCnt >= cPN14_SUPBAT_HIGH_LIMIT_KAZ){
                  if(ucPN14SupBat_High_Reset_KazCnt == cPN14_SUPBAT_HIGH_LIMIT_KAZ){
                     ucPN14SupBat_High_Set_KazCnt=0;
                     Dem_SetEventStatus( Dem_DTC_0xa10b00, DEM_EVENT_STATUS_PASSED);
                  }
                  else
                  {
                     ucPN14SupBat_High_Reset_KazCnt = cPN14_SUPBAT_HIGH_LIMIT_KAZ;
                  }
               }
            }

            if(ucPN14SupBat_value > cPN14_SUPBAT_LOW_LIMIT_RES){
               ucPN14SupBat_Low_Reset_KazCnt++;
               if(ucPN14SupBat_Low_Reset_KazCnt >= cPN14_SUPBAT_HIGH_LIMIT_KAZ){
                  if(ucPN14SupBat_Low_Reset_KazCnt == cPN14_SUPBAT_HIGH_LIMIT_KAZ){
                     ucPN14SupBat_Low_Set_KazCnt=0;
                     Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_PASSED);
                  }
                  else
                  {
                     ucPN14SupBat_Low_Reset_KazCnt = cPN14_SUPBAT_HIGH_LIMIT_KAZ;
                  }
               }
            }
            if(ucPN14SupBat_value < cPN14_SUPBAT_LOW_LIMIT){
               ucPN14SupBat_Low_Set_KazCnt++;
               if(ucPN14SupBat_Low_Set_KazCnt >= cPN14_SUPBAT_LOW_LIMIT_KAZ){
                  if(ucPN14SupBat_Low_Set_KazCnt == cPN14_SUPBAT_LOW_LIMIT_KAZ){
                     ucPN14SupBat_Low_Reset_KazCnt=0;
                     Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_FAILED);
                  }
                  else
                  {
                     ucPN14SupBat_Low_Set_KazCnt=cPN14_SUPBAT_LOW_LIMIT_KAZ;
                  }
               }
            }
         }
      }
      if((bGetPN14SupbatLowDTCActive() == TRUE) && (ucPN14SupBat_Low_Set_KazCnt==0)){
         Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_PASSED);
      }

      if((bGetPN14SupbatHighDTCActive() == TRUE) && (ucPN14SupBat_High_Set_KazCnt==0)){
         Dem_SetEventStatus( Dem_DTC_0xa10b00, DEM_EVENT_STATUS_PASSED);
      }
   }
   else
   {
      ucPN14SupBat_Low_Set_KazCnt=0;
      ucPN14SupBat_High_Set_KazCnt=0;
   }
}

void ResetKazCounter4Kl30Failure(void){
   ucKl30_Low_Set_KazCnt=0;
   ucKl30_High_Set_KazCnt=0;
}

void ResetKazCounter4PN14SupBatFailure(void){
   ucPN14SupBat_Low_Set_KazCnt=0;
   ucPN14SupBat_High_Set_KazCnt=0;
}

