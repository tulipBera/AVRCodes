#include <avr/io.h>
#define F_CPU 1600000
#include <util/delay.h>

#define Relay_PIN     PB1   
#define BUTTON1_PIN PC0  
#define BUTTON2_PIN PC1   

int main(void)
{
	DDRB = 0xFF;
	PORTB &= ~(1 << Relay_PIN );
	DDRC = 0x00;
	PORTC |= (1 << BUTTON1_PIN);
	PORTC |= (1 << BUTTON2_PIN);
	PORTB &= ~(1 << Relay_PIN );
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
