/*
 * Day 6: Time to fix the battery
 * Mission: Battery management system
 *
 * Key Concepts:
 * - analogRead()
 * - Data types (int, long)
 * - Logic
 *
 * Components: Photoresistor, multiple LEDs, resistors
 */

const byte PHOTORESISTOR_PIN = A0;
const unsigned long BATTERY_CAPACITY = 50000;

void setup() {
  Serial.begin(9600);
  pinMode(PHOTORESISTOR_PIN, INPUT);
}

void loop() {
  static unsigned long battery_level = 0;
  battery_level += analogRead(PHOTORESISTOR_PIN);

  if (battery_level > BATTERY_CAPACITY) {
    battery_level = BATTERY_CAPACITY;
  }

  float percentage = ((float)battery_level / (float)BATTERY_CAPACITY) * 100;
  Serial.print("Battery: ");
  Serial.print(percentage);
  Serial.println("%");
  delay(100);
}
