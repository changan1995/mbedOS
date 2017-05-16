/*
This is used for the mbed OS 5 course chapter 1. The basic usage of mbed Os
Be aware of the fact that the code below is specificed for Freescale K64F.
*/
#include "mbed.h"

Thread blink_thread;
DigitalOut red_led(LED1);
InterruptIn button(SW2);
uint16_t counter = 0;
uint16_t delay = 1;
uint16_t status =0;

void blink(){
    while(1){
        red_led = !red_led;
        wait(delay);
    }
}

void pressed(){
    status = 1;
}

int main(){
    printf("\n<<<Hello world>>>\n\n");
    blink_thread.start(blink);
    button.fall(&pressed);
    while(1){
        if(status == 1){
            counter++;    
            status =0;
        }
    }
}