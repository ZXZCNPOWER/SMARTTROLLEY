//this one is used to test the motor only 

const int switchPin1 = 11; //the switch connect to pin 11
const int switchPin2 = 12; //the switch connect to pin 12
const int switchPin3 = 13; //the switch connect to pin 13


int switchState1 = 0;         // variable for reading the pushbutton status
int switchState2 = 0;         // variable for reading the pushbutton status
int switchState3 = 0;         // variable for reading the pushbutton status

int pwmPin1 = 3;
int pwmPin2 = 5;
int i=1;
void setup()
{
  pinMode(switchPin1, INPUT); //initialize thebuttonPin as input
  pinMode(switchPin2, INPUT); //initialize thebuttonPin as input
  pinMode(switchPin3, INPUT); //initialize thebuttonPin as input
  
  pinMode(pwmPin1,OUTPUT); 
  pinMode(pwmPin2,OUTPUT); 
  
  Serial.begin(9600);

}
/**********************************/
void loop()
{
  switchState1 = digitalRead(switchPin1);
  switchState2 = digitalRead(switchPin2);
  switchState3 = digitalRead(switchPin3);
  if (switchState1 == LOW && switchState2 == HIGH && switchState3 == LOW) //if it is,the state is HIGH
  {
    Serial.println(i);
    if (i==1){
    analogWrite(pwmPin1,180);
    analogWrite(pwmPin2,160);
    delay(600);
    i=i+1;
    analogWrite(pwmPin1,0);
    analogWrite(pwmPin2,0);
    }
    else {
      Serial.println(i);
      analogWrite(pwmPin1,150);
      analogWrite(pwmPin2,230);
      delay(105);
      analogWrite(pwmPin1,0);
      analogWrite(pwmPin2,0);//once it runs, dnt need full speed alr
      delay(115);
//    delay(2000);
    }
  }
  else  if (switchState1 == HIGH && switchState2 == LOW && switchState3 == LOW) //if it is,the state is HIGH
  {
    analogWrite(pwmPin1,250); //full speed turn
    analogWrite(pwmPin2,0);
  }
  else  if (switchState1 == LOW && switchState2 == LOW && switchState3 == HIGH) //if it is,the state is HIGH
  {
    analogWrite(pwmPin1,0);
    analogWrite(pwmPin2,250);
  }else {
    i=1;
    analogWrite(pwmPin1,0);
    analogWrite(pwmPin2,0);
  }

}
