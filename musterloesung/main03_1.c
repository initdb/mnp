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
  int zahl =  0x12ab;  // Diese Zahl soll als Hexwert ausgegeben werden  

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/

  

   
  asm {
                  move.l  #12,d5                  // Schleifenzähler in d5
             
  loop:
                  move.w  zahl,d4                 // Wort holen => d4
                  lsr.l   d5,d4                   // 12/8/4/0 Bits nach rechts schieben                                 
                  move.w  d4,d3                   // kopieren nach d3

                  andi.l  #0x000f,d3              // Nibble ermitteln
                  addi.l  #'0',d3                 // in ASCII umwandeln
                  cmpi.l  #'9',d3
                  ble.b   kein_buchstabe
                  addi.l  #'A'-'0'-10,d3          // Hex-Ziffern A - F
  kein_buchstabe: 
                  move.b  d3,-(sp)                // Zeichen auf den Stack
                  jsr     TERM_Write              // Nibble-Ziffer ausgeben
                  adda	  #1,sp					  // Stack in Ordnung bringen

                  subi.l	#4,d5
                  bge     loop                    // 4 mal wiederholen

                  jsr     TERM_WriteLn            // neue Zeile
                  
                  jsr     TERM_Read               // auf Taste warten
  }
    


 



// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

