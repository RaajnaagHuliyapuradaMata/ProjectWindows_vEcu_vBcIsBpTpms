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
#include "HufE2EWrapper.h"

/************************************************************************************************************
 *                                             macro
 ************************************************************************************************************/


/************************************************************************************************************
 *                                            typedef
 ************************************************************************************************************/



/************************************************************************************************************
 *                                    data (Modulglobal) - ROM
 ************************************************************************************************************/
 const E2E_P02ConfigType cE2EConfigWhlplsCnt = {64U,   136U,194U,252U,59U,117U,175U,233U,40U,98U,156U,214U,21U,79U,137U,195U,253U, 1U, 0U, 1U};
 const E2E_P02ConfigType cE2EConfigTireState2 = {16U,  42U,58U,74U,90U,106U,122U,138U,154U,170U,186U,202U,218U,234U,250U,15U,31U,  1U, 0U, 1U};

 const E2E_P02ReceiverStateType cE2EStatesWhlplsCntDefault = {E2E_P02STATUS_OK, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
 const E2E_P02SenderStateType cE2EStateTireState2Default = {0U};


/************************************************************************************************************
 *                                    data (Modulglobal) - RAM
 ************************************************************************************************************/
E2E_P02ReceiverStateType ucE2EStatesWhlplsCnt;// = cE2EStatesWhlplsCntDefault;
E2E_P02SenderStateType ucE2EStateTireState2;// = cE2EStateTireState2Default;
/************************************************************************************************************
 *                                       data (global) - ROM
 ************************************************************************************************************/



/************************************************************************************************************
 *                                       data (global) - RAM
 ************************************************************************************************************/



/***********************************************************************************************************
 *                                 prototype (local functions - private)
 ***********************************************************************************************************/






/************************************************************************************************//**
 *
 * \brief  inits Huf E2E Wrapper 
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] none
 * \param [out] none
 *
 * \return	none
 *
 *------------------------------------------------------------------------------------------------
 */
void HufE2EWrapperInit(void)
{
	uint8 i;
	for (i=0; i<sizeof(E2E_P02ReceiverStateType); i++)
	{
		*((uint8*)&ucE2EStatesWhlplsCnt + i) = 0;
	}
	ucE2EStatesWhlplsCnt.WaitForFirstData=TRUE; // set wait for new data bit

	for (i=0; i<sizeof(E2E_P02SenderStateType); i++)
	{
		*((uint8*)&ucE2EStateTireState2 + i) = 0;
	}
}


/************************************************************************************************//**
 *
 * \brief  checks integrity of received ABS ticks
 *
 *-----------------------------------------------------------------------------------------------
 * \param [in] data
 * \param [out] none
 *
 * \return	1 Ok 0 Error
 *
 *------------------------------------------------------------------------------------------------
 */
 uint8 ucHufE2EWrapperCheckWhlPlsCnt(uint8* data)
 {
	 uint8 ucRetVal;
	 uint8 aucTempData[8];
	 //static uint8 test[16];
	 //static uint8 i = 0;

	 //test[i] = data[2];
	 //i = (i+1)%16;

	 // function is called on new data reception
	 ucE2EStatesWhlplsCnt.NewDataAvailable=1;
	 
	 // perform data serialization	 
	 aucTempData[0] = data[0];
	 aucTempData[1] = ((data[1] & 0xF)<<4) | (data[2] & 0xF);//SQC
	 aucTempData[2] = data[3];
	 aucTempData[3] = data[4];
	 aucTempData[4] = data[5];
	 aucTempData[5] = data[6];
	 aucTempData[6] = data[7];
	 aucTempData[7] = data[8];

	 E2E_P02Check(&cE2EConfigWhlplsCnt, &ucE2EStatesWhlplsCnt, aucTempData); // perform crc check

	 if (ucE2EStatesWhlplsCnt.Status == E2E_P02STATUS_OK)
	 {
		// crc check successful
		 ucRetVal = TRUE;
	 }
	 else{

		 ucRetVal = FALSE;
	 }
	 return ucRetVal;
 }

 /************************************************************************************************//**
 *
 * \brief  add crc to protect tire state message (TPMS Warning and malfuntion lamps)
 *
 *-----------------------------------------------------------------------------------------------
 * \param [inout] data
 *
 *
 * \return	1 OK 0 Error
 *
 *------------------------------------------------------------------------------------------------
 */
 uint8 ucHufE2EWrapperProtectTireState2(uint8* data)
 {
	 uint8 ucRetVal;
	 uint8 aucTempData[2];

	 aucTempData[0] = data[0];

	 // data serialization
	 aucTempData[1] = ((data[1]&0x11)<<6)  | (data[2]&0x0F) |  ((data[3]&0x01)<<4) | ((data[4]&0x01)<<5); 

	 ucRetVal = E2E_P02Protect(&cE2EConfigTireState2, &ucE2EStateTireState2, aucTempData);

	 data[0] = aucTempData[0]; //CRC
	 data[1] = (aucTempData[1] & 0xC0)>>6; //RSV bits
	 data[2] = (aucTempData[1] & 0x0F);// SQC
	 //data[3] = (aucTempData[1] & 0x20)>>4; // Original data
	 //data[4] = (aucTempData[1] & 0x10)>>5; // Original data

	 return ucRetVal;


 }