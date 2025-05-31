#include <Wire.h>
#include <MPU6050_light.h>

int dt = 20;

// Motor control 
int m2i1 = 26;
int m2i2 = 25;
int m2e  = 27;
int m1i1 = 12;
int m1i2 = 14;
int m1e  = 13;

// PWM control
int SDA_pin = 21;
int SCL_pin = 22;

const int pwmFreq = 500;
const int pwmResolution = 8;

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  
  // IMU setup
  Wire.begin(SDA_pin, SCL_pin);
  Wire.setClock(100000);

  byte status = mpu.begin();
  Serial.print("MPU6050 status: ");
  Serial.println(status);
  while (status != 0) {
    Serial.println("MPU6050 not connected. Retrying...");
    delay(50*dt);
    status = mpu.begin();
  }

  Serial.println("MPU6050 initialized successfully!");
  delay(50*dt);

  mpu.calcOffsets(true, true);  

  // motor setup 
  pinMode(m1i1, OUTPUT);
  pinMode(m1i2, OUTPUT);
  pinMode(m2i1, OUTPUT);
  pinMode(m2i2, OUTPUT);

  digitalWrite(m2i1, LOW);
  digitalWrite(m2i2, HIGH);
  digitalWrite(m1i1, LOW);
  digitalWrite(m1i2, HIGH);

  ledcAttach(m1e, pwmFreq, pwmResolution);
  ledcAttach(m2e, pwmFreq, pwmResolution);

  ledcWrite(m1e, 150);
  ledcWrite(m2e, 150);
}

void loop() {
  mpu.update();

  Serial.print("Accel X: "); Serial.print(mpu.getAccX()); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(mpu.getAccY()); Serial.print(" | ");
  Serial.print("Z: "); Serial.print(mpu.getAccZ()); Serial.print(" || ");

  Serial.print("Gyro X: "); Serial.print(mpu.getGyroX()); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(mpu.getGyroY()); Serial.print(" | ");
  Serial.print("Z: "); Serial.println(mpu.getGyroZ());

  delay(8*dt);
}
