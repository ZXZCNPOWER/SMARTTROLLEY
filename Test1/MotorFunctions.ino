void autoMotor(){ //this function includes controlling the motor by buttons.
  
  char command = Serial.read(); // Reads any input char from BlueTooth or RPI

  if ( command ==  'a' || command ==  'b' || command ==  'c' || command ==  'd' || command ==  'e' || command ==  'f' ) { //this shows if the command is sent by rpi 
    Serial.println("read from rpi");
    if ( command == 'f' ){ // Move forward
     
      analogWrite(rm,maxi);
      analogWrite(lm,maxi);
      Serial.println("fwd");
//       if (i==1){
//         analogWrite(lm,180); // THE VALUE HERE IS ACCORDING TO THE WEIGHT 
//         analogWrite(rm,160);
//         delay(600);
//         i=i+1;
//         analogWrite(lm,0);
//         analogWrite(rm,0);
//       } else {
//         Serial.println(i);
//         analogWrite(lm,150);
//         analogWrite(rm,230);
//         delay(105);
//         analogWrite(lm,0);
//         analogWrite(rm,0);//once it runs, dnt need full speed alr
//         delay(115);
    }
    else if ( command == 'c' || command == 'd'){ // Move Left
      analogWrite(lm,off);
      analogWrite(rm,255);
      Serial.println("left");
    }
    else if (command == 'a' || command == 'b'){ //Move right
      analogWrite(lm,maxi);
      analogWrite(rm,255);
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
     
     Serial.println("reading from bluetooth");   

    x = Serial.read();
    delay(10);
    y = Serial.read();
     //Serial.print("X: ");
     Serial.print(x);
     //Serial.print("| Y: ");
     Serial.print(y);
     Serial.println( );
     if (y<120){
       
       analogWrite(lm,150);
       analogWrite(rm,150);
       
//       if (i==1){
//         analogWrite(lm,180); // THE VALUE HERE IS ACCORDING TO THE WEIGHT 
//         analogWrite(rm,160);
//         delay(600);
//         i=i+1;
//         analogWrite(lm,0);
//         analogWrite(rm,0);
//       } else {
//         Serial.println(i);
//         analogWrite(lm,150);
//         analogWrite(rm,230);
//         delay(105);
//         analogWrite(lm,0);
//         analogWrite(rm,0);//once it runs, dnt need full speed alr
//         delay(115);
//      }
     }else if ( x<120){ 
      analogWrite(lm,off);
      analogWrite(rm,255);
     //Serial.print("Left");
     //Serial.println( );
     }
     else if ( x> 160){
      analogWrite(lm,255);
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


