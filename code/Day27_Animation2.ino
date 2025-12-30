/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 27: ANIMATION 2 - Particle system physics      ###
   ###   Advanced animation with interactive emitter        ###
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

const int CONTROL_PIN = A0;

/* ###########################################################
   ###   3. Particle System                                 ###
   ########################################################### */

const int MAX_PARTICLES = 30;

struct Particle {
  float x, y;
  float vx, vy;
  int life;
  bool active;
};

Particle particles[MAX_PARTICLES];

int emitterX = 64;
int emitterY = 50;

/* ###########################################################
   ###   4. Animation Timing                                ###
   ########################################################### */

unsigned long lastFrame = 0;
const int FRAME_DELAY = 33;

/* ###########################################################
   ###   5. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Initialize particles
  for (int i = 0; i < MAX_PARTICLES; i++) {
    particles[i].active = false;
  }
}

/* ###########################################################
   ###   6. Helper Functions                                ###
   ########################################################### */

void spawnParticle() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (!particles[i].active) {
      particles[i].x = emitterX;
      particles[i].y = emitterY;
      particles[i].vx = random(-20, 21) / 10.0;
      particles[i].vy = random(-40, -10) / 10.0;
      particles[i].life = random(20, 40);
      particles[i].active = true;
      break;
    }
  }
}

void updateParticles() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].active) {
      // Apply physics
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      particles[i].vy += 0.2;  // Gravity

      particles[i].life--;

      // Deactivate if off screen or dead
      if (particles[i].life <= 0 ||
          particles[i].x < 0 || particles[i].x > SCREEN_WIDTH ||
          particles[i].y < 0 || particles[i].y > SCREEN_HEIGHT) {
        particles[i].active = false;
      }
    }
  }
}

void drawParticles() {
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].active) {
      // Size based on life
      if (particles[i].life > 25) {
        display.fillCircle((int)particles[i].x, (int)particles[i].y, 2, SSD1306_WHITE);
      } else if (particles[i].life > 10) {
        display.fillCircle((int)particles[i].x, (int)particles[i].y, 1, SSD1306_WHITE);
      } else {
        display.drawPixel((int)particles[i].x, (int)particles[i].y, SSD1306_WHITE);
      }
    }
  }
}

int countActiveParticles() {
  int count = 0;
  for (int i = 0; i < MAX_PARTICLES; i++) {
    if (particles[i].active) count++;
  }
  return count;
}

/* ###########################################################
   ###   7. Main Loop                                       ###
   ########################################################### */

void loop() {
  if (millis() - lastFrame < FRAME_DELAY) {
    return;
  }
  lastFrame = millis();

  // Read control input for emitter X position
  emitterX = map(analogRead(CONTROL_PIN), 0, 1023, 10, SCREEN_WIDTH - 10);

  // Spawn new particles
  if (random(100) < 50) {  // 50% chance each frame
    spawnParticle();
  }

  // Update physics
  updateParticles();

  // Draw
  display.clearDisplay();

  // Title
  display.setCursor(20, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print(F("PARTICLE SYSTEM"));

  // Draw particles
  drawParticles();

  // Draw emitter
  display.fillTriangle(
    emitterX, emitterY,
    emitterX - 5, emitterY + 10,
    emitterX + 5, emitterY + 10,
    SSD1306_WHITE
  );

  // Stats
  display.setCursor(0, 56);
  display.print(F("Particles: "));
  display.print(countActiveParticles());

  display.display();
}

/* ###########################################################
   ###           END OF DAY 27 - ANIMATION 2                ###
   ########################################################### */
