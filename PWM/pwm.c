#include "pwm.h"

//TIM1和TIM8是高级定时器
void TIM1_PWM_Init(u16 arr,u16 psc)
{
	RCC->APB2ENR |= 1<<11;///使能TIM1时钟
	GPIOA->CRH &= 0XFFFFFFF0;
	GPIOA->CRH |= 0X0000000B;//使能PA8是因为TIM1_CH1通道使用PA8的复用功能作为输出
	
	TIM1->ARR = arr; //自动重装载值
	TIM1->PSC = psc; //预分频
	
	TIM1->CCMR1 |= 6<<4; //01100000 PWM模式1，向上计数，CNT<CCR1为有效电平
	TIM1->CCMR1 |= 1<<3; //开启预装载功能
	
	TIM1->CCER  |= 1<<0; //OC1信号输出到对应的输出引脚
	TIM1->BDTR  |= 1<<15;//刹车死区寄存器，高级定时器才需要配置
	TIM1->CR1    = 0x0080; 
	TIM1->CR1   |= 0x01; //使能计数器
}

void TIM8_PWM_Init(u16 arr,u16 psc)//PC6  CH1   ,NOT CH1N
{
	RCC->APB2ENR |= 1<<13;
	RCC->APB2ENR |= 1<<4;
	GPIOC->CRL  &= 0XF0FFFFFF;
	GPIOC->CRL  |= 0X0B000000;
	TIM8->ARR = arr; //自动重装载
	TIM8->PSC = psc; //分频值
	TIM8->CCMR1 |= 6<<4; //01100000
	TIM8->CCMR1 |= 1<<3;
	TIM8->CCER  |= 1<<0;
	TIM8->BDTR  |= 1<<15;
	TIM8->CR1    = 0x0080;
	TIM8->CR1   |= 1;
}


//TIM3和TIM4是通用定时器
void TIM3_PWM_Init(u16 arr,u16 psc)//PA6  CH1 
{
	RCC->APB1ENR |= 1<<1; //TIM3 ENABLE
	RCC->APB2ENR |= 1<<2; //IOPA ENABLE
	GPIOA->CRL  &= 0XF0FFFFFF;
	GPIOA->CRL  |= 0X0B000000;
	TIM3->ARR = arr; //自动重装载
	TIM3->PSC = psc; //分频值
	TIM3->CCMR1 |= 6<<4; //01100000
	TIM3->CCMR1 |= 1<<3;
	TIM3->CCER  |= 1<<0;
	TIM3->CR1    = 0x0080;
	TIM3->CR1   |= 1;
}


void TIM4_PWM_Init(u16 arr,u16 psc)//PB6  CH1 
{
	RCC->APB1ENR |= 1<<2;
	RCC->APB2ENR |= 1<<3;
	GPIOB->CRL  &= 0XF0FFFFFF;
	GPIOB->CRL  |= 0X0B000000;
	TIM4->ARR = arr; //自动重装载
	TIM4->PSC = psc; //分频值
	TIM4->CCMR1 |= 6<<4; //01100000
	TIM4->CCMR1 |= 1<<3;
	TIM4->CCER  |= 1<<0;
	TIM4->CR1    = 0x0080;
	TIM4->CR1   |= 1;
}
