void autoMotor(){ //this function includes controlling the motor by buttons.
  
  char command = Serial.read(); // Reads any input char from BlueTooth or RPI
//  bool valFwd = digitalRead(fwd);
//  bool valLft = digitalRead(lft); 
//  bool valRght = digitalRead(rght);
//  Serial.println(valFwd);
//  Serial.println(valLft);
//  Serial.println(valRght);
  //Serial.println(valLft);
  if ( command == 'f' ){ // Move forward
    analogWrite(rm,maxi);
    analogWrite(lm,180);
    Serial.println("fwd");
  }
  else if ( command == 'c' || command == 'd'){ // Move Left
    analogWrite(lm,off);
    analogWrite(rm,maxi);
    Serial.println("left");
  }
  else if ( command == 'a' || command == 'b'){ //Move right
    analogWrite(lm,180);
    analogWrite(rm,off);
    Serial.println("right");  
  }
  else if (command == 's'){
    analogWrite(lm,off);
    analogWrite(rm,off);
    Serial.println("off");
  }
  Serial.println(command);
  //delay(500);
}

void inputMotor()
{
  
}
