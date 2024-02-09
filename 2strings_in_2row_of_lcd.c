//LCD_control_port = PORTD
//RS = PORTD0
//RW = PORTD1
//EN = PORTD2


#include <avr/io.h>
#define F_CPU 1600000
#include <util/delay.h>

#define LCD_data_port PORTB

void LCD_Command(unsigned char commnad){
	PORTD = 0x00;
	LCD_data_port = commnad;
	PORTD = 0x04;
	_delay_ms(1);
	PORTD = 0x00;
	LCD_data_port = commnad<<4;
	PORTD = 0x04;
	_delay_ms(1);
	PORTD = 0x00;
}

void LCD_DATA(unsigned char data){
	PORTD = 0x01;
	LCD_data_port = data;
	PORTD = 0x05;
	_delay_ms(1);
	PORTD = 0x01;
	LCD_data_port = data<<4;
	PORTD = 0x05;
	_delay_ms(1);
	PORTD = 0x01;
}

void LCD_init(){
	DDRB = 0xFF;
	DDRD = 0xFF;
	PORTD = 0x00;
	LCD_Command(0x32);
	LCD_Command(0x0E);
	LCD_Command(0x01);
	LCD_Command(0x28);
	_delay_ms(2);
}

void LCD_print(const char *str){
	unsigned char i=0;
	while(str[i]!=0){
		LCD_DATA(str[i]);
		i++;
	}
}
int main(void)
{
	LCD_init();
	LCD_print("Hello!! Tulip!!");
	LCD_Command(0xC0);
	LCD_print("Good Morning");
	while (1);
	return 0;
}
