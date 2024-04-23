/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/
#include "std_types.h"
#include "RTC.h"

#include "RTC_Config.h"
char* weekdays[8] = {"FOR","MON","TUE","WED","THU","FRI","SAT","SUN"};
char* months[13] = {"FOR","JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"};
pointer_cbf_t alarm_a_cb=NULL;
pointer_cbf_t alarm_b_cb=NULL;
pointer_cbf_t WU_cb=NULL;
pointer_cbf_t time_stamp_cb=NULL;

#define WP_FIRST_KEY     0xCA
#define WP_SECOND_KEY    0x53
#define PWR_CR    (*(volatile u32*)0x40007000)
#define ALRAE    8
#define ALRBE    9
#define WUTE     10
#define TSE      11
#define ALRAIE    12
#define ALRBIE    13
#define WUTIE       14
#define TSIE       15
#define ALRAF   8
#define ALRBF   9
#define WUTF     10
#define TSF      11
#define RCC_BDCR      (*(volatile u32*)0x40023870)
#define RCC_CSR      (*(volatile u32*)0x40023874)
#define WPR      (*(volatile u32*)0x40002824)
#define RCC_CR      (*(volatile u32*)0x40002808)
typedef struct{   
u32 RTC_TR;        			  
u32 RTC_DR;   
u32 RTC_CR;      
u32 RTC_ISR;  	  
u32 RTC_PRER ; 
u32 RTC_WUTR;
u32 RTC_CALIBR ; 	  
u32 RTC_ALRMAR  ;    
u32 RTC_ALRMBR ;
u32 RTC_WPR ;	
u32 RTC_SSR ;			  
u32 RTC_SHIFTR ;	
u32 RTC_TSTR ;			  
u32 RTC_TSDR ;			  
u32 RTC_TSSSR ;		
u32 RTC_CALR ;			  
u32 RTC_TAFCR ;		
u32 RTC_ALRMASSR ;			  
u32 RTC_ALRMBSSR ;			  
u32 RTC_BKPxR ;	
}RTC_Registers_t;
volatile RTC_Registers_t* RTC=(volatile RTC_Registers_t*)0x40002800;



/**********************************************************************************************/
void RTC_Init(RTC_Configuration_t*conf ){
	u32 local_temp=0;


	PWR_CR |=(0x00001<<8);
	//RCC_CSR|=0x00000001;
	RCC_BDCR=0x00000001;

	RCC_BDCR|=(0x00000001<<8)|(0x00001<<15);
	//RTC->RTC_WPR=WP_FIRST_KEY;
    WPR=WP_FIRST_KEY;
	WPR=WP_SECOND_KEY;

   // RTC->RTC_WPR=WP_SECOND_KEY;

	//RTC->RTC_ISR|=(0x001<<7);
	//while(((RTC->RTC_ISR&0x00000040)>>6)==0);
    local_temp=PREDEV_S|(PREDEV_A<<16);
    RTC->RTC_PRER=local_temp;
    local_temp=0;
    local_temp|=(conf->fmt<<6)|(BYPSHAD<<5)|(conf->OSEL<<21);
    RTC->RTC_CR=local_temp;
    //RTC->RTC_ISR&=~(0x01<<7);


}
/**********************************************************************************************/
void RTC_SetTime(RTC_t *ele){
	u32 local_temp=0;
	u32 local_temp_2=0;
	WPR=WP_FIRST_KEY;
	WPR=WP_SECOND_KEY;
	RTC->RTC_ISR|=(0x001<<7);
	//while((((RTC->RTC_ISR)&0x00000040)>>6)==0);
	while( ((RTC->RTC_ISR >> 6) & 0x01) ==0){

}
	local_temp=(ele->seconds%10)|((ele->seconds/10)<<4)|((ele->minutes%10)<<8)
	|((ele->minutes/10)<<12)|((ele->hours%10)<<16)|((ele->hours/10)<<20);
    RTC->RTC_TR=local_temp;

   // RTC->RTC_ISR&=~(0x01<<7);


}
/**************************************************************************************************************/
void RTC_SetDate (RTC_t *ele){
	u32 local_temp=0;
	WPR=WP_FIRST_KEY;
	WPR=WP_SECOND_KEY;
	//RTC->RTC_ISR|=(0x01<<7);
	while( ((RTC->RTC_ISR >> 6) & 0x01) ==0){

	}
local_temp=(ele->days%10)|((ele->days/10)<<4)|((ele->months%10)<<8)|
((ele->months/10)<<12)|(ele->day_name<<13)|((ele->years%10)<<16)|((ele->years/10)<<20);
RTC->RTC_DR=local_temp;
RTC->RTC_ISR&=~(0x01<<7);

}

/**********************************************************************************************/
void RTC_GetTime(RTC_t *ele){
u32 local_temp=RTC->RTC_TR;
ele->seconds=(local_temp&0xF)+((local_temp&0x70)>>4)*10;
ele->minutes=((local_temp&0xF00)>>8)+((local_temp&0x7000)>>12)*10;
ele->hours=((local_temp&0xF0000)>>16)+((local_temp&0x300000)>>20)*10;
local_temp=RTC->RTC_TSSSR;
ele->ss=(local_temp&0xFFFF);

}
/**************************************************************************************************************/
void RTC_GetDate(RTC_t *ele){
u32 local_temp=RTC->RTC_DR;
ele->days=(local_temp&0xF)+((local_temp&0x30)>>4)*10;
ele->months=((local_temp&0xF00)>>8)+(((local_temp&0x1000)>>12)*10);
ele->years=((local_temp&0xF0000)>>16)+(((local_temp&0xF00000)>>20)*10);
ele->day_name=((local_temp&0xE000)>>13);

}
/******************************************************************************/
void RTC_SetAlarm (ALARM_ID_t id,alarm_conf_t* conf){
u32 local_temp=0;
u32 local_temp_2=0;
local_temp=(conf->seconds%10)|((conf->seconds/10)<<4)|((conf->minutes%10)<<8)|((conf->minutes/10)<<12)
|((conf->hours%10)<<16)|((conf->hours/10)<<20)|((conf->days%10)<<24)|((conf->days/10)<<28)|((conf->mask&0x1)<<7)
|((conf->mask&0x2)<<14)|((conf->mask&0x4)<<21)|((conf->mask&0x8)<<28);
local_temp_2|=conf->ss|((conf->mask&0x000000F0)<<20);
if(id==ALARM_A){
	RTC->RTC_CR&=~(0x00001100);
	while((RTC->RTC_ISR&0x00000001)==0);
	RTC->RTC_ALRMAR=local_temp;
	RTC->RTC_ALRMASSR=local_temp_2;
	alarm_a_cb=conf->pv;
	RTC->RTC_CR|=(0x00001100);
}
else{
	RTC->RTC_CR&=~(0x00002200);
	RTC->RTC_ALRMBR=local_temp;
	RTC->RTC_ALRMBSSR=local_temp_2;
	alarm_b_cb=conf->pv;
	RTC->RTC_CR|=(0x00002200);
}

}

/************************************************************************************************************/
void RTC_SetWakeUpTim(u8 wucksel,u16 value,pointer_cbf_t pv){
u32 local_temp=0;
local_temp|=(0x000001<<WUTIE)|(0x000001<<WUTE)|(wucksel);
RTC->RTC_CR=local_temp;
RTC->RTC_WUTR=value;
WU_cb=pv;
}
/***********************************************************************************************************/
void RTC_SetTimeStamb(pointer_cbf_t pv){
u32 local_temp=0;
local_temp|=(0x000001<<TSIE)|(0x000001<<TSE);
RTC->RTC_CR=local_temp;
time_stamp_cb=pv;
}
/***********************************************************************************************************/
void RTC_Alarm_IRQHandler(void){
if((((0x00000001<<ALRAF)&RTC->RTC_ISR)>>ALRAF)==1){
	if(alarm_a_cb)
	alarm_a_cb();
}
else if((((0x00000001<<ALRBF)&RTC->RTC_ISR)>>ALRBF)==1){
	if(alarm_b_cb)
	alarm_b_cb();
}

}
/***********************************************************************************************/
void RTC_WKUP_IRQHandler(void){
if((((0x00000001<<WUTF)&RTC->RTC_ISR)>>WUTF)==1){
	if(WU_cb)
	WU_cb();
}
}
/*******************************************************************************************/
void TAMP_STAMP_IRQHandler(void){
if((((0x00000001<<TSF)&RTC->RTC_ISR)>>TSF)==1){
if(time_stamp_cb)
time_stamp_cb();
}
}
/*****************************************************************************************************/



