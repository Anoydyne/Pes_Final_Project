/*************************************************************************
 *
 *    File name   : hexdump.c
 *    Description : functions for hexdump
 *
 *    Created on  : 04/30/2022
 *    Author      : Gauriech Ishaan Pilla
 *    Tools       : MCUXpresso IDE,GCC.
 *    Description : Contains functions for hexdump.
 *    Reference	  : Discussed logic for Hexdump with Swapnil Ghonge
 *
 **************************************************************************/

/**************************************************************************
 * File includes here
 **************************************************************************/

#include"hexdump.h"

/******************************************************************************
 * Defines here
 *****************************************************************************/
#define Hexdump_max_size 		(640)
#define char_per_line			(16)
#define Right_shift_28 			(28)
#define Right_shift_24 			(24)
#define Right_shift_20 			(20)
#define Right_shift_16 			(16)
#define Right_shift_12 			(12)
#define Right_shift_8			 (8)
#define Right_shift_4 			 (4)

// Function to convert given input integer to hexadecimal value
static char int_to_hexchar(int x)
{
    if (x >= 0 && x <= 9)
        return '0' + x;
    else if (x >= 10 && x <= 15)
        return 'A' + x - 10;
    else
        return '-';
}

// Takes input as start address and length, Prints hexdump for the given input on UART terminal

void hexdump(uint32_t Start, uint32_t Len)
{
    // Declaring Variables
    uint8_t *start_address = (uint8_t*) Start;
    const uint8_t *total_len = (uint8_t*) Start + Len;

    // For loop to print hexdump from starting address to the given length
    for (int i = 0; i < Len; i += char_per_line)
    {

        putchar(int_to_hexchar(((uint32_t )(start_address)) >> Right_shift_28));
        putchar(int_to_hexchar(((uint32_t )(start_address)) >> Right_shift_24));
        putchar(int_to_hexchar(((uint32_t )(start_address)) >> Right_shift_20));
        putchar(int_to_hexchar(((uint32_t )(start_address)) >> Right_shift_16));
        putchar('_');
        putchar(int_to_hexchar(((uint32_t )(start_address)) >> Right_shift_12));
        putchar(int_to_hexchar(((uint32_t )(start_address)) >> Right_shift_8));
        putchar(int_to_hexchar(((uint32_t )(start_address)) >> Right_shift_4));
        putchar(int_to_hexchar((uint32_t )(start_address) & 0x0000000F));
        putchar(' ');
        putchar(' ');

        for (int i = 0; i < char_per_line && start_address + i < total_len; i++)
        {
            putchar(int_to_hexchar(start_address[i] >> Right_shift_4));
            putchar(int_to_hexchar(start_address[i] & 0x0F));
            putchar(' ');
        }

        start_address += char_per_line;
        putchar('\n');
        putchar('\r');
    }

}
