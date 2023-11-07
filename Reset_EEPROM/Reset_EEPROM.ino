#include <EEPROM.h>

void setup() {
  Serial.begin(9600);
}

bool cont = true;

void loop() {
  if (cont) {
    EEPROM.write(0, 0);
    EEPROM.write(1, 0);
    EEPROM.write(2, 0);

    cont = false;
    Serial.println("Written");
  }
}
