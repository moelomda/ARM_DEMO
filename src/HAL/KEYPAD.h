#ifndef KEYPAD_H
#define KEYPAD_H

#include "Std_Types.h"
#include "KEYPAD_cfg.h"
#include "GPIO.h"
typedef enum 
{
    KEYPAD_enumOK,
    KEYPAD_enumNOK,
    KEPAD_enumDIO_Error
}KEYPAD_enuErrorStatus_t;

void KEYPAD_voidInit(void);

KEYPAD_enuErrorStatus_t KEYPAD_enumGetPressedKey (u8 *Copy_pu8KeyValue);

void KEYPAD_Update(void);

void hhhh(void);

void KEYPAD_Get_State(u8 ROW_number, u8 COL_number, u32 *state);

#endif /* KEYPAD_H */
