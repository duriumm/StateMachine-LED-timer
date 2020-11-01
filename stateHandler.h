#ifndef STATEHANDLER_H_
#define STATEHANDLER_H_


typedef enum{           // enum of all states for LED
  LED_PULSATING_STATE = 1,
  LED_POTMETER_CONTROLLED_STATE = 2,
  LED_BLINKING_STATE = 3,
  LED_OFF_STATE = 4
}LED_STATES;

typedef enum{           // enum for ON and OFF states for button
  BUTTON_ON_STATE = 1,
  BUTTON_OFF_STATE = 2
}BUTTON_STATES;

LED_STATES increment_led_state(LED_STATES currentLedState);

#endif