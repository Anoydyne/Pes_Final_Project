/*************************************************************************
 *    File name   : pwm.h
 *    Description : functions for PWM initialization
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains defines and function prototypes for pwm.c
 *    Reference	  : Code help taken from Dean PWM Section.
 *
 **************************************************************************/

#ifndef PWM_H_
#define PWM_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "timer.h"
#include <MKL25Z4.h>
#include "rgb_led.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)		// on port B
#define BLUE_LED_POS (1)		// on port D


/*************************************************************************************************************
 *
 * Name :	void Init_Blue_LED_PWM(uint16_t period);
 *
 * Description :  initialize TPM0 module. Channel 1 (For Blue Led)
 *
 * Inputs: NONE
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void Init_Blue_LED_PWM(uint16_t period);

/*************************************************************************************************************
 *
 * Name :	void Init_Green_LED_PWM(uint16_t period);
 *
 * Description :  initialize TPM2 module. Channel 1 (For Green Led)
 *
 * Inputs: NONE
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void Init_Green_LED_PWM(uint16_t period);

/*************************************************************************************************************
 *
 * Name :	void Init_Red_LED_PWM(uint16_t period);
 *
 * Description :  initialize TPM2 module. Channel 0 (For Red Led)
 *
 * Inputs: NONE
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void Init_Red_LED_PWM(uint16_t period);

#endif /* PWM_H_ */
