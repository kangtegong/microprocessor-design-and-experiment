#include <avr/io.h>
// #include <stdio.h>
#include <util/delay.h>

int main()
{
    DDRC = 0xFF;
    DDRG = 0x0F;

    PORTG = 0x0F;


    while(1) {
        for(int i = 0; i < 8; i++) {
            PORTC = 1 << i;
            _delay_ms(1000);
        }        
    }

}
