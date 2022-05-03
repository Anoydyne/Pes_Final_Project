/*****************************************************************************************
 * 		File name : test_cbfifo.h
 * 		Description : Contains test cases for testing CBFIFO
 *
 *   	Created on  : 04/30/2022
 *    	Author      : Gauriech Ishaan Pilla
 *   	Tools       : MCUXpresso IDE,GCC.
 *    	Description : Contains test cases for testing both CBFIFO's
 *		Reference	: Code reference taken from professor lectures slide from lecture 5
 *					  lecture-Testing and Assignment 1 Review
 *
 *****************************************************************************************/

/*********************
 * File includes here
 *********************/
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include "cbfifo.h"
#include "uart.h"
#include <assert.h>

/***************************************************************************************************************************
 *
 * Name :  void test_cbfifo();
 *
 * Description : Runs both test cases(Transmitter/Receiver).
 *
 * Input: NONE
 *
 * Return: NONE
 ***************************************************************************************************************************/
void test_cbfifo();
