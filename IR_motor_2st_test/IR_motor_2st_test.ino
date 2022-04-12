#include <Arduino.h>
#include <Servo.h>

// IR sensors left pin
const static int IR_LEFT = 18 ;
// IR sensors left val
int Ir_Left_Val = 0;
// IR sensors right pin
const static int IR_RIGHT = 19;
// IR sensors right val
int Ir_Right_Val = 0;

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
int servo_angle = 90;

// Servo door control IR sensor
const static int IR_TOP = 2;

// Initial Rpm of left and Right motors
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
  // Set IR_TOP as an interrupt to control servo action
  attachInterrupt(digitalPinToInterrupt(IR_TOP),ir_servo ,FALLING);
  // Initialize servo motor to 90°
  servo_motor.write(90);
}

void loop() {
  // check if the servo motor is closed or open
  servo_angle = servo_motor.read();
  // When the servo angle is 0(door closed)
  if(servo_angle == 0){
    // Start processing IR right/left sensor signal
     ir_sensor();
    }
}
