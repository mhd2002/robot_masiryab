#include <Wire.h>
//the rest of sensors
#define fire_detector A1
#define battery_feedback A0
#define green_detector1 A6
#define green_detector2 A7
// digital IOs
#define led A5
#define fan 12
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 11
#define pwm1 10
#define pwm2 9
//
#define pwm_max 255
#define pwm_left 120
#define pwm_right 120
#define pwm_forward 150
//start button
//#define sw A5
//colorSensoe
#define Addr 0x29
typedef struct {

  int blue;
  int green;
  int red;
  int ir;
} ColorSensor;
ColorSensor color;

//variale
bool start = 0;
int pwm = 255;


void setup() {

  configPins();
  Stop();

  Wire.begin();
  Serial.begin(9600);

  configColorSensor();
  Serial.println("ready");

}
void loop() {



  //  if (digitalRead(sw) == 0) {
  //    digitalWrite(led, 1);
  //    delay(100);
  //    digitalWrite(led, 0);
  //
  //  }

  //readColorData();

 // printSens();
  left(pwm_left);
  
    delay(2000);
      right(pwm_right);
delay(2000);
/*
    start = 1;
    while (start) {
    bool sen1 = digitalRead(A2);
    bool sen2 = digitalRead(5);
    bool sen3 = digitalRead(3);
    bool sen4 = digitalRead(4);
    bool sen5 = digitalRead(2);
    bool sen6 = digitalRead(13);


    if ((sen1) && (sen6) && (!sen2) && (!sen3) && (!sen4) && (!sen5)) {

      forward(pwm_forward);
    } else if ((sen1) && (!sen6) && (!sen2) && (!sen3) && (sen4) && (!sen5)) {
      forward(pwm_forward);
    } else if ((sen1) && (sen6) && (!sen2) && (!sen3) && (sen4) && (!sen5)) {
      right(pwm_right);

    } else if ((sen1) && (!sen6) && (sen2) && (!sen3) && (!sen4) && (!sen5)) {
      right(pwm_right);

    } else if ((!sen1) && (!sen6) && (sen2) && (!sen3) && (sen4) && (!sen5)) {
      right(pwm_right);

    } else if ((sen1) && (!sen6) && (!sen2) && (!sen3) && (sen4) && (!sen5)) {
      right(pwm_right);

    } else if ((!sen1) && (sen6) && (sen2) && (!sen3) && (sen4) && (!sen5)) {
      right(pwm_right);

    } else if ((!sen1) && (sen6) && (!sen2) && (!sen3) && (sen4) && (!sen5)) {
      right(pwm_right);

    } else if ((!sen1) && (!sen6) && (sen2) && (!sen3) && (!sen4) && (!sen5)) {
      right(pwm_right);
      /////////////////////////////////////////
    } else if ((sen1) && (!sen6) && (!sen2) && (sen3) && (!sen4) && (!sen5)) {
      left(pwm_left);

    } else if ((sen1) && (!sen6) && (!sen2) && (!sen3) && (!sen4) && (sen5)) {
      left(pwm_left);

    } else if ((!sen1) && (!sen6) && (!sen2) && (sen3) && (!sen4) && (sen5)) {
      left(pwm_left);

    } else if ((!sen1) && (sen6) && (!sen2) && (!sen3) && (!sen4) && (sen5)) {
      left(pwm_left);

    } else if ((!sen1) && (!sen6) && (!sen2) && (sen3) && (!sen4) && (!sen5)) {
      left(pwm_left);

    } else if ((!sen1) && (sen6) && (!sen2) && (sen3) && (!sen4) && (sen5)) {
      left(pwm_left);

    } else if ((sen1) && (sen6) && (!sen2) && (!sen3) && (!sen4) && (sen5)) {
      left(pwm_left);

    } else if ((sen1) && (sen6) && (sen2) && (sen3) && (sen4) && (sen5)) {
      Stop();

    }
    }
  */
}
void forward(char Speed) {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(pwm1, Speed);
  analogWrite(pwm2, Speed - 20);
}

void backward(char Speed) {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
  analogWrite(pwm1, Speed);
  analogWrite(pwm2, Speed);
}

void left(char Speed1) {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 1);
  analogWrite(pwm1, Speed1);
  analogWrite(pwm2, pwm_max);
}
void right(char Speed2) {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(pwm1, pwm_max);
  analogWrite(pwm2, Speed2);
}
void Stop(void) {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 0);
  analogWrite(pwm1, pwm_max);
  analogWrite(pwm2, pwm_max);
}

void configPins(void) {
  for (int i = 6; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(led, OUTPUT);
  for (int i = 2; i < 6; i++) {
    pinMode(i, INPUT);
  }
  pinMode(13, INPUT);
  pinMode(A2, INPUT);
  //pinMode(sw, INPUT_PULLUP);
}

void configColorSensor() {

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Wait Time register
  Wire.write(0x83);
  // Set wait time = 2.4 ms
  Wire.write(0xFF);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  Wire.write(0x81);
  // Select Atime register
  // Atime =2.4 ms, max count = 1024
  Wire.write(0xff);
  // Stop I2C Transmission on the device
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select control register
  Wire.write(0x8F);
  // AGAIN = 4x
  Wire.write(0x02);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select enable register
  Wire.write(0x80);
  // Power ON, RGBC enable, wait time disable
  Wire.write(0x03);
  // Stop I2C Transmission
  Wire.endTransmission();
}

void readColorData() {
  unsigned int data[8];

  // Start I2C Transmission on the device
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x94);
  // Stop I2C Transmission on the device
  Wire.endTransmission();

  // Request 8 byte of data from the device
  Wire.requestFrom(Addr, 8);

  // Read 8 bytes of data
  // cData lsb, cData msb, red lsb, red msb, green lsb, green msb, blue lsb, blue msb
  if (Wire.available() == 8)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
    data[6] = Wire.read();
    data[7] = Wire.read();
  }

  // Convert the data
  int cData = (data[1] * 256.0) + data[0];
  int red = (data[3] * 256.0) + data[2];
  int green = (data[5] * 256.0) + data[4];
  int blue = (data[7] * 256.0) + data[6];

  color.red = red;
  color.blue = blue;
  color.green = green;
  color.ir = cData;

}

void  printColorData(void) {

  Serial.println("-------------------------------------");
  Serial.print("Red color Luminance : ");
  Serial.println(color.red);
  Serial.print("Green color Luminance : ");
  Serial.println(color.green);
  Serial.print("Blue color Luminance : ");
  Serial.println(color.blue);
  Serial.print("IR : ");
  Serial.println(color.ir);

}

void printSens() {

  bool sen1 = digitalRead(13);
  bool sen2 = digitalRead(2);
  bool sen3 = digitalRead(5);
  bool sen4 = digitalRead(4);
  bool sen5 = digitalRead(3);
  bool sen6 = digitalRead(A2);

  Serial.println("-------------------------------------");
  Serial.print("sen1 : ");
  Serial.println(sen1);
  Serial.print("sen2 : ");
  Serial.println(sen2);
  Serial.print("sen3 : ");
  Serial.println(sen3);
  Serial.print("sen4 : ");
  Serial.println(sen4);
  Serial.print("sen5 : ");
  Serial.println(sen5);
  Serial.print("sen6 : ");
  Serial.println(sen6);
  delay(333);
}
