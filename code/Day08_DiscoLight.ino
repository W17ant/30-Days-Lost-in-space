/*
====================================================
🎉 DISCO PARTY MODE – Enhanced from Day 8 Mission
====================================================

📝 Key Differences from Day 8:
1. 🌈 Rapid Color Cycling:
   - Instead of slowly flashing one color (RED), this code **rapidly cycles** through a sequence of **7 colors**.
   - Colors include: Red, Green, Blue, Yellow, Cyan, Magenta, White.

2. ⚡ Fast-Paced Animation:
   - Each color is displayed for **100ms**, creating a **disco strobe effect**.
   - Day 8 used slower color changes for LED testing and gradual transitions.

3. 🕹️ No Input Required:
   - This code **loops endlessly** without external input or sensor readings.
   - Day 8 focused on **basic RGB control and setup**, preparing for future missions.

4. 🚀 Purpose:
   - Day 8 was about **understanding RGB LEDs**.
   - This code transforms that into **entertainment mode**, perfect for restoring **crew morale** (and sanity) during long repairs.
====================================================
*/

#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // DISCO PARTY: Rapid color changes
  displayColor(255, 0, 0);    // RED
  delay(100);
  displayColor(0, 255, 0);    // GREEN
  delay(100);
  displayColor(0, 0, 255);    // BLUE
  delay(100);
  displayColor(255, 255, 0);  // YELLOW
  delay(100);
  displayColor(0, 255, 255);  // CYAN
  delay(100);
  displayColor(255, 0, 255);  // MAGENTA
  delay(100);
  displayColor(255, 255, 255); // WHITE BLAST
  delay(100);
  displayColor(0, 0, 0);      // OFF for a breather
  delay(100);
}

// Function to set RGB LED color
void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}
