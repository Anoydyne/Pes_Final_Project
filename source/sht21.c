/*************************************************************************
 *
 *    File name   : sht21.c
 *    Description : functions to get temperature and humidity values
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : functions to get temperature and humidity values
 *    Reference	  : Discussed logic for i2c with Tejaswini
 *
 **************************************************************************/

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include "sht21.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
#define SHT21_ADDRESS (0x40) 			// I2C device address for SHT21 (From Data sheet)
#define TEMPERATURE (0xE3) 				// hold master register address to get the temperature value
#define HUMIDITY (0xE5) 				// hold master register address to get the humidity value

// Function returns the current temperature value calculated from raw values obtained from sensor (SHT21)
float read_temperature(void)
{
	// Saving the raw values obtained from sensor in a variable
	uint16_t raw_data = I2C1_read(SHT21_ADDRESS,TEMPERATURE);
	// Clear the last 2 bits
	raw_data &= ~0x003;
	// Returns the result in °C. Formula referred from data sheet page 9 module 6.2
	return (-46.85 + 175.72/65536 * (float)raw_data);
}

// Function returns the current Humidity level value calculated from raw values obtained from sensor (SHT21)
float read_humidity(void)
{
	// Saving the raw values obtained from sensor in a variable
	uint16_t raw_data = I2C1_read(SHT21_ADDRESS,HUMIDITY);
	// Clear the last 2 bits
	raw_data &= ~0x003;
	// Returns the result in %RH. Formula referred from data sheet page 9 module 6.1
	return (-6.0 + 125.0/65536 * (float)raw_data);
}
