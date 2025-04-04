#include "oled.h"
#include "ds18b20.h"
#include "stdio.h"
#include "ds3231.h"
#include "ui_setting.h"

#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
unsigned int count;                         //1000 times counter
int time_come=0;

int shao_shui=0;
sbit P00 = P0^0;	  //LAY
void UART_Init(void);	   //11.0592MHz,波特率为9600

int i_count =0;
void ui_main(void)
{
    int highest_tmp=0;
	uchar *now_temp="Not ready";  //字符模式当前温度
	float num_temp;	   //数值模式当前温度
	P00=1;
	while(1)
	{
	    if(dangwei==0)
		{
			highest_tmp=30;
		}
		if(dangwei==1)
		{
			highest_tmp=70;	
		}
		if(dangwei==2)
		{
			highest_tmp=90;	
		}


	 	OLED_ShowString(20,0,"Boiling water",8);   			//这里的Y是指一个字符的其实,不是像素点的起始
		num_temp=DS18B20NumTemp();
		now_temp=DS18B20toString(num_temp);	   
		OLED_ShowString(0,2,now_temp,8);   			//这里的Y是指一个字符的其实,不是像素点的起始

		if(shao_shui&&num_temp<cur_temp)
		{
			P00=0;	
		}

		if(num_temp>highest_tmp)
		{
			P00=1;
		}
		if(KEY3==0)
		{
			delay_ms(2);
			if(KEY3==0)
			{
				P00=~P00;
				shao_shui=!shao_shui;
				if(!shao_shui)
				{
					i_count	=0;
				}
			}	
		}

		if(KEY2==0)
		{
			delay_ms(2);
			if(KEY2==0)
			{
				OLED_Clear();
				break;
					
			}
		}

		if((is_down==1)&&shao_shui)
		{
			i_count++;
		}

		if(i_count==300)
		{
			i_count=0;
			shao_shui=0;
			P00=1;

		}
	}

}

void main()
{


	float temperature;

//	UART_Init();
//	timer0_init();

    OLED_Init();//初始化OLED
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示

	P00=1;
    while (1)
    {

		  ui_main();
		  ui_setting();

    }
}


//void UART_Init(void)	   //11.0592MHz,波特率为9600
//{
//    SCON  = 0x50;                // SCON: 模式 1, 8-bit UART, 使能接收
//    TMOD |= 0x20;               // TMOD: timer 1, mode 2, 8-bit 重装
//    TH1   = 0xFD;               // TH1:  重装值 9600 波特率 晶振 11.0592MHz
//    TL1 = TH1;
//    TR1   = 1;                  // TR1:  timer 1 打开
//    EA    = 1;                  //打开总中断
//    ES    = 0;                  //先关闭串口中断
//	TI    =1;
//}
//
//
////定时器相关
//void timer0_init(void)
//{
//	TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
//    TL0 = T1MS;                     //initial timer0 low byte
//    TH0 = T1MS >> 8;                //initial timer0 high byte
//    TR0 = 1;                        //timer0 start running
//    ET0 = 1;                        //enable timer0 interrupt
//    EA = 1;                         //open global interrupt switch
//    count = 0;                      //initial counter
//}
//
//
///* Timer0 interrupt routine */
//void tm0_isr() interrupt 1
//{
//    TL0 = T1MS;                     //reload timer0 low byte
//    TH0 = T1MS >> 8;                //reload timer0 high byte
//    if (count-- == 0)               //1ms * 1000 -> 1s
//    {
//        count = 1000;               //reset counter
//		 time_come = 1;
//		 
//    }
//
//}
