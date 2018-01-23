#include <stdio.h>
#include <pthread.h>
#include <wiringPi.h>
#include "motordriver.h"
#include "linefollowerdriver.h"
#include "button.h"
//#include "ultrasonic.h"
#include "speedcontroller.h"

#define motor_control_pin 1
#define background_control_pin 2
#define ev_flag 3

#define TRIG 0

/* currently Ultrasonic.c & Ultrasonic.h files are not working so this 
 files should not be compiles , commented the preprocessor include for it 
 
 **this method getdistance() method will provide the Ultrasonic sensor Values 
 */
 
int getdistance() {
        //Send trig pulse
        wiringPiSetup();
        int distance;
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

        distance = travelTime / 58;
	
      return distance;
}


/* Integration of LineFollower, Motor , Ultrasonic Sensor is done here.
* 
*  button_value(motor_control_pin) is the first condition check, 
*  if its HIGH the code traverse -- value on GPIO pin - 1
*   
*  Object Distance Measurement -  getdistance()
*  if object distance is less than 10cm the car will stop by calling stop_motor() 
* 
* 
* 
*/
int main () {
	
		int rightspeed =0;
		int leftspeed =0;
		int leftdirection =0;
		int rightdirection =0;
		int line_follower_values[5],button_status;
		int ev_condition_count;
		int efficient_array[5] = {1,1,0,1,1};
		int digitaldata_test[5];
		int digitaldata_test_park[5];
		int object_distance;
		
		
		while (1) {
			
			if(button_value(motor_control_pin))	{
				/*getdistance() method is unstable has timeout issue , 
				currrently run it with Ultrasonic_Avoidance.py present in same folder*/
					object_distance=getdistance();
					if(object_distance<10)
					{
						printf("object_distance : %d \n",object_distance);
						stop_motor();
						delay(10);
						
						}
						
						
					else {		
						
						digitalResult(&line_follower_values[0]);
						int i=0;
						for (i=0;i<5;i++) {
							printf("%d",line_follower_values[i]);
							}
						
						control_speed(&line_follower_values[0],&rightspeed,&leftspeed,&leftdirection,&rightdirection);
							
						start_motor();
						//printf("leftspeed : %d\n", leftspeed);
						//printf("rightspeed : %d\n", rightspeed);
						run_motor(leftspeed,rightspeed,0,0);
												
						/* background scenario won't be used
						int x,y,z=0;
						while( button_value_ev(background_control_pin)) {
							
							printf("button_value(background_control_pin) : %d \n",button_value(background_control_pin));
							
						    for(x=0; x<5;x++){
							   
							   digitalResult(&digitaldata_test[0]);
							   
							   if(efficient_array[x]==digitaldata_test[x])
							   {
								   z++;
								   printf("count :%d \n",z);
								   
								   }
								   
							   else {
								 printf("Array are nottttt equal \n");
								 z=0;
							      }
								  		   }
								  		   
								  		   
								  		   
							if(z>=400) {
								 printf("time to switch lane");
								 leftspeed=20;
								 rightspeed=20;
															
								digitalResult(&digitaldata_test_park[0]);
								
								if(digitaldata_test_park[0]==1 && digitaldata_test_park[1]==1 
								&&  digitaldata_test_park[2]==1 && digitaldata_test_park[3]==1 
								&& digitaldata_test_park[4] == 0) 
								{
									leftspeed=10;
									rightspeed=20;
									
													}
													
								else if (digitaldata_test_park[0]==0 && digitaldata_test_park[1]==1 
								&&  digitaldata_test_park[2]==1 && digitaldata_test_park[3]==1 
								&& digitaldata_test_park[4] == 1) { 
									
									leftspeed=20;
									rightspeed=10;
									
									}
		
								else {
								
									leftspeed=20;
									rightspeed=20;
								
								}
						
								start_motor();
								run_motor(leftspeed,rightspeed,0,0);
								
													
										}
						
													}
										
										*/
									}
						
							}	
				
			else {
	
					stop_motor();
	
				}

	}
}
