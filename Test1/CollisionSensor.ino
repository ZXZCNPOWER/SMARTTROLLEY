

//this is avoiding obstacle sensor 
//x=0 is stop
//x=1 is moving 


void readColSensor(){
  int cmL =0;
  int cmR = 0 ;
  int op;

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
   delay(50);

   pinMode(pingPin20, OUTPUT);
   digitalWrite(pingPin20, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin20, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin20, LOW);
   pinMode(echoPin11, INPUT);
   duration = pulseIn(echoPin21, HIGH);
   cmR = microsecondsToCentimeters(duration);
   delay(50);

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

    digitalWrite(LEDPin1, LOW);
    digitalWrite(LEDPin2, LOW);
    digitalWrite(LEDPin3, HIGH);
    op = 0; //stop
   }else{

    digitalWrite(LEDPin1, HIGH);
    digitalWrite(LEDPin2, HIGH);
    digitalWrite(LEDPin3, LOW);
    op = 1 ;// moving
   }
   delay(10);
   
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
