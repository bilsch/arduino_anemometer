/* 
 * Sensor to detect the wind speed
 * Note, my main interest here is to detect the air flow from the vents in my house hvac system so I can tune the dampers
 * I'm also not converting these numbers to anything overly meainingful - just reading the raw values
 *
 * Sensor calibration logic comes from this very handy article: http://arduino.cc/en/Tutorial/Calibration
 * Using the anonmeter from http://shop.moderndevice.com/products/wind-sensor
 *
 * Note, the calibration is a little finicky and I don't think its working quite right yet
 *
*/
int md0550_data_pin = A0;
int sensor_value = 0;
int sensorMin = 1023;        // minimum sensor value
int sensorMax = 0;           // maximum sensor value
float sensor_value_to_v = 0;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(md0550_data_pin, INPUT);   
  Serial.begin(115200);
  Serial.println("Giving sensor a chance to boot up");
  delay(10000);
  Serial.println("Calibrating");
  while (millis() < 40000) {
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
  }
  Serial.print("Calibration settled with sensorMax = ");
  Serial.print(sensorMax);
  Serial.print(" and sensorMin = ");
  Serial.println(sensorMin);
}

// loop and read the sensor
void loop() {
  // read the value from the sensor:
  sensor_value = analogRead(md0550_data_pin);
  sensor_value = map(sensor_value, sensorMin, sensorMax, 0, 255);
  sensor_value_to_v =  0.0049 * sensor_value;
  Serial.print("volt: ");
  Serial.println(sensor_value_to_v);
  delay(1000);
}

