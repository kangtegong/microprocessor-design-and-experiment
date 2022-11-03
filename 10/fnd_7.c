#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char digit[10] = {
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
  0x08,
  0x04,
  0x02,
  0x01
};

unsigned char fnd[4];

int main() {
  int i = 0, count = 0;
  DDRC = 0xff;
  DDRG = 0x0f;
  while (1) {
    count++;
    if (count == 10000)
      count = 0;
    fnd[3] = (count / 1000) % 10;
    fnd[2] = (count / 100) % 10;
    fnd[1] = (count / 10) % 10;
    fnd[0] = count % 10;
    for (i = 0; i < 4; i++) {
      PORTC = digit[fnd[i]];
      PORTG = fnd_sel[i];
      _delay_ms(2);
    }
  }
}
