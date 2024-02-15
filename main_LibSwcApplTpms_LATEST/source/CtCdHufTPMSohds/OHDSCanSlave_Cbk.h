/**************************************************************************************************
   Project Name: Operating Hours Distribution Service (OHDS) - CAN Slave
      File Name: OHDSCanSlave_Cbk.h

    Description: Callback header of OHDSCanSlave used by PduR

  -------------------------------------------------------------------------------------------------
       C O P Y R I G H T
  -------------------------------------------------------------------------------------------------
       Copyright (c) 2014 by Vector Informatik GmbH. All rights reserved.

       This software is copyright protected and proprietary to Vector Informatik GmbH.
       Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
       All other rights remain with Vector Informatik GmbH.


       REMOVAL OF THESE COMMENTS IS A VIOLATION OF THE COPYRIGHT AGREEMENT.

  -------------------------------------------------------------------------------------------------
                 A U T H O R   I D E N T I T Y
  -------------------------------------------------------------------------------------------------
   Initials     Name                      Company
   --------     ---------------------     ---------------------------------------------------------
   vislki       Lothar Kieble             Vector Informatik GmbH
   viseml       Michael Epping            Vector Informatik GmbH
  -------------------------------------------------------------------------------------------------
                 R E V I S I O N   H I S T O R Y
  -------------------------------------------------------------------------------------------------
   Date         Rev.     Author  Description
   ----------   -------  ------  ------------------------------------------------------------------
   2013-12-19   1.0.0    vislki  Initial creation
   2014-03-05   1.0.1    vislki  Renamed Compiler_Cfg and MemMap defines
   2014-03-11            viseml  Code Inspection
**************************************************************************************************/
#if !defined(OHDSCANSLAVE_CBK_H)
# define OHDSCANSLAVE_CBK_H

/**************************************************************************************************
* Prototypes of export functions
**************************************************************************************************/
#define OHDS_START_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/**************************************************************************************************
   Function name    : OHDSCanSlave_RxIndication
   ------------------------------------------------------------------------------------------------
   Description      : Indication about received SYNC or FUP message. If received message is a SYNC
                      message data buffer is stored and a timer is started. If a FUP message is
                      received the Operating Hours counter is updated if all checks are successfully
                      passed
   ------------------------------------------------------------------------------------------------
   Called by        : PduR
   ------------------------------------------------------------------------------------------------
   Parameter        : RxPduId: The pduId of the received PDU
                      PduInfoPtr: Information about the received PDU containing the actual message
                                  buffer.
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, OHDS_APPL_VAR) PduInfoPtr);

/**************************************************************************************************
   Function name    : OHDSCanSlave_TxConfirmation
   ------------------------------------------------------------------------------------------------
   Description      : Confirmation about a sent PDU. This function should not be called by the PduR
                      because the OHDSCanSlave is not allowed to transmit data for now.
   ------------------------------------------------------------------------------------------------
   Called by        : PduR
   ------------------------------------------------------------------------------------------------
   Parameter        : TxPduId: The pduId of the transmitted PDU.
   ------------------------------------------------------------------------------------------------
   Returncode       : -
   ------------------------------------------------------------------------------------------------
   Misc             : -
**************************************************************************************************/
FUNC(void, OHDS_CODE) OHDSCanSlave_TxConfirmation(PduIdType TxPduId);


#define OHDS_STOP_SEC_CODE
#include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

/***** end of header file ************************************************************************/
#endif /* ifndef OHDSCANSLAVE_CBK_H */
