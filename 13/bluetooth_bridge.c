// JMOD-BT-1 통신 및 셋업을 위한 JMOD-128-1 용 브릿지 프로그램
// 작성자 : 제이씨넷

#include <avr/io.h>

#define F_CPU 16000000UL

#define BAUD_DIV  (F_CPU/8/BAUD - 1)
#define BAUD_DIV_H BAUD_DIV >> 8
#define BAUD_DIV_L BAUD_DIV
#define BAUD 38400 // 115200 for JMOD-BT-1, 9600 for fb155bc, 38400 for HC-05, 9600 for HC-06

#include <util/delay.h>

#define TX_CH(ch, val) do { while(!(UCSR##ch##A & 0x20)); UDR##ch=val; } while(0)
#define RX_CH(ch, val) do { while(!(UCSR##ch##A & 0x80)); val = UDR##ch;  } while(0)
#define  AVAIL_RX(ch )  (UCSR##ch##A & 0x80)

int main(void){
    char ch;

    UCSR0A = 2; UCSR0B=0x18; UBRR0H=BAUD_DIV_H ; UBRR0L=BAUD_DIV_L;
    UCSR1A = 2; UCSR1B=0x18; UBRR1H=BAUD_DIV_H ; UBRR1L=BAUD_DIV_L;
    while(1){
        if(AVAIL_RX(0))
        {
            RX_CH(0, ch);
            TX_CH(1, ch);
        }
        if(AVAIL_RX(1))
        {
            RX_CH(1, ch);
            TX_CH(0, ch);
        }
    }
}