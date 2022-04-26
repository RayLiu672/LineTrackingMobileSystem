// Performs action depending on servo status(open/closed)
void ir_interrupt() {
  // Check the angle of the servo motor
  servo_angle = servo_motor.read();
  // if the servo motor is closed

  if (servo_angle == 0) {
    // Stop all motor action
    motordirection(LOW, LOW, LOW, LOW);
    // Allows time for full stop
    delay(20);
    // open the servo door
    servo_motor.write(90);
  }

  else if (servo_angle > 0) {
    // Close doors before motor action
    servo_motor.write(0);
    // Start motors to rotate forward --------------------------check the directions -------------------------
    motordirection(HIGH, LOW, LOW, HIGH);
    // Tells the system to get off the stopping tape
    while (Ir_Left_Val == 1 && Ir_Right_Val == 1) {
      // Check IR sensors for line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      analogWrite(ENA, 75);
      analogWrite(ENB, 75);
    }
    //stop the motors to allow better transition?
  }
}
