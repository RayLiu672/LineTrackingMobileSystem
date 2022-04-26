int object_dist() {
  int distance;
  long duration;
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance of the object based on speed of sound/ time it takes for signal to come back
  distance = duration * 0.034 / 2;
  Serial.print("Distance: "); //-----------------------------------------distance check----------------------------------------------------------------
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
