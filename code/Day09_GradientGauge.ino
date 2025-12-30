/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 09: GRADIENT GAUGE - Battery with RGB feedback ###
   ###   Smooth color gradients based on charge level       ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Pin Definitions & Constants                     ###
   ########################################################### */

#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9
#define PHOTORESISTOR_PIN A0

#define BATTERY_CAPACITY 50000UL

/* ###########################################################
   ###   2. Global Variables                                ###
   ########################################################### */

unsigned long battery_level = 0;
bool fullyChargedMessageShown = false;

/* ###########################################################
   ###   3. Setup Function                                  ###
   ########################################################### */

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Simulated Charging Initiated...");
}

/* ###########################################################
   ###   4. Helper Functions                                ###
   ########################################################### */

void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}

void flashRedAlert() {
  displayColor(0, 0, 0);      // OFF
  delay(100);
  displayColor(255, 0, 0);    // RED ON
  delay(200);
  displayColor(0, 0, 0);      // OFF
  delay(100);
}

/* ###########################################################
   ###   5. Main Loop                                       ###
   ########################################################### */

void loop() {
  int lightValue = analogRead(PHOTORESISTOR_PIN);
  battery_level += lightValue;

  // Cap at maximum
  if (battery_level > BATTERY_CAPACITY) {
    battery_level = BATTERY_CAPACITY;
  }

  float percentage = ((float)battery_level / (float)BATTERY_CAPACITY) * 100;
  displayColor(0, 0, 0);  // Reset LED

  int redValue = 0;
  int greenValue = 0;

  if (percentage < 100.0) {
    if (percentage <= 25.0) {
      // CRITICAL: Flashing red
      redValue = 255;
      greenValue = 0;
      flashRedAlert();
      Serial.print("Battery CRITICAL: ");
    }
    else if (percentage <= 70.0) {
      // AMBER: Red fades, green rises
      redValue = constrain(map(percentage, 26, 70, 255, 128), 0, 255);
      greenValue = constrain(map(percentage, 26, 70, 0, 128), 0, 255);
      displayColor(redValue, greenValue, 0);
      delay(250);
      Serial.print("Battery Amber: ");
    }
    else {
      // GREEN: Full gradient to green
      redValue = constrain(map(percentage, 71, 100, 128, 0), 0, 255);
      greenValue = constrain(map(percentage, 71, 100, 128, 255), 0, 255);
      displayColor(redValue, greenValue, 0);
      delay(250);
      Serial.print("Battery Green: ");
    }

    // Serial output
    Serial.print(percentage, 1);
    Serial.print("% | Red: ");
    Serial.print(redValue);
    Serial.print(" | Green: ");
    Serial.print(greenValue);
    Serial.print(" | Light: ");
    Serial.println(lightValue);

    fullyChargedMessageShown = false;
  }
  else {
    // FULLY CHARGED
    if (!fullyChargedMessageShown) {
      Serial.println("Battery Fully Charged! All systems GO!");
      fullyChargedMessageShown = true;
    }
    displayColor(0, 255, 0);  // Solid green
    delay(500);
  }
}

/* ###########################################################
   ###           END OF DAY 09 - GRADIENT GAUGE             ###
   ########################################################### */
