/* ###################################################################
**     Filename    : main8.c
**     Project     : Uebung 8
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
//#include "malloc_wrapper.h"

#include <stdlib.h>



// - Bitte darauf achten, dass am Coldfire-Serial Port ein  
//   Terminal (Putty o.ä.) mit 19200kBaud angeschlossen ist.
// - Als Target muss   <projektname>_RAM_OSBDM   ausgewählt werden.


char     msginput[]  = "\r\nZahl eingeben (0 fuer Ende): "; 
char     msgfehler[] = "\nFehler bei malloc() !\n";

void     *anker = NULL;


  int main(void)
  {
     int counter = 0;

     
     /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
     PE_low_level_init(); /********************************************************/
     /***** End of Processor Expert internal initialization. **********************/

     #if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT)

           
  asm {

     schleife:  

             // Zahl einlesen (Ende vereinfachend mit Wert 0)
             //----------------------------------------------
             clr.l   d0
             pea     msginput
             jsr     TERM_WriteString
             adda    #4,sp          // Stack bereinigen
             jsr     INOUT_ReadInt  // Zahl einlesen
              
             tst.w   d0
             beq     ausgabe
             move.l  d0,d7          // Zahl in d7
             
             // Einzuhängendes Element aufbauen
             // -------------------------------
             move.l  #6,D0          // Speicher fuer Objekt allokieren      
             jsr     malloc         // !! Es gilt register_abi, also Parameter
                                    // !! über Register, nicht über den Stack
             tst.l   a0             // a0 enthaelt Zeiger auf neues Objekt
             beq     fehler            
             move.w  d7,(a0)        // Zahl ins Objekt
             clr.l   2(a0)          // Null-Zeiger ins Objekt 
  //                  ___________ 
  //          a0 -->  |zahl|  0 | 
  //                  ¯¯¯¯¯¯¯¯¯¯¯    
             

  // Organisation der Listeniteration
  //
  // a2 zeigt auf das aktuelle Element (oder 0 für Listenende)
  // a3 zeigt   a u f   d e n   Z e i g e r   im vorhergehenden Element
  //
  //                              a3         a2 
  //                                \         \
  //  anker:                         \         \
  //  ______     ___________     _____V_____    V___________     ___________
  //  |    | --> |zahl|next| --> |zahl|next| --> |zahl|next| --> |zahl|  0 |
  //  ¯¯¯¯¯¯     ¯¯¯¯¯¯¯¯¯¯¯     ¯¯¯¯¯¯¯¯¯¯¯     ¯¯¯¯¯¯¯¯¯¯¯     ¯¯¯¯¯¯¯¯¯¯¯
  //
  //    Funtioniert 
  //       + auch am Listenende (a3 zeigt auf 0, a2 ist 0)
  //       + auch bei Einfügen vor dem ersten Element 
  //                           (a3 zeigt auf Anker, a2 auf das erste Element
  //       + auch bei leerer Liste (a3 zeigt auf Anker, Anker und a2 sind 0)


  // suchen der Einfügestelle 
  //-------------------------

       // Iterator-Pärchen initialisieren
       lea     anker,a3      // Adresse von Zeiger auf Listenanfang in a3
       move.l  anker,a2      // Inhalt von Zeiger auf Listenanfang  in a2

  naechstes:      
       tst.l   a2            // Zeiger = NULL (Listenende), dann 
       beq     gefunden      // Position gefunden
    
    
       // Die nächsten drei Befehle sind Ersatz für cmp.w (a2), d7
       // Der zweite Befehl (EXT) könnte ev. leicht vergessen werden!!!
       move.w  (a2), d0         
       ext.l   d0            // weil cmp nur long möglich ist
       ext.l   d7            //   "       "     "
       cmp.l   d0,d7         // Zahl <= Zahl im Objekt, dann Position gefunden 
                             // d7 - (a2) <= 0,    also    d7 <= a2 
       ble     gefunden
             
       // andernfalls das Iterator-Paar fortschalten
       lea     2(a2),a3      // Adresse von naechstem Listenzeiger in a3
                             // entspricht      move.l a2,a3    adda.l #2,a3
       move.l  2(a2),a2      // Inhalt von naechstem Listenzeiger in a2
       bra     naechstes

  // Einfügestelle gefunden: Objekt einhängen
  //-----------------------------------------                
  gefunden:
       move.l  a2,2(a0)         // neues Objekt einhaengen
       move.l  a0,(a3)
             
       bra     schleife         // naechste Zahl
                  
  // gesamte Liste ausgeben
  //-----------------------
  ausgabe: 
       jsr     TERM_WriteLn          
       move.l  anker,a2         // wieder am Anker anfangen

  schleifeausgabe:                
       tst.l   a2               // am Ende der Liste ?
       beq     ende
       move.w  (a2),-(sp)       // Zahl ausgeben
       jsr     INOUT_WriteInt
       adda    #2,sp            // Stack i.O. bringen
       jsr     TERM_WriteLn
       move.l  2(a2),a2         // Zeiger auf naechstes Objekt nach a2 holen
       bra     schleifeausgabe
            
  fehler: 
       pea     msgfehler        // Fehlermeldung bei malloc()
       jsr     TERM_WriteString
       adda    #4,sp            // Stack i.O. bringen 
                  
  ende:

  }

  #endif

// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

