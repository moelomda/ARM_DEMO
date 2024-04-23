/*
 * UART.CFG.h
 *
 *  Created on: Mar 31, 2024
 *      Author: LEGION
 */

#ifndef MCAL_UART_CFG_H_
#define MCAL_UART_CFG_H_

#include "UART.h"

#define USART_CLK              16000000
#define BaudRate               9600      /* can choose 9600 or 115200 */

#define USART_WORD_LENGTH      USART_WORD_LENGTH_8
#define USART_PARITY           USART_PARITY_DISABLE
#define USART_PARITY_TYPE      USART_PARITY_DISABLE
#define USART_STOP_BITS        USART_STOP_BITS_1
#define USART_OVERSAMPLING     USART_OVERSAMPLING_16


#endif /* MCAL_UART_CFG_H_ */
