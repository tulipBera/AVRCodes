/*
 * motor.c
 *
 * Created: 2/15/2024 10:53:41 AM
 * Author : rajes
 */ 

#include <avr/io.h>
#define F_CPU 1600000
#include <util/delay.h>

#define Relay_PIN     PB1
#define BUTTON1_PIN PC0
#define BUTTON2_PIN PC1

int main(void)
{
	DDRB = 0x02;
	DDRC = 0x00;
	PORTB = 0x02;
	PORTC = 0x00;
	while(1)
	{
		if ((PINC & (1 << BUTTON1_PIN)))
		{
			PORTB &= ~(1 << Relay_PIN );
		}
		else if ((PINC & (1 << BUTTON2_PIN)))
		{
			PORTB |= (1 << Relay_PIN );
		}
	}
}
