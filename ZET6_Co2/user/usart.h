#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

void uart2_init(void);
void LED_Init(void); 
extern uint8_t rxbuff[18];  	
void uart_init(u32 bound);




#endif


