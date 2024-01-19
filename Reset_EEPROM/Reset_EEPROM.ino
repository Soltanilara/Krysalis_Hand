#include <EEPROM.h>

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 17; i++) {
    EEPROM.write(i, 255);
  }

  Serial.write("Written");
}

void loop() {
  
}
