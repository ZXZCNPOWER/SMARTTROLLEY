/*      30.007 Grp 13 Trolley Motor Controller Code w/Joystick
Group Members
Ave, James, Xue Zhi , Ming Yew , Chris Yi An , Zhen Yong

The arduino will read commands from RPI / Blue tooth and act accordingly. The commands are sent in single characters.

A0 - Forward 8
lft - Left 12
rght-Right 13
PWM 3- LM //Left Motor
PWM 5- RM //Right Motor
 */

#include <Wire.h>

#include <VL53L0X.h>

//
bool openCV = false;

// motor variables and pins
char junk;
int ave[1]; //array to store byte data
int fwd = 12;
int lft = 11;
int rght = 13;
int rm = 10;
int lm = 9;
int L_brake = 11;
int R_brake= 12;

//Leveling jack Variables and pins
VL53L0X sensor;
int relay1=2;
int relay2=3;
int relay3=4;
int relay4=5;
int upbut=6;
int downbut=7;
int limitswitchpin = 8;//limit switch pin
int dist = 0;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
int state=0;
int i=0;
int belowcar=0;
int commandjack=0;
int limitswitch=0;


// unused variables
int upbutswitch=0;
int downswitch=0;






//黄线长度160cm，小车98cm seting up ultra sesnor
const int pingPin10 = 53; // Trigger Pin of Ultrasonic Sensor 最右边
const int echoPin11 = 52; // Echo Pin of Ultrasonic Sensor
const int pingPin20 = 51; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin21 = 50; // Echo Pin of Ultrasonic Sensor
const int pingPin3 = 49; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin3 = 48; // Echo Pin of Ultrasonic Sensor
const int pingPin4 = 47; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin4 = 46; // Echo Pin of Ultrasonic Sensor
const int pingPin5 = 45; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin5 = 44; // Echo Pin of Ultrasonic Sensor

//Ledpins to detect collision place
int LEDPin1 = 31;
int LEDPin2 = 33;
//
int moveAllowed;

int LEDPin3 = 35; //THIS PIN CAN BE USED FOR OTHERS

//motor levelling pins

void setup() {
  pinMode(rm, OUTPUT); 
  pinMode(lm, OUTPUT);
  pinMode(R_brake,OUTPUT); // Right Brake
  pinMode(L_brake,OUTPUT);// Left Brake
  digitalWrite(rm,HIGH);
  digitalWrite(lm,HIGH);
  
  pinMode(LEDPin1, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LEDPin3, OUTPUT);
  /*int RM = 0;
  int LM = 0;*/

  //Motor levelling jack
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
  Wire.begin();
  sensor.init();
  sensor.setTimeout(500);
  sensor.startContinuous();


  Serial.begin(9600);
  Serial.begin(38400); //this is for bluetooth
}
  
void loop() {
  readColSensor();
  leveljack();      
  if(Serial.available()){ // check if there is any incoming data from the RPI / Blue tooth
      delay(20);
      
      if (moveAllowed == 1){  //sensor part should have 2 led on 
        automotor();
      }else if (moveAllowed == 0){
        analogWrite(rm,0);
        analogWrite(lm,0);
        Serial.println("stopp");
        
        }
      }
}
