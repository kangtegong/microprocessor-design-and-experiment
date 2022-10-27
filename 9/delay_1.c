#include <avr/io.h> // ATmega128 register 정의
void delay_sec(int sec)
{
    volatile int i, j, k;
    for (i=0; i<sec; i++)
        for (j=0; j<1000; j++)
            for (k=0; k<1000; k++)
            ;
}

int main( )
{

    DDRA = 0xff; // 포트 A를 출력 포트로 사용
    while(1) // 무한루프 실행
    {
        PORTA = 0xff; // LED 모두 ON
        delay_sec(1); // 1초 기다림
        PORTA = 0x00; // LED 모두 OFF
        delay_sec(1); // 1초 기다림
    }
