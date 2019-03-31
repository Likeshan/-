#ifndef __DCMI_H
#define __DCMI_H
#include "sys.h"

void DCMI_GPIO_Init(void);
void DCMI_Init(void);
void DCMI_Start(void);
void DCMI_Stop(void);
extern u32 *Crazy_Buffer;
#endif
