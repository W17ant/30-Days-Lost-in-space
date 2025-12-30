/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 18: MONITORING - System status dashboard       ###
   ###   Multi-sensor integration with real-time display    ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ###########################################################
   ###   1. Display Configuration                           ###
   ########################################################### */

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* ###########################################################
   ###   2. Pin Definitions                                 ###
   ########################################################### */

const int LIGHT_SENSOR_PIN = A0;
const int POWER_SENSOR_PIN = A1;

/* ###########################################################
   ###   3. Global Variables                                ###
   ########################################################### */

int lightLevel = 0;
int powerLevel = 0;

/* ###########################################################
   ###   4. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("HERO Monitoring"));
  display.println(F("System Online"));
  display.display();

  delay(1000);
}

/* ###########################################################
   ###   5. Helper Functions                                ###
   ########################################################### */

void drawProgressBar(int x, int y, int width, int height, int value) {
  display.drawRect(x, y, width, height, SSD1306_WHITE);
  int fillWidth = map(value, 0, 100, 0, width - 2);
  display.fillRect(x + 1, y + 1, fillWidth, height - 2, SSD1306_WHITE);
}

String getStatus(int value) {
  if (value > 75) return "HIGH";
  if (value > 25) return "NORM";
  return "LOW";
}

/* ###########################################################
   ###   6. Main Loop                                       ###
   ########################################################### */

void loop() {
  // Read sensors
  lightLevel = map(analogRead(LIGHT_SENSOR_PIN), 0, 1023, 0, 100);
  powerLevel = map(analogRead(POWER_SENSOR_PIN), 0, 1023, 0, 100);

  // Update display
  display.clearDisplay();

  // Header
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(F("=== HERO STATUS ==="));

  // Light sensor
  display.setCursor(0, 16);
  display.print(F("Light: "));
  display.print(lightLevel);
  display.print(F("% ["));
  display.print(getStatus(lightLevel));
  display.println(F("]"));
  drawProgressBar(0, 26, 100, 8, lightLevel);

  // Power level
  display.setCursor(0, 40);
  display.print(F("Power: "));
  display.print(powerLevel);
  display.print(F("% ["));
  display.print(getStatus(powerLevel));
  display.println(F("]"));
  drawProgressBar(0, 50, 100, 8, powerLevel);

  display.display();

  // Serial output
  Serial.print("Light: ");
  Serial.print(lightLevel);
  Serial.print("% | Power: ");
  Serial.print(powerLevel);
  Serial.println("%");

  delay(250);
}

/* ###########################################################
   ###           END OF DAY 18 - MONITORING                 ###
   ########################################################### */
