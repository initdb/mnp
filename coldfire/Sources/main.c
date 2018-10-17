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
//   Terminal (Putty o.�.) mit 19200kBaud angeschlossen ist.
// - Als Target muss   <projektname>_RAM_OSBDM   ausgew�hlt werden.



void main(void)
{
  int counter = 0;

  

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/


  
  //TERM_WriteString("Los geht's!\r\n");
  
  asm
  { 
	  //start UEB1
	  	  BRA Start //Tells pointer to JMP onto Start
	  	  //hier variablen einf�gen
	  
	  	  str: DC.B "Hello u Benedict!\n\r" //String input
	  
	  Start:
	  	  LEA str,A1 		//Load Effective Address
	  Loop:
	  	  MOVE.B (A1)+,D0 	//Writes @A1 into D0
	  	  TST.B D0 			//Tests if D0 conatins only 0
	  	  BEQ End_Loop		//true -> jumps to end loop
	  	  MOVE.B D0,-(SP)	//false-> writes content of D0 to Stack
	  	  JSR TERM_Write	//call function TERM_Write
	  	  ADDA.L #1,SP		//clean Stack
	  
	  	  BRA Loop			//goto Loop label
	  End_Loop:				//end loop label
	  
	  //start UEB2
	  	  LEA str,A1
	  	  LEA str,A2
	  Loop2: 				//To find the last element of str While
	  	  MOVE.B (A1)+,D0	//increment poiter to 1 after str end
	  	  TST.B D0			//end loop to if content of D0 = 0
	  	  BEQ End_Loop2
	  	  
	  	  BRA Loop2			//We jmp back as long as str is not NULL
	  End_Loop2:
	  	  SUBA.L #1,A1		//move pointer back to str end
	  Loop3:
	  	  //MOVE.B -(A1),D0
	  	  SUBA.L #1,A1
	  	  CMP.L A1,A2
	  	  BEQ End_Loop3
	  	  JSR TERM_Write	//call function TERM_Write
	  	  //ADDA.L #1,SP		//clean Stack
	  	  
	  	  BRA Loop3
	  End_Loop3:
  }
 

 




// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */
