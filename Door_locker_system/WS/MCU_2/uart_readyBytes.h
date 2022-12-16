/*
 * uart_readyBytes.h
 *
 *  Created on: Nov 5, 2021
 *      Author: Mahmoud EL-Asmar
 */

#ifndef UART_READYBYTES_H_
#define UART_READYBYTES_H_


#define uart_sending_password_byte 14



#define new_password	0
#define are_you_ready_for_password 30
#define ready_for_password 31
#define second_entry	7

#define are_you_ready_to_confirm_to_open_doors 32
#define ready_to_confirm_to_open_doors 33
#define confirmed 34
#define unconfirmed 35

#define are_you_ready_to_open 36
#define	ready_to_open_doors	37

#define open_the_door 38
#define doors_opened_and_closed 39

#define uart_sending_password_check_byte 7
#define check_this 8
#define wrong_pass 9
#define correct_pass 10


#define are_you_ready_to_sound_alarm 101
#define ready_to_sound_alarm 102
#define sound_the_alarm 103
#define buzzer_ended 104

#define are_you_ready_to_change_password 105
#define ready_to_change_password		106

#endif /* UART_READYBYTES_H_ */
