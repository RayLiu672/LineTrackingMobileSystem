#include <Arduino.h>

// IR sensors left pin and val
int Ir_Top_Val;
const static int IR_TOP = 3;

// Motor left
const static int ENA = 10;
const static int LEFT_POS_CONTROL = 9;
const static int LEFT_NEG_CONTROL = 8;
// Motor right
const static int ENB = 11;
const static int RIGHT_POS_CONTROL = 6;
const static int RIGHT_NEG_CONTROL = 5;

bool opened = true;

void setup() {
  // put your setup code here, to run once:
  // Communcation with Serial Console
  Serial.begin(9600);
  // IR sensor set as inputs
  pinMode(IR_TOP, INPUT);
  // LEFT Motor Control + Enable pinout  
  pinMode(ENA, OUTPUT);
  pinMode(LEFT_POS_CONTROL, OUTPUT);
  pinMode(LEFT_NEG_CONTROL, OUTPUT);
  // RIGHT Motor Control + Enable pinout  
  pinMode(ENB, OUTPUT);
  pinMode(RIGHT_POS_CONTROL, OUTPUT);
  pinMode(RIGHT_NEG_CONTROL, OUTPUT);

  // initialize motor as LOW
  digitalWrite(LEFT_POS_CONTROL, LOW);29--
  digitalWrite(LEFT_NEG_CONTROL, LOW);
  digitalWrite(RIGHT_POS_CONTROL, LOW);
  digitalWrite(RIGHT_NEG_CONTROL, LOW);
  
  attachInterrupt(digitalPinToInterrupt(IR_TOP),ir_servo ,FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
   if(opened == true){
   digitalWrite(LEFT_POS_CONTROL, LOW);
   digitalWrite(LEFT_NEG_CONTROL, HIGH);
   digitalWrite(RIGHT_POS_CONTROL, HIGH);
   digitalWrite(RIGHT_NEG_CONTROL, LOW);
   }
   else{
    digitalWrite(LEFT_POS_CONTROL, LOW);
   digitalWrite(LEFT_NEG_CONTROL, LOW);
   digitalWrite(RIGHT_POS_CONTROL, LOW);
   digitalWrite(RIGHT_NEG_CONTROL, LOW);
    }
   analogWrite(ENA, 150);
   analogWrite(ENB, 150);
}
void ir_servo(){
  if(opened == true){
    opened = false;
    }
  else{
    opened = true;
    }
  }
