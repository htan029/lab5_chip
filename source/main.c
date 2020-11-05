/*	Author: Heng Tan    
 *  Partner(s) Name: 
 *	Lab Section: 024
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * Demo Link: https://youtu.be/-TcRqPcBT7Q
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Init, Wait, Input, Wait2} state;

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    state = Init;

    unsigned char arr[14] = {
        0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F,
        0x00, 0x20, 0x30, 0x38, 0x3C, 0x3E, 0x3F
    };
    unsigned char i = 0;
    /* Insert your solution below */
    while (1) {
        switch(state){
            case Init: i = 0; state = Wait; break;
            case Wait: if(((~PINA) & 0x01) == 0x01) state = Input; break;
            case Input: state = Wait2; break;
            case Wait2: if(((~PINA) & 0x01) == 0x00) state = Wait; break;
            default: break;
        }

        switch(state){
            case Init: break;
            case Wait: break;
            case Input: i = (i == 13) ? 0 : i+1; PORTB = arr[i]; break;
            case Wait2: break;
            default: break;
        }
    }
    return 1;
}
