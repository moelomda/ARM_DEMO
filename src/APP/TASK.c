#include "TASK.h"

extern void KPD_Task(void);
extern void Stop_Watch_runnable(void);
extern void LCD_TASK(void);
extern void DISPLAY_Task(void);
extern void KEYPAD_Update(void);
extern void Buzzer_Runnable(void);
//extern void test(void);

Task_t Task1 = {.name = "KEYPAD_PRESSED", .periodicityMs = 135, .priority = KEYPAD_PRESSED, .delayMs = 100, .cb = KPD_Task};
Task_t Task2 = {.name = "STOP_WATCH", .periodicityMs = 1000, .priority = STOP_WATCH_, .delayMs = 80, .cb = Stop_Watch_runnable};
Task_t Task3 = {.name = "LCD", .periodicityMs = 2, .priority = LCD, .delayMs = 0, .cb = LCD_TASK};
Task_t Task4 = {.name = "KEYPAD_UPDATE_", .periodicityMs = 5, .priority = KEYPAD_UPDATE_Runnable, .delayMs = 60, .cb = KEYPAD_Update};
Task_t Task5 = {.name = "Runnable", .periodicityMs = 1000, .priority = Runnable, .delayMs = 80, .cb = Buzzer_Runnable};


TaskInfo_t Tasks [_NUM_TASKS] =
{
   [KEYPAD_PRESSED] = {.Task = &Task1},
    [STOP_WATCH_] = {.Task = &Task2},
    [LCD] = {.Task = &Task3},
    [KEYPAD_UPDATE_Runnable] = {.Task = &Task4},
   [Runnable] = {.Task = &Task5}
};
