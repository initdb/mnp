/*
 * mymemcopy.h
 *
 *  Created on: Nov 18, 2018
 *      Author: Benedict
 */

#ifndef MYMEMCOPY_H_
#define MYMEMCOPY_H_

#include <stdio.h>

#include "UART0.h"
#include "support_common.h"  // include peripheral declarations and more; 
#include "uart_support.h"    // universal asynchronous receiver transmitter,
                             // (d.h. die serielle Schnittstelle)
#include "terminal_wrapper.h"

void intro();
void* mymemcopy(void* destination, const void* source, size_t size);
void outro();

#endif /* MYMEMCOPY_H_ */
