#include "Configuration.h"

unsigned long lastDebounceTime = 0;
unsigned long lastRunTime = 0;
unsigned long buttonPressCounter = 0;
unsigned long lastButtonPressCounter = 0;
uint8_t systemStateCounter = INITIAL_SYSTEM_STATE + 1;

char* startCharacters = STARTS_CHARACTERS;
char* seperatorCharacters = SEPERATOR_CHARACTERS;
char* endCharacters = END_CHARACTERS;

char* pinHighState = PIN_HIGH_CHARACTERS;
char* pinLowState = PIN_LOW_CHARACTERS;

static void buttonPressCallback();
static void changeSystemState();
static void printMessage(char* led1PinState, char* led2PinState);

static void buttonPressCallback() 
{
  unsigned long runTime = millis();

  if (lastRunTime > runTime)
  {
    lastDebounceTime = 0;
  }

  lastRunTime = runTime;

  if ((lastRunTime - lastDebounceTime) > DEBOUNCE_DELAY_TIME_MS) 
  {
      lastDebounceTime = lastRunTime;
      ++buttonPressCounter;
  }
}

static void changeSystemState()
{ 
  char* led1PinState = pinHighState;
  char* led2PinState = pinHighState;

  --systemStateCounter;

  switch(systemStateCounter)
  {
    case 3:
      led1PinState = pinHighState;
      led2PinState = pinHighState;
      break;
    case 2:
      led1PinState = pinHighState;
      led2PinState = pinLowState;
      break;
    case 1:
      led1PinState = pinLowState;
      led2PinState = pinHighState;
      break;
    case 0:
      led1PinState = pinLowState;
      led2PinState = pinLowState;
      break;
    default:
      led1PinState = pinHighState;
      led2PinState = pinHighState;
      break;
  }

  if (led1PinState == pinHighState)
  {
    digitalWrite(LED_1_PIN_NUMBER, HIGH);
  }
  else if (led1PinState == pinLowState)
  {
    digitalWrite(LED_1_PIN_NUMBER, LOW);
  }
  else
  {
    ;
  }

  if (led2PinState == pinHighState)
  {
    digitalWrite(LED_2_PIN_NUMBER, HIGH);
  }
  else if (led2PinState == pinLowState)
  {
    digitalWrite(LED_2_PIN_NUMBER, LOW);
  }
  else
  {
    ;
  }

  printMessage(led1PinState, led2PinState);

  if ((systemStateCounter <= END_SYSTEM_STATE) || (systemStateCounter > FIRST_SYSTEM_STATE))
  {
    systemStateCounter = FIRST_SYSTEM_STATE + 1;
  }
}

static void printMessage(char* led1PinState, char* led2PinState)
{
  char* serialMessage;

  char* systemStateStr = "";
  char* buttonPressStr = "";

  uint8_t lenAllocateMemoryForSerialMessage = 0 ;

  systemStateStr = (char *)calloc(LEN_ULONG_MAX_TO_STR + 1, sizeof(char));
  buttonPressStr = (char *)calloc(LEN_ULONG_MAX_TO_STR + 1, sizeof(char));

  itoa(systemStateCounter, systemStateStr, 10);
  itoa(buttonPressCounter, buttonPressStr, 10);

  lenAllocateMemoryForSerialMessage = strlen(startCharacters) + strlen(systemStateStr) + 
                                      strlen(seperatorCharacters) + strlen(led1PinState) + 
                                      strlen(seperatorCharacters) + strlen(led2PinState) + 
                                      strlen(seperatorCharacters) + strlen(buttonPressStr) + 
                                      strlen(endCharacters) + 1;

  serialMessage = (char *)calloc(lenAllocateMemoryForSerialMessage, sizeof(char));

  strcat(serialMessage,startCharacters);
  strcat(serialMessage,systemStateStr);
  strcat(serialMessage,seperatorCharacters);
  strcat(serialMessage,led1PinState);
  strcat(serialMessage,seperatorCharacters);
  strcat(serialMessage,led2PinState);
  strcat(serialMessage,seperatorCharacters);
  strcat(serialMessage,buttonPressStr);
  strcat(serialMessage,endCharacters);

  Serial.print(serialMessage);

  free(serialMessage);
  free(systemStateStr);
  free(buttonPressStr);
}

void setup() {
  Serial.begin(BAUDRATE, SERIAL_PORT_CONFIGS);

  pinMode(LED_1_PIN_NUMBER, OUTPUT);
  pinMode(LED_2_PIN_NUMBER, OUTPUT);
  pinMode(BUTTON_PIN_NUMBER, INPUT_PULLDOWN);

  changeSystemState();
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN_NUMBER), buttonPressCallback, SYSTEM_CHANGE_EDGE_TRIGGERING);
}

void loop()
{
  if (lastButtonPressCounter > buttonPressCounter)
  {
    lastButtonPressCounter = 0;
    buttonPressCounter = 1;
  }

  if (lastButtonPressCounter != buttonPressCounter)
  {
    lastButtonPressCounter = buttonPressCounter;
    changeSystemState();
    Serial.println("");
  }
}