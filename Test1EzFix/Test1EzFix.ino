/*      30.007 Grp 13 Trolley Motor Controller Code w/Joystick
Group Members
Ave, James, Xue Zhi , Ming Yew , Chris Yi An , Zhen Yong

HOW THIS CODE WORKS -- The arduino has 2 main mode , EITHER reading serial data to update states/variables in the machine OR Mechanical response according to the states or variables
SCROLL DOWN AND READ THE specialDelay FUNCITON AND HOW TO USE IT !

*/

#include <Wire.h>

#include <VL53L0X.h>

//
bool openCV = false;

// motor variables and pins
char junk;
char ave; //char to store byte data
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
int limitswitchpin = 7;//limit switch pin
int dist = 0;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
int state=0;
int i=0;
int belowcar=0;
int commandjack=0;
int limitswitch=0;
int statemotor=0;


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
int moveAllowed = 1;

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
  //Serial.begin(38400); //this is for bluetooth
}
  
void loop() {
  if (Serial.available()>0) // to check incoming data, and update state accordingly !!
    ave = Serial.read();
    Serial.println(ave);
    // char U, D ,p is used for levelling jack.
    // char F,f,L,l,R,r,O,o for motor movement. O o is stop commands. Small letters are from bytes from openCV
    // char z,y is to indicate openCV running or not
    switch(ave){
      case 'z':
        openCV = true;
        break;
      case 'p':
        openCV = false;
        break;
      case 'F': // move forward
        statemotor = 1;
        break;
      case 'f': // move forward
        statemotor = 1;
        break;
      case 'L': //move left
        statemotor = 2;
        break;
      case 'l': //move left
        statemotor =2;
        break;
      case 'R': //move right
        statemotor=3;
        break;
      case 'r': // move right
        statemotor=3;
        break;
      case 'O': //stop moving
        statemotor = 0;
        break;
      case 'o': // stop moving
        statemotor = 0;
        break;
      case 'U': // level jack up
        state = 1;
        commandjack=1; // go up 
        Serial.println("UP");
        break;
      case 'D': // level jack down
        state = 1; // Go Down
        Serial.println("DOWN");
        commandjack = 2;
        break;
      case 'y': // holy shiet stop the jack!
        state = 0; // Go Down
        Serial.println("HOLY SHIT STOP THE JACK");
        break;
    }

    leveljack();
    //readColSensor();
    automotor();

    //while
}

void specialDelay( int x ){ // put in the amount of delay you want in microseconds and it would delayed by that valued * 10!!
  for ( int i = 0 ; i < x ;i ++)
  {
    delay (10);
    if (Serial.available()>0){break;}
  }
}
