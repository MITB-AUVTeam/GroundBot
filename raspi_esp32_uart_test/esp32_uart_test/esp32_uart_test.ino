#include <HardwareSerial.h>

void setup() {
  Serial1.begin(9600, SERIAL_8N1, 5, 4);  // RX=16, TX=17
  Serial.begin(9600);
}

void loop() {
  static int count = 0;
  Serial.println(count);
  Serial1.println(count);
  delay(20);
  count++;
}