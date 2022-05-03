/**********************************************************************************
 *
 *    File name   : Accumulate_Line.h
 *    Description : Contains Includes and Function Prototypes for Accumulate_Line.c
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions to take input from user and check for
 *    				enter key or backspace pressed. Sends the final user input
 *    				string to process command to perform various functions
 	  Reference	  :	Code taken from PES Assignment 6
 *
 **********************************************************************************/

#ifndef ACCUMULATE_LINE_H_
#define ACCUMULATE_LINE_H_

/*********************
 * File includes here
 *********************/
#include "uart.h"
#include "cbfifo.h"
#include <string.h>
#include <stdio.h>
#include "process_command.h"

/*************************************************************************************************************
 *
 * Name :		  	void input_process_command();
 *
 * Description : Takes character input and stores in input buffer and checks for
 *    			 enter key or backspace pressed.After user has given input , sends to
 * 				 command process to implement functions as per user input.
 *
 * Inputs: None
 *
 * Return: None
 *************************************************************************************************************/
void input_process_command();

#endif /* ACCUMULATE_LINE_H_ */
