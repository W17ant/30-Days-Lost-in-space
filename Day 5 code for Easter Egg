/*
====================================================
🛠️ Multi-Zone Light Control + Jingle System
        🚀 Enhanced from Day 5 Mission
====================================================

🎯 Purpose:
- Control **Cabin, Storage, and Cockpit lights** using physical switches.
- Play **audio jingles** on a buzzer based on switch combos.
- Includes an **Easter Egg** melody for extra fun.

📝 Key Differences from Day 5:
1. 🔊 Buzzer Integration:
   - Day 5 used **only switches and LEDs**.
   - This code adds a **buzzer** with **custom jingles** for each light zone.

2. 🎹 Combo Detection:
   - Detects **multiple switches ON** and plays **unique tunes**.
   - Day 5 handled only **one light per switch** without combo logic.

3. 🐣 Easter Egg:
   - Special melody plays when **only Storage switch** is ON.
   - No Easter Egg logic in Day 5.

4. 🧠 Advanced Logic:
   - Uses **if-else trees** and **switch counting** for smart responses.
   - Day 5 relied on **basic digitalRead and digitalWrite**.

====================================================
*/

#include "Arduino.h"

const byte CABIN_LIGHTS_PIN = 10;
const byte STORAGE_LIGHTS_PIN = 11;
const byte COCKPIT_LIGHTS_PIN = 12;

const byte CABIN_LIGHTS_SWITCH_PIN = 2;
const byte STORAGE_LIGHTS_SWITCH_PIN = 3;
const byte COCKPIT_LIGHTS_SWITCH_PIN = 4;

const byte BUZZER_PIN = 9; // Buzzer connected to pin 9

int cabinJingle[] = {262, 294, 330, 392};         // C4-D4-E4-G4
int storageJingle[] = {330, 349, 392, 440};       // E4-F4-G4-A4
int cockpitJingle[] = {392, 440, 494, 523};       // G4-A4-B4-C5
int cabinStorageJingle[] = {262, 330, 349, 392};  // C4-E4-F4-G4
int cabinCockpitJingle[] = {262, 392, 440, 494};  // C4-G4-A4-B4
int storageCockpitJingle[] = {330, 392, 440, 494}; // E4-G4-A4-B4
int allSwitchesJingle[] = {262, 330, 392, 523};    // C4-E4-G4-C5

// Easter Egg: Rick Astley's "Never Gonna Give You Up" intro
int easterEggJingle[] = {392, 392, 440, 392, 523, 494}; // G4-G4-A4-G4-C5-B4

void setup() {
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);
  pinMode(STORAGE_LIGHTS_PIN, OUTPUT);
  pinMode(COCKPIT_LIGHTS_PIN, OUTPUT);

  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(STORAGE_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(COCKPIT_LIGHTS_SWITCH_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  bool cabinOn = digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH;
  bool storageOn = digitalRead(STORAGE_LIGHTS_SWITCH_PIN) == HIGH;
  bool cockpitOn = digitalRead(COCKPIT_LIGHTS_SWITCH_PIN) == HIGH;

  int switchCount = cabinOn + storageOn + cockpitOn;

  if (switchCount == 1) {
    if (cabinOn) {
      controlLight(CABIN_LIGHTS_SWITCH_PIN, CABIN_LIGHTS_PIN);
      playJingle(cabinJingle, 4);
    } else if (storageOn) {
      controlLight(STORAGE_LIGHTS_SWITCH_PIN, STORAGE_LIGHTS_PIN);
      playJingle(storageJingle, 4);
    } else if (cockpitOn) {
      controlLight(COCKPIT_LIGHTS_SWITCH_PIN, COCKPIT_LIGHTS_PIN);
      playJingle(cockpitJingle, 4);
    }
  } else if (switchCount == 2) {
    if (cabinOn && storageOn) {
      playJingle(cabinStorageJingle, 4);
    } else if (cabinOn && cockpitOn) {
      playJingle(cabinCockpitJingle, 4);
    } else if (storageOn && cockpitOn) {
      playJingle(storageCockpitJingle, 4);
    }
  } else if (switchCount == 3) {
    playJingle(allSwitchesJingle, 4);
  } else {
    noTone(BUZZER_PIN); // Turn off buzzer if no switches are ON
  }

  // Easter Egg: Storage ON only
  if (storageOn && !cabinOn && !cockpitOn) {
    playJingle(easterEggJingle, 6);
  }

  // Update lights based on switch state
  digitalWrite(CABIN_LIGHTS_PIN, cabinOn);
  digitalWrite(STORAGE_LIGHTS_PIN, storageOn);
  digitalWrite(COCKPIT_LIGHTS_PIN, cockpitOn);
}

void controlLight(byte switchPin, byte ledPin) {
  digitalWrite(ledPin, HIGH);
}

void playJingle(int notes[], int length) {
  for (int i = 0; i < length; i++) {
    tone(BUZZER_PIN, notes[i], 200);
    delay(250);
  }
  noTone(BUZZER_PIN);
}
