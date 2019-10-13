/*
* Brushed ESC
* @author TheHLab
* @created Otc 10, 2019
* This code for ATtiny85 with Arduino IDE, 8Mhz
*/

#define MIDDLE_POINT 1500
#define OUT1 0
#define OUT2 1
#define IN 0

volatile int pwm_value = 0;
volatile int prev_time = 0;
 
void setup() {
  // when pin IN goes high, call the rising function
  attachInterrupt(IN, rising, RISING);
}
 
void loop() { }
 
void rising() {
  attachInterrupt(IN, falling, FALLING);
  prev_time = micros();
}
 
void falling() {
  attachInterrupt(IN, rising, RISING);
  pwm_value = micros()-prev_time;
  PWM_out(pwm_value);
}

void PWM_out(int speeds){
  // speed
  int tempSpeeds = map(abs(speeds-MIDDLE_POINT), 0, 500, 0, 255);
  // direction
  if( speeds > MIDDLE_POINT ){
    analogWrite(OUT1, tempSpeeds );
    pinMode(OUT2, OUTPUT);
    digitalWrite(OUT2, LOW);
  } else {
    pinMode(OUT1, OUTPUT);
    digitalWrite(OUT1, LOW);
    analogWrite(OUT2, tempSpeeds );
  }
}
