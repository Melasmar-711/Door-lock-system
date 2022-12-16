/*
 * buzzer.h
 *
 *  Created on: Nov 5, 2021
 *      Author: Mahmoud EL-Asmar
 */

#ifndef BUZZER_H_
#define BUZZER_H_


#define BUZZER_PORT 	PORTD_ID
#define BUZZER_PIN		PIN4_ID
void BUZZER_on();
void BUZZER_off();
void BUZZER_init();

#endif /* BUZZER_H_ */
