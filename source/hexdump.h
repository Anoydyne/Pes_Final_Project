/*************************************************************************
 *
 *    File name   : hexdump.h
 *    Description : Contains function prototypes for hexdump
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions for hexdump.
 *    Reference	  : Discussed logic for Hexdump with Swapnil Ghonge
 *
 **************************************************************************/

#ifndef HEXDUMP_H_
#define HEXDUMP_H_

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

/*************************************************************************************************************
 *
 * Name :	void hexdump(uint32_t Start, uint32_t Len);
 *
 * Description :Prints Hexdump from starting address to given length on terminal
 *
 * Inputs: uint32_t Start - starting address of hexdump
 * 		   uint32_t Len - length of hexdump
 *
 * Return: NONE
 *************************************************************************************************************/
void hexdump(uint32_t Start, uint32_t Len);

#endif /* HEXDUMP_H_ */
