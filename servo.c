#include "servo.h"
#include "utils.h"

void servoUp()
{
	for (int j = 0; j <10; j++)
	{
		PTB->PSOR |= (1<<SERVO);
		DELAY_us(1800);
		PTB->PCOR |= (1<<SERVO);
		DELAY_us(18200);
	}
}

void servoDown()
{
	for (int j = 0; j <10; j++)
	{
		PTB->PSOR |= (1<<SERVO);
		DELAY_us(700);
		PTB->PCOR |= (1<<SERVO);
		DELAY_us(19300);
	}
}

void servoInit()
{
	PORTB->PCR[SERVO] |= PORT_PCR_MUX(1);
	PTB->PDDR |= (1<<SERVO);
	servoDown();
}
