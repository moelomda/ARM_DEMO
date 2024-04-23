/*
 * UART_Hal.h
 *
 *  Created on: ???/???/????
 *      Author: Mohamed Elomda
 */
#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "UART.h"
#include "UART.CFG.h"
#ifndef UART_HAL_H_
#define UART_HAL_H_



void UART_HalInit(u32 USART_x);
void USART_HalSendByte( u32 USART_x, u8 USART_BYTE  );
void USART_HalGetByte( u32 USART_x, u8* USART_BYTE );
void Uart_HalTxBufferAsync( u32 USART_x,u8* buffer ,u32 len, TXCBF_t CB);
void Uart_HalRxBufferAsync( u32 USART_x,u8* buffer ,u32 len, RXCBF_t CB);
void UartHalTx_done(void);


#endif /* UART_HAL_H_ */
