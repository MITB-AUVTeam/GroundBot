#include <HardwareSerial.h>

HardwareSerial MySerial(1); // UART1

void setup() {
  // USB serial for debugging
  Serial.begin(115200);  

  // UART1 on pins RX=16, TX=17
  MySerial.begin(115200, SERIAL_8N1, 16, 17);

  Serial.println("ESP32 UART1 Started");
}

void loop() {
  const char* message = "Hello from ESP32";

  // Send to Raspberry Pi
  MySerial.println(message);
  MySerial.flush(); // Ensure all data is transmitted

  // Debug message over USB
  Serial.println("Sent: Hello from ESP32");

  delay(1000);
}
