/*
 * trap.h
 *
 *  Created on: Nov 21, 2018
 *      Author: Benedict
 */

#ifndef TRAP_H_
#define TRAP_H_

#include <stdio.h>

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

void trap();

#endif /* TRAP_H_ */
