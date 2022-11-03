#define F_CPU 16000000UL
#include <avr/io.h> // ATmega128 register 정의
#include <avr/interrupt.h> // interrupt 관렦
#include <util/delay.h>

volatile unsigned char data = 0x00; // 초기 data값 = 0x00

SIGNAL(SIG_INTERRUPT4)
{
	data = ~data;
}

void display_led(int data)
{ 
    PORTA = data; // 데이터 Toggle
	_delay_ms(300); // bouncing 무시
}

int main()
{
	DDRA = 0xff; // Port A 출력
    DDRE = 0xef; // 0b11101111, PE4(switch1)는 입력
    
    EICRB = 0x02; // INT4 = falling edge
    EIMSK = 0x10; // INT4 interrupt enable
    SREG |= 1<<7; // SREG bit7 = I (Interrupt Enable) == sei();

while (1)
    display_led(data); // FND Display
}
