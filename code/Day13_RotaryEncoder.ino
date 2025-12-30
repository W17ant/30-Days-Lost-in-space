/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 13: ROTARY ENCODER - Dial input control        ###
   ###   Learn encoder reading and rotation detection       ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Pin Definitions                                 ###
   ########################################################### */

const int ENCODER_CLK = 2;
const int ENCODER_DT = 3;
const int ENCODER_SW = 4;

/* ###########################################################
   ###   2. Global Variables                                ###
   ########################################################### */

volatile int encoderValue = 0;
int lastCLKState;

/* ###########################################################
   ###   3. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  lastCLKState = digitalRead(ENCODER_CLK);

  Serial.println("Rotary Encoder Ready");
  Serial.println("Turn the knob or press the button");
}

/* ###########################################################
   ###   4. Main Loop                                       ###
   ########################################################### */

void loop() {
  // Read current CLK state
  int currentCLKState = digitalRead(ENCODER_CLK);

  // Detect rotation
  if (currentCLKState != lastCLKState && currentCLKState == HIGH) {
    if (digitalRead(ENCODER_DT) != currentCLKState) {
      encoderValue++;
      Serial.print("Clockwise - Value: ");
    } else {
      encoderValue--;
      Serial.print("Counter-clockwise - Value: ");
    }
    Serial.println(encoderValue);
  }

  lastCLKState = currentCLKState;

  // Check button press
  if (digitalRead(ENCODER_SW) == LOW) {
    Serial.println("Button Pressed!");
    encoderValue = 0;
    Serial.println("Value Reset to 0");
    delay(200);  // Debounce
  }
}

/* ###########################################################
   ###           END OF DAY 13 - ROTARY ENCODER             ###
   ########################################################### */
