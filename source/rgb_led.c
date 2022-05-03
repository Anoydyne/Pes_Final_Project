/*************************************************************************
 *
 *    File name   : rgb_led.c
 *    Description : function declarations for RGB led
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains function for controlling RGB led's
 *
 **************************************************************************/

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include"rgb_led.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define MAX_PWM				(255)	// Maximum PWM value for RGB Led
#define ONE_MS_CONS			(5347)	// Constant to generate 1ms delay


//Delay function to generate loop as per the input time.
void Delay(volatile int time)
{
    time = time*ONE_MS_CONS;				// Multiplying time with an approximated value to get desired delay.
    while(time--)							// Decrementing the counter to get the desired delay.
    {
        __asm volatile("NOP");
    }
}

//Assigns input values to respective CnV for RGB led
void rgb_led(unsigned int red, unsigned int green, unsigned int blue)
{
    TPM0->CONTROLS[1].CnV = blue;
    TPM2->CONTROLS[1].CnV = green;
    TPM2->CONTROLS[0].CnV = red;
}

// PWM test function to test all the values of different states
void test_pwm(void)
{
    for (int i=0; i<=MAX_PWM; i++)
    {
        rgb_led(i,0,0);
        Delay(5);
    }
    for (int i=0; i<=MAX_PWM; i++)
    {
        rgb_led(MAX_PWM,i,0);
        Delay(5);
    }
    for (int i=0; i<=MAX_PWM; i++)
    {
        rgb_led(0,i,0);
        Delay(5);
    }
}
