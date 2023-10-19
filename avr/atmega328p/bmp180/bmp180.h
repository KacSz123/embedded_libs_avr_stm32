/*!
 * @file bmp180.h
 * @author {Kacper Szczepanowski} ({kacperszcz159@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef BMP180_H
#define BMP180_H
#include "i2c.h"
#include<stdint-gcc.h>

#define BMP180_ADDR_W 0xEE
#define BMP180_ADDR_R 0xEF

#define BMP180_ULTRA_LOW_POWER 0
#define BMP180_STANDARD 1
#define BMP180_HIGH_RESOLUTION 2
#define BMP180_ULTRA_HIGH_RESOLUTION 3

#define BMP180_OK 0
#define BMP180_NOK 1

/*!
 * @brief 
 * 
 */
typedef struct bmp180DataConf
{
	int16_t ac1;
	int16_t ac2;
	int16_t ac3;
	uint16_t ac4;
	uint16_t ac5;
	uint16_t ac6;
	int16_t b1;
	int16_t b2;
	int16_t mb;
	int16_t mc;
	int16_t md;
	//help b5
	int32_t b5;
    	
}bmp180DataConf;

typedef struct bmp180DataMeasured
{
	int16_t _press;
	uint8_t _temp;
}bmp180DataMeasured;


uint16_t BMP180_readRegisterI2C(uint8_t reg);

uint8_t BMP180_readCalibrationData(bmp180DataConf *data);

uint16_t BMP180_getTemperature();


int32_t BMP180_getPressure(uint8_t oss);

int32_t BMP180_calculatePressure( int32_t bmp180Press, bmp180DataConf *data, uint8_t oss);

/*!
 * @brief 
 * 
 * @param bmp180temp 
 * @param calibData 
 * @param b5 
 * @return int32_t  temperature 0.1 *C
 */
int32_t BMP180_calculateTemp(uint16_t bmp180temp,  bmp180DataConf *calibData);
#endif //BMP180_H
