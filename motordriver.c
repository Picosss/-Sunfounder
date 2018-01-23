#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wiringPi.h>
#include "motordriver.h"

#ifndef MOTORPORT
	#error "Define MOTORPORT not set!"
#endif

#ifndef PORTMOTORSTART
	#error "Define PORTMOTORSTART not set!"
#endif

#ifndef leftmotorpin
	#error "Define leftmotorpin not set!"
#endif

#ifndef rightmotorpin
	#error "Define rightmotorpin not set!"
#endif

#ifndef maximumspeed
	#error "Define maximumspeed not set!"
#endif

#ifndef minimumspeed
	#error "Define minimumspeed not set!"
#endif

#ifndef higestpwm
	#error "Define higestpwm not set!"
#endif

#ifndef lowestpwm
	#error "Define lowestpwm not set!"
#endif



int device;

/*
 * 
 * name: run_motor
 * @param : int left_speed,right_speed - 0 to 100
 * (left_direction, right_direction - 0 for forward & 1 for backward)
 * @return : void
 * @desc : writes the pwm values on to address 0x30 & 0x34 of port -0X40
 * 
 */
void run_motor(int left_speed,int right_speed, int left_direction, int right_direction) {
	
	int left_pwm,right_pwm,writeResultleft,writeResultright;
	device = motor_setup();	
	if (ioctl(device, I2C_SLAVE, MOTORPORT) < 0) {
	
      	perror("ioctl() I2C_SLAVE failed in writing values to address\n");
    
	}
	else {
		left_pwm=speed_to_pwm(left_speed);
		right_pwm=speed_to_pwm(right_speed);
		
		writeResultleft =i2c_smbus_write_word_data(device, 0x34,right_pwm);
			
		if (writeResultleft == -1){
			writeResultleft =i2c_smbus_write_word_data(device, 0x34,right_pwm);
			
				}
		writeResultright =i2c_smbus_write_word_data(device, 0x30, left_pwm);
		
		digitalWrite(leftmotorpin, left_direction);
		digitalWrite(rightmotorpin, right_direction);
		
		close(device);
		

		  }
	
	}

/*
 * 
 * name: motor_setup
 * @param : void
 * @return : void
 * @desc : setting up pins and device for i2c communication
 */
int motor_setup() {
	pinMode(leftmotorpin,OUTPUT);
	pinMode(rightmotorpin,OUTPUT);
	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		
		perror("setup wiringPi failed !");
		
		}
	else {
	
		if ((device = open("/dev/i2c-1", O_RDWR)) < 0)
			{
				perror("open() failed");
					exit (1);
			}
			
		  }
		
		return device;
	
	}


               
/*
 * 
 * name: start_motor
 * @param : void
 * @return : void
 * @desc : starts the motor by reading value from 0X25 of port 0X10
 * special scenario where motor is started by reading block data from 
 * above mentioned address -observation from python code implementation motor.py  
 */
 void start_motor() {
		
		 __u8 rawData[1];
	    device = motor_setup();
	    printf("device van start motor : %d \n", device);
	    	    
	    if (ioctl(device, I2C_SLAVE, PORTMOTORSTART) < 0){
			
            perror("ioctl() I2C_SLAVE failed in the start call\n");
            
            }
	    else {
			printf("motor should start \n");
			i2c_smbus_read_i2c_block_data(device,0x25,0,rawData);
			close(device);		
			
				}
	
		}
  
               
/*
 * 
 * name: stop_motor
 * @param void
 * @return void
 * @desc : stops the motor by reading value from 0X24 of port 0X10
 * and writes 00 value to speed of motor value. 
 * special scenario where motor is Stops by reading block data from 
 * above mentioned address -observation from python code implementation motor.py
 */
 void stop_motor() {
	 
	 __u8 rawData[1];
	 int  writeResultleft,writeResultright;
			device=motor_setup();
		if (ioctl(device, I2C_SLAVE, PORTMOTORSTART) < 0) {
					
			perror("ioctl() I2C_SLAVE failed in the start call\n");
					
				}
    	else {
				
			i2c_smbus_read_i2c_block_data(device,0X24,0,rawData);
					
			writeResultleft =i2c_smbus_write_word_data(device, 0x34,00);
			printf("sucessfully written 0 to speed  : %d\n",writeResultleft);
		
			if (writeResultleft == -1){
						
					writeResultleft =i2c_smbus_write_word_data(device, 0x34,00);
					printf("sucessfully written 0 to speed  : %d\n",writeResultleft);	
							}
					
			writeResultright =i2c_smbus_write_word_data(device, 0x30, 00);
			printf("successfully written 0 to speed  : %d\n",writeResultright);
			
			printf("value is made 0  after stoping the motor \n");		
			close (device);
					
					}
					
			}

/*
 * 
 * name: speed_to_pwm
 * @param : int speed
 * @return : int pwmvalue
 * @desc : converts speed (0 to 100) to pwm value of (0-4095) 
 */
int speed_to_pwm(int speed) {
		
		int pwmvalue=0;
		pwmvalue=(speed-minimumspeed) * (higestpwm-lowestpwm)/
		(maximumspeed-minimumspeed)+lowestpwm;
		return pwmvalue;

                          }

