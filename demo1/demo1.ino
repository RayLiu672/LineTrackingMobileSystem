#include <Arduino.h>

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
// Initialize speed
int Right_Rpm = 100;
int Left_Rpm = 100;

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

}

void loop() {
  // Rpm of left and Right motors
  int Dual_Rpm = 100;
  Right_Rpm = 100;
  Left_Rpm = 100;
  // IR sensors looking for line
  Ir_Right_Val = digitalRead(IR_RIGHT);
  Ir_Left_Val = digitalRead(IR_LEFT);
  Serial.println(Ir_Right_Val);
  Serial.println(Ir_Left_Val);
  // If line is detected
  if (Ir_Right_Val == 1 || Ir_Left_Val == 1) {
    // call detected function
    detected();
  }
  // // If both Ir sensors do not detect the line
  else if (Ir_Right_Val == 0 && Ir_Left_Val == 0) {
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH);
    // continue executing while both Ir sensors do not see the line
    while (Ir_Right_Val == 0 && Ir_Left_Val == 0) {
      // IR sensors looking for line
      Ir_Right_Val = digitalRead(IR_RIGHT);
      Ir_Left_Val = digitalRead(IR_LEFT);
      Serial.println(Ir_Right_Val);
      Serial.println(Ir_Left_Val);
      // ramping Rpm for both motors
      if (Dual_Rpm < 255) {
        Dual_Rpm ++ ;
        analogWrite(ENA, Dual_Rpm);
        analogWrite(ENB, Dual_Rpm);
      }
      delay(20);
    }
  }
}
