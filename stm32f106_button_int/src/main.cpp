#include <Arduino.h>

#define LED_PIN1 PC13
#define BUTTON_PIN1 PA0

int buttonState1;

void setup()

{
  pinMode(LED_PIN1, OUTPUT);
  pinMode(BUTTON_PIN1, INPUT);

}

void loop()
{
  // pooling no debounce
  buttonState1 = digitalRead(BUTTON_PIN1);
  digitalWrite(LED_PIN1, buttonState1);
}
