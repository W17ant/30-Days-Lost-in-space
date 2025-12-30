/*
 * Day 28: Blast off!
 * Mission: DC motor control basics
 *
 * Key Concepts:
 * - PWM motor speed control
 * - H-bridge direction control
 * - analogWrite() for speed
 *
 * Components: DC motor, L293D motor driver, potentiometer
 */

const int MOTOR_EN = 9;   // Enable pin (PWM)
const int MOTOR_IN1 = 7;  // Direction pin 1
const int MOTOR_IN2 = 8;  // Direction pin 2

const int SPEED_PIN = A0;
const int DIR_BUTTON = 2;

int motorSpeed = 0;
bool motorDirection = true; // true = forward, false = reverse
bool lastButtonState = HIGH;
unsigned long lastDebounce = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(DIR_BUTTON, INPUT_PULLUP);

  // Start with motor off
  stopMotor();

  Serial.println(F("=== MOTOR CONTROL ==="));
  Serial.println(F("Turn pot for speed"));
  Serial.println(F("Press button for direction"));
}

void setMotorDirection(bool forward) {
  if (forward) {
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);
  } else {
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
  }
}

void stopMotor() {
  digitalWrite(MOTOR_IN1, LOW);
  digitalWrite(MOTOR_IN2, LOW);
  analogWrite(MOTOR_EN, 0);
}

void loop() {
  // Read speed from potentiometer
  int potValue = analogRead(SPEED_PIN);
  motorSpeed = map(potValue, 0, 1023, 0, 255);

  // Check direction button (debounced)
  bool buttonState = digitalRead(DIR_BUTTON);
  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastDebounce > 200) {
    motorDirection = !motorDirection;
    lastDebounce = millis();
    Serial.print(F("Direction: "));
    Serial.println(motorDirection ? F("FORWARD") : F("REVERSE"));
  }
  lastButtonState = buttonState;

  // Apply motor settings
  if (motorSpeed > 10) { // Dead zone for low values
    setMotorDirection(motorDirection);
    analogWrite(MOTOR_EN, motorSpeed);
  } else {
    stopMotor();
  }

  // Serial output
  Serial.print(F("Speed: "));
  Serial.print(map(motorSpeed, 0, 255, 0, 100));
  Serial.print(F("% | Direction: "));
  Serial.print(motorDirection ? F("FWD") : F("REV"));
  Serial.print(F(" | PWM: "));
  Serial.println(motorSpeed);

  delay(100);
}
