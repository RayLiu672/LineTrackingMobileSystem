void detected(){
    Serial.println("test");
  // IR sensor left and right triggered
  if(Ir_Right_Val == 0 && Ir_Left_Val == 0){
    
    Serial.println("both detected");
    // Turning both motors off
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, LOW);
    digitalWrite(RIGHT_POS_CONTROL, LOW);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
  }
  
  // IR sensor right triggered
  else if(Ir_Right_Val == 0 && Ir_Left_Val == 1){
    
    Serial.println("right detected");
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, HIGH);
    digitalWrite(RIGHT_POS_CONTROL, HIGH);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);   
    
    // increase Left motor Rpm  ------------------------------------------------------------------------------- Take a look a while loop condition ----------------------------------------
    while(Ir_Right_Val == 0){
      Ir_Right_Val = digitalRead(IR_RIGHT); 
      Left_Rpm++; 
      //Increase the Left motor RPM
      analogWrite(ENA, Left_Rpm);    
      delay(20);
        // If it does return to the line -----------------------------(necessary?)
      }
     Left_Rpm = Right_Rpm;       
    }
    
  // IR sensor left triggered  
  else if(Ir_Right_Val == 1 && Ir_Left_Val == 0){ 
    Serial.println("left detected");
    
    // Forward Motion
    digitalWrite(LEFT_POS_CONTROL, LOW);
    digitalWrite(LEFT_NEG_CONTROL, HIGH);
    digitalWrite(RIGHT_POS_CONTROL, HIGH);
    digitalWrite(RIGHT_NEG_CONTROL, LOW);
    
    // increase Right motor Rpm ------------------------------------------------------------------------------- Take a look a while loop condition ----------------------------------------
    while(Ir_Left_Val == 0){
      // Check if robot returned to line
      Ir_Left_Val = digitalRead(IR_LEFT);
      // Increase Right_Rpm
      Right_Rpm++;
      //Increase the Left motor RPM
      analogWrite(ENA, Right_Rpm);    
      delay(20);
      }           
    // Equalize Rpm
    Right_Rpm = Left_Rpm;         
    }
   }
