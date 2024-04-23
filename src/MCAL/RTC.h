/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/

#ifndef RTC_H_
#define RTC_H_
#include "STD_TYPES.h"


/*char* weekdays[8] = {"FORB","MON","TUE","WED","THU","FRI","SAT","SUN"};
char* months[13] = {"FORBIDDEN","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
*/


typedef struct{   
u8 OSEL;
u8 fmt;
}RTC_Configuration_t;


typedef enum{
JAN=1,
FEB,
MAR,
APR,
MAY,
JUN,
JUL,
AUG,
SEP,
OCT,
NOV,
DEC
}month_t;

typedef enum{
MON=1,
TUE,
WEDN,
THUR,
FRI,
SAT,
SUN
}weekday_t;

typedef struct {
u8 days;
month_t months;
weekday_t day_name;
u8 years;
u8 hours;
u8 minutes;
u8 seconds;
u16 ss;
}RTC_t;
typedef struct {
u8 days;
weekday_t week;
month_t month;
u8 year;
u8 hours;
u8 minutes;
u8 seconds;
u16 ss;
u32 mask;
pointer_cbf_t pv;
}alarm_conf_t;

typedef enum{
 ALARM_A,
 ALARM_B
}ALARM_ID_t;


/*******************************************************/
/*OPTIONS FOR WUTCKSEL*/
#define RTC_OVER_16           0
#define RTC_OVER_8            1
#define RTC_OVER_4            2
#define RTC_OVER_2            3
#define ck_spre               5
#define ck_spre_ADDITION      7

/*******************************************************/
/*OPTIONS FOR OSEL*/
#define OUTPUT_DISABLED                 0
#define ALARM_A_OUTPUT_ENABLED          1
#define ALARM_B_OUTPUT_ENABLED          2
#define WAKEUP_OUTPUT_ENABLED           3
/************************************************************/
/*OPTIONS FOR alarm mask **
BIT 0:MASK   1
BIT 1:MASK   2
BIT 2:MASK   3
BIT 3:MASK   4
BIT 4:SS_MASK   
BIT 5:SS_MASK
BIT 6:SS_MASK
BIT 7:SS_MASK
*/

/*options for fmt*/
#define FULL_HOUR_FORMAT     0
#define AM_PM_FORMAT         1
/****************************************************************************************************/
void RTC_Init(RTC_Configuration_t*conf );
void RTC_SetTime(RTC_t *ele);
void RTC_SetDate(RTC_t *ele);
void RTC_GetTime(RTC_t *ele);
void RTC_GetDate(RTC_t *ele);
void RTC_SetAlarm (ALARM_ID_t id,alarm_conf_t* conf);
void RTC_SetWakeUpTim(u8 wucksel,u16 value,pointer_cbf_t pv);
void RTC_SetTimeStamb(pointer_cbf_t pv);
void RTC_Alarm_IRQHandler(void);
void RTC_WKUP_IRQHandler(void);
void TAMP_STAMP_IRQHandler(void);

#endif 
