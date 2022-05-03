/*************************************************************************
 *
 *    File name   : i2c.c
 *    Description : Contains functions to initialize and read for i2c
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions to initialize and read for i2c.
 *    Reference	  : Discussed logic for i2c with Tejaswini
 *    				referred to I2C implementation by dean
 *
 **************************************************************************/
/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "i2c.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define MSB_SHIFT		(8)
#define ONE				(1)


// I2c1 Initialize function
void init_I2C1(void)
{
    //Clock enabled for I2c
    SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;
    //Clock enabled for port E
    SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
}

// I2c1 Set flags function
void I2C1_Set_Flags(void)
{
    // Setting port for i2c. (SDA)
    PORTE->PCR[0] |= PORT_PCR_MUX(6);
    // Setting port for i2c. (SCL)
    PORTE->PCR[1] |= PORT_PCR_MUX(6);
    // Clearing bits of C1 register
    I2C1->C1 = 0;
    // Setting the frequency divider register.
    I2C1->F = I2C_F_ICR(0x11) |			//The SCL divider multiplied by multiplier factor (mul) determines the I2C baud rate.
              I2C_F_MULT(0);			//  Multiplier factor = 1
    //Enabled I2C1 interrupt requests
    I2C1->C1 |= (I2C_C1_IICEN_MASK);
    //selecting High drive mode
    I2C1->C2 |= (I2C_C2_HDRS_MASK);
}

// Function to read raw data from sensor
uint16_t I2C1_read(uint8_t device_address,uint8_t register_address)
{
    // Declaring variables
    uint8_t buffer;
    uint8_t buffer1;
    uint16_t result;

    I2C1_TRAN;
    I2C1_M_START;
    I2C1->D = device_address<<ONE; 				//shifted by 1 bit to make the LSB as 0 for writing to the register.
    TRANS_COM
    I2C1_WAIT;

    I2C1->D = register_address; 				//passing the register address
    TRANS_COM
    I2C1_WAIT;
    I2C1_M_RSTART;
    I2C1->D = ((device_address<<ONE)|0x01);		 //making the LSB as 1 to read from the register
    TRANS_COM
    I2C1_WAIT;

    I2C1_REC;
    I2C1_NACK;

    buffer = I2C1->D; 							// Read values before storing actual read data
    TRANS_COM
    I2C1_WAIT;

    buffer = I2C1->D; 							// Reading the value from register and store in buffer as MSB
    TRANS_COM
    I2C1_WAIT;
    buffer1 = I2C1->D; 							//Reading the value from register and store in buffer as LSB

    I2C1_M_STOP;

    result = (buffer<<MSB_SHIFT); 						// Result generated from buffer and store as MSB
    result += buffer1; 							// Adding the value to result from buffer1 to get complete result

    return result;
}
