/*
 * 출력 버퍼 (\r) 비우는 로직 추가할 것
*/
#include <avr/io.h>
#define NULL 0

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
 unsigned char c;
 unsigned int a;
 
 UBRR0H = 0;
 UBRR0L = 8;

 UCSR0B = 0x18;
 UCSR0C = 0x06;

 DDRA = 0xff;
 PORTA = 0x00;

 char ch[2];

 while(1){
    ch[0] = getchar0();
    ch[1] = getchar0();

    a = ch[0] - '0';

    if (a == 0) {
		puts0("led off\n\r");
		PORTA = 0x00;
	} 
	else {
		puts0("led on\n\r");
		PORTA = 0xff;
	}

	ch[1] = '\r';

}
