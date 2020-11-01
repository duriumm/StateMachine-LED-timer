#include "stateHandler.h"

void init_button();

LED_STATES read_button_state_and_change_LED_state(int ledToUse, LED_STATES currentLedState);

int check_if_button_was_pressed();

BUTTON_STATES return_button_state(BUTTON_STATES currentButtonState);