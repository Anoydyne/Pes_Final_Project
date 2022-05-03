/*************************************************************************************************************************
 *
 * 	File name 	: adc.h
 * 	Description : Contains functions to initialize and read ADC data
 *
 *   Created on  : 04/30/2022
 *   Author      : Gauriech Ishaan Pilla
 *   Tools       : MCUXpresso IDE,GCC.
 *   Reference	 : https://learningmicro.wordpress.com/
 *   			   interfacing-lm35-temperature-sensor-with-kl25z-mcu-using-nxp-kl25z-freedom-development-board/
 *
 *************************************************************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/*********************
 * File includes here
 *********************/
#include <stdio.h>
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"


/*************************************************************************************************************
 *
 * Name :		void init_ADC(void);
 *
 * Description : Initialize the ADC Module.
 *
 * Inputs: None
 *
 * Return: None
 *************************************************************************************************************/
void init_ADC(void);

/*************************************************************************************************************
 *
 * Name :		uint16_t adc_read(uint8_t adc_channel);
 *
 * Description : Function to read the adc value.
 *
 * Inputs: adc_channel - ADC Channel
 *
 * Return: None
 *************************************************************************************************************/
uint16_t adc_read(uint8_t adc_channel);


#endif /* ADC_H_ */
