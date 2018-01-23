#include <stdio.h>
#include <wiringPi.h>
#include "button.h"
/*
 * 
 * name: button_value
 * @param
 * @return 0 - for button low or OFF & 1 for ON 
 * 
 */

int button_value(int pin) {
	

		wiringPiSetup(); 	//configure pins on raspberry pi
		pinMode(pin,INPUT);   
		return((digitalRead(pin))==LOW?0:1);
	
	
		
	}	
	
int button_value_ev(int pin) {
	

		wiringPiSetup(); 	//configure pins on raspberry pi
		pinMode(pin,INPUT);   
		return((digitalRead(pin))==LOW?0:1);
	
	
		
	}
	


