#ifndef INCL_LF_H
#define INCL_LF_H


#define LINEFOLLOWERPORT 17  //9 for LF with 8 sensor
#define SENSORCOUNT 5   // 8 for LF with 8 sensor
#define REGSTARTADDRESS 0
#define REGENDADDRESS (REGSTARTADDRESS + (SENSORCOUNT * 2))



int static rawResult(int *);
int  static analogResult(int *);
int digitalResult(int *);

#endif
