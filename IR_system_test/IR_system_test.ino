// IR sensors 1 and 2 Pin mapping
const static int IR_RIGHT = 18;
const static int IR_LEFT = 19;
// IR sensor values 
int Ir_Right_Val;
int Ir_Left_Val;

void setup() {
  // Communcation with Serial Console
  Serial.begin(9600);
  // IR sensor set as inputs
  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);

}

void loop() {
  // IR sensors looking for line
  Ir_Right_Val = digitalRead(IR_RIGHT);
  Ir_Left_Val = digitalRead(IR_LEFT);
  
  // If line is detected
  if(Ir_Right_Val == 0 | Ir_Left_Val == 0){
    // call detected function
    detected();
    }
}
void detected(){
  Serial.println("test");
  // IR sensor right triggered
  if(Ir_Right_Val == 0 & Ir_Left_Val == 1){
    // increase left motor speed & maybe decrease right motor speed
    Serial.println("right detected");
    }
  // IR sensor left triggered  
  else if(Ir_Left_Val == 0 & Ir_Right_Val == 1){
    // increase left motor speed & maybe decrease right motor speed
    Serial.println("left detected");
    }
  // IR sensor left and right triggered
  else if(Ir_Right_Val == 0 & Ir_Left_Val == 0){
    // Both motors stop
    Serial.println("both detected");
    }
  }
