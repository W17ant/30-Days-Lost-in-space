/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 22: DISPLAY PANEL - Flight dashboard UI        ###
   ###   Multi-element interface with gauges and indicators ###
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

const int THROTTLE_PIN = A0;
const int BUTTON_PIN = 7;

/* ###########################################################
   ###   3. Global Variables                                ###
   ########################################################### */

int throttleValue = 0;
bool systemArmed = false;
unsigned long lastButtonPress = 0;

/* ###########################################################
   ###   4. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("HERO Flight System"));
  display.println(F("Booting..."));
  display.display();

  delay(1500);
}

/* ###########################################################
   ###   5. Helper Functions                                ###
   ########################################################### */

void drawGauge(int x, int y, int value, const char* label) {
  // Draw gauge outline
  display.drawRect(x, y, 30, 40, SSD1306_WHITE);

  // Fill gauge based on value
  int fillHeight = map(value, 0, 100, 0, 38);
  display.fillRect(x + 1, y + 39 - fillHeight, 28, fillHeight, SSD1306_WHITE);

  // Draw label
  display.setCursor(x + 2, y + 42);
  display.print(label);
}

void drawStatusIndicator(int x, int y, bool active, const char* label) {
  if (active) {
    display.fillCircle(x, y, 5, SSD1306_WHITE);
  } else {
    display.drawCircle(x, y, 5, SSD1306_WHITE);
  }
  display.setCursor(x + 10, y - 3);
  display.print(label);
}

/* ###########################################################
   ###   6. Main Loop                                       ###
   ########################################################### */

void loop() {
  // Read inputs
  throttleValue = map(analogRead(THROTTLE_PIN), 0, 1023, 0, 100);

  // Check button press (debounced)
  if (digitalRead(BUTTON_PIN) == LOW && millis() - lastButtonPress > 300) {
    systemArmed = !systemArmed;
    lastButtonPress = millis();
  }

  // Update display
  display.clearDisplay();

  // Header
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(F("== FLIGHT DASHBOARD =="));

  // Draw throttle gauge
  drawGauge(5, 12, throttleValue, "THR");

  // Status panel
  display.setCursor(45, 12);
  display.print(F("Throttle: "));
  display.print(throttleValue);
  display.println(F("%"));

  // Status indicators
  drawStatusIndicator(50, 30, systemArmed, "ARMED");
  drawStatusIndicator(50, 42, throttleValue > 10, "THRUST");
  drawStatusIndicator(50, 54, throttleValue > 80, "MAX PWR");

  // Mission time
  display.setCursor(0, 56);
  display.print(F("T+"));
  display.print(millis() / 1000);
  display.print(F("s"));

  display.display();
  delay(50);
}

/* ###########################################################
   ###           END OF DAY 22 - DISPLAY PANEL              ###
   ########################################################### */
