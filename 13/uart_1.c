#include <avr/io.h>
#define NULL 0
// 1 char를 송신(Transmit)하는 함수
void putchar0(unsigned char c) 
{
  /* 실제 프로그램할 때는 숫자값을 직접 쓰기 않고 Macro(UDRE0)를 사용하거나
   * #define 으로 정의한 것을 사용하는 것이 편리
   */
  while (!(UCSR0A & 0x20)); // UDRE : UCSR0A 6번 비트
  UDR0 = c; // 1 character 전송
}
int main() {
  int i;
  // \n(New Line), \r(Carrage Return)
  unsigned char data[] = "Hi~\n\r"; // 보내고 싶은 문자열
  UBRR0H = 0; // 12비트가 의미를 가짐,
  UBRR0L = 8; // 16Mhz, 115200 baud의 경우  
  UCSR0B = 0x08; // Transmit(TX) Enable
  UCSR0C = 0x06; // UART Mode, 8 Bit Data, No Parity, 1 Stop Bit
  while (1) // 연속적으로 보내기
  {
    i = 0;
    while (data[i] != NULL) // check String End
      putchar0(data[i++]); // 순서대로 보내기
  }
}