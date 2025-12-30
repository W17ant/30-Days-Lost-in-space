/*
====================================================
🔧 Battery Simulation – Enhanced from Day 9 Mission
====================================================

📝 Key Differences from Day 9:
1. 📈 Real Battery Charge Accumulation:
   - Uses a photoresistor to **gradually accumulate charge** over time.
   - Charge is stored in `battery_level` and mapped to 0–100% battery.

2. 🌈 Custom LED Behavior:
   - 0–25%: **Flashing Red Alert** (same as Day 9).
   - 26–70%: **Amber Gradient** (Red fades 255→128, Green rises 0→128).
   - 71–100%: **Green Gradient** (Red fades 128→0, Green rises 128→255).
   - **Improved gradient** over Day 9’s fixed color zones.

3. 🚨 Flash Bug Fix:
   - Resolved **green flash glitch** around 25% using LED reset and safe mapping.
   - All RGB values are **constrained to 0–255** to avoid illegal PWM outputs.

4. ⚡ Fully Charged Message:
   - Displays **“Battery Fully Charged”** once at 100% (like Day 9), but with enhanced flag logic.

5. 💡 Code Modularity:
   - Flash logic is now in a **separate function** (`flashRedAlert()`) for clarity and reuse.
====================================================
*/

#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9
#define PHOTORESISTOR_PIN A0

#define BATTERY_CAPACITY 50000UL
unsigned long battery_level = 0;
bool fullyChargedMessageShown = false;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(PHOTORESISTOR_PIN, INPUT);

  Serial.begin(9600);
  Serial.println("Simulated Charging Initiated: Final Patch Applied...");
}

void loop() {
  int lightValue = analogRead(PHOTORESISTOR_PIN);
  battery_level += lightValue;

  if (battery_level > BATTERY_CAPACITY) {
    battery_level = BATTERY_CAPACITY;
  }

  float percentage = ((float)battery_level / (float)BATTERY_CAPACITY) * 100;

  displayColor(0, 0, 0);  // Reset LED OFF to prevent ghosting

  int redValue = 0;
  int greenValue = 0;

  if (percentage < 100.0) {
    if (percentage <= 25.0) {
      redValue = 255;
      greenValue = 0;

      flashRedAlert();  // Flashing red for low battery

      Serial.print("Battery CRITICAL: ");
    } else if (percentage > 25.0 && percentage <= 70.0) {
      // Amber: Red 255→128, Green 0→128 with safe values
      redValue = constrain(map(percentage, 26, 70, 255, 128), 0, 255);
      greenValue = constrain(map(percentage, 26, 70, 0, 128), 0, 255);

      displayColor(redValue, greenValue, 0);
      delay(250);

      Serial.print("Battery Amber: ");
    } else {
      // Green: Red 128→0, Green 128→255 with safe values
      redValue = constrain(map(percentage, 71, 100, 128, 0), 0, 255);
      greenValue = constrain(map(percentage, 71, 100, 128, 255), 0, 255);

      displayColor(redValue, greenValue, 0);
      delay(250);

      Serial.print("Battery Green: ");
    }

    // Serial readout
    Serial.print(percentage, 1);
    Serial.print("% | Red: ");
    Serial.print(redValue);
    Serial.print(" | Green: ");
    Serial.print(greenValue);
    Serial.print(" | Light: ");
    Serial.println(lightValue);

    fullyChargedMessageShown = false;  // Reset message if not full
  } else {
    // Fully charged
    if (!fullyChargedMessageShown) {
      Serial.println("⚡ Battery Fully Charged! All systems GO! ⚡");
      fullyChargedMessageShown = true;
    }

    displayColor(0, 255, 0);  // Solid green
    delay(500);
  }
}

// Flashing red function for clarity
void flashRedAlert() {
  displayColor(0, 0, 0);  // OFF
  delay(100);
  displayColor(255, 0, 0);  // RED ON
  delay(200);
  displayColor(0, 0, 0);  // OFF again
  delay(100);
}

void displayColor(byte red_intensity, byte green_intensity, byte blue_intensity) {
  analogWrite(RED_PIN, red_intensity);
  analogWrite(GREEN_PIN, green_intensity);
  analogWrite(BLUE_PIN, blue_intensity);
}
