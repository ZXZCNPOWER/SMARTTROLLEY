
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

int enA = 9;
int in1 = 8;
int in2 = 7;

int relay1=2; //relay pins for drill 1 and 2 is together, 3 and 4 together
int relay2=3;
int relay3=4;
int relay4=5;

//int upbut=6;
//int downbut=7;
//int upbutswitch=0;
//int downswitch=0; 
//int initial = 0;

//int State1 = LOW;
//int State2 = LOW;

//int button1 = 11; //button control first
//int button2 = 12;

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
 
  pinMode(relay1,OUTPUT); //relay setup, HIGH=OFF, LOW=ON
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  digitalWrite(relay1,HIGH); 
  digitalWrite(relay2,HIGH); 
  digitalWrite(relay3,HIGH); 
  digitalWrite(relay4,HIGH); 


void loop(){
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
