void ir_sensor() {
  // Rpm of left and Right motors
  int Dual_Rpm = 100;
  Right_Rpm = 100;
  Left_Rpm = 100;
  // IR sensors looking for line
  Ir_Right_Val = digitalRead(IR_RIGHT);
  Ir_Left_Val = digitalRead(IR_LEFT);
  //-------------------------------------------------------------IR Detection Test-------------------------------------------------------------
  Serial.println(Ir_Right_Val);
  Serial.println(Ir_Left_Val);
  // If line is detected
  if (Ir_Right_Val == 0 || Ir_Left_Val == 0) {
    // call motorcontrol function
    motorcontrol();
  }
  // // If both Ir sensors do not detect the line
  else if (Ir_Right_Val == 1 && Ir_Left_Val == 1) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("nothing detected");
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH);
    // continue executing while both Ir sensors do not see the line
    while (Ir_Right_Val == 1 && Ir_Left_Val == 1) {
      // IR sensors looking for line
      Ir_Right_Val = digitalRead(IR_RIGHT);
      Ir_Left_Val = digitalRead(IR_LEFT);
      Serial.println(Ir_Right_Val);
      Serial.println(Ir_Left_Val);
      // ramping Rpm for both motors
      if (Dual_Rpm < 255) {
        Dual_Rpm ++ ;
        analogWrite(ENA, Dual_Rpm);
        analogWrite(ENB, Dual_Rpm);
      }
      delay(20);
    }
  }
}

void motorcontrol() {
  // Checks if system enters motor control function =============================== adjustment needed ============================================================ put it after fxn call
  Serial.println("motorcontrol entered");
  // IR sensor left and right triggered
  if (Ir_Right_Val == 0 && Ir_Left_Val == 0) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("both detected");
    // Turning both motors off
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
  }
  // When right Ir sees line
  else if (Ir_Right_Val == 0 && Ir_Left_Val == 1) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("right detected");
    // Decrease speed of right motor ===============================adjustment needed============================================================
    analogWrite(ENA, 0); // =============================change 0 ===========================================================================
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH);
    // increase Left motor Rpm
    while (Ir_Right_Val == 0) {
      // IR sensors looking for line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      if (Ir_Right_Val == 1) {
        // leave loop if
        break;
      }
      //----------------------------------------------------------------------Get rid of if statement or analogWrite that controls speed ---------------------------------
      if (Right_Rpm < 255) {
        Right_Rpm++;
        //Increase the Left motor RPM
        analogWrite(ENB, Right_Rpm);
      }
      analogWrite(ENB, 255);
      delay(20);
    }
  }
  // When left Ir sees line
  else if (Ir_Right_Val == 1 && Ir_Left_Val == 0) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("left detected");
    // Decrease speed of left motor ===============================adjustment needed============================================================
    analogWrite(ENB, 0); // =============================change 0 ===========================================================================
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH);

    while (Ir_Left_Val == 0) {
      // Check if robot returned to line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      if (Ir_Left_Val == 1) {
        break;
      }
      //----------------------------------------------------------------------Get rid of if statement or analogWrite that controls speed ---------------------------------
      // Increase Right_Rpm
      if (Right_Rpm < 255) {
        Right_Rpm++;
        analogWrite(ENA, Right_Rpm);
      }
      analogWrite(ENA, 255);
      //Increase the Right motor RPM
      delay(20);
    }
  }
}
