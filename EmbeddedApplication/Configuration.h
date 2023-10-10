#ifndef LEDSSTATESCHANGE_H
#define LEDSSTATESCHANGE_H

/* Serial Port Configurations*/
#define BAUDRATE 115200
#define SERIAL_PORT_CONFIGS SERIAL_8N1

/* ESP32 Pin Configurations */
#define BUTTON_PIN_NUMBER 4
#define LED_1_PIN_NUMBER 22
#define LED_2_PIN_NUMBER 23

/* Message which is to be send Structure */
#define STARTS_CHARACTERS "$$"
#define SEPERATOR_CHARACTERS ","
#define END_CHARACTERS "**"
#define PIN_HIGH_CHARACTERS "On"
#define PIN_LOW_CHARACTERS "Off"

/* Debounce Delay Time Configuration */
#define DEBOUNCE_DELAY_TIME_MS 250

/* System State Configurations */
#define FIRST_SYSTEM_STATE 3
#define END_SYSTEM_STATE 0
#define INITIAL_SYSTEM_STATE 3
#define SYSTEM_CHANGE_EDGE_TRIGGERING RISING

/* Definitions */
#define LEN_ULONG_MAX_TO_STR 10

#endif
