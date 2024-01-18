#ifndef RESET_H
#define RESET_H

#include <EEPROM.h>
//For memory writing purposes
union breakdown {
    int value;

    unsigned char valueArr[4];
};

void writeToMemory(int index, int value) {
  union breakdown toWrite;
  toWrite.value = value;

  for (int i = 0; i < 4; i++) {
    EEPROM.write(index + i, toWrite.valueArr[i]);
  }
}

bool unwritten(int start) {
  for (int i = 0; i < 4; i++) {
    if (EEPROM.read(start + i) != 255) {
      return false;
    }
  }

  return true;
}

int readMemory(int start) {
  if (unwritten(start)) {
    return 0;
  }

  union breakdown toWrite;

  for (int i = 0; i < 4; i++) {
    toWrite.valueArr[i] = EEPROM.read(start + i);
  }

  return toWrite.value;
}

#endif