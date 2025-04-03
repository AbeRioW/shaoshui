#include "ds3231.h"
#include "stdio.h"




static void I2C_Delay() {
    unsigned int i;
    for (i = 0; i < 10; i++);
}

static void I2C_Start() {
    SDA = 1;
    SCL = 1;
    I2C_Delay();
    SDA = 0;
    I2C_Delay();
    SCL = 0;
}

static void I2C_Stop() {
    SDA = 0;
    SCL = 1;
    I2C_Delay();
    SDA = 1;
    I2C_Delay();
}

static void I2C_Ack() {
    SDA = 0;
    SCL = 1;
    I2C_Delay();
    SCL = 0;
    SDA = 1;
}

static void I2C_NoAck() {
    SDA = 1;
    SCL = 1;
    I2C_Delay();
    SCL = 0;
}

static bit I2C_WaitAck() {
    SDA = 1;
    SCL = 1;
    I2C_Delay();
    if (SDA) {
        SCL = 0;
        return 0;
    }
    SCL = 0;
    return 1;
}

static void I2C_SendByte(unsigned char dat) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SDA = (dat & 0x80) ? 1 : 0;
        dat <<= 1;
        SCL = 1;
        I2C_Delay();
        SCL = 0;
    }
    I2C_WaitAck();
}

static unsigned char I2C_ReadByte() {
    unsigned char i, dat = 0;
    SDA = 1;
    for (i = 0; i < 8; i++) {
        SCL = 1;
        I2C_Delay();
        dat <<= 1;
        if (SDA) dat |= 0x01;
        SCL = 0;
        I2C_Delay();
    }
    return dat;
}

void DS3231_Write(unsigned char addr, unsigned char dat) {
    I2C_Start();
    I2C_SendByte(0xD0);  // DS3231 的写地址
    I2C_SendByte(addr);  // 寄存器地址
    I2C_SendByte(dat);   // 数据
    I2C_Stop();
}

unsigned char DS3231_Read(unsigned char addr) {
    unsigned char dat;
    I2C_Start();
    I2C_SendByte(0xD0);  // DS3231 的写地址
    I2C_SendByte(addr);  // 寄存器地址
    I2C_Start();
    I2C_SendByte(0xD1);  // DS3231 的读地址
    dat = I2C_ReadByte();
    I2C_NoAck();
    I2C_Stop();
    return dat;
}

//void main() {
//    unsigned char second, minute,  ;
//    DS3231_Write(0x00, 0x00);  // 设置秒
//    DS3231_Write(0x01, 0x30);  // 设置分钟
//    DS3231_Write(0x02, 0x12);  // 设置小时
//
//    while (1) {
//        second = DS3231_Read(0x00);
//        minute = DS3231_Read(0x01);
//        hour = DS3231_Read(0x02);
//        // 在这里处理读取的时间数据
//    }
//}

void show_time(void)
{
     char show[20];
     unsigned int hour_i,minute_i,second_i;
     unsigned char second_c,minute_c,hour_c;

     second_c  = DS3231_Read(0x00);  			//获取秒
     minute_c  = DS3231_Read(0x01);     	   	//获取分
     hour_c    = DS3231_Read(0x02);	        //获取时
	 				 
	 hour_i = 	 ((hour_c&0x7f)>>4)*10+   hour_c&0x0f;
	 minute_i =  ((minute_c&0x7f)>>4)*10+ minute_c&0x0f;
	 second_i =  ((second_c&0x7f)>>4)*10+ second_c&0x0f;
     sprintf(show,"%02d:%02d:%02d",hour_i,minute_i,second_i);	
     OLED_ShowString(70,0,show,8);
}

void show_date(void)
{
     char show[20];
     unsigned int date_i,month_i,year_i;
     unsigned char date_c,month_c,year_c;

	 date_c = DS3231_Read(0x04);	        //获取日
     month_c = DS3231_Read(0x05);			//获取月
     year_c = DS3231_Read(0x06);			//获取年
	 year_i = 	 ((year_c&0x7f)>>4)*10+ year_c&0x0f;
	 month_i = 	 ((month_c&0x7f)>>4)*10+ month_c&0x0f;
	 date_i = 	 ((date_c&0x7f)>>4)*10+ date_c&0x0f;
     sprintf(show,"20%02d-%02d-%02d",year_i,month_i,date_i);
	 OLED_ShowString(0,0,show,8);	
}
