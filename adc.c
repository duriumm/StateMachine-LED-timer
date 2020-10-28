#include "adc.h"
#include <avr/interrupt.h>

void init_single_conversion_mode_ADC()
{
    ADMUX = 0;                  // use #0 ADC pin to use 
    ADMUX |= (1 << REFS0);      // use AVcc as the reference
                                
    ADMUX |= (1 << ADLAR);      // Left adjusted bit data //
 

    ADCSRA |= (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);    // Set prescaler value to 8
    ADCSRA |= (1 << ADEN);      // Enable the ADC
    ADCSRA |= (1 << ADIE);      // Enable Interrupts 

    sei();                      // Enable GLOBAL interrupts
}