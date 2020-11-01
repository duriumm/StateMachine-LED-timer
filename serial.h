#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdio.h>
#include "stateHandler.h"

#define BAUDRATE 38400
#define UBRR (F_CPU/16/BAUDRATE-1)

void uart_init(void);

int uart_putchar(char chr, FILE *stream);

char uart_getchar(void);

//void uart_putstr(const char *str); // FUNKAR EJ måste ha någon file grej i

void uart_echo(void);

void uart_get_string_from_user(unsigned char * stringToCheck);

void print_state_of_LED(LED_STATES currentLedState);

#endif

