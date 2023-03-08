#include "usart.h"	  
uint8_t rxbuff[18];
int i,j;


void uart2_init(void)
{
	USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVUART_InitStructre;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//使能USART2，GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//使能USART2，GPIOA时钟
		//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART2_RX	  GPIOA.3初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
	
	NVUART_InitStructre.NVIC_IRQChannel = USART2_IRQn;
	NVUART_InitStructre.NVIC_IRQChannelCmd = ENABLE;
	NVUART_InitStructre.NVIC_IRQChannelPreemptionPriority = 2;
	NVUART_InitStructre.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVUART_InitStructre);
 
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = 9600;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART2,&USART_InitStructure); //初始化串口
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//开启串口接受中断
	//USART_ITConfig(USART2,USART_IT_IDLE,ENABLE );
	USART_Cmd(USART2,ENABLE);                    //使能串口
}
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}	
   
    return ch;
}  
void uart_init(u32 bound)
{
  //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
    //USART1_RX	  GPIOA.10初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
  
	NVIC_InitStructure.NVIC_IRQChannel  = USART1_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStructure);
	
    //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    
		USART_ITConfig(USART1 ,USART_IT_RXNE,DISABLE ); 
    USART_Init(USART1, &USART_InitStructure);     //初始化串口1	
    USART_Cmd(USART1, ENABLE);                    //使能串口1 
}

void LED_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC ,ENABLE );
   
    
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8 |GPIO_Pin_11|GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_Init(GPIOA ,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOA , GPIO_Pin_8 |GPIO_Pin_11) ;
	GPIO_SetBits(GPIOA ,GPIO_Pin_13 ); 
	
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz ;
    GPIO_Init(GPIOC ,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOC , GPIO_Pin_8 |GPIO_Pin_7) ;
}


//void USART1_IRQHandler(void )
//{
//	uint8_t temp;
//	if(USART_GetITStatus(USART1 ,USART_IT_RXNE )==SET  )
//	{
//		temp = USART_ReceiveData(USART1 );
//	}
//    USART_ClearITPendingBit(USART1 ,USART_IT_RXNE ); 		
//	
//}


void USART2_IRQHandler(void )
{
	if(USART_GetITStatus(USART2 ,USART_IT_RXNE )==SET  )
	{
	  USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		rxbuff[i++] = USART_ReceiveData(USART2 );
		if(i>=2)
		{
				if(rxbuff[0] == 0x20 && rxbuff[1] == 0x5a) //接收帧头
				{
					if(rxbuff[i] == 0x0a&&rxbuff[i-1]==0x0d)
					{
							i = 0;
						  memset(rxbuff,0,18);
					}
				}
				else
				{
					i = 0;
					memset(rxbuff,0,18);
				}
		}
		if(i>=18)
		{
				for(j=0;j<18;j++)
			{
				printf("j = %d,d = %x \r\n",j,rxbuff[j]);
			}
			i = 0;memset(rxbuff,0,18);
		}
	}
}

/*
void USART2_IRQHandler(void)       //串口中断服务函数
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        rxbuff [i++] = USART_ReceiveData(USART1);
    }
    if(i >=  18 )
    {
			
        i = 0;             //接收缓冲区溢出，重新开始接收
       memset(rxbuff,0,18);
    }
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)        //当前为接收到一帧完整的数据包
    {
        USART2->SR;  //先读SR
        USART2->DR;  //再度DR  清除帧空闲中断标志位
        //此处为数据包处理逻辑

			  for(i=0;i<18;i++)
			{
				printf("i = %d ,d = %x \r\n",i ,rxbuff[i]);
			}
        i = 0;
       memset(rxbuff,0,18);

    }
}		
	*/	
/*
void UART2_IRQHandler(void)                	//串口1中断服务程序
{
	static u8 res;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET)
	{
		res=USART_ReceiveData(USART2);//接收数据
		Ultrasound[1]=(Ultrasound[1]<<8)|res;
		if((Ultrasound[1]&0xFF0000FF)==0xA50000A5)
			Trailing[1] = (u16)((Ultrasound[1]&0x00FFFF00)>>8);
		
				
	   USART_ClearFlag(USART2, USART_IT_RXNE);//清除中断标志位
	 }
}
*/

/*
void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //开启DMA时钟
	
	DMA_InitStructure.DMA_BufferSize = 8;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC   ;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte ;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable ;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal   ;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR); 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte ;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable ;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High ;
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  =2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority  =2;
	NVIC_Init(&NVIC_InitStructure) ;	
	
	DMA_Init(DMA1_Channel5 ,&DMA_InitStructure); 
	DMA_ITConfig(DMA1_Channel5,DMA_IT_TC,DISABLE ); 
	DMA_Cmd(DMA1_Channel5,ENABLE);
}
*/

int getc(FILE *f)
{
	/* 等待串口输入数据 */
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	/* 返回值进行强制类型转换 */
	return (int)USART_ReceiveData(USART1);
}



