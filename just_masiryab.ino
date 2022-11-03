#define fan 12
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 11
#define pwm1 10
#define pwm2 9
//
#define pwm_max 255
#define pwm_left 100
#define pwm_right 100
#define pwm_forward 120

void setup() {
  
  configPins();
    Stop();

}

void loop() {

  
 while (1) {
    bool sen1 = digitalRead(13);
    bool sen2 = digitalRead(2);
    bool sen3 = digitalRead(5);
    bool sen4 = digitalRead(4);
    bool sen5 = digitalRead(3);
    bool sen6 = digitalRead(A2);

    if ((sen1) && (sen6) && (!sen2) && (!sen3) && (!sen4) && (!sen5)) {

      forward(pwm_forward);

    } else if ((sen1) && (!sen6) && (!sen2) && (!sen3) && (!sen4) && (!sen5)) {

      forward(pwm_forward);

    } else if ((!sen1) && (sen6) && (!sen2) && (sen3) && (!sen4) && (!sen5)) {

      left(pwm_left);

    } else if ((!sen1) && (sen6) && (!sen2) && (sen3) && (!sen4) && (sen5)) {

      left(pwm_left);

    } else if ((!sen1) && (!sen6) && (!sen2) && (sen3) && (!sen4) && (sen5)) {

      left(pwm_left);

    } else if ((!sen1) && (sen6) && (!sen2) && (!sen3) && (!sen4) && (sen5)) {

      left(pwm_left);

    } else if ((!sen1) && (!sen6) && (!sen2) && (sen3) && (!sen4) && (!sen5)) {

      left(pwm_left);
      //////////////////////////////////////////////////////
    } else if ((!sen1) && (sen6) && (sen2) && (!sen3) && (!sen4) && (!sen5)) {
      right(pwm_right);

    } else if ((!sen1) && (sen6) && (sen2) && (!sen3) && (sen4) && (!sen5)) {

      right(pwm_right);

    } else if ((!sen1) && (!sen6) && (sen2) && (!sen3) && (sen4) && (!sen5)) {

      right(pwm_right);

    } else if ((!sen1) && (sen6) && (!sen2) && (!sen3) && (sen4) && (!sen5)) {

      right(pwm_right);

    } else if ((!sen1) && (!sen6) && (sen2) && (!sen3) && (!sen4) && (!sen5)) {

      right(pwm_right);

    } else if  ((sen1) && (sen6) && (sen2) && (sen3) && (sen4) && (sen5)) {

      Stop();

    }
  }
}

void forward(unsigned char Speed) {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(pwm1, Speed);
  analogWrite(pwm2, Speed - 20);
}

void left(unsigned char Speed) {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 1);
  analogWrite(pwm1, Speed);
  analogWrite(pwm2, pwm_max);
}
void right(unsigned char Speed) {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
  analogWrite(pwm1, pwm_max);
  analogWrite(pwm2, Speed);
}
void Stop(void) {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 1);
  analogWrite(pwm1, pwm_max);
  analogWrite(pwm2, pwm_max);
}

void configPins(void) {
  for (int i = 6; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  //pinMode(led, OUTPUT);
  for (int i = 2; i < 6; i++) {
    pinMode(i, INPUT);
  }
  pinMode(13, INPUT);
  pinMode(A2, INPUT);
  //pinMode(sw, INPUT_PULLUP);
}
