/*
 * mymemcopy.c
 *
 *  Created on: Nov 18, 2018
 *      Author: Benedict
 */


#include "mymemcopy.h"


/****************************************************************
 * Uebung5: mymemcopy											*
 * 			Erstellung und Test eines Unterprogramms mymemcopy.	*
 * 			Aufruf des Unterprogramms aus C.					*
 * 			Funktionskopf in C									*
 * 			Eingangs-, Ausgangs-, 								*
 * 			Frame- und Return-Code in Assembler					*
 ****************************************************************/

void intro()
{
	TERM_WriteString("\r\n########################################################################\r\n");
	TERM_WriteString("\r\nUebung05: mymmemcopy\r\n");
	TERM_WriteString("Erstellung und Test eines Unterprogramms mymemcopy (analog zu memcopy)\r\n");
	TERM_WriteString("und Aufruf des Unterprogramms aus C\r\n");
	TERM_WriteString("\r\n########################################################################\r\n");
}

void call_mymemcopy()
{
	char in[20] = "hello there!";
	char out[20] = "";
		
	intro();
	TERM_WriteString("vorher: ");
	TERM_WriteString(in);
	TERM_WriteString("\r\n");
	mymemcopy(out, in, 5);
	TERM_WriteString("nachher: ");
	TERM_WriteString(out);
	TERM_WriteString("\r\n");
	outro();
	
	//intro();
	//asm
	//{
	//	/********************************************
	//	 * call mymemcopy()							*
	//	 ********************************************/
	//	MOVE.L #7,-(SP)
	//	MOVE.L in,-(SP)
	//	MOVE.L out,-(SP)
		
	//	JSR mymemcopy
		
	//	clean up here!!
	//}
	//outro();
}

void* mymemcopy(void* destination, const void* source, size_t size)
{		
	asm
	{ 
		/********************************************
		 * prepare environment						*
		 ********************************************/
		NAKED					// this is so the compiler is not performing link; oder asm void*

		LINK 	A6,#0			// save FP/A6
		ADDA.L 	#-12,SP			// prepare to save reg onto stack
		MOVEM.L D2/A2-A3,(SP)	// save regs on stack
		
		/********************************************
		 * access function parameters				*
		 ********************************************/
		MOVE.L  16(A6),D2		// copy param size in D2
		MOVE.L  12(a6),A2		// copy param source in A2
		MOVE.L  8(A6),A3		// copy param destination in A3
		
		/********************************************
		 * functionality: copy contents of source 	*
		 * to destination, with the length of size	*
		 ********************************************/
		Loop:
			MOVE.B  (A2)+,(A3)+		// copy contents of A2 to A3
			SUBI.L  #1,D2			// decrement size(D2) of source
			TST.B   D2				// asserts size(D2) equals 0
		BNE     Loop			// if not continue copying 
		
		/********************************************
		 * copy destination to return register A0	*
		 ********************************************/
		MOVE.L  8(A6),A0
		
		/********************************************
		 * recover saved registers from stack		*
		 ********************************************/
		MOVEM.L (SP),D2/A2-A3	
		ADDA.L 	#12,SP			// free unused memory on stack
		UNLK 	A6				// unlink 

		RTS						//return from subroutine
	}		
}
	
void outro()
{
	TERM_WriteString("\r\n########################################################################\r\n\r\n");
}
