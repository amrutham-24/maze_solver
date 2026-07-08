#include <Wire.h>
#include "Adafruit_VL53L0X.h"
// Sensor objects
Adafruit_VL53L0X sensorLeft;
Adafruit_VL53L0X sensorFront;
Adafruit_VL53L0X sensorRight;
// XSHUT pins
#define XSHUT_LEFT   5
#define XSHUT_FRONT  18
#define XSHUT_RIGHT  19
// New I2C addresses
#define ADDR_LEFT   0x30
#define ADDR_FRONT  0x31
#define ADDR_RIGHT  0x32

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  // XSHUT pins
  pinMode(XSHUT_LEFT, OUTPUT);
  pinMode(XSHUT_FRONT, OUTPUT);
  pinMode(XSHUT_RIGHT, OUTPUT);
  // Turn OFF all sensors
  digitalWrite(XSHUT_LEFT, LOW);
  digitalWrite(XSHUT_FRONT, LOW);
  digitalWrite(XSHUT_RIGHT, LOW);
  delay(200);

  // ---------------- LEFT SENSOR ----------------
  digitalWrite(XSHUT_LEFT, HIGH);
  delay(200);
  if (!sensorLeft.begin(0x29)) {
    Serial.println("Left failed");
    while(1);
  }
  sensorLeft.setAddress(ADDR_LEFT);

  Serial.println("Left OK");
  
  // ---------------- FRONT SENSOR ----------------
  digitalWrite(XSHUT_FRONT, HIGH);
  delay(200);
  if (!sensorFront.begin(0x29)) {
    Serial.println("Front failed");
    while(1);
  }
  sensorFront.setAddress(ADDR_FRONT);
  Serial.println("Front OK");

  // ---------------- RIGHT SENSOR ----------------
  digitalWrite(XSHUT_RIGHT, HIGH);
  delay(200);
  if (!sensorRight.begin(0x29)) {
    Serial.println("Right failed");
    while(1);
  }
  sensorRight.setAddress(ADDR_RIGHT);
  Serial.println("Right OK");
  Serial.println("All sensors ready!");
}

void loop() {

  VL53L0X_RangingMeasurementData_t leftMeasure;
  VL53L0X_RangingMeasurementData_t frontMeasure;
  VL53L0X_RangingMeasurementData_t rightMeasure;
  // LEFT
  sensorLeft.rangingTest(&leftMeasure, false);
  Serial.print("Left: ");
  if (leftMeasure.RangeStatus != 4) {
    Serial.print(leftMeasure.RangeMilliMeter);
    Serial.print(" mm");
  }
  else {
    Serial.print("Out");
  }
  Serial.print(" | ");
  // FRONT
  sensorFront.rangingTest(&frontMeasure, false);
  Serial.print("Front: ");
  if (frontMeasure.RangeStatus != 4) {
    Serial.print(frontMeasure.RangeMilliMeter);
    Serial.print(" mm");
  }
  else {
    Serial.print("Out");
  }
  Serial.print(" | ");
  // RIGHT
  sensorRight.rangingTest(&rightMeasure, false);
  Serial.print("Right: ");
  if (rightMeasure.RangeStatus != 4) {
    Serial.print(rightMeasure.RangeMilliMeter);
    Serial.print(" mm");
  }
  else {
    Serial.print("Out");
  }
  Serial.println();
  delay(100);
}
