#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

/*
	Turn on 1 FND
	USED PIN: C G
	select: 0, 1, 2, 3
	data: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
*/
void set_fnd1(int select, int data) {
	/*
	* PORTC = DP-G-F-E-D-C-B-A
	*
	*  AAAA
	* F    B
	* F    B
	*  GGGG
	* E    C
	* E    C
	*  DDDD  DP
	*/

	DDRC  = 0xff; // 1111 1111 : set ddc7 ~ ddc0 to write FND DATA
	DDRG |= 0x0f; // 0000 1111 : set ddg3 ~ ddg0 to write FND SELECT

	// Select the FND to on
	PORTG = 0x8 >> (select % 4);

	// On FND with data
	switch (data) {
		case 0 : PORTC = 0b00111111; break;
		case 1 : PORTC = 0b00000110; break;
		case 2 : PORTC = 0b01011011; break;
		case 3 : PORTC = 0b01001111; break;
		case 4 : PORTC = 0b01100110; break;
		case 5 : PORTC = 0b01101101; break;
		case 6 : PORTC = 0b01111101; break;
		case 7 : PORTC = 0b00100111; break;
		case 8 : PORTC = 0b01111111; break;
		case 9 : PORTC = 0b01101111; break;
		default: PORTC = 0b10000000; break;
	}
}

/*
	Turn on 4 FND
	USED PIN: C G
*/
void set_fnd4(int data, unsigned int ms) {
	unsigned int time = 5;
	unsigned int max_time = ms * F_CPU / 1777000;
	int data0 = (data / 1000) % 10; // 5
	int data1 = (data / 100) % 10; // 0
	int data2 = (data / 10) % 10; // 2
	int data3 = (data / 1) % 10; // 3

	while (time < max_time) {
		set_fnd1(0, data0); _delay_ms(2);
		set_fnd1(1, data1); _delay_ms(2);
		set_fnd1(2, data2); _delay_ms(2);
		set_fnd1(3, data3); _delay_ms(2);
		time++;
	}
}
