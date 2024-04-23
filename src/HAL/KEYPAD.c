
#include "KEYPAD.h"

extern KPD_STR_CONFG_t KPD_configuration;

u8 G_States[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS];

void KEYPAD_voidInit(void)
{
    u8 Loc_Index;
    GPIO_t KEYPAD_CFG;

    for(Loc_Index = 0 ; Loc_Index < KPD_NUMBER_OF_COLUMNS; Loc_Index++)
    {
        KEYPAD_CFG.GPIO_MODE = GPIO_OUTPUT_PP;
        KEYPAD_CFG.GPIO_SPEED = GPIO_MEDIUM_SPEED;
        KEYPAD_CFG.GPIO_PORT = KPD_configuration.Col_Port_Number[Loc_Index];
        KEYPAD_CFG.GPIO_PIN = KPD_configuration.Col_Pin_Number[Loc_Index];

        GPIO_INITPIN(&KEYPAD_CFG);
        GPIO_SET_PINVALUE(KPD_configuration.Col_Port_Number[Loc_Index], KPD_configuration.Col_Pin_Number[Loc_Index], GPIO_SET);

    }

    for(Loc_Index = 0 ; Loc_Index < KPD_NUMBER_OF_ROWS; Loc_Index++)
    {
        KEYPAD_CFG.GPIO_MODE = GPIO_INPUT_PU ;
        KEYPAD_CFG.GPIO_SPEED = GPIO_MEDIUM_SPEED;
        KEYPAD_CFG.GPIO_PORT = KPD_configuration.Row_Port_Number[Loc_Index];
        KEYPAD_CFG.GPIO_PIN = KPD_configuration.Row_Pin_Number[Loc_Index];
        GPIO_INITPIN(&KEYPAD_CFG);
    }
}




void KEYPAD_Get_State(u8 ROW_number, u8 COL_number, u32 *state)
{
    *state = G_States[ROW_number][COL_number];
}



KEYPAD_enuErrorStatus_t KEYPAD_enumGetPressedKey(u8 * Copy_pu8KeyValue)
{
    KEYPAD_enuErrorStatus_t Loc_enum_ErrorStatus = KEYPAD_enumOK;
    u8 Loc_Index1;
    u8 Loc_Index2;
    u8 Loc_u8Keypad_Arr[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS] = KEPAD_ARR;
    u32 Loc_PinValue = 1;

    if (Copy_pu8KeyValue)
    {
        for (Loc_Index1 = 0; Loc_Index1 < KPD_NUMBER_OF_COLUMNS; Loc_Index1++)
        {
//            GPIO_Set_Pin_Value(KPD_configuration.Col_Port_Number[Loc_Index1], KPD_configuration.Col_Pin_Number[Loc_Index1], GPIO_RESET);

            for (Loc_Index2 = 0; Loc_Index2 < KPD_NUMBER_OF_ROWS; Loc_Index2++)
            {
                KEYPAD_Get_State(Loc_Index1, Loc_Index2, &Loc_PinValue);
            //    GPIO_Get_Pin_Value(KPD_configuration.Row_Port_Number[Loc_Index2], KPD_configuration.Row_Pin_Number[Loc_Index2], &Loc_PinValue);
  
                if (Loc_PinValue == 0)
                {
                    *Copy_pu8KeyValue = Loc_u8Keypad_Arr[Loc_Index2][Loc_Index1];
                }
            }

//            GPIO_Set_Pin_Value(KPD_configuration.Col_Port_Number[Loc_Index1], KPD_configuration.Col_Pin_Number[Loc_Index1], GPIO_SET);
        }
    }
    else
    {
        Loc_enum_ErrorStatus = KEYPAD_enumNOK;
    }
return Loc_enum_ErrorStatus;
}




void KEYPAD_Update(void)
{
    static u8 prevHWState[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS];     
    static u8 stateCount[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS];      
    u32 currHWState;                         
    u8 currSwitch;                          
    u8 Loc_Index;

    for(Loc_Index = 0; Loc_Index < KPD_NUMBER_OF_ROWS; Loc_Index++)
    {
    	GPIO_SET_PINVALUE(KPD_configuration.Col_Port_Number[Loc_Index], KPD_configuration.Col_Pin_Number[Loc_Index], GPIO_RESET);

        for (currSwitch = 0; currSwitch < KPD_NUMBER_OF_COLUMNS; currSwitch++)
        {
        	GPIO_GET_PINVALUE(KPD_configuration.Row_Port_Number[currSwitch], KPD_configuration.Row_Pin_Number[currSwitch], &currHWState);

            if(currHWState == prevHWState[Loc_Index][currSwitch])
            {
                stateCount[Loc_Index][currSwitch]++;
            }
            else
            {
                stateCount[Loc_Index][currSwitch] = 0;
            }

            if(stateCount[Loc_Index][currSwitch] == 4)
            {
                G_States[Loc_Index][currSwitch] = currHWState;
                stateCount[Loc_Index][currSwitch] = 0;
            }

            prevHWState[Loc_Index][currSwitch] = currHWState;
        }

        GPIO_SET_PINVALUE(KPD_configuration.Col_Port_Number[Loc_Index], KPD_configuration.Col_Pin_Number[Loc_Index], GPIO_SET);
    }

}

/*
void hhhh(void)
{
    static u8 prevHWState[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS];     
    static u8 stateCount[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLUMNS];      
    u32 currHWState;                         
    u8 currSwitch;                          
    u8 Loc_Index;

    for(Loc_Index = 0; Loc_Index < KPD_NUMBER_OF_ROWS; Loc_Index++)
    {
        GPIO_Set_Pin_Value(KPD_configuration.Col_Port_Number[Loc_Index], KPD_configuration.Col_Pin_Number[Loc_Index], GPIO_RESET);

        for (currSwitch = 0; currSwitch < KPD_NUMBER_OF_COLUMNS; currSwitch++)
        {
            GPIO_Get_Pin_Value(KPD_configuration.Row_Port_Number[currSwitch], KPD_configuration.Row_Pin_Number[currSwitch], &currHWState);

            if(currHWState == prevHWState[Loc_Index][currSwitch])
            {
                stateCount[Loc_Index][currSwitch]++;
            }
            else
            {
                stateCount[Loc_Index][currSwitch] = 0;
            }

            if(stateCount[Loc_Index][currSwitch] == 4)
            {
                G_States[Loc_Index][currSwitch] = currHWState;
                stateCount[Loc_Index][currSwitch] = 0;
            }

            prevHWState[Loc_Index][currSwitch] = currHWState;
        }

        GPIO_Set_Pin_Value(KPD_configuration.Col_Port_Number[Loc_Index], KPD_configuration.Col_Pin_Number[Loc_Index], GPIO_SET);
    }

}
*/
