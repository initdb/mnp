/*
 * function definition file for terminal wrapper functions
 * needed to compile old examples from msp projects
 * M. Hayn 09/22: init version
 */

#include "terminal_wrapper.h" 

static int	__2209sdfjkl_init=1;

static void init_terminal(void)
{
	InitializeUART(kBaud19200);
	__2209sdfjkl_init=0;
}
void TERM_Write(const char ch)
{
	if (__2209sdfjkl_init) {init_terminal();};
	uart_putchar(0, ch);
}

char TERM_Read(void)
{
	if (__2209sdfjkl_init) {init_terminal();};
	return(uart_getchar (0));
}

void TERM_WriteLn(void)
{
	if (__2209sdfjkl_init) {init_terminal();};
	TERM_Write('\r');
	TERM_Write('\n');
}
void TERM_WriteString(const char *string)
{
	if (__2209sdfjkl_init) {init_terminal();};
	while(*string) { TERM_Write(*string); string++;};
}
void INOUT_WriteInt(const int numIn)
{
	char digit;
	int num;
	
	num=numIn;
	
	if (__2209sdfjkl_init) {init_terminal();};
	
	if (num < 0) {TERM_Write('-'); num=-num;};
	if (num > 9999) {digit=(char)(num/10000); TERM_Write(digit+'0');};
	if (num > 999)  {digit=(char)((num%10000)/1000); TERM_Write(digit+'0');};
	if (num > 99)   {digit=(char)((num%1000)/100); TERM_Write(digit+'0');};
	if (num > 9) 	{digit=(char)((num%100)/10); TERM_Write(digit+'0');};
	digit=(char)(num%10); TERM_Write(digit+'0');
}


void TERM_ReadString(char *str, int maxLen) {
  /* reads a string int buffer 'str' with maxLen */
  unsigned char ch = TERM_Read();
  int len = 0;
  
//  while (ch >= ' ' || ch == BS || ch == DEL) {
// quick and dirty fix für BS und DEL von TT am 8.11.2009
  while (ch >= ' ' || ch == 8 || ch == 127) {
    if (ch >= ' ') {
      if ( len < maxLen-1) {
        str[len++] = ch; TERM_Write(ch);
      }
    } else if (len > 0) {
      TERM_Write(ch); len--;
    }
    ch = TERM_Read();
  }
  str[len] = 0;
}


int INOUT_ReadInt(void) { // Version HiCross
  /* reads an integer value from the terminal */
  int neg = 0;
  int val = 0;
  char termCh;
 
  termCh = (int)TERM_Read();
  if (termCh == '-') {
    neg = 1; TERM_Write(termCh); termCh = (int)TERM_Read();
  }
  while (termCh >= '0' && termCh <= '9') {
    TERM_Write(termCh);
    val = 10*val + termCh - (int)'0';
    termCh = (int)TERM_Read();
  }
  if (neg==1) val = -val;
  return val;
}


/* alte Version auskommentiert, TT 8.11.2009
int INOUT_ReadInt(void)
{
	int num=0; char input='\0';int posNeg=1;
	
	if (__2209sdfjkl_init) {init_terminal();};
	
	do{
		input=TERM_Read();
		switch(input) {
			case '-': posNeg=-1; break;
			case '0':
			case '1': 
			case '2':
			case '3': 
			case '4':
			case '5': 
			case '6':
			case '7': 
			case '8':
			case '9': 
				num=num*10+(int)(input-'0');
				break;
			default: break;
		};
	}while((input != '\r') && (input != ' '));
	return(posNeg*num);
}

*/



char INOUT_TermChar(void)
{
	if (__2209sdfjkl_init) {init_terminal();};
	return (TERM_Read());
}
void TERMIO_Init(void) 
{
	if (__2209sdfjkl_init) {init_terminal();};	
}
