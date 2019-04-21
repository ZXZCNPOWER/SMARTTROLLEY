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

//analog pins ?? optional 
int fwd = 2;
int lft = 4;
int rght = 5;

//motor pins
int rm = 5;
int lm = 3;
//int i = 1 ; //for the motor go straight

char junk;   //for bluetooth control
String inputString="";
int x = 0;
int y = 0;


int op ; // check AB sensor status
int maxi = 150;
int off = 0;
String state = ""; 


//黄线长度160cm，小车98cm seting up ultra sesnor
const int pingPin10 = 32; // Trigger Pin of Ultrasonic Sensor 最右边
const int echoPin11 = 33; // Echo Pin of Ultrasonic Sensor
const int pingPin20 = 30; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin21 = 31; // Echo Pin of Ultrasonic Sensor
const int pingPin3 = 24; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin3 = 22; // Echo Pin of Ultrasonic Sensor
const int pingPin4 = 25; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin4 = 26; // Echo Pin of Ultrasonic Sensor
const int pingPin5 = 27; // Trigger Pin of Ultrasonic Sensor中间
const int echoPin5 = 28; // Echo Pin of Ultrasonic Sensor

//Ledpins to detect collision place
int LEDPin1 = 51;
int LEDPin2 = 52;
int LEDPin3 = 53;

void setup() {
  pinMode(rm, OUTPUT);
  pinMode(lm, OUTPUT);
  pinMode(fwd, INPUT);
  pinMode(lft, INPUT);
  pinMode(rght, INPUT);
  pinMode(LEDPin1, OUTPUT);
  pinMode(LEDPin2, OUTPUT);
  pinMode(LEDPin3, OUTPUT);
  /*int RM = 0;
  int LM = 0;*/
  Serial.begin(9600);
  Serial.begin(38400); //this is for bluetooth
}
  
void loop() {

  if(Serial.available()){ // check if there is any incoming data from the RPI / Blue tooth
      readColSensor();
      delay(20);
      if (op == 1){  //sensor part should have 2 led on 
        autoMotor();
        
      }else if (op == 0){
        analogWrite(rm,0);
        analogWrite(lm,0);
        Serial.println("stopp");
        
      }

      }

}
