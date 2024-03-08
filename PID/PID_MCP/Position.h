#ifndef POSITION_H
#define POSITION_H
//Inputs
//A is MCP, B is IP, C is CMC
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24
#define E4A 19
#define E4B 25

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;
volatile int numPulsesD = 0;

//Targets for each motor
volatile int aTarget = 0;
volatile int bTarget = 0;
volatile int cTarget = 0;
volatile int dTarget = 0;

//PID constants
const int kp = 5;

//Position error
int aError = 0;
int bError = 0;
int cError = 0;
int dError = 0;

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

void setPosition() {
  //A's block
  aError = aTarget - numPulsesA;
  Set_PWMA(kp * aError);
  //End A's block

  //B's block
  bError = bTarget - numPulsesB;
  Set_PWMB(kp * bError);
  //End B's block
  
  //C's block
  cError = cTarget - numPulsesC;
  Set_PWMC(kp * cError);
  //End C's block
  
  //D's block
  dError = dTarget - numPulsesD;
  Set_PWMD(kp * dError);
  //End D's block
}

void setupPosition() {
  //Input setting
  pinMode(E1A, INPUT);
  pinMode(E1B, INPUT);
  pinMode(E2A, INPUT);
  pinMode(E2B, INPUT);
  pinMode(E3A, INPUT);
  pinMode(E3B, INPUT);
  pinMode(E4A, INPUT);
  pinMode(E4B, INPUT);
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);
  attachInterrupt(digitalPinToInterrupt(E4A), readPulsesD, RISING);
}
#endif