#include <Servo.h> 

int curr_state = 0;
Servo myservo;

void detected(){
  curr_state = myservo.read();
  if(curr_state == 0){
    myservo.write(180);
    }
  else if(curr_state == 180){
    myservo.write(0);  
    }
  }
  
void setup() 
{ 
  Serial.begin(9600);
  myservo.attach(7);
  // Position that my servo will be set to
  myservo.write(0);
  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3),detected ,FALLING);
  
} 

void loop() {
  // Reading the last input value to myservo.write fxn
  Serial.println(myservo.read());
  
} 
