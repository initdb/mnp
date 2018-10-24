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
  uint32_t zahl = 0xAFFE;

  

  /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init(); /********************************************************/
  /***** End of Processor Expert internal initialization. **********************/


  
  //TERM_WriteString("Los geht's!\r\n");
  /* 
   * ueb1 + ueb2 
   * @TODO correct! */
  /*asm
  { 
	  //start UEB1
	  	  BRA Start //Tells pointer to JMP onto Start
	  	  //hier variablen einfügen
	  
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
	  	  MOVE A1,A2		//save beginning of string to A2
	  Loop2: 				//To find the last element of str While
	  	  MOVE.B +(A1),D0	//increment poiter to 1 after str end
	  	  TST.B D0			//end loop to if content of D0 = 0
	  	  BEQ End_Loop2
	  	  
	  	  BRA Loop2			//We jmp back as long as str is not NULL
	  End_Loop2:
	  
	  	  SUBA.B #1,A1		//move pointer back to str end
	  Loop3:
	  	  MOVE.B -(A1),D0
	  	  MOVE.B D0,-(SP)
	  	  JSR TERM_Write	//call function TERM_Write
	  	  ADDA.L #1,SP		//clean Stack
	  	  CMPA A1,A2
	  	  BEQ End_Loop3
	  	  
	  	  BRA Loop3
	  End_Loop3:
  }*/
 
  /*
   * ueb3
   * */
  
  
  asm
  {
	  	  // shift data right , #12 ersetzen
	  	  MOVE.L #12,D4
	  loop:
	  	  MOVE.L zahl,D1
	  	  LSR.L D4,D1
	  	  // mask with immediate data
	  	  ANDI.L #15,D1
	  	  // get ascii char
	  	  //Bedingungen für Jumps
	  	  //if(x <=9)
	  	  CMPI #9,D1 //D1-9 aka 0-9
	  	  BLE null_bis_neun //D1-9 <= 0
	  	  //else if(x > 9)
	  	  CMPI #9,D1 //D1-9
	  	  BGT A_bis_F //D1-9 > 0
	  continue_loop:
	  	  // print on uart
	  	  MOVE.B D1,-(SP)	//false-> writes content of D1 to Stack
	  	  JSR TERM_Write	//call function TERM_Write
	  	  ADDA.L #1,SP		//clean Stack
	  	  // check if D2 == 0 if true end loop
	  	  TST.L D4
	  	  BEQ end_loop
	  	  // decrement shift register
	  	  SUBQ.L #4,D4
	  	  BRA loop
	  
	  	  
	  null_bis_neun:
	  	  ADDI.L #48,D1
	  	  BRA continue_loop
	  A_bis_F:
	  	  ADDI.L #55,D1
	  	  BRA continue_loop
	  end_loop:
  }




// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
// **************************************************************
 
  for(;;){
	  counter++;
  }
 
}  /* END main */

