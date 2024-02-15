/************************************************************************************************************
 * (c) HuF Electronics GmbH      Abteilung ENTS4     2015
 ************************************************************************************************************/

/*********************************************************************************************************//**
 * \file internal_clock.c
 * \brief Manage internal time and timers
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
#include "internal_clock.h"
#include "internal_clockX.h"
#include "state_fzzX.h"
#include "Rte_CtApHufTPMSmgr.h"
#include "WallocX.h"
#include "state_fzzX.h"
#include "Gpt.h"
/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/
#define cT_SpecialLearn         (uint16) 300 // min 
#define ECU_TIMER_CHANNEL       0U
#define ECU_TIMER_MAX           0xFFFFFFFFU
#define ECU_TIMER_S_PER_TICK    4U //ms per tick
#define ECU_TIMER_FREQ_KHZ      250u // 250kHz Original 8Mhz / Hardware prescaler (2^5) 
/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/
static uint32 ulGlobalTime = 0;
static uint32  ucLastTicks = 0;
static uint32 ucTicksError = 0;

static uint16 ushStanbyTime = cT_STANBY;  // standby timer
static uint16 ushParkingTime = cT_STANBY; // parking time


static uint8 ucOpTimeMethodCurrent; // currently used method

static boolean bAbsErrorDetected =  FALSE;
/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/

extern uint16 uiKl30MFA_Vsys;
extern void TP3(uint8 ucSet);/*CtCdHufTPMSrfd.h*/
extern void SetCodNvMBlockNewDataFlag(boolean);
/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/






/************************************************************************************************//**
 *
 * \brief  inits internal clock and timers
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void InternTimersInit(void)
{	
  ulGlobalTime = 0;
  ucLastTicks = 0;
  ucTicksError = 0;
  Gpt_StartTimer((Gpt_ChannelType) ECU_TIMER_CHANNEL, (Gpt_ValueType) 0);

  ushStanbyTime = cT_STANBY;
  ushParkingTime=cT_STANBY;
	ClearBitFahrzeugzustandFZZ(cKFZPARKING_START_AFD );/* CRS_1211_130_170 */	

}

/************************************************************************************************//**
 *
 * \brief  increments internal millisecond time, function called every 10ms
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void IncrInternMsTimer(void)
{
  uint32 ucCurrentTicks, ucDeltaTicks;

  ucCurrentTicks = Gpt_GetTimeElapsed((Gpt_ChannelType) ECU_TIMER_CHANNEL);

  // get delta ticks since last synchronisation
  if(ucCurrentTicks < ucLastTicks)
  {
    ucDeltaTicks = (ECU_TIMER_MAX - ucLastTicks) + ucCurrentTicks + 1;
  }
  else
  {
      ucDeltaTicks = ucCurrentTicks - ucLastTicks;
  }

  // update ecu internal time in ms, 
  //@white box test team: this is a continious timer which means overflow are expected and tolerated
  ulGlobalTime = ulGlobalTime + ( (ucDeltaTicks + ucTicksError) / ECU_TIMER_FREQ_KHZ ); // get global time

  // update ucLastTime
  ucLastTicks = ucCurrentTicks;

  // update residual error
  ucTicksError =  ucDeltaTicks % ECU_TIMER_FREQ_KHZ; // save error
}

/************************************************************************************************//**
 *
 * \brief  gets internal millisecond time
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] ulInternalTime  internal ms time
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void GetInternMSTime(uint32* ulInternalTime)
{
  uint32 ucCurrentTicks, ucDeltaTicks;
  ucCurrentTicks = Gpt_GetTimeElapsed((Gpt_ChannelType) ECU_TIMER_CHANNEL);

  // get delta ticks since last synchronisation
  if(ucCurrentTicks < ucLastTicks)
  {
    ucDeltaTicks = (ECU_TIMER_MAX - ucLastTicks) + ucCurrentTicks;
  }
  else
  {
      ucDeltaTicks = ucCurrentTicks - ucLastTicks;
  }


	*ulInternalTime = ulGlobalTime + ((ucDeltaTicks + ucTicksError) / ECU_TIMER_FREQ_KHZ );
}

/************************************************************************************************//**
 *
 * \brief  updates or increments ECU parking timer
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] ucVSpeed  current vehicle speed
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void UpdateParkingTimer(uint16 ushVSpeed) 
{
  if(ushVSpeed == 0)
  {
    // max value is cT_STANBY
    if(ushParkingTime<cT_STANBY)
    {
      ushParkingTime++;

    }
  }
  else
	{
    ushParkingTime=0;
  }
}

/************************************************************************************************//**
 *
 * \brief  updates or increments ECU stanby timer
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] bIgnState ignition state
 * \param [in] ucVSpeed  current vehicle speed
 * \param [in] ucVmin lowest speed limit for incrementing the timer
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void UpdateStanbyTimer(boolean bIgnState, uint16 ushVSpeed, uint8 ucVmin) 
{
	static uint8 ucVSpeedCnt = 0; // variable is invcremented each time Vmin is consecutively exceeded 

	/* vehicle speed > Vmin for more than 20 consecutive seconds */
	/* Pal logic doc v1.2 section 8.2 */
	if( (ushVSpeed > ucVmin) && (ucVSpeedCnt < 20) )
	{
		ucVSpeedCnt ++;
	}
	else
	{
		ucVSpeedCnt = 0;
	}
	if ((ucVSpeedCnt==20) && (bIgnState==TRUE))
	{
		ResetStanbyTimer();
	}

	/* increment  stanbyTimer at ignition off or at ingnition on if vehicle speed = 0 */
	/* Pal logic doc v1.2 section 8.2 */
	if ((bIgnState ==  FALSE) || ((bIgnState==TRUE) && (ushVSpeed == 0)))
	{
		if(ushStanbyTime < cT_STANBY)
			ushStanbyTime++;
	}
}

/************************************************************************************************//**
 *
 * \brief  resets ECU stanby timer
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void ResetStanbyTimer(void)
{
	ushStanbyTime = 0;
}

/************************************************************************************************//**
 *
 * \brief  skip stanby time and go direcly in sleep mode
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void SkipStanbyTimer(void)
{

	ushStanbyTime = cT_STANBY;

}

 
uint16 ushGetCurrentECUStanbyTime(void){
	return ushStanbyTime;
}

/************************************************************************************************//**
 *
 * \brief  gets current parking state
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	parking state 1  No Learn 2 Special Learn 3 Full Learn
 *
 *------------------------------------------------------------------------------------------------
 */
uint8 ucGetCurrentECUParkingState(void){
  if(ushParkingTime<cT_SpecialLearn)
  {
    return 1; //No learn
  }
  else if (ushParkingTime<cT_STANBY)
  {
    return 2; //Special learn
  }
  else
  {
    return 3; // Complete learn
  }

}

/************************************************************************************************//**
 *
 * \brief  gets current parking times
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	parking stime in second
 *
 *------------------------------------------------------------------------------------------------
 */
uint16 ushGetCurrentECUParkingTime(void){

  return ushParkingTime;
}


/************************************************************************************************//**
 *
 * \brief  checks whether ECU standby timer is elapsed
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
boolean bStanbyTimerElapsed(void)
{

	return (ushStanbyTime >= cT_STANBY);

}

/************************************************************************************************//**
 *
 * \brief  gets current auto filling start state
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] TRUE or FALSE 
 *
 * \return	auto filling start state
 *
 *------------------------------------------------------------------------------------------------
 */
//uint8 ucGetCurrentECUAfdStartState(void)
//{
//	return ucAfdStart;
//}



uint8  GetOpTimeMethodCurrent(void)
{
  return ucOpTimeMethodCurrent;
}

// normally call by diagnostic job
void SetOpTimeMethodTarget(uint8 ucTimeMethod, uint8 ucCstDelay)
{
  if(ucTimeMethod == OP_TIME_METHOD_CSTDELAY)
  {
    //*(uint8*)Rte_Pim_Pim_PalAbsDelayTimeParam()  = OP_TIME_METHOD_CSTDELAY;
    Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[0] = OP_TIME_METHOD_CSTDELAY;
  }
  else if(ucTimeMethod == OP_TIME_METHOD_OHDS)
  {
    //*(uint8*)Rte_Pim_Pim_PalAbsDelayTimeParam()  = OP_TIME_METHOD_OHDS;
    Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[0] = OP_TIME_METHOD_OHDS;
  }
  else
  {
    //do nothing
  }
  //*((uint8*)Rte_Pim_Pim_PalAbsDelayTimeParam() + (uint8)1) = ucCstDelay;
  Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[1] = ucCstDelay;
  SetCodNvMBlockNewDataFlag(TRUE);
  Rte_Call_PS_Rte_NvmBlock_CpApHufTPMSmgr_Pim_tCodNvMBlock_SetRamBlockStatus(TRUE);
}

// normally call from diagnostic job
uint8 GetOpTimeMehodTarget(void)
{
  //return *(uint8*)Rte_Pim_Pim_PalAbsDelayTimeParam()  ; // return ram content here
  return Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[0];
}

// normally call from diagnostic job
uint8 GetPalAbsConstantDelay(void)
{
  //return *((uint8*)Rte_Pim_Pim_PalAbsDelayTimeParam() + (uint8)1) ; // return ram content here
  return Rte_Pim_Pim_tCodNvMBlock()->aucPalAbsDelayTimeParam[1];
}


void GetSystemOperatingTime(uint32* ulOpTime)
{
  uint8 ucStatus, ucMSB, ucTemp;
  uint32 ulTempOpTime;
 
  ucTemp = ucOpTimeMethodCurrent;

  if ( (GetOpTimeMehodTarget() == OP_TIME_METHOD_CSTDELAY) || (bAbsErrorDetected==TRUE))
  {
    GetInternMSTime(ulOpTime);
    ucOpTimeMethodCurrent = OP_TIME_METHOD_CSTDELAY;
  }
  else if( GetOpTimeMehodTarget() == OP_TIME_METHOD_OHDS)
  {
    Rte_Call_R_OHDS_GetOperatingHours_GetOperatingHours(&ulTempOpTime, &ucMSB, &ucStatus);
    if ((ucStatus & 0x01) == 0x01 ) // check if sync bit is ok
    {
      if( bGetBitFahrzeugzustandFZZ(cFAILURE_MONITORING) && bGetFzzCanSignalImplausibleState(cFZZ_TRACTION_SYSTEM_IMPLAU))
      {
      GetInternMSTime(ulOpTime);
        ucOpTimeMethodCurrent = OP_TIME_METHOD_CSTDELAY;
        bAbsErrorDetected = TRUE;
      }
      else
      {
        *ulOpTime = ulTempOpTime;
        ucOpTimeMethodCurrent = OP_TIME_METHOD_OHDS;
      }

    }
    else
    {
      GetInternMSTime(ulOpTime);
      ucOpTimeMethodCurrent = OP_TIME_METHOD_CSTDELAY;
    }

  }
  else
  {
    // do nothing

  }
   if (ucTemp != ucOpTimeMethodCurrent)
   {
      ReNewABSRef();// reset reference point for ABS calculation if operating time method has changed
   }
}

void SetPalAbsTimeInfoSNA(void)
{


}

