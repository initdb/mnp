/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : UART0.h
**     Project     : test8
**     Processor   : MCF52259CAG80
**     Component   : Init_UART
**     Version     : Component 01.003, Driver 01.03, CPU db: 3.00.000
**     Compiler    : CodeWarrior MCF C Compiler
**     Date/Time   : 2014-10-11, 15:24, # CodeGen: 1
**     Abstract    :
**          This file implements the UART (UART0) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
**     Settings    :
**          Component name                                 : UART0
**          Device                                         : UART0
**          Settings                                       : 
**            Clock settings                               : 
**              Prescaler                                  : 130
**              Transmitter clock settings                 : 
**                Transmitter clock select                 : Internal bus clock
**                Transmitter baud rate                    : 19230.7692 baud
**              Receiver clock settings                    : 
**                Receiver clock select                    : Internal bus clock
**                Receiver baud rate                       : 19230.7692 baud
**            RTS control                                  : No control
**            CTS control                                  : No control
**            Receiver interrupt select                    : RXRDY
**            Error mode                                   : Character mode
**            Parity mode and type                         : No parity
**            Data width                                   : 8
**            Stop-bit length                              : 1.000 (6-8 bits); 1.500 (5 bits)
**            Channel mode                                 : Normal
**          Interrupts                                     : 
**            UART interrupt                               : 
**              Interrupt                                  : INT_UART0
**              Request                                    : Disabled
**              Level                                      : Disabled
**              Priority                                   : 0 (Lowest)
**              ISR name                                   : 
**              Change-of-state interrupt                  : Disabled
**              Delta break interrupt                      : Disabled
**              FIFO/Receiver interrupt                    : Disabled
**              Transmitter ready interrupt                : Disabled
**          Pins                                           : 
**            Receiver pin                                 : Enabled
**              Pin                                        : URXD0_PUA1
**              Pin signal                                 : 
**            Transmitter pin                              : Enabled
**              Pin                                        : UTXD0_PUA0
**              Pin signal                                 : 
**            CTS pin                                      : Disabled
**            RTS pin                                      : Disabled
**            DTIN pin                                     : Disabled
**          Initialization                                 : 
**            Enable transmitter                           : Enabled
**            Enable receiver                              : Enabled
**            Call Init method                             : yes
**     Contents    :
**         Init - void UART0_Init(void);
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file UART0.h
** @version 01.03
** @brief
**          This file implements the UART (UART0) module initialization
**          according to the Peripheral Initialization settings, and
**          defines interrupt service routines prototypes.
*/         
/*!
**  @addtogroup UART0_module UART0 module documentation
**  @{
*/         

#ifndef UART0_H_
#define UART0_H_

/* MODULE UART0. */

/* Including shared modules, which are used in the whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "Cpu.h"


void UART0_Init(void);
/*
** ===================================================================
**     Method      :  UART0_Init (component Init_UART)
**     Description :
**         This method initializes registers of the UART module
**         according to the Peripheral Initialization settings.
**         Call this method in user code to initialize the module. By
**         default, the method is called by PE automatically; see "Call
**         Init method" property of the component for more details.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/


/* END UART0. */
#endif /* #ifndef __UART0_H_ */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale MCF series of microcontrollers.
**
** ###################################################################
*/