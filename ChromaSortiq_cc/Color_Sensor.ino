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
  return Color_Current;
}

// uint32_t getColor() {
//   unsigned long red, blue, green;

//   digitalWrite(ColorSensor_S2, LOW);
//   digitalWrite(ColorSensor_S3, LOW);
//   red = pulseIn(ColorSensor_SignalPin, HIGH);
//   Serial.println("c_Red:" + String(red));

//   digitalWrite(ColorSensor_S2, HIGH);
//   digitalWrite(ColorSensor_S3, HIGH);
//   green = pulseIn(ColorSensor_SignalPin, HIGH);
//   Serial.println("c_Green:" + String(green));

//   digitalWrite(ColorSensor_S2, LOW);
//   digitalWrite(ColorSensor_S3, HIGH);
//   blue = pulseIn(ColorSensor_SignalPin, HIGH);
//   Serial.println("c_Blue:" + String(blue));

//   if (red > 500 && green > 400 && blue > 400) {
//     Serial.println("color is NONE");
//     return Color_None;
//   } else {
//     if (green < 100 && blue < 100) {
//       if (red < 100 && green < 100 && blue < 100) {
//         Serial.println("No dominant color detected.1");
//         return Color_Other;
//       } else {
//         Serial.println("Skyblue detected!");
//         return Color_Blue;
//       }
//     } else {
//       if (red > green && red > blue && red > 50) {
//         Serial.println("Green detected!");
//         return Color_Green;
//       } else if (green > red && green > blue && green > 50 && red < 100) {
//         if (red < 100 && blue < 100) {
//           Serial.println("No dominant color detected.2");
//           return Color_Other;
//         } else {
//           Serial.println("Red detected!");
//           return Color_Red;
//         }
//       } else {
//         if (red < 120 && red < green && red < blue) {
//           Serial.println("Red detected!");
//           return Color_Red;
//         } else {
//           Serial.println("No dominant color detected.3");
//           return Color_Other;
//         }
//       }
//     }
//   }
// }

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

void testColor2() {
  switch (Color_GetTargetMarking()) {
    case Color_Red:
      Serial.println("Color: RED");
      break;
    case Color_Green:
      Serial.println("Color: GREEN");
      break;
    case Color_Blue:
      Serial.println("Color: BLUE");
      break;
    case Color_Other:
      Serial.println("Color: EWAN!");
      break;
    case Color_None:
      Serial.println("Color: None");
      break;
    default:
      Serial.println("Color: None");
      break;
  }
}