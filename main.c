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


#define redLed PD6

LED_STATES currentLedState = OFF_STATE; // State of led set to OFF state at beginning.

int main (void) {

  
  uart_init();		// Initialize Uart
  init_led(redLed);	// Initialize LED
  init_button();	// Initialize button 

  while(1){

	read_button_state_and_change_LED_state(redLed, &currentLedState); // Read the button input and change current Led State based off reading.
	change_led_ON_or_OFF_based_on_LED_state(redLed, currentLedState); // Turn led ON or OFF based off current Led State.
	print_state_of_LED(currentLedState); 							  // Print "released/pushed" only once when pushing/releasing button.
    		
  }
  
  return 0;
}
