#ifndef __SYS_H__
#define __SYS_H__

#include "t5los8051.h"


typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
typedef char            s8;
typedef short           s16;
typedef int             s32;



//宏定义
#define	WDT_ON()	MUX_SEL|=0x02		/******开启看门狗*********/
#define	WDT_OFF()	MUX_SEL&=0xFD		/******关闭看门狗*********/
#define	WDT_RST()	MUX_SEL|=0x01		/******喂狗*********/


#define FOSC     206438400UL
#define T1MS    (65536-FOSC/12/1000)

sbit P3_2=P3^2;
sbit P1_0=P1^0;
sbit P1_1=P1^1;


extern u16 count;




void delays_ms(u16 n);
void INIT_CPU(void);
void T0_Init(void);
void T2_Init(void);
void read_dgusii_vp(int addr,char* buf,int len);
void write_dgusii_vp(int addr,char* buf,int len);
void delay_ms(u16 n);









#endif


