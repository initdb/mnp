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

/* ueb2a */

/* R. Hager , Maschinennahe Programmierung, Inf7, WS 1995/96,  © 1994-2006

   Musterlösung zu Aufgabe 2a (Vergleich Strings - Zeiger)

*/

/*
M.Hayn 08/10/09
- Bitte darauf achten, dass an dem CF-Serial Port ein Terminal mit 
  19200kBaud angeschlossen ist
- Als Target sollte INTERNAL_RAM ausgewählt sein
*/

char  textg[] = "Array global !\r\n";     /* globaler String */
char  *ptextg = "Pointer global !\r\n";   /* globaler Zeiger auf String */

int main(void)
{
	int counter = 0;
    char  textl[] = "Array local !\r\n";      /* lokaler String */
    char  *ptextl = "Pointer local !\r\n";    /* lokaler Zeiger auf String */	

    /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init(); /********************************************************/
	/***** End of Processor Expert internal initialization. **********************/



#if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT) 

    TERM_WriteString(textg);        //ergibt Code wie unten
 	TERM_WriteString(ptextg);
 	TERM_WriteString(textl);
 	TERM_WriteString(ptextl);

asm {  

start:          pea     textg                   //Ausgabe der Zeichenketten
                jsr     TERM_WriteString
                adda.l  #4, sp
                move.l  ptextg,-(sp)
                jsr     TERM_WriteString
                adda.l  #4, sp
                
                pea     textl
                jsr     TERM_WriteString
                adda.l  #4, sp
                move.l  ptextl,-(sp)
                jsr     TERM_WriteString 
                adda.l  #4, sp
}
	
	TERM_WriteLn();			         // Nächste Zeile im Terminal

#endif

	for(;;) {	   
	   	counter++;
	}
}
