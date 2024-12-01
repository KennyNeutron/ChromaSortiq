#include <Servo.h>
#include "Variables.h"
#include <EEPROM.h>


uint32_t last_micros = 0;

// bool flag_Mid = false;
// bool flag_Right = false;
// bool flag_Left = false;

bool hasTurned = false;
bool hasForwarded = false;
bool markerReached = false;
bool packageDropped = false;

uint32_t isr_count = 0;

bool start_operation = false;

uint8_t marker_Station = 0;
uint16_t delay_forward = 1000;


void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  Serial.println("EEPROM[1]:" + String(EEPROM.read(1)));
  //EEPROM.write(1,129);
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
  Motors_Init();

  IR_Init();

  ColorSense_Init();

  myServo.attach(servoPin);
  myServo.write(130);
  delay(1000);
  Servo_DropPackage();
  delay(100);
  interrupt_setup();

  start_operation = true;
}

void loop() {

  if (IR_getScore() >= 3 && !markerReached) {
    markerReached = true;
    Motor_Stop();
    marker_Station++;
    if (marker_Station > 4) {
      marker_Station = 1;
    }
    EEPROM.write(1, marker_Station);
    delay(3000);
  }


  if (marker_Station == 1 && markerReached) {
st_station1:
    while (Color_GetTargetMarking() == Color_None) {
      delay(3000);
    }
    delay(3000);
    if (Color_GetTargetMarking() == Color_None) {
      goto st_station1;
    }
    packageDropped = false;
    continue_forward();
  } else if (marker_Station == 2 && markerReached) {
    if (Color_GetTargetMarking() == Color_Red && !packageDropped) {
      Servo_DropPackage();
      continue_forward();
    } else {
      continue_forward();
    }
  } else if (marker_Station == 3 && markerReached) {
    if (Color_GetTargetMarking() == Color_Green && !packageDropped) {
      Servo_DropPackage();
      continue_forward();
    } else {
      continue_forward();
    }
  } else if (marker_Station == 4 && markerReached) {
    if (Color_GetTargetMarking() == Color_Blue && !packageDropped) {
      Servo_DropPackage();
      continue_forward();
    } else {
      continue_forward();
    }
  }
}

void continue_forward() {
  digitalWrite(enA, 1);  //TRight
  delay(90);
  Motor_Forward();
  delay(delay_forward);
  while (IR_getScore() >= 3) {
    Motor_Forward();
  }
  markerReached = false;
  start_operation = true;
  hasForwarded = true;
}