#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/delay.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "button.h"
#include "stateHandler.h"
#include "adc.h"


#define redLed PD6
volatile unsigned int previousReadADCvalue = 0;
LED_STATES currentLedState = OFF_STATE; // State of led set to OFF state at beginning.


int main (void) {
	
  uart_init();		          // Initialize Uart
  init_led(redLed);	        // Initialize LED
  init_button();	          // Initialize button 

  complete_timer_init();    // Initialize Timer for timer0 with fast pwm mode and Timer2 with ctc mode

  init_single_conversion_mode_ADC(); // Initialize single conversion mode for ADC

  while(1){
	
  }
  return 0;
}

/* Once this timer function is done we head over to the ADC_vect below */
ISR(TIMER2_COMPA_vect){
  ADCSRA |= (1 << ADSC);           // Start the ADC conversion
  OCR0A = previousReadADCvalue;    // Set  OCR0A "led strength" to previousReadADCvalue
}
/* This function triggers after an ADC conversion is completed */
ISR(ADC_vect){
  previousReadADCvalue = ADCH;     // previousReadADCvalue is set to reading of ADCH(ADC Conversion Result)
  printf_P(PSTR("%d\n"),previousReadADCvalue); // value fluctuates with +30 sometimes. Bad Pot meter.
}


