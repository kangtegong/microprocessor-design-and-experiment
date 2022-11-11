#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define SERVO_DEG_0 450
#define SERVO_DEG_P90 700
#define SERVO_DEG_M90 250

void timer_init()
{
	TCCR1A = 0x82;
	TCCR1B = 0x1B;
	ICR1 = 4999;
	OCR1A = SERVO_DEG_0;
	TCNT1 = 0x00;
}

int main(void)
{	
	
	DDRB = 0xFF;
	PORTB = 0x00;
	
	timer_init();
	
    while (1) 
    {
		OCR1A = SERVO_DEG_M90;
		_delay_ms(1000);
		
		OCR1A = SERVO_DEG_0;
		_delay_ms(1000);
		
		OCR1A = SERVO_DEG_P90;
		_delay_ms(1000);
		
		
		OCR1A = SERVO_DEG_0;
		_delay_ms(1000);
    }
}
