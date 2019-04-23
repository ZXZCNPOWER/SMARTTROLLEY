//这个现在也可以工作 也比较准确


//
// #include <Wire.h>
// #include <VL53L0X.h>
//
// VL53L0X sensor;
//
//// void setup()
// {
//   Serial.begin(9600);
//   Wire.begin();
//
//   sensor.init();
//   sensor.setTimeout(500);
//
//   // Start continuous back-to-back mode (take readings as
//   // fast as possible).  To use continuous timed mode
//   // instead, provide a desired inter-measurement period in
//   // ms (e.g. sensor.startContinuous(100)).
//   sensor.startContinuous();
// }

void LASERSENSOR()
{
  dist = sensor.readRangeContinuousMillimeters();
  Serial.print(sensor.readRangeContinuousMillimeters());
  
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

  Serial.println();
}
