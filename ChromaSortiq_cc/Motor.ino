#define in1 5
#define in2 4
#define in3 3
#define in4 2
#define enA 6
#define enB 7

const uint8_t Speed_Motor1 = 125;
const uint8_t Speed_Motor2 = 125;

const uint8_t Speed_RightTurn = 137;
const uint8_t Speed_LeftTurn = 137;

void Motors_Init(){
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
}

void Motor_Forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, Speed_Motor1);
  analogWrite(enB, Speed_Motor2);
}

void Motor_Left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, Speed_LeftTurn);
  analogWrite(enB, Speed_RightTurn);
}

void Motor_Right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, Speed_LeftTurn);
  analogWrite(enB, Speed_RightTurn);
}

void Motor_Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
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