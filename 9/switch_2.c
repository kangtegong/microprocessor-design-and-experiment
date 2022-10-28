/* 공식 강의 자료 소스 코드에 오류 */
#include <avr/io.h> // ATmega128 register 정의
#include <util/delay.h>

int main(){
	unsigned char data = 0x00; // 초기 data값 = 0x00

	DDRA = 0xff; // Port A 출력
	DDRE = 0x00; // Port E 입력

	while (1)
	{
		if((PINE & 0x10) == 0x00) // SW1 검사
		{ 
			data = ~data;
			PORTA = data; // 데이터 Toggle
			_delay_ms(300); // bouncing 무시
		}
	}
}
