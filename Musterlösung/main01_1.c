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
 

/* R. Hager , Maschinennahe Programmierung, WS 1994/95,  
   mit Ergänzungen von T. Tempelmeier © 1994-2018

   Musterlösung zu Aufgabe 1 (Ausgabe eines Strings)

*/



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
  char str[] = "abcdefghijklmnopqrstuvwxyz";  

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/

  
#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT) 



asm { // Anfang Inline-Assembler-Block

     lea str,a2           // Zeiger auf String

schleife:
     move.b   (a2)+,d3
     beq schleife_zu_ende // wenn Zeichen = 0, dann fertig
     move.b   d3,-(sp)    // Zeichen auf den Stack
     jsr      TERM_Write  // Ausgabe eines Zeichens
     adda.l   #1, sp      // Stack bereinigen (Parameterplatz freigeben)
     bra schleife
     
schleife_zu_ende:
     jsr      TERM_Read   // Warten auf Taste

} // Ende Inline-Assembler-Block


	
	TERM_WriteLn();			  // Nächste Zeile im Terminal

#endif



// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

