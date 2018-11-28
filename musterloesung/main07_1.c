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


#define MEMBASE 0x20000000   // Unser Speicher beginnt an dieser Adresse


  int main(void)
  {
  	int counter = 0;
     

     int    userStack[20];
     int    j;


     #if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT) 

     
     /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
     PE_low_level_init(); /********************************************************/
     /***** End of Processor Expert internal initialization. **********************/

     
     
     for(j=0;j<20;j++) userStack[j]=0xaff0+j; // Userstack default init
      
      
     asm {

         bra     start
         
         
  //////////////////////////////////////////////////////////////////////////
     BS:                       // "Betriebssystem", hier nur Ausgabe eines Texts.
                               // Die Adresse des Textes wird als Parameter auf 
                               // dem User-Stack erwartet
							   // Der User Stack wird vom "Betriebssystem" 
							   // bereinigt; es ist nach dem Trap-Befehl keine 
							   // Korrektur des Stack Pointes nötig!
							   
     
         suba #24, sp          // Register sichern
         movem.l a0-a2/d0-d2,(sp)
         
         move   usp, a2        // UserStackPointer nach a2 kopieren.
		                       // a2 zeigt auf "Top of User Stack"
         move.l (a2),-(sp)     // Adresse des Strings vom UserStack holen und
                               // auf den aktuellen Stack (=SystemStack) speichern
         jsr TERM_WriteString  // String ausgeben
         lea     4(sp), sp     // Stack bereinigen (oder mit adda #4, sp

         adda.l #4, a2         // USP bereinigen: USP + 4, [alternativ: lea 4(a2),a2]
         move   a2, usp   
         
         movem.l a0-a2/d0-d2,(sp) 
         adda #24, sp          // Register restaurieren
         
         rte                   // Rücksprung aus BS
         
                               // Hinweis: In diesem einfachen Beispiel erfolgt der Rücksprung 
                               // *immer* zum aufrufenden Prozess! Wenn die BS-Funktion einen 
                               // Prozesswechsel verursacht, dann müssen (mindestens) alle 
                               // Register in den Prozessleitblock des Aufrufers gerettet
                               // werden, auch PC und SR auf dem System Stack. Die Register 
                               // des neuen Prozesses, auf den umgeschaltet wird, müssen aus  
                               // dessen Prozessleitblock restauriert werden (PC und SR via 
                               // System Stack und rte).
							   
							   // Hinweis: In einem echten Betriebssystem muss in der Regel 
							   // eine komplette Umschaltung der Adressräume erfolgen (nicht  
							   // nur eine Umschaltung auf einen anderen Stack). Siehe  
							   // Vorlesung Betriebssysteme, Kapitel "Virtuelle Adressierung".
              
  //////////////////////////////////////////////////////////////////////////       
                               
     start: 

         // BS initialisieren
         lea    BS, a1         // BS-Funktion in den User-Trap-Vektor 0 hängen
         move.l a1, MEMBASE + 0x80 + 0    // Trap-Vektoren ab Offset 0x80, 
                                          // hier Trap-Vektor Nr. 0
         
         // Anwendung initialisieren
         // Mindestens den UserStackPointer besetzen
         lea      userStack[20], a0    
         move.l   a0, usp 
   
         // in den User Mode schalten
         move.w	sr,d1
         andi.l  #0xdfff, d1
         move.w	d1,sr                             

  //////////////////////////////////////////////////////////////////////////
  // Anwendung im User Mode
  // jetzt sind wir im User-Mode

         bra userStart
             // User-Daten (nur Ausgabetexte)
             anfangsText: dc.b "Start User-Programm\r\n" 
             textBS:      dc.b "Textausgabe via BS-Aufruf via TRAP !!\r\n" 
             endeText:    dc.b "Ende User-Programm \r\n" 
         userStart: 
         
         pea anfangsText
         jsr TERM_WriteString  // String ausgeben
         adda.l #4, sp         // Stack bereinigen

         pea textBS            // Adresse des Strings auf den (User-)Stack  
         trap   #0             // Trap 0 (entspricht Einsprungstelle Nr. 0 ins BS)
		                       // Stack wird vom BS bereinigt
         
         pea endeText
         jsr TERM_WriteString  // String ausgeben
         adda.l #4, sp         // Stack bereinigen
  //////////////////////////////////////////////////////////////////////////
         
     }

     #endif

// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

