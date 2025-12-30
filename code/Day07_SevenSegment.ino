/*
 * Day 7: We still need to keep an eye on this
 * Mission: 7-segment display
 *
 * Key Concepts:
 * - digitalWrite() control of display segments
 *
 * Components: 7-segment display, resistors, breadboard
 */

const int SEGMENT_PINS[] = {2, 3, 4, 5, 6, 7, 8};

// Segment patterns for digits 0-9 (a,b,c,d,e,f,g)
const byte DIGIT_PATTERNS[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

void setup() {
  for (int i = 0; i < 7; i++) {
    pinMode(SEGMENT_PINS[i], OUTPUT);
  }
}

void displayNumber(int number) {
  if (number < 0 || number > 9) return;

  for (int i = 0; i < 7; i++) {
    digitalWrite(SEGMENT_PINS[i], DIGIT_PATTERNS[number][i]);
  }
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    displayNumber(i);
    delay(1000);
  }
}
