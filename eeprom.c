//main_project
#include<reg51.h>
#include"delay.h"
#include"lcdhead.h"
#include"i2c.h"
#include"i2c_device.h"
#include"keypad.h"
#include"uart.h"
#define MAX 9999
#define MIN 1001
sbit SW=P3^2;
bit flag=0;
static int temp,temp1,temp2;
unsigned char arr[5],arr1[5];
static long int x=123456789,y=234567891,z=345678912,w=456789123,c=0,j=0;
void gsm(char *arr)
{
uart_string("AT\r\n");
delay_ms(1000);
uart_string("AT+CMGS=\"9664011491\"\r\n");
	delay_ms(1000);
uart_string(arr);
	delay_ms(1000);
	uart_tx(0x1A);
	delay_ms(8000);
}
void OTP_gen(void)
{
	char i;
	for(i=0;i<4;i++)
	{
		arr[i]=temp1%10+48;
		temp1=temp1/10;
	}
	arr[4]='\0';
	i2c_int_store(arr);
}
void OTP_scan(void)
{	
	char i;
	for(i=0;i<4&&flag==0;i++)
{
	arr1[i]=keyscan();
	lcd_data('*');
	}
arr1[i]='\0';
}
void OTP_compare(void)
{
	char i;
	lcd_command(0x1);
	i2c_int_read(arr);
	 for(i=0;i<4&&(arr[i]==arr1[i]);i++);
	if(arr[i]==arr1[i])
		lcd_string("SYSTEM ACCESSED");
	else
		lcd_string("WRONG ENTRY");
	delay_ms(3000);
	lcd_command(0x1);
}
void set_time(void)
{
	i2c_device_write(0xD0,0x0,0x45);//seconds
	i2c_device_write(0xD0,0x1,0x28);//minutes
	i2c_device_write(0xD0,0x2,0x17);//hour
}
void display_time(void)
{
	lcd_command(0x80);
	//displaying hours
	temp2=i2c_device_read(0xD0,0x2);
	lcd_data(temp2/16+48);
	lcd_data(temp2%16+48);
	lcd_data(':');
	//displaying minutes
	temp2=i2c_device_read(0xD0,0x1);
	lcd_data(temp2/16+48);
	lcd_data(temp2%16+48);
	lcd_data(':');
	//displaying seconds
	temp2=i2c_device_read(0xD0,0x0);
	lcd_data(temp2/16+48);
	lcd_data(temp2%16+48);
}
long unsigned int myrand()
{
long int t;
	temp=i2c_device_read(0xD0,0x0);
		temp=(temp/16)+((temp%16)*10);
y^=(y<<5);y^=(y>>7);y^=(y<<22);
t=z+w+c;
z=w;
c=t<0;
w=t&2147483647;
	x+=1411392427;
	return x+y+w+temp;
}
void EINT0_HANDLER(void)interrupt 0
{
	temp1=(myrand()%(MAX+1-MIN))+MIN;
} 
void timer0_handler(void)interrupt 1
{
	TR0=0;//stop timer 0
	j++;
	if(j==20000)
	{
		flag=1;
		lcd_command(0x1);
		lcd_string("OTP EXPIRED");
		delay_ms(3000);
		lcd_command(0x1);
		lcd_string("PRESS ANY KEY");
		j=0;
	}
	TH0=0xFC;
	TL0=0x18;//init to 1ms
	TR0=1;//start timer 0
}
main()
{	
	uart_init();
	lcd_init();
	lcd_command(0xc);
	set_time();
	EA=EX0=1;//EINT0 is enabled
	IT0=1;//EINT0 is level triggered
	while(1)
	{
		if(temp1!=0)
		{
			//initializing timer interrupt
			TH0=0xFC;
			TL0=0x18;//init to 1ms
			EA=ET0=1;
			while(1)
			{
				TR0=1;//start timer 0
				lcd_command(0x1);
				lcd_string("Enter OTP");
				OTP_gen();
i2c_int_read(arr);
				
				uart_string("your OTP is: ");
				uart_string(arr);
				uart_string("\r\n");
lcd_command(0xC0);
	if(flag==0)
		OTP_scan();
	else
		lcd_data(0x1);
	if(flag==0)
		OTP_compare();
	break;
}
}
TR0=0;
temp1=0;
flag=0;
j=0;
display_time();//displaying time
lcd_string("          ");
lcd_command(0xC0);
lcd_string("Press SW for OTP");
}
}