#include "SYSTICK.h"

#define SYSTICK_CONTROL_REG_MASK  0xFFFFFFF9

#define SYSTICK_DISABLE           0xFFFFFFFE
#define SYSTICK_ENABLE            0x00000001

#define COUNT_FLAG  16
#define READ_BIT    0x01

#define SYSTICK_MAX_RELOAD_VALUE  0x00FFFFFF

static SysTick_CallBack_t cbf = NULL;

static u8 SYSTICK_Mode;

typedef struct SYSTICK
{
    u32 STK_CTRL;
    u32 STK_LOAD;
    u32 STK_VAL;
    u32 STK_CALIB;

}SYSTICK_peri_t;

volatile SYSTICK_peri_t *const SYSTICK = (volatile SYSTICK_peri_t *)0xE000E010;

SYSTICK_Error_Status_t SYSTICK_Set_Configuration(u32 configuration, u8 Mode)
{
    SYSTICK_Error_Status_t return_state = SYSTICK_OK;

    if (configuration != SYSTICK_AHB_8_NOEXCEPTION && configuration != SYSTICK_AHB_8_EXCEPTION && \
        configuration != SYSTICK_AHB_NOEXCEPTION   && configuration != SYSTICK_AHB_EXCEPTION)
    {
        return_state = SYSTICK_NOK;
    }
    else if (Mode > SYSTICK_ONE_TIME_MODE)
    {
        return_state = SYSTICK_NOK;
    }
    else
    {
        SYSTICK_Mode = Mode;
        u32 Loc_Reg_Value = SYSTICK->STK_CTRL;
        Loc_Reg_Value &= SYSTICK_CONTROL_REG_MASK;
        Loc_Reg_Value |= configuration;
        SYSTICK->STK_CTRL = Loc_Reg_Value;
    }

    return return_state;
}

void SYSTICK_Start(void)
{
    SYSTICK->STK_VAL = 0;
    SYSTICK->STK_CTRL |= SYSTICK_ENABLE;
}

void SYSTICK_Stop(void)
{
    SYSTICK->STK_CTRL &= SYSTICK_DISABLE;
}

void SYSTICK_Is_Expired(void)
{  
    while(!((SYSTICK->STK_CTRL >> COUNT_FLAG) & READ_BIT));   
}

SYSTICK_Error_Status_t SYSTICK_Set_Time_Ms(u32 Time_Ms)
{
    SYSTICK_Error_Status_t return_state = SYSTICK_OK;

    u32 Preload_Value = (Time_Ms * (SYSTICK_CLOCK_SOURCE/1000))-1;

    if (Preload_Value > SYSTICK_MAX_RELOAD_VALUE)
    {
        return_state = SYSTICK_NOK;
    }
    else
    {
        SYSTICK->STK_LOAD = Preload_Value;
    }

    return return_state;
}

SYSTICK_Error_Status_t SYSTICK_SetCallBack(SysTick_CallBack_t cb)
{
    SYSTICK_Error_Status_t return_state = SYSTICK_OK;

    if (cb)
    {
        cbf = cb;
    }
    else
    {
        return_state = SYSTICK_NOK;
    }

    return return_state;
}

void SysTick_Handler (void)
{
    if (cbf)
    {
        cbf();
    }

    if(SYSTICK_Mode)
    {
        SYSTICK->STK_LOAD = 0;
        SYSTICK->STK_VAL = 0;
    }
}