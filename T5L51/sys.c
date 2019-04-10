#include "sys.h"
#include <intrins.h>


u16 count=0;
static u16 SysTick=0;


 /**
    * @brief 软件ms延时
    *   软件延时    振荡周期T=1/206438400 
    * @param [in] 
    *      n:延时ms
    * @param [out]
    *      无
    * @retval 
    *      无
    */
void delays_ms(u16 n)
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<17203;j++);    
}



 /**
    * @brief INIT CPU
    *   初始化OS的外设，其中有初始化UART2,UART3，关闭开门狗，IO口驱动强度+/-8mA
    *   UART4，UART5，定时器T0 T1 T2，只开启UART2/UART3,其余外设没有开启
    * @param  无
    *
    *   
    * @retval   无
    * 
    */  
void INIT_CPU(void)
{
    EA=0;
    RS0=0;
    RS1=0;
    //SP=0xC0;

    CKCON=0x00;
    T2CON=0x70;
    DPC=0x00;
    PAGESEL=0x01;
    D_PAGESEL=0x02;   //DATA RAM  0x8000-0xFFFF
    MUX_SEL=0x60;   //UART2,UART2开启，WDT关闭
    RAMMODE=0x00;
    PORTDRV=0x01;   //驱动强度+/-8mA
    IEN0=0x00;      //关闭所有中断
    IEN1=0x00;
    IEN2=0x00;
    IP0=0x00;      //中断优先级默认
    IP1=0x00;

    WDT_OFF();      //关闭开门狗

    //IO口配置
    P0=0x00;
    P1=0x00;
    P2=0x00;
    P3=0x00;
    P0MDOUT=0x50;
    P1MDOUT=0xFF;
    P2MDOUT=0x00; 
    P3MDOUT=0x0F;

    //UART2配置8N1  15200
    ADCON=0x80;
    SCON0=0x50;
    SREL0H=0x03;        //FCLK/64*(1024-SREL1)
    SREL0L=0xE4;

    //UART3配置8N1   115200
    SCON1=0x50;
    SREL1H=0x03;       //FCLK/64*(1024-SREL1)
    SREL1L=0xC8;

    //UART4配置8N1      115200
    SCON2T=0x80;
    SCON2R=0x80;
    BODE2_DIV_H=0x00;     //FCLK/8*DIV
    BODE2_DIV_L=0xE0;

    //UART5配置8N1      115200
    SCON3T=0x80;
    SCON3R=0x80;
    BODE3_DIV_H=0x00;       //FCLK/8*DIV
    BODE3_DIV_L=0xE0;

    
    TMOD=0x11;          //16位定时器
    //T0
    TH0=0x00;
    TL0=0x00;
    TR0=0x00;

    //T1
    TH1=0x00;
    TL1=0x00;
    TR1=0x00;
    
    TCON=0x05;      //外部中断下降沿触发

    //T2  Autoload模式
    T2CON=0x70;
    TH2=0x00;
    TL2=0x00;
    TRL2H=0xBC;
    TRL2L=0xCD;        //1ms的定时器

}

 /**
    * @brief 定时器T0初始化
    *        初始化定时器T0，定时间隔为1ms
    * @param [in] 
    *      无
    * @param [out]
    *      无
    * @retval 
    *      无
    */
void T0_Init(void)
{
    TMOD|=0x01;
    TH0=T1MS>>8;        //1ms定时器
    TL0=T1MS;
    ET0=1;              //开启定时器0中断
    EA=1;               //开总中断
    TR0=1;              //开启定时器
}

 /**
    * @brief 定时器T2初始化
    *        初始化定时器T2，定时间隔为1ms
    * @param [in] 
    *      无
    * @param [out]
    *      无
    * @retval 
    *      无
    */
void T2_Init(void)
{
    T2CON=0x70;
    TH2=0x00;
    TL2=0x00;
    TRL2H=0xBC;
    TRL2L=0xCD;        //1ms的定时器
    IEN0|=0x20;     //开启定时器2
    TR2=0x01;
}


 /**
    * @brief 读DGUS II VP数据
    *        一次读写必须是4个字节，因为读写len长度是以字为单位，
    *       所以读写数据分为4中不同情况，情况不同，读写不一样
    * @param [in] 
    *      addr:VP首地址
    *      len: 读VP字长度
    * @param [out]
    *      buf:读取数据保存，buf字节长度为len*2
    * @retval 
    *      无
    */  
void read_dgusii_vp(int addr,char* buf,int len)
{
    int OS_addr=0,OS_addr_offset=0;
    int OS_len=0,OS_len_offset=0;
    EA=0;
    OS_addr=addr/2;
    OS_addr_offset=addr%2;
    ADR_H=(u8)(OS_addr>>16)&0xFF;
    ADR_M=(u8)(OS_addr>>8)&0xFF;
    ADR_L=(u8)OS_addr&0xFF;
    ADR_INC=1;                 //DGUS  OS存储器地址在读写后自动加1
    RAMMODE=0xAF;               //启动读模式
    if(OS_addr_offset==1)       //首地址有偏移，修正
    {
        while(APP_ACK==0);      //等待
        APP_EN=1;
        while(APP_EN==1); 
        *buf++=DATA1;
        *buf++=DATA0;              
        len--;
        OS_addr_offset=0;
    }
    OS_len=len/2;
    OS_len_offset=len%2;
    if(OS_len_offset==1)
    {
         OS_len++;
    }
    while(OS_len--)
    {
        if((OS_len_offset==1)&&(OS_len==0))
        {           
            while(APP_ACK==0);
            APP_EN=1;
            while(APP_EN==1);       //读写执行结束
            *buf++=DATA3;
            *buf++=DATA2;           
            break;    
        } 
        while(APP_ACK==0);
        APP_EN=1;
        while(APP_EN==1);       //读写执行结束 
        *buf++=DATA3;
        *buf++=DATA2;
        *buf++=DATA1;
        *buf++=DATA0;                          
    }   
    RAMMODE=0x00;           //读写完成后RAMMODE必须置零
    EA=1;         
}


 /**
    * @brief 写DGUS II VP数据
    *        一次读写必须是4个字节，因为读写len长度是以字为单位，
    *       所以读写数据分为4中不同情况，情况不同，读写不一样
    * @param [in] 
    *      addr:VP首地址
    *      len: 写VP字长度
    * @param [out]
    *      buf:读取数据保存，buf字节长度为len*2
    * @retval 
    *      无
    */ 
void write_dgusii_vp(int addr,u8* buf,int len)
{
    int OS_addr=0,OS_addr_offset=0;
    int OS_len=0,OS_len_offset=0;
    EA=0;
    OS_addr=addr/2;
    OS_addr_offset=addr%2; 
    ADR_H=(u8)(OS_addr>>16)&0xFF;
    ADR_M=(u8)(OS_addr>>8)&0xFF;
    ADR_L=(u8)OS_addr&0xFF;
    ADR_INC=0x01;                 //DGUS  OS存储器地址在读写后自动加1
    RAMMODE=0x8F;               //启动写模式 
    if(OS_addr_offset==1)
    {
        ADR_INC=0;                     
        RAMMODE=0xAF;
        while(APP_ACK==0);
        APP_EN=1;
        while(APP_EN==1);       //读写执行结束
        ADR_INC=0x01; 
        RAMMODE=0x8F;
        while(APP_ACK==0);      
        DATA1=*buf++;
        DATA0=*buf++;
        APP_EN=1;
        while(APP_EN==1);       //读写执行结束
        len--;
        OS_addr_offset=0;
    }
    OS_len=len/2;
    OS_len_offset=len%2; 
    if(OS_len_offset==1)
    {
         OS_len++;
    } 
    while(OS_len--)
    {
        if((OS_len_offset==1)&&(OS_len==0))
        {
            ADR_INC=0;
            RAMMODE=0xAF;
            while(APP_ACK==0);
            APP_EN=1;                //增加一个读过程，以免写单字时会将另一个单字写0
            while(APP_EN==1);       //读写执行结束
            ADR_INC=0x01;
            RAMMODE=0x8F;
            while(APP_ACK==0);           
            DATA3=*buf++;
            DATA2=*buf++;
            APP_EN=1;
            while(APP_EN==1);       //读写执行结束
            break;
        }
        while(APP_ACK==0);        
        DATA3=*buf++;
        DATA2=*buf++;
        DATA1=*buf++;
        DATA0=*buf++;
        APP_EN=1;
        while(APP_EN==1);       //读写执行结束
    } 
    RAMMODE=0x00;       //读写完成后RAMMODE必须置零
    EA=1;  
}  




 /**
    * @brief 中断处理函数，中断号已经定义好了，不需要再进行修改
    *        using n:可以不需要，因为OS CPU的处理已经很快了，尽量不要中断嵌套
    *       已经改成了接口函数的定时，是否需要增加interrupt n，这个需要在确认下，有板子后，可以测试下
    * @param [in] 
    *      无
    * @param [out]
    *      无
    * @retval 
    *      无
    */ 
void EX0_ISR_PC(void)    interrupt 0
{
    EA=0;
    //code
    EA=1;
}


 /**
    * @brief 定时器T0中断处理函数
    *        用户自己定义
    * @param [in] 
    *      无
    * @param [out]
    *      无
    * @retval 
    *      无
    */
void T0_ISR_PC(void)    interrupt 1
{
    static u16 i=0;
    EA=0;
    TH0=T1MS>>8;
    TL0=T1MS;
    i++;
    if(i>=1000)
    {
        i=0;
        P1_0=!P1_0;        
        count++; 
    }          
    EA=1;
}

void EX1_ISR_PC(void)    interrupt 2
{
    EA=0;
    //code
    EA=1;
}

void T1_ISR_PC(void)    interrupt 3
{
    EA=0;
    //code
    EA=1;
}

void UART2_ISR_PC(void)    interrupt 4
{
    EA=0;
    //code
    EA=1;
}


 /**
    * @brief 定时器T2延时
    *   定时器T2延时，精准延时 
    * @param [in] 
    *      n:延时ms
    * @param [out]
    *      无
    * @retval 
    *      无
    */
void delay_ms(u16 n)
{
    SysTick=n;
    while(SysTick)
    {
        if(ET2==0)
        {   
            SysTick--;
            ET2=1;
        }
    }    
}

void T2_ISR_PC(void)    interrupt 5
{
    TF2=0;    
    SysTick--;    
}


void CAN_ISR_PC(void)    interrupt 9
{
    EA=0;
    //code
    EA=1;
}

void UART4_TX_ISR_PC(void)    interrupt 10
{
    EA=0;
    //code
    EA=1;
}

void UART4_RX_ISR_PC(void)    interrupt 11
{
    EA=0;
    //code
    EA=1;
}

void UART5_TX_ISR_PC(void)    interrupt 12
{
    EA=0;
    //code
    EA=1;
}

void UART5_RX_ISR_PC(void)    interrupt 13
{
    EA=0;
    //code
    EA=1;
}

void UART3_ISR_PC(void)    interrupt 16
{
    EA=0;
    //code
    EA=1;
}










