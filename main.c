/*
@author Pawel Krol
@group wt800
*/

#include "MKL05Z4.h" 
#include "led.h"
#include "lcd.h"
#include "hcsr04.h"
#include "i2c.h"
#include "utils.h"
#include "servo.h"
#include <stdlib.h>
#include <stdio.h> 
#include <stdbool.h> 

int main (void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	hcsr04Init();
	servoInit();
	servoDown();
	ledInit();
	LCD1602_Init();
	LCD1602_Backlight(1);
	
	turnOnLed(RED_LED);
	double distance;
	while(1)
	{
		LCD1602_ClearAll();
		LCD1602_SetCursor(0,0);
		LCD1602_Print("---");
		distance = calculateDistance();
		if(isDistanceBelow(distance))
		{
			turnOffLed(RED_LED);
			turnOffLed(GREEN_LED);
			turnOnLed(BLUE_LED);
			LCD1602_ClearAll();
			LCD1602_SetCursor(0,0);
			LCD1602_Print("Please press");
			LCD1602_SetCursor(0,1);
			LCD1602_Print("the button");
			while((PTB->PDIR & (1<<BUTTON)) != 0 );
			turnOffLed(RED_LED);
			turnOffLed(BLUE_LED);
			turnOnLed(GREEN_LED);
			LCD1602_ClearAll();
			LCD1602_SetCursor(0,0);
			LCD1602_Print("Please come in!");
			servoUp();
			while(isDistanceBelow(distance)) distance = calculateDistance();
			DELAY(3000);
			servoDown();
		}
		else
		{
			turnOnLed(RED_LED);
			turnOffLed(BLUE_LED);
			turnOffLed(GREEN_LED);
		}
		DELAY(500);
	}
}

