/*!
 * @file i2c.h
 * @author {Kacper Szczepanowski} ({kacperszcz159@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef I2C_H
#define I2C_H
#include<stdint-gcc.h>

void I2C_init();

void I2C_start();

void I2C_wait() ;

void I2C_stop();

void I2C_writeByte(uint8_t data);

uint8_t I2C_readByte(uint8_t ack);

void I2C_send(uint8_t device, uint8_t addr, uint8_t data);

uint8_t I2C_receive(uint8_t deviceW,uint8_t deviceR, uint8_t addr, uint8_t ack);



uint8_t I2C_ReadDataAck();

uint8_t I2C_ReadDataNotAck();

#endif // I2C_H