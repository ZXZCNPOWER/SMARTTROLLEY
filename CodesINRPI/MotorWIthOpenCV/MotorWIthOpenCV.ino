/*      30.007 Grp 13 Trolley Motor Controller Code w/Joystick



A0 - Forward 8
lft - Left 12
rght-Right 13
PWM 3- LM //Left Motor
PWM 5- RM //Right Motor
 */

int fwd = 2;
int lft = 4;
int rght = 5;
int rm = 11;
int lm = 10;
int maxi = 150;
int off = 0;

void setup() {
  // put your setup code here, to run once:
  
  pinMode(rm, OUTPUT);
  pinMode(lm, OUTPUT);
  pinMode(fwd, INPUT);
  
  pinMode(lft, INPUT);
  
  pinMode(rght, INPUT);
  
  
  /*int RM = 0;
  int LM = 0;*/
  Serial.begin(9600);

}

void loop() {

if(Serial.available()){ // only send data back if data has been sent
  char command =Serial.read();
  // put your main code here, to run repeatedly:
  bool valFwd = digitalRead(fwd);
  bool valLft = digitalRead(lft); 
  bool valRght = digitalRead(rght);
//  Serial.println(valFwd);
//  Serial.println(valLft);
//  Serial.println(valRght);
  //Serial.println(valLft);
  if (valFwd == HIGH || command == 'f' ){ // Move forward
    analogWrite(rm,maxi);
    analogWrite(lm,maxi);
    Serial.println("fwd");
  }
  else if (valLft == HIGH || command == 'c' || command == 'd'){ // Move Left
    analogWrite(lm,off);
    analogWrite(rm,maxi);
    Serial.println("left");
  }
  else if (valRght== HIGH || command == 'a' || command == 'b'){ //Move right
    analogWrite(lm,maxi);
    analogWrite(rm,off);
    Serial.println("right");  
  }
  else{
    analogWrite(lm,off);
    analogWrite(rm,off);
    Serial.println("off");
  //Serial.println();
  }
  Serial.println(command);
  //delay(500);
}
}
