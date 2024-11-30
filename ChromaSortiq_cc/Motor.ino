#define in1 5
#define in2 4
#define in3 3
#define in4 2
#define enA 6
#define enB 7

int Speed_Motor1 = 130;
int Speed_Motor2 = 130;

int Speed_RightTurn = 128;
int Speed_LeftTurn = 128;

void Motors_Init() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  digitalWrite(enA, 0);
  digitalWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Motor_Forward() {
  digitalWrite(enA, 1);
  digitalWrite(enB, 1);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Motor_Left() {
  digitalWrite(enA, 1);
  digitalWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void Motor_Right() {
  digitalWrite(enA, 0);
  digitalWrite(enB, 1);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Motor_Stop() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  // digitalWrite(in1, LOW);
  // digitalWrite(in2, LOW);
  // digitalWrite(in3, LOW);
  // digitalWrite(in4, LOW);
}


void Operate_StopAndDrop() {
  Motor_Stop();
  if (!servoMoved) {
    myServo.write(30);
    delay(1000);
    myServo.write(80);
    servoMoved = true;
    isReturning = true;
    //currentColor = "";
  }
}

void Servo_Test() {
  myServo.write(30);
  delay(1000);
  myServo.write(80);
  delay(1000);
}