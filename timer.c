#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"


/* Static variables to keep them even when exiting the scope of function */
static uint8_t returnValue = 0;                
static uint8_t isIncrementingBoolean = 1;

void disable_OCR0A(){
    /* OCR0A disconnected */
    TCCR0A &= ~(1 << COM0A1);
}

void enable_OCR0A(){
    /* OCR0A connected  */
    TCCR0A |= (1 << COM0A1); 
}

void complete_timer_init(){

    /* Initialize fast pwm mode */
    TCCR0A |= (1 << WGM01) | (1 << WGM00);  

    /* Non inverting mode */
    TCCR0A |= (1 << COM0A1); 

    /* Init prescaler 64 for timer0 fast pwm mode */
    TCCR0B |= (1 << CS01) | (1 << CS00); 

    /* Set ctc mode for timer2 */
    TCCR2A |= (1 << WGM21); 
   
    /* Set prescaler to 1024 for timer2 */
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); 

    /* (16000000 /        1024      *          (0,010))          - 1 = 155
    (clock_speed / Prescaler_value  * (Desired_time_in_Seconds)) - 1 = 155 */  
    OCR2A = 155; 

    /* ENABLE Interrupt for ISR. */
    TIMSK2 = (1 << OCIE2A);

    /* Initialize counter for timer2 */
    TCNT2 = 0;

    /* enable GLOBAL interrupt */
    sei();
}


uint8_t simple_ramp(){
    /* isIncrementingBoolean and returnValue is static uint8_t variables declared at the top of timer.calculation 
       If isIncrementingBoolean == 1 we increment, else if isIncrementingBoolean == 0 we decrement*/
    if(isIncrementingBoolean == 1){
        returnValue++;
    }
    else if(isIncrementingBoolean == 0){
        returnValue--;
    }

    /* Here we check if max value is reached or if bottom value is reached. And then change isIncrementingBoolean based on it */
    if(returnValue >= 255){ 
        isIncrementingBoolean = 0;
    }
    else if(returnValue <= 0){
        isIncrementingBoolean = 1;
    }

    return returnValue; 
}