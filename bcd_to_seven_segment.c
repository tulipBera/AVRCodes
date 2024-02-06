/*
 * BCD_to_sevenSegment.cpp
 *
 * Created: 2/6/2024 2:26:59 PM
 * Author : rajes
 */ 

#include <avr/io.h>
#define F_CPU 1600000
#include <util/delay.h>

const unsigned int sevenSegment[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int main(void) {
	DDRB = 0xFF; // Set PORTB as output
	
	while (1) {
		uint8_t digit = (PIND & 0x0F); // Collect the lower 4 bits as input from PORTD
		if (digit <= 9) {
			PORTB = sevenSegment[digit];
			} else {
			PORTB = sevenSegment[0]; // Display 0 if digit is greater than 9
		}
		_delay_ms(100); // Delay for better visualization
	}
	return 0;
}


