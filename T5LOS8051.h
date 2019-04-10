#ifndef __T5LOS8051_H__
#define __T5LOS8051_H__


sfr	P0		=	0x80;		/********PO口*******/
sfr	SP		=	0x81;		/********堆栈指针*******/
sfr DPL		=	0x82;		/********DPTR数据指针*******/
sfr DPH		=	0x83;		/********DPTR数据指针*******/
sfr PCON	=	0x87;		/********.7 UART2波特率设置*******/
sfr TCON	=	0x88;		/********T0 T1控制寄存器*******/

sbit	TF1 =	TCON^7;		/********T1中断触发*******/
sbit	TR1	=	TCON^6;		
sbit	TF0	=	TCON^5;		/********T0中断触发*******/
sbit	TR0	=	TCON^4;
sbit	IE1	=	TCON^3;		/********外部中断1*******/
sbit	IT1	=	TCON^2;		/********外部中断1触发方式	0：低电平触发		1：下降沿触发*******/
sbit	IE0	=	TCON^1;		/********外部中断0*******/
sbit	IT0	=	TCON^0;		/********外部中断0触发方式	0：低电平触发		1：下降沿触发*******/

sfr	TMOD	=	0x89;		/********T0 T1模式选择,同8051*******/
sfr	TH0 	=	0x8C;		
sfr TL0 	=	0x8A;
sfr TH1 	=	0x8D;
sfr TL1 	=	0x8B;

sfr CKCON	=	0x8E;		/********CPU运行*******/
sfr	P1		=	0x90;
sfr	DPC		=	0x93;		/********MOVX指令后，DPTR的变化模式	0：不变 1：+1  2：-1*******/
sfr PAGESEL	=	0x94;		/********必须是0x01*******/
sfr	D_PAGESEL	=	0x95;	/********必须是0x02*******/

sfr SCON0	=	0x98;		/********UART2控制接口，同8051*******/
sbit	TI0	=	SCON0^1;
sbit	RI0	=	SCON0^0;
sfr	SBUF0	=	0x99;		/********UART2收发数据接口*******/
sfr	SREL0H	=	0xBA;		/********设置波特率，当ADCON为0x80时*******/
sfr	SREL0L	=	0xAA;

sfr	SCON1	=	0x9B;		/********UART3控制接口*******/
sfr	SBUF1	=	0x9C;
sfr	SREL1H	=	0xBB;
sfr	SREL1L	=	0x9D;

sfr	IEN2	=	0x9A;		/********中断使能控制器SFR  .7~.1必须写0		.0 UART3中断使能控制位*******/
sfr	P2		=	0xA0;
sfr	IEN0	=	0xA8;		/********中断使能控制器0*******/
sbit	EA	=	IEN0^7;		/********中断总控制位*******/
sbit	ET2	=	IEN0^5;		/********定时器2中断控制位*******/
sbit	ES0	=	IEN0^4;		/********UART2*******/
sbit	ET1	=	IEN0^3;		/********T1*******/
sbit	EX1	=	IEN0^2;		/********外部中断1*******/
sbit	ET0	=	IEN0^1;		/********T0*******/
sbit	EX0	=	IEN0^0;		/********外部中断0*******/

sfr	IP0		=	0xA9;				/********中断优先级控制器0*******/
sfr	P3		=	0xB0;
sfr	IEN1	=	0xB8;				/********中断使能接受控制器******/
sbit	ES3R	=	IEN1^5;			/*****UART5接受中断使能控制位****/
sbit	ES3T	=	IEN1^4;			/*****UART5接受中断使能控制位****/
sbit	ES2R	=	IEN1^3;			/*****UART4接受中断使能控制位****/
sbit	ES2T	=	IEN1^2;			/*****UART4接受中断使能控制位****/
sbit	ECAN	=	IEN1^1;			/********CAN中断使能控制位******/

sfr	IP1		=	0xB9;				/********中断优先级控制器0*******/
sfr	IRCON2	=	0xBF;
sfr	IRCON 	=	0xC0;
sbit	TF2	=	IRCON^6;			/********T2中断触发标志*******/
sfr	T2CON	=	0xC8;				/********T2控制寄存器********/
sbit	TR2	=	T2CON^0;			/***********T2使能***********/
sfr	TRL2H	=	0xCB;
sfr	TRL2L	=	0xCA;
sfr	TH2 	=	0xCD;
sfr	TL2 	=	0xCC;

sfr	PSW		=	0xD0;
sbit	CY	=	PSW^7;
sbit	AC	=	PSW^6;
sbit	F0	=	PSW^5;
sbit	RS1	=	PSW^4;
sbit	RS0	=	PSW^3;
sbit	OV	=	PSW^2;
sbit	F1	=	PSW^1;
sbit	P	=	PSW^0;
sfr	ADCON	=	0xD8;
sfr	ACC		=	0xE0;
sfr	B 		=	0xF0;

/******硬件扩展定义*********/
/******DGUS变量存储器访问*********/
sfr	RAMMODE	=	0xF8;				/******DGUS变量存储器访问接口控制寄存器*********/
sbit	APP_REQ	=	RAMMODE^7;
sbit	APP_EN	=	RAMMODE^6;
sbit	APP_RW	=	RAMMODE^5;
sbit	APP_ACK	=	RAMMODE^4;
sfr ADR_H	=	0xF1;
sfr ADR_M	=	0xF2;
sfr ADR_L	=	0xF3;
sfr ADR_INC	=	0xF4;
sfr DATA3	=	0xFA;
sfr DATA2	=	0xFB;
sfr DATA1	=	0xFC;
sfr DATA0	=	0xFD;


//UART4
sfr	SCON2T	=	0x96;					/******UART4发送控制********/
sfr	SCON2R	=	0x97;					/******UART4接收控制*********/
sfr	BODE2_DIV_H	=	0xD9;				/******波特率设置********/
sfr	BODE2_DIV_L	=	0xE7;
sfr	SBUF2_TX	=	0x9E;				/******UART4发送数据接口********/
sfr	SBUF2_RX	=	0x9F;				/******UART4接收数据接口*********/

//UART5
sfr	SCON3T	=	0xA7;					
sfr	SCON3R	=	0xAB;
sfr	BODE3_DIV_H	=	0xAE;
sfr	BODE3_DIV_L	=	0xAF;
sfr	SBUF3_TX	=	0xAC;
sfr	SBUF3_RX	=	0xAD;

//CAN通信
sfr	CAN_CR	=	0x8F;
sfr	CAN_IR	=	0x91;
sfr	CAN_ET	=	0xE8;

//GPIO
sfr	P0MDOUT	=	0xB7;
sfr	P1MDOUT	=	0xBC;
sfr	P2MDOUT	=	0xBD;
sfr	P3MDOUT	=	0xBE;
sfr	MUX_SEL	=	0xC9;
sfr	PORTDRV	=	0xF9;				/******输出驱动强度*********/

//MAC&DIV
sfr	MAC_MODE	=	0xE5;
sfr	DIV_MODE	=	0xE6;

//SFR扩展接口
sfr	EXADR	=	0xFE;
sfr	EXDATA	=	0xFF;





#endif


