/*
 * uart.h
 *
 *  Created on: Oct 31, 2021
 *      Author: Mahmoud EL-Asmar
 */

#ifndef UART_H_
#define UART_H_
#include"std_types.h"

#define receiver_enable				RXEN
#define transmitter_enable			TXEN
#define string_stop		'#'
#define READY	1
#define NOT_READY 0
typedef enum
{
	none=0,even=2,odd
}parity;

typedef enum
{
	bit_5,bit_6,bit_7,bit_8
}character_size;

typedef struct
{
	uint16 baud_rate;
	parity parity_type;
	character_size ch_size;

}UART_ConfigType;


void UART_init(UART_ConfigType *configurations);
void UART_sendByte(uint8);
uint8 UART_receiveByte();
void UART_sendString(const char*str);
void UART_receiveString(char *str);



#endif /* UART_H_ */
