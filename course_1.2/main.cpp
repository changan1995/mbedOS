/*
This is used for the mbed OS 5 course chapter 1. The basic usage of mbed Os
Be aware of the fact that the code below is specificed for Freescale K64F.
*/
#include "mbed.h"
DigitalOut led(LED1);
//DigitalIn button(USER_BUTTON); Use DigitalIn to handle button will cause problem when you want to reset the button value.

//the int to record the press times.
volatile int press_times=0;

//initial the InterruptIn class button, the pin as arguments varys from board to board.
//InterruptIn button(USER_BUTTON);//for F401RE
InterruptIn button(SW2);//for Freescale K64F

/*
This is recommended to support Interrupt.
Interrupt cannot handle complicated function like initial a thread or printf other functions.
recommanded for handle button status rather than others.
*/
Thread read_button;
void press_handle(){
//start a signal flag of 0x1.
    read_button.signal_set(0x1);
}

void press_read(){
    while(1){
// wait until the signal flag of  0x1 is set.
        read_button.signal_wait(0x1);
        press_times++;
        printf("pressed %d times \n",press_times);
        read_button.signal_set(0x0);
    }
}

int main(){
/*
fall is the number funciton in the InterruptIn class, when triggerd by the fall of the 
pin, it will turns to the function pointer as argument.
*/
    button.fall(&press_handle);

//  Start A thread for reading the button status and handle it.   
    read_button.start(callback(press_read));
//one can elaborate the serial ports with Serial class and identify the baud frequency, however the port pin should be specificed.
//  Serial pc(USBTX,USBRX)
//  pc.baud(115200)
    printf("hellwolrd\n");
    while(1){
        led=!led;
        wait(0.5);
    }
}