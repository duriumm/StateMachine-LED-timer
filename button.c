#include "button.h"
#include <avr/io.h>
#include "led.h"
#include "serial.h"
#include <avr/pgmspace.h>



#include "stateHandler.h"

void init_button(){
     
    DDRD &= ~(1 << PD2); // Set button as input 
}

void read_button_state_and_change_LED_state(int ledToUse, LED_STATES * currentLedState){
    /* Here we read the button and set a state depending on if the button is high(1) or low (0) */
    if (PIND & (1 << PD2)){
        *currentLedState = ON_STATE;
    }
        
    else if(!(PIND & (1 << PD2))){
        *currentLedState = OFF_STATE;
    }
}