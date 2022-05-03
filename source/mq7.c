/********************************************************************************************************************
 *
 * 	File name 	: mq7.c
 * 	Description : Contains function to get CO levels data from ADC
 *
 *   Created on  : 04/30/2022
 *   Author      : Gauriech Ishaan Pilla
 *   Tools       : MCUXpresso IDE,GCC.
 *   Reference	 : https://learningmicro.wordpress.com/
 *   			   interfacing-lm35-temperature-sensor-with-kl25z-mcu-using-nxp-kl25z-freedom-development-board/
 *
 ********************************************************************************************************************/

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "mq7.h"

/******************************************************************************
 * Defines
 *****************************************************************************/

#define CO_SENSOR_CHN   		(15)				// ADC15 channel is mapped to PTC1 pin of KL25Z
#define DISABLE_ADC  			(31)				// Writing 0x1F (31) to ADCH register to disable the ADC
#define Right_shift_4 			 (4)
#define AVG_16					(16)

// Function to get the CO levels value from ADC
int get_co(void)
{
    // Declaring Variables
    static uint16_t adc_result;
    static uint16_t adc_result_avg;
    static uint8_t i;

    //Get 16 ADC Results for CO sensor
    for(i=0 ; i<AVG_16 ; i++)
    {
        adc_result += adc_read(CO_SENSOR_CHN);
    }

    adc_result_avg = adc_result >> Right_shift_4;       // Get ADC average value
    adc_result = 0;										// Setting result to zero

    // Disable the ADC Module
    ADC0->SC1[0] |= ADC_SC1_ADCH(DISABLE_ADC);

    return adc_result_avg;
}
