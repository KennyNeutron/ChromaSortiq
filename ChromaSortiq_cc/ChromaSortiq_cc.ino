#include <Servo.h>
#include "Variables.h"

uint32_t last_micros = 0;

// bool flag_Mid = false;
// bool flag_Right = false;
// bool flag_Left = false;

bool hasTurned=false;
bool hasForwarded = false;
bool makerreached = false;

uint32_t isr_count=0;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  Motors_Init();
  IR_Init();
  ColorSense_Init();

  myServo.attach(servoPin);
  myServo.write(80);
  delay(1000);

  Motor_Forward();
  //interrupt_setup();
}

void loop() {

}
