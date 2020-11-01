#include "led.h"
#include <avr/io.h>
#include "serial.h"
#include <avr/pgmspace.h>
#include "stateHandler.h"
#include <util/delay.h>
#include "timer.h"

int isIncrementingBoolean = 1;
static int returnValue = 0;
static int counterForBlinkMode = 0;

static int isPWMmodeDisabled = 0;

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

/* Function to switch LED on/off */
void switch_led(int indexInRegistry){   
    /* We switch the led on/off */
    PORTD ^= (1 << indexInRegistry);     
}

/* Initialize pwm on arduino pin 6 as output */
void init_pwm_6(){                          
    DDRD |= (1 << PD6);
}


void change_led_behaviour_based_on_LED_state(int ledToUse, LED_STATES currentLedState, volatile unsigned int * previousReadADCvalue){
    counterForBlinkMode++;                                      // Increment counterForBlinkMode since it starts at 0

    /* in this function we Change LED behaviour depending on currentLedState  */   

    if(currentLedState == LED_PULSATING_STATE){

        if(isPWMmodeDisabled == 1){                             // If isPWMmodeDisabled is 1(true)        
            enable_OCR0A(); // We start the pwm mode(enabling OCR0A)  
            isPWMmodeDisabled = 0;                              // Set isPWMmodeDisabled to 0 so we only enable OCR0A once
        }
        if(PORTD &= ~(1 << ledToUse)){                          // Check if Led is turned OFF 
            activate_led(ledToUse);                             // if turned off turn it ON                    
        }
        OCR0A = simple_led_ramp();                              // PULSATING LED
    }




    else if(currentLedState == LED_POTMETER_CONTROLLED_STATE){
        
        if(isPWMmodeDisabled == 1){
            enable_OCR0A();                                     // Enable OCR0A
            isPWMmodeDisabled = 0;
        }
        ADCSRA |= (1 << ADSC);                                  // Start the ADC conversion

        printf_P(PSTR("%d\n"),*previousReadADCvalue);

        /* Since the potentiometer fluctuates in value i decided to set the value for if statementcheck here to 1 
           which seemed to work just fine. Here we disable the OCR0A if value goes <= 1 and else we enable the OCR0A
           to correctly turn the light completely off instead of dimming it to the lowest setting. */
        if(*previousReadADCvalue <= 1){
            disable_OCR0A();
        }
        else{
            enable_OCR0A();
        }

        OCR0A = *previousReadADCvalue;                          // Set  OCR0A "led strength" to previousReadADCvalue which is potMeterValue
    }


    else if(currentLedState == LED_BLINKING_STATE){   

        if(isPWMmodeDisabled == 0){                             // We dont want the OCR0A enabled here so we check if it IS
            disable_OCR0A();                                    // enabled and then disable it to use lights correctly.
            isPWMmodeDisabled = 1;
        }   

        if(counterForBlinkMode >= 100){                         // 100 is 1 second. Interrupt(10ms) * 100 = 1000ms = 1 second   
            switch_led(ledToUse);                               // new test with PWM mode off to blink     
            counterForBlinkMode = 0;                            // Reset counter to 0
        }     
    }
    
    else if(currentLedState == LED_OFF_STATE){                  // Simple function to turn the LED off.

        if(isPWMmodeDisabled == 0){                             // Checking again is OCR0A is disabled. If its not, we disable it.
            disable_OCR0A();    
            isPWMmodeDisabled = 1;
        }
        deactivate_led(ledToUse);
    }

    else{
        printf_P(PSTR("something went really bad..."));         // This shouldnt happen but its a good fail check :D
    }
}

uint8_t simple_led_ramp(){
    /* In this function we return a single number each time out of the function. The next time we enter the variable returnValue
    will be the same and then increment or decrement depending on if our boolean value is 1 or 0. This is used for the pulse of
    our LED hence the TOP value of 255 and BOT value of 0. */

    if(isIncrementingBoolean == 1){
        returnValue++;
    }
    else if(isIncrementingBoolean == 0){
        returnValue--;
    }

    if(returnValue >= 255){ 
        isIncrementingBoolean = 0;
    }
    else if(returnValue <= 0){
        isIncrementingBoolean = 1;
    }

    return returnValue; 
}