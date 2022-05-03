/*************************************************************************
 *
 *    File name   : timer.h
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains defines,includes and function prototypes for timer.c
 *    Reference	  : Code help taken from Dean Systick timer Section.
 *
 **************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_


/******************************************************************************
 * File includes here
 *****************************************************************************/

#include <MKL25Z4.h>
#include <stdio.h>
#include <stdlib.h>


/******************************************************************************
 * Declaring defines
 *****************************************************************************/

#define PWM_PERIOD (255)

//for 1 sec = 48000000/16 i.e. 3000000. Using cross multiplication I got 30000 for 10 msec.
#define systick_value (30000)


typedef uint32_t ticktime_t;

/*************************************************************************************************************
 *
 * Name :		  	void init_systick();
 *
 * Description :	initialize systick timer.
 *
 * Inputs: NONE
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void init_systick();

/*************************************************************************************************************
 *
 * Name :		  	void SysTick_Handler();
 *
 * Description :	Systick module interrupt handler
 *
 * Inputs: NONE
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void SysTick_Handler();


/*************************************************************************************************************
 *
 * Name :		  	ticktime_t now();
 *
 * Description :	returns time since startup
 *
 * Inputs: NONE
 *
 * Return: timer_value
 *
 *************************************************************************************************************/
ticktime_t now();

/*************************************************************************************************************
 *
 * Name :		  	void reset_timer();
 *
 * Description :	resets timer to Zero
 *
 * Inputs: NONE
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void reset_timer();

/*************************************************************************************************************
 *
 * Name :		  	ticktime_t get_timer();
 *
 * Description :	 returns time since the last call to reset_timer()
 *
 * Inputs: NONE
 *
 * Return: timer_value-timer_reset_value
 *
 *************************************************************************************************************/
ticktime_t get_timer();


#endif /* TIMER_H_ */
