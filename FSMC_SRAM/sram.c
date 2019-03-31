#include "sram.h"


//初始化外部SRAM
void FSMC_SRAM_Init(void)
{	
    RCC->APB2ENR |= 1<<8; //使能GPIOG时钟 
	RCC->APB2ENR |= 1<<7;  //使能GPIOF时钟 
  	RCC->APB2ENR |= 1<<6;  //使能GPIOE时钟 
	RCC->APB2ENR |= 1<<5;  //使能GPIOD时钟 
    
	GPIOD->CRL &= 0XFF00FFFF;
   	GPIOD->CRL |= 0X00BB0000;   //FSMC_NOE,FSMC_NWE PD4 PD5
		
	GPIOE->CRL &= 0XFFFFFF00;
   	GPIOE->CRL |= 0X000000BB;   //FSMC_NBL0-1 PE0	PE1
		
    GPIOD->CRL &= 0XFFFFFF00;
   	GPIOD->CRL |= 0X000000BB; 
		
    GPIOD->CRH &= 0X00000000;
   	GPIOD->CRH |= 0XBBBBBBBB; 		

    GPIOE->CRL &= 0X0FFFFFFF;
   	GPIOE->CRL |= 0XB0000000;
		
	GPIOE->CRH &= 0X00000000;
   	GPIOE->CRH |= 0XBBBBBBBB; 		

    GPIOF->CRL &= 0XFF000000;
   	GPIOF->CRL |= 0X00BBBBBB;
	GPIOF->CRH &= 0X0000FFFF;
   	GPIOF->CRH |= 0XBBBB0000; 
    
	GPIOG->CRL &= 0XFF000000;
   	GPIOG->CRL |= 0X00BBBBBB;
	
	GPIOG->CRH &= 0XFFFFF0FF;
	GPIOG->CRH |= 0X00000B00;   
 	
 	RCC->AHBENR|=1<<8;       //使能FSMC时钟	 
	FSMC_Bank1->BTCR[4]=0X00000000;  //BCR寄存器
    FSMC_Bank1->BTCR[5]=0X00000000;  //BTR寄存器
    FSMC_Bank1E->BWTR[4]=0X00000000;  
	
	  //操作BCR寄存器 
	  //默认是SRAM存储器  BCR[3:2]=00
	FSMC_Bank1->BTCR[4] |= 1;  //使能对应的存储块
	FSMC_Bank1->BTCR[4] |= 1<<4;  //位宽16位
	FSMC_Bank1->BTCR[4] |= 1<<12; //存储器写使能
	
	//操作BTR寄存器(读寄存器)
	//模式A 默认00 
	FSMC_Bank1->BTCR[5] |= 0<<0;  //地址建立时间   1个HCLK
	FSMC_Bank1->BTCR[5] |= 0X00000800;  //数据保持时间   9个HCLK
	  
	  //操作BWTR寄存器  (写寄存器)
//	  FSMC_Bank1E->BWTR[4]  |= 0<<0; //地址建立时间 1个HCLK  
//    FSMC_Bank1E->BWTR[4]  |= 0X00000800; //数据保持时间 9个HCLK   	 				  											
}

//在指定地址(WriteAddr+Bank1_SRAM3_ADDR)开始,连续写入n个字节.
//pBuffer:字节指针
//WriteAddr:要写入的地址
//n:要写入的字节数
void FSMC_SRAM_WriteBuffer(u8* pBuffer,u32 WriteAddr,u32 n)
{
	for(;n!=0;n--)  
	{										    
		*(u8*)(Bank1_SRAM3_ADDR+WriteAddr)=*pBuffer++;	 		
		WriteAddr++;
	}   
}		

//在指定地址((WriteAddr+Bank1_SRAM3_ADDR))开始,连续读出n个字节.
//pBuffer:字节指针
//ReadAddr:要读出的起始地址
//n:要写入的字节数
void FSMC_SRAM_ReadBuffer(u8* pBuffer,u32 ReadAddr,u32 n)
{
	for(;n!=0;n--)  
	{											    
		*pBuffer++=*(u8*)(Bank1_SRAM3_ADDR+ReadAddr);    
		ReadAddr++;
	}  
} 
 
