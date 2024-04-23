#include "APP.h"
#include "STD_TYPES.h"
#include "SCHEDULER.h"
#include "LCD_CFG.h"
#include "LCD.h"
#include "RTC_Config.h"
#include "KEYPAD.h"
#include "RCC.h"
#include "RTC.h"

extern key;
 extern char* weekdays[8] ;
 extern char* months[13] ;
 extern RTC_t alarm;

 void Disp_Date_Time(RTC_t* ele);
extern u8 Recived_Data;
watch_t watch;
RTC_t edit;
//RTC_t watch_rtc;
pointer_cbf_t commands[16]={arrow_up,arrow_down,arrow_right,arrow_left,edit_mode,ok,mode,reset,pause_resume,set_alarm,noopper,noopper,noopper,noopper,noopper,noopper};
void ACTION_Get(u8 command){
commands[command]();
}
/***********************************************/
static void noopper(void){
	
}
/**************************************************************/
static void set_alarm(void){
	if(watch.curr_state==DISPLAY){
	        watch.curr_state=SET_ALARM;
	        Disp_Date_Time(&watch.watch);
	        LCD_Cursor_On_Async();
	        watch.curr_x=0;
	        watch.curr_y=0;

	    	LCD_Go_To_Location_Async(0,0);

	        edit=watch.watch;

	    }
}
/***************************************************************/
static void arrow_up(void){
//LCD_SetCursor(u8 Copy_u8Row, u8 Copy_u8Col);
    //watch.curr_state=EDIT_TIME;

if(watch.curr_state==EDIT){

	Disp_Date_Time(&watch.watch);
	watch.curr_x^=0x01;
	LCD_Go_To_Location_Async(watch.curr_x,0);

}
else if((watch.curr_state==EDIT_TIME)||(watch.curr_state==SET_ALARM)){
    if((watch.curr_y==8)||(watch.curr_y==7)){
        edit.minutes=(edit.minutes+1)%60;
    }   
    /*else if(watch.curr_y==7){
        edit.minutes=(edit.minutes+10)%60;
    }*/
    else if((watch.curr_y==4)||(watch.curr_y==5)){
        edit.hours=(edit.hours+1)%24;
    }
    /*else if(watch.curr_y==4){
        edit.hours=(edit.hours+10)%24;
    }*/
    else if((watch.curr_y==11)||(watch.curr_y==10)){
        edit.seconds=(edit.seconds+1)%60;
    }
    /*else if(watch.curr_y==10){
        edit.seconds=(edit.seconds+10)%60;
    }*/
    Disp_Date_Time(&edit);
    LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);

}
else if(watch.curr_state==EDIT_DATE){
    if(watch.curr_y==1||watch.curr_y==2||watch.curr_y==0){
        edit.day_name=(edit.day_name+1);
        if((edit.day_name)==8)
        	edit.day_name=1;

    }   
   /* else if(watch.curr_y==5){
        edit.days=(edit.days+10)%30;
        if(edit.days==0)
        edit.days=30;
    }*/
    else if((watch.curr_y==4)||(watch.curr_y==5)){
        edit.days=(edit.days+1)%32;
        if(edit.days==0)
        edit.days=1;
    }
    else if(watch.curr_y==8||watch.curr_y==9||watch.curr_y==7){
        edit.months=(edit.months+1);
        if(edit.months==13)
             edit.months=1;
    }/*
    else if(watch.curr_y==14){
        edit.years=(edit.years+10)%100;
    }*/
    else if((watch.curr_y==13)||(watch.curr_y==14)||(watch.curr_y==12)||(watch.curr_y==11)){
        edit.years=(edit.years+1)%100;
    }
    Disp_Date_Time(&edit);
        if((watch.curr_y==1||watch.curr_y==2||watch.curr_y==0)){
        LCD_Go_To_Location_Async(1,3);
        watch.curr_x=1;
        watch.curr_y=2;
        }
        else
        LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);

}
}
/*****************************************************************************/
static void arrow_down(void){
	if(watch.curr_state==EDIT){

		Disp_Date_Time(&watch.watch);
		watch.curr_x^=0x01;
		LCD_Go_To_Location_Async(watch.curr_x,0);

	}
else if((watch.curr_state==EDIT_TIME)||(watch.curr_state==SET_ALARM)){
    if((watch.curr_y==8)||(watch.curr_y==7)){
        edit.minutes=((edit.minutes-1)+60)%60;
    }   
    /*else if(watch.curr_y==7){
        edit.minutes=((edit.minutes-10)+60)%60;
    }*/
    else if((watch.curr_y==5)||(watch.curr_y==4)){
        edit.hours=((edit.hours-1)+24)%24;
    }
    /*else if(watch.curr_y==4){
        edit.hours=((edit.hours-10)+24)%24;
    }*/
    else if((watch.curr_y==11)||(watch.curr_y==10)){
        edit.seconds=((edit.seconds-1)+60)%60;
    }
    /*
    else if(watch.curr_y==10){
        edit.seconds=((edit.seconds-10)+60)%60;
    }*/
    Disp_Date_Time(&edit);
    LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);
}
else if(watch.curr_state==EDIT_DATE){
    if(watch.curr_y==1||watch.curr_y==2||watch.curr_y==0){
        edit.day_name=((edit.day_name-1)+7)%7;
        	if(edit.day_name==0)
        		edit.day_name=7;
    }
    /*
    else if(watch.curr_y==5){
        edit.days=(edit.days+10)%30;
    }*/
    else if((watch.curr_y==4)||(watch.curr_y==5)){
        edit.days=(edit.days-1)%32;
        if(edit.days==0)
        	edit.days=31;
    }
    else if(watch.curr_y==8||watch.curr_y==9||watch.curr_y==7){
        edit.months=(edit.months-1);
        if(edit.months==0)
        	edit.months=12;

    }/*
    else if(watch.curr_y==14){
        edit.years=((edit.years-10)+100)%100;
    }*/
    else if((watch.curr_y==13)||(watch.curr_y==14)||(watch.curr_y==12)||(watch.curr_y==11)){
        edit.years=((edit.years-1)+100)%100;
    }
    if((watch.curr_y==1||watch.curr_y==2||watch.curr_y==0))
        LCD_Go_To_Location_Async(1,3);

    Disp_Date_Time(&edit);
    if((watch.curr_y==1||watch.curr_y==2||watch.curr_y==0)){
            LCD_Go_To_Location_Async(1,3);
            watch.curr_x=1;
            watch.curr_y=2;
            }
    else
    LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);

}
}
/*****************************************************************************/
static void arrow_right(void){
if((watch.curr_state==EDIT_TIME)||(watch.curr_state==EDIT_DATE)||(watch.curr_state==SET_ALARM)){
	watch.curr_y++;
    watch.curr_y=(watch.curr_y%16);
    Disp_Date_Time(&edit);
    LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);


}
    
}
/****************************************************************************/
static void arrow_left(void){
if((watch.curr_state==EDIT_TIME)||(watch.curr_state==EDIT_DATE)||(watch.curr_state==SET_ALARM)){
    if(watch.curr_y==0){
    watch.curr_y=15;
    Disp_Date_Time(&edit);
    LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);
    }
    else{
    	watch.curr_y--;
    	    watch.curr_y=(watch.curr_y%16);
    	    Disp_Date_Time(&edit);
    	    LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);
    }

}
    
}
/******************************************************************/
static void edit_mode(void){
    
    if(watch.curr_state==DISPLAY){
        watch.curr_state=EDIT;
        LCD_Cursor_On_Async();
        watch.curr_x=0;
        watch.curr_y=0;
        LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);
        edit=watch.watch;

    }
    else if(watch.curr_state==EDIT){
        if(watch.curr_x==0){
        watch.curr_state=EDIT_TIME;
        LCD_Clear_Screen_Async();
        LCD_Cursor_On_Async();
        RTC_GetDate(&edit);
        RTC_GetTime(&edit);
        Disp_Date_Time(&edit);
        }
        else if(watch.curr_x==1){
        watch.curr_state=EDIT_DATE;
        LCD_Clear_Screen_Async();
        LCD_Cursor_On_Async();
        RTC_GetDate(&edit);
        RTC_GetTime(&edit);
        Disp_Date_Time(&edit);
        LCD_Go_To_Location_Async(1,0);

        }
        //LCD_Go_To_Location_Async(watch.curr_x,watch.curr_y);

       // LCD_Go_To_Location_Async(0,0);
    }

}
/*******************************************************************************/
static void mode(void){
if(watch.curr_state== DISPLAY){
    watch.curr_state=STOP_WATCH;
    LCD_Clear_Screen_Async();
    LCD_Write_String_Async((u8 *)"00:00:00",9,0,4);
	//LCD_GoToXY(0,4);
}
else/* if(watch.curr_state==STOP_WATCH||watch.curr_state==STOP_WATCH_PAUSED||
watch.curr_state==STOP_WATCH_RESUMED||watch.curr_state==EDIT)*/{
    watch.curr_state=DISPLAY;
        //key=;
    RTC_GetDate(&watch.watch);
    RTC_GetTime(&watch.watch);
    Disp_Date_Time(&watch.watch);
    key='D';
}
}
/************************************************************************/
static void on_off(void){

    
}
/*************************************************************/
static void ok(void){
if(watch.curr_state==EDIT_TIME||watch.curr_state==EDIT_DATE||watch.curr_state==SET_ALARM){

    if(watch.curr_state==SET_ALARM){
    alarm.hours=edit.hours;
    alarm.minutes=edit.minutes;
    alarm.seconds=edit.seconds;
    }
    else{
    	RTC_SetTime(&edit);
    	RTC_SetDate(&edit);
    	watch.watch=edit;
        Disp_Date_Time(&edit);
    }
    watch.curr_state=DISPLAY;


}
//try to move in edit mode at the same time
}

/***********************************************************/
static void reset(void){
if(watch.curr_state==STOP_WATCH_PAUSED||watch.curr_state==STOP_WATCH_RESUMED){
    watch.curr_state=STOP_WATCH;
        key='C';

}
}
/*******************************************/
static void pause_resume(void){
if(watch.curr_state==STOP_WATCH_RESUMED){
    watch.curr_state=STOP_WATCH_PAUSED;
    key='B';
   // LCD_Write_String_Async((u8 *)"Omarel3w",9,0,4);
}
else if(watch.curr_state==STOP_WATCH_PAUSED||watch.curr_state==STOP_WATCH){
    watch.curr_state=STOP_WATCH_RESUMED;
       key='A';
     //  LCD_Write_String_Async((u8 *)"el3wOmar",9,0,4);
}
}

/**********************************************************************************************************************/
