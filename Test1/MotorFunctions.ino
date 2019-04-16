void autoMotor(){ //this function includes controlling the motor by buttons.
  
  char command = Serial.read(); // Reads any input char from BlueTooth or RPI

  if ( command ==  'a' || command ==  'b' || command ==  'c' || command ==  'd' || command ==  'e' || command ==  'f' ) { //this shows if the command is sent by rpi 
    
    if ( command == 'f' ){ // Move forward
    analogWrite(rm,maxi);
    analogWrite(lm,maxi);
    Serial.println("fwd");
    }
    else if ( command == 'c' || command == 'd'){ // Move Left
      analogWrite(lm,off);
      analogWrite(rm,maxi);
      Serial.println("left");
    }
    else if (command == 'a' || command == 'b'){ //Move right
      analogWrite(lm,maxi);
      analogWrite(rm,off);
      Serial.println("right");  
    }
    else{
      analogWrite(lm,off);
      analogWrite(rm,off);
      Serial.println("off");
    }
    Serial.println(command);
    //delay(500);
    
  }else if (isDigit(command)){ //this is if the value is from bluetooth ,which is a integer
    

    x = Serial.read();
    delay(10);
    y = Serial.read();
     //Serial.print("X: ");
     Serial.print(x);
     //Serial.print("| Y: ");
     Serial.print(y);
     Serial.println( );
     if (y<120){
      analogWrite(rm,maxi);
      analogWrite(lm,maxi);
      //Serial.print("Forward");
      //Serial.println( );
     }
     else if ( x<120){ 
      analogWrite(lm,off);
      analogWrite(rm,maxi);
     //Serial.print("Left");
     //Serial.println( );
     }
     else if ( x> 160){
      analogWrite(lm,maxi);
      analogWrite(rm,off);
     //Serial.print("Right");
     //Serial.println( );
     }
     else{
      analogWrite(lm,off); 
      analogWrite(rm,off); 
    }
  
    
  }
  }

void inputMotor()
{
  
}
