/************************************************************************************************************
 * (c) HuF Hülsbeck & Fürst GmbH Co.KG      Abteilung PDSTPS     2016
 ************************************************************************************************************/

/*********************************************************************************************************//**
 * \file SupplyBatterie.c
 * \brief Manager 4 SupplyBatterie SG + PN14_SupBat_Stat (Supply battery voltage diagnostic)
 *
 *------------------------------------------------------------------------------------------------------------
 * Global Description
 * 
 *
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 * Modul Description
 * 
 *
 * Purpose:
 *
 *
 *
 *------------------------------------------------------------------------------------------------------------
 */


/************************************************************************************************************
 *                                             include
 ************************************************************************************************************/
#include "Rte_CtApHufTPMSdia.h"


/**********************************************************************************************************************
 * DO NOT CHANGE THIS COMMENT!           << Start of include and declaration area >>        DO NOT CHANGE THIS COMMENT!
 *********************************************************************************************************************/
#include "Adc.h"
#include "DEM.h"
#include "state_fzzX.h"
#include "SupplyBattery.h"
/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/

/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/
/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/
//void CheckADCvalue4Kl30Diagnostic( uint16 );
//void CheckPN14SupBatState4SupplybatterieDiagnostic(uint8);
/************************************************************************************************************
 *                               prototype (external functions - interface)
 ************************************************************************************************************/

/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/


/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/
//Adc_ValueGroupType AdcBuffer;
//Adc_GroupType AdcGroup4Kl30;

//uint16 uiKl30MFA_ADCvalue;
//uint16 uiKl30MFA_Vsys; /* value 4 diagnostic Kl.30 with value range:  Kl.30=12V -> uiKl30MFA_Vsys=120dez Kl.30=9V -> uiKl30MFA_Vsys=90dez*/

uint8 ucKl30_High_Set_KazCnt;
uint8 ucKl30_High_Reset_KazCnt;
uint8 ucKl30_Low_Set_KazCnt;
uint8 ucKl30_Low_Reset_KazCnt;

//uint8 ucKl30_Low_Low_Limit_KazCnt;
//uint8 ucKl30_KazCnt=FALSE; /*CRS_1211_050_005*/
//uint16 uiKl30_Value4Average[3]; /*CRS_1211_050_005*/

/* for PN14_SupBat_Stat diagnostic DEM 0xa10a00 + 0xa10b00 */ 
uint8 ucPN14SupBat_High_Set_KazCnt;
uint8 ucPN14SupBat_High_Reset_KazCnt;
uint8 ucPN14SupBat_Low_Set_KazCnt;
uint8 ucPN14SupBat_Low_Reset_KazCnt;
//uint8 ucPN14SupBat_DiagStartState;

/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



 /************************************************************************************************
 * \brief routine start: Filling Detection MANUAL Restart of TPMS 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 * \CRS_1211_050_050
 *------------------------------------------------------------------------------------------------
 */
/**************************************************************************************************************************************/	
void CheckADCvalue4Kl30Diagnostic(uint16 uiKl30Value)
{

	if( bGetBitFahrzeugzustandFZZ( cFAILURE_MONITORING ) == TRUE )  /* CRS_1211_050_018 CRS_1211_050_014 cdd 10sec after engine start */
	{

		/*@AS todo  CRS_1211_050_002 cKL30_HIGH_LIMIT*/
		if(uiKl30Value > cKL30_HIGH_LIMIT) /*A:U > 16V*/
		{
			ucKl30_High_Set_KazCnt++;
			if(ucKl30_High_Set_KazCnt >= cKL30_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
			{
				if(ucKl30_High_Set_KazCnt == cKL30_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
				{
					/*@@AS Dem_SetEventStatus( Dem_DTC_0xd162XX, DEM_EVENT_STATUS_FAILED);*/
					EvKl30DiagUeberSpgFZZ(); /* set FZZbit for upper kl30 voltage*/
					EvKl30DiagNoUnterSpgFZZ();
					ucKl30_High_Reset_KazCnt=0;
					Dem_SetEventStatus( Dem_DTC_0xa10e00, DEM_EVENT_STATUS_FAILED);/* CRS_1211_050_006 the power supply is too high*/
				}
				else
				{
					ucKl30_High_Set_KazCnt=cKL30_HIGH_LIMIT_KAZ;  /*KAZ braker*/
				}
			}
			ucKl30_Low_Reset_KazCnt++;
			if(ucKl30_Low_Reset_KazCnt >= cKL30_LOW_LIMIT_KAZ)  /*15sec > 9,5V*/
			{
				if(ucKl30_Low_Reset_KazCnt == cKL30_LOW_LIMIT_KAZ)  /*15sec > 9,5V*/
				{								
					EvKl30DiagNoUnterSpgFZZ();
					ucKl30_Low_Set_KazCnt=0;
					Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_PASSED);/*CRS_1211_050_036 OIL#1064 CRS_1211_050_006  9V RESET*/
				}
				else
				{
					ucKl30_Low_Reset_KazCnt = cKL30_LOW_LIMIT_KAZ;/*KAZ braker*/
				}
			}
		}
		else /*U < 16V*/
		{
			if(uiKl30Value <= cKL30_HIGH_LIMIT_RES) /* B: 15,5V*/
			{
				ucKl30_High_Reset_KazCnt++;
				if(ucKl30_High_Reset_KazCnt >= cKL30_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
				{
					if(ucKl30_High_Reset_KazCnt == cKL30_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
					{								
						EvKl30DiagNoUeberSpgFZZ();
						ucKl30_High_Set_KazCnt=0;
						Dem_SetEventStatus( Dem_DTC_0xa10e00, DEM_EVENT_STATUS_PASSED);/*CRS_1211_050_036 OIL#1064 CRS_1211_050_006  16V RESET*/
					}
					else
					{
						ucKl30_High_Reset_KazCnt = cKL30_HIGH_LIMIT_KAZ;/*KAZ braker*/
					}
				}
			}
			if(uiKl30Value >= cKL30_LOW_LIMIT_RES) /*C: U>9,5 V*/
			{
				ucKl30_Low_Reset_KazCnt++;
				if(ucKl30_Low_Reset_KazCnt >= cKL30_HIGH_LIMIT_KAZ)  /*15sec > 95V*/
				{
					if(ucKl30_Low_Reset_KazCnt == cKL30_HIGH_LIMIT_KAZ)  /*15sec > 95V*/
					{								
						EvKl30DiagNoUnterSpgFZZ();
						ucKl30_Low_Set_KazCnt=0;
						Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_PASSED);/*CRS_1211_050_036 OIL#1064 CRS_1211_050_006  9V RESET*/
					}
					else
					{
						ucKl30_Low_Reset_KazCnt = cKL30_HIGH_LIMIT_KAZ;/*KAZ braker*/
					}
				}
			}
			if(uiKl30Value < cKL30_LOW_LIMIT) /*D: U < 9V */
			{
				ucKl30_Low_Set_KazCnt++;
				if(ucKl30_Low_Set_KazCnt >= cKL30_LOW_LIMIT_KAZ) /*15sec < 9V*/
				{
					if(ucKl30_Low_Set_KazCnt == cKL30_LOW_LIMIT_KAZ) /*15sec < 9V*/
					{
						EvKl30DiagUnterSpgFZZ();/* set FZZbit for lower kl30 voltage*/
						ucKl30_Low_Reset_KazCnt=0;
            Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_FAILED); /*CRS_1211_050_006 the power supply is too low*/
					}
					else
					{
						ucKl30_Low_Set_KazCnt=cKL30_LOW_LIMIT_KAZ;  /*CRS_1211_050_013 KAZ brake*/
					}
				}
			}
		}
		if((bGetKl30LowDTCActive() == TRUE) && (ucKl30_Low_Set_KazCnt==0)) /*CRS_1211_050_050 Passed=TRUE Not Completed since last clear Bit=1 */
		{
			Dem_SetEventStatus( Dem_DTC_0xa10d00, DEM_EVENT_STATUS_PASSED);/* Not Completed since last clear Bit Set=1 Kl.30 i.O.*/
		}

		if((bGetKl30HighDTCActive() == TRUE) && (ucKl30_High_Set_KazCnt==0)) /*CRS_1211_050_050*/
		{
			Dem_SetEventStatus( Dem_DTC_0xa10e00, DEM_EVENT_STATUS_PASSED);/* Not Completed since last clear Bit Set=1 Kl.30 i.O.*/
		}

	}
	else
	{
		ucKl30_Low_Set_KazCnt=0; /*CRS_1211_050_007*/
		ucKl30_High_Set_KazCnt=0; /*CRS_1211_050_007*/
	}
}

/* finish Kl.30 diagnostic*/
/**********************************************************************************************************************/


 /************************************************************************************************
 * \brief routine start: CAN Message 0x122 PN14_SupBat_Stat for Supply battery voltage diagnostic of TPMS
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return none
 * \ CRS_1211_050_050
 *------------------------------------------------------------------------------------------------
 */
/**************************************************************************************************************************************/	


void CheckPN14SupBatState4SupplybatterieDiagnostic(uint8 ucPN14SupBat_value)
{

	if( bGetBitFahrzeugzustandFZZ( cFAILURE_MONITORING ) == TRUE )  /* CRS_1211_050_018 CRS_1211_050_014 cdd 10sec after engine start */
	{

/**************************************************************************************************************************************/	
/* start CAN-message: PN14_SupBat_Stat diagnostic: Supply battery voltage  8Bit 0V-25,4V [1bit=0,1V] CRS_1211_050_020*/ 
	//if( bGetBitPN14_SupBatCutSw_Stat( cOPN ) == TRUE )  /* @@@AS siehe K Matrix PN14_SupBat_Stat --> BIT:Battery cutoff switch is open*/
	//{
		/*@AS todo  CRS_1211_050_020 value !=255?*/
		if(ucPN14SupBat_value != cPN14_SUPBAT_INVALID)
		{
/******************************************************************/
			if(ucPN14SupBat_value > cPN14_SUPBAT_HIGH_LIMIT) /*A:U > 16V*/
			{
				ucPN14SupBat_High_Set_KazCnt++;
				if(ucPN14SupBat_High_Set_KazCnt >= cPN14_SUPBAT_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
				{
					if(ucPN14SupBat_High_Set_KazCnt == cPN14_SUPBAT_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
					{
						ucPN14SupBat_High_Reset_KazCnt=0;
						Dem_SetEventStatus( Dem_DTC_0xa10b00, DEM_EVENT_STATUS_FAILED);/* CRS_1211_050_020 too high*/
					}
					else
					{
						ucPN14SupBat_High_Set_KazCnt=cPN14_SUPBAT_HIGH_LIMIT_KAZ;  /*KAZ brake return*/
					}
				}
				ucPN14SupBat_Low_Reset_KazCnt++;
				if(ucPN14SupBat_Low_Reset_KazCnt >= cPN14_SUPBAT_LOW_LIMIT_KAZ)  /*15sec > 9,5V*/
				{
					if(ucPN14SupBat_Low_Reset_KazCnt == cPN14_SUPBAT_LOW_LIMIT_KAZ)  /*15sec > 9,5V*/
					{								
						ucPN14SupBat_Low_Set_KazCnt=0;
						Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_PASSED);/*CRS_1211_050_036 OIL#1064 CRS_1211_050_006  9V RESET*/
					}
					else
					{
						ucPN14SupBat_Low_Reset_KazCnt = cPN14_SUPBAT_LOW_LIMIT_KAZ;/*KAZ braker*/
					}
				}
			}
			else /*U < 16V*/
			{
				if(ucPN14SupBat_value < cPN14_SUPBAT_HIGH_LIMIT_RES) /*CRS_1211_050_046 (<= --> <)   B: 15,5V*/
				{
					ucPN14SupBat_High_Reset_KazCnt++;
					if(ucPN14SupBat_High_Reset_KazCnt >= cPN14_SUPBAT_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
					{
						if(ucPN14SupBat_High_Reset_KazCnt == cPN14_SUPBAT_HIGH_LIMIT_KAZ)  /*15sec > 165V*/
						{								
							ucPN14SupBat_High_Set_KazCnt=0;
							Dem_SetEventStatus( Dem_DTC_0xa10b00, DEM_EVENT_STATUS_PASSED);/*CRS_1211_050_036 OIL#1064 CRS_1211_050_020  16V RESET*/
						}
						else
						{
							ucPN14SupBat_High_Reset_KazCnt = cPN14_SUPBAT_HIGH_LIMIT_KAZ;
						}
					}
				}
/******************************************************************/
				if(ucPN14SupBat_value > cPN14_SUPBAT_LOW_LIMIT_RES) /*CRS_1211_050_046 (>= --> >) C: U>9,5 V*/
				{
					ucPN14SupBat_Low_Reset_KazCnt++;
					if(ucPN14SupBat_Low_Reset_KazCnt >= cPN14_SUPBAT_HIGH_LIMIT_KAZ)  /*15sec > 95V*/
					{
						if(ucPN14SupBat_Low_Reset_KazCnt == cPN14_SUPBAT_HIGH_LIMIT_KAZ)  /*15sec > 95V*/
						{								
							ucPN14SupBat_Low_Set_KazCnt=0;
							Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_PASSED);/*CRS_1211_050_036 OIL#1064 CRS_1211_050_020  9V RESET*/
						}
						else
						{
							ucPN14SupBat_Low_Reset_KazCnt = cPN14_SUPBAT_HIGH_LIMIT_KAZ;
						}
					}
				}
				if(ucPN14SupBat_value < cPN14_SUPBAT_LOW_LIMIT) /*D: U < 9V */
				{
					ucPN14SupBat_Low_Set_KazCnt++;
					if(ucPN14SupBat_Low_Set_KazCnt >= cPN14_SUPBAT_LOW_LIMIT_KAZ) /*15sec < 9V*/
					{
						if(ucPN14SupBat_Low_Set_KazCnt == cPN14_SUPBAT_LOW_LIMIT_KAZ) /*15sec < 9V*/
						{
							ucPN14SupBat_Low_Reset_KazCnt=0;
							//Dem_SetEventStatus( Dem_DTC_0xa10b00, DEM_EVENT_STATUS_FAILED); /*CRS_1211_050_020 the SupBat is too low CRS_1211_050_045*/
							Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_FAILED);/*CRS_1211_050_045 the SupBat is too low*/
						}
						else
						{
							ucPN14SupBat_Low_Set_KazCnt=cPN14_SUPBAT_LOW_LIMIT_KAZ;  /*CRS_1211_050_020 KAZ brake*/
						}
					}
				}
			}
		}
		if((bGetPN14SupbatLowDTCActive() == TRUE) && (ucPN14SupBat_Low_Set_KazCnt==0)) /* CRS_1211_050_050 Passed=TRUE Not Completed since last clear Bit=1 */
		{
			Dem_SetEventStatus( Dem_DTC_0xa10a00, DEM_EVENT_STATUS_PASSED);/* Not Completed since last clear Bit Set=1 Kl.30 i.O.*/
		}

		if((bGetPN14SupbatHighDTCActive() == TRUE) && (ucPN14SupBat_High_Set_KazCnt==0))  /*CRS_1211_050_050*/
		{
			Dem_SetEventStatus( Dem_DTC_0xa10b00, DEM_EVENT_STATUS_PASSED);/* Not Completed since last clear Bit Set=1 Kl.30 i.O.*/
		}
	}
	else
	{
		ucPN14SupBat_Low_Set_KazCnt=0;	
		ucPN14SupBat_High_Set_KazCnt=0;
	}
}
/* finish CAN-message: PN14_SupBat_Stat diagnostic*/
/**********************************************************************************************************************/




void ResetKazCounter4Kl30Failure(void)  
{
	ucKl30_Low_Set_KazCnt=0; /*CRS_1211_050_007*/
	ucKl30_High_Set_KazCnt=0; /*CRS_1211_050_007*/
}

void ResetKazCounter4PN14SupBatFailure(void)  
{
	ucPN14SupBat_Low_Set_KazCnt=0;	
	ucPN14SupBat_High_Set_KazCnt=0;
}

