/********************************************************************************************************************
 *
 * 	File name 	: mq7.h
 * 	Description : Contains function prototypes for mq7.c
 *
 *   Created on  : 04/30/2022
 *   Author      : Gauriech Ishaan Pilla
 *   Tools       : MCUXpresso IDE,GCC.
 *   Description : Contains function to get CO levels data from ADC
 *   Reference	 : https://learningmicro.wordpress.com/
 *   			   interfacing-lm35-temperature-sensor-with-kl25z-mcu-using-nxp-kl25z-freedom-development-board/
 *
 ********************************************************************************************************************/

#ifndef MQ7_H_
#define MQ7_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"
#include "math.h"
#include "adc.h"

/*************************************************************************************************************
 *
 * Name :	int get_co(void);
 *
 * Description : Function to get the CO levels value from ADC
 *
 * Inputs: NONE
 *
 * Return: Raw values of CO Levels
 *************************************************************************************************************/
int get_co(void);

#endif /* MQ7_H_ */
