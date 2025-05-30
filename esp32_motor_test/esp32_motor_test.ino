#include <Wire.h>

// Motor control pins
int m2i1 = 26;
int m2i2 = 25;
int m2e  = 27;
int m1i1 = 12;
int m1i2 = 14;
int m1e  = 13;

const int pwmFreq = 5000;
const int pwmResolution = 8;

void setup() {
  pinMode(m1i1, OUTPUT);
  pinMode(m1i2, OUTPUT);
  pinMode(m2i1, OUTPUT);
  pinMode(m2i2, OUTPUT);

  // Initialize PWM on motor enable pins
  ledcAttach(m1e, pwmFreq, pwmResolution);
  ledcAttach(m2e, pwmFreq, pwmResolution);

  Serial.begin(9600);
}

void loop() {
  // Set motor directions
  digitalWrite(m2i1, LOW);
  digitalWrite(m2i2, HIGH);
  digitalWrite(m1i1, LOW);
  digitalWrite(m1i2, HIGH);

  // Run motors at full speed (255 max for 8-bit resolution)

  for(int i = 0; i <= 255; i++)
  {
    ledcWrite(m1e, i);
    ledcWrite(m2e, i);

    delay(20);  // Run motors for 2 seconds
  }

  delay(500);

  for(int i = 255; i >= 0; i--)
  {
    ledcWrite(m1e, i);
    ledcWrite(m2e, i);

    delay(20);  // Run motors for 2 seconds
  }
  
  delay(500);
}
