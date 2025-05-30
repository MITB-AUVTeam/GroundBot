#include <Wire.h>

int m2i1 = 26;
int m2i2 = 25;
int m2e = 27;
int m1i1 = 12;
int m1i2 = 14;
int m1e = 13;  

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