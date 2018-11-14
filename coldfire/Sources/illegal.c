/*
 * illegal.c
 *
 *  Created on: Nov 14, 2018
 *      Author: Benedict
 */

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

#include "illegal.h"

#define MEMOFFSET 0x20000000

/****************************************************************
 * Uebung6: Illegal instruction, testen Sie den Befehl 			*
 * einschließlich Verbiegen des zugehörigen Vektors.			*
 ****************************************************************/
void illegal()
{
	char start[] = "Programm starting...\n\r";
	char exeption[] = "An exeption occoured, the ninja fly is annoyingly passing by!\n\r";
	char stop[] = "Programm stopping...\n\r";
	
	asm
	{
		BRA Start
		
		myExeptionHandler:
			// prints out exeption str on uart
			PEA exeption
			JSR TERM_WriteString
			ADDA #4,SP
			
			/********************************************
			 * handle exception here!!					*
			 ********************************************/
			
			// Return from Exeption
			RTE
		
		Start:
			// prints out start str on uart
			PEA start
			JSR TERM_WriteString
			ADDA #4,SP
			
			LEA myExeptionHandler,A1
			MOVE.L A1,MEMOFFSET+0x10
			
			ILLEGAL
			
			// prints out stop str on uart
			PEA stop
			JSR TERM_WriteString
			ADDA #4,SP
	}
}
