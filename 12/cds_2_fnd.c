#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define CDS_VALUE 871

void init_adc();
unsigned short read_adc();

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
  unsigned short value;
  DDRC = 0xff;
  DDRG = 0x0f;

  DDRA = 0xff;
  init_adc();
  while (1) {
    value = read_adc();
    fnd[3] = (value / 1000) % 10;  // 큰 의미 x
    fnd[2] = (value / 100) % 10;	// 큰 의미 x
    fnd[1] = (value / 10) % 10;
    fnd[0] = value % 10;
    for (int i = 0; i < 4; i++) {
      PORTC = digit[fnd[i]];
      PORTG = fnd_sel[i];
      _delay_ms(2);
    }
  }
}

void init_adc() {
  ADMUX = 0x00;
  // REFS(1:0) = "00" AREF(+5V) 기준전압 사용
  // ADLAR = '0' 디폴트 오른쪽 정렬
  // MUX(4:0) = "00000" ADC0 사용, 단극 입력
  ADCSRA = 0x87;
  // ADEN = '1' ADC Enable
  // ADFR = '0' single conversion 모드
  // ADPS(2:0) = "111" 프리스케일러 128분주
}

unsigned short read_adc() {
  unsigned char adc_low, adc_high;
  unsigned short value;
  ADCSRA |= 0x40; // ADC start conversion, ADSC = '1'
  while ((ADCSRA & 0x10) != 0x10) // ADC 변환 완료 검사
  ;
  adc_low = ADCL; // 변환된 Low 값 읽어오기
  adc_high = ADCH; // 변환된 High 값 읽어오기
  value = (adc_high << 8) | adc_low;
  // value 는 High 및 Low 연결한 16비트값
  return value;
}
