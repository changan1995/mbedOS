#include "mbed.h"
#include "rtos.h"
 
DigitalOut led1(LED_GREEN);
DigitalOut led2(LED_BLUE);
DigitalOut led3(LED_RED);
DigitalIn sw2(SW2);
DigitalIn sw3(SW3);
Thread thread;
Ticker timer;
Serial pc(USBTX, USBRX);

 
void led2_thread(){
    while (true) {
        led2 =! led2;
        pc.printf("led2 pressed \n");
        Thread::wait(1000);
    }
}

void led3blink(){
    while(true){
        led3 =! led3;
        wait(0.2);
    }
 }
 
void check_sw2(){
    if(sw2==0){
    pc.printf("sw2 pressed \n");
//    timer.attach(led3blink,1.0);
    }
}

int main() {
    led3 =1;
    int before_red_time =0;
    thread.start(led2_thread);
    pc.baud(115200);
    pc.printf("Hello World from FRDM-K64F board.\n");
    while (before_red_time <6) {
        led1 =! led1;
        check_sw2();
        pc.printf("led1 pressed \n");
        Thread::wait(500);
    }
/*    timer.attach(led3blink,1.0);
    thread.terminate();
    while (true){
        led3 = 1;
        led1 =! led1;
        Thread::wait(500);
    }
*/
}