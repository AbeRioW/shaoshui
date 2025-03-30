#include "oled.h"
#include "ds18b20.h"
#include "stdio.h"
sbit P00 = P0^0;


void main()
{

uchar *now_temp="Not ready";  //�ַ�ģʽ��ǰ�¶�
float num_temp;	   //��ֵģʽ��ǰ�¶�
	float temperature;
	 char show[20];
    OLED_Init();//��ʼ��OLED
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  	OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
    while (1)
    {
			num_temp=DS18B20NumTemp();
			now_temp=DS18B20toString(num_temp);	   
			OLED_ShowString(0,0,now_temp,8);
		    delay_ms(1000);
    }
}

