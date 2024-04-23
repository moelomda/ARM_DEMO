/*
 * UART_Hal.c
 *
 *  Created on: ???/???/????
 *      Author: Mohamed Elomda
 */

#include "UART_Hal.h"
#define UART1_TX  0
#define UART1_RX  1
#define UART2_TX  2
#define UART2_RX  3
#define UART6_TX  4
#define UART6_RX  5
GPIO_t UART_CH[6]=
{
  [UART1_TX]=
  {
			 .GPIO_PORT =  GPIOB,
			 .GPIO_PIN  =  GPIO_PIN6,
			 .GPIO_MODE = GPIO_AF_PP,
			 .GPIO_SPEED = GPIO_HIGH_SPEED ,
  },
  [UART1_RX]=
  {
		     .GPIO_PORT =  GPIOB,
			 .GPIO_PIN  =  GPIO_PIN7,
			 .GPIO_MODE =  GPIO_AF_PP,
			 .GPIO_SPEED = GPIO_HIGH_SPEED ,


  },
  [UART2_TX]=
  {
			 .GPIO_PORT =  GPIOA,
			 .GPIO_PIN  =  GPIO_PIN2,
			 .GPIO_MODE =  GPIO_AF_PP,
			 .GPIO_SPEED = GPIO_HIGH_SPEED,


  },
  [UART2_RX]=
  {
	     .GPIO_PORT =  GPIOA,
		 .GPIO_PIN  =  GPIO_PIN3,
		 .GPIO_MODE =  GPIO_AF_PP,
		 .GPIO_SPEED = GPIO_HIGH_SPEED ,


  },
  [UART6_TX]=
  {
			     .GPIO_PORT =  GPIOC,
				 .GPIO_PIN  =  GPIO_PIN6,
				 .GPIO_MODE = GPIO_AF_PP,
				 .GPIO_SPEED = GPIO_HIGH_SPEED,
  },
  [UART6_RX]=
  {
		     .GPIO_PORT =  GPIOC,
			 .GPIO_PIN  =  GPIO_PIN7,
			 .GPIO_MODE =  GPIO_AF_PP,
			 .GPIO_SPEED = GPIO_HIGH_SPEED,
  }


};
void UART_HalInit(u32 USART_x)
{


  if(USART_x == USARTID_1)
  {
	  GPIO_AF_CFG(GPIOB,GPIO_PIN6,GPIO_AF7_USART1_2);
	  GPIO_AF_CFG(GPIOB,GPIO_PIN7,GPIO_AF7_USART1_2);
	  RCC_EnablePeri(RCC_AHB1,GPIOAEN);
	  RCC_EnablePeri(RCC_APB2,USART1EN);
	  GPIO_INITPIN(&UART_CH[UART1_TX]);
	  GPIO_INITPIN(&UART_CH[UART1_RX]);
	  NVIC_CTRL_EnableIRQ(NVIC_USART1_INTERRUPT);

  }
  else if (USART_x== USARTID_2)
  {
	  GPIO_AF_CFG(GPIOA,GPIO_PIN2,GPIO_AF7_USART1_2);
	  GPIO_AF_CFG(GPIOA,GPIO_PIN3,GPIO_AF7_USART1_2);
	  RCC_EnablePeri(RCC_AHB1,GPIOAEN);
	  RCC_EnablePeri(RCC_APB1,USART2EN);
	  GPIO_INITPIN(&UART_CH[UART2_TX]);
	  GPIO_INITPIN(&UART_CH[UART2_RX]);
	  NVIC_CTRL_EnableIRQ(NVIC_USART2_INTERRUPT);

  }
  else if (USART_x == USARTID_6)
  {
	     GPIO_AF_CFG(GPIOC,GPIO_PIN6,GPIO_AF8_USART6);
	     GPIO_AF_CFG(GPIOC,GPIO_PIN7,GPIO_AF8_USART6);
	     RCC_EnablePeri(RCC_AHB1,GPIOCEN);
	     RCC_EnablePeri(RCC_APB2,USART6EN);
	     GPIO_INITPIN(&UART_CH[UART6_TX]);
	     GPIO_INITPIN(&UART_CH[UART6_RX]);
	     NVIC_CTRL_EnableIRQ(NVIC_USART6_INTERRUPT);

  }
  else
  {

  }
  USART_Init(USART_x);
}
void  USART_HalSendByte( u32 USART_x, u8 USART_BYTE  )
{
	USART_SendByte(  USART_x,  USART_BYTE  );
}
void USART_HalGetByte( u32 USART_x, u8* USART_BYTE )
{
	USART_GetByte(USART_x, USART_BYTE );
}
void Uart_HalTxBufferAsync( u32 USART_x,u8* buffer ,u32 len, TXCBF_t CB)
{
	Uart_TxBufferAsync(  USART_x,buffer ,len,  CB);
}
void Uart_HalRxBufferAsync( u32 USART_x,u8* buffer ,u32 len, RXCBF_t CB)
{
	Uart_RxBufferAsync( USART_x, buffer , len,  CB);
}
void UartHalTx_done(void)
{
	UartTx_done();
}
