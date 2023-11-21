#include <EEPROM.h>

//Inputs
#define E1A 2
#define E1B 4
#define E2A 3
#define E2B 5
#define BUTTON 18

//Outputs
#define AIN1 9
#define AIN2 10
#define BIN1 6
#define BIN2 8

//Motor variables
#define PPR 7
#define gearRatio 10
#define SPEED 300
double rotations = 15.0 / 0.35;

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;

//Set the max and min number of pulses, which equates to number of rotations
long maxPulsesCW = (int) (rotations * PPR * gearRatio);
long maxPulsesCCW = 0;

enum state {
  ROTATECW = 0,
  ROTATECCW = 1,
};

bool toContinue = true;

state currentStateA = ROTATECW;
state currentStateB = ROTATECW;

void setup() {
  Serial.begin(9600);

  //Input setting
  pinMode(E1A, INPUT);
  pinMode(E1B, INPUT);
  pinMode(E2A, INPUT);
  pinMode(E2B, INPUT);
  pinMode(BUTTON, INPUT);
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  //attachInterrupt(digitalPinToInterrupt(BUTTON), exit, RISING);

  //Output setting
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);

  //First set all the pins to low
  analogWrite(AIN1, LOW);
  analogWrite(AIN2, LOW);
  analogWrite(BIN1, LOW);
  analogWrite(BIN1, LOW);
}

//Read the pulses of motor A
void readPulsesA() {
  int b = digitalRead(E1B);

  if (b > 0) {
    numPulsesA++;
  }
  else {
    numPulsesA--;
  }
}

//Read the pulses of motor B
void readPulsesB() {
  int b = digitalRead(E2B);

  if (b > 0) {
    numPulsesB++;
  }
  else {
    numPulsesB--;
  }
}

//Set the speed of motor A
void Set_PWMA(int pwm)
{
  if(pwm>0)
  {
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255 - pwm);
  }
  else
  {
    analogWrite(AIN1, 255 + pwm);
    analogWrite(AIN2, 255);
  }
}

//Set the speed of motor B
void Set_PWMB(int pwm)
{
  if(pwm>0)
  {
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255 - pwm);
  }
  else
  {
    analogWrite(AIN1, 255 + pwm);
    analogWrite(AIN2, 255);
  }
}

void loop() {
  if (toContinue) {
    //Check the rotation state of Motor A
    switch(currentStateA) {
      case ROTATECW:
        if (numPulsesA <= maxPulsesCW) {
          Set_PWMA(SPEED);
        }
        else {
          Set_PWMA(0);
          delay(1000);

          currentStateA = ROTATECCW;
        }
        break;
      case ROTATECCW:
        if (numPulsesA >= maxPulsesCCW) {
          Set_PWMA(-SPEED);
        }
        else {
          Set_PWMA(0);
          delay(1000);

          currentStateA = ROTATECW;
        }
        break;
    }

    //Check the rotation state of motorB
    switch(currentStateB) {
      case ROTATECW:
        if (numPulsesB <= maxPulsesCW) {
          Set_PWMB(SPEED);
        }
        else {
          Set_PWMB(0);
          delay(1000);

          currentStateB = ROTATECCW;
        }
        break;
      case ROTATECCW:
        if (numPulsesB >= maxPulsesCCW) {
          Set_PWMB(-SPEED);
        }
        else {
          Set_PWMB(0);
          delay(1000);

          currentStateB = ROTATECW;
        }
        break;
    }
  }
}
