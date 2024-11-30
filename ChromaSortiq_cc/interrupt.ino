void interrupt_setup() {
  cli();

  // TCCR0A = 0;
  // TCCR0B = 0;
  // TCNT0 = 0;
  // OCR0A = 124;
  // TCCR0A |= (1 << WGM01);
  // TCCR0B |= (1 << CS01) | (1 << CS00);
  // TIMSK0 |= (1 << OCIE0A);


  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 249;
  TCCR2A |= (1 << WGM21);
  TCCR2B |= (1 << CS21);
  TIMSK2 |= (1 << OCIE2A);

  sei();
}





ISR(TIMER2_COMPA_vect) {
  cli();
  if (!makerreached) {

    if (IR_Status('M') && !hasForwarded) {
      Motor_Forward();
      delay(100);
      hasForwarded = true;
    }

    if (!IR_Status('L') && !IR_Status('R') && IR_Status('M') && !hasForwarded) {
      Motor_Forward();
      hasForwarded = true;
    }


    if (IR_Status('L') && !IR_Status('M')) {
      digitalWrite(enA, 0); //TurnRight
      hasForwarded = false;
    } else if (IR_Status('R') && !IR_Status('M')) {
      digitalWrite(enB, 0); //TurnLeft
      hasForwarded = false;
    }
  }

  sei();
}