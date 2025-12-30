/*
 * Day 12: Can you hear us?
 * Mission: Buzzer sound control
 *
 * Key Concepts:
 * - tone() function
 * - Timing
 *
 * Components: Passive buzzer, resistor
 */

const int BUZZER_PIN = 9;

// Note frequencies
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Buzzer Test Starting...");
}

void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration + 50);
}

void playStartupSound() {
  playTone(NOTE_C4, 200);
  playTone(NOTE_E4, 200);
  playTone(NOTE_G4, 200);
  playTone(NOTE_C5, 400);
}

void playAlertSound() {
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 1000, 100);
    delay(200);
  }
}

void loop() {
  Serial.println("Playing startup sound...");
  playStartupSound();
  delay(1000);

  Serial.println("Playing alert sound...");
  playAlertSound();
  delay(2000);
}
