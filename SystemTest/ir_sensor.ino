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
        // Turning both motors off
        motordirection(LOW, LOW, LOW, LOW);
      }
      // If object is greater than 4cm away and Servo door is closed
      else if (dist > 4 && servo_angle == 0) {
        // Forward Motion
        motordirection(HIGH, LOW, LOW, HIGH);
        // Rpm for both motors
        analogWrite(ENA, Dual_Rpm);
        analogWrite(ENB, Dual_Rpm);
      }
      else if (servo_angle == 80 && dist != 0) {
        // Turning both motors off
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
// Determines the motor's action depending on condition
void motorcontrol() {
  // Checks if system enters motor control function
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
        // Decrease speed of right motor
        analogWrite(ENB, 45);
      }
      else if (servo_angle == 80 && dist != 0) {
        // Turning both motors off
        motordirection(LOW, LOW, LOW, LOW);
      }
      // IR sensors looking for line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      if (Ir_Right_Val == 1 || Ir_Left_Val == 0) {
        // leave loop if
        break;
      }
      // Set left motor speed 
      analogWrite(ENA, 215);
    }
  }
  // When left Ir sees line
  else if (Ir_Right_Val == 1 && Ir_Left_Val == 0) {
    //-------------------------------------------------------------Detection Test-------------------------------------------------------------
    Serial.println("left detected");
    // While the left Ir sensor sees the line
    while (Ir_Left_Val == 0) {
      //Check the Servo doors position(open/closed)
      servo_angle = servo_motor.read();
      // Calculate the objects distance if any
      int dist = object_dist();
      // If object is greater than 0cm and less than 4cm and Servo door is closed
      if (dist > 0 && dist <= 4 && servo_angle == 0) {
        // Turning both motors off
        motordirection(LOW, LOW, LOW, LOW);
      }
      // if the distance of object is within 4cm and Servo door closed
      else if (dist > 4 && servo_angle == 0) {
        // Change motor direction to turn left
        motordirection(LOW, HIGH, LOW, HIGH);
        // Decrease speed of left motor
        analogWrite(ENA, 45);
      }
      // Checks if the Servo door is opened and distance of object is not 0
      else if (servo_angle == 80 && dist != 0) {
        // Turning both motors off
        motordirection(LOW, LOW, LOW, LOW);
      }
      // Check if system returns to line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      // Checks for line detection 
      if (Ir_Left_Val == 1 || Ir_Right_Val == 0) {
        break;
      }
      //Increase the Right motor RPM
      analogWrite(ENB, 215);
    }
  }
}
