  
void readColSensor(){
  int cmL =0;
  int cmR = 0 ;

   long duration, inches, cm;
   pinMode(pingPin10, OUTPUT);
   digitalWrite(pingPin10, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin10, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin10, LOW);
   pinMode(echoPin11, INPUT);
   duration = pulseIn(echoPin11, HIGH);
//   inches = microsecondsToInches(duration);
   cmL = microsecondsToCentimeters(duration);

   pinMode(pingPin20, OUTPUT);
   digitalWrite(pingPin20, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin20, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin20, LOW);
   pinMode(echoPin11, INPUT);
   duration = pulseIn(echoPin21, HIGH);
   cmR = microsecondsToCentimeters(duration);

   pinMode(pingPin3, OUTPUT);
   digitalWrite(pingPin3, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin3, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin3, LOW);
   pinMode(echoPin11, INPUT);
   duration = pulseIn(echoPin3, HIGH);
   cm = microsecondsToCentimeters(duration);

  

   delay(50);

   if ((20 <cmL && cmL < 300) || (20 <cmR && cmR< 300) || (20<cm && cm < 300)){
    Serial.println("STOP");
    Serial.println(cmR);
    Serial.println(cmL);
    Serial.println(cm);
    digitalWrite(LEDPin1, LOW);
    digitalWrite(LEDPin2, LOW);
    digitalWrite(LEDPin3, HIGH);
   }else{
    Serial.println("moving");
    Serial.println(cmR);
    Serial.println(cmL);
    Serial.println(cm);
    digitalWrite(LEDPin1, HIGH);
    digitalWrite(LEDPin2, HIGH);
    digitalWrite(LEDPin3, LOW);
   }
   delay(100);
   
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
