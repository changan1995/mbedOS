/*
this is ued to show the mechanism of the Interrupt,Thread.
*/

#include "mbed.h"
#include "rtos.h"
 
InterruptIn mybutton(USER_BUTTON);
DigitalOut led1(LED1);
//DigitalOut led2(LED2);
//Serial pc(USBTX,USBRX);    
 
float delay = 1.0; // 1 sec
 
void pressed()
{   
    printf(">>>>PRESSED<<<<<"\n\n);
    if (delay == 1.0)
        delay = 0.2; // 200 ms
    else
        delay = 1.0; // 1 sec
}

void blink_thread(void const *args){
     while(1){
         led1 =! led1;
         wait(delay);
         printf(">Blink_thread wait %f second< \n",delay);
        }
 }
 
int main()
{   
//  pc.baud(115200);
    printf("the main function started with 9600 baud \n");
    mybutton.fall(&pressed);
    Thread thread(blink_thread, NULL, osPriorityNormal, DEFAULT_STACK_SIZE);
    while(1){printf(">the main loop is on \n");wait(2);}
}
 
            