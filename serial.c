#include <avr/io.h>

#include <stdio.h>

#include "serial.h"
#include "stateHandler.h"
#include <avr/pgmspace.h>

static FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

static int has_ON_state_Printed = 0; // static ints to save value
static int has_OFF_state_Printed = 0;

void uart_init(void) {
	UBRR0H = (unsigned char)(UBRR >> 8);
	UBRR0L = (unsigned char)(UBRR);
	UCSR0A = 0;
	UCSR0B = (1 << TXEN0 | 1 << RXEN0);
	UCSR0C = (1 << UCSZ01 | 1 << UCSZ00);

	stdout = &uart_stdout;
}

int uart_putchar(char chr, FILE *stream) {
	if (chr == '\n') {
		uart_putchar('\r', NULL);
	}
	while (!(UCSR0A & (1 << UDRE0)))
		;
	UDR0 = chr;
	return 0;
}

char uart_getchar(void) {
	while (!(UCSR0A & (1 << RXC0)))
		;
	return UDR0;
}

void print_state_of_LED(LED_STATES currentLedState){
    /* Here we print pushed or released ONCE depending on if we pressed the button or relased it*/
    if(currentLedState == ON_STATE && has_ON_state_Printed == 0){
        printf_P(PSTR("pushed\r\n"));
        has_ON_state_Printed = 1;
        has_OFF_state_Printed = 0;
    }
    else if(currentLedState == OFF_STATE && has_OFF_state_Printed == 0){
        printf_P(PSTR("released\r\n"));
        has_OFF_state_Printed = 1;
        has_ON_state_Printed = 0;
    }
}

/*
void uart_putstr(const char *str){          // Takes a "string" and loops through it untill char is 0
                                            // for every char in the loop it sends it out with uart_putchar() and then increments char in string
    int i = 0;
    while (str[i] != 0)                     // While the string is not null??            
    {
        uart_putchar(str[i]);               // Print out every char of the string
        i++;                                   
    }
}
*/

void uart_get_string_from_user(unsigned char * stringInMain){ // Gets input from user with uart_getchar() 
                                                              // until read character is \n, then null terminates
                                                              // the string and saves it to stringInMain.

    char character = 'a';

    int i = 0;
    while(character != '\n'){
        character = uart_getchar();
        stringInMain[i] = character;
        i++;
    }
    stringInMain[i] = '\0'; // Null terminate string
}

/*void uart_check_if_string_is_ON_or_OFF(unsigned char * stringToCheck, STATES *currentEnumState){ // Checks string saved in main.c and then changes
                                                                                                 // enum state based on what the string contains.
                                                                                                 // Then sets the string to "".

    if (strcmp(stringToCheck, "ON\r\n") == 0 && *currentEnumState != ON_STATE){ 
        strcpy(stringToCheck, "");             // Empty the string for next use //
        *currentEnumState = ON_STATE;
        uart_putstr("Led is on!\n");
    }
    else if(strcmp(stringToCheck, "OFF\r\n") == 0 && *currentEnumState != OFF_STATE){ 
        strcpy(stringToCheck, "");
        *currentEnumState = OFF_STATE;
        uart_putstr("Led is off!\n");
    }
    else{
        uart_putstr("Invalid input try the following commands below.\n"
        "1. Enter ON when the led is OFF \n2. Enter OFF when the led is ON\n");
        strcpy(stringToCheck, "");            
    }
}
*/

/*
void uart_print_currentEnumState(STATES currentEnumState){  // Prints current enum state as string based on current enum state :)
   
    if(currentEnumState == ON_STATE){
        uart_putstr("LIGHT STATE ON\n");
    }
    else if(currentEnumState == OFF_STATE){
        uart_putstr("LIGHT STATE OFF\n");
    }
    else{
        uart_putstr("Light state is not 1 or 2... it must be fucked up!!!");
    }
}
*/
