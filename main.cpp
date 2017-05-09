/*
this example do the following things:
1.use a constant loop to print '*'
2.start a thread after 2000 unit time and print '< \n';
3.then you will see the thread outcome.
*/
#include "mbed.h"
#include "rtos.h"
Serial pc(USBTX, USBRX);

void print_char(char c)
{
    pc.printf("%c", c);
    fflush(stdout);
}

DigitalOut led1(LED1);

void print_thread(void const *argument)
{   
    Thread::wait(2000);
    pc.printf("\n thread ^ started \n");
    while (true) {
        Thread::wait(1000);
        print_char('<');
        print_char('\n');
    }
}

int main()
{   
    led1 = 1;
    pc.baud(115200);
    pc.printf("\n\n*** RTOS basic example ***\n");
    Thread thread(print_thread, NULL, osPriorityNormal, DEFAULT_STACK_SIZE);
    while (true) {
        print_char('*');
        Thread::wait(500);
    }
}
