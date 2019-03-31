#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#define FORWARD 1
#define REVERSE 2
#define STOP 3
// #define KEY0 PCin(5)
// #define KEY1 PAin(15)
// #define WK_UP PAin(0)
#define KEY0 (1<<5) //KEY0 PC5
#define KEY1 (1<<15) //KEY1 PA15
#define WK_UP (1<<0) //WK_UP PA0
#define KEY0_GET() ((GPIOC->IDR & (KEY0))?1:0)//读取按键0
#define KEY1_GET() ((GPIOA->IDR & (KEY1))?1:0)//读取按键1
#define WKUP_GET() ((GPIOA->IDR & (WK_UP))?1:0)//读取按键WK_UP

void KEY_Init(void);
u8 KEY_Scan(u8 mode);

#endif
