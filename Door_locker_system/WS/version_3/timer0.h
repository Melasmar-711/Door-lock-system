/*
 * timer0.h
 *
 *  Created on: Nov 1, 2021
 *      Author: Mahmoud EL-Asmar
 */

#ifndef TIMER0_H_
#define TIMER0_H_


#include"std_types.h"

#define NO_CLK 		0
#define FCPU_CLK 	1
#define FCPU_8		8
#define FCPU_64		64
#define FCPU_256	256
#define FCPU_1024 1024

#define NO_clk 0
#define	SYS_CLK	1
#define	SYS_8	2
#define	SYS_64	3
#define	SYS_256	4
#define	SYS_1024	5
#define	EXTERNAL_CLK_FALLING	6
#define	EXTERNAL_CLK_RISING	7

typedef enum
{
	NORMAL=0b0000,CTC=0b1000
}TIMER0_mode;


void TIMER0_setCallBack(void(*ptr_fun)(void));
void TIMER0_countMilliSeconds_ctc(uint16 ms,uint16 prescaler);
void TIMER0_countMilliSeconds_overflow(uint16 ms,uint16 prescaler);
void TIMER0_init(TIMER0_mode mode_op);

#endif /* TIMER0_H_ */
