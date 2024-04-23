#include "GPIO.h"
#include "LCD.h"


#define LCD_POWER_ON         0
#define LCD_FUNCTION_SET     1
#define LCD_DISPLAY_ON_OFF   2
#define LCD_DISPLAY_CLEAR    3
#define LCD_ENTERY_MODE_SET  4

#define INIT           0
#define OPERATIONAL    2
#define TURN_OFF_LCD   3

#define LCD_IDLE    0
#define LCD_BUSY    1

#define LCD_GOTO_XY                 1
#define LCD_WRITE_SPECIAL_PATTERN   2
#define LCD_DISPLAY_SPECIAL_PATTERN 3
#define LCD_WRITE_STRING            4
#define LCD_CURSOR_ON               5
#define LCD_CURSOR_OFF              6
#define LCD_CLEAR                   7


static u8 Global_LCD_State;

typedef struct
{
    u8 col;
    u8 row;
}LCD_Location_t;

typedef struct 
{
    u8* data;
    u8 lengh;

}LCD_Data_t;

u8 Global_Buffer_Start;  
u8 Global_Buffer_End;

typedef struct
{
    LCD_Location_t  LCD_Buffer_GO_TO_LOCATION;
    LCD_Data_t      LCD_Buffer_DATA;
    char user_Request;

}LCD_Buffer;    

LCD_Buffer Buffer[20];



extern  LCD_cfg_t LCD_initialization [11];


static u8 Buffer_Is_Empty(void)  
{
    char x; 
    if(Global_Buffer_Start == Global_Buffer_End)
    {
        x = 1;
    }
    else
    {
        x = 0;
    }
    return x;
}

static u8 Buffer_Is_Full (void)  
{
    char x;
    if(Global_Buffer_End == 20)
    {
        x = 1;
    }
    else
    {
        x = 0;
    }
    return x;
}

static u8 LCD_Get_Enable(void)
{
	GPIO_GET_PINVALUE(LCD_initialization[E].port,LCD_initialization[E].pin,&LCD_initialization[E].connection);
     
     return LCD_initialization[E].connection;
}

/*************************************************************************************************************************/
void LCD_init_HW(void)
{
	GPIO_t LCD_configuration;
    u8 Loc_index;

    LCD_configuration.GPIO_MODE = GPIO_OUTPUT_PP;
    LCD_configuration.GPIO_SPEED = GPIO_MEDIUM_SPEED;

    
    for (Loc_index = 0; Loc_index < 11; Loc_index++)
    {
        LCD_configuration.GPIO_PORT = LCD_initialization[Loc_index].port;
        LCD_configuration.GPIO_PIN = LCD_initialization[Loc_index].pin;
        GPIO_INITPIN(&LCD_configuration);
        GPIO_SET_PINVALUE(LCD_initialization[Loc_index].port, LCD_initialization[Loc_index].pin, GPIO_RESET);
    }

}

/*************************************************************************************************************************/
void Write_Command(u8 command)
{
	GPIO_SET_PINVALUE(LCD_initialization[RS].port,LCD_initialization[RS].pin,GPIO_RESET);
	GPIO_SET_PINVALUE(LCD_initialization[RW].port,LCD_initialization[RW].pin,GPIO_RESET);

	static u8 counter;
	
    if (LCD_Get_Enable() == 0)
    {
        for (counter = 0; counter < 8; counter++)
	    {
		    LCD_initialization[counter].connection = ((command >> counter) & 0x01);

/*            if (LCD_initialization[counter].connection == 0)
            {
                LCD_initialization[counter].connection = GPIO_RESET;
            } 
*/
		    GPIO_SET_PINVALUE(LCD_initialization[counter].port,LCD_initialization[counter].pin,LCD_initialization[counter].connection);
	    }
	
        GPIO_SET_PINVALUE(LCD_initialization[E].port,LCD_initialization[E].pin,GPIO_SET);
    }
    else
    {
    	GPIO_SET_PINVALUE(LCD_initialization[E].port,LCD_initialization[E].pin,GPIO_RESET);
    }
}

/*************************************************************************************************************************/

void Write_Data(u8 data)
{
	GPIO_SET_PINVALUE(LCD_initialization[RS].port,LCD_initialization[RS].pin,GPIO_SET);
	GPIO_SET_PINVALUE(LCD_initialization[RW].port,LCD_initialization[RW].pin,GPIO_RESET);

	static u8 counter;
	
    if (LCD_Get_Enable() == 0)
    {
        for (counter = 0; counter < 8; counter++)
	    {
		    LCD_initialization[counter].connection = ((data >> counter) & 0x01);
/*
            if (LCD_initialization[counter].connection == 0)
            {
                LCD_initialization[counter].connection = GPIO_RESET;
            } 
*/
		    GPIO_SET_PINVALUE(LCD_initialization[counter].port,LCD_initialization[counter].pin,LCD_initialization[counter].connection);
	    }
	
        GPIO_SET_PINVALUE(LCD_initialization[E].port,LCD_initialization[E].pin,GPIO_SET);
    }
    else
    {
    	GPIO_SET_PINVALUE(LCD_initialization[E].port,LCD_initialization[E].pin,GPIO_RESET);
    }
	
}

/*************************************************************************************************************************/

void lcd_init(void)
{
    static u8 count = 0;
    static u8 LCD_Init_State = LCD_POWER_ON;
    Global_LCD_State = INIT;

    switch (LCD_Init_State)
    {
        case LCD_POWER_ON:
            
            count++;
            if (count == 20)
            {
                LCD_Init_State++;
                count = 0;
            }
            break;

        case LCD_FUNCTION_SET:

            Write_Command(FUNCTION_SET);
            if (LCD_Get_Enable() == 0)
            {
                LCD_Init_State++;
            }
            break;

        case LCD_DISPLAY_ON_OFF:

            Write_Command(DISPLAY_ON_OFF);
            if (LCD_Get_Enable() == 0)
            {
                LCD_Init_State++;
            }
            break; 

        case LCD_DISPLAY_CLEAR:

            Write_Command(DISPLAY_CLEAR);
            if (LCD_Get_Enable() == 0)
            {
                LCD_Init_State++;
            }
            break; 

        case LCD_ENTERY_MODE_SET:

            Write_Command(ENTRY_MODE_SET);
            if (LCD_Get_Enable() == 0)
            {
                LCD_Init_State++;
                Global_LCD_State = OPERATIONAL;
            }
            break;              
    
        default:

            break;
    }

}

/*************************************************************************************************************************/

static void LCD_Go_To_Location(void)
{
	u8 Loc_u8Location=0;

	if (Buffer[Global_Buffer_Start].LCD_Buffer_GO_TO_LOCATION.row == FIRST_LINE)
	{
		Loc_u8Location = Buffer[Global_Buffer_Start].LCD_Buffer_GO_TO_LOCATION.col;
	}
	else if (Buffer[Global_Buffer_Start].LCD_Buffer_GO_TO_LOCATION.row == SECOND_LINE)
	{
		Loc_u8Location = Buffer[Global_Buffer_Start].LCD_Buffer_GO_TO_LOCATION.col + 0x40;
	}
	Write_Command(Loc_u8Location + 128);
}

/*************************************************************************************************************************/
/*
void LCD_enuWriteSpecialPattern(u8* Copy_pu8Pattern, u8 Copy_u8_CGRAM_Block_Number)
{
	u8 Loc_u8CGRAMLocation = Copy_u8_CGRAM_Block_Number * 8;
	u8 counter;
	
	Write_Command(Loc_u8CGRAMLocation + 64);
	
	for (counter = 0; counter <8; counter ++)
	{
		Write_Data(Copy_pu8Pattern[counter]);
	}
	
}
*/
/*************************************************************************************************************************/
/*
void LCD_enuDisplaySpecialPattern(u8 Copy_u8_CGRAM_Block_Number, u8 Copy_u8X, u8 Copy_u8Y)
{
	LCD_Go_To_Location(Copy_u8X,Copy_u8Y);
	
	Write_Data(Copy_u8_CGRAM_Block_Number);
}
*/
/*************************************************************************************************************************/
/*
void LCD_enuWriteString(u8* Copy_pchPattern, u8 Copy_u8Length, u8 Copy_u8X, u8 Copy_u8Y)
{
	u8 counter;
	
	LCD_Go_To_Location(Copy_u8X, Copy_u8Y);
	
	for (counter = 0; counter < Copy_u8Length; counter++)
	{
		Write_Data(Copy_pchPattern[counter]);
	}
}
*/
/*************************************************************************************************************************/

/*
void LCD_DisplayCharacter(void)
{
    static u8 counter = 0;

    if(counter <= 1)
    {
        LCD_Go_To_Location();
        counter++;
    }
    else if (counter > 1 && counter <= 3)
    {
        Write_Data(Global_LCD_Data.data[0]);
    }
}
*/

/*************************************************************************************************************************/


/*************************************************************************************************************************/


/*************************************************************************************************************************/

void LCD_Go_To_Location_Async(u8 row, u8 col)
{
    if ( ! Buffer_Is_Full())
    {
        Buffer[Global_Buffer_End].user_Request = LCD_GOTO_XY;
        Buffer[Global_Buffer_End].LCD_Buffer_GO_TO_LOCATION.col = col;
        Buffer[Global_Buffer_End].LCD_Buffer_GO_TO_LOCATION.row = row;
        Global_Buffer_End++;
    }
}

/*************************************************************************************************************************/
/*
void LCD_DisplayCharacter_Async(u8* character, u8 row, u8 col)
{
//    if (LCD_Operational_State != LCD_BUSY)
//    {
        LCD_User_Request = LCD_DISPLAY_CHARACTER;
        
        Global_LCD_Location.col = col;
        Global_LCD_Location.row = row;

        Global_LCD_Data.data = character;
        Global_LCD_Data.lengh = 0;
//    }
}
*/

void LCD_Write_String_Async(u8* Copy_pchPattern, u8 Copy_u8Length, u8 row, u8 col)
{ 

if ( ! Buffer_Is_Full())
    {
        Buffer[Global_Buffer_End].user_Request = LCD_WRITE_STRING;

        Buffer[Global_Buffer_End].LCD_Buffer_GO_TO_LOCATION.col = col;
        Buffer[Global_Buffer_End].LCD_Buffer_GO_TO_LOCATION.row = row;
        
        Buffer[Global_Buffer_End].LCD_Buffer_DATA.data = Copy_pchPattern;
        Buffer[Global_Buffer_End].LCD_Buffer_DATA.lengh = Copy_u8Length;

        Global_Buffer_End++;
    }
}

void LCD_Clear_Screen_Async(void)
{
   if ( ! Buffer_Is_Full())
   {
        Buffer[Global_Buffer_End].user_Request = LCD_CLEAR;
        Global_Buffer_End++;
   }
}

static void LCD_Clear_Screen(void)
{
    Write_Command(DISPLAY_CLEAR);
}

void LCD_Cursor_On_Async(void)
{
   if ( ! Buffer_Is_Full())
   {
        Buffer[Global_Buffer_End].user_Request = LCD_CURSOR_ON;
        Global_Buffer_End++;
   }
}
static void LCD_Cursor_On(void)
{
    Write_Command(CURSOR_ON);
}
/**************************************************************************************************************/

void LCD_Cursor_Off_Async(void)
{
   if ( ! Buffer_Is_Full())
   {
        Buffer[Global_Buffer_End].user_Request = LCD_CURSOR_OFF;
        Global_Buffer_End++;
   }
}
static void LCD_Cursor_Off(void)
{
    Write_Command(DISPLAY_ON_OFF);
}


static void LCD_WriteString(void)
{

    static u8 counter = 0;
    static u8 counter1 = 0;
    static u8 counter2 = 0;

    if (counter <= 1)
    {
        LCD_Go_To_Location();
        counter++;
    }
    else
    {
        if (Buffer[Global_Buffer_Start].LCD_Buffer_DATA.data[counter1] != '\0')
        //if(counter1 < (Buffer[Global_Buffer_Start].LCD_Buffer_DATA.lengh))
        {
            Write_Data(Buffer[Global_Buffer_Start].LCD_Buffer_DATA.data[counter1]);

            counter2++;
            if (counter2 % 2 == 0)
            {
                counter1++;
            }      
        }
        else
        {
            counter = 0;
            counter1 = 0;
            counter2 = 0;
        }
    }
    
}
/*************************************************************************************************************************/
void LCD_Operational(void)
{
    static u8 count = 0;

            switch (Buffer[Global_Buffer_Start].user_Request)
            {
                case LCD_GOTO_XY:

                    LCD_Go_To_Location();

                    if (LCD_Get_Enable() == 0)
                    {
                        Global_Buffer_Start++;

                        if (Buffer_Is_Empty())
                        {
                            Global_Buffer_Start = Global_Buffer_End = 0;
                            Buffer[Global_Buffer_Start].user_Request = 8;
                        }
                /*      else
                        {
                            Global_Buffer_Start++;
                        }
                */  }

                    break;
/*
                case LCD_WRITE_SPECIAL_PATTERN:
                    break;

                case LCD_DISPLAY_SPECIAL_PATTERN:
                    break;            
*/
                case LCD_WRITE_STRING:
                    
                    LCD_WriteString();

                    count++;
                    if ( (count >=  ( (Buffer[Global_Buffer_Start].LCD_Buffer_DATA.lengh * 2) + 1) )  && (LCD_Get_Enable() == 0) )
                    {   
                        Global_Buffer_Start++;

                        if (Buffer_Is_Empty())
                        {
                            Global_Buffer_Start = Global_Buffer_End = 0;
                            Buffer[Global_Buffer_Start].user_Request = 8;
                        }
            /*          else
                        {
                            Global_Buffer_Start++;
                        }
            */
                        count = 0;
                    }
                    break;

                case LCD_CURSOR_ON:

                    LCD_Cursor_On();
                    
                    if (LCD_Get_Enable() == 0)
                    {
                        Global_Buffer_Start++;

                        if (Buffer_Is_Empty())
                        {
                            Global_Buffer_Start = Global_Buffer_End = 0;
                            Buffer[Global_Buffer_Start].user_Request = 8;
                        }
                    }
                    break;

                case LCD_CURSOR_OFF:

                    LCD_Cursor_Off();
                    
                    if (LCD_Get_Enable() == 0)
                    {
                        Global_Buffer_Start++;

                        if (Buffer_Is_Empty())
                        {
                            Global_Buffer_Start = Global_Buffer_End = 0;
                            Buffer[Global_Buffer_Start].user_Request = 8;
                        }
                    }
                    break;

                case LCD_CLEAR:

                    LCD_Clear_Screen();
                    
                    if (LCD_Get_Enable() == 0)
                    {
                        Global_Buffer_Start++;

                        if (Buffer_Is_Empty())
                        {
                            Global_Buffer_Start = Global_Buffer_End = 0;
                            Buffer[Global_Buffer_Start].user_Request = 8;
                        }
                /*      else
                        {
                            Global_Buffer_Start++;
                        }
                */  }

                    break;    

                default:
                    break;
            }
}




void LCD_TASK(void)
{
    switch (Global_LCD_State)
    {
    case INIT:
        lcd_init();
        break;
    
    case OPERATIONAL:
        LCD_Operational();
        break;   
    
    case TURN_OFF_LCD:

        break;
    
    default:

        break;    
    }
}
