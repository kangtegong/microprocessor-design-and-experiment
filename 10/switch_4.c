#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define STOP 0
#define GO 1

volatile int cur_time = 0;
volatile int stop_time = 0;
volatile int state = STOP; 

unsigned char digit[] = {
  0x3f,
  0x06,
  0x5b,
  0x4f,
  0x66,
  0x6d,
  0x7c,
  0x07,
  0x7f,
  0x67
};

unsigned char fnd_sel[4] = {
  0x01,
  0x02,
  0x04,
  0x08
};

SIGNAL(SIG_INTERRUPT4) {
  if (state == STOP)
    state = GO; // STOP ? GO
  else {
    state = STOP; // GO ? STOP
    stop_time = cur_time; // 현재시간 복사
  }
}
SIGNAL(SIG_INTERRUPT5) {
  state = STOP; // 초기화, 리셋
  cur_time = 0;
  stop_time = 0;
}

void init() {
  DDRC = 0xff; // FND Data
  DDRG = 0x0f; // FND Select
  DDRE = 0xcf; // INT4, 5
  PORTC = digit[0];
  PORTG = 0x0f;
  EICRB = 0x0a; //falling edge
  EIMSK = 0x30; //interrupt en
  SREG |= 1 << 7;
}

void display_fnd(int count) // 수행시간 = 약 10ms
{
  int i, fnd[4];
  fnd[3] = (count / 1000) % 10; // 천 자리
  fnd[2] = (count / 100) % 10; // 백 자리
  fnd[1] = (count / 10) % 10; // 십 자리
  fnd[0] = count % 10; // 일 자리
  for (i = 0; i < 4; i++) {
    PORTC = digit[fnd[i]];
    PORTG = fnd_sel[i];
    _delay_ms(2 + i % 2);
  }
}

int main() {
  init();
  while (1) {
    if (state == STOP)
      display_fnd(stop_time);
    else
      display_fnd(cur_time);
    cur_time++;
  }
}
