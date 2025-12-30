/*
 * Day 29: Prepare for landing
 * Mission: Advanced motor control
 *
 * Key Concepts:
 * - Smooth acceleration/deceleration
 * - Motor sequences
 * - Display integration
 *
 * Components: DC motor, L293D driver, OLED display, button
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int MOTOR_EN = 9;
const int MOTOR_IN1 = 7;
const int MOTOR_IN2 = 8;
const int BUTTON_PIN = 2;

int currentSpeed = 0;
int targetSpeed = 0;
bool motorDirection = true;

enum MotorState { STOPPED, ACCELERATING, RUNNING, DECELERATING, LANDING };
MotorState state = STOPPED;

unsigned long stateStartTime = 0;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  stopMotor();
  updateDisplay();
}

void setMotor(int speed, bool forward) {
  if (forward) {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
  } else {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
  }
  analogWrite(MOTOR_EN, speed);
}

void stopMotor() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_EN, 0);
  currentSpeed = 0;
}

void drawSpeedBar() {
  display.drawRect(10, 45, 108, 12, SSD1306_WHITE);
  int barWidth = map(currentSpeed, 0, 255, 0, 106);
  display.fillRect(11, 46, barWidth, 10, SSD1306_WHITE);
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Header
  display.setCursor(15, 0);
  display.println(F("=== LANDING CTRL ==="));

  // State
  display.setCursor(0, 15);
  display.print(F("State: "));
  switch (state) {
    case STOPPED:      display.println(F("STOPPED")); break;
    case ACCELERATING: display.println(F("ACCELERATING")); break;
    case RUNNING:      display.println(F("CRUISING")); break;
    case DECELERATING: display.println(F("DECELERATING")); break;
    case LANDING:      display.println(F("LANDING SEQ")); break;
  }

  // Speed info
  display.setCursor(0, 28);
  display.print(F("Speed: "));
  display.print(map(currentSpeed, 0, 255, 0, 100));
  display.print(F("% "));
  display.println(motorDirection ? F("[FWD]") : F("[REV]"));

  // Speed bar
  drawSpeedBar();

  // Instructions
  display.setCursor(0, 58);
  display.print(F("Press btn: "));
  display.print(state == STOPPED ? F("START") : F("LAND"));

  display.display();
}

void smoothAccelerate(int target, int rate) {
  if (currentSpeed < target) {
    currentSpeed = min(currentSpeed + rate, target);
  } else if (currentSpeed > target) {
    currentSpeed = max(currentSpeed - rate, target);
  }
  setMotor(currentSpeed, motorDirection);
}

void loop() {
  // Check button press
  static bool lastButton = HIGH;
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButton == HIGH) {
    if (state == STOPPED) {
      state = ACCELERATING;
      targetSpeed = 200;
      stateStartTime = millis();
    } else if (state == RUNNING) {
      state = LANDING;
      stateStartTime = millis();
    }
    delay(50); // Debounce
  }
  lastButton = buttonState;

  // State machine
  if (millis() - lastUpdate > 50) {
    lastUpdate = millis();

    switch (state) {
      case ACCELERATING:
        smoothAccelerate(targetSpeed, 5);
        if (currentSpeed >= targetSpeed) {
          state = RUNNING;
        }
        break;

      case RUNNING:
        // Maintain speed
        break;

      case LANDING:
        // Landing sequence: slow down, reverse briefly, stop
        if (millis() - stateStartTime < 2000) {
          smoothAccelerate(100, 3);
        } else if (millis() - stateStartTime < 3000) {
          motorDirection = false;
          smoothAccelerate(80, 5);
        } else if (millis() - stateStartTime < 4000) {
          smoothAccelerate(0, 5);
        } else {
          stopMotor();
          motorDirection = true;
          state = STOPPED;
        }
        break;

      default:
        break;
    }

    updateDisplay();
  }
}
