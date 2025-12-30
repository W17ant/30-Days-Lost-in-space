/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 14: KEYPAD - Security PIN entry system         ###
   ###   Learn matrix keypad scanning and password logic    ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

#include <Keypad.h>

/* ###########################################################
   ###   1. Keypad Configuration                            ###
   ########################################################### */

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

/* ###########################################################
   ###   2. Security Settings                               ###
   ########################################################### */

const String SECRET_CODE = "1234";
String enteredCode = "";

/* ###########################################################
   ###   3. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);
  Serial.println("=== SECURITY PANEL ===");
  Serial.println("Enter 4-digit code:");
}

/* ###########################################################
   ###   4. Main Loop                                       ###
   ########################################################### */

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("*");
    enteredCode += key;

    if (enteredCode.length() == 4) {
      Serial.println();

      if (enteredCode == SECRET_CODE) {
        Serial.println("ACCESS GRANTED!");
        // Trigger success action here
      } else {
        Serial.println("ACCESS DENIED!");
        // Trigger failure action here
      }

      enteredCode = "";
      delay(1000);
      Serial.println("Enter 4-digit code:");
    }
  }
}

/* ###########################################################
   ###           END OF DAY 14 - KEYPAD                     ###
   ########################################################### */
