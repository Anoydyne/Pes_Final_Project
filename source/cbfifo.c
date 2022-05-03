/****************************************************************************
 *
 * 	File name 	: cbfifo.c
 * 	Description : Contains functions to implement circular buffer FIFOs
 *
 *   Created on  : 04/30/2022
 *   Author      : Gauriech Ishaan Pilla
 *   Tools       : MCUXpresso IDE,GCC.
 *   Reference	 : Adapted the logic from Cbfifo used in PES Assignment 2
 *
 ****************************************************************************/

/*********************
 * File includes here
 *********************/

#include"cbfifo.h"

/******************************************************************************
 * Defines here
 *****************************************************************************/
#define CB_size (256)   //Define maximum CBFIFO byte size

/************************************
 * Structure defined
 ************************************/

typedef struct circular_buffer
{
    uint8_t buffer[CB_size];
    int write;
    int read;
    int buffer_length;
} cbfifo;

/******************************************************
 * Two types of fifo. Enum defined for this in .h file
 *******************************************************/
cbfifo CB_fifo_type[2];

/*************************************************************************************************************
 *
 * Name : size_t cbfifo_enqueue(void *buf, size_t nbyte,uint32_t command_type)
 *
 * Description : Enqueues data onto the CB_fifo_type, up to the limit of the available CB_fifo_type capacity.
 *
 * Inputs: *buf  			Destination for the dequeued data
 *         nbyte 			Bytes of data requested
 *		  command_type		Fifo type defined here(transmitter/receiver)
 *
 * Return: The number of bytes actually enqueued, which could be 0. In case of an error, returns -1.
 *
 *************************************************************************************************************/

size_t cbfifo_enqueue(void *buf, size_t nbyte, uint32_t command_type)
{
    size_t length_e = 0;                                   	// declaring variable
    uint32_t primask;
    if (buf == NULL)                     					//Checking whether buf is equal to NULL
    {
        return -1;                                         	// Return Value
    }
    else if (nbyte == 0)               						// Checking whether nbyte is equal to 0
    {
        return 0;                                          	// Return Value
    }
    //Checking whether buffer length is more than or equal to maximum size
    else if (CB_fifo_type[command_type].buffer_length >= CB_size)
    {
        return 0;                                          // Return Value
    }
    // If nbyte is more than difference of maximum size and length of buffer
    else if (nbyte > (CB_size - CB_fifo_type[command_type].buffer_length))
    {
        nbyte = CB_size - CB_fifo_type[command_type].buffer_length; 	// Assigning value of nbyte
    }
    {
        primask = __get_PRIMASK();

        __disable_irq();

        for (int i = 0; i < nbyte; i++)                   	// For loop to enqueue
        {
            //filling data into the buffer
            CB_fifo_type[command_type].buffer[CB_fifo_type[command_type].write] = *(uint8_t*) (buf + i);
            length_e++;                  					//Incrementing length of bytes enqueued
            CB_fifo_type[command_type].buffer_length++; 	//Incrementing the length of buffer
            CB_fifo_type[command_type].write++; 			//Incrementing the write pointer
            if (CB_fifo_type[command_type].write == CB_size)//If write pointer reaches maximum size
            {
                CB_fifo_type[command_type].write = 0; 		//Write pointer points to beginning i.e. 0
            }

        }

        __set_PRIMASK(primask);
        return length_e;                 					//Returning the total elements enqueued
    }
}

/******************************************************************************************************************************************************
 *
 * Name : size_t cbfifo_dequeue(void *buf, size_t nbyte,uint32_t command_type)
 *
 * Description : Attempts to remove ("dequeue") up to nbyte bytes of data from the CB_fifo_type. Removed data will be copied into the buffer pointed to by buf
 *
 * Inputs:  *buf     			    Destination for the dequeued data
 *           nbyte    				Bytes of data requested
 *			command_type  			Fifo type defined here(transmitter/receiver)
 *
 * Return: The number of bytes actually copied, which will be between 0 and nbyte.
 *
 ********************************************************************************************************************************************************/

size_t cbfifo_dequeue(void *buf, size_t nbyte, uint32_t command_type)
{

    size_t length_d = 0;                                   	// declaring variable
    uint32_t primask;

    if (buf == NULL)                     					//Checking whether buf is equal to NULL
    {
        return -1;                                          // Return Value
    }
    else if (CB_fifo_type[command_type].buffer_length == 0)   //Checking whether buffer length is equal to 0
    {
        return 0;                                          // Return Value
    }
    else if (nbyte == 0)               				     // Checking whether nbyte is equal to 0
    {
        return 0;                                          // Return Value
    }
    else if (nbyte > CB_fifo_type[command_type].buffer_length)   // If nbyte is more than length of buffer
    {
        nbyte = CB_fifo_type[command_type].buffer_length;  // Assign length of buffer to nbyte
    }
    else
    {
        nbyte = nbyte;                					   //else let nbyte value remain unchanged
    }

    primask = __get_PRIMASK();

    __disable_irq();

    for (int i = 0; i < nbyte; i++)                 		// For loop to dequeue bytes
    {
        // dequeuing bytes to location pointed by buff
        *(uint8_t*) buf = CB_fifo_type[command_type].buffer[CB_fifo_type[command_type].read];
        length_d++;                     					// Incrementing length of bytes dequeued
        CB_fifo_type[command_type].buffer_length--; 		// Decrementing buffer length
        buf = (uint8_t*) buf + 1;                         	// Incrementing buffer
        CB_fifo_type[command_type].read++;          		// Incrementing read pointer
        if (CB_fifo_type[command_type].read == CB_size) 	// If read pointer reaches maximum size
        {
            CB_fifo_type[command_type].read = 0; 			// Read pointer points to beginning i.e. 0
        }

        __set_PRIMASK(primask);
    }
    return length_d;                    					// Returning the total elements dequeued
}

/**************************************************************************
 *
 * Name : size_t cbfifo_length(uint32_t command_type)
 *
 * Description : This function returns the length of CBFIFO
 *
 * Inputs: command_type- Fifo type defined here(transmitter/receiver)
 *
 * Return: Returns the length of CBFIFO.

 *****************************************************************************/

size_t cbfifo_length(uint32_t command_type)
{
    return CB_fifo_type[command_type].buffer_length; 		//Returning length of buffer
}

/*********************************************************************
 *
 * Name : size_t cbfifo_capacity(uint32_t command_type)
 *
 * Description : The function returns the maximum capacity of CBFIFO
 *
 * Inputs: command_type- Fifo type defined here(transmitter/receiver)
 *
 * Return: Returns the maximum capacity of CBFIFO.

 ***********************************************************************/
size_t cbfifo_capacity(uint32_t command_type)
{
    return CB_size;                   						//Returning the maximum capacity of CBFIFO
}

/*************************************************************************************************************
 *
 * Name :	void cbfifo_reset(uint32_t command_type);
 *
 * Description :	resets cbfifo
 *
 * Inputs: command_type- The buffer(transmitter/receiver) which has to be reset
 *
 * Return: None
 *************************************************************************************************************/
void cbfifo_reset(uint32_t command_type)
{
    CB_fifo_type[command_type].buffer_length = 0;
    CB_fifo_type[command_type].read = 0;
    CB_fifo_type[command_type].write = 0;
}
