/*
 * uart.c
 *
 *  Created on: Oct 31, 2021
 *      Author: Mahmoud EL-Asmar
 */
#include"uart.h"
#include"common_macros.h"
#include<avr/io.h>
#include<avr/interrupt.h>


uint8 data_received;

void UART_init(UART_ConfigType* configurations)
{
	uint16 ubrr_value=0;
	SREG=(1<<7);
	UCSRA=(1<<U2X);	/*double transmission speed*/
	/*RXCIE -->when receiving a byte is complete an interrupt happens that return the byte
	 * RXEN--->receiver enable
	 * TXEN---> transmitter enable
	 * */
	UCSRB|=(1<<receiver_enable)|(1<<transmitter_enable);
	/*
	 * this sets the character size of the data
	 * */
	UCSRC=(1<<URSEL)|((configurations->ch_size)<<UCSZ0)|((configurations->parity_type)<<UPM0);
	/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / ((configurations->baud_rate) * 8UL))) - 1);
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;



}

void UART_sendByte(uint8 data)
{
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR=data;

}
uint8 UART_receiveByte()
{
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return UDR;
}
void UART_sendString(const char*str)
{
	uint8 i = 0;

		/* Send the whole string */
		while(str[i] != '\0')
		{
			UART_sendByte(str[i]);
			i++;
		}

}
void UART_receiveString(char *str)
{
	uint8 i=0;
	str[i]=UART_receiveByte();
	while(str[i]!=string_stop)
	{
		i++;
		str[i]=UART_receiveByte();
	}
	str[i]='\0';
}
