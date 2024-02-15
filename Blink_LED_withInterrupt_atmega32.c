#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
   DDRC |= (1<<PINC0) | (1<<PINC1);
   DDRD &= ~(1<<PIND2);
   PORTD |= (1<<PIND2);
   PORTC = 0x01;
   GICR |= (1<<INT0);
   //MCUCR |= (1<<ISC01);
   sei();
    while (1) 
    {
		PORTC |= (1<<PINC0);
		_delay_ms(50);
		PORTC &= ~(1<<PINC0);
		_delay_ms(50);
    }
	return 0;
}

ISR (INT0_vect){
	for(unsigned char i=0; i<5; i++){
	PORTC |= (1<<PINC1);
	_delay_ms(50);
	PORTC &= ~(1<<PINC1);
	_delay_ms(50);
	}
}


