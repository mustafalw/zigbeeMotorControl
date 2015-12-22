/* @section  I N C L U D E S */
#include "at89c5131.h"

void init_uart();
void delay_ms(int);

void main(void)
{
	init_uart();            // initial configuration of UART
	while(1)
	{		
		SBUF = P1;          // copy the value of port P1 in SBUF so as to start transmitting using UART
		while(!TI);         // empty while loop until TI becomes 1 i.e. transmission has completed
		TI  = 0;            // make TI zero for next transmission
		delay_ms(100);      // a delay of 100 ms buffer so that Rx side does not overflow
	}
}

void init_uart()
{
	TMOD = 0x20;            // timer 1 in mode 2
	TH1	 = 0xF3;            // timer 1 overflows in 12 clock cycles
	SCON = 0x50;            // SM0 = 0, SM1 = 1 i.e. 1 start bit, 1 stop bit and 8 data bits, REN = 1 i.e. enable Rx
	TR1  = 1;               // start timer 1
}

/**
 * FUNCTION_PURPOSE: A delay of around 1000us for a 24MHz crystel
 * FUNCTION_INPUTS: void
 * FUNCTION_OUTPUTS: none
 */
void delay_ms(int delay)
{
	int d=0;
	while(delay>0)
	{
		for(d=0;d<382;d++);
		delay--;
	}
}
