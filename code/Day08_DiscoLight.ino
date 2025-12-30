/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 08: DISCO LIGHT - RGB LED color cycling        ###
   ###   Rapid color changes with analogWrite() PWM         ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Pin Definitions                                 ###
   ########################################################### */

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

/* ###########################################################
   ###   2. Setup Function                                  ###
   ########################################################### */

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

/* ###########################################################
   ###   3. Helper Functions                                ###
   ########################################################### */

void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}

/* ###########################################################
   ###   4. Main Loop                                       ###
   ########################################################### */

void loop() {
  // DISCO PARTY: Rapid color cycling
  displayColor(255, 0, 0);      // RED
  delay(100);
  displayColor(0, 255, 0);      // GREEN
  delay(100);
  displayColor(0, 0, 255);      // BLUE
  delay(100);
  displayColor(255, 255, 0);    // YELLOW
  delay(100);
  displayColor(0, 255, 255);    // CYAN
  delay(100);
  displayColor(255, 0, 255);    // MAGENTA
  delay(100);
  displayColor(255, 255, 255);  // WHITE
  delay(100);
  displayColor(0, 0, 0);        // OFF
  delay(100);
}

/* ###########################################################
   ###           END OF DAY 08 - DISCO LIGHT                ###
   ########################################################### */
