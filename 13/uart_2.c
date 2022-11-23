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
 unsigned char prompt[] = "minchul > ";
 unsigned char *ptr;
 unsigned char c;
 
 UBRR0H = 0;
 UBRR0L = 8;

 UCSR0B = 0x18;
 UCSR0C = 0x06;

 while(1){
    c = getchar0( );
    putchar0(c);
    if (c == '\r')
    {
        putchar0('\n');
        ptr = prompt;
        puts0(ptr);
    }
 }

}
