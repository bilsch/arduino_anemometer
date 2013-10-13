/* 
  
  The MIT License (MIT)
  
  Copyright (c) 2013 Bill Schwanitz
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.


 * Sensor to detect the wind speed
 * Note, my main interest here is to detect the air flow from the vents in my house hvac system so I can tune the dampers
 * I'm also not converting these numbers to anything overly meainingful - just reading the raw values
 *
 * Sensor calibration logic comes from this very handy article: http://arduino.cc/en/Tutorial/Calibration
 * Using the anonmeter from http://shop.moderndevice.com/products/wind-sensor
 *
 * Note, the calibration is a little finicky and I don't think its working quite right yet
 *
 * To allow for no direct serial console the sensor will keep the led solid until booting/calibration is complete
 * Once the calibration is complete, the led will be pulsed on/off during each poll ( 500 ms, so its pretty fast )
 *
 * Pin connections
 * Out => A0
 * RV  => not connected, probably should be ;)
 * TMP => not connected, probably should be ;)
 *
*/
String location = "BEDROOM";
int md0550_data_pin = A0;    // output pin
int sensor_value = 0;
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value
float sensor_value_to_v = 0;
int led = 13;


void setup() {                
  // initialize the digital pin as an output.
  pinMode(md0550_data_pin, INPUT);   
  Serial.begin(115200);
//  Serial.println("Giving sensor a chance to boot up");
  delay(10000);
//  Serial.println("Calibrating");
  while (millis() < 40000) {
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    sensor_value = analogRead(md0550_data_pin);

    // record the maximum sensor value
    if (sensor_value > sensorMax) {
      /* Serial.print("Overriding sensorMax ");
      Serial.println(sensor_value); */
      sensorMax = sensor_value;
    }

    // record the minimum sensor value
    if (sensor_value < sensorMin) {
      /* Serial.print("Overriding sensorMin ");
      Serial.println(sensor_value); */
      sensorMin = sensor_value;
    }
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  }
//  Serial.print("Calibration settled with sensorMax = ");
//  Serial.print(sensorMax);
//  Serial.print(" and sensorMin = ");
//  Serial.println(sensorMin);
}

// loop and read the sensor
void loop() {
  // read the value from the sensor:
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  sensor_value = analogRead(md0550_data_pin);
  sensor_value = map(sensor_value, sensorMin, sensorMax, 0, 255);
  sensor_value_to_v =  0.0049 * sensor_value;
  Serial.print(location);
  Serial.print(" volt: ");
  Serial.println(sensor_value_to_v);
  digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(500);
}

