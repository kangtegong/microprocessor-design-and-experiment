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

int main()
{
    DDRA = 0xFF;

    // ex.1
    // set_led(0b10101010);

    // ex.2
    set_led_ms(0b10101010, 1000);
    set_led_ms(0b01010101, 1000);
    set_led_ms(0b11111111, 1000);
}
