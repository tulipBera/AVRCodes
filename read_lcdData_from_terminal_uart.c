#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define baud_rate 9600
#define LCD_data_port PORTB

char tx_data;

void usart_init(void) {
	UBRRH = 0x00;
	UBRRL = 0x33;
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

unsigned char usart_rx(void) {
	while (!(UCSRA & (1 << RXC)));
	return UDR;
}

void LCD_Command(unsigned char command) {
	PORTD = 0x00;
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
	DDRB = 0xFF;
	DDRA = 0xFF;
	PORTA = 0x00;
	LCD_Command(0x0E);
	LCD_Command(0x01);
	_delay_ms(2);
}

void LCD_print_char(char c) {
	LCD_DATA(c);
}

void LCD_print(const char *str) {
	while (*str != '\0') {
		LCD_DATA(*str++);
	}
}

int main(void) {
	usart_init();
	LCD_init();
	
	while (1) {
		tx_data = usart_rx();
		LCD_print_char(tx_data);
	}
}
