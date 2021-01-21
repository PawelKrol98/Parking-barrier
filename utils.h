#ifndef UTILS_H
#define UTILS_H
# include "MKL05Z4.h"

#define DELAY(x)   for(uint32_t i=0;i<(x*10000);i++)__nop()
#define DELAY_us(x)   for(uint32_t i=0;i<(x*10);i++)__nop() 
#define RED_LED 8
#define GREEN_LED 9
#define BLUE_LED 10
#define TRIG 1
#define ECHO 2
#define BUTTON 7
#define SERVO 11

#endif
