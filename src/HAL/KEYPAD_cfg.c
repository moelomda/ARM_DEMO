#include "KEYPAD.h"
#include "GPIO.h"
 KPD_STR_CONFG_t KPD_configuration = 
 {
    .Row_Pin_Number  = {GPIO_PIN5, GPIO_PIN11, GPIO_PIN12, GPIO_PIN8},

    .Row_Port_Number = {GPIOB, GPIOA, GPIOA, GPIOB},

    .Col_Pin_Number  = {GPIO_PIN9, GPIO_PIN10, GPIO_PIN12, GPIO_PIN13},
    
    .Col_Port_Number = {GPIOB, GPIOB, GPIOB, GPIOB}
 };
