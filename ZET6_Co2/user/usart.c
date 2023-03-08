#include "usart.h"	  
uint8_t rxbuff[18];
int i,j;


void uart2_init(void)
{
	USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVUART_InitStructre;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART2��GPIOAʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//ʹ��USART2��GPIOAʱ��
		//USART2_TX   GPIOA.2
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART2_RX	  GPIOA.3��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
	
	NVUART_InitStructre.NVIC_IRQChannel = USART2_IRQn;
	NVUART_InitStructre.NVIC_IRQChannelCmd = ENABLE;
	NVUART_InitStructre.NVIC_IRQChannelPreemptionPriority = 2;
	NVUART_InitStructre.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVUART_InitStructre);
 
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = 9600;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART2,&USART_InitStructure); //��ʼ������
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);//�������ڽ����ж�
	//USART_ITConfig(USART2,USART_IT_IDLE,ENABLE );
	USART_Cmd(USART2,ENABLE);                    //ʹ�ܴ���
}
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}	
   
    return ch;
}  
void uart_init(u32 bound)
{
  //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
    //USART1_RX	  GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  
  
	NVIC_InitStructure.NVIC_IRQChannel  = USART1_IRQn ;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
	NVIC_Init(&NVIC_InitStructure);
	
    //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    
		USART_ITConfig(USART1 ,USART_IT_RXNE,DISABLE ); 
    USART_Init(USART1, &USART_InitStructure);     //��ʼ������1	
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
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
				if(rxbuff[0] == 0x20 && rxbuff[1] == 0x5a) //����֡ͷ
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
void USART2_IRQHandler(void)       //�����жϷ�����
{
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        rxbuff [i++] = USART_ReceiveData(USART1);
    }
    if(i >=  18 )
    {
			
        i = 0;             //���ջ�������������¿�ʼ����
       memset(rxbuff,0,18);
    }
    if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)        //��ǰΪ���յ�һ֡���������ݰ�
    {
        USART2->SR;  //�ȶ�SR
        USART2->DR;  //�ٶ�DR  ���֡�����жϱ�־λ
        //�˴�Ϊ���ݰ������߼�

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
void UART2_IRQHandler(void)                	//����1�жϷ������
{
	static u8 res;
	if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET)
	{
		res=USART_ReceiveData(USART2);//��������
		Ultrasound[1]=(Ultrasound[1]<<8)|res;
		if((Ultrasound[1]&0xFF0000FF)==0xA50000A5)
			Trailing[1] = (u16)((Ultrasound[1]&0x00FFFF00)>>8);
		
				
	   USART_ClearFlag(USART2, USART_IT_RXNE);//����жϱ�־λ
	 }
}
*/

/*
void DMA_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE); //����DMAʱ��
	
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
	/* �ȴ������������� */
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	/* ����ֵ����ǿ������ת�� */
	return (int)USART_ReceiveData(USART1);
}



