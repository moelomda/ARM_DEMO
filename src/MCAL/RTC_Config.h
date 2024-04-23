/***************************************************************************************************/
/***************************************************************************************************/
/************************* creator:Omar Ahmed ******************************************************/
/*************************  layer:mcal *************************************************************/
/*************************    swc:DIO   ************************************************************/

#ifndef RTC_CONFIG_H_
#define RTC_CONFIG_H_
#include "std_types.h"
#define PREDEV_A    127
#define PREDEV_S    255





/**********************************************************************/
/*options for TSEDGE*/
#define TSEDGE 
#define TIMESTAMP_RISING_EDGE                 0
#define TIMESTAMP_FALLING_EDGE                 1
/**********************************************PROTOTYPES**********************************************/
#define BYPSHAD    READING_DIRECT_FROM_CALENDAR_COUNTER
#define READING_FROM_SHADOW_REG                          0
#define READING_DIRECT_FROM_CALENDAR_COUNTER               1



#endif 
