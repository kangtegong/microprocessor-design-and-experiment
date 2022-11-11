#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void buzzer(int hz, int count);

int main()
{
  int i;
  int hertz[] = {1047, 1175, 1319, 1397, 1568, 1760, 1795, 2093};             // 도~도 주파수
  int loop[] = {1047, 1175, 1319, 1397, 1568, 1760, 1795, 2093}; // 1초간 실행 횟수
  DDRB = 0x10;                            // PB4 만 출력으로 설정 
  while(1)                                   
  {
    for (i=0; i<8; i++)
      buzzer(hertz[i], loop[i]);          // 도~도 음 생성, 1초간
    _delay_ms(1000);              // 도~도 음 생성 후1초 동안 묵음
    }
}

void buzzer(int hz, int count)                         // hz 의 주파수를 갖는 펄스를 count 개수만큼 생성
{
  int i, ms, us;
  ms = 1000/(2*hz);                                   // 1개 펄스의 ON 또는 OFF의 ms 단위 시간
  us = (1000.0/(2*hz) - ms) * 1000;            // 1개 펄스의 ON 또는 OFF의 us 단위 시간
  for(i=0; i<count; i++)
  {
    PORTB |= 1 << 4;              // buzzer ON
    _delay_ms(ms);                        // (ms)ms동안 delay
    _delay_us(us);                         // (us)us 동안 delay         
    PORTB &= ~(1 << 4);                      // buzzer OFF
    _delay_ms(ms);                       // (ms)ms 동안 delay
    _delay_us(us);                         // (us)us 동안 delay
  }
}
