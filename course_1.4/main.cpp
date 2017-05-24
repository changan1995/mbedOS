#include "mbed.h"
#include <string>
#include <vector>
#include <inttypes.h>
#include "mbedtls/entropy_poll.h"
#include <sstream>
DigitalOut led(LED1);
Thread blinky_thread;
int counter;
//vector strategy
//uint16_t position;
//std::vector<uint32_t> blink_pattern;

//array...
int delaytime[255];
int position=0;
int size;

void blink(){
    position=0;
    printf("blink initialized\n");
    while(1){
         //debug the position and the delay time in vector
         printf("position is at %d\n",position);
         printf("delay time is %d\n",delaytime[position]);
         
         led=!led;
         if(position >= size){
            printf("size is %d \n",size);
             led=0;
             printf("finished blinking\n");
            return;
         }
         Thread::wait(delaytime[position]);
         position++;
         printf("position ++\n");
     }
}


int main() {
            printf("helloworld\n");
    led=0;
        // std::string initial the pattern;
        std::string s("100:500:100:500:100:500:100:500:100");
        printf("led_execute_callback pattern=%s\n",s.c_str());
        // our pattern is something like 500:200:500, so parse that
        std::size_t found = s.find_first_of(":");
        int phase=0;
        size =0;
        while (found!=std::string::npos) {
            //counter for read
            //printf("time %d \n",counter);counter++;wait(1);
            
            //debug the string
            //printf("led_execute_callback pattern=%s \n",s.substr(0,found).c_str());
            
            //debug the found all at 
            //printf("time %d \n",found);
            delaytime[phase]=atoi((const char*)s.substr(0,found).c_str());
            //blink_pattern.push_back(atoi((const char*)s.substr(0,found).c_str()));
            s = s.substr(found+1);
            found=s.find_first_of(":");
            if(found == std::string::npos) {
            delaytime[phase]=atoi((const char*)s.c_str());   
            //    blink_pattern.push_back(atoi((const char*)s.c_str()));
            size=phase;
            }
            phase++;
        }
    
       blinky_thread.start(callback(blink));
    }