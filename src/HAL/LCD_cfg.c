#include "LCD.h"
#include "GPIO.h"

 LCD_cfg_t LCD_initialization [11] = 
{
    [LCD_D0] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN0,
        .connection = GPIO_PU
    }
    ,
    [LCD_D1] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN1,
        .connection = GPIO_PU
    }
    ,
    [LCD_D2] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN2,
        .connection = GPIO_PU
    }
    ,
    [LCD_D3] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN3,
        .connection = GPIO_PU
    }
    ,
    [LCD_D4] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN4,
        .connection = GPIO_PU
    }
    ,
    [LCD_D5] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN5,
        .connection = GPIO_PU
    }
    ,
    [LCD_D6] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN6,
        .connection = GPIO_PU
    }
    ,
    [LCD_D7] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN7,
        .connection = GPIO_PU
    }
    ,
    [RS] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN8,
        .connection = GPIO_PU
    }
    ,
    [RW] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN9,
        .connection = GPIO_PU
    }
    ,
    [E] = 
    {
        .port = GPIOA,
        .pin = GPIO_PIN10,
        .connection = GPIO_PU
    }

};
