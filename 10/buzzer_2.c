#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void buzzer(int hz);

int main() {
  DDRB = 0x10; // 포트 B의 bit4 를 출력 상태로 세팅
  while(1) {
      buzzer(500);
  }
}

void buzzer(int hz) {
  int ms = (int)(500 / (float) hz);

  PORTB = 0x10;
  _delay_ms(ms);

  PORTB = 0x00;
  _delay_ms(ms);
}
