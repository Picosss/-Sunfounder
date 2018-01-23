#include <stdio.h>
#include <pthread.h>
#include "motordriver.h"
#include "linefollowerdriver.h"
#include "speedcontroller.h"

/*
  This method read the Linefollower digital value & based on it modify
  the speed of Left & right Motor accordingly
  
  The Left and right motor direction is always forward hence value 0 
  
  */
void control_speed(int *line_follower_values,int *rightspeed, int *leftspeed, int *leftdirection, int *rightdirection) {
	
	
	/* [0,0,0,0,0] CONDITION - white && black Background*/
				if(line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==0
				&& line_follower_values[3]==0&& line_follower_values[4]==0) {
					*rightspeed=0;
					*leftspeed=0; 
					*leftdirection=0;
					*rightdirection=0;
				}
				
				
				/* [1,1,1,1,1] CONDITION - white Background &&  black Background*/
				else if(line_follower_values[0] ==1 && line_follower_values[1] ==1&& line_follower_values[2]==1
				&& line_follower_values[3]==1&& line_follower_values[4]==1) {
					*rightspeed=0;
					*leftspeed=0;
					*leftdirection=0;
					*rightdirection=0;
				
				}
				
				//(line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==0
				//&& line_follower_values[3]==1&& line_follower_values[4]==1
				
				/* [0,0,1,0,0] CONDITION - white Background && [1,1,0,1,1] CONDITION - black Background*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==1
				&& line_follower_values[3]==0&& line_follower_values[4]==0)){
					*rightspeed=40;
					*leftspeed=40;
					*leftdirection=0;
					*rightdirection=0;
					
				}

				//(line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==0
				//&& line_follower_values[3]==1&& line_follower_values[4]==1)
				
				/* [0,0,1,1,0] CONDITION - white Background && [1,1,0,0,1] CONDITION - black Background*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==1
				&& line_follower_values[3]==1&& line_follower_values[4]==0)) {
					*rightspeed=40;
					*leftspeed=25;
					*leftdirection=0;
					*rightdirection=0;
				}
				//(line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==0
				//&& line_follower_values[3]==0 && line_follower_values[4]==1)
				
				/* [0,1,1,0,0] CONDITION - white Background && [1,0,0,1,1] CONDITION - black Background*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==1 && line_follower_values[2]==1
				&& line_follower_values[3]==0&& line_follower_values[4]==0)){
					
					*rightspeed=25;
					*leftspeed=40;
					*leftdirection=0;
					*rightdirection=0;
										
				}
				
				//(line_follower_values[0] ==1 && line_follower_values[1] ==0 && line_follower_values[2]==0
				//&& line_follower_values[3]==1 && line_follower_values[4]==1)
				
				/* [0,0,1,0,1] CONDITION - white Background && [1,1,0,1,0] CONDITION - black Background*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==1
				&& line_follower_values[3]==0 && line_follower_values[4]==1)) {
					*rightspeed=40;
					*leftspeed=10;
					*leftdirection=0;
					*rightdirection=0;
				}
				//(line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==0
				//&& line_follower_values[3]==0 && line_follower_values[4]==0)
				
				/* [1,0,1,0,0] CONDITION - white Background && [0,1,0,1,1] CONDITION - black Background*/          
				else if((line_follower_values[0] ==1 && line_follower_values[1] ==0 && line_follower_values[2]==1
				&& line_follower_values[3]==0 && line_follower_values[4]==0)) {
					
					*rightspeed=10;
					*leftspeed=40;
					*leftdirection=0;
					*rightdirection=0;
										
				}
				//(line_follower_values[0] ==0 && line_follower_values[1] ==1 && line_follower_values[2]==0
				//&& line_follower_values[3]==1 && line_follower_values[4]==1)
									
				/* [0,0,O,0,1] CONDITION - white Background && [1,1,1,1,0] CONDITION - black Background*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==0
				&& line_follower_values[3]==0&& line_follower_values[4]==1)){
					*rightspeed=40;
					*leftspeed=10;
					*leftdirection=0;
					*rightdirection=0;
					
				}
				//(line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==1
				//&& line_follower_values[3]==1 && line_follower_values[4]==0)
				
				/* [1,0,0,0,0] CONDITION - white Background && [0,1,1,1,1] CONDITION - black Background*/
				else if((line_follower_values[0] ==1 && line_follower_values[1] ==0 && line_follower_values[2]==0
				&& line_follower_values[3]==0&& line_follower_values[4]==0)) {
					
					*rightspeed=10;
					*leftspeed=40;
					*leftdirection=0;
					*rightdirection=0; 
										 
				}
				//(line_follower_values[0] ==0 && line_follower_values[1] ==1 && line_follower_values[2]==1
				//&& line_follower_values[3]==1 && line_follower_values[4]==1)
				
				/* [0,0,O,1,0] CONDITION - white Background && [1,1,1,0,1] CONDITION - black Background*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==0
				&& line_follower_values[3]==1&& line_follower_values[4]==0)){
					*rightspeed=40;
					*leftspeed=10;
					*leftdirection=0;
					*rightdirection=0;
				}
				//(line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==1
				//&& line_follower_values[3]==0 && line_follower_values[4]==1)
				
				/* [0,1,O,0,0] CONDITION - white Background && [1,0,1,1,1] CONDITION - black Background*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==1 && line_follower_values[2]==0
				&& line_follower_values[3]==0 && line_follower_values[4]==0)) {
					
					*rightspeed=10;
					*leftspeed=40;
					*leftdirection=0;
					*rightdirection=0;
									
									}
				//(line_follower_values[0] ==1 && line_follower_values[1] ==0 && line_follower_values[2]==1
				//&& line_follower_values[3]==1 && line_follower_values[4]==1)
				
				//critical condition
				/* [0,0,O,1,1] CONDITION - white Background &&*/
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==0
				&& line_follower_values[3]==1&& line_follower_values[4]==1)) {
					
							*rightspeed=30;
							*leftspeed=10;
							*leftdirection=0;
							*rightdirection=0;
							
							
				}
				//critical condition
				//(line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==1
				//&& line_follower_values[3]==1 && line_follower_values[4]==1)
				/* [1,1,0,0,0] CONDITION - white Background && [0,0,1,1,1] CONDITION - black Background*/
				else if((line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==0
				&& line_follower_values[3]==0 && line_follower_values[4]==0)) {
													
							*rightspeed=10; //*rightspeed=10; 
							*leftspeed=30;
							*leftdirection=0;
							*rightdirection=0; 
							
							} 
				//critical condition
				
				//(line_follower_values[0] ==1 && line_follower_values[1] == 1 && line_follower_values[2]==0
				//&& line_follower_values[3]==0 && line_follower_values[4]==0))
				/* [0,0,1,1,1] CONDITION  -priority given to 1 [*,*,1,1,1] therfore it will turn right */
				else if((line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==1
				&& line_follower_values[3]==1&& line_follower_values[4]==1)){	
							*rightspeed=30;
							*leftspeed=10;
							*leftdirection=0;
							*rightdirection=0;
						}
				
				//critical condition
				//(line_follower_values[0] ==0 && line_follower_values[1] ==0 && line_follower_values[2]==0
				//&& line_follower_values[3]==1 && line_follower_values[4]==1)
				/* [1,1,1,0,0] CONDITION -priority given to 1 [1,1,1,*,*] therfore it will turn left */
				else if((line_follower_values[0] ==1 && line_follower_values[1] ==1 && line_follower_values[2]==1
				&& line_follower_values[3]==0&& line_follower_values[4]==0)) {
				
							*rightspeed=10;
							*leftspeed=30;							
							*leftdirection=0;
							*rightdirection=0; 
							
					} 
														
				/* [*,*,*,*,*] DEFAULT  CONDITION */
				else  {
					*leftspeed=0;
					*rightspeed=0;
					*leftdirection=0;
					*rightdirection=0;
				}



	
	}
