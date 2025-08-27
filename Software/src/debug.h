// ===================================================================================
// Project:   deBug - CH55x printf style debugging library for CH551, CH552, CH554 
// Year:      2025
// Author:    Georgi Bakalski
// Github:    https://github.com/irdroid
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// printf style debugging for CH551, CH552, CH554 over UART0, Uses the tiny printf
// library to save space.The output from the custom printf(xprintf) is redirected 
// to UART0. 
#pragma once
// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================
#include "xprintf.h"
#include "ch554.h"

#define VERSION_MAJOR   1
#define VERSION_MINOR   0
#define VERSION_PATCH   0

// ===================================================================================
// Data types and Structures
// ===================================================================================

/* Possible baud rate settings*/
typedef enum
{
    DEBUG_BAUD_9600    =  9600,
    DEBUG_BAUD_19200   =  19200,
    DEBUG_BAUD_38400   =  38400,
    DEBUG_BAUD_57600   =  57600,
    DEBUG_BAUD_115200  =  115200
}deBugBaudRate_t;

/* Possible clock sources for the UART0 module */
typedef enum 
{
    DEBUG_UART_CLK_SRC_T1,    /* Timer 1 as clock source for UART0 */
    DEBUG_UART_CLK_SRC_T2     /* Timer 2 as clock source for UART0 */    
}deBugUartClockSrc_t;

/* Possible Pin mappings of UART0 module */
typedef enum
{
    DEBUG_UART0_TX_P31,   /* UART0 TX on pin P31 */
    DEBUG_UART0_TX_P13    /* UART0 TX on pin P13 */
}deBugUartTxPin_t;

/* deBug Driver context */
typedef struct{
    deBugBaudRate_t     baudRate;           /* The UART0 Baud rate to be configured */
    deBugUartClockSrc_t uartClockSource;    /* UART0 Clock source */
    deBugUartTxPin_t    txPin;              /* UART0 transmit pin configuration */
}deBug_t;

// ===================================================================================
// Function declarations
// ===================================================================================

/* @brief Initialize debugging via UART0 module
*
*  @param debBugPtr - reference to the driver instance
*/
void deBugInit(deBug_t *deBugPtr);

/* @brief Send byte via UART0 
*  @param Data - the byte to be sent
*/
void deBugSendByte(uint8_t Data);

#if SDCC < 370
void putchar(char c);
#else
int putchar(int c);
#endif


