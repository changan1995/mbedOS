/*
This is used for the mbed OS 5 course chapter 1. The basic usage of mbed Os
Be aware of the fact that the code below is specificed for Freescale K64F.
*/
#include "mbed.h"
DigitalOut led(LED1);
//DigitalIn button(USER_BUTTON); Use DigitalIn to handle button will cause problem when you want to reset the button value.
volatile int press_times=0;
InterruptIn button(USER_BUTTON);
//This is recommended to support Interrupt.
volatile bool clicked = false;

//Interrupt cannot handle complicated function like initial a thread or printf other functions.
//recommanded for handle button status rather than others.
void press_handle(){
    clicked=1;
}

int main(){
    button.fall(&press_handle);
    printf("hellwolrd\n");
    while(1){
        led=!led;
        wait(0.5);
        if(clicked){
          clicked=0;
          press_times++;
          printf("pressed %d times \n",press_times);
        }
    }
}