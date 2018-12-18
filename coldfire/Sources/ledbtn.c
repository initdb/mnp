/*
 * ledbtn.c
 *
 *  Created on: Dec 12, 2018
 *      Author: Benedict
 */

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

#include "ledbtn.h"

/********************************************
 * register addresses						*
 ********************************************/
#define MEMMAP_OFF	0x40000000
// port pin assignment registers
#define PNQPAR		(MEMMAP_OFF + 0x100068)
#define PTCPAR		(MEMMAP_OFF + 0x10006f)
// port data direction registers
#define DDRNQ		(MEMMAP_OFF + 0x100020)
#define DDRTC		(MEMMAP_OFF + 0x100027)
// port pin data/ set data registers
#define PORTNQ		(MEMMAP_OFF + 0x100038)
#define SETTC		(MEMMAP_OFF + 0x10003f)
// port clear output data
#define CLRTC		(MEMMAP_OFF + 0x100057)

void btn_set_on_press()
{
	asm 
	{
		/* MCF52259RM.pdf
	  	- SW1 and SW2 are connected to PNQPAR5 and PNQPAR1 (Quad function pins!!)
	  	- LED's 1-4 are connected to DDRTC0-DDRTC3
	  	*/
	  	
	    /* Enable Switches to be pollable ====================================== */
	    /* MCF52259RM.pdf
	     - Pin Assignment must be set to GPIO function 
	       (15.6.5.3 Port NQ Pin Assignment Register (PNQPAR))
	     - Port Data Direction must be cleared for input function 
	       (15.6.2 Port Data Direction Registers (DDRn))
	     - Output Data Register must be cleared 
	       (15.6.1 Port Output Data Registers (PORTn))
	    */
		CLR.L D0
		MOVE.W PNQPAR,D0
		ANDI.L #0xf0f0,D0
		MOVE.W D0,PNQPAR
		
		CLR.L D0
		MOVE.B D0,PTCPAR
		
	    /* Enable LEDs as digital outputs ==================================== */
	  	/* MCF52259RM.pdf
	  	- Port Data Direction must be set for output function 
	  	  (15.6.2 Port Data Direction Registers (DDRn))
	  	- Pin Assignment must be set to GPIO function 
	  	  (15.6.5.1 Dual-Function Pin Assignment Registers)
	     - Output Data Register must be set/reset 
	       (15.6.1 Port Output Data Registers (PORTn))
	  	*/
		CLR.L D0
		MOVE.B DDRNQ,D0
		ANDI.L #0xdd,D0
		MOVE.B D0,DDRNQ
	  	
		CLR.L D0
		MOVE.B DDRTC,D0
		ORI.L #0xf,D0
		MOVE.B D0,DDRTC


	    loop:
			// read current btn value
			CLR.L D0
	    	MOVE.B PORTNQ,D0
			ANDI.L #0x20,D0
			//LSR.L #5,D0
			
			MOVE.L #0x20,D1
			CMP.L D0,D1
			BEQ setled
			// set LEDs to high
			MOVE.B #0x0f,D2
			MOVE.B D2,SETTC
	    bra loop
	    
	    setled:
	    	// set LEDs to low
	    	MOVE.L #0x00,D2
	    	MOVE.B D2,CLRTC
	    bra loop
	}
}
