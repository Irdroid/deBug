// ===================================================================================
// Project:   deBug - CH55x printf style debugging library demo
// Year:      2025
// Author:    Georgi Bakalski
// Github:    https://github.com/irdroid
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// printf style debugging demo for CH551, CH552, CH554 over UART0, using deBug library
// The output from the custom printf(xprintf) is redirected to the UART0.

// Compilation Instructions:
// -------------------------
// - Chip:  CH551, CH552 or CH554
// - Clock: 24 MHz internal
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash' immediatly afterwards.

// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

#include "src/system.h"                   /* system functions */
#include "src/debug.h"                    /* deBug functions */
#include "delay.h"                        /* delay functions */

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  
  /* Configure the system clock */
  CLK_config();

  /* Wait for a stable clock */
  DLY_ms(5);

  // example variable for debugging
  uint16_t counter = 0;

  /* deBug configuration settings structure. 
   * Please note that on some development boards the pin P13
   * is not available, depending on the type of the chip package,
   * for example CH552G does not have Pin P13, CH552T does have it,
   * Check if this pin is available on your development board,
   * before configuring deBug with Pin P13. P31 should be available
   * on all development boards. 
   */
  deBug_t deBug = {
    .baudRate = DEBUG_BAUD_9600,              /* Baud rate 9600, 8 Data bits, no parity, 1 Stop bit */
    .txPin = DEBUG_UART0_TX_P31,              /* UART0 TX on Pin P31 */
    .uartClockSource = DEBUG_UART_CLK_SRC_T1  /* The timer, used as a clock source for the UART module */
  };
  
  /* Init Debuging library */
  deBugInit(&deBug);
  
  while(1) { 

    /* Debug style printf to UART0 */
    PRINTF("deBug: %u\n", counter); 

    /* Increment the counter variable */
    counter++;

    /* Wait */
    DLY_ms(500);
  }
}
