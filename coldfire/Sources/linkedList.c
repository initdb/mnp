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

	    // Zahl einlesen (Ende vereinfachend mit Wert 0)
	    //----------------------------------------------
	 

	    // Einzuhngendes Element aufbauen
	    // -------------------------------
	    // Mit malloc; malloc erwartet den Parameter im Register D0,
		// weil dafr "register_abi" gilt (nicht compact_abi)


		//                  ___________ 
		//          a0 -->  |zahl|  0 | 
		//              
	             

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

		// Iterator-Prchen initialisieren
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
