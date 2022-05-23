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
    // continue executing while both Ir sensors do not see the line
    while (Ir_Right_Val == 1 && Ir_Left_Val == 1) {
      servo_angle = servo_motor.read();
      int dist = object_dist();
      if (dist > 0 && dist <= 4 && servo_angle == 0) {
        motordirection(LOW, LOW, LOW, LOW);
      }
      else if (dist > 4 && servo_angle == 0) {
        // Forward Motion
        motordirection(HIGH, LOW, LOW, HIGH);
        // Rpm for both motors
        analogWrite(ENA, Dual_Rpm);
        analogWrite(ENB, Dual_Rpm);
      }
      else if (servo_angle == 80 && dist != 0) {
        motordirection(LOW, LOW, LOW, LOW);
      }
      // IR sensors looking for line
      Ir_Right_Val = digitalRead(IR_RIGHT);
      Ir_Left_Val = digitalRead(IR_LEFT);
      Serial.println(Ir_Right_Val);
      Serial.println(Ir_Left_Val);
    }
  }
}

void motorcontrol() {
  // Checks if system enters motor control function =============================== adjustment needed ============================================================
  Serial.println("motorcontrol entered");
  // IR sensor left and right triggered
  if (Ir_Right_Val == 0 && Ir_Left_Val == 0) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("both detected");
    // Turning both motors off
    motordirection(LOW, LOW, LOW, LOW);
  }
  // When right Ir sees line
  else if (Ir_Right_Val == 0 && Ir_Left_Val == 1) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("right detected");
    // increase Left motor Rpm
    while (Ir_Right_Val == 0) {
      servo_angle = servo_motor.read();
      // Check for incoming objects
      int dist = object_dist();
      if (dist > 0 && dist <= 4 && servo_angle == 0) {
        motordirection(LOW, LOW, LOW, LOW);
      }
      else if (dist > 4 && servo_angle == 0) {
        // Right Turn
        motordirection(HIGH, LOW, HIGH, LOW);
        // Decrease speed of right motor ===============================adjustment needed============================================================
        analogWrite(ENB, 45);
      }
      else if (servo_angle == 80 && dist != 0) {
        motordirection(LOW, LOW, LOW, LOW);
      }
      // IR sensors looking for line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      if (Ir_Right_Val == 1 || Ir_Left_Val == 0) {
        // leave loop if
        break;
      }
      analogWrite(ENA, 215);
    }
  }
  // When left Ir sees line
  else if (Ir_Right_Val == 1 && Ir_Left_Val == 0) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("left detected");
    while (Ir_Left_Val == 0) {
      servo_angle = servo_motor.read();
      int dist = object_dist();
      if (dist > 0 && dist <= 4 && servo_angle == 0) {
        motordirection(LOW, LOW, LOW, LOW);
      }
      else if (dist > 4 && servo_angle == 0) {
        // Left turn
        motordirection(LOW, HIGH, LOW, HIGH);
        // Decrease speed of left motor ===============================adjustment needed============================================================
        analogWrite(ENA, 45);
      }
      else if (servo_angle == 80 && dist != 0) {
        motordirection(LOW, LOW, LOW, LOW);
      }
      // Check if system returns to line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      //
      if (Ir_Left_Val == 1 || Ir_Right_Val == 0) {
        break;
      }
      //Increase the Right motor RPM
      analogWrite(ENB, 215);
    }
  }
}
