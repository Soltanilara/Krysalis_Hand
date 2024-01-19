//Inputs
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24
#define E4A 19
#define E4B 25

//Outputs
#define AIN1 4
#define AIN2 5
#define BIN1 6
#define BIN2 7
#define CIN1 8
#define CIN2 9
#define DIN1 10
#define DIN2 11

//Motor variables
#define SPEED 100

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;
volatile int numPulsesD = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesIndexPinkie = 2400;
int maxPulsesMiddleRing = 1800;
int minPulses = 0;

//Have the respective motors finished their cycles yet?
bool aIncomplete = true;
bool bIncomplete = true;
bool cIncomplete = true;
bool dIncomplete = true;

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
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);
  attachInterrupt(digitalPinToInterrupt(E4A), readPulsesD, RISING);

  //Output setting
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(CIN1, OUTPUT);
  pinMode(CIN2, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);

  //First set all the pins to low
  analogWrite(AIN1, LOW);
  analogWrite(AIN2, LOW);
  analogWrite(BIN1, LOW);
  analogWrite(BIN2, LOW);
  analogWrite(CIN1, LOW);
  analogWrite(CIN2, LOW);
  analogWrite(DIN1, LOW);
  analogWrite(DIN2, LOW);
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
    analogWrite(BIN1, 255 - pwm);
    analogWrite(BIN2, 255);
  }
  else
  {
    analogWrite(BIN1, 255);
    analogWrite(BIN2, 255 + pwm);
  }
}

//Set the speed of motor C
void Set_PWMC(int pwm)
{
  if(pwm>0)
  {
    analogWrite(CIN1, 255 - pwm);
    analogWrite(CIN2, 255);
  }
  else
  {
    analogWrite(CIN1, 255);
    analogWrite(CIN2, 255 + pwm);
  }
}

//Set the speed of motor D
void Set_PWMD(int pwm)
{
  if(pwm>0)
  {
    analogWrite(DIN1, 255 - pwm);
    analogWrite(DIN2, 255);
  }
  else
  {
    analogWrite(DIN1, 255);
    analogWrite(DIN2, 255 + pwm);
  }
}

void loop() {
  while (aIncomplete || bIncomplete || cIncomplete || dIncomplete) {
    if (numPulsesA <= maxPulsesIndexPinkie) {
      Set_PWMA(SPEED);
    }
    else {
      Set_PWMA(0);
      aIncomplete = false;
    }

    if (numPulsesB <= maxPulsesMiddleRing) {
      Set_PWMB(SPEED);
    }
    else {
      Set_PWMB(0);
      bIncomplete = false;
    }

    if (numPulsesC <= maxPulsesMiddleRing) {
      Set_PWMC(SPEED);
    }
    else {
      Set_PWMC(0);
      cIncomplete = false;
    }

    if (numPulsesD <= maxPulsesIndexPinkie) {
      Set_PWMD(SPEED);
    }
    else {
      Set_PWMD(0);
      dIncomplete = false;
    }
    Serial.println(numPulsesC);
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;
  cIncomplete = true;
  dIncomplete = true;

  while (aIncomplete || bIncomplete || cIncomplete || dIncomplete) {
    if (numPulsesA >= minPulses) {
      Set_PWMA(-SPEED);
    }
    else {
      Set_PWMA(0);
      aIncomplete = false;
    }

    if (numPulsesB >= minPulses) {
      Set_PWMB(-SPEED);
    }
    else {
      Set_PWMB(0);
      bIncomplete = false;
    }

    if (numPulsesC >= minPulses) {
      Set_PWMC(-SPEED);
    }
    else {
      Set_PWMC(0);
      cIncomplete = false;
    }

    if (numPulsesD >= minPulses) {
      Set_PWMD(-SPEED);
    }
    else {
      Set_PWMD(0);
      dIncomplete = false;
    }
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;
  cIncomplete = true;
  dIncomplete = true;
}
