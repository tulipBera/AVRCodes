#include <avr/io.h>
#define F_CPU 1600000
#include <util/delay.h>

#define LED_PIN     PB0   
#define BUTTON1_PIN PC0  
#define BUTTON2_PIN PC1   

int main(void)
{
	DDRB = 0xFF;
	PORTB &= ~(1 << LED_PIN);
	DDRC = 0x00;
	PORTC |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN);
	PORTB &= ~(1 << LED_PIN);
	while(1)
	{		
		if ((PINC & (1 << BUTTON1_PIN)))
		{
			PORTB |= (1 << LED_PIN);
		}
		else if ((PINC & (1 << BUTTON2_PIN)))
		{
			PORTB &= ~(1 << LED_PIN);
		}
	}
}
