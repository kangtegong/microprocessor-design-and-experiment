#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

void set_led(unsigned char bits) {
    DDRA |= bits;
    PORTA = bits;
}

void set_led_ms(unsigned char bits, int ms) {
    set_led(bits);
    _delay_ms(ms);
}
