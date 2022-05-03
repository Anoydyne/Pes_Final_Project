/*************************************************************************
 *
 *    File name   : i2c.h
 *    Description : Contains function prototypes for i2c.c
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions to initialize and read for i2c.
 *    Reference	  : Discussed logic for i2c with Tejaswini
 *    				referred to I2C implementation by dean
 *
 **************************************************************************/
#ifndef I2C_H_
#define I2C_H_

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

/******************************************************************************
 *	Defines
 *****************************************************************************/

// I2c start signal with selecting master mode
#define I2C1_M_START (I2C1->C1 |= I2C_C1_MST_MASK)

// I2c Stop signal with selecting slave mode
#define I2C1_M_STOP 	(I2C1->C1 &= ~I2C_C1_MST_MASK)

// define to set the repeat start bit for generating the repeated start condition of I2c
#define I2C1_M_RSTART (I2C1->C1 |= I2C_C1_RSTA_MASK)

//Transit mode for I2c
#define I2C1_TRAN (I2C1->C1 |= I2C_C1_TX_MASK)

//Receiver mode for I2c
#define I2C1_REC (I2C1->C1 &= ~I2C_C1_TX_MASK)

// I2c wait define to wait until interrupt
#define I2C1_WAIT while((I2C1->S & I2C_S_IICIF_MASK)==0);\
					I2C1->S |= I2C_S_IICIF_MASK;

// Not acknowledge signal for I2c
#define I2C1_NACK (I2C1->C1 |= I2C_C1_TXAK_MASK)

// Acknowledge signal for I2c
#define I2C1_ACK (I2C1->C1 &= ~I2C_C1_TXAK_MASK)

// Wait until the transfer of byte and acknowledgment signal is completed
#define TRANS_COM while((I2C1->S & I2C_S_TCF_MASK)==0);


/*************************************************************************************************************
 *
 * Name :	void init_I2C1(void);
 *
 * Description : I2C1 initialize function
 *
 * Inputs: NONE
 *
 * Return: NONE
 *************************************************************************************************************/
void init_I2C1(void);

/*************************************************************************************************************
 *
 * Name :	void I2C1_Set_Flags(void);
 *
 * Description : I2C1 Function to set the required flags(ICR, IICEN and MULT)
 *
 * Inputs: NONE
 *
 * Return: NONE
 *************************************************************************************************************/
void I2C1_Set_Flags(void);

/*************************************************************************************************************
 *
 * Name :	uint16_t I2C1_read(uint8_t device_address,uint8_t register_address);
 *
 * Description : I2C1 Function to read the raw data from SHT21 (temperature and humidity)
 *
 * Inputs: device_address- I2C device address
 * 		   register_address- address of register(temperature or humidity) to read data from.
 *
 * Return: Returns the raw data value from sensor (temperature and humidity)
 *************************************************************************************************************/
uint16_t I2C1_read(uint8_t device_address,uint8_t register_address);

#endif /* I2C_H_ */
