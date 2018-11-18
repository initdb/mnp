/*
 * mymemcopy.c
 *
 *  Created on: Nov 18, 2018
 *      Author: Benedict
 */

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"
#include <stdio.h>


#include "mymemcopy.h"


/****************************************************************
 * Uebung5: mymemcopy											*
 * 			Erstellung und Test eines Unterprogramms mymemcopy.	*
 * 			Aufruf des Unterprogramms aus C.					*
 * 			Funktionskopf in C									*
 * 			Eingangs-, Ausgangs-, 								*
 * 			Frame- und Return-Code in Assembler					*
 ****************************************************************/

void introUe5()
{
	TERM_WriteString("\r\n########################################################################\r\n");
	TERM_WriteString("\r\nUebung05: mymmemcopy\r\n");
	TERM_WriteString("Erstellung und Test eines Unterprogramms mymemcopy (analog zu memcopy)\r\n");
	TERM_WriteString("und Aufruf des Unterprogramms aus C\r\n");
	TERM_WriteString("\r\n########################################################################\r\n");
}

void* mymemcopy(void* destination, const void* source, size_t size)
{		
	asm
	{ 
		NAKED					// look up

		/********************************************
		 * handle exception here!!					*
		 ********************************************/
		LINK 	A6,#0			// save FP/A6
		ADDA.L 	#-12,SP			// prepare to save reg onto stack
		MOVEM.L D2/A2-A3,(SP)	// save regs on stack
		
		/********************************************
		 * handle exception here!!					*
		 ********************************************/
		MOVE.L  16(A6),D2		// copy param size in D2
		MOVE.L  12(a6),A2		// copy param source in A2
		MOVE.L  8(A6),A3		// copy param destination in A3
		
		/********************************************
		 * handle exception here!!					*
		 ********************************************/
		Loop:
			MOVE.B  (A2)+,(A3)+		// copy contents of A2 to A3
			SUBI.L  #1,D2			// decrement size(D2) of source
			TST.B   D2				// asserts size(D2) equals 0
		BNE     Loop			//if not continue copying 
		
		/********************************************
		 * handle exception here!!					*
		 ********************************************/
		MOVE.L  8(A6),A0		//Ziel nach a0 rückgabewert
		MOVEM.L (SP),D2/A2-A3	//Register holen vom Stack	
		ADDA.L 	#12,SP			//Speicherfreigeben von Register auf SP
		UNLK 	A6				//FP vom Stack nehmen

		RTS						//return from subroutine
	}		
}
	
void outro()
{
	TERM_WriteString("\r\n########################################################################\r\n\r\n");
}
