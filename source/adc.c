/********************************************************************************************************************
 *
 * 	File name 	: adc.c
 * 	Description : Contains functions to initialize and read ADC data
 *
 *   Created on  : 04/30/2022
 *   Author      : Gauriech Ishaan Pilla
 *   Tools       : MCUXpresso IDE,GCC.
 *   Reference	 : https://learningmicro.wordpress.com/
 *   			   interfacing-lm35-temperature-sensor-with-kl25z-mcu-using-nxp-kl25z-freedom-development-board/
 *
 ********************************************************************************************************************/

/*********************
 * File includes here
 *********************/
#include "adc.h"

/*********************
 * Defines
 *********************/
#define MSB_MASK 		(0x8000)

/**************************************************
Local function prototype
***************************************************/
static int adc_cal(void);

//Initialize the ADC Module
void init_ADC(void)
{
    int cal_adc;								// Variable used for calibrating ADC.

    // Enable ADC0 Clock
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;

    // Calibration of ADC
    do
    {
        cal_adc = adc_cal();
    }
    while (cal_adc == -1);

    // Configure ADC
    ADC0->SC1[0] |= (ADC_SC1_AIEN_MASK); 		// Conversion complete interrupt is enabled
    ADC0->SC1[0] &= ~ADC_SC1_DIFF_MASK;  		// Single Ended ADC

    // Reset CFG1 register
    ADC0->CFG1 = 0;
    ADC0->CFG1 |= (ADC_CFG1_MODE(2)  |   		// single-ended 10-bit mode
                   ADC_CFG1_ADICLK(1)|   		// (Bus Clock)/2
                   ADC_CFG1_ADIV(3)  |    	 	// The divide ratio is 8 i.e clock rate is (input clock)/8.
                   ADC_CFG1_ADLPC_MASK); 		// Low-power configuration

    ADC0->SC3  &= ~ADC_SC3_AVGE_MASK;			// Hardware average function enabled.
}


/*************************************************************************************************************
 *
 * Name :	static int adc_cal(void)
 *
 * Description : Calibrate the ADC Module.
 *
 * Inputs: None
 *
 * Return: None
 *************************************************************************************************************/
static int adc_cal(void)
{
    uint16_t calib;

    ADC0->CFG1 |= (ADC_CFG1_MODE(3)  |  		// single-ended 16-bit conversion
                   ADC_CFG1_ADICLK(1)|  		// (Bus Clock)/2
                   ADC_CFG1_ADIV(3));   		// The divide ratio is 8 i.e clock rate is (input clock)/8.

    ADC0->SC3  |= (ADC_SC3_AVGE_MASK |    		// Hardware average function enabled.
                   ADC_SC3_AVGS(3)   | 			// Set Hardware average to 32 samples.
                   ADC_SC3_CAL_MASK);   		// Begins the calibration process

    while (ADC0->SC3 & ADC_SC3_CAL_MASK); 		// While loop to wait for the calibration to end

    if (ADC0->SC3 & ADC_SC3_CALF_MASK)   		// Check if calibration was successful
        return -1;

    calib = 0;
    calib += ADC0->CLPS + ADC0->CLP4 + ADC0->CLP3 +
             ADC0->CLP2 + ADC0->CLP1 + ADC0->CLP0;
    calib /= 2;
    calib |= MSB_MASK;    // Set MSB
    ADC0->PG = calib;

    calib = 0;
    calib += ADC0->CLMS + ADC0->CLM4 + ADC0->CLM3 +
             ADC0->CLM2 + ADC0->CLM1 + ADC0->CLM0;
    calib /= 2;
    calib |= MSB_MASK;    // Set MSB
    ADC0->MG = calib;

    return 0;
}


// ADC read module
uint16_t adc_read(uint8_t adc_channel)
{
    // Write to SC1A to start conversion
    ADC0->SC1[0] = ((adc_channel & ADC_SC1_ADCH_MASK) |
                    (ADC0->SC1[0] &
                     (ADC_SC1_AIEN_MASK | ADC_SC1_DIFF_MASK)));

    while(ADC0->SC2 & ADC_SC2_ADACT_MASK);    		// Conversion in progress
    while(!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));		// wait until Conversion Complete Flag is set


    return ADC0->R[0];
}
