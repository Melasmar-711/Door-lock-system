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
#define READY			1
#define NOT_READY		0
#define bit_8			3
#define even			2
#define odd				3
#define none			0

typedef struct
{
	uint16 baud_rate;
	uint8 parity_type;
	 uint8 ch_size;

}UART_ConfigType;


void UART_init(UART_ConfigType *configurations);
void UART_sendByte(uint8);
uint8 UART_receiveByte();
void UART_sendString(const char*str);
void UART_receiveString(char *str);



#endif /* UART_H_ */
