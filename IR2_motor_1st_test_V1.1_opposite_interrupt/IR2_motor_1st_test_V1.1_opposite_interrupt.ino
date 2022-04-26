#include <Arduino.h>
#include <Servo.h>

// IR sensors left pin and val
int Ir_Left_Val;
const static int IR_LEFT = 12;
// IR sensors right pin and val
const static int IR_RIGHT = 13;
int Ir_Right_Val;

// Motor left
const static int ENA = 10;
const static int LEFT_POS_CONTROL = 9;
const static int LEFT_NEG_CONTROL = 8;
// Motor right
const static int ENB = 11;
const static int RIGHT_POS_CONTROL = 6;
const static int RIGHT_NEG_CONTROL = 5;
// Initialize Motor speed
int Right_Rpm = 100;
int Left_Rpm = 100;
//Interrupt Pin
const static int IR_INTER = 3;

Servo servo_motor;
// Servo Motor
const static int SERVO_PIN = 4;
// Set the servo door as open
int servo_angle = 0;

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

  // initialize pin as input and attach interrupt to it
  pinMode(IR_INTER, INPUT);
  // Set IR_INTER as an interrupt to control servo action
  attachInterrupt(digitalPinToInterrupt(IR_INTER), ir_interrupt, FALLING);
  // Initializes the servo door to be open
  servo_motor.write(servo_angle);
}

void loop() {
  // check if the servo motor is closed or open
  servo_angle = servo_motor.read();
  // When the servo angle is 0(door closed)
  if (servo_angle == 0) {
    // Start processing IR right/left sensor signal
    ir_sensor();
  }
}
