#include <avr/io.h>
#include "timer.h"

/* Static variables to keep them even when exiting the scope of function */
static uint8_t returnValue = 0;                
static uint8_t isIncrementingBoolean = 1;

void timer0_init(){

  /*TCCR0A is the Timer/Counter Control Register A which we use to initialize CTC mode
  TCCR0A uses (WGM01 = bit 1) and (WGM00 = bit 0)
  For TCCR0A we have (MAX = 0xFF) and (BOTTOM = 0x00)
  To init CTC mode for TCCR0A we put (WGM01 = 1)*/
  TCCR0A |= (1 << WGM01);
   
  /* Generate an interrupt each time the counter (TCNT0) reaches 155 
  Output Compare Value calculation is: (16 000 000 / (1024 x 100)) – 1 = 155,25 Which is rounded to 155.*/
  OCR0A = 155; 

  /* ENABLE Interrupt for ISR. for this deluppgift we will NOT use ISR*/
  //TIMSK0 = (1 << OCIE0A);
  
  /* initialize the counter */
  TCNT0 = 0;

  /*TCCR0B is the Timer/Counter Control Register B which we use to initialize prescaler. DETTA BORDE GÖRAS SIST TCCR0B
  TCCR0B uses (CS02 = bit 2) and (CS01 = bit 1) and (CS00= bit 0)
  To init prescaler 1024 for TCCR0B we put (CS02 = 1) and (CS00 = 1)*/   
  TCCR0B |= (1 << CS02) | (1 << CS00);
}

void pwm_timer0_init(){

    /* Initialize fast pwm mode */
    TCCR0A |= (1 << WGM01) | (1 << WGM00); 

    /* Non inverting mode */
    TCCR0A |= (1 << COM0A1); 

    /* Init prescaler 64 */
    TCCR0B |= (1 << CS01) | (1 << CS00); 

    // 16 000 000 / (64 * 256) = 976.5625 ~ 977. PWM frequency is 977.
}

void ctc_timer2_init(){

    /* Set ctc mode for timer2 */
    TCCR2A |= (1 << WGM21);  

    /* (16000000 /        1024      *          (0,016))          - 1 = 249
    (clock_speed / Prescaler_value  * (Desired_time_in_Seconds)) - 1 = 249 */
    OCR2A = 249; 

    /* initialize the counter */
    TCNT2 = 0;     

    /* Set prescaler to 1024 */
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); 

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