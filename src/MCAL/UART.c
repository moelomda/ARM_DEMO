/*
 * UART.c
 *
 *  Created on: Mar 30, 2024
 *      Author: LEGION
 */

#include "UART.h"
#include "UART.CFG.h"

#define USART_1                        0x40011000
#define USART_2                        0x40004400
#define USART_6                        0x40011400
#define USART_ENABLE                   0x00002000
#define STOP_BITMASK                   0x00003000
#define FRACTION_OVERFLOW              0x10
#define FIRST_BYTE                     0x0F
#define SECOND_BYTE                    0xF0
#define TX_ENABLE                      0x00000008
#define TXEIE_ENABLE                   0x00000080
#define RX_ENABLE                      0x00000004
#define RXNEIE_ENABLE                  0x00000020
#define TX_DONE                        0x00000080
#define RX_DONE                        0x00000020
#define TC_DONE                        0x00000040
typedef enum
{
	Ready,
	Busy
} Req_State_t;

typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
} USART_Peri_t;


typedef struct
{
	u8 *data;
	u32 pos;
	u32 size;
} buffer_t;

typedef struct
{

	buffer_t buffer;
	Req_State_t state;
	TXCBF_t CallBack;

} TX_Req_t;

typedef struct
{

	buffer_t buffer;
	Req_State_t state;
	RXCBF_t CallBack;

} RX_Req_t;

static volatile USART_Peri_t* const USART_PORTS[] =
{
		(USART_Peri_t* )(USART_1),
		(USART_Peri_t* )(USART_2),
		(USART_Peri_t* )(USART_6)
};

TX_Req_t TX_Req;
RX_Req_t RX_Req;



UART_enuErrorStatus_t USART_Init(u32 USART_x)
{
	UART_enuErrorStatus_t loc_UART_ErrorStatus = UART_enuOK;
	u32 LOC_BRR   ;
	u32 LOC_USARTDIV ;
	u32 LOC_OVERSAMPLING ;
	u32 LOC_Mantissa ;
	u32 LOC_Fraction ;

	u32 LOC_CR1   ;
	u32 LOC_TempCR2  ;

	LOC_OVERSAMPLING = USART_OVERSAMPLING /USART_OVERSAMPLING_8;
	LOC_USARTDIV = (((u64)USART_CLK*1000)/((8*(2-LOC_OVERSAMPLING))*BaudRate)) ;
	LOC_Mantissa = LOC_USARTDIV/1000 ;
	LOC_Fraction = (LOC_USARTDIV % 1000 )*(8*(2-LOC_OVERSAMPLING));

	if (LOC_Fraction % 1000 >= 500)
	{

		LOC_Fraction = (LOC_Fraction / 1000) + 1;
	}
	else
	{
		LOC_Fraction = LOC_Fraction / 1000;
	}

	if (LOC_Fraction >= FRACTION_OVERFLOW)
	{
		LOC_Mantissa += LOC_Fraction & SECOND_BYTE;
	}

	LOC_BRR= (LOC_Mantissa << 4)|(LOC_Fraction & FIRST_BYTE );

	LOC_CR1=(USART_PARITY_TYPE)|(USART_PARITY)|(USART_WORD_LENGTH)|(USART_OVERSAMPLING)|(USART_ENABLE);
	LOC_CR1&=~(0x000000A0);

	(USART_PORTS[USART_x])->BRR = LOC_BRR ;

	(USART_PORTS[USART_x])->CR1 = LOC_CR1;

	LOC_TempCR2=(USART_PORTS[USART_x])->CR2;
	LOC_TempCR2 &=~ STOP_BITMASK ;
	LOC_TempCR2 |=USART_STOP_BITS ;
	(USART_PORTS[USART_x])->CR2 =LOC_TempCR2 ;
	(USART_PORTS[USART_x])->SR = 0;



	return loc_UART_ErrorStatus;
}



UART_enuErrorStatus_t USART_SendByte(u32 USART_x, u8 USART_BYTE  )
{
	UART_enuErrorStatus_t loc_UART_ErrorStatus = UART_enuOK;

	if(TX_Req.state==Ready)
	{

		TX_Req.state=Busy;

		(USART_PORTS[USART_x])->DR = (USART_BYTE) ;
		(USART_PORTS[USART_x])->CR1 |= TX_ENABLE;

		//(USART_PORTS[USART_x])->CR1 |= TX_ENABLE;
		while (((((USART_PORTS[USART_x])->SR) & 0x00000040 )>>6)==0);

		(USART_PORTS[USART_x])->SR &=~ (0x00000040) ;

		(USART_PORTS[USART_x])->CR1 &=~ (0x00000080) ;
		TX_Req.state=Ready;
	}
	return loc_UART_ErrorStatus;
}

UART_enuErrorStatus_t USART_GetByte( u32 USART_x, u8* USART_BYTE )
{
	UART_enuErrorStatus_t loc_UART_ErrorStatus = UART_enuOK;

	if(RX_Req.state==Ready)
	{

		RX_Req.state=Busy;
		(USART_PORTS[USART_x])->CR1 |= RX_ENABLE;
		while(!(((USART_PORTS[USART_x])->SR) & RX_DONE));
		* USART_BYTE=(USART_PORTS[USART_x])->DR ;
		(USART_PORTS[USART_x])->CR1 &=~ RX_ENABLE ;
		RX_Req.state=Ready;
	}

	return loc_UART_ErrorStatus;
}


UART_enuErrorStatus_t Uart_TxBufferAsync(u32 USART_x,u8* buffer ,u32 len, TXCBF_t CB)
{
	UART_enuErrorStatus_t loc_UART_ErrorStatus = UART_enuOK;

	if(TX_Req.state==Ready)
	{
		TX_Req.state=Busy;
		TX_Req.buffer.data=	buffer;
		TX_Req.buffer.size=	len;
		TX_Req.buffer.pos=	0;
		TX_Req.CallBack =	CB;

		(USART_PORTS[USART_x])->CR1 |= TX_ENABLE;
		(USART_PORTS[USART_x])->DR = TX_Req.buffer.data[0] ;
		TX_Req.buffer.pos++;
		(USART_PORTS[USART_x])->CR1 |= TXEIE_ENABLE;

	}




	return loc_UART_ErrorStatus;
}


UART_enuErrorStatus_t Uart_RxBufferAsync(u32 USART_x,u8* buffer ,u32 len, RXCBF_t CB)
{
	UART_enuErrorStatus_t loc_UART_ErrorStatus = UART_enuOK;
u32 loc;

	if(RX_Req.state==Ready)
	{
		(USART_PORTS[USART_x])->CR1 &=~ (0x00000020);
		RX_Req.state=Busy;
		RX_Req.buffer.data=	buffer;
		RX_Req.buffer.size=	len;
		RX_Req.buffer.pos=	0;
		RX_Req.CallBack =	CB;

		//(USART_PORTS[USART_x])->CR1 |= RX_ENABLE;
		loc=(USART_PORTS[USART_x])->CR1;
		loc|= RXNEIE_ENABLE|RX_ENABLE;
		(USART_PORTS[USART_x])->CR1=loc;
		(USART_PORTS[USART_x])->SR &= ~(0x00000020);

	}


	return loc_UART_ErrorStatus;

}


void USART1_IRQHandler(void)
{

	if ((USART_PORTS[USARTID_1])->SR & TC_DONE )
	{
		if (TX_Req.buffer.pos < TX_Req.buffer.size)
		{
			(USART_PORTS[USARTID_1])->DR = TX_Req.buffer.data[TX_Req.buffer.pos] ;
			TX_Req.buffer.pos++;
		}
		else
		{

			(USART_PORTS[USARTID_1])->CR1 &=~ TX_ENABLE;
			(USART_PORTS[USARTID_1])->CR1 &=~ TXEIE_ENABLE;
			TX_Req.state=Ready;

			if(TX_Req.CallBack)
			{
				TX_Req.CallBack();
			}
		}
	}
	if ((USART_PORTS[USARTID_1])->SR & RX_DONE )
	{
		if (RX_Req.buffer.pos < RX_Req.buffer.size)
		{
			RX_Req.buffer.data[RX_Req.buffer.pos] = (USART_PORTS[USARTID_1])->DR ;
			RX_Req.buffer.pos++;
		}
		else
		{

			//(USART_PORTS[USARTID_1])->CR1 &=~ RX_ENABLE;
			(USART_PORTS[USARTID_1])->CR1 &=~ RXNEIE_ENABLE;
			RX_Req.state=Ready;

			if(RX_Req.CallBack)
			{
				RX_Req.CallBack();
			}
		}
		(USART_PORTS[USARTID_1])->SR &= ~(0x00000020);

	}
}

void USART2_IRQHandler(void)
{


	if ((USART_PORTS[USARTID_2])->SR & TC_DONE )
	{
		if (TX_Req.buffer.pos < TX_Req.buffer.size)
		{
			(USART_PORTS[USARTID_2])->DR = TX_Req.buffer.data[TX_Req.buffer.pos] ;
			TX_Req.buffer.pos++;
		}
		else
		{

			(USART_PORTS[USARTID_2])->CR1 &=~ TX_ENABLE;
			(USART_PORTS[USARTID_2])->CR1 &=~ TXEIE_ENABLE;
			TX_Req.state=Ready;

			if(TX_Req.CallBack)
			{
				TX_Req.CallBack();
			}
		}
	}
	if ((USART_PORTS[USARTID_2])->SR & RX_DONE )
	{
		if (RX_Req.buffer.pos < RX_Req.buffer.size)
		{
			RX_Req.buffer.data[RX_Req.buffer.pos] = (USART_PORTS[USARTID_2])->DR ;
			RX_Req.buffer.pos++;
		}
		else
		{

			(USART_PORTS[USARTID_2])->CR1 &=~ RX_ENABLE;
			(USART_PORTS[USARTID_2])->CR1 &=~ RXNEIE_ENABLE;
			RX_Req.state=Ready;

			if(RX_Req.CallBack)
			{
				RX_Req.CallBack();
			}
		}
	}
}


void USART6_IRQHandler(void)
{

	if ((USART_PORTS[USARTID_6])->SR & TC_DONE )
	{
		if (TX_Req.buffer.pos < TX_Req.buffer.size)
		{
			(USART_PORTS[USARTID_6])->DR = TX_Req.buffer.data[TX_Req.buffer.pos] ;
			TX_Req.buffer.pos++;
		}
		else
		{

			(USART_PORTS[USARTID_6])->CR1 &=~ TX_ENABLE;
			(USART_PORTS[USARTID_6])->CR1 &=~ TXEIE_ENABLE;
			TX_Req.state=Ready;

			if(TX_Req.CallBack)
			{
				TX_Req.CallBack();
			}
		}
	}
	if ((USART_PORTS[USARTID_6])->SR & RX_DONE )
	{
		if (RX_Req.buffer.pos < RX_Req.buffer.size)
		{
			RX_Req.buffer.data[RX_Req.buffer.pos] = (USART_PORTS[USARTID_6])->DR ;
			RX_Req.buffer.pos++;
		}
		else
		{

			(USART_PORTS[USARTID_6])->CR1 &=~ RX_ENABLE;
			(USART_PORTS[USARTID_6])->CR1 &=~ RXNEIE_ENABLE;
			RX_Req.state=Ready;

			if(RX_Req.CallBack)
			{
				RX_Req.CallBack();
			}
		}
	}
}

