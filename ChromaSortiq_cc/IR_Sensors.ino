#define IR_Left A2
#define IR_Right A0
#define IR_Middle A1
#define IR_Marker A3

void IR_Init() {
  pinMode(IR_Left, INPUT_PULLUP);
  pinMode(IR_Right, INPUT_PULLUP);
  pinMode(IR_Middle, INPUT_PULLUP);
  pinMode(IR_Marker, INPUT_PULLUP);
}


bool IR_Status(char WhichIR) {
  switch (WhichIR) {
    case 'L':  //LEFT IR
      return digitalRead(IR_Left);
      break;
    case 'R':  //RIGHT IR
      return digitalRead(IR_Right);
      break;
    case 'M':  //MARKING IR
      return digitalRead(IR_Middle);
      break;
    case 'K':
      return digitalRead(IR_Marker);
    default:
      return false;
      break;
  }
}

void IR_test() {
  Serial.println("IR Left Status: " + String(IR_Status('L')));
  Serial.println("IR Right Status: " + String(IR_Status('R')));
  Serial.println("IR Middle Status: " + String(IR_Status('M')));
  Serial.println("IR Marker Status: " + String(IR_Status('K')));
  Serial.println("IR Score:" +String(IR_getScore()));
}


uint8_t IR_getScore() {
  uint8_t score = 0;

  if (IR_Status('L')) {
    score++;
  }
  if (IR_Status('R')) {
    score++;
  }
  if (IR_Status('M')) {
    score++;
  }
  if (IR_Status('K')) {
    score++;
  }
  return score;
}