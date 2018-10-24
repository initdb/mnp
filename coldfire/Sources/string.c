/************************************
 * string.c							*
 *									*
 *  Created on: Oct 24, 2018		*
 *      Author: Caroline, Benedict	*
 ************************************/

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

#include "string.h"

/****************************************************************
 * Uebung1: Ausgabe eines Strings								*
 * Mit einer Schleife alle Zeichen des Strings einzeln ausgeben	*
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

/****************************************************************
 * Uebung2: Ausgabe eines Strings (rückwärts)					*
 * Wie Übung 1, aber String rückwärts 							*
 * (beginnend mit dem letzen Zeichen) ausgeben:					*
 ****************************************************************/
string_revert()
{
	asm
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
}
