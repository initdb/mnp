/*
 * string.c
 *
 *  Created on: Oct 24, 2018
 *      Author: Caroline, Benedict
 */

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

#include "string.h"

/****************************************************************
 * Uebung1: Ausgabe eines Strings
 * Mit einer Schleife alle Zeichen des Strings einzeln ausgeben
 ****************************************************************/
void string()
{
	asm
	{
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
	}	  
}
