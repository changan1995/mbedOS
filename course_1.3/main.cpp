/*
This is used for the mbed OS 5 course chapter 1. The basic usage of mbed Os
Be aware of the fact that the code below is specificed for Freescale K64F.
*/
#include "mbed.h"
DigitalOut led(LED1);
//DigitalOut led2(LED2);//if you are using a board with multiple LEDs you can try this.


    //initial the thread.
    Thread thread1;
    Thread thread2;

//Again, this will comfront troubles when you want to reset the button status.
//DigitalIn button(USER_BUTTON);
InterruptIn button(SW2);
volatile bool clicked = false;
void press_handle(){
//set a signal flag for triggering.
    thread1.signal_set(0x1);
}

//initial a delay time. and record press number.
volatile float delay=0.5;
volatile int press_times=0;

//press count thread.
void press_count(){
    while(1){
        //since both track need to use the clicked variable, use mutex can prevent mutal conflix 
        thread1.signal_wait(0x1);
        thread1.signal_set(0x0);
        press_times++;
        printf("pressed %d times \n",press_times);
        if(delay<3){
            delay=delay+0.5;
        }
        else{delay=0.5;}       
        printf("delaytime is %f\n",delay);
    }
}

void blinky(){
    while(1){
        led=!led;
        wait(delay);
    }
}
int main(){
    button.fall(&press_handle);
    printf("hellwolrd\n");
    thread1.start(callback(press_count));
    thread2.start(callback(blinky));
}