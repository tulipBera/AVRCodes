
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define baud_rate 9600
#define LCD_data_port PORTB

void usart_init(void){
	UBRRH = 0x00;
	UBRRL = 0x33;
	UCSRB = (1<<TXEN) | (1<<RXEN);
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
}
unsigned char UART_Receive(void) {
	return UDR;
	while (!(UCSRA & (1 << RXC)));
}
/*void usart_tx(char x){
	UDR = x;
	while(!(UCSRA & (1<<UDRE)));
}


void usart_msg(const char *c){
	while(*c != 0)
	usart_tx(*c++);
}*/


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

void LCD_print(const char *str) {
	unsigned char i=0;
	while(str[i]!=0) {
		LCD_DATA(str[i]);
		i++;
	}
}

int main(void)
{
	usart_init();
	
	while (1) {
		unsigned char received_char = UART_Receive();
		char received_str[2];
		received_str[0] = received_char;
		received_str[1] = '\0';
		LCD_print(received_str);
		//LCD_print(0x0d);
		_delay_ms(1000);
	}
}
