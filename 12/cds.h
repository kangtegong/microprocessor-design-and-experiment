void init_adc()
{
	ADMUX = 0x00;
	// REFS(1:0) = "00" AREF(+5V) 기준전압 사용
	// ADLAR = 디폴트 오른쪽 정렬
	// MUX(4:0) = "00000" ADC0 사용, 단극 입력
	ADCSRA = 0x87;
	// ADEN = ADC를 Enable
	// ADFR = single conversion 모드
	// ADPS(2:0) = "111" 프리스케일러 128분주
}

unsigned short read_adc() {
	unsigned char adc_low, adc_high;
	unsigned short value;
	ADCSRA |= 0x40; // ADC start conversion
	while ((ADCSRA & 0x10) != 0x10); // ADC 변환 완료 검사
	adc_low = ADCL; // 변환된 Low 값 읽어오기
	adc_high = ADCH; // 변환된 High 값 읽어오기
	value = (adc_high << 8) | adc_low; // value 는 High 및 Low 연결 16비트값
	return value;
}
