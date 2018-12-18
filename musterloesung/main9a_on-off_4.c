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
#include "support_common.h"  // Deklarationen für die Peripherie 
#include "uart_support.h"    // Serielle Schnittstelle
#include "terminal_wrapper.h"



  // - Bitte darauf achten, dass am Coldfire-Serial Port ein  
  //   Terminal (Putty o.ä.) mit 19200kBaud angeschlossen ist.
  // - Als Target muss   <projektname>_RAM_OSBDM   ausgewählt werden.




  // In der Praxis werden die folgenden Defines vom Chip-Hersteller mit der
  // Entwicklungsumgebung zur Verfügung gestellt. Siehe Datei MCF52259_GPIO.h
  // Nur aus didaktischen Gründen sollten Sie die Definitionen selbst machen.
  // Hier in der Musterlösung entsprechend:


  /* Definitionen für MCF_GPIO Port NQ */
  #define MNP_GPIO_PORTNQ        0x40100008
  #define MNP_GPIO_DDRNQ         0x40100020
  #define MNP_GPIO_PINDATA_SETNQ 0x40100038
  #define MNP_GPIO_CLRNQ         0x40100050
  #define MNP_GPIO_PNQPAR        0x40100068
  #define MNP_GPIO_PORTNQ_NQ1    0x02
  #define MNP_GPIO_PORTNQ_NQ5    0x20


  /* Definitionen für MCF_GPIO Port TC */
  #define MNP_GPIO_PORTTC        0x4010000F
  #define MNP_GPIO_DDRTC         0x40100027
  #define MNP_GPIO_SETTC         0x4010003F
  #define MNP_GPIO_CLRTC         0x40100057
  #define MNP_GPIO_PTCPAR        0x4010006F
  #define MNP_GPIO_PORTTC_TC0    0x1
  #define MNP_GPIO_PORTTC_TC1    0x2
  #define MNP_GPIO_PORTTC_TC2    0x4
  #define MNP_GPIO_PORTTC_TC3    0x8





  int main(void)
  {
  	int counter = 0;
  	
    /***** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
    PE_low_level_init(); /********************************************************/
    /***** End of Processor Expert internal initialization. **********************/


  asm 
  {
  	/* MCF52259RM.pdf
  	- SW1 and SW2 verbunden mit PNQPAR5 and PNQPAR1 (Quad function pins!!)
  	- LED's 1-4 verbunden mit DDRTC0-DDRTC3
  	*/
  	
     /* Taster als digitale Eingabe konfigurieren  ============================= */
     /* MCF52259RM.pdf
     - Pin Assignment auf GPIO function 
       (15.6.5.3 Port NQ Pin Assignment Register (PNQPAR))
     - Port Data Direction Löschen für input function 
       (15.6.2 Port Data Direction Registers (DDRn))
     - Output Data Register löschen 
       (15.6.1 Port Output Data Registers (PORTn))
     */

  	// andi.w #0xF0F0, MNP_GPIO_PNQPAR  geht nicht, deshalb folgender Code
  	move.w   MNP_GPIO_PNQPAR,d0 //NQ5 and NQ1 löschen für GPIO Funktion
  	and.l    #0xF0F0, d0
  	move.w   d0, MNP_GPIO_PNQPAR

  	
  	// andi.b #0xDD, MNP_GPIO_DDRNQ  geht nicht, deshalb folgender Code
  	move.b   MNP_GPIO_DDRNQ, d0 //NQ5 and NQ1 löschen für input Funktion
  	andi.l   #0xDD,d0
  	move.b   d0, MNP_GPIO_DDRNQ
  	

  	// andi.b #0xDD, MNP_GPIO_CLRNQ  geht nicht, deshalb folgender Code
  	move.b   MNP_GPIO_CLRNQ,d0           //NQ5+NQ1 löschen
  	andi.l   #0xDD,d0	
  	move.b   d0, MNP_GPIO_CLRNQ



    /* LEDs als digitale Ausgabe konfigurieren ========================== */
  	/* MCF52259RM.pdf
  	- Pin Assignment auf GPIO Funktion setzen
  	  (15.6.5.1 Dual-Function Pin Assignment Registers)
   	- Port Data Direction auf output Funktion setzen 
  	  (15.6.2 Port Data Direction Registers (DDRn))
    - Output Data Register zurücksetzen 
      (15.6.1 Port Output Data Registers (PORTn))
  	*/
  	
     clr.b    MNP_GPIO_PTCPAR       //GPIO Funktion (=0)

  	 move.b   #0xf, d0              //output Funktion (=1)
  	 move.b   d0, MNP_GPIO_DDRTC
  	
     clr.b    MNP_GPIO_CLRTC        //LEDS OFF, siehe Figure 15-3

     
     loop:
 
     ////////////////////////// Taster 1 schaltet LED 1
     	clr.l    d0                         // Reset D0
  	    move.b   MNP_GPIO_PINDATA_SETNQ, d0 // Taster via PINDATA_SETNQ abfragen
     	andi.l   #MNP_GPIO_PORTNQ_NQ5, d0   // Check NQ5 auf 0 (SW1 gedrückt)
     	bne      LED1_OFF                   // falls nicht gedrückt: Sprung
  	
       	move.l   #MNP_GPIO_PORTTC_TC0,d1
     	move.b	 d1, MNP_GPIO_SETTC         // LED einschalten via set bit in GPIO_SET
     	bra      LED1_END
  	
     LED1_OFF:	
     	move.l   #~(MNP_GPIO_PORTTC_TC0),d1
     	move.b   d1, MNP_GPIO_CLRTC         // LED ausschalten via clear bit in GPIO_CLR

     LED1_END:

     // Nochmal dasselbe für Nr. 2:
     ////////////////////////// Taster 2 schaltet LED 2
     	clr.l    d0
     	move.b   MNP_GPIO_PINDATA_SETNQ, d0 // Taster via PINDATA_SETNQ abfragen
     	andi.l   #MNP_GPIO_PORTNQ_NQ1, d0   // Check NQ1 auf 0 (SW2 gedrückt)
     	bne      LED2_OFF
  	
     	move.l   #MNP_GPIO_PORTTC_TC1,d1
     	move.b   d1, MNP_GPIO_SETTC         // LED einschalten via set bit in GPIO_SET
     	bra      LED2_END
  	
     LED2_OFF:	
     	move.l   #~(MNP_GPIO_PORTTC_TC1),d1
     	move.b   d1, MNP_GPIO_CLRTC         // LED ausschalten via clear bit in GPIO_CLR

  	
     LED2_END:	
     	bra	    loop	

     }

  }
