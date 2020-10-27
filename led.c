#include "led.h"
#include <avr/io.h>
#include "serial.h"
#include <avr/pgmspace.h>

/* Init led as "output" */
void init_led(int indexInRegistry){         
    /*  Set a 1 to index PB1(second index) in the DDRB registry and thereby configuring the pin as output */
    DDRD |= (1 << indexInRegistry);
}

/* Function to activate LED */
void activate_led(int indexInRegistry){ 
    /*  We set the second bit(PB1) in PORTB registry to 1 if the second bit(PB1) ALREADY is 1 or 0 */
    PORTD |= (1 << indexInRegistry);   
}

/* Function to deactivate LED */
void deactivate_led(int indexInRegistry){   
    /* We set the second bit (PB1) in PORTB registry to ~1(inverted 1 that becomes 0) IF the second bit(PB1) ALREADY is 1 */
    PORTD &= ~(1 << indexInRegistry);   
}

/* Initialize pwm on arduino pin 6 as output */
void init_pwm_6(){                          
    DDRD |= (1 << PD6);
}


void change_led_ON_or_OFF_based_on_LED_state(int ledToUse, LED_STATES currentLedState){ 
    /* Activate the led or Deactivate led depending on the Led_State */                                                               
    if(currentLedState == ON_STATE){
        activate_led(ledToUse);
    }
    else if(currentLedState == OFF_STATE){
        deactivate_led(ledToUse);
    }
    else{
        printf_P(PSTR("something went really bad...")); // This shouldnt happen :D
    }
}
