//uart.h
void uart_init()
{
	SCON=0x50;
	TMOD=0x21;//initialize timer 0 on mode 1 and timer 1 in mode 2
	TH1=TL1=253;
	TR1=1;
}
void uart_tx(unsigned char ch)
{
	SBUF=ch;
	while(TI==0);
	TI=0;
	
}
unsigned char uart_rx()
{
	while(RI==0);
	RI=0;
	return SBUF;
	
}
void uart_string(char *s)
{
	while(*s)
	{
	uart_tx(*s);
	s++;
}
}




