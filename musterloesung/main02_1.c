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


/* R. Hager , Maschinennahe Programmierung, WS 1994/95, 
   mit Ergänzungen von T. Tempelmeier, © 1994-2018

   Musterlösung zu Aufgabe 2 (Ausgabe eines Strings rückwärts)

*/

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



  asm { //Anfang Inline-Assembler-Block

       lea str,a2             // Zeiger auf String
       clr.l d3               // Zähler für Stringlänge

  noch_kein_Ende:

       addq.l #1,d3
       tst.b (a2)+            // tst  =  Vergleich mit 0

  bne noch_kein_Ende

       // d3 enthält jetzt die Anzahl der Zeichen des Strings einschließlich des 0-Byte.
       // a2 zeigt auf das Zeichen nach dem 0-Byte.

       subq.l #1, d3         // Anzahl Zeichen im String ohne 0-Byte
       subq.l #1, a2         // Zeiger um 1 zurückgesetzt (jetzt auf 0-Byte)

       bra schl_ende         // Einsprung ans Schleifenende
                             // => auch leere Strings werden richtig behandelt
                             // => Schleife muss von (AnzahlZeichen - 1) downto 0 laufen

  schleife:

       move.b -(a2),-(sp)    // Zeichen auf den Stack
       jsr TERM_Write        // Ausgabe eines Zeichens
       adda.l #1, sp         // Stack bereinigen (Parameterplatz freigeben)

     schl_ende:
       subq.l #1, d3         

  bge schleife


       jsr TERM_Read         // Warten auf Taste

  } /* Ende des Assembler-Blocks */

	
	TERM_WriteLn();			  // Nächste Zeile im Terminal

#endif



// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

