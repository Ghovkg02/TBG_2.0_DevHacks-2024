#include <Wire.h>
#include <MPU6050.h>

// Define I2C addresses
#define MPU6050_ADDR_1 0x68  // First MPU6050 (ADDR pin low)
#define MPU6050_ADDR_2 0x69  // Second MPU6050 (ADDR pin high)

MPU6050 mpu1(MPU6050_ADDR_1);
MPU6050 mpu2(MPU6050_ADDR_2);

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);  // SDA, SCL pins for ESP32

    // Initialize the first MPU6050
    mpu1.initialize();
    if (!mpu1.testConnection()) {
        Serial.println("MPU6050 #1 connection failed");
        while (1);
    }

    // Initialize the second MPU6050
    mpu2.initialize();
    if (!mpu2.testConnection()) {
        Serial.println("MPU6050 #2 connection failed");
        while (1);
    }

    // Optional: configure additional settings here
}

void loop() {
    // Read quaternion data from both MPU6050 sensors
    float q1[4], q2[4];
    getQuaternion(mpu1, q1);
    getQuaternion(mpu2, q2);

    // Send quaternion data to Processing
    Serial.print("Q1: "); 
    Serial.print(q1[0]); Serial.print(", ");
    Serial.print(q1[1]); Serial.print(", ");
    Serial.print(q1[2]); Serial.print(", ");
    Serial.print(q1[3]); Serial.println();
    
    Serial.print("Q2: "); 
    Serial.print(q2[0]); Serial.print(", ");
    Serial.print(q2[1]); Serial.print(", ");
    Serial.print(q2[2]); Serial.print(", ");
    Serial.print(q2[3]); Serial.println();

    delay(100); // Adjust delay as necessary
}

// Function to read quaternion data from MPU6050
void getQuaternion(MPU6050& mpu, float* q) {
    mpu.getQuaternion(q);
}
