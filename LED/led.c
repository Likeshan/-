#include "sys.h"   
#include "led.h"

//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2; // PORTA 
	RCC->APB2ENR|=1<<5; // PORTD 
	GPIOA->CRH&=0XFFFFFFF0;
	GPIOA->CRH|=0X00000003;//PA8 
	GPIOA->ODR|=1<<8; //PA8 
	
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2 
	GPIOD->ODR|=1<<2; //PD.2 
}

