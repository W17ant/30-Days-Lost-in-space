/*
 * Day 19: Incoming transmission
 * Mission: Data visualization on OLED
 *
 * Key Concepts:
 * - Graphical data display
 * - Line graphs
 * - Real-time plotting
 *
 * Components: OLED display, photoresistor
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int SENSOR_PIN = A0;
const int GRAPH_WIDTH = 100;
const int GRAPH_HEIGHT = 40;
const int GRAPH_X = 20;
const int GRAPH_Y = 20;

int dataPoints[100];
int dataIndex = 0;
int sampleCount = 0;

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Initialize data array
  for (int i = 0; i < GRAPH_WIDTH; i++) {
    dataPoints[i] = 0;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Data Viz System"));
  display.println(F("Initializing..."));
  display.display();

  delay(1000);
}

void drawGraph() {
  // Draw axes
  display.drawLine(GRAPH_X, GRAPH_Y, GRAPH_X, GRAPH_Y + GRAPH_HEIGHT, SSD1306_WHITE);
  display.drawLine(GRAPH_X, GRAPH_Y + GRAPH_HEIGHT, GRAPH_X + GRAPH_WIDTH, GRAPH_Y + GRAPH_HEIGHT, SSD1306_WHITE);

  // Draw data line
  for (int i = 1; i < GRAPH_WIDTH; i++) {
    int idx1 = (dataIndex + i - 1) % GRAPH_WIDTH;
    int idx2 = (dataIndex + i) % GRAPH_WIDTH;

    int y1 = map(dataPoints[idx1], 0, 100, GRAPH_HEIGHT, 0);
    int y2 = map(dataPoints[idx2], 0, 100, GRAPH_HEIGHT, 0);

    display.drawLine(
      GRAPH_X + i - 1, GRAPH_Y + y1,
      GRAPH_X + i, GRAPH_Y + y2,
      SSD1306_WHITE
    );
  }

  // Y-axis labels
  display.setCursor(0, GRAPH_Y);
  display.print(F("100"));
  display.setCursor(0, GRAPH_Y + GRAPH_HEIGHT - 6);
  display.print(F("0"));
}

void loop() {
  // Read and store sensor value
  int sensorValue = map(analogRead(SENSOR_PIN), 0, 1023, 0, 100);
  dataPoints[dataIndex] = sensorValue;
  dataIndex = (dataIndex + 1) % GRAPH_WIDTH;
  sampleCount++;

  // Update display
  display.clearDisplay();

  // Header
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println(F("=== SIGNAL MONITOR ==="));

  // Current value
  display.setCursor(0, 10);
  display.print(F("Value: "));
  display.print(sensorValue);
  display.print(F("%"));

  // Draw graph
  drawGraph();

  display.display();

  // Serial plotter output
  Serial.println(sensorValue);

  delay(100);
}
