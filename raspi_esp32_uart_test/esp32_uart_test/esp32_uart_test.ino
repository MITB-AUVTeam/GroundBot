#include <HardwareSerial.h>

HardwareSerial MySerial(1);

void setup() {
  MySerial.begin(115200, SERIAL_8N1, 16, 17); // RX=16, TX=17 (change pins as needed)
}

void loop() {
  MySerial.println("Hello from ESP32");
  delay(1000);
}
