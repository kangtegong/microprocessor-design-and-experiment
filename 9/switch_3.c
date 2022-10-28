/* 추가 예제 */
#define F_CPU 16000000UL	/** MPU operating frequency setting */

#include <stdint.h>			/** type uint */
#include <avr/io.h>			/** DDR, PORT etc. GPIO port */
#include <util/delay.h>		/** _delay_ms function */

int main(void)
{	
	DDRA = 0xff;	/* LED 0 ~ 7 port all output */
	DDRE = 0xcf;	/* SW1, SW2 port all input */
	PORTA = 0x00;   /* LED all off */			
	
    while (1) 
    {
		if(!((PINE & 0x10) | (PINE & 0x20))) {	/** push all sw */
			PORTA = 0xff;
		}
		else if(!(PINE & 0x10)) {		/** push sw1 */
			PORTA = 0x0f;
		}
		else if(!(PINE & 0x20)) {		/** push sw2 */
			PORTA = 0xf0;
		}
		else {							
			PORTA = 0x00;
		}
    }
	
	return 0;
}

