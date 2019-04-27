
void automotor() {
  
  Serial.println(ave[0]);
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    ave[0] = Serial.read(); // Reads the data from the serial port
    //Serial.println(state);
    if (ave[0] == 122 || ave[0] == 121) //open CV start or stop z, 122 is start y,121 is stop 
    {
      if (ave[0] == 122)
      {
        openCV = true;
      }
      else if (ave[0] == 121)
      {
        openCV = false;
      }
    }
    delay(5);
  }
    if (ave[0] == 79 && openCV == false){              //incase of 'O' Stop , 79 ASCII
      
    digitalWrite(rm,HIGH);//RM off
    digitalWrite(lm,HIGH); //LM off
    digitalWrite(R_brake,LOW);//Right Brake on
    digitalWrite(L_brake,LOW);//Left Brake on
    
    //Serial.println("off");
    }

    else if (ave[0] == 111 && openCV == true){              //incase of 'O' Stop , 79 ASCII
      
    digitalWrite(rm,HIGH);//RM off
    digitalWrite(lm,HIGH); //LM off
    digitalWrite(R_brake,LOW);//Right Brake on
    digitalWrite(L_brake,LOW);//Left Brake on
    
    //Serial.println("off");
    }

     else if(ave[0] == 70 &&  openCV == false){   //incase of 'F' Forward, 70 ASCII
      Forward();
      //Serial.println("Fwd");
      }

     else if(ave[0] == 102 && openCV == true){   //incase of 'f' Forward, 102 ASCII
      Forward();
      //Serial.println("Fwd");
      }

       else if(ave[0] == 76 && openCV == false){   //incase of 'L' turn Left, 76 ASCII
        Left();
    
      //Serial.println("Left");
       }
          else if(ave[0] == 108 && openCV == true){   //incase of 'l' turn Left, 108 ASCII
        Left();    
      //Serial.println("Left");
       }
       
      else if(ave[0] == 82 && openCV == false){   //incase of 'R' turn Right ,114 ASCII
      Right();
     // Serial.println("Right");
       }

      else if(ave[0] == 114 && openCV == true){   //incase of 'r' turn Right ,114 ASCII
      Right();
    
     // Serial.println("Right");
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
