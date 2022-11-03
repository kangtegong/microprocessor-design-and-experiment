#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char digit[21] = {
  0x00,
  0x00,
  0x00,
  0x00,
  0x3f,
  0x06,
  0x3f,
  0x40,
  0x66,
  0x3f,
  0x06,
  0x7c,
  0x40,
  0x06,
  0x3f,
  0x7f,
  0x06,
  0x00,
  0x00,
  0x00,
  0x00
};
unsigned char fnd_sel[4] = {
  0x08,
  0x04,
  0x02,
  0x01
};
int main() {
  int i, j, k;
  DDRC = 0xff;
  DDRG = 0x0f;

  while (1) {
    for (k = 0; k < 13 + 4; k++) {
      for (j = 0; j < 100; j++) {
        for (i = 0; i < 4; i++) {
          PORTC = digit[i + k];
          PORTG = fnd_sel[i];
          _delay_ms(2);
        }
      }
    }
  }
}
