
#include <avr/io.h>
#include <util/delay.h>
#include "bmp180.h"



uint16_t BMP180_readRegisterI2C(uint8_t reg)
{
	I2C_start();
	I2C_writeByte(BMP180_ADDR_W);
	I2C_writeByte(reg);
	I2C_start();
	I2C_writeByte(BMP180_ADDR_R);
	uint8_t msb = I2C_readByte(reg);
	uint8_t lsb = I2C_readByte(0);
	I2C_stop();
	uint16_t tmp=((msb<<8)|lsb);
	return tmp;
}


uint8_t BMP180_readCalibrationData(bmp180DataConf *data)
{	
	I2C_init();

	for(uint16_t reg=0xAA; reg<=0xBE; reg+=2)
	{	
       int16_t ok = BMP180_readRegisterI2C(reg);

		switch (reg)
		{
		case 0xAA:
			data->ac1=(int16_t)ok;
			break;
		case 0xAC:
			data->ac2=(int16_t)ok;
			break;
		case 0xAE:
			data->ac3=(int16_t)ok;
			break;
		case 0xB0:
			data->ac4=(uint16_t)ok;
			break;
		case 0xB2:
			data->ac5=(uint16_t)ok;
			break;
		case 0xB4:
			data->ac6=(uint16_t)ok;
			break;
		case 0xB6:
			data->b1=(int16_t)ok;
			break;
		case 0xB8:
			data->b2=(int16_t)ok;
			break;
		case 0xBA:
			data->mb=(int16_t)ok;
			break;
		case 0xBC:
			data->mc=(int16_t)ok;
			break;
		case 0xBE:
			data->md=(int16_t)ok;
			break;
		}
	}
	// I2C_stop();
	return 0;
}



uint16_t BMP180_getTemperature()
{	
	I2C_start();
	I2C_writeByte(BMP180_ADDR_W);
	I2C_writeByte(0xF4);
	I2C_writeByte(0x2E);
	I2C_stop();
	_delay_us(4500);
	// I2C_start();

	uint16_t tmp = BMP180_readRegisterI2C(0xF6);
	I2C_stop();

	return tmp;
}



int32_t BMP180_getPressure(uint8_t oss)
{	
	uint8_t ossP=oss;
	I2C_start();
	I2C_writeByte(BMP180_ADDR_W);
	I2C_writeByte(0xF4);
	switch (oss)
	{
	case BMP180_ULTRA_LOW_POWER:
		I2C_writeByte(0x34+(oss<<6));	
		I2C_stop();
		_delay_us(4500);
		break;
	case BMP180_STANDARD:
		I2C_writeByte(0x34+(oss<<6));	
		I2C_stop();
		_delay_us(7500);
		/* code */
		break;
	case BMP180_HIGH_RESOLUTION:
		I2C_writeByte(0x34+(oss<<6));	
		I2C_stop();
		_delay_us(13500);
		/* code */
		break;
	case BMP180_ULTRA_HIGH_RESOLUTION:
		I2C_writeByte(0x34+(oss<<6));	
		I2C_stop();
		_delay_us(25500);
		/* code */
		break;
	default:
		ossP=BMP180_ULTRA_LOW_POWER;
		I2C_writeByte(0x34+(ossP<<6));	
		I2C_stop();
		_delay_us(4500);
		break;
	}
	I2C_start();
	I2C_writeByte(BMP180_ADDR_W);
	I2C_writeByte(0xF6);
	I2C_start();
	I2C_writeByte(BMP180_ADDR_R);
	uint8_t msb = I2C_readByte(0xF6);
	uint8_t lsb = I2C_readByte(0);
	I2C_stop();
	int32_t press=(((int32_t)msb<<16)+((int32_t)lsb<<8))>>(8-ossP);
	return press;
}

long BMP180_calculatePressure( int32_t bmp180Press, bmp180DataConf *data, uint8_t oss)
{
int32_t b6 = data->b5 - 4000;
    int32_t x1 = ((int32_t) data->b2 * (b6 * b6 >> 12)) >> 11;
    int32_t x2 = (int32_t) data->ac2 * b6 >> 11;
    int32_t x3 = x1 + x2;
    int32_t b3 = ((((int32_t) data->ac1 * 4 + x3) << oss) + 2) >> 2;
    x1 = (int32_t) data->ac3 * b6 >> 13;
    x2 = ((int32_t) data->b1 * (b6 * b6 >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    uint32_t b4 = (uint32_t) data->ac4 * (x3 + 32768) >> 15;
    uint32_t b7 = ((bmp180Press - b3) * (50000 >> oss));

    long p;
    if (b7 < 0x80000000) {
        p = ((b7 * 2) / b4);
    } else {
        p = ((b7 / b4) * 2);
    }

    x1 = (p >> 8) * (p >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    p = p + ((x1 + x2 + 3791) >> 4);

    return p;
}



int32_t BMP180_calculateTemp(uint16_t bmp180temp,  bmp180DataConf *calibData) 
{
    int32_t x1 = ((bmp180temp - calibData->ac6) * (int32_t) calibData->ac5) >> 15;
    int32_t x2 = ((int32_t) calibData->mc << 11) / (x1 + calibData->md);
    calibData->b5 = x1 + x2;

    int32_t temperature = ((calibData->b5 + 8) >> 4);
    // temperature /= (float) 10;

    return temperature;
}

