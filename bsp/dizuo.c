#include "oled.h"
#include "ds18b20.h"
#include "stdio.h"
#include "ds3231.h"
#include "ui_setting.h"

#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
unsigned int count;                         //1000 times counter
int time_come=0;

sbit P00 = P0^0;	  //LAY
void UART_Init(void);	   //11.0592MHz,波特率为9600
void timer0_init(void);

void main()
{

	uchar *now_temp="Not ready";  //字符模式当前温度
	float num_temp;	   //数值模式当前温度
	float temperature;

	UART_Init();
	timer0_init();

    OLED_Init();//初始化OLED
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示

    DS3231_Write(0x00, 0x00);  // 设置秒
    DS3231_Write(0x01, 0x30);  // 设置分钟
    DS3231_Write(0x02, 0x12);  // 设置小时

	DS3231_Write(0x03, 0x03);  // 设置week
	DS3231_Write(0x04, 0x19);  // 设置日
	DS3231_Write(0x05, 0x0a);  // 设置月
	DS3231_Write(0x06, 0x00);  // 设置年

//	ui_set_date();

    while (1)
    {
		if(time_come)
		{
			time_come = 0;
			show_date();
			show_time();

			num_temp=DS18B20NumTemp();
			now_temp=DS18B20toString(num_temp);	   
			OLED_ShowString(0,1,now_temp,8);   			//这里的Y是指一个字符的其实,不是像素点的起始
		}

//		if(KEY3==0)
//		{
//			delay_ms(2);
//			if(KEY3==0)
//			{
//				OLED_Clear();
//				ui_setting();	
//			}
//		}
    }
}


void UART_Init(void)	   //11.0592MHz,波特率为9600
{
    SCON  = 0x50;                // SCON: 模式 1, 8-bit UART, 使能接收
    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit 重装
    TH1   = 0xFD;               // TH1:  重装值 9600 波特率 晶振 11.0592MHz
    TL1 = TH1;
    TR1   = 1;                  // TR1:  timer 1 打开
    EA    = 1;                  //打开总中断
    ES    = 0;                  //先关闭串口中断
	TI    =1;
}


//定时器相关
void timer0_init(void)
{
	TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = T1MS;                     //initial timer0 low byte
    TH0 = T1MS >> 8;                //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;                         //open global interrupt switch
    count = 0;                      //initial counter
}


/* Timer0 interrupt routine */
void tm0_isr() interrupt 1
{
    TL0 = T1MS;                     //reload timer0 low byte
    TH0 = T1MS >> 8;                //reload timer0 high byte
    if (count-- == 0)               //1ms * 1000 -> 1s
    {
        count = 1000;               //reset counter
		 time_come = 1;
		 
    }

}
