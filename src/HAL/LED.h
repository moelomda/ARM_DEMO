/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/

#ifndef LED_H_
#define LED_H_
#include "std_types.h"
#include "LED_Config.h"
typedef struct{   
void* Port;        			  
u8 Pin;   
u8 Polarity;      
u8 state;  	  	  
}Led_Configuration_t;

typedef enum{
RetErrorState_LED_OK=0,
RetErrorState_LED_NOK_WRONGCONFIGURATION,
RetErrorState_LED_NOK_WRONGGPIOCONFIGURATION
}LED_enumRetErrorState_t;

/***********************************************************************************************/
/*OPTIONS FOR LED PIN NUMBERS*/
#define LED_GPIO_PIN_0           0
#define LED_GPIO_PIN_1           1
#define LED_GPIO_PIN_2           2
#define LED_GPIO_PIN_3           3
#define LED_GPIO_PIN_4           4
#define LED_GPIO_PIN_5           5
#define LED_GPIO_PIN_6           6
#define LED_GPIO_PIN_7           7
#define LED_GPIO_PIN_8           8
#define LED_GPIO_PIN_9           9
#define LED_GPIO_PIN_10          10
#define LED_GPIO_PIN_11          11
#define LED_GPIO_PIN_12          12
#define LED_GPIO_PIN_13          13
#define LED_GPIO_PIN_14          14
#define LED_GPIO_PIN_15          15
/*******************************************************/
/*OPTIONS FOR LED PORTS SELECTION*/
#define LED_GPIO_PORT_A       (void*) 0x40020000
#define LED_GPIO_PORT_B       (void*) 0x40020400
#define LED_GPIO_PORT_C       (void*) 0x40020800
#define LED_GPIO_PORT_D       (void*) 0x40020C00
#define LED_GPIO_PORT_E       (void*) 0x40021000
#define LED_GPIO_PORT_H       (void*) 0x40021C00

/*******************************************************/
/*OPTIONS FOR LED STATE*/
#define LED_ON          1
#define LED_OFF         0

/*******************************************************/
/*OPTIONS FOR LED POLARITY*/
#define LED_FORWARD          1
#define LED_REVERSE          0
/**********************************************PROTOTYPES**********************************************/

LED_enumRetErrorState_t LED_Init(void );

LED_enumRetErrorState_t LED_Toggle(Led_Alias_List_t Led_Alias);
LED_enumRetErrorState_t LED_Off(Led_Alias_List_t Led_Alias);
LED_enumRetErrorState_t LED_On(Led_Alias_List_t Led_Alias);
void toggleled1(void);
void toggleled2(void);

#endif 
