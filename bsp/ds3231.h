#ifndef __DS3231_H_
#define __DS3231_H_

#include "reg52.h"
#include "oled.h"

//DS3221����
/**********************************
		PIN�ڶ���
**********************************/
sbit SDA = P0^2;  // I2C ������
sbit SCL = P0^1;  // I2C ʱ����

#define DS3231_ADDRESS 0xd0   //ds3231��i2c��ַ					  

void DS3231_Write(unsigned char addr, unsigned char dat);
unsigned char DS3231_Read(unsigned char addr);

void show_time(void);
void show_date(void);

#endif
