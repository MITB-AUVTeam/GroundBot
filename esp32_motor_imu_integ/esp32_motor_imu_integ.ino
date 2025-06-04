#include <Arduino.h>
#include <ArduinoJson.h>

String input = "";
int m2i1 = 7;
int m2i2 = 6;
int m2e = 9;
int m1i1 = 5;
int m1i2 = 4;
int m1e = 3;

int i = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Waiting for MPU data...");
  pinMode(m1i1, OUTPUT);
  pinMode(m1i2, OUTPUT);
  pinMode(m2i1, OUTPUT);
  pinMode(m2i2, OUTPUT);
  pinMode(m1e, OUTPUT);
  pinMode(m2e, OUTPUT);
}

void loop()
{
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n') {
      StaticJsonDocument<128> doc;
      DeserializationError error = deserializeJson(doc, input);
      input = ""; // reset buffer

      if (!error)
      {
        float ax = doc["ax"];
        float ay = doc["ay"];
        float az = doc["az"];
        float gx = doc["gx"];
        float gy = doc["gy"];
        float gz = doc["gz"];

        Serial.print("AX: ");
        Serial.print(ax);
        Serial.print(" AY: ");
        Serial.print(ay);
        Serial.print(" AZ: ");
        Serial.print(az);
        Serial.print(" | GX: ");
        Serial.print(gx);
        Serial.print(" GY: ");
        Serial.print(gy);
        Serial.print(" GZ: ");
        Serial.println(gz);
      }
    } else {
      input += c;
    }
  }

  // i++;
  // if (i <= 25500)
  // {
    digitalWrite(m2i1, LOW);
    digitalWrite(m2i2, HIGH);
    analogWrite(m2e, 200);
    digitalWrite(m1i1, LOW);
    digitalWrite(m1i2, HIGH);
    analogWrite(m1e, 200);
  // }
  // else if (i > 25500 && i < 51000)
  // {
  //   digitalWrite(m2i1, LOW);
  //   digitalWrite(m2i2, HIGH);
  //   analogWrite(m2e, 255);
  //   digitalWrite(m1i1, LOW);
  //   digitalWrite(m1i2, HIGH);
  //   analogWrite(m1e, 255);
  // }
  // else if (i > 51000)
  // {
  //   i = 0;
  // }
  delay(1);
}
