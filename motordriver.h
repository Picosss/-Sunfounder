
#define MOTORPORT 64
#define PORTMOTORSTART 16
#define leftmotorpin 21
#define rightmotorpin 22

#define maximumspeed 100
#define minimumspeed 0
#define higestpwm 4095
#define lowestpwm   0

void run_motor(int left_speed, int right_speed, int left_direction, int right_direction) ;
int motor_setup();
void start_motor();
void stop_motor();
int speed_to_pwm(int speed);
