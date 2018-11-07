/*
 * subroutine.c
 *
 *  Created on: Nov 7, 2018
 *      Author: Benedict
 */

/************************************
 * subroutine.c						*
 *									*
 *  Created on: Nov 07, 2018		*
 *      Author: Caroline, Benedict	*
 ************************************/


#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

#include "subroutine.h"

/****************************************************************
 * Uebung4: Ausgeben eines Speicherwortes als Hexadezimalwert.	*
 * als Unterprogramm von Uebung 3 gemäß Aufrufkonventionen		*
 * unseres Compilers und Aufruf des Unterprogramms aus Assembler*
 ****************************************************************/
void subroutine()
{
	uint32_t zahl = 0xAFFE;
	
	asm
	{		
		BRA Start
		
		/******************************************************************************
		 * subroutine / function hextoascii()										  *
		 ******************************************************************************/
		UP_hextoascii:
			/********************************************************
			 * in subroutine										*
			 ********************************************************/
			// create frame pointer and save to A6
			LINK A6,#-4
			// save registers, not needed here?
			// SUBA.L #24,SP
			// MOVEM.L ...,(SP)
			
			/********************************************************
			 * !!! old exercise	!!!!								*
			 ********************************************************/
			//Don'r use D2 its easily broken pls use D4
			MOVE.L #12,D4 //4*4 Bit - 4 Bit = "12"
			loop: //start of "loop"
				/********************************************************
				 * !!! new !!! 											*
				 ********************************************************/
				MOVE.W 10(A6),D1 //move func parameter 1 to "D1"
				
				/********************************************************
				 * ASR or Logical Shift Right D4 to D1					*
				 * We use  LSR (1-8) instead of LSRI since its below 8	*
				 ********************************************************/
				LSR.L D4,D1
				// mask with immediate data
				ANDI.L #15,D1
				// get ascii char
				//Bedingungen für Jumps
				//if(x <=9)
				CMPI #9,D1 //D1-9 aka 0-9
					BLE null_bis_neun //D1-9 <= 0; Jump to "null_bis_neun"
				//else if(x > 9)
				CMPI #9,D1 //D1-9
					BGT A_bis_F //D1-9 > 0; Jump to A_bis_F
				  
				continue_loop:
				// print as char
				MOVE.B D1,-(SP)	//false-> writes content of "D1" to Stack
				JSR TERM_Write	//call function "TERM_Write"
				ADDA.L #1,SP		//clean Stack
				// check if D2 == 0 if true "end_loop"
				TST.L D4
					BEQ end_loop
				// decrement shift register
				SUBQ.L #4,D4
			BRA loop //Branch: Jumps back to "loop:"  
			  
				null_bis_neun: //If "D1" smaller equals 0, ADD immediate Data 48 to "D1"
					ADDI.L #48,D1
				BRA continue_loop
				
				A_bis_F: //If "D1" greater than 0, Add immediate Data 55 to "D1"
					ADDI.L #55,D1
				BRA continue_loop //Branch jumps to "continue_loop"
				  
			end_loop: //If shift register == 0 -> "end_loop"
			/********************************************************
			 * !!! end old exercise	!!!!							*
			 ********************************************************/
			/* recover saved registers */
			// MOVEM.L (SP),...
			// ADDA.L #24,SP
			UNLK A6
		RTS
		/******************************************************************************
		 * main()																	  *
		 ******************************************************************************/
		Start:
			/* prepare before calling subroutine */
			// write last to first function parameter to stack 
			MOVE.L zahl,-(SP)
			/* call subroutine */
			JSR UP_hextoascii
			/* clean up parameter */
			ADDA.L #2,SP
	}
}



