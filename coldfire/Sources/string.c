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
void string_revert()
{
	char str[] = "Hello u qt ! ;)";
	
	asm
	{	
		// save str address in A1
		LEA str,A1
		// clear string length counter
		CLR.L D4
		
		count_elements:		//find the last element of str
			ADDQ.L #1,D4	//increment counter by 1
			TST.B (A1)+		//test if element pointed by A2 == 0 and increment pointer A2
		BNE count_elements	//end loop if TST==0
		
		SUBQ.L #1,A1		//move pointer back to str end
		SUBQ.L #1,D4		//substract count of D1 by 1
		
		BRA print_end
		
		print_elements:
				MOVE.B -(A1),-(SP)
				JSR TERM_Write		//call function TERM_Write
				ADDA.L #1,SP		//clean Stack
			print_end:
				SUBQ.L #1,D4		//decrement counter
		BGE print_elements
	}
}
