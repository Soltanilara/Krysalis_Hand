//Inputs
#define E1A 2
#define E1B 22
#define E2A 3
#define E2B 23
#define E3A 18
#define E3B 24
#define E4A 19
#define E4B 25
#define E5A 20
#define E5B 26
#define E6A 21
#define E6B 27

//Outputs
#define AIN1 4
#define AIN2 5
#define BIN1 6
#define BIN2 7
#define CIN1 8
#define CIN2 9
#define DIN1 10
#define DIN2 11
#define EIN1 12
#define EIN2 13
#define FIN1 44
#define FIN2 45

//Motor variables
#define SPEED 255

//Track the number of pulses from each motor
volatile int numPulsesA = 0;
volatile int numPulsesB = 0;
volatile int numPulsesC = 0;
volatile int numPulsesD = 0;
volatile int numPulsesE = 0;
volatile int numPulsesF = 0;

//Set the max and min number of pulses, which equates to number of rotations
int maxPulsesCW = 850;
int maxPulsesCCW = 0;

//Have the respective motors finished their cycles yet?
bool aIncomplete = true;
bool bIncomplete = true;
bool cIncomplete = true;
bool dIncomplete = true;
bool eIncomplete = true;
bool fIncomplete = true;

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
  pinMode(E5A, INPUT);
  pinMode(E5B, INPUT);
  pinMode(E6A, INPUT);
  pinMode(E6B, INPUT);
  attachInterrupt(digitalPinToInterrupt(E1A), readPulsesA, RISING);
  attachInterrupt(digitalPinToInterrupt(E2A), readPulsesB, RISING);
  attachInterrupt(digitalPinToInterrupt(E3A), readPulsesC, RISING);
  attachInterrupt(digitalPinToInterrupt(E4A), readPulsesD, RISING);
  attachInterrupt(digitalPinToInterrupt(E5A), readPulsesE, RISING);
  attachInterrupt(digitalPinToInterrupt(E6A), readPulsesF, RISING);
  //attachInterrupt(digitalPinToInterrupt(BUTTON), exit, RISING);

  //Output setting
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(CIN1, OUTPUT);
  pinMode(CIN2, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DIN2, OUTPUT);
  pinMode(EIN1, OUTPUT);
  pinMode(EIN2, OUTPUT);
  pinMode(FIN1, OUTPUT);
  pinMode(FIN2, OUTPUT);

  //First set all the pins to low
  analogWrite(AIN1, LOW);
  analogWrite(AIN2, LOW);
  analogWrite(BIN1, LOW);
  analogWrite(BIN2, LOW);
  analogWrite(CIN1, LOW);
  analogWrite(CIN2, LOW);
  analogWrite(DIN1, LOW);
  analogWrite(DIN2, LOW);
  analogWrite(EIN1, LOW);
  analogWrite(EIN2, LOW);
  analogWrite(FIN1, LOW);
  analogWrite(FIN2, LOW);
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

//Read the pulses of motor D
void readPulsesD() {
  int b = digitalRead(E4B);

  if (b > 0) {
    numPulsesD--;
  }
  else {
    numPulsesD++;
  }
}

//Read the pulses of motor E
void readPulsesE() {
  int b = digitalRead(E5B);

  if (b > 0) {
    numPulsesE--;
  }
  else {
    numPulsesE++;
  }
}

//Read the pulses of motor F
void readPulsesF() {
  int b = digitalRead(E6B);

  if (b > 0) {
    numPulsesF--;
  }
  else {
    numPulsesF++;
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

//Set the speed of motor D
void Set_PWMD(int pwm)
{
  if(pwm>0)
  {
    analogWrite(DIN1, 255);
    analogWrite(DIN2, 255 - pwm);
  }
  else
  {
    analogWrite(DIN1, 255 + pwm);
    analogWrite(DIN2, 255);
  }
}

//Set the speed of motor E
void Set_PWME(int pwm)
{
  if(pwm>0)
  {
    analogWrite(EIN1, 255);
    analogWrite(EIN2, 255 - pwm);
  }
  else
  {
    analogWrite(EIN1, 255 + pwm);
    analogWrite(EIN2, 255);
  }
}

//Set the speed of motor F
void Set_PWMF(int pwm)
{
  if(pwm>0)
  {
    analogWrite(FIN1, 255);
    analogWrite(FIN2, 255 - pwm);
  }
  else
  {
    analogWrite(FIN1, 255 + pwm);
    analogWrite(FIN2, 255);
  }
}

void loop() {
  while (aIncomplete || bIncomplete || cIncomplete || dIncomplete || eIncomplete || fIncomplete) {
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

    if (numPulsesC <= maxPulsesCW) {
      Set_PWMC(SPEED);
    }
    else {
      Set_PWMC(0);
      cIncomplete = false;
    }

    if (numPulsesD <= maxPulsesCW) {
      Set_PWMD(SPEED);
    }
    else {
      Set_PWMD(0);
      dIncomplete = false;
    }

    if (numPulsesE <= maxPulsesCW) {
      Set_PWME(SPEED);
    }
    else {
      Set_PWME(0);
      eIncomplete = false;
    }

    if (numPulsesF <= maxPulsesCW) {
      Set_PWMF(SPEED);
    }
    else {
      Set_PWMF(0);
      fIncomplete = false;
    }
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;
  cIncomplete = true;
  dIncomplete = true;
  eIncomplete = true;
  fIncomplete = true;

  while (aIncomplete || bIncomplete || cIncomplete || dIncomplete || eIncomplete || fIncomplete) {
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

    if (numPulsesD >= maxPulsesCCW) {
      Set_PWMD(-SPEED);
    }
    else {
      Set_PWMD(0);
      dIncomplete = false;
    }

    if (numPulsesE >= maxPulsesCCW) {
      Set_PWME(-SPEED);
    }
    else {
      Set_PWME(0);
      eIncomplete = false;
    }

    if (numPulsesF >= maxPulsesCCW) {
      Set_PWMF(-SPEED);
    }
    else {
      Set_PWMF(0);
      fIncomplete = false;
    }
  }

  delay(1000);
  aIncomplete = true;
  bIncomplete = true;
  cIncomplete = true;
  dIncomplete = true;
  eIncomplete = true;
  fIncomplete = true;
}
