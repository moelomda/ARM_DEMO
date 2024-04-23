#ifndef SYSTICK_H
#define SYSTICK_H

#include "Std_Types.h"

#define SYSTICK_CLOCK_SOURCE        16000000

#define SYSTICK_AHB_8_NOEXCEPTION   0x00000000
#define SYSTICK_AHB_8_EXCEPTION     0x00000002
#define SYSTICK_AHB_NOEXCEPTION     0x00000004
#define SYSTICK_AHB_EXCEPTION       0x00000006

#define SYSTICK_ONE_TIME_MODE   0x01
#define SYSTICK_PERIODIC_MODE   0x00

typedef void(*SysTick_CallBack_t)(void);

typedef enum
{
    SYSTICK_OK,
    SYSTICK_NOK

}SYSTICK_Error_Status_t;

SYSTICK_Error_Status_t SYSTICK_Set_Configuration(u32 configuration, u8 Mode);

void SYSTICK_Start(void);

void SYSTICK_Stop(void);

SYSTICK_Error_Status_t SYSTICK_Set_Time_Ms(u32 Time_Ms);

void SYSTICK_Is_Expired(void);

SYSTICK_Error_Status_t SYSTICK_SetCallBack(SysTick_CallBack_t cb);

#endif
/*SYSTICH_H*/
