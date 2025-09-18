## printf style debugging Adapter and C library for WCH CH551, CH552, CH554 microcontrollers
![deBug kit](https://raw.githubusercontent.com/Irdroid/deBug/refs/heads/main/Hardware/Pictures/deBug1.jpg)

The WCH CH55x series of MCUs are 8bit 89C51 core microcontrollers well equipped with peripherals such as UART modules, PWM modules, general purpose timers, touch modules and SPI modules . Those MCUs lack debug unit, such as JTAG or SWD, thus debugging is only possible with printf style serial debugging.

**deBug** is a Project that was started in 2025 with the aim to provide an easy to use hardware and software tools, that features printf style debugging for the CH55x series of MCUs.

The Project goal is to deliver to the user an easy to use printf style debugging solution and easy inclusion into new and existing Projects that use the CH55x MCUs. 

The physical debuging serial interface (CH551, CH552, CH554) is UART0. It is present in all MCUs from the CH55x series and it can be clocked via timer1 or timer2 (User configurable).

### Software
- The **deBug** Project provides a C library, that consist of four files - debug.c, debug.h, xprintf.c and xprintf.h. 
- To use the library in your Project you just need those four files. The library gives the user the ability to configure the required UART parameters to use the printf style debuging. 
- Minimal printf implementation (in order save flash space) which is available in xprintf.c and xprintf.h. (with this the library flash size is about 1.4k)
- The library also works with the standard printf (stdio.h), but this would require more flash space(about 3k)


To use the library you need to include the debug.h in your project and:

Provide the UART0 configuration settings in the deBug_t structure. The user can configure the BAUD rate, The UART TX pin mappings (which can be either P31 or P13) and the UART0 clock source (which can be either TIMER1 or TIMER2) 
```
deBug_t deBug = {
    .baudRate = DEBUG_BAUD_9600,              /* Baud rate 9600, 8 Data bits, no parity, 1 Stop bit */
    .txPin = DEBUG_UART0_TX_P31,              /* UART0 TX on Pin P31 */
    .uartClockSource = DEBUG_UART_CLK_SRC_T1  /* The timer, used as a clock source for the UART module */
};
```

Initialize the deBug library (which aslo initializes UART0):
```
/* Init Debuging library */
deBugInit(&deBug);
```

After the above initializations you can use printf as you normally do:
```
PRINTF("variable %u", var);
```

- The output from PRINTF will be sent to UART0.

- In addition to the printf, there is a interface via the deBugSendByte(uint8_t Data) function, which can be used to send bytes to UART0.

### Hardware
![deBug adapter for CH55x MCUs](https://raw.githubusercontent.com/Irdroid/deBug/refs/heads/main/Hardware/Pictures/deBug4.jpg)

deBug in style with our serial debugging adapter, the adapter shape says it all :) . You are too good and you are coding with no bugs? No problem, grab our adapter and use it as amulet! No bug will dare to enter you code :) 

- Debug by connecting just one wire (When the target and the debugging adapter are connected to the same PC)
- USB Type-C connection to the host PC
- Standard virtual serial port enumeration on the host PC

The serial debugging adapter comes with clamps, USB-C connection to the Host computer and a wrist keychain strap. The adapter is manufactured by Hardware Group Ltd. and can be purchased from from Tindie:

[Purchase - deBug adapter for CH55x MCUs](https://www.tindie.com/products/irdroid/debug-printf-style-debugging-adapter-for-ch55x/)


