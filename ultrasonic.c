#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "ultrasonic.h"
 

 
#define TRIG 0
//#define ECHO 1
 
int distance_value;
 
void getCM(int *distance) {
        //Send trig pulse
        wiringPiSetup();
        pinMode(TRIG, OUTPUT);
        digitalWrite(TRIG, 1);
        delayMicroseconds(20);
        digitalWrite(TRIG, 0);
		pinMode(TRIG, INPUT);
        //Wait for echo start
        while(digitalRead(TRIG) == 0);
 		long startTime = micros();
        //Wait for echo end
        
        while(digitalRead(TRIG) == 1);
        long travelTime = micros() - startTime;
 
        //Get distance in cm

        *distance = travelTime / 58;
	
      
}

int main(void) {
        
 int count =0;
 
 while (1) {
	 
	 getCM(&distance_value);
	 count++;
        printf("Distance: %dcm , at count : %d  \n", distance_value,count);
        
 }
        return 1;
}

