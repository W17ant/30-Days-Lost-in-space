/*
 * Day 4: Cabin Lighting
 * Mission: Multiple LED control
 *
 * Key Concepts:
 * - digitalWrite() with multiple pins
 * - Loops
 *
 * Components: 3x LEDs, 3x 220Ω resistors, breadboard, jumper wires
 */

const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  // All LEDs on
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  delay(500);

  // All LEDs off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(500);
}
