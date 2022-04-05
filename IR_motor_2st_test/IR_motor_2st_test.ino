#include <Arduino.h>
#include <Servo.h>

// IR sensors left pin and val
int Ir_Left_Val;
const static int IR_LEFT = 18 ;
// IR sensors right pin and val
const static int IR_RIGHT = 19;
int Ir_Right_Val;

// Motor left
const static int ENA = 10;
const static int LEFT_POS_CONTROL = 9;
const static int LEFT_NEG_CONTROL = 8;
// Motor right
const static int ENB = 11;
const static int RIGHT_POS_CONTROL = 6;
const static int RIGHT_NEG_CONTROL = 5;

// Servo Motor
const static int SERVO_PIN = 7;
Servo servo_motor;

// Rpm of left and Right motors
int Right_Rpm = 0;
int Left_Rpm = 0;
int Dual_Rpm = 0;

void setup() {
  // Communcation with Serial Console
  Serial.begin(9600);
  
  // IR sensor set as inputs
  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);
  
  // LEFT Motor Control + Enable pinout
  pinMode(ENA, OUTPUT);
  pinMode(LEFT_POS_CONTROL, OUTPUT);
  pinMode(LEFT_NEG_CONTROL, OUTPUT);
  
  // RIGHT Motor Control + Enable pinout
  pinMode(ENB, OUTPUT);
  pinMode(RIGHT_POS_CONTROL, OUTPUT);
  pinMode(RIGHT_NEG_CONTROL, OUTPUT);

  // initialize motor as LOW
  digitalWrite(LEFT_POS_CONTROL, LOW);
  digitalWrite(LEFT_NEG_CONTROL, LOW);
  digitalWrite(RIGHT_POS_CONTROL, LOW);
  digitalWrite(RIGHT_NEG_CONTROL, LOW);
  
  // Servo Motor Pin
  servo_motor.attach(SERVO_PIN);
}

void loop() {
  
  // IR sensors looking for line
  Ir_Right_Val = digitalRead(IR_RIGHT);
  Ir_Left_Val = digitalRead(IR_LEFT);

  // If line is detected
  if (Ir_Right_Val == 0 || Ir_Left_Val == 0) {
    // call detected function
    detected();
  }
  else if (Ir_Right_Val == 1 && Ir_Left_Val == 1) {
    Serial.println("nothing detected");
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, HIGH);
    digitalWrite(RIGHT_POS_CONTROL, HIGH); 
    digitalWrite(RIGHT_NEG_CONTROL, LOW);

    // Motor action continues as normal
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
