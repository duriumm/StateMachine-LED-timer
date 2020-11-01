#include "stateHandler.h"

LED_STATES increment_led_state(LED_STATES currentLedState){
    /* Here we simply loop through the 4 states and reset when we reach the top */
    
    if(currentLedState == LED_OFF_STATE){
        currentLedState = LED_PULSATING_STATE;
    }
    else{
        currentLedState += 1;
    }   
    return currentLedState;
}