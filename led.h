#ifndef LED_H_
#define LED_H_

#include "stateHandler.h"

void init_led(int indexInRegistry);

void activate_led(int indexInRegistry);

void deactivate_led(int ledToDeactivate);

void toggle_led(int ledToToggle);

void change_led_ON_or_OFF_based_on_LED_state(int ledToUse, LED_STATES currentLedState);


#endif