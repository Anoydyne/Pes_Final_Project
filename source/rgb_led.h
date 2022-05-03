/*************************************************************************
 *
 *    File name   : rgb_led.h
 *    Description : function declarations for RGB led
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains function prototype for rgb_led.c
 *
 **************************************************************************/

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "MKL25Z4.h"
#include"pwm.h"

#ifndef RGB_LED_H_
#define RGB_LED_H_


/*************************************************************************************************************
 *
 * Name :		  void rgb_led(unsigned int red, unsigned int green, unsigned int blue);
 *
 * Description :	Assigns input values to respective CnV for RGB led.
 *
 * Inputs: unsigned int red, unsigned int green, unsigned int blue
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void rgb_led(unsigned int red, unsigned int green, unsigned int blue);

/*************************************************************************************************************
 *
 * Name :		  void test_pwm(void);
 *
 * Description :	PWM test function to test all the values of different states
 *
 * Inputs: NONE
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void test_pwm(void);

/*************************************************************************************************************
 *
 * Name :		  void Delay(volatile int time);
 *
 * Description :	Delay function to generate loop as per the input time.
 *
 * Inputs: time- value to generate a delay
 *
 * Return: NONE
 *
 *************************************************************************************************************/
void Delay(volatile int time);

#endif /* RGB_LED_H_ */
