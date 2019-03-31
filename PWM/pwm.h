#ifndef __PWM_H
#define __PWM_H
#include "sys.h"
//通过改变TIM->CCR1的值来改变占空比，从而控制输出占空比
#define TIM1_PWM_VAL TIM1->CCR1
#define TIM8_PWM_VAL TIM8->CCR1
#define TIM3_PWM_VAL TIM3->CCR1
#define TIM4_PWM_VAL TIM4->CCR1

void TIM1_PWM_Init(u16 arr,u16 psc);  // pwm
void TIM8_PWM_Init(u16 arr,u16 psc);  // pwm
void TIM3_PWM_Init(u16 arr,u16 psc); 
void TIM4_PWM_Init(u16 arr,u16 psc); 
#endif
