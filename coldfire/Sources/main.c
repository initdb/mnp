/* ###################################################################
**     Filename    : main.c
**     Project     : test8
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2014-10-11, 15:20, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/                  
/* MODULE main */ 
 
  #pragma compact_abi 
 

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

/************************************************************
 * includes für uebungen									*
 ************************************************************/
#include "string.h"
#include "hextoascii.h"
#include "subroutine.h"
#include "illegal.h"
#include "mymemcopy.h"
#include "trap.h"
#include "linkedList.h"
#include "ledbtn.h"

// - Bitte darauf achten, dass am Coldfire-Serial Port ein  
//   Terminal (Putty o.ä.) mit 19200kBaud angeschlossen ist.
// - Als Target muss   <projektname>_RAM_OSBDM   ausgewählt werden.



void main(void)
{
	int counter = 0;
	uint32_t zahl = 0xAFFE;  
	
	/***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! **/
	PE_low_level_init(); /*******************************************************/
	/***** End of Processor Expert internal initialization. *********************/
	
	/****************************************************************************
	 * execute functions here!													*
	 ****************************************************************************/
	//string();
	//string_revert();
	//hex_to_ascii();
	//subroutine();
	//illegal();
	//call_mymemcopy();
	//trap();
	//linked_list();
	btn_set_on_press();
	 
	// Als Ende-Behandlung nachfolgend ein einfacher Leerlauf-Prozess 
	// **************************************************************
	 
	for(;;)
	{
		counter++;
	} 
}  /* END main */

