/*
This is used for the mbed OS 5 course chapter 1. The basic usage of mbed Os
Be aware of the fact that the code below is specificed for Freescale K64F.
*/
#include "mbed.h"
DigitalOut led(LED1);
DigitalOut led2(LED2);
//DigitalIn button(USER_BUTTON);
volatile int press_times=0;
InterruptIn button(USER_BUTTON);
volatile bool clicked = false;
volatile float delay=0.5;
Mutex buttonstatus;

void press_handle(){
    clicked=1;
}

/* todo: try to modify the debug function
void debug_mutex()
{
    printf("\n");
    printf(buttonstatus.lock());
    printf("\n");
}*/

void press_count(){
    button.fall(&press_handle);
    printf("hellwolrd\n");
    while(1){
        buttonstatus.lock();        
 //       debug_mutex();
        if(clicked){
            press_times++;
            printf("pressed %d times \n",press_times);
        }
        clicked=0;
        buttonstatus.unlock();
    }
}

void blinky(){
    while(1){
        buttonstatus.lock();
        led=!led;
        wait(delay);
 //       debug_mutex();
        if(clicked){
            if(delay<3){
            delay=delay+0.5;
            }
            else{delay=0.5;}       
            printf("delaytime is %f\n",delay);
        }
        buttonstatus.unlock();
    }
}
    Thread thread1;
    Thread thread2;
int main(){
    thread1.start(callback(press_count));
    thread2.start(callback(blinky));
}