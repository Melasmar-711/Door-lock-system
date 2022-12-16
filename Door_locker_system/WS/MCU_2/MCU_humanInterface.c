/*
 * main.c
 *
 *  Created on: Oct 31, 2021
 *      Author: Mahmoud EL-Asmar
 */


#include "uart.h"
#include "util/delay.h"
#include <avr/io.h>
#include "gpio.h"
#include "uart_readyBytes.h"
#include "lcd.h"
#include "keypad.h"
#include"application_status.h"





int main()
{
	uint8 error_times=0;
	uint8 i=0;
	uint8 current_status;
	uint8 next_status=new_password;
	uint8 option;
	/*check byte */
	uint8 check;
	uint8  password_check[]="NNNN ";
	uint8 password[8]="NNNN ";

	/**/
	UART_ConfigType configurations;
	configurations.baud_rate=9600;
	configurations.ch_size=bit_8;
	configurations.parity_type=none;
	UART_init(&configurations);
	/*lcd intilization */
	LCD_init();

	LCD_displayString("enter password");



	while(1)
	{
		/*-------------------------------------------------------------------------------*/
		if(next_status==new_password)
		{
			current_status=new_password;
			LCD_moveCursor(1,0);
			for(i=0;i<4;i++)
			{
				password[i] = KEYPAD_getPressedKey();
				_delay_ms(500);
				/* get the pressed key number */
				LCD_intgerToString(password[i]);
			}
			password[i]=KEYPAD_getPressedKey();
			_delay_ms(500);
			next_status=second_entry;
		}
		/*-------------------------------------------------------------------------------*/
		else if(next_status==second_entry)
		{
			current_status=second_entry;
			LCD_moveCursor(0,0);
			LCD_displayString("Enter again    ");
			LCD_moveCursor(1,0);
			LCD_displayString("	       ");
			//while((check=UART_receiveByte())!=READY){};
			LCD_moveCursor(1,0);
			for(int i=0;i<4;i++)
			{

				password_check[i] = KEYPAD_getPressedKey();
				_delay_ms(500);
				/* get the pressed key number */
				LCD_intgerToString(password_check[i]);
			}
			password_check[i]=KEYPAD_getPressedKey();
			_delay_ms(500);

			for(i=0;i<5;i++)
			{
				if(password[i]!=password_check[i])
				{
					next_status=re_entry_wrong;
					break;
				}
				else
				{
					next_status=re_entry_right;
				}
			}
		}
		/*------------------------------------------------------------------------------*/

		else if(next_status==re_entry_wrong)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("wrong password  ");
			LCD_moveCursor(1,0);
			LCD_displayString("          ");
			_delay_ms(1500);
			LCD_moveCursor(0,0);
			LCD_displayString("enter password  ");
			next_status=new_password;
		}
		/*----------------------------------------------------------------*/
		else if(next_status==re_entry_right)
		{
			UART_sendByte(are_you_ready_for_password);
			while(UART_receiveByte()!=ready_for_password){}
			for(uint8 x=0;password[x]!='\0';x++)
			{
				UART_sendByte(password[x]);
			}
			// status=main options
			next_status=main_options;
		}
		/*-------------------------------------------------------------------------*/
		else if (next_status==main_options)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("+ open door   ");
			LCD_moveCursor(1,0);
			LCD_displayString("-change password");
			option=KEYPAD_getPressedKey();
			_delay_ms(500);
			if(option==open_door)
			{

				//change status to enter password
				next_status=enter_password;
			}
			else if(option==change_pass)
			{
				//change status to new_password
				next_status=enter_password_for_change;
			}
		}
		/*-------------------------------------------------------------------------*/
		else if (next_status==enter_password)
		{	LCD_moveCursor(0,0);
		LCD_displayString("enter password");
		LCD_moveCursor(1,0);
		LCD_displayString("                ");
		/*take password and send it
		 *
		 *but wait here till the control unit says it's right*/
		LCD_moveCursor(1,0);
		for(i=0;i<4;i++)
		{
			password[i] = KEYPAD_getPressedKey();
			_delay_ms(500);
			/* get the pressed key number */
			LCD_displayCharacter('*');
		}
		password[i]=KEYPAD_getPressedKey();
		_delay_ms(500);
		UART_sendByte(are_you_ready_to_confirm_to_open_doors);
		while((check=UART_receiveByte())!=ready_to_confirm_to_open_doors){}
		UART_sendString(password);
		check=UART_receiveByte();
		if(check==confirmed)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("pass  correct");
			UART_sendByte(are_you_ready_to_open);
			while((check=UART_receiveByte())!=ready_to_open_doors){}
			UART_sendByte(open_the_door);
			LCD_moveCursor(1,0);
			LCD_displayString("                ");
			LCD_moveCursor(0,0);
			LCD_displayString("doors_opening ");
			while((check=UART_receiveByte())!=doors_opened_and_closed){}
			next_status=main_options;
		}
		else
		{
			error_times++;
			LCD_moveCursor(0,0);
			LCD_displayString("wroooong pass");
			if(error_times==3)
			{
				error_times=0;
				next_status=show_warning;
			}
		}
		}

		/*-------------------------------------------------------------------------------*/
		else if(next_status==show_warning)
		{
			UART_sendByte(are_you_ready_to_sound_alarm);
			while((check=UART_receiveByte())!=ready_to_sound_alarm){}
			UART_sendByte(sound_the_alarm);

			while((check=UART_receiveByte())!=buzzer_ended){}
			next_status=main_options;
		}
		/*-------------------------------------------------------------------------------*/
		else if(next_status==enter_password_for_change)
		{
			LCD_moveCursor(0,0);
			LCD_displayString("enter old pass");
			LCD_moveCursor(1,0);
			LCD_displayString("                ");
			/*take password and send it
			 *
			 *but wait here till the control unit says it's right*/
			LCD_moveCursor(1,0);
			for(i=0;i<4;i++)
			{
				password[i] = KEYPAD_getPressedKey();
				_delay_ms(500);
				/* get the pressed key number */
				LCD_displayCharacter('*');
			}
			password[i]=KEYPAD_getPressedKey();
			_delay_ms(500);
			UART_sendByte(are_you_ready_to_change_password);
			while((check=UART_receiveByte())!=ready_to_change_password){}
			UART_sendString(password);
			check=UART_receiveByte();
			if(check==confirmed)
			{
				next_status=new_password;
				LCD_moveCursor(0,0);
				LCD_displayString("enter new pass");
				LCD_moveCursor(1,0);
				LCD_displayString("                ");
			}
		}
	}
}
