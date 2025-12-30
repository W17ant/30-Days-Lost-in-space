/*
 * Day 30: Mission complete
 * Mission: Complete integrated system
 *
 * Key Concepts:
 * - System integration
 * - All components working together
 * - Final mission demonstration
 *
 * Components: OLED display, LEDs, buzzer, motor, sensors, keypad
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin definitions
const int MOTOR_EN = 9;
const int MOTOR_IN1 = 7;
const int MOTOR_IN2 = 8;
const int BUZZER_PIN = 6;
const int RED_LED = 10;
const int GREEN_LED = 11;
const int SENSOR_PIN = A0;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A1, A2, A3, 5};
byte colPins[COLS] = {4, 3, 2, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// System states
enum SystemState { BOOT, IDLE, ARMED, COUNTDOWN, LAUNCH, FLIGHT, LANDING, COMPLETE };
SystemState state = BOOT;

const String LAUNCH_CODE = "1234";
String enteredCode = "";

int countdown = 10;
unsigned long stateTimer = 0;
int motorSpeed = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Display failed"));
    for (;;);
  }

  state = BOOT;
  stateTimer = millis();
}

void playTone(int freq, int duration) {
  tone(BUZZER_PIN, freq, duration);
}

void setMotor(int speed) {
  motorSpeed = speed;
  if (speed > 0) {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_EN, speed);
  } else {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    analogWrite(MOTOR_EN, 0);
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  switch (state) {
    case BOOT:
      display.setCursor(20, 10);
      display.setTextSize(2);
      display.println(F("HERO"));
      display.setTextSize(1);
      display.setCursor(10, 35);
      display.println(F("Mission Control"));
      display.setCursor(10, 50);
      display.println(F("Initializing..."));
      break;

    case IDLE:
      display.setCursor(5, 0);
      display.println(F("=== HERO COMMAND ==="));
      display.setCursor(0, 20);
      display.println(F("Enter launch code:"));
      display.setCursor(40, 35);
      display.setTextSize(2);
      for (int i = 0; i < enteredCode.length(); i++) {
        display.print(F("*"));
      }
      display.setTextSize(1);
      display.setCursor(0, 55);
      display.println(F("Press # to confirm"));
      break;

    case ARMED:
      display.setCursor(25, 0);
      display.println(F("SYSTEM ARMED"));
      display.setCursor(10, 25);
      display.setTextSize(2);
      display.println(F("READY"));
      display.setTextSize(1);
      display.setCursor(5, 50);
      display.println(F("Press A to launch"));
      break;

    case COUNTDOWN:
      display.setCursor(30, 0);
      display.println(F("T-MINUS"));
      display.setTextSize(4);
      display.setCursor(50, 20);
      display.println(countdown);
      display.setTextSize(1);
      break;

    case LAUNCH:
      display.setTextSize(2);
      display.setCursor(15, 25);
      display.println(F("LIFTOFF!"));
      break;

    case FLIGHT:
      display.setCursor(25, 0);
      display.println(F("IN FLIGHT"));
      display.setCursor(0, 20);
      display.print(F("Altitude: "));
      display.print(map(motorSpeed, 0, 255, 0, 100));
      display.println(F(" km"));
      display.setCursor(0, 35);
      display.print(F("Sensor: "));
      display.println(analogRead(SENSOR_PIN));
      display.setCursor(0, 55);
      display.println(F("Press D to land"));
      break;

    case LANDING:
      display.setCursor(20, 0);
      display.println(F("LANDING SEQ"));
      display.setCursor(0, 25);
      display.print(F("Speed: "));
      display.print(map(motorSpeed, 0, 255, 0, 100));
      display.println(F("%"));
      break;

    case COMPLETE:
      display.setCursor(5, 0);
      display.println(F("=== MISSION ==="));
      display.setTextSize(2);
      display.setCursor(10, 20);
      display.println(F("COMPLETE"));
      display.setTextSize(1);
      display.setCursor(0, 50);
      display.println(F("Congratulations!"));
      break;
  }

  display.display();
}

void loop() {
  char key = keypad.getKey();

  switch (state) {
    case BOOT:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, HIGH);
      if (millis() - stateTimer > 3000) {
        state = IDLE;
        enteredCode = "";
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        playTone(1000, 200);
      }
      break;

    case IDLE:
      if (key) {
        if (key == '#') {
          if (enteredCode == LAUNCH_CODE) {
            state = ARMED;
            playTone(2000, 300);
            digitalWrite(GREEN_LED, HIGH);
          } else {
            playTone(200, 500);
            digitalWrite(RED_LED, HIGH);
            delay(500);
            digitalWrite(RED_LED, LOW);
          }
          enteredCode = "";
        } else if (key == '*') {
          enteredCode = "";
        } else if (enteredCode.length() < 4) {
          enteredCode += key;
          playTone(800, 50);
        }
      }
      break;

    case ARMED:
      if (key == 'A') {
        state = COUNTDOWN;
        countdown = 10;
        stateTimer = millis();
      }
      break;

    case COUNTDOWN:
      if (millis() - stateTimer >= 1000) {
        stateTimer = millis();
        countdown--;
        playTone(1000, 100);

        if (countdown <= 0) {
          state = LAUNCH;
          stateTimer = millis();
          playTone(2000, 1000);
        }
      }
      // Flashing red during countdown
      digitalWrite(RED_LED, (millis() / 250) % 2);
      break;

    case LAUNCH:
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      setMotor(255);
      if (millis() - stateTimer > 2000) {
        state = FLIGHT;
      }
      break;

    case FLIGHT:
      // Cruise at medium speed
      setMotor(180);
      if (key == 'D') {
        state = LANDING;
        stateTimer = millis();
      }
      break;

    case LANDING:
      // Gradual slowdown
      motorSpeed = max(0, motorSpeed - 2);
      setMotor(motorSpeed);
      if (motorSpeed == 0) {
        state = COMPLETE;
        playTone(1500, 100);
        delay(150);
        playTone(2000, 100);
        delay(150);
        playTone(2500, 300);
      }
      delay(50);
      break;

    case COMPLETE:
      digitalWrite(GREEN_LED, (millis() / 500) % 2);
      if (key == '*') {
        state = BOOT;
        stateTimer = millis();
      }
      break;
  }

  updateDisplay();
}
