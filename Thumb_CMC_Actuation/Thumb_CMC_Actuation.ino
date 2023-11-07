#include <util/atomic.h>
#include <EEPROM.h>

//Inputs
//#define BUTTON 2
#define ENCA 2
#define ENCB 4
#define BUTTON 3

//Outputs
#define IN2 9
#define IN1 10

#define PPR 11
#define gearRatio 18.5
#define SPEED 80

double rotations = 0.115;

volatile int numRotations = 0;
long maxRotationsCW = (int) (rotations * PPR * gearRatio);
long maxRotationsCCW = -maxRotationsCW;

enum state {
  ROTATECW = 0,
  ROTATECCW = 1,
};

bool toContinue = true;
bool reset = false;

volatile state currentState = ROTATECCW;

void setup() {
  Serial.begin(9600);

  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA), readRotations, RISING);
  attachInterrupt(digitalPinToInterrupt(BUTTON), exit, RISING);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  analogWrite(IN1, LOW);
  analogWrite(IN2, LOW);

  if (!reset) {
    uint8_t bit1 = EEPROM.read(0);
    uint8_t bit2 = EEPROM.read(1);
    uint8_t dir = EEPROM.read(2);

    //If the both bits are 255, then we know that the the arduino has never spun before
    if (bit1 != 255 || bit2 != 255) {
      numRotations = (int16_t) (bit1 << 8 | bit2);
    }

    if (dir != 255) {
      currentState = dir;
    }
  }

  Serial.print("Reading: ");
  Serial.println((double) numRotations / (PPR * gearRatio));
}

void exit() {
  Set_PWMA(0);
  toContinue = false;

  uint8_t bit1 = (numRotations >> 8) & 0xFF;
  uint8_t bit2 = numRotations & 0xFF;

  EEPROM.write(0, bit1);
  EEPROM.write(1, bit2);
  EEPROM.write(2, currentState);

  Serial.print("Writing: ");
  Serial.println((double) numRotations / (PPR * gearRatio));
}

void readRotations() {
  int b = digitalRead(ENCB);

  if (b > 0) {
    numRotations++;
  }
  else {
    numRotations--;
  }
}

void Set_PWMA(int pwm)
{
  if(pwm>0)
  {
    analogWrite(IN1, 255 - pwm);
    analogWrite(IN2, 255);
  }
  else
  {
    analogWrite(IN2, 255 + pwm);
    analogWrite(IN1, 255);
  }
}

void loop() {
  if (toContinue) {
    switch(currentState) {
      case ROTATECW:
        if (numRotations <= maxRotationsCW) {
          Set_PWMA(SPEED);
        }
        else {
          Set_PWMA(0);
          delay(1000);

          currentState = ROTATECCW;
        }
        break;
      case ROTATECCW:
        if (numRotations >= maxRotationsCCW) {
          Set_PWMA(-SPEED);
        }
        else {
          Set_PWMA(0);
          delay(1000);

          currentState = ROTATECW;
        }
        break;
    }
  }

  Serial.println((double) numRotations / (PPR * gearRatio));
}
