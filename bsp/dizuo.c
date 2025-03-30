#include "oled.h"
#include "ds18b20.h"
#include "stdio.h"
sbit P00 = P0^0;


void main()
{

uchar *now_temp="Not ready";  //字符模式当前温度
float num_temp;	   //数值模式当前温度
	float temperature;
	 char show[20];
    OLED_Init();//初始化OLED
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  	OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    while (1)
    {
			num_temp=DS18B20NumTemp();
			now_temp=DS18B20toString(num_temp);	   
			OLED_ShowString(0,0,now_temp,8);
		    delay_ms(1000);
    }
}

