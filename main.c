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

volatile uint32_t timer;

void PIT_IRQHandler()
{
	timer ++;
	PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
}

int main (void)
{
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	// inicjalizacja elementow ukladu
	hcsr04Init();
	servoInit();
	ledInit();
	LCD1602_Init();
	LCD1602_Backlight(1);
	
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;			// wlaczenie zegara dla PIT
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;				// wlaczenie  PIT
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(SystemCoreClock/2);		// przerwanie co 1s
	PIT->CHANNEL[0].TCTRL = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);	
	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	
	
	turnOnLed(RED_LED);
	double distance;
	const double minimalDistance = 10.0;
	bool wasButtonPressed = false;
	while(1)
	{
		LCD1602_ClearAll();
		LCD1602_SetCursor(0,0);
		LCD1602_Print("---");
		distance = calculateDistance();
		if(isDistanceBelow(distance, minimalDistance))
		{
			turnOffLed(RED_LED);
			turnOffLed(GREEN_LED);
			turnOnLed(BLUE_LED);
			LCD1602_ClearAll();
			LCD1602_SetCursor(0,0);
			LCD1602_Print("Please press");
			LCD1602_SetCursor(0,1);
			LCD1602_Print("the button");
			
			PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;
			while(isDistanceBelow(distance, minimalDistance))  
			{
				distance = calculateDistance();
				wasButtonPressed = (PTB->PDIR & (1<<BUTTON)) == 0;
				if (wasButtonPressed) break;
			}
			distance = calculateDistance();
			
			PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK; // wlaczenie timera
			if(!isDistanceBelow(distance, minimalDistance))
			{
				while(timer <= 5) // jezeli samochod odjedzie bez naciskania przycisku, odczekujemy 5 sekund
				{
					wasButtonPressed = false;
				}
			}
			PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK; // wylaczenie timera
			timer =0; // reset timera
			
			turnOffLed(RED_LED);
			turnOffLed(BLUE_LED);
			turnOnLed(GREEN_LED);
			if (!wasButtonPressed) continue; // jesli nie wcisnieto przycisku to powtarzamy petle
			
			LCD1602_ClearAll();
			LCD1602_SetCursor(0,0);
			LCD1602_Print("Please come in!");
			servoUp();
			while(isDistanceBelow(distance, minimalDistance)) distance = calculateDistance();
			DELAY(3000);
			turnOnLed(RED_LED);
			turnOffLed(BLUE_LED);
			turnOffLed(GREEN_LED);
			servoDown();
		}
		else
		{
			turnOnLed(RED_LED);
			turnOffLed(BLUE_LED);
			turnOffLed(GREEN_LED);
		}
		DELAY(100);
	}
}

