/*	Author: lab
 *  Partner(s) Name: Kenny
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {start, init, wait1, wait2, unlock, lock} state;

void Tick(){

	unsigned char y = PINA & 0x02;
	unsigned char poundButton = PINA & 0x04;
	unsigned char lockDoor = PINA & 0x80;
	unsigned char door = 0x00;
	

	switch(state){//transitions
		case start:
			state = init;
			break;
		case init:
			state = wait1;
			break;
		case wait1:
			if(lockDoor){
				state = lock;
			}
			else if(poundButton){
				state = wait2;
			}
			else{
				state = wait1;
			}
			break;
		case wait2:
			if(y){
				state = unlock;
			}
			else{
				state = wait1;
			}
			break;
		case unlock:
			state = wait1;
			break;
		case lock:
			state = wait1;
			break;
		default:
			state = init;
			break;
	}

	switch(state){//state actions
                case init:
			door = 0x00;
                	break;
		case wait1:
			break;
		case wait2:
			break;
		case unlock:
			door = 0x01;
			break;
		case lock:
			door = 0x00;
			break;
		
                default:
                	break;
        }
	PORTB = door;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output
	state = init;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
