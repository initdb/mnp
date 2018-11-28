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
//#include "malloc_wrapper.h"

#include <stdlib.h>



// - Bitte darauf achten, dass am Coldfire-Serial Port ein  
//   Terminal (Putty o.�.) mit 19200kBaud angeschlossen ist.
// - Als Target muss   <projektname>_RAM_OSBDM   ausgew�hlt werden.


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
 







 
             // Einzuh�ngendes Element aufbauen
             // -------------------------------
             // Tipp: Die Funktion malloc hat "register_abi", nicht "compact_abi". 
			 // Das bedeutet, dass die Parameterversorgung nicht �ber den Stack erfolgt, 
			 // sondern �ber Register, im vorliegenden Fall �ber Register D0.







  //          Ergebnis:
  //                  ___________ 
  //          a0 -->  |zahl|  0 | 
  //                  �����������    
             

  // Organisation der Listeniteration
  //
  // a2 zeigt auf das aktuelle Element (oder 0 f�r Listenende)
  // a3 zeigt   a u f   d e n   Z e i g e r   im vorhergehenden Element
  //
  //                              a3         a2 
  //                                \         \
  //  anker:                         \         \
  //  ______     ___________     _____V_____    V___________     ___________
  //  |    | --> |zahl|next| --> |zahl|next| --> |zahl|next| --> |zahl|  0 |
  //  ������     �����������     �����������     �����������     �����������
  //
  //    Funtioniert 
  //       + auch am Listenende (a3 zeigt auf 0, a2 ist 0)
  //       + auch bei Einf�gen vor dem ersten Element 
  //                           (a3 zeigt auf Anker, a2 auf das erste Element
  //       + auch bei leerer Liste (a3 zeigt auf Anker, Anker und a2 sind 0)


  // suchen der Einf�gestelle
  //-------------------------

       // Iterator-Paar initialisieren

	   
	   
  naechstes:      

  
  
  
  
  
  
  
  
  
  
  // Einf�gestelle gefunden: Objekt einh�ngen
  //-----------------------------------------                
  gefunden:
  



  
       bra     schleife         // naechste Zahl
                  
  // gesamte Liste ausgeben
  //-----------------------
  ausgabe: 









  
  ende:

  }

  #endif

// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

