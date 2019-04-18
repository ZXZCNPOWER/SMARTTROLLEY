#include <Wire.h> //这个是可以工作的 距离也可以

#define VL53L0X_REG_IDENTIFICATION_MODEL_ID         0xc0
#define VL53L0X_REG_IDENTIFICATION_REVISION_ID      0xc2
#define VL53L0X_REG_PRE_RANGE_CONFIG_VCSEL_PERIOD   0x50
#define VL53L0X_REG_FINAL_RANGE_CONFIG_VCSEL_PERIOD 0x70
#define VL53L0X_REG_SYSRANGE_START                  0x00
#define VL53L0X_REG_RESULT_INTERRUPT_STATUS         0x13
#define VL53L0X_REG_RESULT_RANGE_STATUS             0x14
#define address 0x29


int enA = 9;
int in1 = 8;
int in2 = 7;
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // start serial for output
//  Serial.println("VLX53LOX test started.");
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}


void demoOne()
 
{
 
  // This function will run the motors in both directions at a fixed speed
 
  // Turn on motor A

  digitalWrite(in1, HIGH); //等下加上condition，从laser的那边读数
  digitalWrite(in2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enA, 200);
 

 
  // Now change motor directions
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  

 
  delay(2000);
 
  // Now turn off motors
 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  

 
}
 
void loop()
 
{
  int dist = 0;
  digitalWrite(in1, HIGH); //等下加上condition，从laser的那边读数
  digitalWrite(in2, LOW);
 
  // Set speed to 200 out of possible range 0~255
 
  analogWrite(enA, 200);
  delay(1000);
  lasersensor();
  
  if (dist > 100 ){

    digitalWrite(in1, HIGH); //等下加上condition，从laser的那边读数
    digitalWrite(in2, LOW);
    analogWrite(enA, 50);
    delay(200);
    digitalWrite(in1, LOW); //等下加上condition，从laser的那边读数
    digitalWrite(in2, LOW);
    analogWrite(enA,0);
 
    
  }else{
    digitalWrite(in1, HIGH); //等下加上condition，从laser的那边读数
    digitalWrite(in2, LOW);
    analogWrite(enA, 50);
    
  }


 
}
