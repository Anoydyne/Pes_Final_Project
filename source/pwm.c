/*************************************************************************
 *    File name   : pwm.c
 *    Description : functions for PWM initialization
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains function for initialization of RGB led's
 *    Reference	  : Code help taken from Dean PWM Section.
 *
 **************************************************************************/

/******************************************************************************
 * File includes here
 *****************************************************************************/

#include "pwm.h"

//initialize TPM0 module. Channel 1 (For Blue Led)
void Init_Blue_LED_PWM(uint16_t period)
{
    // Enable clock to port D
    SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;;

    // Blue FTM0_CH1, Mux Alt 4
    // Set pin to FTMs
    PORTD->PCR[BLUE_LED_POS] &= ~PORT_PCR_MUX_MASK;
    PORTD->PCR[BLUE_LED_POS] |= PORT_PCR_MUX(4);

    // Configure TPM
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
    //set clock source for tpm: 48 MHz
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
    //load the counter and mod
    TPM0->MOD = period-1;
    //set TPM count direction to up with a divide by 2 prescaler
    TPM0->SC =  TPM_SC_PS(1);
    // Continue operation in debug mode
    TPM0->CONF |= TPM_CONF_DBGMODE(3);
    // Set channel 1 to edge-aligned low-true PWM
    TPM0->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    // Set initial duty cycle
    TPM0->CONTROLS[1].CnV = 40;
    // Start TPM
    TPM0->SC |= TPM_SC_CMOD(1);
}

//initialize TPM2 module. Channel 1 (For Green Led)
void Init_Green_LED_PWM(uint16_t period)
{
    // Enable clock to port B
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;

    // Blue FTM0_CH1, Mux Alt 3
    // Set pin to FTMs
    PORTB->PCR[GREEN_LED_POS] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[GREEN_LED_POS] |= PORT_PCR_MUX(3);

    // Configure TPM
    SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
    //set clock source for tpm: 48 MHz
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
    //load the counter and mod
    TPM2->MOD = period-1;
    //set TPM count direction to up with a divide by 2 prescaler
    TPM2->SC =  TPM_SC_PS(1);
    // Continue operation in debug mode
    TPM2->CONF |= TPM_CONF_DBGMODE(3);
    // Set channel 1 to edge-aligned low-true PWM
    TPM2->CONTROLS[1].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    // Set initial duty cycle
    TPM2->CONTROLS[1].CnV = 0;
    // Start TPM
    TPM2->SC |= TPM_SC_CMOD(1);
}

//initialize TPM2 module. Channel 0 (For Red Led)
void Init_Red_LED_PWM(uint16_t period)
{
    // Enable clock to port B
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;;

    // Red FTM0_CH0, Mux Alt 3
    // Set pin to FTMs
    PORTB->PCR[RED_LED_POS] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[RED_LED_POS] |= PORT_PCR_MUX(3);

    // Configure TPM
    SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;
    //set clock source for tpm: 48 MHz
    SIM->SOPT2 |= (SIM_SOPT2_TPMSRC(1) | SIM_SOPT2_PLLFLLSEL_MASK);
    //load the counter and mod
    TPM2->MOD = period-1;
    //set TPM count direction to up with a divide by 2 prescaler
    TPM2->SC =  TPM_SC_PS(1);
    // Continue operation in debug mode
    TPM2->CONF |= TPM_CONF_DBGMODE(3);
    // Set channel 0 to edge-aligned low-true PWM
    TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    // Set initial duty cycle
    TPM2->CONTROLS[0].CnV = 0;
    // Start TPM
    TPM2->SC |= TPM_SC_CMOD(1);
}
