#define IR_Left A0
#define IR_Right A1
#define IR_Marking A2


void IR_Init() {
    pinMode(IR_Left, INPUT);
    pinMode(IR_Right, INPUT);
    pinMode(IR_Marking, INPUT);
}


bool Status_IR(char WhichIR){
    switch(WhichIR){
        case 'L': //LEFT IR
            return digitalRead(IR_Left);
            break;
        case 'R': //RIGHT IR
            return digitalRead(IR_Right);
            break;
        case 'M': //MARKING IR
            return digitalRead(IR_Marking);
            break;
        default:
            return false;
            break;
    }
}