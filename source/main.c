/*************************************************************************
 *
 *    File name   : main.c
 *    Description : Main Function
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Main Function
 *
 **************************************************************************/

/******************************************************************************
 * File includes here
 *****************************************************************************/

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "adc.h"
#include"mq7.h"
#include "i2c.h"
#include "sht21.h"
#include"sysclock.h"
#include"uart.h"
#include "pwm.h"
#include"rgb_led.h"
#include "timer.h"
#include "test_cbfifo.h"
#include"Accumulate_Line.h"
#include"timer.h"

/******************************************************************************
 * Defines here
 *****************************************************************************/
#define BAUD_RATE (38400)


// Main function
int main(void)
{

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    Init_UART0(BAUD_RATE);

    // initialization of led's
    Init_Red_LED_PWM(PWM_PERIOD);
    Init_Green_LED_PWM(PWM_PERIOD);
    Init_Blue_LED_PWM(PWM_PERIOD);

#ifdef DEBUG //Enable PWM automated testing only in debug mode
    test_pwm();
    printf("PWM Tested Successfully! \n\r");
#endif

    sysclock_init();	//	initialize the system clock
    init_I2C1();		//	initialize I2C1
    init_ADC();			//	initialize ADC
    init_systick();		//	initialize Systick timer

#ifdef DEBUG //Enable CBFIFO automated testing only in debug mode
    test_cbfifo();
    printf("CBFIFO Tested Successfully! \n\r");
#endif

    printf("\n\rWelcome to my PES Final Project! \n\r");
    printf("Created by Gauriech Ishaan Pilla.\n\r");
    printf("? ");


    // Enter an infinite loop
    while(1)
    {
        input_process_command();
    }
    return 0 ;
}
