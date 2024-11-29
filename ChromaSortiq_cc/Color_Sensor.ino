#define ColorSensor_S0 8
#define ColorSensor_S1 9
#define ColorSensor_S2 10
#define ColorSensor_S3 11
#define ColorSensor_SignalPin 12

void ColorSense_Init() {
  pinMode(ColorSensor_S0, OUTPUT);
  pinMode(ColorSensor_S1, OUTPUT);
  pinMode(ColorSensor_S2, OUTPUT);
  pinMode(ColorSensor_S3, OUTPUT);
  pinMode(ColorSensor_SignalPin, INPUT);
  digitalWrite(ColorSensor_S0, HIGH);
  digitalWrite(ColorSensor_S1, LOW);
}


uint32_t Color_GetTargetMarking() {
  unsigned long red, blue, green;

  digitalWrite(ColorSensor_S2, LOW);
  digitalWrite(ColorSensor_S3, LOW);
  red = pulseIn(ColorSensor_SignalPin, HIGH);

  digitalWrite(ColorSensor_S2, HIGH);
  digitalWrite(ColorSensor_S3, HIGH);
  green = pulseIn(ColorSensor_SignalPin, HIGH);

  digitalWrite(ColorSensor_S2, LOW);
  digitalWrite(ColorSensor_S3, HIGH);
  blue = pulseIn(ColorSensor_SignalPin, HIGH);

  if (red < 70 && red < green && red < blue) {
    return Color_Red;
  } else if (green < 90 && green < red && green < blue) {
    return Color_Green;
  } else if (blue < 51 && blue < red && blue < green) {
    return Color_Blue;
  } else {
    return Color_None;
  }
}

void Color_TestColor() {
  last_micros = micros();
  switch (Color_GetTargetMarking()) {
    case Color_Red:
      Serial.println("The color is RED");
      break;
    case Color_Green:
      Serial.println("The color is GREEN");
      break;
    case Color_Blue:
      Serial.println("The color is BLUE");
      break;
    case Color_None:
      Serial.println("The color is NO COLOR DETECTED");
      break;
    default:
      Serial.println("The color is NO COLOR DETECTED");
      break;
  }
  Serial.println("Time Elapsed:" + String(micros() - last_micros));
}