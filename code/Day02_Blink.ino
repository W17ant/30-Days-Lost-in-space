/*
 * Day 2: It's really dark in here...
 * Mission: Blink your first LED
 *
 * Key Concepts:
 * - Digital output
 * - pinMode()
 * - digitalWrite()
 *
 * Components: LED, 220Ω resistor, breadboard, jumper wires
 */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
