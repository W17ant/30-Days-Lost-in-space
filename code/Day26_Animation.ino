/*
 * Day 26: Fasten your seatbelt
 * Mission: OLED animation basics
 *
 * Key Concepts:
 * - Frame-based animation
 * - Sprite movement
 * - Timing control
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

// Rocket sprite 8x16
const unsigned char PROGMEM rocketSprite[] = {
  0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0x7E, 0x3C, 0x24, 0x42, 0x81, 0x00
};

// Star positions
struct Star {
  int x;
  int y;
  int speed;
};

Star stars[20];

// Rocket position
float rocketX = 60;
float rocketY = 24;
float rocketVelX = 0;
float rocketVelY = 0;

// Animation timing
unsigned long lastFrame = 0;
const int FRAME_DELAY = 33; // ~30 FPS

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Initialize stars
  for (int i = 0; i < 20; i++) {
    stars[i].x = random(0, SCREEN_WIDTH);
    stars[i].y = random(0, SCREEN_HEIGHT);
    stars[i].speed = random(1, 4);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
}

void updateStars() {
  for (int i = 0; i < 20; i++) {
    stars[i].x -= stars[i].speed;
    if (stars[i].x < 0) {
      stars[i].x = SCREEN_WIDTH;
      stars[i].y = random(0, SCREEN_HEIGHT);
      stars[i].speed = random(1, 4);
    }
  }
}

void drawStars() {
  for (int i = 0; i < 20; i++) {
    if (stars[i].speed > 2) {
      display.drawPixel(stars[i].x, stars[i].y, SSD1306_WHITE);
      display.drawPixel(stars[i].x + 1, stars[i].y, SSD1306_WHITE);
    } else {
      display.drawPixel(stars[i].x, stars[i].y, SSD1306_WHITE);
    }
  }
}

void updateRocket() {
  // Simple oscillation pattern
  static float angle = 0;
  angle += 0.1;

  rocketY = 24 + sin(angle) * 15;
  rocketX = 60 + cos(angle * 0.5) * 20;
}

void drawRocket() {
  display.drawBitmap((int)rocketX, (int)rocketY, rocketSprite, 8, 16, SSD1306_WHITE);

  // Draw exhaust flame (alternating)
  if ((millis() / 100) % 2 == 0) {
    display.drawLine(rocketX + 2, rocketY + 16, rocketX + 4, rocketY + 20, SSD1306_WHITE);
    display.drawLine(rocketX + 5, rocketY + 16, rocketX + 4, rocketY + 22, SSD1306_WHITE);
  } else {
    display.drawLine(rocketX + 3, rocketY + 16, rocketX + 3, rocketY + 21, SSD1306_WHITE);
    display.drawLine(rocketX + 5, rocketY + 16, rocketX + 5, rocketY + 19, SSD1306_WHITE);
  }
}

void loop() {
  if (millis() - lastFrame < FRAME_DELAY) {
    return;
  }
  lastFrame = millis();

  // Update
  updateStars();
  updateRocket();

  // Draw
  display.clearDisplay();

  // Title
  display.setCursor(30, 0);
  display.setTextSize(1);
  display.print(F("HERO FLIGHT"));

  // Stars background
  drawStars();

  // Rocket
  drawRocket();

  // Status bar
  display.setCursor(0, 56);
  display.print(F("Frame: "));
  display.print(millis() / FRAME_DELAY);

  display.display();
}
