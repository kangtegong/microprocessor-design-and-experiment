#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define ON 1
#define OFF 0

int main() {
  int state = OFF;
  DDRA = 0xff; // Port A 출력
  DDRE = 0x00; // Port E 입력

  while (1) { // SW1 검사
    if ((PINE & 0x10) == 0x00) {
      if (state == OFF) {
        PORTA = 0xff;
        state = ON;
      } else {
        PORTA = 0x00;
        state = OFF;
      }
      _delay_ms(300);
    }
  }
}