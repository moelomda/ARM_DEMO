#include "APP.h"
#include "DataCollect.h"
extern u8 buzzer_flag;
RTC_t alarm;

extern void  Operation_Proc(void);
/* Define constants */
extern u8 key;
extern u8 Recived_Data;
#define PRESSED     1
extern watch_t watch;
/* Global variables */
u8 operation_state = 0;
u8 Rx_buffer[4];
u8 key_value = IDLE_KEY;
alarm_conf_t  cnf;

extern u8 Main_State ;
/* Initialization function */
extern void buzzer_on(void);
void Init_Proc()
{
	cnf.days=18;
	cnf.month=APR;
    cnf.year=24;
    cnf.hours=5;
	cnf.week=WEDN;
    cnf.minutes=42;
    cnf.mask=0x00000009;
    cnf.pv=buzzer_on;
	watch.curr_state=DISPLAY;
	NVIC_CTRL_EnableIRQ(NVIC_RCC_INTERRUPT);
   /* Initialize UART, SHED, KEYPAD, and LCD */
		RTC_t ele;
		RTC_t set;
		alarm.seconds=10;
		alarm.minutes=42;
		alarm.hours=5;
			set.days=18;
			set.months=APR;
			set.years=24;
			set.hours=5;
			set.minutes=41;
			set.seconds=50;
			set.day_name=WEDN;
			RCC_SelectClock(RCC_SYSCLK_HSI);
		RTC_Configuration_t conf={OUTPUT_DISABLED,FULL_HOUR_FORMAT};
		RCC_EnablePeri(RCC_AHB1,GPIOAEN);
		RCC_EnablePeri(RCC_AHB1,GPIOBEN);
		RCC_EnablePeri(RCC_APB1,PWREN);
		LED_Init();
		RTC_Init(&conf);
		LCD_init_HW();
		KEYPAD_voidInit();
		UART_HalInit(USARTID_1);
		//RTC_SetAlarm (ALARM_A,&cnf);
		//RTC_GetTime(&ele);
		//RTC_GetDate(&ele);
		//Disp_Date_Time(&ele);
		RTC_SetTime(&set);
		RTC_SetDate(&set);
		Uart_RxBufferAsync(USARTID_1,&Recived_Data,1,UART_CallBack);

		SCHED_Init();
		SCHED_Start();
	/* Start asynchronous reception of data from UART */
		//USART_HalGetByte();
}

/* UART callback function */
void UART_CallBack()
{
    /* Set state to OPERATION and update operation state */
	 Main_State = OPERATION;
    operation_state = Recieve_Data;
    if((Recived_Data>=0)&&(Recived_Data<=15))
    Operation_Proc();
    /* Continue asynchronous reception of data from UART */
	Uart_RxBufferAsync(USARTID_1,&Recived_Data,1,UART_CallBack);

    //Uart_RxBufferAsync( USARTID_1, Rx_buffer , 4,  UART_CallBack);
}

/* KEYPAD task function */
void KPD_Task(void)
{
    /* Get pressed key from the keypad */
    KEYPAD_enumGetPressedKey(&key_value);
    //condition
    if((key_value != IDLE_KEY))
    {
    Main_State = OPERATION;
    operation_state = Send_Data;
    Operation_Proc();

    }

}
/*void Display_Proc()
{
	u8 hours, minutes, seconds;
    u16 ss;
	u8 day ;
	char **Day;
    month_t month ;
    u8 year;
	weekday_t week;
    RTC_GetTime(&hours, &minutes, &seconds, &ss);
	LCD_ClearDisplay();
	//delay
	LCD_SetCursor(1 , 5 );
	//delay
	displayTime(hours, minutes, seconds);
	//delay
	LCD_SetCursor(2, 1);
    RTC_GetDate(day, &Day, month, year);
	//delay
	displayDate( day ,  &Day,  month ,  year);
}
void displayTime(u8 hours, u8 minutes, u8 seconds)
{
    char hourStr[3];
    char minStr[3];
    char secStr[3];
    char buffer[9];

    // Convert integers to strings
    sprintf(hourStr, "%02d", hours);
    sprintf(minStr, "%02d", minutes);
    sprintf(secStr, "%02d", seconds);

    // Concatenate strings
    strcpy(buffer, hourStr);
    strcat(buffer, ":");
    strcat(buffer, minStr);
    strcat(buffer, ":");
    strcat(buffer,secStr);
    LCD_SetCursor(1, 5);
    //delay
    LCD_WriteString(buffer);
}
void displayDate(weekday_t week, u8 days, month_t month, u8 year)
{
    char dayStr[3];
    char monthStr[3];
    char yearStr[5];
    char buffer[15]; // Increased buffer size to accommodate the date

    // Convert integers to strings
    sprintf(dayStr, "%02d", days);
    sprintf(monthStr, "%02d", month);
    sprintf(yearStr, "%04d", year);

    // Concatenate strings
    strcpy(buffer, getWeekdayString(week)); // Get weekday string representation
    strcat(buffer, " "); // Add space separator
    strcat(buffer, dayStr);
    strcat(buffer, " ");
    strcat(buffer, getMonthString(month)); // Get month string representation
    strcat(buffer, " ");
    strcat(buffer, yearStr);
    // Display the date on LCD
    LCD_SetCursor(1, 5);
    // Delay if needed
    LCD_WriteString(buffer);
}*/
void buzzer_on(void){
	buzzer_flag=1;
}
