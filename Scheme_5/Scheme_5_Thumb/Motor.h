//Outputs
#define AIN1 8
#define AIN2 9
#define BIN1 4
#define BIN2 5
#define CIN1 6
#define CIN2 7

void setupMotors() {
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