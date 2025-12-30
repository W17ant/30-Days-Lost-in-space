/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 12: BUZZER - Audio feedback with tone()        ###
   ###   Learn frequency control and musical notes          ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Pin Definitions                                 ###
   ########################################################### */

const int BUZZER_PIN = 9;

/* ###########################################################
   ###   2. Note Frequency Definitions                      ###
   ########################################################### */

#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_B4 494
#define NOTE_C5 523

/* ###########################################################
   ###   3. Setup Function                                  ###
   ########################################################### */

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Buzzer Test Starting...");
}

/* ###########################################################
   ###   4. Helper Functions                                ###
   ########################################################### */

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

/* ###########################################################
   ###   5. Main Loop                                       ###
   ########################################################### */

void loop() {
  Serial.println("Playing startup sound...");
  playStartupSound();
  delay(1000);

  Serial.println("Playing alert sound...");
  playAlertSound();
  delay(2000);
}

/* ###########################################################
   ###           END OF DAY 12 - BUZZER                     ###
   ########################################################### */
