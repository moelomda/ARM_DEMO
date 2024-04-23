#ifndef TASK_H
#define TASH_H

#include "Std_Types.h"

typedef enum
{
    KEYPAD_PRESSED,
    STOP_WATCH_,
    LCD,
  KEYPAD_UPDATE_Runnable,
	Runnable,
    _NUM_TASKS

}Task_ID_t;


typedef void (*TaskCb_t)(void);

typedef struct
{
    char * name;
    u32 periodicityMs;
    u32 priority;
    u32 delayMs;
    TaskCb_t cb;

}Task_t;


typedef struct
{
    const Task_t * const Task;
    u32 remainingTimeMs;

}TaskInfo_t;

#endif /*TASK_H*/
