void ir_sensor() {
  // If line is detected
  if (Ir_Right_Val == 0 || Ir_Left_Val == 0) {
    // call detected function
    motor_control();
  }

  else if (Ir_Right_Val == 1 && Ir_Left_Val == 1) {
    Serial.println("nothing detected");
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, HIGH);
    digitalWrite(RIGHT_POS_CONTROL, HIGH);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);

    // Motor action continues as normal ---------------------------------------change to while ------------------------------------------
    for (Dual_Rpm == Right_Rpm; Dual_Rpm < 256; Dual_Rpm++) {
      Ir_Right_Val = digitalRead(IR_RIGHT);
      Ir_Left_Val = digitalRead(IR_LEFT);
      analogWrite(ENA, Dual_Rpm);
      analogWrite(ENB, Dual_Rpm);
      delay(20);
      if (Ir_Right_Val == 0 || Ir_Left_Val == 0) {
        break;
      }
    }
  }
}

// System Control based on angle of Servo (Interrupt)
void ir_servo() {
  servo_angle = servo_motor.read();
  // Servo angle greater than 0 degrees(open)
  if (servo_angle > 0) {
    // close doors
    servo_motor.write(0);
    // turning right direction
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH);
    analogWrite(ENA, 100);
    analogWrite(ENB, 100);
    // checks IR sensors
    while (Ir_Right_Val != 0 && Ir_Left_Val != 1) {
      // Read IR sensor data
      Ir_Right_Val = digitalRead(IR_RIGHT);
      Ir_Left_Val = digitalRead(IR_LEFT);
    }
    // stop motor rotation
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }

  // if the servo motor is 0 degrees(closed)
  else if (servo_angle == 0) {
    // motors stop
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
    // doors open
    servo_motor.write(90);
  }
}
