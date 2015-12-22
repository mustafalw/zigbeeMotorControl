/* @section  I N C L U D E S */
#include "at89c5131.h"

// map each pin of port 0 with an sbit variable
sbit C1 = P0^0;
sbit C2 = P0^1;
sbit C3 = P0^2;
sbit C4 = P0^3;
sbit O1 = P1^5;
sbit O2 = P1^6;
sbit O3 = P1^4;
sbit O4 = P1^7;

void init_uart()
{
	TMOD = 0x20;            // timer 1 in mode 2
	TH1	 = 0xF3;            // timer 1 overflows in 12 clock cycles
	SCON = 0x50;            // SM0 = 0, SM1 = 1 i.e. 1 start bit, 1 stop bit and 8 data bits, REN = 1 i.e. enable Rx
	TR1  = 1;               // start timer 1
}
	
void main(void){
	init_uart();            // initial configuration of UART
    while(1)
	{ 
	    RI=0;
		while(!RI);
		P1=SBUF<<4;         // store Rx data in P1		
		if(P1==0xF0)        // move forward
		{C1=1;
		 C2=0;
		 C3=1;
		 C4=0;}
		
		else if(P1==0x60)   // move backward
		{C1=0;
		 C2=1;
		 C3=0;
		 C4=1;}
		
		else if(O1==0&&O2==0)   // stop
		{C1=0;
		C2=0;
		C3=0;
		C4=0;}
		
		else if(O3==1&&O1==1)   // turn right
		{C1=1;
		C2=0;
		C3=0;
		C4=1;}
		
		else if(O2==1&&O4==1)   // turn left
		{C1=0;
		C2=1;
		C3=1;
		C4=0;}
		else{}
	}	
}
