void motor_control() {
  // IR sensor left and right triggered
  if (Ir_Right_Val == 0 && Ir_Left_Val == 0) {
    Serial.println("both detected");
    // Turning both motors off
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
  }
  // IR sensor right triggered
  else if (Ir_Right_Val == 0 && Ir_Left_Val == 1) {
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, HIGH);
    digitalWrite(RIGHT_POS_CONTROL, HIGH);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
    // increase Left motor Rpm  ---------------------------------------change to while ------------------------------------------
    for (Left_Rpm = Right_Rpm; Left_Rpm < 256; Left_Rpm++) {
      // Check if robot returned to line
      Ir_Right_Val = digitalRead(IR_RIGHT);
      // If it does return to the line
      if (Ir_Right_Val == 1) {
        // Equalize Rpm
        Left_Rpm = Right_Rpm;
        break;
      }
      //Increase the Left motor RPM
      analogWrite(ENA, Left_Rpm);
      delay(20);
    }
  }
  
  // IR sensor left triggered
  else if (Ir_Right_Val == 1 && Ir_Left_Val == 0) {
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, HIGH);
    digitalWrite(RIGHT_POS_CONTROL, HIGH);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
    // increase Right motor Rpm  ---------------------------------------change to while ------------------------------------------
    for (Right_Rpm = Right_Rpm; Right_Rpm < 256; Right_Rpm++) {
      // Check if robot returned to line
      Ir_Left_Val = digitalRead(IR_LEFT);
      // If it does return to the line
      if (Ir_Left_Val == 1) {
        // Equalize Rpm
        Right_Rpm = Left_Rpm;
        break;
      }
      //Increase the Right motor RPM
      analogWrite(ENA, Right_Rpm);
      delay(20);
    }
  }
}
