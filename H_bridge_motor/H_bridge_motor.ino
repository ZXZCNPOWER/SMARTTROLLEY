
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

int enA = 9;
int in1 = 8;
int in2 = 7;
 
int initial = 0;

int State1 = LOW;
int State2 = LOW;

int button1 = 11; //button control first
int button2 = 12;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();

//  Serial.println("VLX53LOX test started.");
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);

}


 
void UPMOVE()
 
{
  int dist = 0;
  GY();
  
  if (dist < 100 ){   //being blocked

    initial = initial + 1; //如果最开始就已经比车高了， 那stage就是1 
    digitalWrite(in1, HIGH); //UP 
    digitalWrite(in2, LOW);
    delay(100);

 
    
  }else if (dist > 100) {
    initial = initial; // 如果最开始没有车高，那么stage就是0
    if (initial == 0 ) {
      digitalWrite(in1, HIGH);
      digitalWrite(in1, LOW);
      delay(100);
    }else{

     digitalWrite(in1, LOW); //说明已经经过了车后保险杠， 再遇到空就停下了
     digitalWrite(in2, LOW);
     delay(100);
    }
   
  if ( initial > 500 ) {   //I DNT KNOW HOW TO MAKE THIS STOP ....HELP (CAN ADD BUZZER ON)
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW); 
    delay(5000);

    
  }
  }


 
}

void DOWNMOVE(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
}
void loop(){
  State1 = digitalRead(button1);
  State2 = digitalRead(button2);
  
  if ( State1 == HIGH && State2 == LOW){
    UPMOVE();
  }else if (State2 == HIGH && State1 == LOW){
    DOWNMOVE();
  }else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }
  



}
