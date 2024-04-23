#include "SCHEDULER.h"

extern TaskInfo_t Tasks [_NUM_TASKS];

static volatile u8 Global_Sched_Ticks_Pending;

static void SCHED_Pending(void)
{
    Global_Sched_Ticks_Pending++;
}


static void SCHED(void)
{
    u8 Loc_Index;

    for(Loc_Index =0; Loc_Index < _NUM_TASKS; Loc_Index++)
    {
        if((Tasks[Loc_Index].Task->cb) && (Tasks[Loc_Index].remainingTimeMs == 0))
        {
            Tasks[Loc_Index].Task->cb();
            Tasks[Loc_Index].remainingTimeMs = Tasks[Loc_Index].Task->periodicityMs;
        }

        Tasks[Loc_Index].remainingTimeMs -= SCHED_TICK_MS;
    }
}

void SCHED_Init(void)
{
    u8 Loc_index;

    for(Loc_index = 0; Loc_index < _NUM_TASKS; Loc_index++)
    {
        Tasks[Loc_index].remainingTimeMs = Tasks[Loc_index].Task->delayMs;
    }

    SYSTICK_Set_Time_Ms(SCHED_TICK_MS);
    SYSTICK_SetCallBack(SCHED_Pending);
}

void SCHED_Start(void)
{
    SYSTICK_Set_Configuration(SYSTICK_AHB_EXCEPTION,SYSTICK_PERIODIC_MODE);
    SYSTICK_Start();

    while(1)
    {
        if(Global_Sched_Ticks_Pending != 0)
        {
            Global_Sched_Ticks_Pending--;
            SCHED();
        }
    }
}
