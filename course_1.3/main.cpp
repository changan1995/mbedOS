/*
This is used for the mbed OS 5 course chapter 1. The basic usage of mbed Os
Be aware of the fact that the code below is specificed for Freescale K64F.
*/
#include "mbed.h"
DigitalOut led(LED1);
//DigitalOut led2(LED2);//if you are using a board with multiple LEDs you can try this.

//Again, this will comfront troubles when you want to reset the button status.
//DigitalIn button(USER_BUTTON);
InterruptIn button(USER_BUTTON);
volatile bool clicked = false;
void press_handle(){
    clicked=1;
}

//initial a delay time. and record press number.
volatile float delay=0.5;
volatile int press_times=0;

//you can use mutex to prevent mutal conflicts.
Mutex buttonstatus;


/* todo: try to modify the debug function
void debug_mutex()
{
    printf("\n");
    printf(buttonstatus.lock()); //the return is not a string.
    printf("\n");
}
*/

//press count thread.
void press_count(){
    button.fall(&press_handle);
    printf("hellwolrd\n");
    while(1){
        //since both track need to use the clicked variable, use mutex can prevent mutal conflix 
        //when other track counter the mutex lock, they will stop and wait for this thread unlock
        buttonstatus.lock();        
        //debug_mutex(); // todo
        if(clicked){
            press_times++;
            printf("pressed %d times \n",press_times);
        }
        clicked=0;
        //unlock enable the other track to stop waiting.
        buttonstatus.unlock();
    }
}

void blinky(){
    while(1){
        //lock the mutex
        buttonstatus.lock();
        led=!led;
        wait(delay);
 //       debug_mutex();
        // a delay time loop of 6 times 
        if(clicked){
            if(delay<3){
            delay=delay+0.5;
            }
            else{delay=0.5;}       
            printf("delaytime is %f\n",delay);
        }
        //unlock the mutex
        buttonstatus.unlock();
    }
}
    //initial the thread.
    Thread thread1;
    Thread thread2;
int main(){
    thread1.start(callback(press_count));
    thread2.start(callback(blinky));
}