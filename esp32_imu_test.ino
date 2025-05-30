#include <Wire.h>

void setup() {
  Wire.begin(21, 22);  // Your SDA/SCL pins
  Serial.begin(115200);
  delay(1000);
  Serial.println("Scanning...");

  byte count = 0;
  for (byte addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found I2C device at 0x");
      Serial.println(addr, HEX);
      count++;
      delay(10);
    }
  }

  if (count == 0) Serial.println("No I2C devices found.");
  else Serial.println("Scan complete.");
}

void loop() {}
