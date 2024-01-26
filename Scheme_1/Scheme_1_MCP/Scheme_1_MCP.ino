#include "Motor.h"
#include "Signal.h"

//Inputs
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24
#define E4A 19
#define E4B 25

//Motor variables
#define SPEED 100

//State
enum state {
  CONTRACT,
  EXTEND,
  STOP,
};

volatile state currentState = CONTRACT;

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;
volatile int numPulsesD = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesIndexPinkie = 2400;
int maxPulsesMiddleRing = 1800;
int minPulses = 0;

//External inputs
#define CONTRACT_SELF 20
#define EXTEND_SELF 21

void setup() {
  Serial.begin(9600);

  //Input setting
  pinMode(E1A, INPUT);
  pinMode(E1B, INPUT);
  pinMode(E2A, INPUT);
  pinMode(E2B, INPUT);
  pinMode(E3A, INPUT);
  pinMode(E3B, INPUT);
  pinMode(E4A, INPUT);
  pinMode(E4B, INPUT);
  pinMode(CONTRACT_SELF, INPUT);
  pinMode(EXTEND_SELF, INPUT);
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);
  attachInterrupt(digitalPinToInterrupt(E4A), readPulsesD, RISING);
  attachInterrupt(digitalPinToInterrupt(CONTRACT_SELF), startContract, RISING);
  attachInterrupt(digitalPinToInterrupt(EXTEND_SELF), startExtend, RISING);

  setupMotors();
  setupSignal();
}

void startContract() {
  currentState = CONTRACT;
}

void startExtend() {
  currentState = EXTEND;
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

//Read the pulses of motor C
void readPulsesC() {
  int b = digitalRead(E3B);

  if (b > 0) {
    numPulsesC++;
  }
  else {
    numPulsesC--;
  }
}

//Read the pulses of motor D
void readPulsesD() {
  int b = digitalRead(E4B);

  if (b > 0) {
    numPulsesD++;
  }
  else {
    numPulsesD--;
  }
}

bool contract() {
  bool aComplete = false;
  bool bComplete = false;
  bool cComplete = false;
  bool dComplete = false;

  if (numPulsesA <= maxPulsesIndexPinkie) {
      Set_PWMA(SPEED);
    }
    else {
      Set_PWMA(0);
      aComplete = true;
    }

    if (numPulsesB <= maxPulsesMiddleRing) {
      Set_PWMB(SPEED);
    }
    else {
      Set_PWMB(0);
      bComplete = true;
    }

    if (numPulsesC <= maxPulsesMiddleRing) {
      Set_PWMC(SPEED);
    }
    else {
      Set_PWMC(0);
      cComplete = true;
    }

    if (numPulsesD <= maxPulsesIndexPinkie) {
      Set_PWMD(SPEED);
    }
    else {
      Set_PWMD(0);
      dComplete = true;
    }

    return aComplete && bComplete && cComplete && dComplete;
}

bool extend() {
  bool aComplete = false;
  bool bComplete = false;
  bool cComplete = false;
  bool dComplete = false;

  if (numPulsesA >= minPulses) {
      Set_PWMA(-SPEED);
    }
    else {
      Set_PWMA(0);
      aComplete = true;
    }

    if (numPulsesB >= minPulses) {
      Set_PWMB(-SPEED);
    }
    else {
      Set_PWMB(0);
      bComplete = true;
    }

    if (numPulsesC >= minPulses) {
      Set_PWMC(-SPEED);
    }
    else {
      Set_PWMC(0);
      cComplete = true;
    }

    if (numPulsesD >= minPulses) {
      Set_PWMD(-SPEED);
    }
    else {
      Set_PWMD(0);
      dComplete = true;
    }

    return aComplete && bComplete && cComplete && dComplete;
}

void loop() {
  switch (currentState) {
    case CONTRACT:
      if (contract()) {
        currentState = STOP;
        delay(1000);
        contractPIP();
      }

      break;
    case EXTEND:
      if (extend()) {
        currentState = STOP;
        delay(1000);
        extendPIP();
      }
      break;
    default:
      Set_PWMA(0);
      Set_PWMB(0);
      Set_PWMC(0);
      Set_PWMD(0);
      break;
  }
  Serial.println(currentState);
}
