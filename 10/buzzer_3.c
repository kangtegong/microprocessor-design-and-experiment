#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

void buzzer(int hz, int count);
int main() {
  int i;
  DDRB = 0x10;
  while (1) {
    for (i = 0; i < 20; i++) {
      buzzer(480, 12);
      buzzer(320, 8);
    }
    _delay_ms(2000);
  }
}

void buzzer(int hz, int count) {
  int i, ms, us;
  ms = (int)(500 / (float) hz);
  us = ((500 / (float) hz) - ms) * 1000;
  for (i = 0; i < count; i++) {

    PORTB = 0x10;
    _delay_ms(ms);
    _delay_us(us);

    PORTB = 0x00;
    _delay_ms(ms);
    _delay_us(us);
  }
}
