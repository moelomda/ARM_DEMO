/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/
#include "std_types.h"
#include "GP.h"


#define PIN_MODE_MASK   0x00000003
#define PIN_MODE_CATEGORY_DIVIDOR    6
#define SET_PIN_VALUE_MASK    0x00000001


typedef struct{   
u32 GPIO_MODER;        			  
u32 GPIO_OTYPER;   
u32 GPIO_OSPEEDR;      
u32 GPIO_PUPDR;  	  
u32 GPIO_IDR ; 
u32 GPIO_ODR;
u32 GPIO_BSRR ; 	  
u32 GPIO_LCKR  ;    
u32 GPIO_AFRL ;
u32 GPIOx_AFRH ;			  
}GPIO_Registers_t;
/***********************************************************************/
GPIO_enumRetErrorState_t GPIO_InitPin(Pin_Configuration_t*gpio ){
	u32 Local_u32Temp=0;
    GPIO_enumRetErrorState_t RetErrorState_InitPin=RetErrorState_GPIO_OK;
	
	if(((gpio->Port)<GPIO_PORT_A)||((gpio->Port)>GPIO_PORT_H))
	RetErrorState_InitPin=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;

	else if(((gpio->Pin)<GPIO_PIN_0)||((gpio->Pin)>GPIO_PIN_15))
	RetErrorState_InitPin=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;

	else if(((gpio->Speed)<LOW_SPEED_MODE)||((gpio->Speed)>VERY_HIGH_SPEED_MODE))
	RetErrorState_InitPin=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;

	else if(((gpio->Mode)<INPUT_FLOATING)||((gpio->Mode)>ANALOG))
	RetErrorState_InitPin=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	
	else{

	Local_u32Temp=((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_MODER;
	Local_u32Temp&=~(PIN_MODE_MASK<<(2*(gpio->Pin)));
	Local_u32Temp |= (((gpio->Mode)/PIN_MODE_CATEGORY_DIVIDOR)<<(2*(gpio->Pin)));
	((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_MODER=Local_u32Temp;
	
	if(((gpio->Mode)>=OUTPUT_PUSH_PULL)||((gpio->Mode)<=AF_OPEN_DRAIN_PULL_DOWN)){
	Local_u32Temp=((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_OTYPER;
	Local_u32Temp&=~(1<<(gpio->Pin));
	Local_u32Temp |= ((((gpio->Mode)%6)/3)<<(gpio->Pin));
	((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_OTYPER=Local_u32Temp;
	}
	Local_u32Temp=((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_OSPEEDR;
	Local_u32Temp&=~(PIN_MODE_MASK<<(2*(gpio->Pin)));
	Local_u32Temp |= ((gpio->Speed)<<(2*(gpio->Pin)));
	((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_OSPEEDR=Local_u32Temp;
	
	Local_u32Temp=((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_PUPDR;
	Local_u32Temp&=~(PIN_MODE_MASK<<(2*(gpio->Pin)));
	if((gpio->Mode)!=INPUT_FLOATING)
		Local_u32Temp |= (((gpio->Mode)%3)<<(2*(gpio->Pin)));
	((volatile GPIO_Registers_t*)(gpio->Port))->GPIO_PUPDR=Local_u32Temp;
	}
    return	RetErrorState_InitPin;
}
/**********************************************************************************************/
GPIO_enumRetErrorState_t GPIO_SetPinValue(Pin_Configuration_t*gpio,u8 Pin_value ){
	u32 Local_u32Temp;
    GPIO_enumRetErrorState_t RetErrorState_SetPinValue=RetErrorState_GPIO_OK;
	if(((gpio->Port)<GPIO_PORT_A)||((gpio->Port)>GPIO_PORT_H))
	RetErrorState_SetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	else if(((gpio->Pin)<GPIO_PIN_0)||((gpio->Pin)>GPIO_PIN_15))
	RetErrorState_SetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	else if((Pin_value>PIN_SET)||(Pin_value<PIN_RESET))
	RetErrorState_SetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	
	else{
	Local_u32Temp=((volatile GPIO_Registers_t *)(gpio->Port))->GPIO_BSRR;
	Local_u32Temp&=~(1<<gpio->Pin);
	Local_u32Temp |= ((SET_PIN_VALUE_MASK)<<((gpio->Pin)+(16* (Pin_value^0x1))));
	((volatile GPIO_Registers_t *)(gpio->Port))->GPIO_BSRR=Local_u32Temp;
	}
    return	RetErrorState_SetPinValue;}

/**********************************************************************************************/
GPIO_enumRetErrorState_t GPIO_GetPinValue(Pin_Configuration_t*gpio,u32 *Pin_value ){
	u32 Local_u32Temp;
    GPIO_enumRetErrorState_t RetErrorState_GetPinValue=RetErrorState_GPIO_OK;

	if(((gpio->Port)<GPIO_PORT_A)||((gpio->Port)>GPIO_PORT_H))
	RetErrorState_GetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;

	else if(((gpio->Pin)<GPIO_PIN_0)||((gpio->Pin) > GPIO_PIN_15))
	RetErrorState_GetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;

	
	else{
	Local_u32Temp=((volatile GPIO_Registers_t *)(gpio->Port))->GPIO_IDR;
	*Pin_value= (Local_u32Temp&(0x00000001<<(gpio->Pin)))>>gpio->Pin;
	}
	
    return	RetErrorState_GetPinValue;
}
 
GPIO_enumRetErrorState_t GPIO_ConfigureAltrFunc(Pin_Configuration_t*gpio,GPIO_ALTR_t type){
	u32 Local_u32Temp;
    GPIO_enumRetErrorState_t RetErrorState_ConfigureAltrFunc=RetErrorState_GPIO_OK;
	
	if(((gpio->Port)<GPIO_PORT_A)||((gpio->Port)>GPIO_PORT_H))
	RetErrorState_ConfigureAltrFunc=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;

	else if(((gpio->Pin)<GPIO_PIN_0)||((gpio->Pin)>GPIO_PIN_15))
	RetErrorState_ConfigureAltrFunc=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	
	else{
		if(((gpio->Pin)<GPIO_PIN_8)){
		Local_u32Temp=((GPIO_Registers_t*)(gpio->Port))->GPIO_AFRL;
		Local_u32Temp&=~(0x0000000F<<((gpio->Pin)%8));
		Local_u32Temp|=((u32)type<<((gpio->Pin)%8));
		((GPIO_Registers_t*)(gpio->Port))->GPIO_AFRL=Local_u32Temp;
		}
		else{
		Local_u32Temp=((GPIO_Registers_t*)(gpio->Port))->GPIOx_AFRH;
		Local_u32Temp&=~(0x0000000F<<((gpio->Pin)%8));
		Local_u32Temp|=((u32)type<<((gpio->Pin)%8));
		((GPIO_Registers_t*)(gpio->Port))->GPIOx_AFRH=Local_u32Temp;	
		}
	}
	
    return	RetErrorState_ConfigureAltrFunc;
}
/**
GPIO_enumRetErrorState_t GPIO_TogglePinValue(Pin_Configuration_t*gpio,u8 Pin_value ){
	u32 Local_u32Temp;
    GPIO_enumRetErrorState_t RetErrorState_SetPinValue=RetErrorState_GPIO_OK;
	if(((gpio->Port)<GPIO_PORT_A)||((gpio->Port)>GPIO_PORT_H))
	RetErrorState_SetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	else if(((gpio->Pin)<GPIO_PIN_0)||((gpio->Pin)>GPIO_PIN_15))
	RetErrorState_SetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	else if((Pin_value<PIN_SET)||(Pin_value>PIN_RESET))
	RetErrorState_SetPinValue=RetErrorState_GPIO_NOK_WRONGCONFIGURATION;
	
	else{
	Local_u32Temp=((volatile GPIO_Registers_t *)(gpio->Port))->GPIO_BSRR;
	Local_u32Temp&=~(1<<gpio->Pin);
	Local_u32Temp |= ((SET_PIN_VALUE_MASK)<<((gpio->Pin)+(16* Pin_value)));
	((volatile GPIO_Registers_t *)(gpio->Port))->GPIO_BSRR=Local_u32Temp;
	}
    return	RetErrorState_SetPinValue;}
*/

