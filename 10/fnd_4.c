#include <avr/io.h>
// #include <stdio.h>
#include <util/delay.h>

#define FND_A   0x01
#define FND_B   0x02
#define FND_C   0x04
#define FND_D   0x08
#define FND_E   0x10
#define FND_F   0x20
#define FND_G   0x40
#define FND_DP  0x80


int main()
{
    DDRC = 0xFF;
    DDRG = 0x0F;

    PORTG = 0x0F;


    while(1) {
        // 1
        PORTG = 0x08;
        PORTC = FND_B | FND_C;
        _delay_ms(2); // 잔상효과 고려. 크게 값을 취하면 잔상 떨어짐
        // 2
        PORTG = 0x04;
        PORTC = FND_A | FND_B | FND_D | FND_E | FND_G;
        _delay_ms(2);
        // 3
        PORTG = 0x02;
        PORTC = FND_A | FND_B | FND_C | FND_D | FND_G;
        _delay_ms(2);
        // 4
        PORTG = 0x01;
        PORTC = FND_B | FND_C | FND_F | FND_G;
        _delay_ms(2);
    }

}
