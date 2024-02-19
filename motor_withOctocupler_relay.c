#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define BUTTON_PIN1 PD2
#define BUTTON_PIN2 PD3
#define OCTOCUPLER_PIN PC0
#define LED_PIN PC5

//volatile bool OCTOCUPLER_status = false;

int main(void)
{
	DDRD = 0x00;
	PORTD &= ~(1 << BUTTON_PIN1);
	PORTD &= ~(1 << BUTTON_PIN2);
	

	DDRC = 0xFF;
	PORTC &= ~(1 << OCTOCUPLER_PIN);
	PORTC &= ~(1 << LED_PIN);

	GICR |= (1 << INT0)|(1<<INT1);

	MCUCR = 0x00;
	sei();

	while (1)
	{
		//if(OCTOCUPLER_status == false){
			PORTC |= (1 << LED_PIN);
			_delay_ms(50);
			PORTC &= ~(1 << LED_PIN);
			_delay_ms(50);
		//}
	}
	return 0;
}

ISR(INT0_vect)
{
	PORTC |= (1<<OCTOCUPLER_PIN);
	//OCTOCUPLER_status = true;
}
ISR(INT1_vect){
	PORTC &= ~(1<<OCTOCUPLER_PIN);
	//OCTOCUPLER_status = false;
}
