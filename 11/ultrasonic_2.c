#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define TRIG 6
#define ECHO 7

unsigned char digit[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7c, 0x07, 0x7f, 0x67};
unsigned char fnd_sel[4] = {0x01, 0x02, 0x04, 0x08};
unsigned char fnd[4];

void display_fnd(unsigned int value);

int main(void)
{
 unsigned int distance;
 DDRC = 0xff;
 DDRG = 0x0f;
 DDRE = ((DDRE|(1<<TRIG)) & ~(1<<ECHO));

 while(1)
 {
  TCCR1B = 0x02;
  PORTE &= ~(1<<TRIG);
  _delay_us(10);
  PORTE |= (1<<TRIG);
  _delay_us(10);
  PORTE &= ~(1<<TRIG);

  while(!(PINE & (1<<ECHO)));
  TCNT1 = 0x0000;
  while(PINE & (1<<ECHO)) ;

  TCCR1B = 0x00;
  distance = (unsigned int)(TCNT1 / 2 / 5.8);
  display_fnd(distance);
 }
}

void display_fnd(unsigned int value)
{
 int i;
 fnd[3] = (value/1000)%10;
 fnd[2] = (value/100)%10;
 fnd[1] = (value/10)%10;
 fnd[0] = (value/1)%10;
 for(i=0; i<4; i++)
 {
  PORTC = digit[fnd[i]] | (i==1 ? 0x80 : 0x00);
  PORTG = fnd_sel[i];
  _delay_ms(2);
  if(i%2)
   _delay_ms(1);
 }
}


