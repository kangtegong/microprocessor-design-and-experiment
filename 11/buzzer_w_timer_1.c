#include <avr/io.h>
#include <avr/interrupt.h>

#define ON 1
#define OFF 0
#define DO_data 17
volatile int state = OFF;

SIGNAL(SIG_OVERFLOW0) {
  if (state == ON) {
    PORTB = 0x00;
    state = OFF;
  } else {
    PORTB = 0x10;
    state = ON;
  }
  TCNT0 = DO_data;
}

int main() {
  DDRB = 0x10;
  TCCR0 = 0x03; // 8분주
  TIMSK = 0x01; // Overflow
  TCNT0 = DO_data;
  sei(); // 전역 인터럽트
  while (1);
}
