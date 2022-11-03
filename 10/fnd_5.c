#include <avr/io.h>
int main()
{
    DDRC = 0xff; // C 포트는 모두 출력
    DDRG = 0x0f; // G 포트도 4개는 출력
    PORTC = 0x3f; // '0' 표현
    PORTG = 0x01; // 가장 우측의 digit 선택
}
