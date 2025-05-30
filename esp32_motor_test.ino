#include <Wire.h>

int m1i1 = 2;
int m1i2 = 4;
int m1e = 15;
int m2i1 = 18;
int m2i2 = 19;
int m2e = 5;  

void setup() {
  pinMode(m1i1, OUTPUT);
  pinMode(m1i2, OUTPUT);
  pinMode(m1e, OUTPUT);
  pinMode(m2i1, OUTPUT);
  pinMode(m2i2, OUTPUT);
  pinMode(m2e, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  digitalWrite(m2i1, LOW);
  digitalWrite(m2i2, HIGH);
  digitalWrite(m1i1, LOW);
  digitalWrite(m1i2, HIGH);

  analogWrite(m1e, 255);
  analogWrite(m2e, 255);
  
}