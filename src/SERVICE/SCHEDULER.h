#ifndef SCHEDULER_H
#define SCHEDULAR_H

#include "Std_Types.h"
#include "SYSTICK.h"
#include "TASK.h"

#define SCHED_TICK_MS   1




typedef enum
{
    SCHED_OK,
    SCHED_NOK

}SCHED_ErrorStatus_t;

void SCHED_Init(void);

void SCHED_Start(void);

#endif /*SCHEDULER_H*/
