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
#define BIN1 7
#define BIN2 8

//Motor variables
#define SPEED 255

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesCW = 1000;
int maxPulsesCCW = 0;

bool toContinue = true;

//Have the respective motors finished their cycles yet?
bool aIncomplete = true;
bool bIncomplete = true;

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
  pinMode(BIN2, OUTPUT);

  //First set all the pins to low
  analogWrite(AIN1, LOW);
  analogWrite(AIN2, LOW);
  analogWrite(BIN1, LOW);
  analogWrite(BIN2, LOW);
}

//Read the pulses of motor A
void readPulsesA() {
  int b = digitalRead(E1B);

  if (b > 0) {
    numPulsesA--;
  }
  else {
    numPulsesA++;
  }
}

//Read the pulses of motor B
void readPulsesB() {
  int b = digitalRead(E2B);

  if (b > 0) {
    numPulsesB--;
  }
  else {
    numPulsesB++;
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
    analogWrite(BIN1, 255);
    analogWrite(BIN2, 255 - pwm);
  }
  else
  {
    analogWrite(BIN1, 255 + pwm);
    analogWrite(BIN2, 255);
  }
}

void loop() {
  while (aIncomplete || bIncomplete) {
    if (numPulsesA <= maxPulsesCW) {
      Set_PWMA(SPEED);
    }
    else {
      Set_PWMA(0);
      aIncomplete = false;
    }

    if (numPulsesB <= maxPulsesCW) {
      Set_PWMB(SPEED);
    }
    else {
      Set_PWMB(0);
      bIncomplete = false;
    }
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;

  while (aIncomplete || bIncomplete) {
    if (numPulsesA >= maxPulsesCCW) {
      Set_PWMA(-SPEED);
    }
    else {
      Set_PWMA(0);
      aIncomplete = false;
    }

    if (numPulsesB >= maxPulsesCCW) {
      Set_PWMB(-SPEED);
    }
    else {
      Set_PWMB(0);
      bIncomplete = false;
    }
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;
}
