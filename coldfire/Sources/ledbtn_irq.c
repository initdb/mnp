/*
 * ledbtn_irq.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Benedict
 */


/* ###################################################################
**     Filename    : main.c
**     Project     : test8
**     Processor   : MCF52259CAG80
**     Version     : Driver 01.00
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2014-10-11, 15:20, # CodeGen: 0
**     Abstract    :
**         Main module.
**         Uebung 9d (Schalter via Interrupt)
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




  // In der Praxis werden die folgenden Defines vom Chip-Hersteller mit der
  // Entwicklungsumgebung zur Verfügung gestellt. Siehe Datei MCF52259_GPIO.h
  // Nur aus didaktischen Gründen sollten Sie die Definitionen selbst machen.
  // Hier in der Musterlösung entsprechend:


  /* Definitionen für MCF_GPIO Port NQ */
  #define MNP_GPIO_PORTNQ      0x40100008
  #define MNP_GPIO_DDRNQ       0x40100020
  #define MNP_GPIO_SETNQ       0x40100038
  #define MNP_GPIO_CLRNQ       0x40100050
  #define MNP_GPIO_PNQPAR      0x40100068
  #define MNP_GPIO_PORTNQ_NQ1  0x02
  #define MNP_GPIO_PORTNQ_NQ5  0x20


  /* Definitionen für MCF_GPIO Port TC */
  #define MNP_GPIO_PORTTC      0x4010000F
  #define MNP_GPIO_DDRTC       0x40100027
  #define MNP_GPIO_SETTC       0x4010003F
  #define MNP_GPIO_CLRTC       0x40100057
  #define MNP_GPIO_PTCPAR      0x4010006F
  #define MNP_GPIO_PORTTC_TC0  0x1
  #define MNP_GPIO_PORTTC_TC1  0x2
  #define MNP_GPIO_PORTTC_TC2  0x4
  #define MNP_GPIO_PORTTC_TC3  0x8


  /* Definitionen für MCF_Edge Post */
  #define MNP_INTC0_IMRL       0x40000C0C  // Interrupt Mask Register 
  #define MNP_EPORT_EPPAR      0x40130000  // Edge control register
  #define MNP_EPORT_EPIER      0x40130003  // Edge Port Interrupt Enable Reg
  #define MNP_EPORT_EPFR       0x40130006  // Edge Port Flag Register 




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
            
        /* LEDs als digitale Ausgabe konfigurieren ==========================        bekannt         */
         /* MCF52259RM.pdf
         - Port Data Direction auf output Funktion setzen 
           (15.6.2 Port Data Direction Registers (DDRn))
         - Pin Assignment auf GPIO Funktion setzen
           (15.6.5.1 Dual-Function Pin Assignment Registers)
        - Output Data Register zurücksetzen 
          (15.6.1 Port Output Data Registers (PORTn))
         */
         
         clr.b    MNP_GPIO_PTCPAR        //GPIO Funktion (=0)
         move.b   #0xf, d0               //output Funktion (=1)
         move.b   d0, MNP_GPIO_DDRTC
         clr.b    MNP_GPIO_CLRTC        //LEDS OFF, siehe Figure 15-3
         /* LEDs als digitale Ausgabe konfigurieren ==========================       bekannt (Ende) */

         
         
        /* Taster als digitale Eingabe konfigurieren  ============================= */
        /* MCF52259RM.pdf
         - Pin Assignment auf IRQ function (primary function) 
           (15.6.5.3 Port NQ Pin Assignment Register (PNQPAR))
         - Port Data Direction Löschen für input function 
           (15.6.2 Port Data Direction Registers (DDRn))
         - Output Data Register löschen 
           (15.6.1 Port Output Data Registers (PORTn))
        */
         
        
      // Achtung: Andere Funktion für NQ1 und NQ5 (primary function (=IRQ), 01 statt 00)
         move.w   MNP_GPIO_PNQPAR,d0    // NQ5 und NQ1 auf IRQ Funktion (01)
         and.l #0xF0F0, d0
         or.l  #0x0404, d0
         move.w   d0, MNP_GPIO_PNQPAR
      
         move.b   MNP_GPIO_DDRNQ, d0   //NQ5 and NQ1 löschen für input Funktion
         andi.l   #0xDD,d0
         move.b   d0, MNP_GPIO_DDRNQ
         
         move.b   MNP_GPIO_CLRNQ,d0    //NQ5+NQ1 löschen
         andi.l   #0xDD,d0 
         move.b   d0, MNP_GPIO_CLRNQ

      // Einhängen der Unterbrechungsantwortprogramme (interrupt service routines)
      //   (IRQ5=sw1 / IRQ1=sw2) 
        lea     int_handler_IRQ1, a1
        ########Hier fehlt was         // IRQ1 Vector
        lea     int_handler_IRQ5, a1
         ########Hier fehlt was         // IRQ5 Vector 

         
      // Einstellen rising/falling edge detection, 
      // Einstellen auf falling edge active (MCF52259RM 17.4.1)
         ########Hier fehlt was         
      
      // Enable EPORT Interrupts (MCF52259RM 17.4.3)              // ENABLE
         move.b   MNP_EPORT_EPIER, d1
         or.l  #0x00000022, d1       // 0x20=IRQ5, 0x2=IRQ1 
         move.b   d1, MNP_EPORT_EPIER
      
      // enable IRQ1+5  (MCF52259RM 16.3.2)                       // ÄUSSERE MASKE
         move.l   MNP_INTC0_IMRL, d1
         and.l #(~0x00000022), d1    //  0x20=IRQ5, 0x2=IRQ1 
         move.l   d1, MNP_INTC0_IMRL
      
      // Interrupts im Statusregister freigeben (CFPRM 1.5.1)     // INNERE MASKE
         ########Hier fehlt was         


        
    loop:                       // Das ist unser Leerlaufprozess
      bra       loop  
      

    //////////////////////////////////////////////////////////////////////////////
    int_handler_IRQ5:      
        move.l   d0, -(sp)     // WICHTIG!  Alle benutzten Register retten
        move.l   d1, -(sp)
      
      LED1_ON:
      ########Hier fehlt was               // LED einschalten 

      // Interupt zurücksetzen (MCF52259 17.4.6)
      move.b   #0x20,d0                    // Schreiben von 1 löscht die Bits!
      move.b   d0, MNP_EPORT_EPFR
      
      move.l   (sp)+,d1      // WICHTIG!  Alle benutzten Register restaurieren
      move.l   (sp)+,d0  
      rte 
        
        
    //////////////////////////////////////////////////////////////////////////////    
    int_handler_IRQ1:      
        move.l   d0, -(sp)
        move.l   d1, -(sp)
        
      LED1_OFF:  
      ########Hier fehlt was         // LED ausschalten
         
      // Interupt zurücksetzen (MCF52259 17.4.6)
      move.b   #0x02,d0                    // Schreiben von 1 löscht die Bits! 
      move.b   d0, MNP_EPORT_EPFR
      
      move.l   (sp)+,d1
      move.l   (sp)+,d0  
      rte
    //////////////////////////////////////////////////////////////////////////////    


    }
  }
