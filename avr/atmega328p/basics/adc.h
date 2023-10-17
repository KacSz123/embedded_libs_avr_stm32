#ifndef __ADC_H__
#define __ADC_H__
#define F_CPU 16000000UL // Defining the CPU Frequency

#include <avr/io.h>		// Contains all the I/O Register Macros
#include <util/delay.h> 
///////////////////////////////////////////////////////////////
// ADC macros
///////////////////////////////////////////////////////////////

// vol ref
#define V_REF_OFF (0 << REFS0) | (0 << REFS1)
#define AVCC_EXTER (1 << REFS0) | (0 << REFS1)
#define INTERNAL_1V1 (1 << REFS0) | (1 << REFS1)

// Channel selection
#define A0 (0<<MUX0)
#define A1 (1<<MUX0)
#define A2 (2<<MUX0)
#define A3 (3<<MUX0)
#define A4 (4<<MUX0)

// Nbit conv
#define CONV_10B (0 << ADLAR)
#define CONV_8B (1 << ADLAR)
void ADC_init();
uint16_t ADC_takeMeasure(const uint8_t PIN);
#endif //__ADC_H__