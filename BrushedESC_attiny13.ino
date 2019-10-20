/*
* Brushed ESC
* @author TheHLab
* @created Otc 18, 2019
* This code for ATtiny13 with Arduino IDE - MCUdude/MicroCore, 9.6Mhz
* Demo: https://youtu.be/hYDtW29BTBY
*/

#include <PinChangeInterrupt.h>

#define MIDDLE_POINT 1500
#define OUT1 0
#define OUT2 1
#define IN 2

volatile int pre_pwm_value = 0;
volatile int pwm_value = 0;
volatile int prev_time = 0;
 
void setup() {
  pinMode(OUT2, OUTPUT);
  pinMode(OUT1, OUTPUT);
  // when pin IN goes high, call the rising function
  attachPCINT(IN, rising,RISING);
}
 
void loop() {}
 
void rising() {
  attachPCINT(IN, falling,FALLING);
  prev_time = micros();
}
 
void falling() {
  attachPCINT(IN, rising,RISING);
  pre_pwm_value = pwm_value;
  pwm_value = micros()-prev_time;
  if( pwm_value < 1000 || pwm_value > 2000 ){
    pwm_value = pre_pwm_value;
  }
  PWM_out(pwm_value);
}

void PWM_out(int speeds){
  // speed
  int tempSpeeds = map(abs(speeds-MIDDLE_POINT), 0, 500, 0, 255);
  if(tempSpeeds>255) tempSpeeds = 255;
  // direction
  if( speeds > MIDDLE_POINT ){
    analogWrite(OUT1, tempSpeeds );
    digitalWrite(OUT2, LOW);
  } else {
    digitalWrite(OUT1, LOW);
    analogWrite(OUT2, tempSpeeds );
  }
}
