#define F_CPU 8000000UL
#include <avr/io.h> 
#include <util/delay.h>
 
int main(void)
{
    DDRB=0x20;   // PB5 out 
    TCCR1A=0x82; 
    TCCR1B=0x1A; 
    OCR1A=3000; 
    ICR1=19999; // OCR1A -> OC Clear / Fast PWM TOP = ICR1 / 8분주
    while(1)
    {
        OCR1A = 2000; // 0 degree,  >2ms pulse
        _delay_ms(1000);
        OCR1A = 1000; // 180 degree, <1ms pulse
        _delay_ms(1000);    
    }
}
