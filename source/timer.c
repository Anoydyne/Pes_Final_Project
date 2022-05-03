/*************************************************************************
 *
 *    File name   : timer.c
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions for systic timer initialization and other functions.
 *    Reference	  : Code help taken from Dean Systick timer Section.
 *
 **************************************************************************/
/******************************************************************************
 * File includes here
 *****************************************************************************/
#include"timer.h"

/******************************************************************************
* Declaring Variables
******************************************************************************/

volatile ticktime_t timer_value = 0;
volatile ticktime_t timer_reset_value = 0;

void init_systick()							// initialize the timing system
{
    SysTick->LOAD = systick_value;			//Storing value in load register.(30000 for 10msec)
    NVIC_SetPriority(SysTick_IRQn,3);		//setting interrupt priority
    SysTick->VAL = 0;
    SysTick->CTRL=	SysTick_CTRL_TICKINT_Msk| SysTick_CTRL_ENABLE_Msk;	//enabling interrupt
}

void SysTick_Handler()						//Systick module interrupt handler
{
    timer_value++;
}

ticktime_t now()							// returns time since startup
{
    return(timer_value);
}
void reset_timer()							// resets timer to Zero
{
    timer_reset_value = now();
    init_systick();
}

ticktime_t get_timer()						//returns time since the last call to reset_timer()
{
    return(timer_value-timer_reset_value);
}
