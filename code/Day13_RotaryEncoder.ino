/*
 * Day 13: HERO Security 101
 * Mission: Rotary encoder intro
 *
 * Key Concepts:
 * - digitalRead()
 * - Encoder hardware
 * - Interrupt handling
 *
 * Components: Rotary encoder, resistors, breadboard
 */

const int ENCODER_CLK = 2;
const int ENCODER_DT = 3;
const int ENCODER_SW = 4;

volatile int encoderValue = 0;
int lastCLKState;

void setup() {
  Serial.begin(9600);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  lastCLKState = digitalRead(ENCODER_CLK);

  Serial.println("Rotary Encoder Ready");
  Serial.println("Turn the knob or press the button");
}

void loop() {
  // Read current CLK state
  int currentCLKState = digitalRead(ENCODER_CLK);

  // Detect rotation
  if (currentCLKState != lastCLKState && currentCLKState == HIGH) {
    if (digitalRead(ENCODER_DT) != currentCLKState) {
      encoderValue++;
      Serial.print("Clockwise - Value: ");
    } else {
      encoderValue--;
      Serial.print("Counter-clockwise - Value: ");
    }
    Serial.println(encoderValue);
  }

  lastCLKState = currentCLKState;

  // Check button press
  if (digitalRead(ENCODER_SW) == LOW) {
    Serial.println("Button Pressed!");
    encoderValue = 0;
    Serial.println("Value Reset to 0");
    delay(200); // Debounce
  }
}
