/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/

#ifndef GPIO_H_
#define GPIO_H_




typedef struct{
void* Port	;
u8 Pin;
u8 Speed;
u32 Mode;
}Pin_Configuration_t;

typedef enum{
RetErrorState_GPIO_OK=0,
RetErrorState_GPIO_NOK_WRONGCONFIGURATION,
RetErrorState_GPIO_NOK_WRONGNUMBER
}GPIO_enumRetErrorState_t;
/********************************************/
typedef enum{
ALTR_FUNC_CAT_0,
ALTR_FUNC_CAT_1,
ALTR_FUNC_CAT_2,
ALTR_FUNC_CAT_3,
ALTR_FUNC_CAT_4,
ALTR_FUNC_CAT_5,
ALTR_FUNC_CAT_6,
ALTR_FUNC_CAT_7,
ALTR_FUNC_CAT_8,
ALTR_FUNC_CAT_9,
ALTR_FUNC_CAT_10,
ALTR_FUNC_CAT_11,
ALTR_FUNC_CAT_12,
ALTR_FUNC_CAT_13,
ALTR_FUNC_CAT_14,
ALTR_FUNC_CAT_15
}GPIO_ALTR_t;
/**********************************************INTERFACES**********************************************/
/*OPTIONS FOR GPIO PIN NUMBERS*/
#define GPIO_PIN_0           0
#define GPIO_PIN_1           1
#define GPIO_PIN_2           2
#define GPIO_PIN_3           3
#define GPIO_PIN_4           4
#define GPIO_PIN_5           5
#define GPIO_PIN_6           6
#define GPIO_PIN_7           7
#define GPIO_PIN_8           8
#define GPIO_PIN_9           9
#define GPIO_PIN_10          10
#define GPIO_PIN_11          11
#define GPIO_PIN_12          12
#define GPIO_PIN_13          13
#define GPIO_PIN_14          14
#define GPIO_PIN_15          15
/*******************************************************/
/*OPTIONS FOR GPIO PORTS SELECTION*/
#define GPIO_PORT_A       (void*)0x40020000
#define GPIO_PORT_B       ((void*)0x40020400)
#define GPIO_PORT_C       ((void*)0x40020800)
#define GPIO_PORT_D       ((void*)0x40020C00)
#define GPIO_PORT_E       ((void*)0x40021000)
#define GPIO_PORT_H       ((void*)0x40021C00)
/*******************************************************/
/*OPTIONS FOR GPIO PINS SPEED*/
#define LOW_SPEED_MODE                0
#define MEDIUM_SPEED_MODE             1
#define HIGH_SPEED_MODE               2
#define VERY_HIGH_SPEED_MODE          3
/*******************************************************/
/*OPTIONS FOR GPIO PINS MODE*/

#define INPUT_FLOATING                            0
#define INPUT_PULL_UP                             1
#define INPUT_PULL_DOWN                           2


#define OUTPUT_PUSH_PULL                          0x00000006
#define OUTPUT_PUSH_PULL_UP                       7
#define OUTPUT_PUSH_PULL_DOWN                     8
#define OUTPUT_OPEN_DRAIN                         9
#define OUTPUT_OPEN_DRAIN_PULL_UP                 10
#define OUTPUT_OPEN_DRAIN_PULL_DOWN               11



#define AF_PUSH_PULL                              12
#define AF_PUSH_PULL_UP                           13
#define AF_PUSH_PULL_DOWN                         14
#define AF_OPEN_DRAIN                             15
#define AF_OPEN_DRAIN_PULL_UP                     16
#define AF_OPEN_DRAIN_PULL_DOWN                   17
											  
#define ANALOG          			           	  18
/*******************************************************/
/*OPTIONS FOR PIN VALUE*/
#define PIN_SET           1
#define PIN_RESET          0

/**********************************************PROTOTYPES**********************************************/
GPIO_enumRetErrorState_t GPIO_InitPin(Pin_Configuration_t*gpio );
GPIO_enumRetErrorState_t GPIO_SetPinValue(Pin_Configuration_t*gpio,u8 Pin_value );
GPIO_enumRetErrorState_t GPIO_GetPinValue(Pin_Configuration_t*gpio,u32 *Pin_value );
GPIO_enumRetErrorState_t GPIO_ConfigureAltrFunc(Pin_Configuration_t*gpio,GPIO_ALTR_t type);


#endif 
