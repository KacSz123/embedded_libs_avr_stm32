#ifndef USART_H
#define USART_H

#include<stdint-gcc.h>
/////////////////////////////////////	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
// USART MACROS
/////////////////////////////////////

// stop bit
#define STOP_BIT_1 (0<<USBS0)
#define STOP_BIT_2 (1<<USBS0)
#define STOP_BIT STOP_BIT_1

// sync mode
#define ASYNCHRONOUS ((0 << UMSEL00)|(0 << UMSEL01))
#define SYNCHRONOUS  ((1 << UMSEL00)|(0 << UMSEL01))

// bits number
#define BITS_5 ((0 << UCSZ00)|(0 << UCSZ01)|(0 << UCSZ02))//(0<<UCSZ00)
#define BITS_6 ((1 << UCSZ00)|(0 << UCSZ01)|(0 << UCSZ02)) //(1<<UCSZ00)
#define BITS_7 ((0 << UCSZ00)|(1 << UCSZ01)|(0 << UCSZ02)) //(2<<UCSZ00)
#define BITS_8 ((1 << UCSZ00)|(1 << UCSZ01)|(0 << UCSZ02)) //(6<<UCSZ00)
#define BITS_9 ((1 << UCSZ00)|(1 << UCSZ01)|(1 << UCSZ02)) //(7<<UCSZ00)
#define BIT_NUM BITS_8
// transmition mode
#define TRANSMIT_O (1<<TXEN0)
#define RECEIVE_O (1<<RXEN0)
#define TRA_N_REC ((1<<RXEN0)|(1<<TXEN0))
#define USART_MODE TRA_N_REC

// parity
#define NONE ((0 << UPM00) | (0 << UPM01))
#define EVEN ((0 << UPM00) | (1 << UPM01))
#define ODD  ((1 << UPM00) | (1 << UPM01))
#define PARITY_MODE NONE

/*!
 * @brief asfd asfasf as fs
 * 
 * @param usart_baud 
 */
void USART_Init(unsigned long usart_baud);
// #define KURWA "KURWA"

void USART_TransmitByte(uint8_t byte);


void USART_TransmitString(uint8_t *msg);


uint8_t USART_ReceiveByte();


uint8_t* USART_ReceiveString();


#endif //USART_H