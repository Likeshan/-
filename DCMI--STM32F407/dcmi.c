#include "dcmi.h"
#include "dma.h"
void DCMI_GPIO_Init(void)
{
	RCC->AHB1ENR |= 0X1F<<0;
	GPIO_AF_Set(GPIOA,8,0);
	GPIO_Set(GPIOD,PIN3,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_50M,GPIO_PUPD_PU);//PWRDOWN
	
	GPIO_AF_Set(GPIOA,4,13);  //DCMI复用配置
	GPIO_AF_Set(GPIOA,6,13);
	GPIO_AF_Set(GPIOB,7,13);
	GPIO_AF_Set(GPIOC,6,13);
	GPIO_AF_Set(GPIOC,7,13);
	GPIO_AF_Set(GPIOC,8,13);
	GPIO_AF_Set(GPIOC,9,13);
	GPIO_AF_Set(GPIOC,11,13);
	GPIO_AF_Set(GPIOB,6,13);
	GPIO_AF_Set(GPIOE,5,13);
	GPIO_AF_Set(GPIOE,6,13);
	GPIO_Set(GPIOA,PIN8,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//XCLK
	GPIO_Set(GPIOA,PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//PCLK
	GPIO_Set(GPIOA,PIN4,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//HREF
	GPIO_Set(GPIOB,PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//D5
	GPIO_Set(GPIOB,PIN7,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//VSYNC
	GPIO_Set(GPIOC,PIN6|PIN7|PIN8|PIN9|PIN11,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//D0,D1,D2,D3,D4
	GPIO_Set(GPIOE,PIN5|PIN6,GPIO_MODE_AF,GPIO_OTYPE_PP,GPIO_SPEED_100M,GPIO_PUPD_PU);//D6,D7
	

	
}

void DCMI_Init(void)
{
	u32 a;
	DCMI_GPIO();
	RCC->AHB2ENR |=1<<0;
	DCMI->IER=0x0;
	DCMI->ICR=0x1F;
	DCMI->ESCR=0x0;
	DCMI->ESUR=0x0;
	DCMI->CWSTRTR=0x0;
	DCMI->CWSIZER=0x0;	
	DCMI->CR = 0X0;      //初始化DCMI进行配置
	DCMI->CR &= ~(1<<1); //连续捕获
	DCMI->CR |= 1<<5;    //PCLK上升沿有效
	DCMI->CR |= 1<<6;    //HSYNC高电平有效
	DCMI->CR |= 1<<7;		 //VSYNC高电平有效
	
	
	
	DCMI->CWSIZER=240<<16;
	
	DCMI->CWSIZER|=240*240*2;
	DCMI->IER|=1<<0; 							//开启帧中断
	MY_NVIC_Init(1,2,DCMI_IRQn,2);
	DCMI->CR |= 1<<14;   //使能DCMI

}
void DCMI_IRQHandler(void)
{
	u16 temp;
	long int i;
	u16 T=0XAD55;
	if(DCMI->MISR & 0X01)
	{
		DCMI_Stop();
		
		LCD_SetCursor(0x00,0x00);	       //设置光标位置 
		LCD_WriteRAM_Prepare();     		 //开始写入GRAM
		
		for(i=0; i<38400; i++)
		{ 
			temp = (u16)(Crazy_Buffer[i]>>16);
			if(temp>T)
			{			
				temp = 0XFFFF;//white
				LCD_DATA = temp;
			}
			else
			{
				temp = 0X0000;//black
				LCD_DATA = temp;
			}
			
			temp = (u16)(Crazy_Buffer[i]);
			if(temp>T)
			{			
				temp = 0XFFFF;//white
				LCD_DATA = temp;
			}
			else
			{
				temp=0X0000;//black
				LCD_DATA = temp;
			}
		
		}
	
		
	LCD_SetCursor(0,0);
	LCD_WriteReg(0x22,0x1018);
	//LCD_Clear(0xFFFF);//清屏
	DCMI->ICR|=1<<0;	//清除帧中断
		DCMI_Start();//开始摄像
	}
}

void DCMI_Start(void)
{
	DMA2_Stream1->CR |= 1<<0;         //使能数据流
	DCMI->CR |= 1<<0;      				    //使能捕获
}

void DCMI_Stop(void)
{
	DCMI->CR &=~(1<<0); 			        //关闭捕获  
	while(DCMI->CR&0X01);		          //等待传输结束 
	DMA2_Stream1->CR&=~(1<<0);	      //关闭DMA2_Stream1  	
} 
