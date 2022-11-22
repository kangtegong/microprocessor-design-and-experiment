/* LED로 X-mas Tree 만들기 */
#include <avr/io.h> // ATmega128 register 정의
#include <util/delay.h>

int main( )
{
    DDRA = 0xff; // 포트 A를 출력 포트로 사용
    while(1) // 무한루프 실행
    {
        PORTA = rand(); // 0~255 난수 발생 및 LED 표시
        _delay_ms(rand()%3 * 1000); 
    }
}
