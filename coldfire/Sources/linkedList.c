/*
 * linkedList.c
 *
 *  Created on: Nov 28, 2018
 *      Author: Benedict
 */

#include "linkedList.h"

char msginput[]  = "\r\nZahl eingeben (0 fuer Ende): "; 
char msgerror[] = "\nFehler bei malloc() !\n";
char msgout[] = "\r\nSortierte Liste:\r\n";
char msgdelimiter[] = "->";
char msgend[] = "ende.\r\n";

void *anker = NULL;

void linked_list()
{
	int counter = 0;

	asm
	{
		schleife:  
			// clear D0 reg of artefacts
			CLR.L D0
			
			// print out msginput str
			PEA msginput
			JSR TERM_WriteString
			ADDA.L #4,SP
			
			// Zahl einlesen (Ende vereinfachend mit Wert 0)
			//----------------------------------------------
			// Read integer from Terminal
			JSR INOUT_ReadInt
			
			TST.W D0 //test longword D0 is Null
			BEQ ausgabe //if prior tst cmd 0 -> jump to ausgabe 
			
			MOVE.L D0,D7			
			// Einzufuegendes Element aufbauen
			// -------------------------------
			// Mit malloc; malloc erwartet den Parameter im Register D0,
			// weil dafuer "register_abi" gilt (nicht compact_abi)
			MOVE.L #6,D0
			JSR malloc
			MOVE.W D7,(A0)
	
			TST.L A0        // a0 enthaelt Zeiger auf neues Objekt
			BEQ	fehler
			
			CLR.L 2(A0)		// Bereinigen der letzten 4Byte des neuen Elements
			//         +----+----+ 
			// a0 -->  |zahl|  0 | 
			//         +----+----+
					 
	
			// Organisation der Listeniteration
			//
			// a2 zeigt auf das aktuelle Element (oder 0  Listenende)
			// a3 zeigt   a u f   d e n   Z e i g e r   im vorhergehenden Element
			//
			//                              a3         a2 
			//                                \         \
			//  anker:                         \         \
			//  ______     ___________     _____V_____    V___________     ___________
			//  |    | --> |zahl|next| --> |zahl|next| --> |zahl|next| --> |zahl|  0 |
			//  
			//
			//    Funtioniert 
			//       + auch am Listenende (a3 zeigt auf 0, a2 ist 0)
			//       + auch bei Einfgen vor dem ersten Element 
			//                           (a3 zeigt auf Anker, a2 auf das erste Element
			//       + auch bei leerer Liste (a3 zeigt auf Anker, Anker und a2 sind 0)
	
			// suchen der Einfgestelle
			//-------------------------
	
			// Iterator-Paerchen initialisieren
			LEA anker,A3
			MOVE.L (A3),A2
			//LEA anker,A3
			naechstes:      
				// finden der einfuege Stelle
				// Fall 1: Element nicht in Liste
				TST.L A2		// test ob A2 = NULL
				BEQ gefunden	// falls ja Ende der Listes
				
				// Fall 2: Element vergleichen
				MOVE.W (A2),D0
				EXT.L D0		// !! EXT: sign extend
				EXT.L D7		// !!
				CMP.L D0,D7		// compare nur mit .L (32 bit) words
				BLE gefunden
				
				// weiterschalten des Iterator-Paerchen
				LEA 2(A2),A3
				MOVE.L (A3),A2
			BRA naechstes
			// Einfuegestelle gefunden: Objekt einhaengen
			//-----------------------------------------                
			gefunden:
				MOVE.L A0,(A3)
				MOVE.L A2,2(A0)

		bra schleife         // naechste Zahl
      
		// gesamte Liste ausgeben
		//-----------------------
		ausgabe:
			// print out msgout str
			PEA msgout
			JSR TERM_WriteString
			ADDA.L #4,SP
			
			// printout each element of the list
			LEA anker,A2
			outputloop:
				TST.L A2		// test ob A2 = NULL
				BEQ ende		// falls ja Ende der Listes
				// printout
				MOVE.W (A2),-(SP)
				JSR INOUT_WriteInt
				ADDA.L #2,SP
				
				PEA msgdelimiter
				JSR TERM_WriteString
				ADDA.L #4,SP
				// set iterator to next one
				MOVE.L 2(A2),A2
			BRA outputloop
		
		fehler:	//Fehler behandlung eigentlich nur Ausgabe
			PEA	msgerror 
			jsr	TERM_WriteString	
			adda #4, SP
		bra ende
			
		ende:
			PEA	msgend
			jsr	TERM_WriteString	
			adda #4, SP
	}
}
