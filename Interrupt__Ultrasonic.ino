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
    servo_motor.write(80);
  }

  else if (servo_angle == 80) {
    // Close doors before motor action
    servo_motor.write(0);
    // Start motors to rotate forward --------------------------check the directions -------------------------
    motordirection(HIGH, LOW, LOW, HIGH);
    // Tells the system to get off the stopping tape
    while (Ir_Left_Val == 0 && Ir_Right_Val == 0) {
      // Check IR sensors for line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      analogWrite(ENA, 100);
      analogWrite(ENB, 100);
    }
  }
}

int object_dist() {
  int distance;
  long duration;
  // Clears the trigPin condition
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHOPIN, HIGH);
  // Calculating the distance of the object based on speed of sound/ time it takes for signal to come back
  distance = duration * 0.034 / 2;
  Serial.print("Distance: "); //-----------------------------------------distance check----------------------------------------------------------------
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
