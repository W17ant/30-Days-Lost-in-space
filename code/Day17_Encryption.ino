/*
 * Day 17: Top secret decoder
 * Mission: Message encryption/decryption
 *
 * Key Concepts:
 * - Character manipulation
 * - Caesar cipher implementation
 * - String processing
 *
 * Components: OLED display, rotary encoder
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int ENCODER_CLK = 2;
const int ENCODER_DT = 3;
const int ENCODER_SW = 4;

volatile int shiftValue = 0;
int lastCLKState;

String secretMessage = "KHUR VDYHV WKH GDB";
String decodedMessage = "";

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
