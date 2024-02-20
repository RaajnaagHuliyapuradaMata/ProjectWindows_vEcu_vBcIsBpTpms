

#include "HufE2EWrapper.h"

 const E2E_P02ConfigType cE2EConfigWhlplsCnt = {64U,   136U,194U,252U,59U,117U,175U,233U,40U,98U,156U,214U,21U,79U,137U,195U,253U, 1U, 0U, 1U};
 const E2E_P02ConfigType cE2EConfigTireState2 = {16U,  42U,58U,74U,90U,106U,122U,138U,154U,170U,186U,202U,218U,234U,250U,15U,31U,  1U, 0U, 1U};

 const E2E_P02ReceiverStateType cE2EStatesWhlplsCntDefault = {E2E_P02STATUS_OK, 0U, 0U, 0U, 0U, 0U, 0U, 0U};
 const E2E_P02SenderStateType cE2EStateTireState2Default = {0U};

E2E_P02ReceiverStateType ucE2EStatesWhlplsCnt;
 E2E_P02SenderStateType ucE2EStateTireState2;

void HufE2EWrapperInit(void)
{
   uint8 i;
   for (i=0; i<sizeof(E2E_P02ReceiverStateType); i++)
   {
      *((uint8*)&ucE2EStatesWhlplsCnt + i) = 0;
   }
   ucE2EStatesWhlplsCnt.WaitForFirstData=TRUE;

   for (i=0; i<sizeof(E2E_P02SenderStateType); i++)
   {
      *((uint8*)&ucE2EStateTireState2 + i) = 0;
   }
}

 uint8 ucHufE2EWrapperCheckWhlPlsCnt(uint8* data)
 {
    uint8 ucRetVal;
    uint8 aucTempData[8];

      ucE2EStatesWhlplsCnt.NewDataAvailable=1;
     aucTempData[0] = data[0];
    aucTempData[1] = ((data[1] & 0xF)<<4) | (data[2] & 0xF);
     aucTempData[2] = data[3];
    aucTempData[3] = data[4];
    aucTempData[4] = data[5];
    aucTempData[5] = data[6];
    aucTempData[6] = data[7];
    aucTempData[7] = data[8];

    E2E_P02Check(&cE2EConfigWhlplsCnt, &ucE2EStatesWhlplsCnt, aucTempData);

    if (ucE2EStatesWhlplsCnt.Status == E2E_P02STATUS_OK)
    {
       ucRetVal = TRUE;
    }
    else{

       ucRetVal = FALSE;
    }
    return ucRetVal;
 }

 uint8 ucHufE2EWrapperProtectTireState2(uint8* data)
 {
    uint8 ucRetVal;
    uint8 aucTempData[2];

    aucTempData[0] = data[0];
     aucTempData[1] = ((data[1]&0x11)<<6)  | (data[2]&0x0F) |  ((data[3]&0x01)<<4) | ((data[4]&0x01)<<5);

    ucRetVal = E2E_P02Protect(&cE2EConfigTireState2, &ucE2EStateTireState2, aucTempData);

    data[0] = aucTempData[0];
     data[1] = (aucTempData[1] & 0xC0)>>6;
     data[2] = (aucTempData[1] & 0x0F);

    return ucRetVal;

 }
