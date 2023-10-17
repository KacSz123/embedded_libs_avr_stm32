
#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
#include "usart.h"

void USART_Init(unsigned long usart_baud)
{


	unsigned long baud = (((F_CPU / (usart_baud * 16UL))) - 1);
	// Set Baud Rate
	UBRR0H = baud >> 8;
	UBRR0L = baud;

	// Set Frame Format: Asynchronous,parity: None  ; 1stop Bit  ;
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | BIT_NUM;

	// Enable Receiver and Transmitter
	UCSR0B = USART_MODE;
}

void USART_TransmitByte(uint8_t byte)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;

#if BIT_NUM == BITS_9 // only if data frame is 9bits long
	/* Copy 9th bit to TXB8 */
	UCSR0B &= ~(1 << TXB80);
	if (byte & 0x0100)
		UCSR0B |= (1 << TXB80);
		/* Put data into buffer, sends the data */
#endif

	UDR0 = byte;
}
void USART_TransmitString(uint8_t *msg)
{
	uint8_t *byte = msg;
	for (unsigned int i = 0; i < strlen((char *)msg); ++i)
		USART_TransmitByte(*(byte + i));

	////234234 23 423 42 3
}

