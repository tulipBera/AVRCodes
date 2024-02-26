//https://circuitdigest.com/microcontroller-projects/gps-module-interfacing-with-atmega16-32-avr-microcontroller


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#define USART_BAUDRATE 9600

#define LCDPORTDIR DDRB
#define LCDPORT PORTB
#define rs 0
#define rw 1
#define en 2

#define RSLow (LCDPORT &= ~(1 << rs))
#define RSHigh (LCDPORT |= (1 << rs))
#define RWLow (LCDPORT &= ~(1 << rw))
#define ENLow (LCDPORT &= ~(1 << en))
#define ENHigh (LCDPORT |= (1 << en))

enum {
	CMD = 0,
	DATA,
};

char buf[100];
volatile int ind = 0, flag, stringReceived = 0;
char gpgga[] = {'$', 'G', 'P', 'G', 'G', 'A'};
char latitude[10];
char longitude[10];
char time[7];

ISR(USART_RXC_vect) {
	char ch = UDR;
	buf[ind] = ch;
	ind++;
	if (ind < 7) {
		if (buf[ind - 1] != gpgga[ind - 1]) // $GPGGA
		ind = 0;
	}
	if (ind >= 50)
	stringReceived = 1;
}

void uart_write(char ch) {
	while (!(UCSRA & (1 << UDRE)));
	UDR = ch;
}


void uart_begin() {
	UCSRC = (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRH = 0x00;
	UBRRL = 0x33;
	UCSRB = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);
}

void lcdwrite(char ch, char r) {
	LCDPORT = ch & 0xF0;
	RWLow;
	if (r == 1)
	RSHigh;            //Set RS (Register Select) high for data mode
	else
	RSLow;             //Set RS (Register Select) low for command mode
	ENHigh;            // set enable as high for transfer data
	_delay_ms(1);
	ENLow;
	_delay_ms(1);
	LCDPORT = ch << 4 & 0xF0;
	RWLow;
	if (r == 1)
	RSHigh;
	else
	RSLow;
	ENHigh;
	_delay_ms(1);
	ENLow;
	_delay_ms(1);
}

void lcdprint(char *str) {
	while (*str) {
		lcdwrite(*str++, DATA);
	}
}

void lcdbegin() {
	char lcdcmd[5] = {0x02, 0x28, 0x0E, 0x06, 0x01};
	for (int i = 0; i < 5; i++)
	lcdwrite(lcdcmd[i], CMD);
}

int main() {
	LCDPORTDIR = 0xFF;
	uart_begin();
	lcdbegin();
	lcdprint("GPS Interfacing");
	lcdwrite(0xC0, CMD);
	lcdprint("Using Atmega32 ");
	_delay_ms(1000);
	lcdwrite(0x01, 0);
	lcdprint("Waiting for GPS");
	_delay_ms(1000);
	lcdwrite(0x01, 0);
	sei();
	while (1) {
		if (stringReceived == 1) {
			cli();
			for (int i = 0; i < ind; i++)
			uart_write(buf[i]);
			ind = 0;
			stringReceived = 0;
			lcdwrite(0x80, 0);
			//lcdprint("Lat:");
			for (int i = 18; i < 27; i++) {
				latitude[i - 18] = buf[i];
				//lcdwrite(latitude[i - 18], 1);
			}
			char Latitude[] = {latitude[0], latitude[1], latitude[4], latitude[2], latitude[3], latitude[5], latitude[6], latitude[7], latitude[8]};
			for (int i=0; i<9; i++)
			{
				lcdwrite(Latitude[i], 1);
			}
			lcdwrite(0xC0, 0);
			//lcdprint("Lon:");
			for (int i = 31; i < 40; i++) {
				longitude[i - 31] = buf[i];
				//lcdwrite(longitude[i - 31], 1);
			}
			char Longitude[] = {longitude[0], longitude[1], longitude[4], longitude[2], longitude[3], longitude[5], longitude[6], longitude[7], longitude[8]};
			for (int i=0; i<9; i++)
			{
				lcdwrite(Longitude[i], 1);
			}
			// Clear the buffer
			for (int i = 0; i < 100; i++) {
				buf[i] = 0;
			}
			_delay_ms(500);
			sei();
		}
	}
	return 0;
}
