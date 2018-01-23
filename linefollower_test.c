#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "linefollowerdriver.h"

int line_follower_values[5];
int line_follower_analog[5];
int main(){
	while(1) {

		digitalResult(&line_follower_values[0]);
						int j=0;
						for (j=0;j<5;j++) {
							printf("%d",line_follower_values[j]);
							}
							printf("\n");
	}
	
					}
