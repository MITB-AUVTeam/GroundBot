#include <Wire.h>

int m1i1 = 2;
int m1i2 = 4;
int m1e = 15;
int m2i1 = 18;
int m2i2 = 19;
int m2e = 5;

#define MPU6500_ADDR 0x68

// MPU-6500 Register addresses
#define WHO_AM_I 0x75
#define PWR_MGMT_1 0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H 0x43

// Sensitivity scale factors from datasheet
const float ACCEL_SCALE = 16384.0;  // LSB/g for ±2g (default)
const float GYRO_SCALE = 131.0;     // LSB/(°/s) for ±250 °/s (default)

void setup() {
  pinMode(m1i1, OUTPUT);
  pinMode(m1i2, OUTPUT);
  pinMode(m1e, OUTPUT);
  pinMode(m2i1, OUTPUT);
  pinMode(m2i2, OUTPUT);
  pinMode(m2e, OUTPUT);

  Serial.begin(9600);
  Wire.begin(21, 22);  // SDA = GPIO21, SCL = GPIO22 on ESP32

  delay(2000);

  Serial.println("Initializing MPU6500...");

  // Wake up the MPU-6500 (clear sleep bit)
  writeRegister(PWR_MGMT_1, 0x00);
  delay(500);

  // Check WHO_AM_I register
  uint8_t whoami = readRegister(WHO_AM_I);
  Serial.print("WHO_AM_I = 0x");
  Serial.println(whoami, HEX);
  // if (whoami != 0x70) {
  //   Serial.println("MPU-6500 not found!");
  //   while (1);
  // } else {
  //   Serial.println("MPU-6500 found and ready.");
  // }
}

void loop() {

  digitalWrite(m2i1, LOW);
  digitalWrite(m2i2, HIGH);
  digitalWrite(m1i1, LOW);
  digitalWrite(m1i2, HIGH);

  analogWrite(m1e, 255);
  analogWrite(m2e, 255);


  int16_t ax = read16(ACCEL_XOUT_H);
  int16_t ay = read16(ACCEL_XOUT_H + 2);
  int16_t az = read16(ACCEL_XOUT_H + 4);

  int16_t gx = read16(GYRO_XOUT_H);
  int16_t gy = read16(GYRO_XOUT_H + 2);
  int16_t gz = read16(GYRO_XOUT_H + 4);

  // Convert to physical units
  float accelX = (float)ax / ACCEL_SCALE * 9.80665;  // m/s²
  float accelY = (float)ay / ACCEL_SCALE * 9.80665;
  float accelZ = (float)az / ACCEL_SCALE * 9.80665;

  float gyroX = (float)gx / GYRO_SCALE * 3.14159265 / 180.0;  // rad/s
  float gyroY = (float)gy / GYRO_SCALE * 3.14159265 / 180.0;
  float gyroZ = (float)gz / GYRO_SCALE * 3.14159265 / 180.0;

  Serial.print("Accel (m/s^2): ");
  Serial.print(accelX, 3);
  Serial.print("\t");
  Serial.print(accelY, 3);
  Serial.print("\t");
  Serial.print(accelZ, 3);
  Serial.print("\t");

  Serial.print("Gyro (rad/s): ");
  Serial.print(gyroX, 3);
  Serial.print("\t");
  Serial.print(gyroY, 3);
  Serial.print("\t");
  Serial.println(gyroZ, 3);

  delay(100);
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(MPU6500_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6500_ADDR, 1);
  return Wire.read();
}

int16_t read16(uint8_t reg) {
  Wire.beginTransmission(MPU6500_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6500_ADDR, 2);
  uint8_t high = Wire.read();
  uint8_t low = Wire.read();
  return (int16_t)(high << 8 | low);
}

void writeRegister(uint8_t reg, uint8_t data) {
  Wire.beginTransmission(MPU6500_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}
