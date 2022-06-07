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
  // Checks to see if the Servo door is opened
  else if (servo_angle == 80) {
    // Close doors before motor action
    servo_motor.write(0);
    // Start motors to rotate forward 
    motordirection(HIGH, LOW, LOW, HIGH);
    // Tells the system to get off the stopping tape
    while (Ir_Left_Val == 0 && Ir_Right_Val == 0) {
      // Check IR sensors for line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      // Rpm for both motors
      analogWrite(ENA, 100);
      analogWrite(ENB, 100);
    }
  }
}

// Ultrasonic object detection
int object_dist() {
  // Distance of object detected
  int distance;
  // How long for sound waves to travel from emitter to reciever
  long duration;
  // Clears the trigPin condition
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  // Sets the trigPin LOW (INACTIVE)
  digitalWrite(TRIGPIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHOPIN, HIGH);
  // Calculating the distance of the object based on speed of sound/ time it takes for signal to come back
  distance = duration * 0.034 / 2;
  //-----------------------------------------distance check----------------------------------------------------------------
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
