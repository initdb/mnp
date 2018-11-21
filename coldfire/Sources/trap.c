/*
 * trap.c
 *
 *  Created on: Nov 21, 2018
 *      Author: Benedict
 */

#include "trap.h"

#define MEMOFFSET 0x20000000
/****************************************************************
 * Uebung7: Trap-Befehl											*
 * 			Simulieren einen "Betriebsystemaufruf" mit dem Trap-*
 * 			Befehl; verwenden Sie eine einfache Stringausgabe	*
 * 			als Ersatz für die Betriebsystemfunktion; 			*
 * 			übergeben SIe die Stringadresse als Parameter an das*
 * 			Betriebsystem										*
 ****************************************************************/

void trap()
{
	char start[] = "Programm starting...\n\r";
	char svc[] = "A svc occoured\n\r";
	char stop[] = "Programm stopping...\n\r";
	 
	int userstack[20];
	
	// initialize stack
	int i;
	for(i = 0; i < sizeof(userstack); i++)
	{
		userstack[i] = 0xAFFE;
	}
	
	asm
	{
		BRA Start
		
		Betriebssystem:
			// prints out svc str on uart
			PEA svc
			JSR TERM_WriteString
			ADDA #4,SP
					
			// Return from Exeption
		RTE
			
		Start:
			// prints out start str on uart
			PEA start
			JSR TERM_WriteString
			ADDA #4,SP
			
			/********************************************
			 * main functionality						*
			 ********************************************/
			// prepare user stack
			LEA userstack,A2
			ADDA.L #20,A2
			// !! here no .W or .L etc
			// !! will not work otherwise
			MOVE A2,USP
			
			LEA Betriebssystem,A1
			MOVE.L A1,MEMOFFSET+0x80
			
			/********************************************
			 * switch to user mode						*
			 ********************************************/
			MOVE.W SR,D1
			AND.L 0xDFFF,D1
			MOVE.W D1,SR
			
			// call supervisor call
			TRAP #0
			
			/********************************************/
			// prints out start str on uart
			PEA stop
			JSR TERM_WriteString
			ADDA #4,SP
			
		RTS
	}
}

