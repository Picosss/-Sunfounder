#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "linefollowerdriver.h"

#ifndef LINEFOLLOWERPORT
	#error "Define LINEFOLLOWERPORT not set!"
#endif

#ifndef SENSORCOUNT
	#error "Define SENSORCOUNT not set!"
#endif

#ifndef REGSTARTADDRESS
	#error "Define REGSTARTADDRESS not set!"
#endif

#ifndef REGENDADDRESS
	#error "Define REGENDADDRESS not set!"
#endif


static int rawDataInt[REGENDADDRESS];
static int analogData[SENSORCOUNT];
static int digitaldata[SENSORCOUNT];

int device;

/*
	 This function connects the Line Follower module on Port LINEFOLLOWERPORT 17
	 port address depends on Linefollower hardware -  ' i2c dump -y 1 '
	 command on terminal would provide the address
	 
	 i2c_smbus_read_i2c_block_data is avaliable on <linux/i2c-dev.h> library 
	 which has to be installed like wiringPi Library
	 
	 REGSTARTADDRESS & REGENDADDRESS would depend on number of sensor LineFollower
	 for 5 sensor  REGENDADDRESS=10 & 8 sensor REGENDADDRESS=16 
	 
	 the raw values from Line follower will be written on rawData (__u8) which should 
	 be converted to int.
 
 */
int static rawResult(int *rawDataInt){
 
		int  resultLength;
	     __u8 rawData[REGENDADDRESS];
		if ((device = open("/dev/i2c-1", O_RDWR)) < 0)
			{
			perror("open() failed");
			exit (1);
			}
		if (ioctl(device, I2C_SLAVE, LINEFOLLOWERPORT) < 0)
			  perror("ioctl() I2C_SLAVE failed\n");
			
		else  {
			
			int i=0;
			int j=0;
			
			resultLength = i2c_smbus_read_i2c_block_data(device,REGSTARTADDRESS,REGENDADDRESS,rawData);
			
			close(device);
			
			for (j=0;j <REGENDADDRESS ; j++) {
				
			 rawDataInt[j] = (int)rawData[j];
			 
												}	
												
				} 
						
			return 0;
  }
  
/*
	This function converts the raw value of line follower tuo analog value by 
	shifting right 8 bit of highest byte & adding it to lower byte to generate
	anlong value
*/
   
 int static analogResult(int *analogData) {
	  
      int x=rawResult(&rawDataInt[0]);
	  int i=0;
	  int j = 0;
	  	  
	  for (j= 0; j < REGENDADDRESS ; j++ )
	  {	  
		int high_byte = rawDataInt[j*2] << 8 ;
		int low_byte = rawDataInt[j*2+1];
		analogData[j] = high_byte + low_byte;
			
	  }
	 
	  return 0;
  }
  
/*
 
 */
  int digitalResult(int *digitaldata) {
  
		int referenceValue, lowReference, highReference;
		int y=analogResult(&analogData[0]);
 
  		int j=0;
		lowReference = analogData[0];  // need to start with some value
		
		highReference = analogData[0];  // need to start with some value
		
		for ( j=1; j < SENSORCOUNT; j++) {
			if (analogData[j] < lowReference)
				lowReference = analogData[j];
			if (analogData[j] > highReference)
				highReference = analogData[j];
		}
		referenceValue = lowReference + ((highReference-lowReference)/3);
               int k=0;
              if((highReference-lowReference)>=0) {
				  
				   for (k=0; k < SENSORCOUNT; k++) {
					   
                                if (analogData[k] >= (referenceValue)) {
                                        digitaldata[k]=0;
					}
                                else if (analogData[k] < (referenceValue)){
                                        digitaldata[k]=1;
					}		
							
				   }
				   
			   }
			   else {
				   
				   for (k=0; k < SENSORCOUNT; k++) {
				 digitaldata[k] = 0;
								}
			   } 
			           
               return 0;
		  
  
  
  }
  
                     


  
