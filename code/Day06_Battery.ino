/* ###########################################################
   ###   30 DAYS LOST IN SPACE - INVENTR.IO                 ###
   ###   DAY 06: BATTERY - Power level monitoring           ###
   ###   Learn data types, logic, and charge accumulation   ###
   ###   Last Updated: 30-12-2024                           ###
   ########################################################### */

/* ###########################################################
   ###   1. Pin Definitions & Constants                     ###
   ########################################################### */

const byte PHOTORESISTOR_PIN = A0;
const unsigned long BATTERY_CAPACITY = 50000;

/* ###########################################################
   ###   2. Setup Function                                  ###
   ########################################################### */

void setup() {
  Serial.begin(9600);
  pinMode(PHOTORESISTOR_PIN, INPUT);
}

/* ###########################################################
   ###   3. Main Loop                                       ###
   ########################################################### */

void loop() {
  static unsigned long battery_level = 0;
  battery_level += analogRead(PHOTORESISTOR_PIN);

  // Cap at maximum capacity
  if (battery_level > BATTERY_CAPACITY) {
    battery_level = BATTERY_CAPACITY;
  }

  // Calculate and display percentage
  float percentage = ((float)battery_level / (float)BATTERY_CAPACITY) * 100;
  Serial.print("Battery: ");
  Serial.print(percentage);
  Serial.println("%");

  delay(100);
}

/* ###########################################################
   ###           END OF DAY 06 - BATTERY                    ###
   ########################################################### */
