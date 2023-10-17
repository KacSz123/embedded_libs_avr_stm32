#include "adc.h"


void ADC_init()
{
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADMUX |= AVCC_EXTER | A0 | CONV_10B;
}

uint16_t ADC_takeMeasure(const uint8_t PIN)
{
	uint16_t ADC_10bit_Result = 0;
	ADMUX = (ADMUX & 0xF0)|(PIN & 0x0F);
	ADCSRA |= (1 << ADEN) | (1 << ADSC);
	
	while (!(ADCSRA & (1 << ADIF))); // Wait for conversion to finish

	ADC_10bit_Result = ADC; // Read the ADC value to 16 bit int

	ADCSRA |= (1 << ADIF);
	return ADC_10bit_Result;
}