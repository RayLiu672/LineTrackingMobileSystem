void detected(){
  // IR sensor left and right triggered
  if(Ir_Right_Val == 1 && Ir_Left_Val == 1){
    
    Serial.println("both detected");
    // Turning both motors off
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
  }
  
  // IR sensor right triggered
  else if(Ir_Right_Val == 1 && Ir_Left_Val == 0){    
    Serial.println("right detected");
     // Right stop
    analogWrite(ENB, 45);
    
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH); 
    
    // increase Left motor Rpm  ------------------------------------------------------------------------------- Take a look a while loop condition ----------------------------------------
    while(Ir_Right_Val == 0){
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT); 
      if(Ir_Left_Val == 0){
        break;
        }
      if(Left_Rpm < 255){
        Left_Rpm++; 
        //Increase the Left motor RPM
        analogWrite(ENA, Left_Rpm);
      }    
      analogWrite(ENA, 255);
      delay(20);
      }      
    }
    
  // IR sensor left triggered  
  else if(Ir_Right_Val == 0 && Ir_Left_Val == 1){ 
    Serial.println("left detected");
    // left stop
    analogWrite(ENA, 0);
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH);
    
    // increase Right motor Rpm ------------------------------------------------------------------------------- Take a look a while loop condition ----------------------------------------
    while(Ir_Left_Val == 0){
      // Check if robot returned to line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      if(Ir_Right_Val == 0){
        break;
        }
      // Increase Right_Rpm
      if(Right_Rpm < 255){
        Right_Rpm++;
        analogWrite(ENB, Right_Rpm);
      }
      analogWrite(ENB, 255);
      //Increase the Right motor RPM    
      delay(20);
      }             
    }
   }
