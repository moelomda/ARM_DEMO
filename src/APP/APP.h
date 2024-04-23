/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/

#ifndef APP_H_
#define APP_H_
#include "std_types.h"
#include "SCHED.h"
#include "LCD_cfg.h"
#include "LCD.h"
#include "RTC_Config.h"
#include "KEYPAD.h"
#include "RCC.h"
#include "RTC.h"
#include "UART_Hal.h"
#include "LED.h"
#include "LED_Config.h"
#include "GP.h"
#include <stdio.h>
typedef enum {
DISPLAY,
EDIT,
EDIT_TIME,
EDIT_DATE,
STOP_WATCH,
STOP_WATCH_PAUSED,
STOP_WATCH_RESUMED,
SET_ALARM
}watch_mode;
typedef struct 
{
watch_mode prev_state;
watch_mode curr_state;
RTC_t watch;
u8 curr_x;
u8 curr_y;
}watch_t;

static void arrow_up(void);
static void arrow_down(void);
static void arrow_right(void);
static void arrow_left(void);
static void mode(void);
static void edit_mode(void);
static void on_off(void);
static void ok(void);
//static void pause(void);
static void noopper(void);
static void reset(void);
static void pause_resume(void);
static void set_alarm(void);

//void Disp_Date_Time(RTC_t *ele);
//void ACTION_Get(u8 command);
#endif
