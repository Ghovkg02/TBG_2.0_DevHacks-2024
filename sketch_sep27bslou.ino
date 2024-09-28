#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
const int vibratorPin = 5;  // Pin for the vibrator

void setup() {
  Serial.begin(115200);  // Start the serial communication
  Wire.begin();
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  pinMode(vibratorPin, OUTPUT);
}

void loop() {
  if (mpu.testConnection()) {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    
    // Get acceleration and gyroscope data
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // Send the data to Processing via serial
    Serial.print("Accel: ");
    Serial.print(ax); Serial.print(", ");
    Serial.print(ay); Serial.print(", ");
    Serial.println(az);

    Serial.print("Gyro: ");
    Serial.print(gx); Serial.print(", ");
    Serial.print(gy); Serial.print(", ");
    Serial.println(gz);
  }

  delay(100);  // Delay to avoid flooding the serial port
  
  // Check for vibrator command from Processing
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'V') {
      // Activate vibrator if 'V' command is received
      digitalWrite(vibratorPin, HIGH);
      delay(500);  // Vibrate for 500ms
      digitalWrite(vibratorPin, LOW);
    }
  }
}


