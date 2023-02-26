#include <Arduino.h>

#define SERIAL_BAUDS 115200

#ifndef LED_BUILTIN
  #define LED_BUILTIN PC13
#endif

//unsigned int ledTimerLast = 0;
//int ledTimerTrigger = 500;

// door sensor switch
#define BUTTON_PIN1 PA0
int buttonState1;
int buttonLastState1;

// setup PWMServoDriver with I2C
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41); // select address
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire); // select address & chanell 

#define SERVOMIN  250 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  500 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(SERIAL_BAUDS);
  delay(2000);

  // door sensor button setup 
  pinMode(BUTTON_PIN1, INPUT);

 // initialize PCA9685
  Serial.println("initialize PCA9685");
  pwm.begin();
  //Serial.println("pwm.begin");
  pwm.setOscillatorFrequency(27000000);
  //Serial.println("pwm.setOscillatorFrequency");
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  //Serial.println("pwm.setPWMFreq");
  delay(10);
 
}


void loop()
{
  

  // door sensor reading pooling no debounce
  buttonState1 = digitalRead(BUTTON_PIN1);
  digitalWrite(LED_BUILTIN, buttonState1);

  Serial.print(buttonState1);
  if(buttonState1) {
    Serial.println(" max");
    //pwm.setPWM(servonum, 0, SERVOMAX);
    if(buttonState1 != buttonLastState1) {
    for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
      pwm.setPWM(servonum, 0, pulselen);
    }
    buttonLastState1 = buttonState1;
    }
    
  } else {
    Serial.println(" min");
    //pwm.setPWM(servonum, 0, SERVOMIN);
    if(buttonState1 != buttonLastState1) {
      for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        pwm.setPWM(servonum, 0, pulselen);
      }
      buttonLastState1 = buttonState1;
    }
  }
  
  /*
  if((millis() - ledTimerLast) > ledTimerTrigger {
    ledTimerLast = millis();
    digitalWrite(LED_PIN1, buttonState1);
  }
  */
}
