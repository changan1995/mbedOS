#include "mbed.h"
#include <string>
#include <vector>
#include <inttypes.h>
#include "mbedtls/entropy_poll.h"
#include <sstream>
DigitalOut led(LED1);
Thread blinky_thread;
int counter;

class BlinkArgs
{
    public:
    BlinkArgs(){
        clear();
    }
    void clear(){
        position=0;
        blink_pattern.clear();
    }
    uint16_t position;
    std::vector<uint32_t> blink_pattern;
};


BlinkArgs *blinkarg;

void do_blink(){
        printf("blink initialized\n");
     while(1){
         //debug the position and the delay time in vector
         printf("position is at %d\n",blinkarg->position);
         printf("delay time is %d\n",blinkarg->blink_pattern.at(blinkarg->position));
         
         led=!led;
         if(blinkarg->position >= blinkarg->blink_pattern.size()){
            printf("size is %d \n",blinkarg->blink_pattern.size());
             led=0;
             printf("finished blinking\n");
            return;
         }
         wait(blinkarg->blink_pattern.at(blinkarg->position));
         blinkarg->position++;
         printf("position ++\n");
     }
}

int main() {
        printf("helloworld\n");
        led=0;
        // std::string initial the pattern;
        std::string s("100:500:100:500:100:500:100:500:100");
        printf("led_execute_callback pattern=%s\n",s.c_str());
        blinkarg->clear();
        // our pattern is something like 500:200:500, so parse that
        std::size_t found = s.find_first_of(":");
        
        while (found!=std::string::npos) {
            //counter for read
            //printf("time %d \n",counter);counter++;wait(1);
            
            //debug the string
            //printf("led_execute_callback pattern=%s \n",s.substr(0,found).c_str());
            
            //debug the found all at 
            //printf("time %d \n",found);
            blinkarg->blink_pattern.push_back(atoi((const char*)s.substr(0,found).c_str()));
            s = s.substr(found+1);
            found=s.find_first_of(":");
            if(found == std::string::npos) {
                blinkarg->blink_pattern.push_back(atoi((const char*)s.c_str()));
            }
        }
    
       blinky_thread.start(callback(do_blink));
    }