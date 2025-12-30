/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 04: CABIN LIGHTS - Multiple LED control        ###
   ###   Learn multi-pin output with loops                  ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Pin Definitions                                 ###
   ########################################################### */

const int LED1 = 2;
const int LED2 = 3;
const int LED3 = 4;

/* ###########################################################
   ###   2. Setup Function                                  ###
   ########################################################### */

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

/* ###########################################################
   ###   3. Main Loop                                       ###
   ########################################################### */

void loop() {
  // All LEDs on
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  delay(500);

  // All LEDs off
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  delay(500);
}

/* ###########################################################
   ###           END OF DAY 04 - CABIN LIGHTS               ###
   ########################################################### */
