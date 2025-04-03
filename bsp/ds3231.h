#ifndef __DS3231_H_
#define __DS3231_H_

#include "reg52.h"
#include "oled.h"

//DS3221引脚
/**********************************
		PIN口定义
**********************************/
sbit SDA = P0^2;  // I2C 数据线
sbit SCL = P0^1;  // I2C 时钟线

#define DS3231_ADDRESS 0xd0   //ds3231的i2c地址					  

void DS3231_Write(unsigned char addr, unsigned char dat);
unsigned char DS3231_Read(unsigned char addr);

void show_time(void);
void show_date(void);

#endif
