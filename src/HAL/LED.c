/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/
#include "std_types.h"
#include "LED.h"
#include "GP.h"
extern Led_Configuration_t LEDS[_Led_Num];
//#define LOW_SPEED_MODE                            0
//#define OUTPUT_PUSH_PULL_UP                       0

/**********************************************************************************************/
LED_enumRetErrorState_t LED_Init(void ){
    LED_enumRetErrorState_t RetErrorState_Init=RetErrorState_LED_OK;
	Pin_Configuration_t obj;

		obj.Speed=LOW_SPEED_MODE;
		obj.Mode=OUTPUT_PUSH_PULL;
		for(u8 iter=0;iter<_Led_Num;iter++){
			obj.Port=LEDS[iter].Port;
			obj.Pin=LEDS[iter].Pin;
			GPIO_InitPin(&obj);
			//GPIO_SetPinValue(obj,);
		}
    return	RetErrorState_Init;
}
/**********************************************************************************************/
LED_enumRetErrorState_t LED_On(Led_Alias_List_t Led_Alias){
	Pin_Configuration_t obj;
    LED_enumRetErrorState_t RetErrorState_LED_On=RetErrorState_LED_OK;
	obj.Port=LEDS[Led_Alias].Port;
	obj.Pin=LEDS[Led_Alias].Pin;
	GPIO_SetPinValue(&obj,(LED_ON^(LEDS[Led_Alias].Polarity)));
	//GPIO_SetPinValue(&obj,0);
    return	RetErrorState_LED_On;
}
/**************************************************************************************************************/
LED_enumRetErrorState_t LED_Off(Led_Alias_List_t Led_Alias){
	Pin_Configuration_t obj;
    LED_enumRetErrorState_t RetErrorState_LED_Off=RetErrorState_LED_OK;
	obj.Port=LEDS[Led_Alias].Port;
	obj.Pin=LEDS[Led_Alias].Pin;
	GPIO_SetPinValue(&obj,(LED_OFF^(LEDS[Led_Alias].Polarity)));
    return	RetErrorState_LED_Off;
}
/**************************************************************************************************************/
LED_enumRetErrorState_t LED_Toggle(Led_Alias_List_t Led_Alias){
	LEDS[Led_Alias].state = LEDS[Led_Alias].state^0x01;
u32 curr_state=LEDS[Led_Alias].state;
	Pin_Configuration_t obj;
    LED_enumRetErrorState_t RetErrorState_LED_Off=RetErrorState_LED_OK;
	obj.Port=LEDS[Led_Alias].Port;
	obj.Pin=LEDS[Led_Alias].Pin;
	GPIO_SetPinValue(&obj,(curr_state^(LEDS[Led_Alias].Polarity)));

    return	RetErrorState_LED_Off;
}

void toggleled1(void){
    //LED_Toggle(front_led);
}
void toggleled2(void){
  //  LED_Toggle(back_led);
}






