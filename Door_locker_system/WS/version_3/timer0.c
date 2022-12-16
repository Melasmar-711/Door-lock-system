/*
 * timer0.c
 *
 *  Created on: Nov 1, 2021
 *      Author: Mahmoud EL-Asmar
 */
#include"timer0.h"
//#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */


static volatile void (*g_callBackPtr)(void) = NULL_PTR;
uint8 volatile static num_of_calls_needed=0;
uint8 volatile counter =0;

ISR(TIMER0_OVF_vect)
{

	if(g_callBackPtr != NULL_PTR&&counter<num_of_calls_needed)
		{
			counter++;

		}
	if(counter==(num_of_calls_needed))
	{
		/* Call the Call Back function in the application after the time is reached */
		(*g_callBackPtr)();
		counter=0;

	}

}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR&&counter<num_of_calls_needed)
			{
				counter++;


			}
		if(counter==(num_of_calls_needed))
		{
			/* Call the Call Back function in the application after the time is reached */
			(*g_callBackPtr)();
			counter=0;

		}
}

void TIMER0_init(TIMER0_mode mode_op)
{
	SREG=(1<<7);
	TCCR0=0;
	TCCR0=(1<<FOC0);
	if((mode_op)==CTC)
	{
		TIMSK=(TIMSK&0xFC)|(1<<OCIE0);
		TCCR0|=(1<<WGM01);
		TCCR0=(TCCR0&0x8F);

	}
	else
	{
		TIMSK=(TIMSK&0xFC)|(1<<TOIE0);
		TCCR0&=~(1<<WGM01);
		TCCR0&=~(1<<WGM00);
		TCCR0|=(NORMAL<<3);
	}

	TCNT0=0;
	OCR0=0;
}

void TIMER0_countMilliSeconds_overflow(uint16 ms,uint16 prescaler)
{

	uint64 num_of_ticks;
	num_of_ticks=(ms*F_CPUU/1000)/(prescaler);
	if (num_of_ticks<255)
	{
		TCNT0=255-num_of_ticks;
		num_of_calls_needed=1;
	}
	else
	{
		TCNT0=0;
		num_of_calls_needed=num_of_ticks/255;

	}
	switch(prescaler)
	{
	case FCPU_1024:
		TCCR0=(TCCR0&0xF8)|(SYS_1024);
		break;
	case FCPU_256:
		TCCR0=(TCCR0&0xF8)|(SYS_256);
		break;
	case FCPU_64:
		TCCR0=(TCCR0&0xF8)|(SYS_64);
		break;
	case FCPU_8:
		TCCR0=(TCCR0&0xF8)|(SYS_8);
		break;
	case FCPU_CLK:
		TCCR0=(TCCR0&0xF8)|(SYS_CLK);
		break;
	case	NO_CLK:
		TCCR0=(TCCR0&0xF8)|(NO_CLK);
		break;
	}


}
void TIMER0_countMilliSeconds_ctc(uint16 ms,uint16 prescaler)
{

		uint64 num_of_ticks;
		num_of_ticks=(ms*(F_CPUU/1000))/(prescaler);
		if (num_of_ticks<=255)
		{
			TCNT0=0;
			OCR0=num_of_ticks;
			num_of_calls_needed=1;
		}
		else
		{
			TCNT0=0;
			OCR0=255;
			num_of_calls_needed=(num_of_ticks/255);
		}
		switch(prescaler)
			{
			case FCPU_1024:
				TCCR0=(TCCR0&0xF8)|(SYS_1024);
				break;
			case FCPU_256:
				TCCR0=(TCCR0&0xF8)|(SYS_256);
				break;
			case FCPU_64:
				TCCR0=(TCCR0&0xF8)|(SYS_64);
				break;
			case FCPU_8:
				TCCR0=(TCCR0&0xF8)|(SYS_8);
				break;
			case FCPU_CLK:
				TCCR0=(TCCR0&0xF8)|(SYS_CLK);
				break;
			case	NO_CLK:
				TCCR0=(TCCR0&0xF8)|(NO_CLK);
				break;

			}

}


void TIMER0_setCallBack(void(*ptr_fun)(void))
{
	g_callBackPtr=ptr_fun;
}


