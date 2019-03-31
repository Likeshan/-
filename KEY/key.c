
#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	RCC->APB2ENR |= 1<<2;
	RCC->APB2ENR |= 1<<4;   
	JTAG_Set(SWD_ENABLE);
	GPIOA->CRL &= 0XFFFFFFF0; //PA0设为输入
	GPIOA->CRL |= 0X00000008;
	GPIOA->CRH &= 0X0FFFFFFF; //PA15设为输入
	GPIOA->CRH |= 0X80000000;
	GPIOA->ODR |= 1<<15; 	  //PA15上拉输入
	GPIOC->CRL &= 0XFF0FFFFF;
	GPIOC->CRL |= 0X00800000;
	GPIOC->ODR |= 1<<5;       //PC5上拉输入
}

u8 KEY_Scan(u8 mode)
{

	static u8 key_up=1;
	if(mode)key_up=1; //连按
	if(key_up && (KEY0_GET()==0 || KEY1_GET()==0 || WKUP_GET()==1))
	{ 
		delay_ms(10);
		key_up=0;
		if(KEY0_GET()==0){
			return FORWARD;
		}
		else if(KEY1_GET()==0){
			return REVERSE;
		}
		else if(WKUP_GET()==1){
			return STOP;
		}
	}else if(KEY0_GET()==1 && KEY1_GET()==1 && WKUP_GET()==0){
		key_up=1;
	}
	return 0;
}
