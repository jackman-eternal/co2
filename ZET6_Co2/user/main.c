#include "stm32f10x.h"
#include "adc.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"

int main(void)
{
	delay_init();
	Adc_Init();
	uart_init(9600);
	uart2_init();
	NVIC_Configuration();
	int i = 0;
	printf("initalize \r\n");
	while(1)
	{
//		delay_ms(500);
//		printf("serial communicate\r\n");
	  	delay_ms(1000);
	
	}
}


