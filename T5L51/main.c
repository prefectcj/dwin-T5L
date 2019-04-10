#include "t5los8051.h"
#include "sys.h"







int main(void)
{   
    INIT_CPU();
    T2_Init();
    EA=1;
	while(1)
	{   
        P1_1=!P1_1;
        delay_ms(1000);
	}
}



















