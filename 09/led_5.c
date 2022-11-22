/* LED로 X-mas Tree 만들기 */
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
        PORTA = rand(); // 0~255 난수 발생 및 LED 표시
        delay_sec(rand()%3); // 0~2 난수 delay 시간 발생 및 시간 지연
    }
}
