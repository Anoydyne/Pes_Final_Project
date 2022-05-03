/*************************************************************************
 *
 *    File name   : sht21.h
 *    Description : Function prototypes of sht21.c
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : functions to get temperature and humidity values
 *    Reference	  : Discussed logic for i2c with Tejaswini
 *
 **************************************************************************/

#ifndef SHT21_H_
#define SHT21_H_

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
#include "i2c.h"

/*************************************************************************************************************
 *
 * Name :		  float read_temperature(void);
 *
 * Description :	This function is used to obtain the current temperature (result in °C).
 * 					Formula is referred from data sheet to convert the raw values from sensor to °C.
 *					Formula referred from data sheet page 9 module 6.2
 *
 * Inputs: NONE
 *
 * Return: Current Temperature in °C
 *
 *************************************************************************************************************/
float read_temperature(void);

/*************************************************************************************************************
 *
 * Name :		  float read_humidity(void);
 *
 * Description :	This function is used to obtain the current Humidity level (result in %RH).
 * 					Formula is referred from data sheet to convert the raw values from sensor to %RH.
 * 					Formula referred from data sheet page 9 module 6.1
 *
 * Inputs: NONE
 *
 * Return: Current Humidity level in %RH
 *
 *************************************************************************************************************/
float read_humidity(void);


#endif /* SHT21_H_ */
