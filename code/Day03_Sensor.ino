/*
 * Day 3: I'm worried about your battery levels
 * Mission: Read analog sensors
 *
 * Key Concepts:
 * - analogRead()
 * - Power monitoring
 * - Serial communication
 *
 * Components: Photoresistor, 10kΩ resistor
 */

const int PHOTORESISTOR_PIN = A0;

void setup() {
  Serial.begin(9600);
  pinMode(PHOTORESISTOR_PIN, INPUT);
}

void loop() {
  int sensorValue = analogRead(PHOTORESISTOR_PIN);
  Serial.println(sensorValue);
  delay(100);
}
