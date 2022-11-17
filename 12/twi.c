#define ATS75_ADDR 0x98 // 0b10011000, 7비트를 1비트 left shift
#define ATS75_CONFIG_REG 1
#define ATS75_TEMP_REG 0

#define UCHAR unsigned char // UCHAR 정의
#define USHORT unsigned short // USHORT 정의
void init_twi_port();
void write_twi_1byte_nopreset(UCHAR reg, UCHAR data);
void write_twi_0byte_nopreset(UCHAR reg);
USHORT read_twi_2byte_preset();

void write_twi_1byte_nopreset(UCHAR reg, UCHAR data) {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // START 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || ((TWSR & 0xf8) != 0x08 &&
      (TWSR & 0xf8) != 0x10)); // ACK를 기다림
  TWDR = ATS75_ADDR | 0; // SLA+W 준비, W=0
  TWCR = (1 << TWINT) | (1 << TWEN); // SLA+W 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xf8) != 0x18);
  TWDR = reg; // aTS75 Reg 값 준비
  TWCR = (1 << TWINT) | (1 << TWEN); // aTS75 Reg 값 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xF8) != 0x28);
  TWDR = data; // DATA 준비
  TWCR = (1 << TWINT) | (1 << TWEN); // DATA 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xF8) != 0x28);
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // STOP 전송
}

void write_twi_0byte_nopreset(UCHAR reg) {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // START 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || ((TWSR & 0xf8) != 0x08 &&
      (TWSR & 0xf8) != 0x10)); // ACK를 기다림
  TWDR = ATS75_ADDR | 0; // SLA+W 준비, W=0
  TWCR = (1 << TWINT) | (1 << TWEN); // SLA+W 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xf8) != 0x18);
  TWDR = reg; // aTS75 Reg 값 준비
  TWCR = (1 << TWINT) | (1 << TWEN); // aTS75 Reg 값 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xF8) != 0x28);
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // STOP 전송
}

USHORT read_twi_2byte_preset() {
  UCHAR high_byte, low_byte;
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // START 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || ((TWSR & 0xf8) != 0x08 &&
      (TWSR & 0xf8) != 0x10)); // ACK를 기다림
  TWDR = ATS75_ADDR | 1; // SLA+R 준비, R=1
  TWCR = (1 << TWINT) | (1 << TWEN); // SLA+R 전송
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xf8) != 0x40);
  TWCR = (1 << TWINT) | (1 << TWEN | 1 << TWEA); // 1st DATA 준비
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xf8) != 0x50);
  high_byte = TWDR; // 1 byte DATA 수신
  TWCR = (1 << TWINT) | (1 << TWEN | 1 << TWEA); // 2nd DATA 준비
  while (((TWCR & (1 << TWINT)) == 0x00) || (TWSR & 0xf8) != 0x50);
  low_byte = TWDR; // 1 byte DATA 수신
  return ((high_byte << 8) | low_byte); // 수신 DATA 리턴
}