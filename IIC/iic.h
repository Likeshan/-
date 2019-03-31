#ifndef __IIC_H
#define __IIC_H
#include "sys.h"
 
/* 

		使用OLED时将倒数两行注释取消！！

*/ 		   
//IO方向设置
#define SDA_IN()  {GPIOC->CRH&=0XFFFFFF0F;GPIOC->CRH|=0X00000080;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFFFF0F;GPIOC->CRH|=0X00000030;}

//IO操作函数	 
#define IIC_SCL    PCout(10) //SCL
#define IIC_SDA    PCout(9) //SDA	 
#define READ_SDA   PCin(9)  //输入SDA 

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);								//发送IIC开始信号
void IIC_Stop(void);	  						//发送IIC停止信号
void IIC_Send_Byte(u8 txd);					//IIC发送一个字节
u8 IIC_Wait_Ack(void); 							//IIC等待ACK信号
void IIC_Ack(void);									//IIC发送ACK信号
void IIC_NAck(void);								//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);	  

//void OLED_WriteOneByte(u8 WriteAddr,u8 DataToWrite);		     //指定地址写入一个字节
//u8 OLED_Check(void);  //检查器件
#endif
