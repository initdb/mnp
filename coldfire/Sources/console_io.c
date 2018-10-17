/** ###################################################################
**     Filename  : Tereminal_IO.C
**     Project   : Project
**     Processor : MCF
**     Compiler  : CodeWarrior MCF C Compiler
**     Date/Time : 21.12.2010, 9:53
**     Contents  :
**         This file contains methods for console IO to the UART.
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################*/

/* MODULE Tereminal_IO */

#include <file_struc.h>
#include <support_common.h>
#include "IO_Map.h"

#if defined(__MCF5301x__) || defined(__MCF5227x__)
  /* UART1 is used on hardware boards */
  #define PE_CONSOLE_UART_RX_DATA_REG URB1
  #define PE_CONSOLE_UART_TX_DATA_REG UTB1
  #define PE_CONSOLE_UART_STATUS_REG USR1
  #define PE_CONSOLE_UART_RXRDY_MASK USR1_RXRDY_BITMASK
  #define PE_CONSOLE_UART_TXRDY_MASK USR1_TXRDY_BITMASK
  #define PE_CONSOLE_UART_TXEMP_MASK USR1_TXEMP_BITMASK
#else
  /* UART0 hardware boards */
  #define PE_CONSOLE_UART_RX_DATA_REG MCF_UART0_URB
  #define PE_CONSOLE_UART_TX_DATA_REG MCF_UART0_UTB
  #define PE_CONSOLE_UART_STATUS_REG  MCF_UART0_USR
  #define PE_CONSOLE_UART_RXRDY_MASK  MCF_UART_USR_RXRDY
  #define PE_CONSOLE_UART_TXRDY_MASK  MCF_UART_USR_TXRDY
  #define PE_CONSOLE_UART_TXEMP_MASK  MCF_UART_USR_TXEMP
#endif

/* Function prototypes */
int __read_console(__file_handle handle, unsigned char* buffer, size_t * count);
int __write_console(__file_handle handle, unsigned char* buffer, size_t* count);
int __close_console(__file_handle handle);

/****************************************************************************/
/*
 *	__read_console
 *
 *  Receive the specified amount of data from the UART into the given buffer.
 */
/****************************************************************************/

 int __read_console(__file_handle handle, unsigned char* buffer, size_t * count)
{
#pragma unused(handle)

size_t i;
uint8 c;

  i = *count;
  *count = 0;
  while (i > 0) {
    while((PE_CONSOLE_UART_STATUS_REG & PE_CONSOLE_UART_RXRDY_MASK) != PE_CONSOLE_UART_RXRDY_MASK) {}; /* Get data from UART */
    c = PE_CONSOLE_UART_RX_DATA_REG;
    *buffer = c;
    (*count)++;
    
    if (c == '\n') {
      break;
    }
    if (c == '\r') {
      *buffer = '\n';
      break;
    }
    
    buffer++;
    i--;
  }
  /* Return receiver status */
  //return ((uint8)(testReg8Bits(USR1,USR1_OE_BITMASK | USR1_PE_BITMASK | USR1_FE_BITMASK | USR1_RB_BITMASK)));

  return (__no_io_error);
}


/****************************************************************************/
/*
 *	__write_console
 *
 *  Send the specified amount of data to the UART from the given buffer.
 */
/****************************************************************************/

int __write_console(__file_handle handle, unsigned char* buffer, size_t* count)
{
#pragma unused(handle)

size_t i;

  for (i = 0; i < *count; i++) {
    // Send '\r' before each '\n'.
    if (buffer[i] == '\n') {
      PE_CONSOLE_UART_TX_DATA_REG = '\r';
      // Wait until UART is ready to write a next character into output buffer
      while ((PE_CONSOLE_UART_STATUS_REG & PE_CONSOLE_UART_TXRDY_MASK) == 0) {};
    }
    // Save a character into the transmit buffer of the UART device
    PE_CONSOLE_UART_TX_DATA_REG = (unsigned char)buffer[i];
    // Wait until UART is ready for saving a next character into the transmit buffer
    while ((PE_CONSOLE_UART_STATUS_REG & PE_CONSOLE_UART_TXRDY_MASK) == 0) {};
  }
  // Wait until last character is sent
  while ((PE_CONSOLE_UART_STATUS_REG & PE_CONSOLE_UART_TXEMP_MASK) == 0) {};

  return(__no_io_error);
}

/****************************************************************************/
/*
 *  __close_console
 *
 *	Close the file specified by handle from the given buffer.
 */
/****************************************************************************/


int __close_console(__file_handle handle)
{
#pragma unused(handle )

  return(__no_io_error);
}

/* END Tereminal_IO */
