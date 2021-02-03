#include "servo.h"
#include "utils.h"

void servoUp()
{
	uint32_t highTime;
	uint32_t lowTime;
	for(uint32_t j = 1300; j > 200; j = j - 15)
	{
		PTB->PSOR |= (1<<SERVO);
		highTime = 2000 - j;
		DELAY_us(highTime);
		PTB->PCOR |= (1<<SERVO);
		lowTime = 18000 + j;
		DELAY_us(lowTime);
	}
}

void servoDown()
{
	uint32_t highTime;
	uint32_t lowTime;
	for(uint32_t j = 200; j < 1300; j = j + 15)
	{
		PTB->PSOR |= (1<<SERVO);
		highTime = 2000 - j;
		DELAY_us(highTime);
		PTB->PCOR |= (1<<SERVO);
		lowTime = 18000 + j;
		DELAY_us(lowTime);
	}
}

void servoInit()
{
	PORTB->PCR[SERVO] |= PORT_PCR_MUX(1);
	PTB->PDDR |= (1<<SERVO);
	servoDown();
}
