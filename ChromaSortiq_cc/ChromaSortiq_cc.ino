#include <Servo.h>
#include "Variables.h"

void setup() {
  Serial.begin(9600);
  Motors_Init();
  IR_Init();
  ColorSense_Init();

  myServo.attach(servoPin);
  myServo.write(80);
}

void loop() {
  if (Color_GetTargetMarking() == Color_Red) {
    Serial.println("The color is RED");
  }
}
