// 방향제어
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRB|=0x20;
	PORTB|=0x20;

	TCCR1A=0x82;
	TCCR1B=0x1b;
	ICR1=4999;     //TOP 0부터 시작
	OCR1A=375;     //0도
	while(1)
	{
		OCR1A=500;     //-90도
		_delay_ms(1000);
		OCR1A=500;     //90도
		_delay_ms(1000);
	}
}
