/*
 * dc_motor.h
 *
 *  Created on: Oct 12, 2021
 *  Author: Mahmoud EL-Asmar
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_


#include "std_types.h"


#define DcMotor_Port	PORTB_ID
#define DcMotor_IN1		PIN3_ID
#define DcMotor_IN2		PIN4_ID
#define DcMotor_Enable	PIN5_ID
#define STOP	0
#define CW		1
#define	CCW		2



void DcMotor_Rotate(uint8 direction);
void DcMotor_init(void);

#endif /* DCMOTOR_H_ */
