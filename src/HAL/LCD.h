#ifndef LCD_H
#define LCD_H

#include "Std_Types.h"
#include "LCD_cfg.h"

#define  GPIO_PU 0x00000001
#define	LCD_D0	0
#define	LCD_D1	1
#define	LCD_D2	2
#define	LCD_D3	3
#define	LCD_D4	4
#define	LCD_D5	5
#define	LCD_D6	6
#define	LCD_D7	7

#define RS		8
#define RW		9
#define E		10

#define FUNCTION_SET	0b00111000	/* -> 0x38 */
#define DISPLAY_ON_OFF	0b00001100	/* -> 0x0C */
#define DISPLAY_CLEAR	0b00000001	/* -> 0x01 */
#define ENTRY_MODE_SET	0b00000110	/* -> 0x06 */
#define CURSOR_ON       0x0E

#define FIRST_LINE	 0
#define SECOND_LINE	 1

#define LCD_SHIFTING_LEFT           0x18
#define LCD_SHIFTING_RIGHT          0x1C

typedef struct 
{
    void* port;
    u32 pin;
    u32 connection;

}LCD_cfg_t;

void LCD_init_HW(void);
void LCD_Write_String_Async(u8* Copy_pchPattern, u8 Copy_u8Length, u8 row, u8 col);
void LCD_Clear_Screen_Async(void);
void LCD_DisplayCharacter_Async(u8* character, u8 row, u8 col);
void LCD_Go_To_Location_Async(u8 row, u8 col);
void LCD_Cursor_On_Async(void);
void LCD_Cursor_Off_Async(void);


#endif /*LCD_H*/
