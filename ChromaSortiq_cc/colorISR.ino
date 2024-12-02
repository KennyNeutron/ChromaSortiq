void ColorISR() {
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
    Color_Current = Color_Red;
  } else if (green < 90 && green < red && green < blue) {
    Color_Current = Color_Green;
  } else if (blue < 51 && blue < red && blue < green) {
    Color_Current = Color_Blue;
  } else {
    Color_Current = Color_None;
  }
}
