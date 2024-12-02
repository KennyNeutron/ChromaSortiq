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
uint16_t delay_forward = 100;


void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  Serial.println("EEPROM[1]:" + String(EEPROM.read(1)));
  pinMode(13, OUTPUT);
  Motors_Init();

  IR_Init();

  ColorSense_Init();

  //++++ TEST HERE ++++
  // myServo.attach(servoPin);
  // Servo_DropPackage();
  // interrupt_setup();
  // while (1) {
  //   ColorISR();
  //   testColor2();
  // }
  //++++++++++++++++++++
  delay(3000);

  myServo.attach(servoPin);
  delay(1000);
  Servo_Shake();
  delay(500);
  Servo_DropPackage();
  delay(100);


  int_en = true;
  interrupt_setup();
  start_operation = true;
}

void loop() {
  if (IR_getScore() == 4 && !markerReached) {
    Motor_Stop();
    int_en = false;
    markerReached = true;
    marker_Station++;
    if (marker_Station > 4) {
      marker_Station = 1;
    }
    EEPROM.write(1, marker_Station);
    delay(3000);
    if (Color_GetTargetMarking() == Color_None) {
      packageDropped = true;
    }
  }


  if (marker_Station == 1 && markerReached) {
    ColorISR();
    ColorISR();
st_station1:
    ColorISR();
    delay(5000);
    if (Color_GetTargetMarking() == Color_None) {
      goto st_station1;
    }
    if (Color_GetTargetMarking() == Color_Other) {
      Servo_Shake();
      ColorISR();
      ColorISR();
      ColorISR();
      delay(3000);
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
  int_en = false;
  Motor_Forward();
  delay(100);
  while (IR_getScore() >= 3) {
    delay(100);
  }
  int_en = true;
  //FIND CENTER HERE
  //robot_FindCenter();
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