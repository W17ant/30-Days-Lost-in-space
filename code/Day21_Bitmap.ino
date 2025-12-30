/*
 * Day 21: Can you picture it?
 * Mission: Bitmap graphics on OLED
 *
 * Key Concepts:
 * - Bitmap image display
 * - PROGMEM storage
 * - Custom graphics
 *
 * Components: OLED display
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Rocket bitmap 16x32 pixels
const unsigned char PROGMEM rocketBitmap[] = {
  0x01, 0x80, 0x03, 0xC0, 0x07, 0xE0, 0x0F, 0xF0,
  0x0F, 0xF0, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8,
  0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8,
  0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8, 0x1F, 0xF8,
  0x3F, 0xFC, 0x7F, 0xFE, 0x7F, 0xFE, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0x3F, 0xFC,
  0x1F, 0xF8, 0x0E, 0x70, 0x1C, 0x38, 0x38, 0x1C,
  0x30, 0x0C, 0x20, 0x04, 0x00, 0x00, 0x00, 0x00
};

// Star bitmap 8x8 pixels
const unsigned char PROGMEM starBitmap[] = {
  0x08, 0x08, 0x3E, 0x1C, 0x3E, 0x08, 0x14, 0x22
};

// Planet bitmap 16x16 pixels
const unsigned char PROGMEM planetBitmap[] = {
  0x07, 0xE0, 0x1F, 0xF8, 0x3F, 0xFC, 0x7F, 0xFE,
  0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE,
  0x7F, 0xFE, 0x3F, 0xFC, 0x1F, 0xF8, 0x07, 0xE0
};

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Bitmap Demo"));
  display.display();

  delay(1000);
}

void drawStarfield() {
  // Draw random stars
  for (int i = 0; i < 15; i++) {
    int x = random(0, SCREEN_WIDTH);
    int y = random(0, SCREEN_HEIGHT);
    display.drawPixel(x, y, SSD1306_WHITE);
  }

  // Draw some star bitmaps
  display.drawBitmap(10, 10, starBitmap, 8, 8, SSD1306_WHITE);
  display.drawBitmap(100, 5, starBitmap, 8, 8, SSD1306_WHITE);
  display.drawBitmap(60, 50, starBitmap, 8, 8, SSD1306_WHITE);
}

void loop() {
  // Scene 1: Rocket
  display.clearDisplay();
  drawStarfield();
  display.drawBitmap(56, 16, rocketBitmap, 16, 32, SSD1306_WHITE);
  display.setCursor(30, 56);
  display.print(F("HERO Shuttle"));
  display.display();
  delay(2000);

  // Scene 2: Planet
  display.clearDisplay();
  drawStarfield();
  display.drawBitmap(56, 24, planetBitmap, 16, 16, SSD1306_WHITE);
  display.setCursor(35, 56);
  display.print(F("Destination"));
  display.display();
  delay(2000);

  // Scene 3: Multiple objects
  display.clearDisplay();
  drawStarfield();
  display.drawBitmap(10, 20, rocketBitmap, 16, 32, SSD1306_WHITE);
  display.drawBitmap(100, 30, planetBitmap, 16, 16, SSD1306_WHITE);
  display.setCursor(30, 0);
  display.print(F("Mission Day 21"));
  display.display();
  delay(2000);
}
