#include "ui_setting.h"

int cur_temp=27;
int is_down=0;
int dangwei = 0;

void ui_setting(void)
{
	  int position=0;
	  char show_temp[20]={0},char_down[20]={0};
	  OLED_ShowString(40,0,"Setting",8);
	  while(1)
	  {
	  	
		 if(position<3)
		 {
		 	dangwei	=position;
		 }
	  	 OLED_ShowString(0,1,position==0?">gear 1":" gear 1",8);		//30du
		 OLED_ShowString(0,2,position==1?">gear 2":" gear 2",8);	    //70du		   
		 OLED_ShowString(0,3,position==2?">gear 3":" gear 3",8);		//100du	

		 if(position==3)
		 {
		 	sprintf(show_temp,">const temp:%d",cur_temp); 		 	
		 }
		 else
		 {
		 	sprintf(show_temp," const temp:%d",cur_temp);
		 }  
		 OLED_ShowString(0,4,show_temp,8);


		if(position==4)
		{
			 (is_down==0)?OLED_ShowString(0,5,">timed shutdown: NO",8):OLED_ShowString(0,5,">timed shutdown:YES",8);
		}
		else
		{
			  (is_down==0)?OLED_ShowString(0,5," timed shutdown: NO",8):OLED_ShowString(0,5," timed shutdown:YES",8);
		}

		 if(KEY5==0)
		 {
		 	delay_ms(2);
			if(KEY5==0)
			{
				position++;
				if(position==5)
				{
				   position=4;
				}	
			}
		 }

		if(KEY4==0)
		 {
		 	delay_ms(2);
			if(KEY4==0)
			{
				position--;
				if(position<0)
				{
				   position=0;
				}	
			}
		 }

		 if(KEY1==0)
		 {
		 	delay_ms(2);
			if(KEY1==0)
			{
				switch(position)
				{
					case 3:
						cur_temp--;
						if(cur_temp<0)
							cur_temp=0;	
					break;
					case 4:
						is_down=0;
					break;
				}
			}		 	
		 }


		 
		 if(KEY2==0)
		 {
		 	delay_ms(2);
			if(KEY2==0)
			{
				switch(position)
				{
					case 3:
						cur_temp++;
						if(cur_temp>90)
							cur_temp=90;	
					break;
					case 4:
						is_down=1;
					break;
				}
			}		 	
		 }

		 if(KEY3==0)
		 {
		 	delay_ms(2);
			if(KEY3==0)
			{
				OLED_Clear();
				break;	
			}
		 }
	  }   			
}
