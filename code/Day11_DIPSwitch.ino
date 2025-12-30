/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 11: DIP SWITCH - Control panel inputs          ###
   ###   Learn digitalRead() with pull-up resistors         ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Pin Definitions                                 ###
   ########################################################### */

const int SWITCH1_PIN = 2;
const int SWITCH2_PIN = 3;
const int SWITCH3_PIN = 4;
const int SWITCH4_PIN = 5;

const int LED1_PIN = 9;
const int LED2_PIN = 10;
const int LED3_PIN = 11;
const int LED4_PIN = 12;

/* ###########################################################
   ###   2. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);

  // Set switch pins as inputs with pull-up resistors
  pinMode(SWITCH1_PIN, INPUT_PULLUP);
  pinMode(SWITCH2_PIN, INPUT_PULLUP);
  pinMode(SWITCH3_PIN, INPUT_PULLUP);
  pinMode(SWITCH4_PIN, INPUT_PULLUP);

  // Set LED pins as outputs
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
}

/* ###########################################################
   ###   3. Main Loop                                       ###
   ########################################################### */

void loop() {
  // Read switch states (LOW = ON due to pull-up)
  bool switch1 = digitalRead(SWITCH1_PIN) == LOW;
  bool switch2 = digitalRead(SWITCH2_PIN) == LOW;
  bool switch3 = digitalRead(SWITCH3_PIN) == LOW;
  bool switch4 = digitalRead(SWITCH4_PIN) == LOW;

  // Control LEDs based on switches
  digitalWrite(LED1_PIN, switch1);
  digitalWrite(LED2_PIN, switch2);
  digitalWrite(LED3_PIN, switch3);
  digitalWrite(LED4_PIN, switch4);

  // Print status
  Serial.print("Switches: ");
  Serial.print(switch1);
  Serial.print(switch2);
  Serial.print(switch3);
  Serial.println(switch4);

  delay(100);
}

/* ###########################################################
   ###           END OF DAY 11 - DIP SWITCH                 ###
   ########################################################### */
