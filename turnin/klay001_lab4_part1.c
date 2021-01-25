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

enum States {start, init, on, off} state;

void Tick(){
	unsigned char tmpA = PINA & 0x01;
	unsigned char tmpB = 0x00;

	switch(state){//transitions
		case start:
			state = init;
			break;
		case init:
			if(tmpA == 0x01){
				state = off;
			}
			else{
				state = on;
			}
			break;
		case on:
			if(tmpA == 0x01){
                                state = off;
                        }
                        else{
                                state = on;
                        }

			break;
		case off:
			if(tmpA == 0x01){
                                state = on;
                        }
                        else{
                                state = off;
                        }
			break;
		default:
			state = init;
			break;
	}

	switch(state){//state actions
                case init:
			tmpB = 0x01;
                	break;
		case on:
			tmpB = 0x01;
			break;
                case off:
			tmpB = 0x02;
			break;
                default:
                	break;
        }
	PORTB = tmpB;
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
