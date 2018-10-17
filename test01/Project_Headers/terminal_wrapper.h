/*
 * header declaration file for terminal wrapper functions
 * needed to compile old examples from msp projects
 * M. Hayn 09/22: init version
 */

#pragma compact_abi

#ifndef __TERMINAL_WRAPPER__
#define __TERMINAL_WRAPPER__

#define ENABLE_UART_SUPPORT 1 

#include "support_common.h" /* include peripheral declarations and more */
#include "uart_support.h" 

void TERM_Write(const char ch);
char TERM_Read(void);
void TERM_WriteLn(void);
void TERM_WriteString(const char *string);
void TERM_ReadString(char *str, int maxLen);
void INOUT_WriteInt(const int num);
int INOUT_ReadInt(void);
char INOUT_TermChar(void);
void TERMIO_Init(void);


#endif
