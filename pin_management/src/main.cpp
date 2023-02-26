#include <Wire.h>
#include <Keypad.h>
#include <Arduino.h>
#include <LiquidCrystal_PCF8574.h>

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
// Display Configuration
*/

LiquidCrystal_PCF8574 lcd(0x27);

/*
// Other
*/

const int LED_PIN = 13;
const int DOOR_SWITCH_PIN = 12;

int PIN_CODE = 0;

/*
// Main
*/

void setup() {
  // Start serial port and wait for a connection.
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Status: Serial connected");

  // Setup display
  Wire.begin();
  Wire.beginTransmission(0x27);
  Wire.endTransmission();
  lcd.begin(16, 2);

  // Others
  pinMode(LED_PIN, OUTPUT);
  pinMode(DOOR_SWITCH_PIN, INPUT_PULLUP);

  Serial.println("Status: Setup complete");
}  // setup()


// State machine with 5 main states: V_IDLE, V_AUTH, V_ALARM,
// V_OPENED, V_CONFIG

// V_IDLE: Waiting for a card to be scanned
// V_AUTH: Waiting for a valid PIN to be entered
// V_ALARM: Activate the buzzer and the LED while asking for a PIN
// V_OPENED: Open the door and wait for the switch to be closed
// V_CONFIG: Configure the system

enum State { V_IDLE, V_AUTH, V_ALARM, V_OPENED, V_CONFIG };
int auth_destination = 0; // 0: OPENED, 1: CONFIG
State state = V_IDLE;

void loop() {
  switch (state) {
    case V_IDLE:
      // Wait for a card to be scanned. If a valid card is
      // scanned, go to V_AUTH state and set the auth_destination
      // to 0 (V_OPENED) or 1 (V_CONFIG) depending on the card.

      // Listen for possible movments detected by the accelerometer.
      // If a movement is detected, go to V_ALARM state.

      // Listen if the switch is high (door open). If that appens,
      // go to V_ALARM state.

      // Note 1: the scanning module is not yet implemented
      // so, for now, we will simulate a card scan by reading
      // the serial port: opn (auth destination 0) or cfg
      // (auth destination 1)

      // Note 2: the accelerometer is not yet implemented
      // so, for now, we will simulate a movement by reading
      // the serial port: mov

      lcd.clear();
      lcd.setBacklight(0);

      while (1)
      {
        if (Serial.available() > 0)
        {
          String input = Serial.readStringUntil('\n');
          if (input == "opn")
          {
            auth_destination = 0;
            state = V_AUTH;
            break;
          }
          else if (input == "cfg")
          {
            auth_destination = 1;
            state = V_AUTH;
            break;
          }
          else if (input == "mov")
          {
            state = V_ALARM;
            break;
          }
        }
        if (digitalRead(DOOR_SWITCH_PIN) == LOW)
        {
          state = V_ALARM;
          break;
        }
      }
      break;
    case V_AUTH:
      // Wait for a valid PIN to be entered
      // If a valid PIN is entered, go to V_OPENED state
      // If an invalid PIN is entered, go to V_ALARM state

      lcd.clear();
      lcd.setBacklight(255);
      lcd.setCursor(0, 0);
      lcd.print("   ENTER PIN:   ");
      lcd.print("     ------     ");

      while (1)
      {
        char key = keypad.getKey();
        if (key != NO_KEY)
        {
          // Handle key press
        }
        delay(1);
      }

      break;
    case V_ALARM:
      // Activate the buzzer and the LED while asking for a PIN
      // If a valid PIN is entered, go to V_IDLE state
      // If an invalid PIN is entered, go to V_ALARM state

      lcd.clear();
      lcd.setBacklight(255);
      lcd.setCursor(0, 0);
      lcd.print("ALARM");
      digitalWrite(LED_PIN, HIGH);

      while (1)
      {
        // TODO: buzzer and keypad code here
        delay(1);
      }

      break;
    case V_OPENED:
      // Open the door and wait for the switch to be closed
      // If the switch is closed, go to V_IDLE state
      break;
    case V_CONFIG:
      // Configure the system
      // If the switch is closed, go to V_IDLE state

      lcd.clear();
      lcd.setBacklight(255);
      lcd.setCursor(0, 0);
      lcd.print("CONFIG");

      while (1)
      {
        // TODO: configs to do here
        delay(1);
      }

      break;
  }  // switch (state)  
}  // loop()