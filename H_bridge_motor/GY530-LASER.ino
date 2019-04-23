
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;


int relay1=2;         //ALL OF THIS NEED TO CHANGE ACCORDING TO ARDUINO MEGA
int relay2=3;
int relay3=4;
int relay4=5;
int upbut=6;
int downbut=7;
int upbutswitch=0;
int downswitch=0;
int limitswitchpin = 8;//limit switch pin
int dist = 0;


unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
int state=0;
int i=0;
int belowcar=0;
int commandjack=0;
int limitswitch=0;
void setup() {
  
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  pinMode(limitswitchpin, INPUT);
  //pinMode(upbut,INPUT);
  //pinMode(downbut,INPUT);
  digitalWrite(relay1,HIGH); 
  digitalWrite(relay2,HIGH); 
  digitalWrite(relay3,HIGH); 
  digitalWrite(relay4,HIGH); 
  Serial.begin(9600);

  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  sensor.startContinuous();

}

void loop() {


  if (state==1){
    LASERSENSOR();
    if (i==0){
      startMillis=millis();
      i=1;
      if (commandjack==1){
        
        up();
        if (dist > 100) {
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
      if (currentMillis - startMillis>5000){
      state=0;
      i=0;
      startMillis=0;
      }
      else if (commandjack=1){
        if (belowcar==1){
          if (dist < 100){
            belowcar = 0;
          }
        }
        else if (belowcar=0){
          if (dist>1000){
            state=0;
          }
        }

      }
      else if (commandjack=2){
        limitswitch=digitalRead(limitswitchpin);
        if (limitswitch==HIGH){
          state=0;
        }
      }
    }
  }
  else{
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
