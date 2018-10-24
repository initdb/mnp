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

/************************************************************
 * includes für uebungen
 ************************************************************/
#include "string.h"
#include "hextoascii.h"

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
	
	
	/***********************************************************************************
	 * Uebung2: Ausgabe eines Strings (rückwärts)
	 * Wie Übung 1, aber String rückwärts (beginnend mit dem letzen Zeichen) ausgeben:
	 **********************************************************************************/
	/*asm
	{ 
		
		
		LEA str,A1
		MOVE A1,A2		//save beginning of string to A2
		Loop2: 				//To find the last element of str While
			MOVE.B +(A1),D0	//increment poiter to 1 after str end
			TST.B D0			//end loop to if content of D0 = 0
			BEQ End_Loop2
					  
			BRA Loop2			//We jmp back as long as str is not NULL
		End_Loop2:
				  
		SUBA.L #1,A1		//move pointer back to str end
		Loop3:
			MOVE.B -(A1),D0
			MOVE.B D0,-(SP)
			JSR TERM_Write	//call function TERM_Write
			ADDA.L #1,SP		//clean Stack
			CMPA A1,A2
			BEQ End_Loop3
					  
		BRA Loop3
		
		End_Loop3:
	}
	 */
	
	string();
	//hex_to_ascii();
	 
	// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
	// **************************************************************
	 
	for(;;)
	{
		counter++;
	} 
}  /* END main */

