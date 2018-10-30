/* ###################################################################
**     Filename    : main.c
**     Project     : test8
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2014-10-11, 15:20, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/                  
/* MODULE main */ 
 
  #pragma compact_abi 
 

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)

#include "terminal_wrapper.h"

// - Bitte darauf achten, dass am Coldfire-Serial Port ein  
//   Terminal (Putty o.ä.) mit 19200kBaud angeschlossen ist.
// - Als Target muss   <projektname>_RAM_OSBDM   ausgewählt werden.



void main(void)
{
  int counter = 0;
    

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/

  
 #define SYSTEM_CLOCK_KHZ 80000 // System clock is 80.000.000 Hz
 uart_init(0, SYSTEM_CLOCK_KHZ, kBaud19200);
 	
 uart_putchar(0, 'X');
 uart_putchar(0, '\r');  
 uart_putchar(0, '\n'); 
 
 

	// Ein Aufruf von uart_putchar in Assembler
	
	asm{
	                         // Param2: ASCII-Code von Y
	   move.b #'Y', -(SP)    // auf den Stack
	   
	   move.w #0,   -(SP)    // Param1: channel 0 auf den Stack
	                         // move.WORD, weil bei uns ein int 2 Bytes hat
							 // (Das war mein Fehler: 
							 // - falsches Projekt macht den Aufruf oben für 'X' mit move.LONG, weil dort ein int 4 Bytes hat
							 // - ich habe die 4 Bytes = LONG übernommen, obwohl das richtige Projekt nur 2 Bytes für ein int hat
							 // - im richtigen Projekt -also bei Ihnen- ging's dann mit move.LONG = 4 Bytes schief
							 // Entschuldigen Sie bitte meinen Fehler.)
							 
	   jsr uart_putchar
	   adda.l #3, SP         // Parameter auf dem Stack wieder freigeben
	   
	}

	
	TERM_Write('Z');



// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

