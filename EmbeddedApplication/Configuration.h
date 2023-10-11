#ifndef LEDSSTATESCHANGE_H
#define LEDSSTATESCHANGE_H

/* Serial Port Configurations*/
/* For more information please see https://www.arduino.cc/reference/en/language/functions/communication/serial/begin/ */
#define BAUDRATE 115200                    ///< This macro represents baudrate for serial communication.
#define SERIAL_PORT_CONFIGS SERIAL_8N1     ///< This macro represents serial port configuration for serial communication.

/* ESP32 Pin Configurations */
/* For more information, please see https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2018/08/ESP32-DOIT-DEVKIT-V1-Board-Pinout-36-GPIOs-updated.jpg?quality=100&strip=all&ssl=1 */
#define BUTTON_PIN_NUMBER 4                 ///< This macro represents button pin.
#define LED_1_PIN_NUMBER 22                 ///< This macro represents led 1 pin.
#define LED_2_PIN_NUMBER 23                 ///< This macro represents led 2 pin.

/* Message which is to be send Structure */
#define STARTS_CHARACTERS "$$"              ///< This macro represents start characters of message structure to be send.
#define SEPERATOR_CHARACTERS ","            ///< This macro represents seperator characters of message structure to be send.
#define END_CHARACTERS "**"                 ///< This macro represents end characters of message structure to be send.
#define PIN_HIGH_CHARACTERS "On"            ///< This macro represents pin high state of message structure to be send.
#define PIN_LOW_CHARACTERS "Off"            ///< This macro represents pin low state of message structure to be send.

/* Debounce Delay Time Configuration */
#define DEBOUNCE_DELAY_TIME_MS 250           ///< This macro represents delay time as millisecond to prevent button debounce. Also, represents system deadzone time.

/* System State Configurations */
#define FIRST_SYSTEM_STATE 3                 ///< This macro represents start system state.
#define END_SYSTEM_STATE 0                   ///< This macro represents end system state.
#define INITIAL_SYSTEM_STATE 3               ///< When the systems starts, this macro sets the system to its value state. And, this macro can get between FIRST_SYSTEM_STATE and END_SYSTEM_STATE values.
#define SYSTEM_CHANGE_EDGE_TRIGGERING RISING ///< For more information, please see https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/

/* Definitions */
#define LEN_ULONG_MAX_TO_STR 10              ///< This macro represents length of maximum unsigned long variable type as a string.

#endif
