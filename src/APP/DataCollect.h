#include "UART_Hal.h"
#include "NVIC.h"
#include "RCC.h"
#include "SYSTICK.h"
#include "SCHED.h"
#include "LCD.h"
#include "std_types.h"
#include "KEYPAD.h"
#include "GPIO.h"
#include <string.h>
#include <stdio.h>
typedef enum
{
    INIT,
    IDLE,
    OPERATION,
    MODE,
} States_enu_t;
typedef enum
{
Send_Data,
Recieve_Data,
}Operation_State;
void Display_Proc();
void UART_CallBack();
void Init_Proc();
void KPD_Task();
/*void displayTime(u8 hours, u8 minutes, u8 seconds);
void displayDate(weekday_t week, u8 days, month_t month, u8 year);*/
