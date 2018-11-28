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


#define MEMBASE 0x20000000     // Unser Speicher beginnt an dieser Adresse


  int main(void)
  {
  	int counter = 0;

  	char  exeptiontext[] = "Hoppla, das war illegal !!\r\n";  
    char  starttext[]    = "Hallo, jetzt geht's los !!\r\n";
    char  endetext[]     = "Hallo - Programmende !!\r\n"; 


  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/

  
     #if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT) 

     
     asm {
              bra     start

        ////////////////////////////////////////////////////////////
        // Dies ist der "Exception Handler"
        
        Exception_Handler:
              pea     exeptiontext       // Ausgabe    
              jsr     TERM_WriteString   //
              adda    #4, sp			 // Stack freigeben
              
              add.l  #2, 4(sp)		     // Den auf dem Stack gespeicherten 
                                         // PC auf den nächsten Befehl setzen.
                                         // WICHTIGER HINWEIS:
                                         // Das ist i.A. keine sinnvolle Behandlung der Exception!!!
              rte
        /////////////////////////////////////////////////////////////                


        start:   
              lea Exception_Handler, a1  // Adresse des Exception Handlers einhängen in ...
              move.l  a1, MEMBASE+0x10   // Vektor Nr. 4 (Illegaler Opcode), Offset 0x10


              pea     starttext         // Ausgabe am Programmanfang
              jsr     TERM_WriteString
              adda    #4, sp            // Stack freigeben


              illegal                   // Illegaler Opcode  = 0x4afc
              //dc.w 0x4afc             // ginge ebenfalls


              pea     endetext          // Ausgabe am Programmende    
              jsr     TERM_WriteString
              adda    #4, sp            // Stack freigeben


              jsr TERM_Read             // Warten auf Tastendruck
     }

 

#endif


// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

