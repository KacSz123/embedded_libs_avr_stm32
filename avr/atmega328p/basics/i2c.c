// avr libs
#include <avr/io.h>		// Contains all the I/O Register Macros
#include <util/delay.h> // Generates a Blocking Delay
#include <string.h>
#include <stdio.h>
#include <math.h>

//my headers
#include "i2c.h"

#ifdef F_CPU
#define F_CPU 16000000UL  
#endif
void I2C_init()
{
	TWBR=4;
	TWSR=(1<<TWPS1)|(1<<TWPS0); //prescaler 64
}


void I2C_start()
{
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);  // signal 'start'
	while(!(TWCR&(1<<TWINT))); // waiting for TWINT flag
}

void I2C_stop()
{
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);   
}


void I2C_writeByte(uint8_t data)
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));// waiting for TWINT flag
}

uint8_t I2C_readByte(uint8_t ack)
{
	if(ack)
	{
		TWCR=(1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	}
	else
	{
		TWCR=(1<<TWINT)|(1<<TWEN);
	}
	while(!(TWCR&(1<<TWINT)));

	return TWDR;
}
void I2C_send(uint8_t device, uint8_t addr, uint8_t data)
{
	I2C_start();
	I2C_writeByte(device);
	I2C_writeByte(addr);
	I2C_writeByte(data);
	I2C_stop();
}
/*!
 * @brief 
 * 
 * @param device 
 * @param addr 
 * @return uint8_t 
 */
uint8_t I2C_receive(uint8_t deviceW,uint8_t deviceR, uint8_t addr, uint8_t ack)
{
	I2C_start();
	I2C_writeByte(deviceW);
	I2C_writeByte(addr);
	I2C_start();
	I2C_writeByte(deviceR);
	uint8_t tmp = I2C_readByte(ack);
	I2C_stop();

	return tmp;
}


void I2C_wait() {
    while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_ReadDataAck() {
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    I2C_wait();

    return TWDR;
}

uint8_t I2C_ReadDataNotAck() {
    TWCR = (1 << TWINT) | (1 << TWEN);
    I2C_wait();

    return TWDR;
}