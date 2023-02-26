#include <Arduino.h>

int ledPin = PC13;
int buttonPin = PA0;
int ledToggle;
int previousState = HIGH;
unsigned int previousPress = 0;
volatile int buttonFlag;
int buttonDebounce = 20;


void button_ISR()
{
  buttonFlag = 1;
}


void setup()

{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), button_ISR, CHANGE);
}



void loop()
{
  if((millis() - previousPress) > buttonDebounce && buttonFlag)
  {
    previousPress = millis();
    if(digitalRead(buttonPin) == LOW && previousState == HIGH)
    {
      ledToggle =! ledToggle;
      digitalWrite(ledPin, ledToggle);
      previousState = LOW;
    } else if (digitalRead(buttonPin) == HIGH && previousState == LOW)
    {
      previousState = HIGH;
    }
    buttonFlag = 0;
  }
}
