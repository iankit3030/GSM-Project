//i2c_device.h
void i2c_device_write(unsigned char sa,unsigned char mr,unsigned char _data)
{
	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(mr);
	i2c_ack();
	i2c_write(_data);
	i2c_ack();
	i2c_stop();
	delay_ms(10);
}
unsigned char i2c_device_read(unsigned char sa,unsigned char mr)
{
	unsigned char temp;
	i2c_start();
	i2c_write(sa);
	i2c_ack();
	i2c_write(mr);
	i2c_ack();
	i2c_start();
	i2c_write(sa|1);
	i2c_ack();
	temp=i2c_read();
	i2c_noack();
	i2c_stop();
	return temp;
}
void i2c_int_store(unsigned char *arr)
{
	unsigned char i=0;
	while(arr[i])
	{
	i2c_device_write(0xA0,0x4+i,arr[i]);
	i++;
	}
}
void i2c_int_read(unsigned char *arr)
{
	unsigned char i=0;
while(i<4)
{
	arr[i]=i2c_device_read(0xA0,0x4+i);
	i++;
}
arr[4]='\0';
}



