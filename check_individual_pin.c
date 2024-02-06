/*
 * BCD_to_sevenSegment.cpp
 *
 * Created: 2/6/2024 2:26:59 PM
 * Author : rajes
 */ 

#include <avr/io.h>
#define F_CPU 1600000
#include <util/delay.h>

const unsigned int sevenSegment[] = {0x3F, 0x06};

int main(void)
{
	 DDRB = 0xFF; // Set Port B as output
	 DDRD &= ~(1 << DDD0); // Set Pin D0 as input as 0
	 //PORTD |= (1 << PORTD1); // Enable pull-up resistor for Pin D1
	/* Replace with your application code */
	while (1)
	{
		if(PIND & (1 << PIND0)){                // check a particular pin of port D, if condition gets true execute the if statement
			//left shift 0000 0001 with n times (n is the pin number of port) and and with actual all pin data of port D, and if true PIND0=1, if false PIND0=0
			PORTB = sevenSegment[1];
			_delay_ms(500);
		}
		else{
			PORTB = sevenSegment[0];
			_delay_ms(500);
		}
	}
}


