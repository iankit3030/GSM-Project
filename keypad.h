//keypad.h
sbit R0=P1^4;
sbit R1=P1^5;
sbit R2=P1^6;
sbit R3=P1^7;
sbit C0=P1^0;
sbit C1=P1^1;
sbit C2=P1^2;
code unsigned char keypad_look_tbl[4][3]={'1','2','3','4','5','6','7','8','9','*','0','#'};
bit colscan()
{
	return (C0&C1&C2);
}
unsigned char keyscan()
{
	unsigned char row,col;
	R0=R1=R2=R3=0;
	C0=C1=C2=1;
	while(colscan()==1);
	delay_ms(20);
	//check R0
	R0=0;
	R1=1;
	R2=1;
	R3=1;
	if(colscan()==0)
	{
	row=0;
	goto colcheck;
	}
	//check R1
	R0=1;
	R1=0;
	R2=1;
	R3=1;
	if(colscan()==0)
	{
		row=1;
	goto colcheck;
	}
	//check R2
	R0=1;
	R1=1;
	R2=0;
	R3=1;
	if(colscan()==0)
	{
		row=2;
		goto colcheck;
	}
	//check R3
	R0=1;
	R1=1;
	R2=1;
	R3=0;
	if(colscan()==0)
	{
		row=3;
		goto colcheck;
	}
	colcheck:
	if(C0==0)
		col=0;
	if(C1==0)
	col=1;
	if(C2==0)
	col=2;

	while(colscan()==0);
	return keypad_look_tbl[row][col];
}
	
	
	