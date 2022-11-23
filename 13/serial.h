#include <avr/io.h>

void uart_write_char(char c) {
	while (!(UCSR0A & 0x20));
	UDR0 = c;
}

char uart_read_char(char write_back) {
	char c;
	while (!(UCSR0A & 0x80));
	c = UDR0;

	if (write_back) {
		uart_write_char(c);
		if (c == '\r') {
			uart_write_char('\n');
		}
	}
	return c;
}


void uart_write_string(char *str, int str_len) {
	int i;

	for (i = 0 ; i < str_len; i++) {
		uart_write_char(str[i]);
	}
}

void init_uart() {
	// Set USART Baud Rate Register as 9600bps
	// UBRR = 103
	UBRR0H = 0b00000000;
	UBRR0L = 0b01100111;

	// TXENn is 1
	UCSR0B = 0x18; // TX Enable

	// UCSRnC: - UMSELn UPMn1 UPMn0 USBSn UCSZn1 UCSZn0 UCPOLn
	// UCSZn1 and UCSZn0 are 1
	UCSR0C = 0x06; // UART, 8 bits data, no parity, 1 stop bit
}
