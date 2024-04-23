/*
 * UART.h
 *
 *  Created on: Mar 30, 2024
 *      Author: LEGION
 */

#ifndef MCAL_UART_H_
#define MCAL_UART_H_
#include"UART.CFG.h"
#include "STD_TYPES.h"






#define USARTID_1                   0
#define USARTID_2                   1
#define USARTID_6                   2


#define USART_WORD_LENGTH_8           0x00000000
#define USART_WORD_LENGTH_9           0x00010000

#define USART_PARITY_DISABLE          0x00000000
#define USART_PARITY_ENABLE           0x00000400

#define USART_PARITY_EVEN             0x00000000
#define USART_PARITY_ODD              0x00000200

#define USART_STOP_BITS_1             0x00000000
#define USART_STOP_BITS_0_5           0x00001000
#define USART_STOP_BITS_2             0x00002000
#define USART_STOP_BITS_1_5           0x00003000

#define USART_OVERSAMPLING_16         0x00000000
#define USART_OVERSAMPLING_8          0x00008000


typedef enum
{
	UART_enuOK ,
	UART_enuNOK

} UART_enuErrorStatus_t ;


typedef void (*TXCBF_t)(void);
typedef void (*RXCBF_t)(void);

UART_enuErrorStatus_t USART_Init( u32 USART_x);
UART_enuErrorStatus_t USART_SendByte( u32 USART_x, u8 USART_BYTE  );
UART_enuErrorStatus_t USART_GetByte( u32 USART_x, u8* USART_BYTE );
UART_enuErrorStatus_t Uart_TxBufferAsync( u32 USART_x,u8* buffer ,u32 len, TXCBF_t CB);
UART_enuErrorStatus_t Uart_RxBufferAsync( u32 USART_x,u8* buffer ,u32 len, RXCBF_t CB);
UART_enuErrorStatus_t UartTx_done(void);

#endif /* MCAL_UART_H_ */
