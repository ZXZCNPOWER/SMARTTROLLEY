void automotor() {
       if (statemotor==0){
         digitalWrite(lm,HIGH);
         digitalWrite(rm,HIGH);
         digitalWrite(R_brake,LOW);
         digitalWrite(L_brake,LOW);
       }
       else if (statemotor==1 && moveAllowed== 1){
         Forward();
         Serial.println("forward");
       }
       else if (statemotor==2 && moveAllowed== 1){
         Left();
         Serial.println("Left");
       }
       else if (statemotor==3 && moveAllowed== 1){
         Right();
         Serial.println("Right");
       }
    }
    

void Forward()
{
      Serial.println("Fwd");
      digitalWrite(rm,LOW);//RM on
      digitalWrite(lm,LOW);//LM on
      digitalWrite(R_brake,HIGH);// Left Brake off
      digitalWrite(L_brake,HIGH);//Right Brake off
      delay(500);
      
      digitalWrite(rm,HIGH);//RM off
      digitalWrite(lm,HIGH);// LM off 
      digitalWrite(R_brake,HIGH);//Right Brake off
      digitalWrite(L_brake,HIGH);//Left Brake off
      delay(500);
}

void Left()
{
          Serial.println("Left");
          digitalWrite(rm,LOW);//RM on
          digitalWrite(lm,HIGH);//LM off
          digitalWrite(R_brake,HIGH);//Right Brake off
          digitalWrite(L_brake,LOW);//Left Brake on
          delay(500);
      
          digitalWrite(rm,HIGH);//RM off
          digitalWrite(lm,HIGH);//LM off
          digitalWrite(R_brake,HIGH);//Right Brake Off
          digitalWrite(L_brake,LOW);//Left Brake on
          delay(500);
}

void Right()
{
      Serial.println("Right");
      digitalWrite(rm,HIGH);//RM off
      digitalWrite(lm,LOW); //LM on
      digitalWrite(R_brake,LOW); //Right Brake On
      digitalWrite(L_brake,HIGH);//Left Brake Off
      delay(500);
  
      digitalWrite(rm,HIGH);//RM off
      digitalWrite(lm,HIGH);//LM off
      digitalWrite(R_brake,LOW);//Right Brake on
      digitalWrite(L_brake,HIGH);//Left Brake off
      
      delay(500);
}
