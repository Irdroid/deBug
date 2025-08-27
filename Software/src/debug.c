// ===================================================================================
// Project:   deBug - CH55x printf style debugging library for WCH CH551, CH552, CH554  
// Year:      2025
// Author:    Georgi Bakalski
// Github:    https://github.com/irdroid
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// printf style debugging for CH551, CH552, CH554 over UART0. Uses the tiny xprintf
// library to save flash space.The output from the custom printf(xprintf) is redirected 
// to UART0. 
// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include "debug.h"
// ===================================================================================
// Static Function implementations
// ===================================================================================

/* Select the transmit pin for the UART0 module */
static void deBugSelectTxPin(deBugUartTxPin_t txPin)
{
    if(txPin == DEBUG_UART0_TX_P13){
            PIN_FUNC = (PIN_FUNC & ~bUART0_PIN_X) | bUART0_PIN_X;
    }else if(txPin == DEBUG_UART0_TX_P31){
            PIN_FUNC |= ~bUART0_PIN_X;
    }
}

// ===================================================================================
// Function implementations
// ===================================================================================

void deBugInit(deBug_t *deBugPtr)
{
    /* Select transmit pin for the UART0 Module */
	deBugSelectTxPin(deBugPtr->txPin);
	
    uint32_t x;
    volatile uint8_t x2;

    SM0 = 0;
    SM1 = 1;
    SM2 = 0;	

    x = 10 * (F_CPU / deBugPtr->baudRate / 16); /* If you change the main 
					frequency, be careful not to overflow the value of x */
    x2 = x % 10;
    x /= 10;
    if(x2 >= 5)x++;
	
	/* Configure the UART0 Clock source */
	switch (deBugPtr->uartClockSource)
	{
		case DEBUG_UART_CLK_SRC_T1:
            TCLK = 0;   /* UART0 transmit clock via Timer 1 */
            RCLK = 0;
            PCON |= SMOD;
			TMOD = TMOD & ~ bT1_GATE & ~ bT1_CT & ~ MASK_T1_MOD | bT1_M1;
			T2MOD = T2MOD | bTMR_CLK | bT1_CLK;
			TH1 = 0-x;                                                    	
			TR1 = 1;                                                      
			break;
        case DEBUG_UART_CLK_SRC_T2:
            TCLK = 1;   /* UART0 transmit clock via Timer 2 */
            C_T2 = 0;
            CP_RL2 = 0;
            T2MOD = T2MOD | bTMR_CLK | bT2_CLK;                             
            RCAP2=0-x;                                                    
            TR2 = 1;                                                               	
		default:
			break;
	}
    TI = 1;     /* Enable transmission */
    REN = 0;    /* Disable reception */                                                     
}

void deBugSendByte(uint8_t Data)
{
        SBUF = Data;	/* Write the byte into UART0 FIFO */
        while(TI ==0);	/* wait for transmit to finish (TI == 1) */
        TI = 0;			/* Clear TI */
}

#if SDCC < 370
/* @brief redirect putchar output to UART0,
 * It assumes the UART is initialized successfuly */
void putchar(char c)
{
    while (!TI); /* assumes UART is initialized */
    TI = 0;
    SBUF = c;
}

#else
/* @brief redirect putchar output to UART0,
 * It assumes the UART is initialized successfuly */
int putchar(int c)
{
    while (!TI); /* assumes UART is initialized */
    TI = 0;
    SBUF = c & 0xFF;

    return c;
}
#endif