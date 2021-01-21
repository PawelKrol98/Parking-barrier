#include "led.h"
#define RED_LED 8
#define GREEN_LED 9
#define BLUE_LED 10

void ledInit(void)
{
	PORTB->PCR[RED_LED] |= PORT_PCR_MUX(1);
	PORTB->PCR[GREEN_LED] |= PORT_PCR_MUX(1);
	PORTB->PCR[BLUE_LED] |= PORT_PCR_MUX(1);
	PTB->PDDR |= (1<<RED_LED);
	PTB->PDDR |= (1<<GREEN_LED); 
	PTB->PDDR |= (1<<BLUE_LED);
	
	PTB->PSOR |= (1<<GREEN_LED);
	PTB->PSOR |= (1<<RED_LED);
	PTB->PSOR |= (1<<BLUE_LED);
}

void turnOnLed(uint32_t led)
{
	PTB->PCOR |= (1<<led);
}

void turnOffLed(uint32_t led)
{
	PTB->PSOR |= (1<<led);
}
