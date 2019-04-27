void leveljack() {
  if (state==1){
    LASERSENSOR();
    if (i==0){
      startMillis=millis();
      i=1;
      if (commandjack==1){
        up();
        if (dist > 200) {
          belowcar=1;
        }
        else{
          belowcar=0;
        }
      }

      else if (commandjack==2){
        down();
      }
    }

    else {     //i is other number
      currentMillis=millis();
      Serial.println(currentMillis);
      if (currentMillis - startMillis>5000){
      state=0;
      i=0;  
      startMillis=0;
      }
      else if (commandjack==1){
        if (belowcar==1){
          if (dist < 200){
            belowcar = 0;
          }
        }
        else if (belowcar==0){
          if (dist>500){
            state=0;
          }
        }
      }
      else if (commandjack==2){
        limitswitch=digitalRead(limitswitchpin);
        if (limitswitch==HIGH){
          state=0;
          i=0;
          Serial.println("HIGH");
        }
        else if (limitswitch==LOW){
          Serial.println("LOW");
      }
    }
  }
  }
  else{
    Serial.println("Off");
    off();
  }
}





void up() {
  digitalWrite(relay2,LOW);
  delay(50);
  digitalWrite(relay1,LOW);
}



void down(){ 
  digitalWrite(relay3,LOW); 
  delay(50); 
  digitalWrite(relay4,LOW); 
} 

void off(){ 
  digitalWrite(relay2,HIGH); 
  delay(50); 
  digitalWrite(relay1,HIGH); 
  delay(50); 
  digitalWrite(relay3,HIGH); 
  delay(50); 
  digitalWrite(relay4,HIGH); 
}


void LASERSENSOR()

{
  dist = sensor.readRangeContinuousMillimeters();
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
  Serial.println();

}
