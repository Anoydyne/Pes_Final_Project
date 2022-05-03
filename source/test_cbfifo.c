/****************************************************************************************
 * 		File name : test_cbfifo.c
 * 		Description : Contains test cases for testing CBFIFO
 *
 *    	Created on  : 04/30/2022
 *    	Author      : Gauriech Ishaan Pilla
 *    	Tools       : MCUXpresso IDE,GCC.
 *   	Description : Contains test cases for testing both CBFIFO's
 *		Reference	: Code reference taken from professor lectures slide from lecture 5
 *					  lecture-Testing and Assignment 1 Review
 ***************************************************************************************/

/*****************************
 * File includes here
 ****************************/
#include "test_cbfifo.h"

/*************************************************************************************************************
 *
 * Name : static void test_cbfifo_transmiter()
 *
 * Description : tests cases for CBFIFO receiver buffer
 *
 * Inputs: Multiple inputs given to test.
 *
 * Return: returns print statement if all test cases have passed
 *
 **************************************************************************************************************/

static void test_cbfifo_transmiter()
{
    char str[261] = { 'H', 'e', 'l', 'l', 'o', 'I', 's', 'h', 'a', 'a', 'n',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'H', 'e', 'l', 'l', 'o', 'I', 's', 'h', 'a', 'a', 'n', 'a', 'b',
                      'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
                      'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
                      'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
                      'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
                      'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'H', 'e',
                      'l', 'l', 'o'
                    };
    char dequeque_buf[261];
    int expected_read = 0;
    int expected_write = 0;

    int capacity = cbfifo_capacity(transmitter);

    //Test 1-Putting NULL for enqueue
    assert(cbfifo_enqueue(NULL, 1, transmitter) == -1);

    //Test 2-Putting NULL for Dequeue
    assert(cbfifo_dequeue(NULL, 1, transmitter) == -1);

    //Test 3- Checking buffer length when empty
    assert(cbfifo_length(transmitter) == 0);

    // Test 4- Enqueue 60 bytes
    assert(cbfifo_enqueue(str, 60, transmitter) == 60);

    // Test 5- Dequeue 10 bytes. Compare both the buffers and check the expected length
    assert(cbfifo_dequeue(dequeque_buf, 10, transmitter) == 10);
    assert(strncmp(dequeque_buf, str, 10) == 0);
    assert(cbfifo_length(transmitter) == 50);

    // Test 6- Enqueue 65 bytes
    assert(cbfifo_enqueue(str, 65, transmitter) == 65);
    assert(cbfifo_length(transmitter) == 115);

    // Test 7- Dequeue all elements
    assert(cbfifo_dequeue(dequeque_buf, 115, transmitter) == 115);
    assert(cbfifo_length(transmitter) == 0);

    // Test 8- Enqueue full capacity, then try 1 more enqueue then dequeue all the elements.

    assert(cbfifo_enqueue(str, capacity, transmitter) == capacity);
    assert(cbfifo_length(transmitter) == capacity);
    assert(cbfifo_enqueue(str, 1, transmitter) == 0);
    assert(cbfifo_dequeue(dequeque_buf, capacity, transmitter) == capacity);
    assert(cbfifo_length(transmitter) == 0);
    assert(strncmp(dequeque_buf, str, capacity) == 0);

    //Test 9- when nbyte is equal to 0 it should return 0
    assert(cbfifo_enqueue(str, 0, transmitter) == 0);

    //Test 10- Dequeue when buffer length is zero should return 0
    assert(cbfifo_length(transmitter) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 1, transmitter) == 0);

    //Test 11- Testing read and write pointer in cbfifo
    assert(cbfifo_enqueue(str, capacity, transmitter) == capacity);
    expected_write = capacity;
    assert(cbfifo_length(transmitter) == capacity);
    assert(cbfifo_dequeue(dequeque_buf, 100, transmitter) == 100);
    expected_read = 100;
    assert(cbfifo_length(transmitter) == 156);
    assert(strncmp(dequeque_buf, str, 100) == 0);
    assert(cbfifo_enqueue(str + 25, 25, transmitter) == 25);
    expected_read += 25;
    assert(cbfifo_length(transmitter) == 181);

    //empty buffer for next test case
    assert(cbfifo_dequeue(dequeque_buf, 181, transmitter) == 181);
    assert(cbfifo_length(transmitter) == 0);

    //Test 12- Add 45 bytes and pull out 40 later remove all and empty
    assert(cbfifo_enqueue(str, 45, transmitter) == 45);
    assert(cbfifo_length(transmitter) == 45);
    assert(cbfifo_dequeue(dequeque_buf, 40, transmitter) == 40);
    assert(cbfifo_length(transmitter) == 5);
    assert(strncmp(dequeque_buf, str, 40) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 5, transmitter) == 5);
    assert(cbfifo_length(transmitter) == 0);

    //Test 13- Testing read and write pointer in cbfifo
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 100, transmitter) == 100);
    expected_write = 100;
    assert(cbfifo_length(transmitter) == 100);
    assert(cbfifo_dequeue(dequeque_buf, 32, transmitter) == 32);
    expected_read = 32;
    assert(cbfifo_length(transmitter) == 68);
    assert(strncmp(dequeque_buf, str, 32) == 0);
    assert(cbfifo_enqueue(str + expected_write, 12, transmitter) == 12);
    expected_read += 12;
    assert(cbfifo_length(transmitter) == 80);

    //empty buffer for next test case
    assert(cbfifo_dequeue(dequeque_buf, 80, transmitter) == 80);
    assert(cbfifo_length(transmitter) == 0);

    //Test 14- Enqueue elements and then dequeue more than that.
    assert(cbfifo_enqueue(str, 32, transmitter) == 32);
    assert(cbfifo_length(transmitter) == 32);
    assert(cbfifo_dequeue(dequeque_buf, 48, transmitter) == 32);
    assert(cbfifo_length(transmitter) == 0);
    assert(strncmp(dequeque_buf, str, 32) == 0);

    //Test 15- Enqueue elements and then dequeue more than that in two steps.
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 50, transmitter) == 50);
    assert(cbfifo_length(transmitter) == 50);
    expected_write = 50;
    assert(cbfifo_dequeue(dequeque_buf, 25, transmitter) == 25);
    assert(cbfifo_length(transmitter) == 25);
    expected_read = 25;
    assert(cbfifo_dequeue(dequeque_buf + expected_read, 30, transmitter) == 25);
    assert(cbfifo_length(transmitter) == 0);
    assert(strncmp(dequeque_buf, str, 50) == 0);

    //Test 16- Checking if capacity is 256
    assert(capacity == 256);

    //printf("\n\r test_cbfifo_transmiter- passed all test cases\n\r");
}

/*************************************************************************************************************
 *
 * Name : static void test_cbfifo_receiver()
 *
 * Description : tests cases for CBFIFO receiver buffer
 *
 * Inputs: Multiple inputs given to test.
 *
 * Return: returns print statement if all test cases have passed
 *
 **************************************************************************************************************/

static void test_cbfifo_receiver()
{
    char str[261] = { 'H', 'e', 'l', 'l', 'o', 'I', 's', 'h', 'a', 'a', 'n',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'H', 'e', 'l', 'l', 'o', 'I', 's', 'h', 'a', 'a', 'n', 'a', 'b',
                      'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
                      'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
                      'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B',
                      'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                      'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b',
                      'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'H', 'e',
                      'l', 'l', 'o'
                    };
    char dequeque_buf[261];
    int expected_read = 0;
    int expected_write = 0;

    int capacity = cbfifo_capacity(receiver);

    //Test 1-Putting NULL for enqueue
    assert(cbfifo_enqueue(NULL, 1, receiver) == -1);

    //Test 2-Putting NULL for Dequeue
    assert(cbfifo_dequeue(NULL, 1, receiver) == -1);

    //Test 3- Checking buffer length when empty
    assert(cbfifo_length(receiver) == 0);

    // Test 4- Enqueue 60 bytes
    assert(cbfifo_enqueue(str, 60, receiver) == 60);

    // Test 5- Dequeue 10 bytes. Compare both the buffers and check the expected length
    assert(cbfifo_dequeue(dequeque_buf, 10, receiver) == 10);
    assert(strncmp(dequeque_buf, str, 10) == 0);
    assert(cbfifo_length(receiver) == 50);

    // Test 6- Enqueue 65 bytes
    assert(cbfifo_enqueue(str, 65, receiver) == 65);
    assert(cbfifo_length(receiver) == 115);

    // Test 7- Dequeue all elements
    assert(cbfifo_dequeue(dequeque_buf, 115, receiver) == 115);
    assert(cbfifo_length(receiver) == 0);

    // Test 8- Enqueue full capacity, then try 1 more enqueue then dequeue all the elements.

    assert(cbfifo_enqueue(str, capacity, receiver) == capacity);
    assert(cbfifo_length(receiver) == capacity);
    assert(cbfifo_enqueue(str, 1, receiver) == 0);
    assert(cbfifo_dequeue(dequeque_buf, capacity, receiver) == capacity);
    assert(cbfifo_length(receiver) == 0);
    assert(strncmp(dequeque_buf, str, capacity) == 0);

    //Test 9- when nbyte is equal to 0 it should return 0
    assert(cbfifo_enqueue(str, 0, receiver) == 0);

    //Test 10- Dequeue when buffer length is zero should return 0
    assert(cbfifo_length(receiver) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 1, receiver) == 0);

    //Test 11- Testing read and write pointer in cbfifo
    assert(cbfifo_enqueue(str, capacity, receiver) == capacity);
    expected_write = capacity;
    assert(cbfifo_length(receiver) == capacity);
    assert(cbfifo_dequeue(dequeque_buf, 100, receiver) == 100);
    expected_read = 100;
    assert(cbfifo_length(receiver) == 156);
    assert(strncmp(dequeque_buf, str, 100) == 0);
    assert(cbfifo_enqueue(str + 25, 25, receiver) == 25);
    expected_read += 25;
    assert(cbfifo_length(receiver) == 181);

    //empty buffer for next test case
    assert(cbfifo_dequeue(dequeque_buf, 181, receiver) == 181);
    assert(cbfifo_length(receiver) == 0);

    //Test 12- Add 45 bytes and pull out 40 later remove all and empty
    assert(cbfifo_enqueue(str, 45, receiver) == 45);
    assert(cbfifo_length(receiver) == 45);
    assert(cbfifo_dequeue(dequeque_buf, 40, receiver) == 40);
    assert(cbfifo_length(receiver) == 5);
    assert(strncmp(dequeque_buf, str, 40) == 0);
    assert(cbfifo_dequeue(dequeque_buf, 5, receiver) == 5);
    assert(cbfifo_length(receiver) == 0);

    //Test 13- Testing read and write pointer in cbfifo
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 100, receiver) == 100);
    expected_write = 100;
    assert(cbfifo_length(receiver) == 100);
    assert(cbfifo_dequeue(dequeque_buf, 32, receiver) == 32);
    expected_read = 32;
    assert(cbfifo_length(receiver) == 68);
    assert(strncmp(dequeque_buf, str, 32) == 0);
    assert(cbfifo_enqueue(str + expected_write, 12, receiver) == 12);
    expected_read += 12;
    assert(cbfifo_length(receiver) == 80);

    //empty buffer for next test case
    assert(cbfifo_dequeue(dequeque_buf, 80, receiver) == 80);
    assert(cbfifo_length(receiver) == 0);

    //Test 14- Enqueue elements and then dequeue more than that.
    assert(cbfifo_enqueue(str, 32, receiver) == 32);
    assert(cbfifo_length(receiver) == 32);
    assert(cbfifo_dequeue(dequeque_buf, 48, receiver) == 32);
    assert(cbfifo_length(receiver) == 0);
    assert(strncmp(dequeque_buf, str, 32) == 0);

    //Test 15- Enqueue elements and then dequeue more than that in two steps.
    expected_write = 0;
    expected_read = 0;
    assert(cbfifo_enqueue(str, 50, receiver) == 50);
    assert(cbfifo_length(receiver) == 50);
    expected_write = 50;
    assert(cbfifo_dequeue(dequeque_buf, 25, receiver) == 25);
    assert(cbfifo_length(receiver) == 25);
    expected_read = 25;
    assert(cbfifo_dequeue(dequeque_buf + expected_read, 30, receiver) == 25);
    assert(cbfifo_length(receiver) == 0);
    assert(strncmp(dequeque_buf, str, 50) == 0);

    //Test 16- Checking if capacity is 256
    assert(capacity == 256);

    //printf("\n\r test_cbfifo_receiver- passed all test cases\n\r");
}

void test_cbfifo()
{
    test_cbfifo_transmiter();
    test_cbfifo_receiver();
}
