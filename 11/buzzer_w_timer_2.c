#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL

#define DO 0
#define RE 1
#define MI 2
#define FA 3
#define SOL 4
#define LA 5
#define SI 6
#define DDO 7
#define EOS - 1

#define ON 1
#define OFF 0
volatile int state = OFF;
volatile int tone;

char t_table[8] = {
  17,
  43,
  66,
  77,
  97,
  114,
  117,
  137
};

int f_table[8] = {
  1047 / 2,
  1175 / 2,
  1319 / 2,
  1397 / 2,
  1568 / 2,
  1760 / 2,
  1796 / 2,
  2093 / 2
};

int song[] = {
  DO,
  RE,
  MI,
  FA,
  SOL,
  LA,
  SI,
  DDO,
  EOS
};

SIGNAL(SIG_OVERFLOW0) {
  if (state == ON) {
    PORTB = 0x00;
    state = OFF;
  } else {
    PORTB = 0x10;
    state = ON;
  }
  TCNT0 = t_table[tone];
}

int main() {
  int i = 0;
  DDRB = 0x10;
  TCCR0 = 0x03; // 8분주
  TIMSK = 0x01; // Overflow
  TCNT0 = t_table[song[i]];
  sei(); // 전역 인터럽트
  do {
    tone = song[i++];
    _delay_ms(f_table[tone]);
  } while (tone != EOS);
}
