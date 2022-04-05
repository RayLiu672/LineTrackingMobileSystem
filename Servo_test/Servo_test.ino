#include <Servo.h> 

// 
Servo myservo;

void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(7);
  // Position that my servo will be set to
  myservo.write(0);  
  
} 

void loop() {
  // Reading the last input value to myservo.write fxn
  Serial.println(myservo.read());
  
} 
