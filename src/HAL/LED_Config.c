/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/
#include "std_types.h"
#include "LED.h"
#include "LED_Config.h"

Led_Configuration_t LEDS[_Led_Num]={

	[front_led]={
	LED_GPIO_PORT_B,LED_GPIO_PIN_0,LED_FORWARD,LED_OFF}
/*
	[back_led]={
	LED_GPIO_PORT_A,LED_GPIO_PIN_1,LED_FORWARD,LED_OFF},

	[reer_led]={
	LED_GPIO_PORT_A,LED_GPIO_PIN_2,LED_FORWARD,LED_OFF}*/
};












