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



// - Bitte darauf achten, dass am Coldfire-Serial Port ein  
//   Terminal (Putty o.ä.) mit 19200kBaud angeschlossen ist.
// - Als Target muss   <projektname>_RAM_OSBDM   ausgewählt werden.

char string1[20] = "Dies ist String1";
char string2[20] = "Leerer String";


void* mymemcpy(void* ziel, const void* quelle, size_t anzahl){
asm{     naked                   //oder alternativ:   asm void* ... 

         link a6, #-2               // zum Spass eine lokale Variable (2 Bytes),
                                    // wird hier aber nicht gebraucht
         adda    #-12, sp
         movem.l d2/a2-a3,(sp)      //Register sichern

         move.l  16(a6),d2          //Anzahl hole              
         move.l  12(a6),a2          //Quelleadresse holen
         move.l  8(a6),a3           //Zieladresse holen
loop:                
         move.b  (a2)+,(a3)+        //byteweise kopieren
                
         subi.l   #1,d2
         bne     loop               //anzahl mal wiederholen

         move.l  8(a6),a0           //Rueckgabewert nach a0
                
         movem.l (sp),d2/a2-a3      //Register holen
         adda    #12, sp            //Stack i.O. bringen                  
         unlk    a6                 //Stackframe abbauen
         rts
}}



void main(void)
{
  int counter = 0;
  int x[10] = {0,1,2,3,4,5,6,7,8,9};
  int y[10] = {0};

  

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/


  
  
  #if (CONSOLE_IO_SUPPORT || ENABLE_UART_SUPPORT) 

  printf("String1        : %s\r\n", string1);
  printf("String2 vorher : %s\r\n", string2);

  /* C Version */
  printf("String2 nachher (mymemcpy in C aufgerufen): %s\r\n", mymemcpy(string2,string1,20));

  /* Assembler Version */
  asm { 
               move.l  #20,-(sp)   //Anzahl auf Stack
               pea     string1
               pea     string2
               jsr     mymemcpy    //Aufruf von mymemcpy
               adda      #10,sp    //Stack bereinigen (Parameterplatz freigeben)
  }

  printf("String2 nachher(mymemcpy in Assembler aufgerufen): %s\r\n", string2);

  
  printf("y vorher: ");
  for (counter=0; counter<10; counter++){
	  printf("%i, ",(long int)y[counter]);
  }
  mymemcpy(y,x,20);
  printf("\n\ry nachher: ");
  for (counter=0; counter<10; counter++){
	  printf("%i, ",(long int)y[counter]);
  }
 
#endif


// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

