//delay.h
void delay_ms(unsigned int ms)
{
unsigned char i;
for(;ms>0;ms--)
{
for(i=250;i>0;i--);
for(i=247;i>0;i--);
}
}