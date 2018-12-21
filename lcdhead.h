//lcdhead.h
sfr lcd=0x80;
sbit RS=P3^4;
sbit RW=P3^5;
sbit EN=P3^6;
void lcd_data(unsigned char ch)
{
	lcd=ch;
	RS=1;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}
void lcd_command(unsigned char ch)
{
	lcd=ch;
	RS=0;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}
void lcd_init()
{
	lcd_command(0x1);
	lcd_command(0x2);
	lcd_command(0x6);
	lcd_command(0xE);
	lcd_command(0x38);
}
void lcd_string(const char *s)
{
	while(*s)
	{
		lcd_data(*s);
	s++;
	}
}
/*void lcd_int(unsigned int n)
{
	unsigned int num;
	char count=0,i;
	char arr[10];
	num=n;
	
	while(num)
	{
		count++;
		num=num/10;
	}	
	
	for(i=0;i<count;i++)
	{
	arr[i]=n%10+48;
	n=n/10;
}
	lcd_string(arr);
	}*/
	