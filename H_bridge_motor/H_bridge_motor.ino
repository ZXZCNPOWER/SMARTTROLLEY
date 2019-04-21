
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

int enA = 9;
int in1 = 8;
int in2 = 7;
 
int initial = 0;


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
}


 
void loop()
 
{
  int dist = 0;


  lasersensor();
  
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
    }

    
  }


 
}
