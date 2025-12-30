/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 02: BLINK - Your first LED circuit             ###
   ###   Learn digital output with pinMode/digitalWrite     ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Setup Function                                  ###
   ########################################################### */

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

/* ###########################################################
   ###   2. Main Loop                                       ###
   ########################################################### */

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // LED on
  delay(1000);                      // Wait 1 second
  digitalWrite(LED_BUILTIN, LOW);   // LED off
  delay(1000);                      // Wait 1 second
}

/* ###########################################################
   ###           END OF DAY 02 - BLINK                      ###
   ########################################################### */
