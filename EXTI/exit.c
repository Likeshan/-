#include "exti.h"
#include "delay.h"
#include "usart.h"

//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	/*
	Code here
	*/	 
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
}

void EXTI_Init(void)
{

	Ex_NVIC_Config(GPIO_A,0,RTIR); 		//上升沿触发,0号外部中断
	//Ex_NVIC_Config(GPIO_C,5,FTIR);		//下降沿触发,5号外部中断
	//Ex_NVIC_Config(GPIO_A,15,FTIR);		//下降沿触发,15号外部中断

	MY_NVIC_Init(2,2,EXTI0_IRQn,2);    	//抢占2，子优先级2，组2
	//MY_NVIC_Init(2,1,EXTI9_5_IRQn,2);  	//抢占2，子优先级1，组2
	//MY_NVIC_Init(2,0,EXTI15_10_IRQn,2);	//抢占2，子优先级0，组2	   
}

