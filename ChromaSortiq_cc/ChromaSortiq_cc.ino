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
uint16_t delay_forward = 300;


void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  Serial.println("EEPROM[1]:" + String(EEPROM.read(1)));
  pinMode(13, OUTPUT);
  Motors_Init();

  IR_Init();

  ColorSense_Init();

  myServo.attach(servoPin);
  myServo.write(130);
  delay(1000);
  Servo_Shake();
  delay(500);
  Servo_DropPackage();
  delay(100);

  //++++ TEST HERE ++++
  // while (1) {
  //   IR_test();
  // }
  //++++++++++++++++++++

  interrupt_setup();
  start_operation = true;
}

void loop() {

  if (IR_getScore() >= 3 && IR_Status('K') && !markerReached) {
    Motor_Stop();
    markerReached = true;
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
  markerReached = true;
  Motor_Forward();
  delay(delay_forward);
  //FIND CENTER HERE
  robot_FindCenter();
  markerReached = false;
  start_operation = true;
  hasForwarded = true;
}

void robot_FindCenter() {
  if (IR_Status('M')) {
    goto rFC_exit;
  }
rFC_start:
  uint32_t lp_count = 0;    //count
  uint32_t lpc_limit = 90;  //limit
  uint32_t lpc_inc = 10;    //increment
  while (!IR_Status('M')) {
    while (!IR_Status('M') && lp_count < lpc_limit) {
      digitalWrite(enA, 1);
      digitalWrite(enB, 0);
      delay(10);
      lp_count++;
    }
    digitalWrite(enA, 0);
    digitalWrite(enB, 0);
    delay(100);
    lp_count = 0;
    while (!IR_Status('M') && lp_count < lpc_limit) {
      digitalWrite(enA, 0);
      digitalWrite(enB, 1);
      delay(10);
      lp_count++;
    }
    digitalWrite(enA, 0);
    digitalWrite(enB, 0);
    delay(100);
    lp_count = 0;
    lpc_limit += lpc_inc;
  }

  if (!IR_Status('L') && !IR_Status('R') && IR_Status('M')) {
    goto rFC_exit;
  } else {
    goto rFC_start;
  }

rFC_exit:
  delay(1);
}