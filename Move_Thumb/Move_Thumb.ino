//A is CMC joint, B and C are joints

//Inputs
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24

//Outputs
#define AIN1 4
#define AIN2 5
#define BIN1 6
#define BIN2 7
#define CIN1 8
#define CIN2 9

//Motor variables
#define SPEED 255

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesCWCMC = 25;
int maxPulsesCWJoints = 850;
int maxPulsesCCW = 0;

//Have the respective motors finished their cycles yet?
bool aIncomplete = true;
bool bIncomplete = true;
bool cIncomplete = true;

void setup() {
  Serial.begin(9600);

  //Input setting
  pinMode(E1A, INPUT);
  pinMode(E1B, INPUT);
  pinMode(E2A, INPUT);
  pinMode(E2B, INPUT);
  pinMode(E3A, INPUT);
  pinMode(E3B, INPUT);
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);
  //attachInterrupt(digitalPinToInterrupt(BUTTON), exit, RISING);

  //Output setting
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(CIN1, OUTPUT);
  pinMode(CIN2, OUTPUT);

  //First set all the pins to low
  analogWrite(AIN1, LOW);
  analogWrite(AIN2, LOW);
  analogWrite(BIN1, LOW);
  analogWrite(BIN2, LOW);
  analogWrite(CIN1, LOW);
  analogWrite(CIN2, LOW);
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

//Read the pulses of motor C
void readPulsesC() {
  int b = digitalRead(E3B);

  if (b > 0) {
    numPulsesC--;
  }
  else {
    numPulsesC++;
  }
}

//Set the speed of motor A
void Set_PWMA(int pwm)
{
  if(pwm>0)
  {
    analogWrite(AIN1, 255 - pwm);
    analogWrite(AIN2, 255);
  }
  else
  {
    analogWrite(AIN1, 255);
    analogWrite(AIN2, 255 + pwm);
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

//Set the speed of motor C
void Set_PWMC(int pwm)
{
  if(pwm>0)
  {
    analogWrite(CIN1, 255);
    analogWrite(CIN2, 255 - pwm);
  }
  else
  {
    analogWrite(CIN1, 255 + pwm);
    analogWrite(CIN2, 255);
  }
}

void loop() {
  while (aIncomplete || bIncomplete || cIncomplete) {
    if (numPulsesA <= maxPulsesCWCMC) {
      Set_PWMA(SPEED);
    }
    else {
      Set_PWMA(0);
      aIncomplete = false;
    }

    if (numPulsesB <= maxPulsesCWJoints) {
      Set_PWMB(SPEED);
    }
    else {
      Set_PWMB(0);
      bIncomplete = false;
    }

    if (numPulsesC <= maxPulsesCWJoints) {
      Set_PWMC(SPEED);
    }
    else {
      Set_PWMC(0);
      cIncomplete = false;
    }
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;
  cIncomplete = true;

  while (aIncomplete || bIncomplete || cIncomplete) {
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

    if (numPulsesC >= maxPulsesCCW) {
      Set_PWMC(-SPEED);
    }
    else {
      Set_PWMC(0);
      cIncomplete = false;
    }
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;
  cIncomplete = true;
}
