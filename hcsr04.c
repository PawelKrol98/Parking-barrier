#include "hcsr04.h"
#include "led.h"

double calculateDistance()
{
	int time;
	time = 0;
	DELAY_us(2);
	PTB->PSOR |= (1<<TRIG);
	DELAY_us(10);
	PTB->PCOR |= (1<<TRIG);
	while((PTB->PDIR & (1<<ECHO)) == 0 );
	while((PTB->PDIR & (1<<ECHO)) != 0 )
	{
		DELAY_us(1);
		time ++;
	}
	double timer = (double)time;
	return timer * 34.0 / 2000.0;
}

bool isDistanceBelow(double distance)
{
	return distance < 10.0;
}

void hcsr04Init()
{
	PORTB->PCR[ECHO] |= PORT_PCR_MUX(1);
	PORTB->PCR[TRIG] |= PORT_PCR_MUX(1);
	PORTB->PCR[BUTTON] |= PORT_PCR_MUX(1);
	PORTB->PCR[BUTTON] |= PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PTB->PDDR |= (1<<TRIG);
}
