#include <avr/io.h>
#define NULL 0

unsigned char digit[10] = {
  0x3f,
  0x06,
  0x5b,
  0x4f,
  0x66,
  0x6d,
  0x7c,
  0x07,
  0x7f,
  0x67
};

// 1바이트를 송신(transmit)하는 함수
void putchar0(unsigned char c){
 while(!(UCSR0A & 0x20));
 UDR0 = c;
}

unsigned char getchar0() {
    while(!(UCSR0A & 0x80));
    return (UDR0);
}

// string 송신하는 함수
void puts0(unsigned char *ptr){
    while(1){
        if(*ptr != NULL)
        putchar0(*ptr++);
    else
        return;
 }
}

int main(void){
 unsigned char prompt[] = "minchul > ";
 unsigned char *ptr;
 unsigned char c;
 unsigned int a;
 
 UBRR0H = 0;
 UBRR0L = 8;

 UCSR0B = 0x18;
 UCSR0C = 0x06;

 DDRC = 0xff; // C 포트는 모두 출력
 DDRG = 0x0f; // G 포트도 4개는 출력

 while(1){
    c = getchar0( );
    putchar0(c);
  
    a = c - '0';
    if (0 <= a && a <= 9) {
	    PORTC = digit[a]; // '0' 표현
	    PORTG = 0x01; // 가장 우측의 digit 선택
	} 

    if (c == '\r')
    {
        putchar0('\n');
        ptr = prompt;
        puts0(ptr);
    }
 }

}
