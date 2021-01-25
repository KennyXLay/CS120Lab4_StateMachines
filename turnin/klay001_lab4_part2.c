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

enum States {start, init, inc, dec, reset, wait} state;

void Tick(){
	unsigned char tmpA = PINA & 0x01;
	unsigned char tmpB = PINA & 0X02;
	unsigned char tmpC = 0x07;

	switch(state){//transitions
		case start:
			state = init;
			break;
		case init:
			state = wait;
			break;
		case wait:
			if(tmpA && tmpB){
				state = reset;
			}
			else if(tmpB){
				state = dec;
			}
			else if(tmpA){
				state = inc;
			}
			else{
				state = wait;
			}
			break;
		case inc:
			state = wait;
			break;
		case dec:
			state = wait;
			break;
		case reset:
			state = wait;
			break;
		default:
			state = init;
			break;
	}

	switch(state){//state actions
                case init:
			tmpC = 0x07;
                	break;
		case wait:
			break;
		case inc:
			if(tmpC < 0x09){
				tmpC++;
			}
			break;
                case dec:
			if(tmpC > 0x00){
                                tmpC--;
                        }
			break;
		case reset:
			tmpC = 0x00; 
			break;
                default:
                	break;
        }
	PORTC = tmpC;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRC = 0xFF; PORTC = 0x00; //output
	state = init;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
