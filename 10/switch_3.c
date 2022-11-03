#include <avr/io.h> // ATmega128 register 정의
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};
unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};
volatile int count = 0;

SIGNAL(SIG_INTERRUPT4)
{
count++;
_delay_ms(1);
}

void display_fnd(int count)
{ 
    int i, fnd[4];
    fnd[3] = (count/1000)%10; // 천 자리
    fnd[2] = (count/100)%10; // 백 자리
    fnd[1] = (count/10)%10; // 십 자리
    fnd[0] = count%10; // 일 자리
    for (i=0; i<4; i++)
    { 
        PORTC = digit[fnd[i]];
        PORTG = fnd_sel[i];
        _delay_ms(2+i%2);
    }
}

int main()
{
    DDRC = 0xff; // C 포트는 FND 데이터 신호
    DDRG = 0x0f; // G 포트는 FND 선택 신호
    DDRE = 0xef; // 0b11101111, PE4(switch1)는 입력
    EICRB = 0x02; // INT4 = falling edge
    EIMSK = 0x10; // INT4 interrupt enable
    SREG |= 1<<7; // SREG bit7 = I (Interrupt Enable)
while (1)
    display_fnd(count); // FND Display
} 
