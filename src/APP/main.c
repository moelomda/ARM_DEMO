
#include "APP.h"

#include "DataProcessing.h"

extern RTC_t alarm;
 u8 buzzer_state=0;
/* Define states enumeration */
u8 Main_State = INIT;
extern watch_t watch;
extern char* weekdays[8];
extern char* months[13];
void Disp_Date_Time(RTC_t* ele);
u8 time_str[9];
u8 date_str[16];
u8 stop_watch_str[9];
RTC_t elem;
RTC_t set;
u8 key='D';
u8 buzzer_flag=0;
void ACTION_Task(void);
void  main (void)
{

	Init_Proc();


}

/*
void display_task()
{

if(watch.curr_state==DISPLAY)
{
	RTC_GetTime(&watch.watch);
	RTC_GetDate(&watch.watch);
	WATCH_DispDateTime(&watch.watch);
}
}*/

void DISPLAY_Task(void){
	if(watch.curr_state==DISPLAY)
	{
		//RTC_GetTime (&watch.wa
		//RTC_GetDate (&watch.watch);
		Disp_Date_Time(&watch.watch);
	}
}
void Disp_Date_Time(RTC_t* ele){
	//u8 date_str[12];

		//LCD_DisplayClear();
	    sprintf(time_str,"%02d:%02d:%02d",ele->hours,ele->minutes,ele->seconds);
	    //LCD_Go_To_Location_Async(0,4);
	    LCD_Write_String_Async(time_str,9,0,4);
		sprintf(date_str,"%s %02d/%s/%04d",weekdays[ele->day_name],ele->days,months[ele->months],(ele->years)+2000);
		//LCD_Go_To_Location_Async(1,0);
		LCD_Write_String_Async(date_str,16,1,0);
        LCD_Go_To_Location_Async(0,0);


}
void Stop_Watch_runnable(void)
{
    static u8  seconds = 0;
    static u8  minutes = 0;
    static u8  hours = 0;
if(watch.curr_state==DISPLAY){
	 RTC_GetDate(&watch.watch);
	    RTC_GetTime(&watch.watch);
		if((alarm.hours==watch.watch.hours)&&(alarm.minutes==watch.watch.minutes)&&(alarm.seconds==watch.watch.seconds) ){
			buzzer_flag=1;
		}

    LCD_Cursor_Off_Async();

	    Disp_Date_Time(&watch.watch);

}
else{
    switch(key) //start
    {
    case 'A':
    	seconds++;

        if (seconds == 60)
        {
            seconds = 0;
            minutes++;
        }
        if (minutes == 60)
        {
            minutes = 0;
            hours++;
        }
        LCD_Clear_Screen_Async();
        sprintf(stop_watch_str,"%02d:%02d:%02d",hours,minutes,seconds);
       // LCD_GoToXY(0,4);
        LCD_Write_String_Async(&stop_watch_str,9,0,4);
        break;
    case 'B':

        LCD_Clear_Screen_Async();
		//LCD_GoToXY(0,4);
        LCD_Write_String_Async(&stop_watch_str,9,0,4);

        break;
    case 'C':
        seconds = 0;
        minutes = 0;
        hours = 0;
        LCD_Clear_Screen_Async();

        sprintf(stop_watch_str,"%02d:%02d:%02d",hours,minutes,seconds);
     //   LCD_GoToXY(0,4);
        LCD_Write_String_Async(&stop_watch_str,9,0,4);
    break;
}
}
}
/*
void ACTION_Task(void){
ACTION_Get(4);
}*/
void Buzzer_Runnable(void){
static u8 counter = 0;
if(buzzer_flag==1){
    if (counter <= 10)
    {
        counter++;

        LED_Toggle(front_led);
    }
    if(counter==11){
    	buzzer_flag=0;
    	counter=0;
    }
}
}
