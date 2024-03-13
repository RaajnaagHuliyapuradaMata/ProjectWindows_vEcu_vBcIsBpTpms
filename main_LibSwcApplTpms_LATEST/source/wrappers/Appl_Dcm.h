

#if !defined(__APPL_DCM_H__)
#define __APPL_DCM_H__

typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_NegativeResponseCodeType;
#define DCM_E_GENERALREJECT                                          0x10u
#define DCM_E_SERVICENOTSUPPORTED                                    0x11u
#define DCM_E_SUBFUNCTIONNOTSUPPORTED                                0x12u
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT                  0x13u
#define DCM_E_RESPONSE_TOO_LONG                                      0x14u
#define DCM_E_BUSYREPEATREQUEST                                      0x21u
#define DCM_E_CONDITIONSNOTCORRECT                                   0x22u
#define DCM_E_REQUESTSEQUENCEERROR                                   0x24u
#define DCM_E_REQUESTOUTOFRANGE                                      0x31u
#define DCM_E_SECURITYACCESSDENIED                                   0x33u
#define DCM_E_INVALIDKEY                                             0x35u
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                                 0x36u
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED                            0x37u
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED                              0x70u
#define DCM_E_TRANSFERDATASUSPENDED                                  0x71u
#define DCM_E_GENERALPROGRAMMINGFAILURE                              0x72u
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER                              0x73u
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING               0x78u
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION                 0x7Eu
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION                     0x7Fu
#define DCM_E_RPMTOOHIGH                                             0x81u
#define DCM_E_RPMTOOLOW                                              0x82u
#define DCM_E_ENGINEISRUNNING                                        0x83u
#define DCM_E_ENGINEISNOTRUNNING                                     0x84u
#define DCM_E_ENGINERUNTIMETOOLOW                                    0x85u
#define DCM_E_TEMPERATURETOOHIGH                                     0x86u
#define DCM_E_TEMPERATURETOOLOW                                      0x87u
#define DCM_E_VEHICLESPEEDTOOHIGH                                    0x88u
#define DCM_E_VEHICLESPEEDTOOLOW                                     0x89u
#define DCM_E_THROTTLE_PEDALTOOHIGH                                  0x8Au
#define DCM_E_THROTTLE_PEDALTOOLOW                                   0x8Bu
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL                          0x8Cu
#define DCM_E_TRANSMISSIONRANGENOTINGEAR                             0x8Du
#define DCM_E_BRAKESWITCH_NOTCLOSED                                  0x8Fu
#define DCM_E_SHIFTERLEVERNOTINPARK                                  0x90u
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED                            0x91u
#define DCM_E_VOLTAGETOOHIGH                                         0x92u
#define DCM_E_VOLTAGETOOLOW                                          0x93u

typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_ProtocolType;
#define DCM_OBD_ON_CAN                                               0x00u
#define DCM_UDS_ON_CAN                                               0x01u
#define DCM_UDS_ON_FLEXRAY                                           0x02u
#define DCM_ROE_ON_CAN                                               0x03u
#define DCM_ROE_ON_FLEXRAY                                           0x04u
#define DCM_PERIODICTRANS_ON_CAN                                     0x05u
#define DCM_PERIODICTRANS_ON_FLEXRAY                                 0x06u

typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_ConfirmationStatusType;
#define DCM_RES_POS_OK                                               0x00u
#define DCM_RES_POS_NOT_OK                                           0x01u
#define DCM_RES_NEG_OK                                               0x02u
#define DCM_RES_NEG_NOT_OK                                           0x03u

typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_SesCtrlType;
#define DCM_DEFAULT_SESSION                                          0x01u
#define DCM_PROGRAMMING_SESSION                                      0x02u
#define DCM_EXTENDED_DIAGNOSTIC_SESSION                              0x03u
#define DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION                         0x04u
#define HUF_TEST_LOAD                                                0x60u
#define DCM_ALL_SESSION_LEVEL                                        0xFFu

typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_SecLevelType;
#define DCM_SEC_LEV_LOCKED                                           0x00u
#define DCM_SEC_LEV_L1                                               0x01u
#define DCM_SEC_LEV_ALL                                              0xFFu

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_12Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_12Byte_Type[12];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_17Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_17Byte_Type[17];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_5Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_5Byte_Type[5];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_24Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_24Byte_Type[24];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_3Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_3Byte_Type[3];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_8Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_8Byte_Type[8];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_1Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_1Byte_Type[1];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_20Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_20Byte_Type[20];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_4Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_4Byte_Type[4];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_16Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_16Byte_Type[16];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_7Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_7Byte_Type[7];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_2Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_2Byte_Type[2];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_11Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_11Byte_Type[11];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_10Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_10Byte_Type[10];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_18Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_18Byte_Type[18];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_80Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_80Byte_Type[80];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_100Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_100Byte_Type[100];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_15Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_15Byte_Type[15];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_13Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_13Byte_Type[13];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_48Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_48Byte_Type[48];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_27Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_27Byte_Type[27];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_0Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_0Byte_Type[1];
#endif

#if defined (VECTOR_POLYSPACE_TEST)
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_4294967295Byte_Type[];
#else
  typedef VAR(uint8, DCM_VAR_NOINIT) Dcm_4294967295Byte_Type[1];
#endif

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0102_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0102_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0102_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0102_WriteData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x010d_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x010d_ReadData(P2VAR(Dcm_17Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0120_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0120_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0140_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0140_ReadData(P2VAR(Dcm_24Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0200_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0200_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0201_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0201_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0210_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0210_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0215_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0215_ReadData(P2VAR(Dcm_20Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0215_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0215_WriteData(P2VAR(Dcm_20Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0216_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0216_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0216_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0216_WriteData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0217_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0217_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0217_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0217_WriteData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0218_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0218_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0218_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0218_WriteData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0219_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0219_ReadData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0219_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0219_WriteData(P2VAR(Dcm_5Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021a_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021a_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021b_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021b_ReadData(P2VAR(Dcm_16Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021c_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021c_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021d_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021d_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021e_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021e_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021e_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x021e_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0220_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0220_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0221_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0221_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0222_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0222_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0223_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0223_ReadData(P2VAR(Dcm_11Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0227_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0227_ReadData(P2VAR(Dcm_20Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0228_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0228_ReadData(P2VAR(Dcm_20Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0229_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0229_ReadData(P2VAR(Dcm_20Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022a_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022a_ReadData(P2VAR(Dcm_20Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022b_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022b_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022c_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022c_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022d_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022d_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022e_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x022e_ReadData(P2VAR(Dcm_10Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0231_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0231_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0231_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0231_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0242_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0242_ReadData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0242_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0242_WriteData(P2VAR(Dcm_3Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0243_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0243_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0244_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0244_ReadData(P2VAR(Dcm_18Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0245_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0245_ReadData(P2VAR(Dcm_80Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0247_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0247_ReadData(P2VAR(Dcm_100Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0249_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0249_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0249_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0249_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024a_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024a_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024a_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024a_WriteData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024b_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024b_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024b_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024b_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024c_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024c_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024c_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024c_WriteData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024d_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x024d_ReadData(P2VAR(Dcm_80Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026a_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026a_ReadData(P2VAR(Dcm_16Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026b_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026b_ReadData(P2VAR(Dcm_16Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026c_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026c_ReadData(P2VAR(Dcm_16Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026d_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x026d_ReadData(P2VAR(Dcm_16Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0271_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0271_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0271_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0271_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0273_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0273_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0274_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0274_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0277_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0277_ReadData(P2VAR(Dcm_15Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0278_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0278_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0279_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0279_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027a_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027a_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027b_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027b_ReadData(P2VAR(Dcm_12Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027c_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027c_ReadData(P2VAR(Dcm_13Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027d_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027d_ReadData(P2VAR(Dcm_13Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027e_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027e_ReadData(P2VAR(Dcm_13Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027f_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x027f_ReadData(P2VAR(Dcm_13Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0280_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0280_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0280_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0280_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0283_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x0283_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a2_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a2_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a2_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a2_WriteData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a3_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a3_ReadData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a3_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a3_WriteData(P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a4_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a4_ReadData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a4_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a4_WriteData(P2VAR(Dcm_7Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a5_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a5_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a5_ConditionCheckWrite(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02a5_WriteData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data, uint16 dataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02f9_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0x02f9_ReadData(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xef03_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xef03_ReadData(P2VAR(Dcm_8Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf100_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf100_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf103_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf103_ReadData(P2VAR(Dcm_48Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf103_ReadDataLength(P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) DidLength);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf10d_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf10d_ReadData(P2VAR(Dcm_4Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf18c_ConditionCheckRead(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_DidServices_0xf18c_ReadData(P2VAR(Dcm_27Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) data);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0201_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0203_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_4294967295Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0219_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0219_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0219_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0245_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0245_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0245_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0302_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0302_Stop(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0302_RequestResults(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_8Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0305_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0306_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0307_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0308_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0309_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x030a_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x030b_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x030c_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x030d_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x030e_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x030f_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0310_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0311_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0312_Start(P2VAR(Dcm_4Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0x0313_Start(P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_1Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_RoutineServices_0xff01_Start(P2VAR(Dcm_0Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) RequestData, uint16 RequestDataLength, P2VAR(Dcm_2Byte_Type, AUTOMATIC, DCM_VAR_NOINIT) ResponseData, P2VAR(uint16, AUTOMATIC, DCM_VAR_NOINIT) ResponseDataLength, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_SessionControl_GetSesChgPermission(Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_SessionControl_ChangeIndication(Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew);
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_SessionControl_ConfirmationRespPending(Dcm_ConfirmationStatusType status);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_ComControlService_CheckCondition(uint8 subNetId, uint8 msgType, boolean rxState, boolean txState);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) Appl_Dcm_ResetService_EcuReset(uint8 resetType, P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR_NOINIT) ErrorCode);

#ifndef SKIP_MAGIC_NUMBER
  #ifdef APPL_DCM_MAGIC_NUMBER
    #error "APPL_DCM_MAGIC_NUMBER has already been defined outside of <C:\_TSS\DAG\MFA2\Target\SWC\Appl_Dcm.h>"
  #else
#define APPL_DCM_MAGIC_NUMBER 268053759
  #endif
#endif

#endif
