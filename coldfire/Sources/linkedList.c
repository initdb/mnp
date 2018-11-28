/*
 * linkedList.c
 *
 *  Created on: Nov 28, 2018
 *      Author: Benedict
 */

#include "linkedList.h"

char msginput[]  = "\r\nZahl eingeben (0 fuer Ende): "; 
char msgfehler[] = "\nFehler bei malloc() !\n";

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
			
			TST.L D0 //test longword D0 is Null
			BEQ ausgabe //if prior tst cmd 0 -> jump to ausgabe 
			
			MOVE.L D0,D7			
			// Einzufuegendes Element aufbauen
			// -------------------------------
			// Mit malloc; malloc erwartet den Parameter im Register D0,
			// weil dafuer "register_abi" gilt (nicht compact_abi)
			MOVE.L #6,D0
			JSR malloc
			MOVE.W D7,(A0)
	
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
	
			// Iterator-Praechen initialisieren
				LEA anker,A3
				MOVE.L (A3),A2
			naechstes:      
	
			// Einfgestelle gefunden: Objekt einhngen
			//-----------------------------------------                
			gefunden:

				
		bra schleife         // naechste Zahl
      
		// gesamte Liste ausgeben
		//-----------------------
		ausgabe: 

		ende:
	}
}
