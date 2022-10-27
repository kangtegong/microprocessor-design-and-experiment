/* GPIO로 LED 켜고 끄기
LED 8개가 연결되어 있는 포트 : Port A(PA)
- 비트7 : LED7(LD1)
- 비트6 : LED6(LD2)
- 비트5 : LED5(LD3)
- 비트4 : LED4(LD4)
- 비트3 : LED3(LD5)
- 비트2 : LED2(LD6)
- 비트1 : LED1(LD7) 
- 비트0 : LED0(LD8) 
*/

#include <avr/io.h> // ATmega128 register 정의
int main()
{
    DDRA = 0xff; // 포트 A를 출력 포트로 사용
    PORTA = 0xff; // 0xff = 0b11111111, LED 모두 ON
}

