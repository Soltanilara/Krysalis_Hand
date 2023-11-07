#include <util/atomic.h>  // For the ATOMIC_BLOCK macro

//Time depending Encoder Control for fingers

/////////////////////////// Wiring method of this routine///////////////////////////
//  ArduinoUNOpin ------ AT8236module
//        Pin5        ---        BIN1
//        Pin6        ---        BIN2
//        Pin9        ---        AIN1
//        Pin10       ---        AIN2
//        PinA5       ---        ADC
//        Pin8        ---        E1A
//        Pin4        ---        E1B
//        Pin3        ---        E2A
//        Pin2        ---        E2B
//         GND        ---        GND

/////////PWM Output pin////////
//#define BIN1 5
//#define BIN2 6
#define AIN1 9
#define AIN2 10
#define BIN1 5
#define BIN2 6
#define Voltage A5 //Analog pin reading power supply voltage

/////////Encoder pin////////
#define ENCODER_L 8  //Encoder acquisition pins: 2 for each channel, 4 in total
#define DIRECTION_L 4
//#define ENCODER_R 20
//#define DIRECTION_R 21

double V; //Store voltage variable
unsigned long TimeA=0;
unsigned long EncoderTime=0;
bool EncoderFlag=1;
bool Mode=0;

volatile long Velocity_L, Velocity_R;   //Left and right wheel encoder data
float Velocity_Left, Velocity_Right = 0;   //Left and right wheel speed
int delayShow=0;
unsigned long TimeB=0;
bool MotorFlag=1;
bool TimeFlag=1;

volatile int posi = 0; // specifying posi as volatile.

//The default PWM value can be set directly through the serial port for different speeds
int putPWM =30;

// Counter variables for revolutions
int revolutions = 0;
bool forwardDirection = true;

void setup() {
  Serial.begin(9600);
  
  //Encoder pin
  pinMode(ENCODER_L, INPUT);  
  pinMode(DIRECTION_L, INPUT);
  //pinMode(ENCODER_R, INPUT);
  //pinMode(DIRECTION_R, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER_L), READ_ENCODER_L, CHANGE); //Enable external interrupt encoder interface 2
  //attachInterrupt(digitalPinToInterrupt(ENCODER_R), READ_ENCODER_R, CHANGE); //Enable external interrupt encoder interface 1

  //PWMpin
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  //pinMode(BIN1, OUTPUT);
  //pinMode(BIN2, OUTPUT);

  //Analog input pin
  pinMode(Voltage,INPUT); //Initialize as input

}

//Set the PWM value of motor A, the range is - 255~255, where 0~255 corresponds to the duty ratio of 0~100, and a negative number means the motor is reversed
void Set_PWMA(int dir, int pwmVal) {
  analogWrite(AIN1, pwmVal);
  if(dir == 1)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else if (dir == -1)
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  else
  {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
}

/*****Function function: external interrupt reads encoder data and has double frequency function. Note that external interrupt is triggered by jump edge********/
void READ_ENCODER_L() {
  int b = digitalRead(DIRECTION_L);
  if(b > 0)
  {
    posi++;
  }

  else
  {
    posi--;
  }
}

void loop() {
  int pos = 0;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
  {
    pos = posi;
  }

  for (int i = 0; i < 3; i++) {
    Set_PWMA(1,100);
    //Set_PWMB(1,100);
    delay(200);
    Set_PWMA(0, 5);
    delay(100);
  }

  Set_PWMA(0,100);
  //Set_PWMB(0,100);
  delay(1000);

  /*
  for (int i = 0; i < 3; i++) {
    Set_PWMA(-1,100);
    //Set_PWMB(1,100);
    delay(200);
    Set_PWMA(0, 5);
    delay(100);
  }

  Set_PWMA(0,100);
  //Set_PWMB(0,100);
  delay(1000);
  Serial.println(pos);*/
  


    Velocity_Left = (Velocity_Left / 450) * 100 * 60;  // Calculate left wheel speed in RPM
    Velocity_Right = (Velocity_Right / 450) * 100 * 60;  // Calculate right wheel speed in RPM

    delayShow++;
    

    // Display data once in 50ms
    if (delayShow == 50) {
      delayShow = 0;
      Serial.print("Velocity_L = ");
      Serial.print(Velocity_Left);
      Serial.println(" R/M");

      Serial.print("Velocity_R = ");
      Serial.print(Velocity_Right);
      Serial.println(" R/M");

      V = analogRead(Voltage); // Read analog quantity of analog pin A0
      Serial.print("Input voltage = ");
      Serial.print(V * 0.05371);  // Convert analog quantity and output through serial port
      Serial.println("V");

      Serial.print("PWM = ");
      Serial.println(putPWM);

      Serial.println("");
      Serial.println("");
    }

    // Increment the revolution counter
    revolutions++;
  }