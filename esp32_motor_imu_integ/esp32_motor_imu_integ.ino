#include <Wire.h>
#include <MPU6050_light.h>

int dt = 20;
int i = 0;

// Motor control 
int m2i1 = 7;
int m2i2 = 6;
int m2e  = 9;
int m1i1 = 5;
int m1i2 = 4;
int m1e  = 3;



MPU6050 mpu(Wire);

void setup() {
  Serial.begin(115200);
  
  // IMU setup
  Wire.begin();
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
  pinMode(m1e, OUTPUT);
  pinMode(m2e, OUTPUT);

}

void loop() {
  mpu.update();

  Serial.print("Accel X: "); Serial.print(mpu.getAccX()); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(mpu.getAccY()); Serial.print(" | ");
  Serial.print("Z: "); Serial.print(mpu.getAccZ()); Serial.print(" || ");

  Serial.print("Gyro X: "); Serial.print(mpu.getGyroX()); Serial.print(" | ");
  Serial.print("Y: "); Serial.print(mpu.getGyroY()); Serial.print(" | ");
  Serial.print("Z: "); Serial.println(mpu.getGyroZ());

  delay(5*dt);
 i++;
  if(i<=255){
  digitalWrite(m2i1, LOW);
  digitalWrite(m2i2, HIGH);
  analogWrite(m2e, i);
  digitalWrite(m1i1, LOW);
  digitalWrite(m1i2, HIGH);
  analogWrite(m1e, i);
  }
  else if (i>255&&i<510){
    digitalWrite(m2i1, LOW);
  digitalWrite(m2i2, HIGH);
  analogWrite(m2e, i-255);
  digitalWrite(m1i1, LOW);
  digitalWrite(m1i2, HIGH);
  analogWrite(m1e, i-255);
  }
  else if (i>=510){
    i=0;
  }
}