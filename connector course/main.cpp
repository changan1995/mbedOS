/*
this is for mbed os course connector part.
*/

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

//use array instead of vector, vector the pushback function somehow doesnt work well.
//delaytime stands for the blink pattern, position is the No of the blink sequence.Size is the length of the blink pattern.
int delaytime[255];
int position=0;
int size;

//blink function is used to blink the LED according to the custormized pattern.
void blink(){
    //clear the position.
    position=0;
    printf("blink initialized\n");
    while(1){
         //debug the position and the delay time in vector
         printf("position is at %d\n",position);
         printf("delay time is %d\n",delaytime[position]);
         
         led=!led;

         //if the position reach the end stop the blink pattern.
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
        led=0;//can be replaced by background blink.

        // std::string initial the pattern;
        std::string s("100:500:100:500:100:500:100:500:100");
        
        //confirm the blink pattern, this can be transfered from other function or online.
        printf("led_execute_callback pattern=%s\n",s.c_str());

        // pointer found to the place of ":"
        std::size_t found = s.find_first_of(":");

        //phase serve as position in blink function however to prevent mutual invoking from different thread, use phase instead
        int phase=0;
        
        //clear the length of the pattern.
        size =0;

        //loop until can find ":" which means this is the last delay time.
        while (found!=std::string::npos) {
            /*debug
            //counter for read
            printf("time %d \n",counter);counter++;wait(1)         
            //debug the string
            printf("led_execute_callback pattern=%s \n",s.substr(0,found).c_str());
            //debug the found all at 
            printf("time %d \n",found);
            */

            //put the delay time in to the array.
            delaytime[phase]=atoi((const char*)s.substr(0,found).c_str());
            //blink_pattern.push_back(atoi((const char*)s.substr(0,found).c_str()));
            
            //delete the used pattern to the new one.
            s = s.substr(found+1);
            found=s.find_first_of(":");

            //handle the last blink delay time
            if(found == std::string::npos) {
            delaytime[phase]=atoi((const char*)s.c_str());   
            //    blink_pattern.push_back(atoi((const char*)s.c_str()));
            size=phase;
            }
            //the blink pattern move on.
            phase++;
        }
        //start the thread of blinking. one can start a background blinking in it.
        blinky_thread.start(callback(blink));
    }