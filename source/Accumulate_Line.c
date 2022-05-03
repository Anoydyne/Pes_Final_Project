/*****************************************************************************
 *
 *    File name   : Accumulate_Line.c
 *    Description : function declarations for accumulate line functions
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions to take input from user and check for
 *    				enter key or backspace pressed. Sends the final user input
 *    				string to process command to perform various functions
 *	  Reference	  :	Code taken from PES Assignment 6
 *
 *
 *****************************************************************************/

/******************************************************************************
 * File includes here
 *****************************************************************************/
#include"Accumulate_Line.h"

/******************************************************************************
 * Defines here
 *****************************************************************************/

#define buffer_size     	(2000)				//defining buffer size
#define Carriage_Return 	(0X0D)				//Hex ASCII value for Enter
#define Backspace      		(0X08)				//Hex ASCII value for Backspace

void input_process_command()
{
    char buffer[buffer_size];
    char character;
    int i = 0;

    while (1)
    {
        while ((cbfifo_length(receiver) == 0))	//Waiting to receive a character
        {
            ;
        }
        cbfifo_dequeue(&character, 1, receiver);//Reading the received character
        putchar(character);						//Echo back on terminal

        if (character == Carriage_Return) 		//checking if user has pressed enter
        {
            buffer[i] = '\0'; 					//If enter is pressed terminate the string
            break;
        }
        else if (character == Backspace) 		//checking if user has pressed backspace.
        {
            //If backspace is pressed delete the character from the terminal and input buffer
            i--;
            printf(" \b");
        }
        else
        {
            buffer[i] = character;				//Store the received data in input buffer
            i++;								//Increment 'i' to store new character
        }

    }

    printf("\n\r");								//New line and return to head
    process_command(buffer);					//Calling command process to implement functions as per user input
}
