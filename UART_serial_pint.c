#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define baud_rate 9600

char tx_data;

void usart_init(void){
	UBRRH = 0x00;
	UBRRL = 0x33;
	UCSRB = (1<<TXEN) | (1<<RXEN);
	UCSRC = (1<<URSEL) | (3<<UCSZ0);
}

void usart_tx(char x){
	UDR = x;
	while(!(UCSRA & (1<<UDRE)));
}


void usart_msg(const char *c){
	while(*c != 0)
	usart_tx(*c++);
}

int main(void)
{
	usart_init();
	while(1){
		usart_msg("Hello Tulip!! Good Morning!!");
		usart_tx(0x0d);
		_delay_ms(1000);
		
	}
}
