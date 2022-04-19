void detected(){
  // IR sensor left and right triggered
  if(Ir_Right_Val == 1 && Ir_Left_Val == 1){
    // Turning both motors off
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
  }
  
  // When left Ir sees line
  else if(Ir_Right_Val == 0 && Ir_Left_Val == 1){    
    // decrease speed of left motor
    analogWrite(ENA, 0);
    
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH);   
    
    // increase Left motor Rpm  
    while(Ir_Left_Val == 1){
      // IR sensors looking for line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT); 
      if(Ir_Left_Val == 0){
        // leave loop
        break;
        }
      if(Right_Rpm < 255){
        Right_Rpm++; 
        //Increase the Left motor RPM
        analogWrite(ENB, Right_Rpm);
      }    
      delay(20);
      }      
    }

  // When right Ir sees line
  else if(Ir_Right_Val == 1 && Ir_Left_Val == 0){ 
    // decrease speed of right motor
    analogWrite(ENB, 0);
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, HIGH);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, HIGH); 
    while(Ir_Right_Val == 1){
      // Check if robot returned to line
      Ir_Left_Val = digitalRead(IR_LEFT);
      Ir_Right_Val = digitalRead(IR_RIGHT);
      if(Ir_Right_Val == 0){
        // leave loop
        break;
        }
      // Increase Right_Rpm
      if(Right_Rpm < 255){
        Right_Rpm++;
        analogWrite(ENA, Right_Rpm);
      }    
      delay(20);
      }             
    }
   }
