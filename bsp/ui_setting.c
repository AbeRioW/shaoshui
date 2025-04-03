#include "ui_setting.h"

void ui_setting(void)
{
    int position = 0;

	while(1)
	{
		OLED_ShowString(20,0,position==0?">1.Gear adjustment":" 1.Gear adjustment",8); 
		OLED_ShowString(20,1,position==1?">2.Date Setting":" 2.Date Setting",8); 
			if(KEY4==0)
			{
				delay_ms(2);
				if(KEY4==0)
				{
					position--;
					if(position<0)
					{
						position=1;
					}
				}
			}

			if(KEY5==0)
			{
				delay_ms(2);
				if(KEY5==0)
				{
					position++;
					if(position>1)
					{
						position=0;
					}
				}
			}


			if(KEY3==0)
			{
				delay_ms(2);
				if(KEY3==0)
				{
					switch(position)
					{
						case 0:
							
						break;
						case 1:
							OLED_Clear();
							//ui_set_date();
						break;
					}
				}
			}

			//KEY1被按下,返回键
			if(KEY1==0)
			{
				delay_ms(2);
				if(KEY1==0)
				{
				    OLED_Clear();
					return;
				}				
			}			
	}
}


//void ui_set_date(void)
//{
//    int position=0;
//    unsigned int hour_i,minute_i,second_i;
//    unsigned char second_c,minute_c,hour_c;
//
//	unsigned int date_i,month_i,year_i;
//    unsigned char date_c,month_c,year_c;
//
//	char show_data1[15],show_data2[15];
//
//
//	OLED_ShowString(20,0,"Date Set",8);
//	second_c  = DS3231_Read(0x00);  			//获取秒
//    minute_c  = DS3231_Read(0x01);     	   	//获取分
//    hour_c    = DS3231_Read(0x02);	        //获取时 
//
//	 hour_i = 	 ((hour_c&0x7f)>>4)*10+   hour_c&0x0f;
//	 minute_i =  ((minute_c&0x7f)>>4)*10+ minute_c&0x0f;
//	 second_i =  ((second_c&0x7f)>>4)*10+ second_c&0x0f;
//
//	 date_c = DS3231_Read(0x04);	        //获取日
//     month_c = DS3231_Read(0x05);			//获取月
//     year_c = DS3231_Read(0x06);			//获取年
//
//	 year_i = 	 ((year_c&0x7f)>>4)*10+ year_c&0x0f;
//	 month_i = 	 ((month_c&0x7f)>>4)*10+ month_c&0x0f;
//	 date_i = 	 ((date_c&0x7f)>>4)*10+ date_c&0x0f;
//
//	while(1)
//	{
//	    sprintf(show_data1,"20%02d-%02d-%02d   ",year_i,month_i,date_i);	
//		sprintf(show_data2,"%02d:%02d:%02d   ",hour_i,minute_i,second_i);
//		OLED_ShowString(0,1,show_data1,8);
//		OLED_ShowString(0,2,show_data2,8);
//
//		if(KEY3==0)
//		{
//			delay_ms(2);
//			if(KEY3==0)
//			{
//				position++;
//				if(position>5)
//					position=0;	
//			}
//		}
//
//		if(KEY4==0)
//		{
//			delay_ms(2);
//			if(KEY4==0)
//			{
//				switch(position)
//				{
//				   	case 0:
//					   year_c--;
//					   if(year_c<0)
//					   {
//					   		year_c = 0x63; 	
//					   } 
//					break;
//					case 1:
//						month_c--;
////						month_c = 	
//					break;
//				}
//			}
//		}
//	}	
//}
