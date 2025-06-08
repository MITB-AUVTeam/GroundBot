#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();  // SDA, SCL for arduino

  byte status = mpu.begin();
  Serial.print("MPU6050 status: ");
  Serial.println(status);
  while (status != 0) {
    Serial.println("MPU6050 not connected. Retrying...");
    delay(1000);
    status = mpu.begin();
  }

  Serial.println("MPU6050 initialized successfully!");
  delay(1000);

  mpu.calcOffsets(true, true);  // Calibrate both gyro and accel
}

void loop() {
  mpu.update();

  Serial.print("Accel X: "); Serial.print(mpu.getAccX()); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(mpu.getAccY()); Serial.print(" | ");
  Serial.print("Z: "); Serial.print(mpu.getAccZ()); Serial.print(" || ");

  Serial.print("Gyro X: "); Serial.print(mpu.getGyroX()); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(mpu.getGyroY()); Serial.print(" | ");
  Serial.print("Z: "); Serial.println(mpu.getGyroZ());

  delay(500);
}
