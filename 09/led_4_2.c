/* GPIO로 LED 움직임 표현하기 : Binary Counter 구현 */
#include <avr/io.h> // ATmega128 register 정의
#include <util/delay.h>

int main()
{
    unsigned char count=0; // LED용 count는 양수 1 바이트
    DDRA = 0xff; // 포트 A를 출력 포트로 사용
    while(1) // 무한루프 실행
    {
        count = count + 1; // count 1 증가
        PORTA = count; // LED에 숫자 표시
        _delay_ms(1000); // 1초 기다림
    }
} 

