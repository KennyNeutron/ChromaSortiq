const uint32_t Color_Red = 0xFF0000;
const uint32_t Color_Green = 0x00FF00;
const uint32_t Color_Blue = 0x0000FF;
const uint32_t Color_None = 0xFFFFFF;
const uint32_t Color_Other = 0x5A5A5A;

uint32_t Color_Current = 0;

bool isReturning = false;
bool servoMoved = false;

#define servoPin 13

Servo myServo;

#define in1 5
#define in2 4
#define in3 3
#define in4 2
#define enA 6
#define enB 7
bool int_en = false;