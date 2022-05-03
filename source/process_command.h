/***********************************************************************************************
 *
 *    File name   : process_command.h
 *    Description : command processing function prototypes and includes
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions to process the given user input
 *    Reference	  : Code reference taken from professor's command processing lecture slides
 *
 *
 ************************************************************************************************/

#ifndef PROCESS_COMMAND_H_
#define PROCESS_COMMAND_H_

/**************************************************************************
 * File includes here
 **************************************************************************/
#include "sysclock.h"
#include <stdint.h>
#include <stdio.h>
#include <MKL25Z4.H>
#include"uart.h"
#include "test_cbfifo.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "hexdump.h"
#include "adc.h"
#include "mq7.h"
#include "i2c.h"
#include "sht21.h"
#include "pwm.h"
#include"rgb_led.h"
#include"timer.h"

/************************************************************************************************************************
 *
 * Name :	void process_command(char *input);
 *
 * Description : Process command function. This function is used to decode the user input data, perform Lexical Analysis
 *  and run the code for the given user specified commands and perform the necessary functions.
 *
 * Input: Takes buffer input to perform the command processing functions
 *
 * Return: NONE
 ************************************************************************************************************************/
void process_command(char *input);

#endif /* PROCESS_COMMAND_H_ */
