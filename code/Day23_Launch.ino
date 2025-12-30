/*
 * Day 23: Flight sequence
 * Mission: Launch countdown system
 *
 * Key Concepts:
 * - State machines
 * - Countdown sequences
 * - Multi-component coordination
 *
 * Components: OLED display, LEDs, buzzer, button
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int BUTTON_PIN = 7;
const int BUZZER_PIN = 9;
const int RED_LED = 10;
const int YELLOW_LED = 11;
const int GREEN_LED = 12;

enum State { IDLE, COUNTDOWN, LAUNCH, ABORT };
State currentState = IDLE;

int countdownValue = 10;
unsigned long lastTick = 0;
unsigned long launchTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  updateDisplay();
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  switch (currentState) {
    case IDLE:
      display.setTextSize(1);
      display.setCursor(10, 0);
      display.println(F("=== LAUNCH CONTROL ==="));
      display.setCursor(20, 25);
      display.setTextSize(2);
      display.println(F("READY"));
      display.setTextSize(1);
      display.setCursor(15, 50);
      display.println(F("Press to initiate"));
      break;

    case COUNTDOWN:
      display.setTextSize(1);
      display.setCursor(25, 0);
      display.println(F("T-MINUS"));
      display.setTextSize(4);
      display.setCursor(50, 20);
      display.println(countdownValue);
      display.setTextSize(1);
      display.setCursor(15, 55);
      display.println(F("Hold btn to abort"));
      break;

    case LAUNCH:
      display.setTextSize(2);
      display.setCursor(20, 10);
      display.println(F("LIFTOFF!"));
      display.setTextSize(1);
      display.setCursor(20, 40);
      display.print(F("Flight time: "));
      display.print((millis() - launchTime) / 1000);
      display.println(F("s"));
      break;

    case ABORT:
      display.setTextSize(2);
      display.setCursor(25, 20);
      display.println(F("ABORT"));
      display.setTextSize(1);
      display.setCursor(15, 50);
      display.println(F("Press to reset"));
      break;
  }

  display.display();
}

void setLEDs(bool red, bool yellow, bool green) {
  digitalWrite(RED_LED, red);
  digitalWrite(YELLOW_LED, yellow);
  digitalWrite(GREEN_LED, green);
}

void loop() {
  bool buttonPressed = digitalRead(BUTTON_PIN) == LOW;

  switch (currentState) {
    case IDLE:
      setLEDs(false, true, false);
      if (buttonPressed) {
        currentState = COUNTDOWN;
        countdownValue = 10;
        lastTick = millis();
        delay(200);
      }
      break;

    case COUNTDOWN:
      setLEDs(true, true, false);

      // Check for abort (hold button)
      if (buttonPressed) {
        currentState = ABORT;
        noTone(BUZZER_PIN);
        break;
      }

      // Count down every second
      if (millis() - lastTick >= 1000) {
        lastTick = millis();
        tone(BUZZER_PIN, 1000, 100);
        countdownValue--;

        if (countdownValue <= 0) {
          currentState = LAUNCH;
          launchTime = millis();
          tone(BUZZER_PIN, 2000, 500);
        }
      }
      break;

    case LAUNCH:
      setLEDs(false, false, true);
      // Blink green during flight
      if ((millis() / 200) % 2 == 0) {
        digitalWrite(GREEN_LED, HIGH);
      } else {
        digitalWrite(GREEN_LED, LOW);
      }
      break;

    case ABORT:
      setLEDs(true, false, false);
      if (buttonPressed) {
        currentState = IDLE;
        delay(200);
      }
      break;
  }

  updateDisplay();
  delay(50);
}
