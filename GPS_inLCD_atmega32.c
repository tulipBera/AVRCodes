#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <string.h> 

#define baud_rate 9600
#define Buffer_Size 150
#define LCD_data_port PORTC

char GGA_Buffer[Buffer_Size];
volatile uint16_t Index;
bool IsItGGAString = false;

void usart_init(void) {
	UBRRH = 0;
	UBRRL = 103; // Set UBRR to 103 for 9600 baud rate
	UCSRB = (1 << TXEN) | (1 << RXEN) | (1 << RXCIE); // Enable RX and RX interrupt
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void LCD_Command(unsigned char command) {
	PORTA = 0x00;
	LCD_data_port = command;
	PORTA = 0x04;
	_delay_ms(1);
	PORTA = 0x00;
}

void LCD_DATA(unsigned char data) {
	PORTA = 0x01;
	LCD_data_port = data;
	PORTA = 0x05;
	_delay_ms(1);
	PORTA = 0x01;
}

void LCD_init() {
	DDRC = 0xFF;
	DDRA = 0xFF;
	PORTA = 0x00;
	_delay_ms(15); // Wait for LCD to power up
	LCD_Command(0x38); // 8-bit mode, 2 lines, 5x7 font
	_delay_ms(1);
	LCD_Command(0x0E); // Display ON, Cursor ON
	_delay_ms(1);
	LCD_Command(0x01); // Clear display
	_delay_ms(2);
	LCD_Command(0x06); // Increment cursor, no display shift
	_delay_ms(1);
}

void LCD_print(const char *str) {
	unsigned char i = 0;
	while (str[i] != 0) {
		LCD_DATA(str[i]);
		i++;
	}
}

ISR(USART_RXC_vect) {
	char received_char = UDR;
while(!(UCSRA & (1<<UDRE)));

	if (received_char == '$') {
		Index = 0;
		IsItGGAString = true;
	}

	if (IsItGGAString) {
		GGA_Buffer[Index++] = received_char;
		if (received_char == '\n') {
			IsItGGAString = false;
			GGA_Buffer[Index] = '\0';
			Index = 0;
			LCD_print(GGA_Buffer);
		}
	}
}

int main(void) {
	cli();
	usart_init();
	LCD_init();
	_delay_ms(3000);
	sei();

	while (1) {
		if (IsItGGAString && (GGA_Buffer[0] == '$' && GGA_Buffer[1] == 'G' && GGA_Buffer[2] == 'P' && GGA_Buffer[3] == 'G' && GGA_Buffer[4] == 'G' && GGA_Buffer[5] == 'A')) {
			LCD_print(GGA_Buffer);
		}

		IsItGGAString = false;
		Index = 0;
	}
	return 0;
}
