#define F_CPU    16000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
 
#define aTS75_CONFIG_REG        1
#define aTS75_TEMP_REG        0
 
void I2C_Init(void) {
    TWBR = 12;                            // 16000000 / (16 + (2x12)) x prescaler = 400000Hz = 400kHz
    TWSR = (0<<TWPS1) | (0<<TWPS0);        // prescaler = 1
    TWCR = 0x04;
}

void I2C_start(void) {
    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}
 
void I2C_write(unsigned char data) {
    TWDR = data;
    TWCR = (1<<TWINT) | (1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
}
 
unsigned char I2C_read(unsigned char ackVal) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (ackVal<<TWEA);
    while(!(TWCR & (1<<TWINT)));
    return TWDR;
}
 
void I2c_stop(void) {
    TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
    for(int k=0; k<100; k++);                    //wait
}

/*
 * Pointer set followed by immediate write to the Configuration Register 데이터시트 참조 
 */
void temp_init(void) {
    I2C_Init();
    I2C_start();
    I2C_write(0b10011000);
    I2C_write(aTS75_CONFIG_REG);        // Configuration Register P1 = 0, P0 = 1
    I2C_write(0x00);
    I2c_stop();
}
 
 
/*
 * Pointer set followed by immediate read from a 2-byte register 데이터시트 참조
 */
int temp_read(void) {
    char high_byte, low_byte;
    I2C_start();
    I2C_write(0b10011000);
    I2C_write(aTS75_TEMP_REG);            // Temperature Register P1, P0 = 0 
    
    I2C_start();
    I2C_write(0b10011000 | 1);            // Address + write (not read)
    high_byte = I2C_read(1);            
    low_byte = I2C_read(0);
    I2c_stop();
    
    return ((high_byte<<8) | low_byte);
}
 
void display_FND(int value)
{
    char digit[12] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67, 0x40, 0x00};
    char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};
    char value_int, value_deci, num[4];
    int i;
    if((value & 0x8000) != 0x8000)        // Sign 비트 체크
    num[3] = 11;
    else
    {    num[3] = 10;
        value = (~value)-1;            // 2's Compliment
    }
    value_int = (char)((value & 0x7f00) >> 8);
    value_deci = (char)(value & 0x00ff);
    num[2] = (value_int / 10) % 10;
    num[1] = value_int % 10;
    num[0] = ((value_deci & 0x80) == 0x80) * 5;
    for(i=0; i<4; i++)
    {
        PORTC = digit[num[i]];
        PORTG = fnd_sel[i];
        if(i==1)
        PORTC |= 0x80;
        _delay_ms(2);
    }
}
 
int main(void)
{
    int temperature = 0;
    DDRC = 0xff; DDRG = 0xff;
    PORTD = 3;
    temp_init();
    _delay_ms(100);
    while (1) 
    {
        temperature = temp_read();
    //     char value_int = (char)((temperature & 0x7f00) >> 8);
        _delay_ms(10);
        display_FND(temperature);
    }
}