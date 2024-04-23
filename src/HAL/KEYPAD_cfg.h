#ifndef KEYPAD_confg_H
#define KEYPAD_confg_H

/*number of rows*/
#define KPD_NUMBER_OF_ROWS              4
/*number of columns*/
#define KPD_NUMBER_OF_COLUMNS           4
#define IDLE_KEY                        15
typedef enum
{
Arrow_Up,
Arrow_Down,
Arrow_Right,
Arrow_Left,
Edit_Key,
Ok_Key,
Mode_Key,
Reset_Key,
Start_Stop_Key,
Set_Alarm
}KEYS_T;
#define KEPAD_ARR  {{Arrow_Up,Arrow_Down,Arrow_Right,Arrow_Left},{Edit_Key,Ok_Key,Mode_Key,Reset_Key},{Start_Stop_Key,Set_Alarm,IDLE_KEY,IDLE_KEY,IDLE_KEY},{IDLE_KEY,IDLE_KEY,IDLE_KEY,IDLE_KEY}}
//#define KEPAD_ARR  {{'A','B','C','0'},{'A','B','C','0'},{'A','B','C','0'},{'A','B','C','0'}}

typedef struct
{
    u8 Row_Pin_Number[KPD_NUMBER_OF_ROWS];
    void * Row_Port_Number[KPD_NUMBER_OF_ROWS];
    u8 Col_Pin_Number[KPD_NUMBER_OF_COLUMNS];
    void * Col_Port_Number[KPD_NUMBER_OF_COLUMNS];

}KPD_STR_CONFG_t;

#endif /* KEYPAD_confg_H */
