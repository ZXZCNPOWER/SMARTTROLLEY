

//this is avoiding obstacle sensor 
//x=0 is stop
//x=1 is moving 
//change to 5 sensors alr, 

void readColSensor(){
  int cmL =0;
  int cmR = 0 ;
  int cma = 0;
  int cmb = 0;

   long duration, inches, cm;
   pinMode(pingPin10, OUTPUT);
   digitalWrite(pingPin10, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin10, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin10, LOW);
   pinMode(echoPin11, INPUT);
   duration = pulseIn(echoPin11, HIGH);
   cmL = microsecondsToCentimeters(duration);

   pinMode(pingPin20, OUTPUT);
   digitalWrite(pingPin20, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin20, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin20, LOW);
   pinMode(echoPin21, INPUT);
   duration = pulseIn(echoPin21, HIGH);
   cmR = microsecondsToCentimeters(duration);
   



   pinMode(pingPin3, OUTPUT);
   digitalWrite(pingPin3, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin3, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin3, LOW);
   pinMode(echoPin3, INPUT);
   duration = pulseIn(echoPin3, HIGH);
   cm = microsecondsToCentimeters(duration);
   


   pinMode(pingPin4, OUTPUT);
   digitalWrite(pingPin4, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin4, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin4, LOW);
   pinMode(echoPin4, INPUT);
   duration = pulseIn(echoPin4, HIGH);
   cma = microsecondsToCentimeters(duration);


   pinMode(pingPin5, OUTPUT);
   digitalWrite(pingPin5, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin5, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin5, LOW);
   pinMode(echoPin5, INPUT);
   duration = pulseIn(echoPin5, HIGH);
   cmb = microsecondsToCentimeters(duration);

  
   Serial.println(cmL);
   Serial.println(cmR);
   Serial.println(cm);
   Serial.println(cma);
   Serial.println(cmb);


   if ((20 <cmL && cmL < 300) || (20 <cmR && cmR< 300) || (20<cm && cm < 300) || (20<cma && cma < 300) || (20<cmb && cmb < 300)){

    digitalWrite(LEDPin1, LOW);
    digitalWrite(LEDPin2, HIGH);
    moveAllowed = 1; //stop
    Serial.println(moveAllowed);
    //Serial.println("move not allowed");
   }else{

    digitalWrite(LEDPin1, HIGH);
    digitalWrite(LEDPin2, LOW);
    moveAllowed = 1 ;// moving
    Serial.println(moveAllowed);
    Serial.println("move allowed");
   }
   
   

}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
