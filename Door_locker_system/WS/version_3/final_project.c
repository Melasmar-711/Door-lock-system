/*
 * final_project.c
 *
 *  Created on: Oct 31, 2021
 *      Author: Mahmoud EL-Asmar
 */


#include"util/delay.h"
#include"uart.h"
#include"timer0.h"
#include<avr/io.h>
#include <avr/interrupt.h>
#include "external_eeprom.h"
#include "uart_readyBytes.h"
#include"application_status.h"
#include"twi.h"
#include"dcmotor.h"
#include"buzzer.h"







int main()
{
	uint8 i=0;
	uint8 password[8];
	uint8 password_check[8];
	uint8 check_byte;
	uint16 adresses[]={0x0311,0x0312,0x0313,0x0314};


	/*I2C init*/
	TWI_init(BAUD_400Kb);


	/*
	 * UART_initialization
	 * */
	UART_ConfigType UART_configurations;
	UART_configurations.baud_rate=9600;
	UART_configurations.ch_size=bit_8;
	UART_configurations.parity_type=none;
	UART_init(&UART_configurations);
	DcMotor_init();
	/*
	 * timer initlization
	 * */
	//TIMER0_init(CTC);
	//TIMER0_countMilliSeconds_ctc(3000,FCPU_1024);
	while(1)
	{

		check_byte=UART_receiveByte();
		if(check_byte==are_you_ready_for_password)
		{
			UART_sendByte(ready_for_password);
			UART_receiveString(password);

			for(i=0;i<4;i++)
			{

				EEPROM_writeByte(adresses[i],password[i]);
				_delay_ms(10);

			}
		}
		/*---------------------------------------------------------------------------------------*/
		if(check_byte==are_you_ready_to_confirm_to_open_doors)
		{
			for(i=0;i<4;i++)
			{
				EEPROM_readByte(adresses[i],&password_check[i]);
				_delay_ms(10);
			}
			UART_sendByte(ready_to_confirm_to_open_doors);
			UART_receiveString(password);

			for(i=0;i<4;i++)
			{
				if(password[i]!=password_check[i])
				{
					UART_sendByte(unconfirmed);
					break;
				}
				else
				{
					if(i==3)
					{
						UART_sendByte(confirmed);
					}
				}
			}
		}

		/*---------------------------------------------------------------------------------------*/
		if(check_byte==are_you_ready_to_open)
		{
			UART_sendByte(ready_to_open_doors);
		}
		if(check_byte==open_the_door)
		{
			DcMotor_Rotate(CW);
			_delay_ms(6000);
			_delay_ms(6000);
			_delay_ms(1000);
			DcMotor_Rotate(STOP);
			_delay_ms(3000);
			DcMotor_Rotate(CCW);
			_delay_ms(6000);
			_delay_ms(6000);
			_delay_ms(1000);
			DcMotor_Rotate(STOP);
			UART_sendByte(doors_opened_and_closed);
		}
		/*---------------------------------------------------------------------------------------*/
		if(check_byte==are_you_ready_to_sound_alarm)
		{
			UART_sendByte(ready_to_sound_alarm);
		}

		if(check_byte==sound_the_alarm)
		{
			BUZZER_on();
			for(i=0;i<60;i++)
			{
				_delay_ms(1000);

			}
			BUZZER_off();
			UART_sendByte(buzzer_ended);
		}
/*---------------------------------------------------------------------------------------*/
		if(check_byte==are_you_ready_to_change_password)
		{
			for(i=0;i<4;i++)
			{
				EEPROM_readByte(adresses[i],&password_check[i]);
				_delay_ms(10);
			}
			UART_sendByte(ready_to_change_password);
			UART_receiveString(password);
			for(i=0;i<4;i++)
			{
				if(password[i]!=password_check[i])
				{
					UART_sendByte(unconfirmed);
					break;
				}
				else
				{
					if(i==3)
					{
						UART_sendByte(confirmed);
					}
				}
			}
		}


	}
}
