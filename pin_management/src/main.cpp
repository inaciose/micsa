#include <Wire.h>
#include <Keypad.h>
#include <Arduino.h>

/*
// Keypad Configuration
*/

const int ROW_NUM = 4; const int COLUMN_NUM = 3;

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte   pin_rows[ROW_NUM] = {9, 8, 7, 6};
byte pin_column[COLUMN_NUM] = {5, 4, 3};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

/*
// Other
*/

const int LED_PIN = 13;

/*
// Main
*/

void setup() {
  // Start serial port and wait for a connection.
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Status: Serial connected");

  // Others
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Status: Setup complete");
}  // setup()


void loop() {
  char key = keypad.getKey();

  if (key){
    Serial.println(key);
    digitalWrite(LED_PIN, HIGH);
    delay(5);
    digitalWrite(LED_PIN, LOW);
  }
}  // loop()