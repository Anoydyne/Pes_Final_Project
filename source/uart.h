/***********************************************************************************************************
 *
 *    File name   : uart.h
 *    Description : UART 0 Initialization functions
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains UART 0 Initialization functions
 *    Reference	  : Code reference taken from Dean UART section(chapter 8)
 *    DEAN Github - https://github.com/alexander-g-dean/ESF/tree/master/NXP/Code/Chapter_8/Serial-Demo
 *
 ************************************************************************************************************/

#ifndef UART_H_
#define UART_H_

/**************************************************************************
 * File includes here
 **************************************************************************/
#include <stdint.h>
#include <MKL25Z4.H>
#include "cbfifo.h"

/*************************************************************************************************************
 *
 * Name :			void Init_UART0(uint32_t baud_rate);
 *
 * Description :	Initialization of UART0 with user defined Baud rate
 *
 * Inputs:			uint32_t baud_rate - Baud rate for UART0
 *
 * Return: 			NONE
 *************************************************************************************************************/
void Init_UART0(uint32_t baud_rate);

#endif /* UART_H_ */
