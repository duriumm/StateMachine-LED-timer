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
LED_STATES currentLedState = LED_PULSATING_STATE;    // State of led set to LED_PULSATING_STATE state at beginning.
BUTTON_STATES currentButtonState = BUTTON_OFF_STATE; // State of led set to OFF state at beginning.

volatile unsigned int isInterrupted = 0;             // volatile "bool" so we can change it inside our timer2 interrupt ISR

int main (void) {
	
  uart_init();		          // Initialize Uart
  init_led(redLed);	        // Initialize LED
  init_button();	          // Initialize button 

  complete_timer_init();    // Initialize Timer for timer0 with fast pwm mode and Timer2 with ctc mode

  init_single_conversion_mode_ADC(); // Initialize single conversion mode for ADC

  while(1){

    if(isInterrupted == 1){          // Check if isInterrupted == 1 (To make things happen outside interrupt instead of inside)
      change_led_behaviour_based_on_LED_state(redLed, currentLedState, &previousReadADCvalue);// We change the LED behaviour to 
                                                                                              // pulse/potMeter/blink/off depending on State                                                                                            
      isInterrupted = 0;    // Set isInterrupted to 0                                                           
    }   
  }
  return 0;
}

/* Once this timer function is done we head over to the ADC_vect below */
ISR(TIMER2_COMPA_vect){

  currentLedState = change_led_state_after_button_press(redLed, currentLedState); // After a registered button press is made we increment
  
  isInterrupted = 1;    // set isInterrupted to 1 so in main loop we can start executing our code based on it 
                                                                               
}

/* This function triggers after an ADC conversion is completed 
  (conversion happens inside change_led_behaviour_based_on_LED_state() function while LED_POTMETER_CONTROLLED_STATE is enabled) */
ISR(ADC_vect){
  previousReadADCvalue = ADCH;     // previousReadADCvalue is set to reading of ADCH(ADC Conversion Result)
}


