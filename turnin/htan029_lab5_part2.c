/*	Author: Heng Tan    
 *  Partner(s) Name: 
 *	Lab Section: 024
 *	Assignment: Lab 5  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 * Demo Link: https://youtu.be/-TcRqPcBT7Q
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Wait, Increment, Decrement, Wait2, Wait3} state;

unsigned char cnt;

void Tick(){
    switch(state){
        case Start: PORTC = cnt = 0x07; state = Wait; break;
        case Wait: 
            if(((~PINA) & 0x03) == 0x03){  
                PORTC = cnt = 0x00;
            } else if (((~PINA) & 0x03) == 0x01){
                state = Increment;
            } else if (((~PINA) & 0x03) == 0x02){
                state = Decrement;
            }
            break;
        case Increment: state = Wait2; break;
        case Decrement: state = Wait3; break;
        case Wait2:
            if(((~PINA) & 0x03) == 0x01) state = Wait2;
            else state = Wait;
            break;
        case Wait3:
            if(((~PINA) & 0x03) == 0x02) state = Wait3;
            else state = Wait;
            break;
        default: break;
    };

    switch (state){
        case Start: break;
        case Wait: break;
        case Increment: //PORTC = cnt = (cnt == 0x09) ? 0x09 : cnt+1; break;
            if(cnt == 0x09){
                cnt = 0x09;
                PORTC = cnt;
            } else {
                cnt++;
                PORTC = cnt;
            }
            break;
        case Decrement: //PORTC = cnt = (cnt == 0x00) ? 0x00 : cnt-1; break;
            if(cnt == 0x00){
                cnt = 0x00;
                PORTC = cnt;
            } else {
                cnt--;
                PORTC = cnt;
            }
            break;
        case Wait2: break;
        case Wait3: break;
        default: break;
    };
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    state = Start;
    TimerSet(1);
    TimerOn();
    /* Insert your solution below */
    while (1) {
        Tick();
        while(!TimerFlag){}
        TimerFlag = 0;
    }
    return 1;
}
