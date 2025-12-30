/*
 * Day 24: Autopilot online
 * Mission: Automated control system
 *
 * Key Concepts:
 * - Feedback loops
 * - Sensor-based automation
 * - Target tracking
 *
 * Components: OLED display, photoresistor, LEDs, potentiometer
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int SENSOR_PIN = A0;
const int SETPOINT_PIN = A1;
const int OUTPUT_PIN = 9;

int sensorValue = 0;
int setpointValue = 0;
int outputValue = 0;
int error = 0;

// Simple P controller
const float Kp = 0.5;

bool autopilotEnabled = true;

void setup() {
  Serial.begin(9600);

  pinMode(OUTPUT_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("AUTOPILOT SYSTEM"));
  display.println(F("Initializing..."));
  display.display();

  delay(1500);
}

void drawBar(int x, int y, int width, int height, int value, int maxVal) {
  display.drawRect(x, y, width, height, SSD1306_WHITE);
  int fillWidth = map(constrain(value, 0, maxVal), 0, maxVal, 0, width - 2);
  display.fillRect(x + 1, y + 1, fillWidth, height - 2, SSD1306_WHITE);
}

void loop() {
  // Read inputs
  sensorValue = map(analogRead(SENSOR_PIN), 0, 1023, 0, 255);
  setpointValue = map(analogRead(SETPOINT_PIN), 0, 1023, 0, 255);

  // Calculate error and output
  error = setpointValue - sensorValue;

  if (autopilotEnabled) {
    outputValue = constrain(Kp * error + 127, 0, 255);
    analogWrite(OUTPUT_PIN, outputValue);
  }

  // Update display
  display.clearDisplay();

  // Header
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print(F("== AUTOPILOT "));
  display.println(autopilotEnabled ? F("[ON] ==") : F("[OFF] =="));

  // Sensor value
  display.setCursor(0, 12);
  display.print(F("Sensor: "));
  display.println(sensorValue);
  drawBar(60, 12, 60, 8, sensorValue, 255);

  // Setpoint
  display.setCursor(0, 24);
  display.print(F("Target: "));
  display.println(setpointValue);
  drawBar(60, 24, 60, 8, setpointValue, 255);

  // Error
  display.setCursor(0, 36);
  display.print(F("Error:  "));
  display.print(error);
  display.print(F(" ("));
  if (error > 10) {
    display.print(F("+ADJ"));
  } else if (error < -10) {
    display.print(F("-ADJ"));
  } else {
    display.print(F("LOCK"));
  }
  display.println(F(")"));

  // Output
  display.setCursor(0, 48);
  display.print(F("Output: "));
  display.println(outputValue);
  drawBar(60, 48, 60, 8, outputValue, 255);

  // Status
  display.setCursor(0, 58);
  if (abs(error) < 10) {
    display.print(F("STATUS: ON TARGET"));
  } else {
    display.print(F("STATUS: CORRECTING"));
  }

  display.display();

  // Serial output
  Serial.print("Sensor: ");
  Serial.print(sensorValue);
  Serial.print(" | Target: ");
  Serial.print(setpointValue);
  Serial.print(" | Error: ");
  Serial.print(error);
  Serial.print(" | Output: ");
  Serial.println(outputValue);

  delay(100);
}
