

#if (!defined SCRC_CRC8H2F_H)
#define SCRC_CRC8H2F_H



#include <SCrc.h>              
#if (SCRC_FUNCENABLED_SCRC_CRC8H2F == STD_OFF)
#include <Crc.h>
#endif 



#if (SCRC_FUNCENABLED_SCRC_CRC8H2F == STD_OFF)

#if (defined SCrc_CalculateCRC8H2F) 
#error SCrc_CalculateCRC8H2F is already defined
#endif


#define SCrc_CalculateCRC8H2F(data,length,startvalue,isfirstcall) \
   Crc_CalculateCRC8H2F((data),(length),(startvalue),(isfirstcall))

#endif 





#if (SCRC_FUNCENABLED_SCRC_CRC8H2F == STD_ON)

#define SCRC_START_SEC_CODE
#include <MemMap.h>


extern FUNC(uint8, SCRC_CODE) SCrc_CalculateCRC8H2F
(
    P2CONST(uint8, AUTOMATIC, SCRC_APPL_DATA) SCrc_DataPtr,
    uint32                                    SCrc_Length,
    uint8                                     SCrc_StartValue8H2F,
    boolean                                   SCrc_IsFirstCall
);

#define SCRC_STOP_SEC_CODE
#include <MemMap.h>

#endif 









#endif 

