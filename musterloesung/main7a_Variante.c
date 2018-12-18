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
#include <stdio.h>
#include <stdbool.h>


// - Bitte darauf achten, dass am Coldfire-Serial Port ein  
//   Terminal (Putty o.ä.) mit 19200kBaud angeschlossen ist.
// - Als Target muss   <projektname>_RAM_OSBDM   ausgewählt werden.

inline unsigned long int bitrev3 (unsigned long int x){      //   !!!! inline
     int i;
     unsigned long int result = 0;
     unsigned long int rechts = 0x00000001;
     unsigned long int links  = 0x80000000;
     for (i=0; i<=31; i++) {
    	 if ((x & rechts) == rechts) {result |= links;}      // Assembler: AND, OR
    	 rechts = rechts << 1;                   // Assembler: LSL
    	 links  = links  >> 1;    	             // Assembler: LSR
     }
     return result;
}
// Statt ((x & rechts) == rechts) würde auch (x & rechts) reichen. 

void main(void)
{
  int counter = 0;
  unsigned long int testdatum = 0x1234abcd;
  unsigned long int ergebnis;   // erwartet: 0xb3d52c48 = -1277875128
  

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/

  

asm{

      move.l testdatum, d0
      bitrev d0                 // Das ist der Befehl in der Hardware (in ISA A+ verfügbar)
      move.l d0, ergebnis
}

printf("Testergebnis BITREV (Hardware-Befehl in ISA_A+): %lx \r\n", ergebnis);

ergebnis = bitrev3(testdatum);
printf("Testergebnis BITREV3 (C Inline-Funktion):        %lx \r\n", ergebnis);

printf("Ende\n\r");


  

// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */






