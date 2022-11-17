#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define CDS_VALUE 871

void init_adc();
unsigned short read_adc();

int main() {
  unsigned short value;
  DDRA = 0xff;
  DDRB = 0x10; // 포트 B의 bit4 를 출력 상태로 세팅

  init_adc();
  
  do {
    value = read_adc();
    if (value < CDS_VALUE) {
      PORTB = 0x10; // 1ms 동안 ‘On’ 상태 유지
      _delay_ms(1);
      PORTB = 0x00; // 1ms 동안 ‘Off’ 상태 유지
      _delay_ms(1);
    }
    else {
      PORTB = 0x00; // 1ms 동안 ‘Off’ 상태 유지
      _delay_ms(1);
    }
  } while (1);
}

void init_adc() {
  ADMUX = 0x00;
  ADCSRA = 0x87;
}

unsigned short read_adc() {
  unsigned char adc_low, adc_high;
  unsigned short value;
  ADCSRA |= 0x40;
  while ((ADCSRA & 0x10) != 0x10) 
  ;
  adc_low = ADCL; 
  adc_high = ADCH;
  value = (adc_high << 8) | adc_low;
  return value;
}
