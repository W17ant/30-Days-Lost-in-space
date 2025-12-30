/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 17: ENCRYPTION - Caesar cipher decoder         ###
   ###   Learn character manipulation and string processing ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ###########################################################
   ###   1. Display Configuration                           ###
   ########################################################### */

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* ###########################################################
   ###   2. Pin Definitions                                 ###
   ########################################################### */

const int ENCODER_CLK = 2;
const int ENCODER_DT = 3;
const int ENCODER_SW = 4;

/* ###########################################################
   ###   3. Global Variables                                ###
   ########################################################### */

volatile int shiftValue = 0;
int lastCLKState;

String secretMessage = "KHUR VDYHV WKH GDB";
String decodedMessage = "";

/* ###########################################################
   ###   4. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  lastCLKState = digitalRead(ENCODER_CLK);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("=== DECODER ==="));
  display.println(F("Turn knob to decode"));
  display.display();

  delay(1000);
  updateDisplay();
}

/* ###########################################################
   ###   5. Helper Functions                                ###
   ########################################################### */

String caesarCipher(String text, int shift) {
  String result = "";
  for (int i = 0; i < text.length(); i++) {
    char c = text[i];
    if (c >= 'A' && c <= 'Z') {
      c = ((c - 'A' - shift + 26) % 26) + 'A';
    } else if (c >= 'a' && c <= 'z') {
      c = ((c - 'a' - shift + 26) % 26) + 'a';
    }
    result += c;
  }
  return result;
}

void updateDisplay() {
  decodedMessage = caesarCipher(secretMessage, shiftValue);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(F("=== TOP SECRET ==="));
  display.println();
  display.print(F("Shift: "));
  display.println(shiftValue);
  display.println();
  display.println(F("Encoded:"));
  display.println(secretMessage);
  display.println();
  display.println(F("Decoded:"));
  display.println(decodedMessage);
  display.display();

  Serial.print("Shift: ");
  Serial.print(shiftValue);
  Serial.print(" -> ");
  Serial.println(decodedMessage);
}

/* ###########################################################
   ###   6. Main Loop                                       ###
   ########################################################### */

void loop() {
  int currentCLKState = digitalRead(ENCODER_CLK);

  if (currentCLKState != lastCLKState && currentCLKState == HIGH) {
    if (digitalRead(ENCODER_DT) != currentCLKState) {
      shiftValue = (shiftValue + 1) % 26;
    } else {
      shiftValue = (shiftValue - 1 + 26) % 26;
    }
    updateDisplay();
  }

  lastCLKState = currentCLKState;

  if (digitalRead(ENCODER_SW) == LOW) {
    shiftValue = 0;
    updateDisplay();
    delay(200);
  }
}

/* ###########################################################
   ###           END OF DAY 17 - ENCRYPTION                 ###
   ########################################################### */
