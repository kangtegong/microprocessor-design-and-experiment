#include <avr/io.h>
#include <avr/interrupt.h>

#define ON  1
#define OFF 0

volatile int state = OFF;
volatile int tone_index = 0;

char TCNT0s[8] = {
	17, 43, 66, 77, 97, 114, 117, 137
};

ISR(TIMER0_OVF_vect) {
	// set tone (set count)
	TCNT0 = TCNT0s[tone_index];

	// switch state
	if (state == OFF) {
		PORTB |= 0x10;
		state = ON;
	} else {
		PORTB &= 0xEF;
		state = OFF;
	}
}


void init_buzzer() {
	DDRB |= 0x10;
	TCCR0 = 0x03; 
	TIMSK = 0x01; 
	sei(); // global interrupt enable
}

void set_tone_next() {
	tone_index = (tone_index + 1) % 8;
}

void simple_test() {
	int count = 1000;
	while (count--) {
		PORTB = 0x10;
		_delay_ms(1);
		PORTB = 0x00;
		_delay_ms(1);
	}
}
