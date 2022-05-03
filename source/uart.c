/***********************************************************************************************************
 *
 *    File name   : uart.c
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

/**************************************************************************
 * File includes here
 **************************************************************************/
#include "uart.h"

/******************************************************************************
 * Defines here
 *****************************************************************************/
#define UART_OVERSAMPLE_RATE 	(16) 		//sampling rate
#define SYS_CLOCK				(24e6)	 	//system clock
#define STOP_BIT	  			(1)			//1 for 2 stop bits , 0 for 1 stop bit
#define PARITY      			(0)			//Parity none
#define BIT        				(0)			//0 for 8 bit, 1 for 9 bit

// Initializing UART0
void Init_UART0(uint32_t baud_rate)
{
    uint16_t sbr;

    // Enable clock gating for UART0 and Port A
    SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

    // Make sure transmitter and receiver are disabled before init
    UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

    // Set UART clock to 24 MHz clock
    SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
    //SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

    // Set pins to UART0 Rx and Tx
    PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
    PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

    // Set baud rate and oversampling ratio
    sbr = (uint16_t) ((SYS_CLOCK) / (baud_rate * UART_OVERSAMPLE_RATE));
    UART0->BDH &= ~UART0_BDH_SBR_MASK;
    UART0->BDH |= UART0_BDH_SBR(sbr >> 8);
    UART0->BDL = UART0_BDL_SBR(sbr);
    UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

    // Disable interrupts for RX active edge and LIN break detect, select two stop bit
    UART0->BDH |= UART0_BDH_RXEDGIE(
                      0) | UART0_BDH_SBNS(STOP_BIT) | UART0_BDH_LBKDIE(0);

    // Don't enable loopback mode, use 8 data bit mode, don't use parity
    UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(BIT) | UART0_C1_PE(PARITY);

    // Don't invert transmit data, don't enable interrupts for errors
    UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
                | UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

    // Clear error flags
    UART0->S1 = UART0_S1_OR(
                    1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

    // Send LSB first, do not invert received data
    UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

    // Enable interrupts. Listing 8.11 on p. 234

    NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);

    // Enable receive interrupts but not transmit interrupts yet
    UART0->C2 |= UART_C2_RIE(1);

    // Enable UART receiver and transmitter
    UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

    // Clear the UART RDRF flag
    UART0->S1 &= ~UART0_S1_RDRF_MASK;

}

// UART0 IRQ Handler. Listing 8.12 on p. 235
void UART0_IRQHandler(void)
{
    uint8_t rec_char;
    uint8_t trans_char;

    if (UART0->S1 & (UART_S1_OR_MASK | UART_S1_NF_MASK |
                     UART_S1_FE_MASK | UART_S1_PF_MASK))
    {
        // clear the error flags
        UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
                     UART0_S1_FE_MASK | UART0_S1_PF_MASK;
        // read the data register to clear RDRF
        rec_char = UART0->D;
    }
    if (UART0->S1 & UART0_S1_RDRF_MASK)
    {
        // received a character
        rec_char = UART0->D;
        if (!(cbfifo_capacity(receiver) == cbfifo_length(receiver)))
        {
            cbfifo_enqueue(&rec_char, 1, receiver);	//Enqueue the character to Receive Buffer
        }
        else
        {
            // error - queue full.
            // discard character
        }
    }
    if ((UART0->C2 & UART0_C2_TIE_MASK) && 		// transmitter interrupt enabled
            (UART0->S1 & UART0_S1_TDRE_MASK))
    {
        // tx buffer empty, can send another character
        {
            if (cbfifo_dequeue(&trans_char, 1, transmitter))
            {
                UART0->D = trans_char;
            }
            else
            {
                UART0->C2 &= ~UART0_C2_TIE_MASK;
            }
        }
    }
}

//This function is used to enqueque the character from transmit buffer
//This function replaces/ties to putchar() and printf() with uart function
int __sys_write(int handle, char *buf, int size)
{
    if (buf == NULL)
    {
        return -1;									// Return -1 if buf is NULL
    }

    while (cbfifo_length(transmitter) == cbfifo_capacity(transmitter))
    {
        ;
    }
    if (cbfifo_enqueue(buf, size, transmitter) == 0)
    {

        return -1;								// Return -1 if buffer is full
    }
    else
    {
        // start transmitter if it is not already started
        if (!(UART0->C2 & UART0_C2_TIE_MASK))
        {
            UART0->C2 |= UART0_C2_TIE(1);
        }
        return 0;

    }
}

//This function is used to dequeque the character from receiver buffer.
//This function replaces/ties to getchar() and sscanf() with uart function
int __sys_readc(void)
{
    int character;

    while (cbfifo_length(receiver) == 0)//Will return if the receive buffer is empty
    {
        ;
    }
    if (cbfifo_dequeue(&character, 1, receiver) == 1)
    {
        return character;
    }
    else
    {
        return -1;
    }
}
