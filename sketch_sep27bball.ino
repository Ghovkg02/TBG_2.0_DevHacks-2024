#include <Wire.h>
#include <MPU6050.h>

// Create MPU6050 objects for two sensors
MPU6050 mpu1;
MPU6050 mpu2;

// Variables to hold sensor data
int16_t ax1, ay1, az1; // Accel data for MPU6050 1
int16_t ax2, ay2, az2; // Accel data for MPU6050 2

void setup() {
  Serial.begin(115200); // Start serial communication at 115200 baud rate
  
  // Initialize I2C
  Wire.begin();
  
  // Initialize the first MPU6050
  mpu1.initialize();
  mpu2.initialize();
  
  // Check if both sensors are connected
  if (!mpu1.testConnection()) {
    Serial.println("MPU6050 1 not connected!");
  }
  if (!mpu2.testConnection()) {
    Serial.println("MPU6050 2 not connected!");
  }
}

void loop() {
  // Get accelerometer data for both sensors
  mpu1.getAcceleration(&ax1, &ay1, &az1);
  mpu2.getAcceleration(&ax2, &ay2, &az2);
  
  // Send data in the format: ax1, ay1, az1, ax2, ay2, az2
  Serial.print(ax1); Serial.print(","); 
  Serial.print(ay1); Serial.print(","); 
  Serial.print(az1); Serial.print(","); 
  Serial.print(ax2); Serial.print(","); 
  Serial.print(ay2); Serial.print(","); 
  Serial.print(az2); Serial.println(); // Print to serial
  
  delay(100); // Adjust delay as needed
}
