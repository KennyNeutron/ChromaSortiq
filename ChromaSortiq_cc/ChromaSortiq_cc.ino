#include <Servo.h>
#include "Variables.h"

uint32_t last_micros = 0;

void setup() {
  Serial.begin(9600);
  Motors_Init();
  IR_Init();
  ColorSense_Init();

  myServo.attach(servoPin);
  myServo.write(80);

  Serial.println("Start");
}

void loop() {
  if (!Status_IR('L') && !Status_IR('R') && Status_IR('M')) {
    Motor_Forward();
  } else if (Status_IR('L') && !Status_IR('R') && !Status_IR('M')) {
    Motor_Left();
  } else if (!Status_IR('L') && Status_IR('R') && !Status_IR('M')) {
    Motor_Right();
  } else if (Status_IR('L') && Status_IR('R')) {
    Motor_Stop();
  }
}
