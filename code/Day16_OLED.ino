/*
 * Day 16: Hello OLED
 * Mission: OLED display introduction
 *
 * Key Concepts:
 * - I2C communication
 * - OLED display basics
 * - Graphics library usage
 *
 * Components: 128x64 OLED display (SSD1306), jumper wires
 *
 * Note: Requires Adafruit_SSD1306 and Adafruit_GFX libraries
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Welcome message
  display.setCursor(0, 0);
  display.println(F("=== HERO SYSTEMS ==="));
  display.println();
  display.println(F("OLED Display"));
  display.println(F("Initialized"));
  display.println();
  display.println(F("Day 16 Complete!"));
  display.display();

  delay(2000);
}

void loop() {
  // Display cycling text demo
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(F("HERO"));
  display.setTextSize(1);
  display.println();
  display.println(F("Systems Online"));
  display.println();
  display.print(F("Uptime: "));
  display.print(millis() / 1000);
  display.println(F("s"));
  display.display();

  delay(1000);
}
