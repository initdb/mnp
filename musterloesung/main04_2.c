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

  int zahl = 0x12af;
  

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/

  #if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT) 

   
     asm {

           bra     start

     hexaus:  ///////////////////////////////////////////////////////////////
              // Parameter: In hex auszugebender Wert (16 Bits) auf dem Stack
              ///////////////////////////////////////////////////////////////       
              
           link    a6,#0           //Stackframe aufbauen, 0 lokale Varaiablen

           adda   #-16, sp         //Platz auf Stack schaffen zum Sichern der 
                                   //Register (4x Long)
           movem.l d2-d5,(sp)      //Register sichern

           move.w  8(a6),d5        //Parameter holen => d5       
           move.l  #12,d4          //Schleifenzähler in d4

     loop:                        
           move.w  d5,d3           //kopieren nach d3
           lsr.l   d4,d3           //12/8/4/0 Bit nach rechts schieben  

           andi.l  #0x000f,d3      //Nibble ermitteln
           addi.l  #'0',d3         //in ASCII umwandeln
           cmpi.l  #'9',d3
           ble.b   kein_buchstabe
           addi.l  #'A'-'0'-10,d3  //Hex-Ziffern A - F
     kein_buchstabe: 
           move.b  d3,-(sp)        //Parameter auf den Stack (Byte)
           jsr     TERM_Write      //Nibble-Ziffer ausgeben
           adda   #1, sp           //Stack freigeben

           subi.l   #4,d4          //Shift-Register um 4 erniedrigen
           bge     loop            //insgesamt 4 mal wiederholen

           jsr     TERM_WriteLn    //neuZeile

           movem.l (sp),d2-d5      //gesicherte Register restaurieren
           adda   #16, sp          //Platz auf Stack wieder freigeben (4x Long)
                  
           unlk    a6              //Stackframe abbauen
           rts                     //Rücksprung
     //ende hexaus //////////////////////////////////////////////////////////////
                  

     start:                        //"Hauptprogramm" 
           move.w  zahl,-(sp)      //Parameter auf den Stack (Word=16 Bit)
           jsr     hexaus          //Aufruf des Unterprogramms hexaus
           adda   #2,sp            //Clear Stack (Word=16 Bit)
     }

#endif
  
 
 




// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

