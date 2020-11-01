#include "button.h"
#include <avr/io.h>
#include "led.h"
#include "serial.h"
#include <avr/pgmspace.h>


#include "stateHandler.h"

int hasButtonBeenPressed = 0;


void init_button(){     
    DDRD &= ~(1 << PD2); // Set button as input 
}


int check_if_button_was_pressed(){
    /* Here we check if the button was pressed DOWN and then 
       if it was RELEASED in the same sequence. If it was succesfull
       we return 1(true) else we return 0(false) */
    if (PIND & (1 << PD2)){
        hasButtonBeenPressed = 1;
    }
    if(!(PIND & (1 << PD2)) && hasButtonBeenPressed == 1){
        hasButtonBeenPressed = 0;
        return 1;
    }
    else{
        return 0;
    }
}

LED_STATES change_led_state_after_button_press(int ledToUse, LED_STATES currentLedState){   
    /* If we get a correct button press (== 1) in return then we set currentLedState to whatever the increment_led_state() 
       function returns which is 1-4 different states. We then return the state to wherever we called the function from */
    
    if(check_if_button_was_pressed() == 1){
        currentLedState = increment_led_state(currentLedState); 
        printf_P(PSTR("Current Led state: %d\n"),currentLedState); // print out current led state.
    }
    return currentLedState;
}

BUTTON_STATES return_button_state(BUTTON_STATES currentButtonState){
    /* Just a simple function to check our current button state if it is pressed down or let go and then return the state it is in */
    if (PIND & (1 << PD2)){
        currentButtonState = BUTTON_ON_STATE;
    }
        
    else if(!(PIND & (1 << PD2))){
        currentButtonState = BUTTON_OFF_STATE;
    }
    return currentButtonState;
}